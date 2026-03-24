class ServerPanelBase 
{
	int m_LogLevel;

    void ServerPanelBase() 
	{
        if (g_Game.IsServer()) 
		{
			Print("[ServerPanel] Loading server configuration...");
            ServerPanelConfigManager.SetConfig();
			if (!ServerPanelConfigManager.GetConfig()) 
			{
				Print("[ServerPanel] ERROR: Failed to load server configuration.");
				return;
			}

			ServerPanelServerConfig cfg = ServerPanelConfigManager.GetConfig();
			m_LogLevel = cfg.LOGLEVEL;
			ServerPanelLogger.SetLogLevel(m_LogLevel);

			if (cfg.DISABLE_PANEL_LOG_FILE) {
				ServerPanelLogger.SetConsoleOnly();
				Print("[ServerPanel] File logging disabled (DISABLE_PANEL_LOG_FILE). ServerPanelLogger -> console only (see LOGLEVEL).");
			} else {
				ServerPanelLogger.SwitchToCustomIO();
			}

			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Server configuration loaded.");
        }

        InitRPC();
    }

	void InitRPC() {
		if (g_Game.IsServer())	{
			//Server calls
			if (m_LogLevel) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfigRPC", "GetConfigRequest");
			}
			GetRPCManager().AddRPC("ServerPanelConfigRPC", "GetConfigRequest", this, SingeplayerExecutionType.Server);
			
			if (m_LogLevel) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelStatsRPC", "SyncPanelStatsRequest");
			}
			GetRPCManager().AddRPC("ServerPanelStatsRPC", "SyncPanelStatsRequest", this, SingeplayerExecutionType.Server);

		}
		else	{
			//Client calls
			if (m_LogLevel) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfigRPC", "ConfigResponse");
			}
			GetRPCManager().AddRPC("ServerPanelConfigRPC", "GetConfigResponse", this, SingeplayerExecutionType.Client);
			GetRPCManager().SendRPC("ServerPanelConfigRPC", "GetConfigRequest", NULL, true, NULL);
		}
	}

    //void GetConfigRequest(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)	
	void GetConfigRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (!g_Game.IsServer())
			return;
	
		ref ServerPanelServerConfig config = ServerPanelConfigManager.GetConfig();
		if (!config)
		{
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfigRPC", "No server config available to send.");
			return; // On n'envoie rien si pas prêt
		}
		
		GetRPCManager().SendRPC("ServerPanelConfigRPC", "GetConfigResponse", new Param1<ref ServerPanelServerConfig>(ServerPanelConfigManager.GetConfig()), true, sender);
		
		if (m_LogLevel) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfigRPC", sender.GetName() + " (" + sender.GetId() + ") - Config sync");
		}
	}

	//void GetConfigResponse(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) 
	void GetConfigResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (!g_Game.IsClient()) return;

		Param1<ref ServerPanelServerConfig> data;
		if (!ctx.Read(data)) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfig", "Failed to read config data from server response.");
			return;
		}

		// Mise en cache de la configuration localement sur le client
		ServerPanelConfigManager.SetConfig(data.param1);
		ServerPanelServerConfig cached = ServerPanelConfigManager.GetConfig();
		if (cached) {
			m_LogLevel = cached.LOGLEVEL;
			ServerPanelLogger.SetLogLevel(m_LogLevel);
		}
		
		if (m_LogLevel) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Configuration received and cached from server.");
		}
	}

	// Payload selon ServerPanel.json serveur : side panel (DISPLAYPLAYERINFO), onglet joueur (DISPLAYPLAYERTAB), liste (DISPLAYPLAYERLIST).
	// sideInts = [heure, sante, sang] si side ; sinon [sante, sang] seulement si onglet joueur seul.
	void SyncPanelStatsRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Server || !g_Game.IsServer()) return;

		ref TStringArray playerListS = new TStringArray();
		ref TIntArray sideInts = new TIntArray();
		ref TFloatArray playerTabFloats = new TFloatArray();
		ref TFloatArray sideHydration = new TFloatArray();
		vector plyPos = "0 0 0";
		string playerName = "";
		string playerId = "";
		bool hasDisease = false;

		ref ServerPanelServerConfig cfg = ServerPanelConfigManager.GetConfig();
		bool wantSide = cfg && cfg.DISPLAYPLAYERINFO;
		bool wantTab = cfg && cfg.DISPLAYPLAYERTAB;
		bool wantList = wantSide && cfg && cfg.DISPLAYPLAYERLIST;

		array<Man> players = new array<Man>();

		if (wantList) {
			g_Game.GetPlayers(players);
			for (int i = 0; i < players.Count(); ++i) {
				PlayerBase player = PlayerBase.Cast(players.Get(i));
				if (!player) {
					ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_WARN, "ServerPanelStatsRPC", "Failed to cast player at index " + i);
					continue;
				}

				PlayerIdentity plyIdent = player.GetIdentity();
				if (!plyIdent) {
					ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_WARN, "ServerPanelStatsRPC", "Player identity is null for player at index " + i);
					continue;
				}

				playerListS.Insert(plyIdent.GetName());
			}
		}

		if (sender) {
			playerId = sender.GetId();
			PlayerBase requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
			if (wantSide) {
				playerName = sender.GetName();
			}

			if (requestingPlayer) {
				if (wantSide) {
					sideInts.Insert(g_Game.GetTime());
					sideInts.Insert(requestingPlayer.GetHealth());
					sideInts.Insert(requestingPlayer.GetHealth("", "Blood"));
					sideHydration.Insert(requestingPlayer.GetStatWater().Get());
					sideHydration.Insert(requestingPlayer.GetStatEnergy().Get());
					plyPos = requestingPlayer.GetPosition();
				}

				if (wantTab) {
					if (!wantSide) {
						sideInts.Insert(requestingPlayer.GetHealth());
						sideInts.Insert(requestingPlayer.GetHealth("", "Blood"));
					}

					playerTabFloats.Insert(requestingPlayer.GetHealth("", "Shock"));
					playerTabFloats.Insert(requestingPlayer.GetStatStamina().Get());
					playerTabFloats.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_DISTANCE));
					playerTabFloats.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_PLAYTIME));
					playerTabFloats.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_PLAYERS_KILLED));
					playerTabFloats.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_INFECTED_KILLED));
					playerTabFloats.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_LONGEST_SURVIVOR_HIT));

					MissionServer missionServer = MissionServer.Cast(g_Game.GetMission());
					if (missionServer) {
						playerTabFloats.Insert(missionServer.GetServerUptime());
					} else {
						playerTabFloats.Insert(0);
					}

					hasDisease = requestingPlayer.HasDisease();
				}
			} else {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_WARN, "ServerPanelStatsRPC", "Failed to cast sender's player.");
			}
		} else {
			playerId = "Unknown ID";
		}

		GetRPCManager().SendRPC("ServerPanelStatsRPC", "SyncPanelStats", new Param7<ref TStringArray, ref TIntArray, ref TFloatArray, ref TFloatArray, vector, string, bool>(playerListS, sideInts, playerTabFloats, sideHydration, plyPos, playerName, hasDisease), true, sender);

		if (m_LogLevel) {
			string logNick = playerName;
			if (logNick == "" && sender) {
				logNick = sender.GetName();
			}
			if (logNick == "") {
				logNick = "Unknown";
			}
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelStatsRPC", logNick + " (" + playerId + ") - Panel stats sync");
		}
	}
};
