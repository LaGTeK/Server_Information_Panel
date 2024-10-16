class ServerPanelBase {
    ref ServerPanelServerConfig g_ServerConfig;
	bool m_LogLevel;
	
	//private bool displayPlayerTab = g_ServerConfig && g_ServerConfig.DISPLAYPLAYERTAB;

    void ServerPanelBase() {
        if (GetGame().IsServer()) {
        	ServerPanelLogger.SwitchToCustomIO();
            // Load configuration when the server starts
            ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Reading Server Config");
            g_ServerConfig = ServerPanelConfigManager.GetConfig();
			m_LogLevel = g_ServerConfig.LOGLEVEL;

            // Check if configuration loaded properly
            if (!g_ServerConfig) {
                ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfig", "Failed to load server configuration.");
                return;
            }
        }

        InitRPC();
    }

	void InitRPC() {
		if (GetGame().IsServer())	{
			//Server calls
			if (m_LogLevel) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfigRPC", "GetConfigRequest");
			}
			GetRPCManager().AddRPC("ServerPanelConfigRPC", "GetConfigRequest", this, SingeplayerExecutionType.Server);
			
			if (m_LogLevel) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfigRPC", "SyncPlayerStatsRequest");
			}
			GetRPCManager().AddRPC("ServerPanelStatsRPC", "SyncPlayerStatsRequest", this, SingeplayerExecutionType.Server);

			
			if (m_LogLevel) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfigRPC", "SyncSidePanelInfoRequest");
			}
			GetRPCManager().AddRPC("ServerPanelStatsRPC", "SyncSidePanelInfoRequest", this, SingeplayerExecutionType.Server);

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

    void GetConfigRequest(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)	{
		if (!GetGame().IsServer())
			return;
		GetRPCManager().SendRPC("ServerPanelConfigRPC", "GetConfigResponse", new Param1<ref ServerPanelServerConfig>(g_ServerConfig), true, sender);
		
		if (m_LogLevel) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfigRPC", sender.GetName() + " (" + sender.GetId() + ") - Config sync");
		}
	}

	void GetConfigResponse(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
		if (!GetGame().IsClient()) return;

		Param1<ref ServerPanelServerConfig> data;
		if (!ctx.Read(data)) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfig", "Failed to read config data from server response.");
			return;
		}

		// Mise en cache de la configuration localement sur le client
		g_ServerConfig = data.param1;
		
		if (m_LogLevel) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Configuration received and cached from server.");
		}
	}

	void SyncPlayerStatsRequest(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
		if (type != CallType.Server || !GetGame().IsServer()) return;

		ref TIntArray plyIData = new TIntArray();
		ref TFloatArray plyFData = new TFloatArray();
		bool m_HasDisease = false;

		// Corrected string assignment using standard if-else
		string playerName;
		string playerId;

		// Collect stats for the requesting player only
		if (sender) {
			playerName = sender.GetName();
			playerId = sender.GetId();
			PlayerBase requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
			if (requestingPlayer) {
				plyIData.Insert(requestingPlayer.GetHealth());
				plyIData.Insert(requestingPlayer.GetHealth("", "Blood"));
				plyFData.Insert(requestingPlayer.GetHealth("", "Shock"));
				plyFData.Insert(requestingPlayer.GetStatStamina().Get());
				plyFData.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_DISTANCE));
				plyFData.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_PLAYTIME));
				plyFData.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_PLAYERS_KILLED));
				plyFData.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_INFECTED_KILLED));
				plyFData.Insert(requestingPlayer.StatGet(AnalyticsManagerServer.STAT_LONGEST_SURVIVOR_HIT));
				m_HasDisease = requestingPlayer.HasDisease();
			} else {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelStatsRPC", "Failed to cast sender's player.");
			}
		}	
		else {
			playerName = "Unknown";
			playerId = "Unknown ID";
		}

		// Send the data back to the client
		GetRPCManager().SendRPC("ServerPanelStatsRPC", "SyncPlayerStats", new Param3<ref TIntArray, ref TFloatArray, bool>(plyIData, plyFData, m_HasDisease), true, sender);
		
		if (m_LogLevel) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelStatsRPC", playerName + " (" + playerId + ") - Player Stats sync");
		}
	}

	void SyncSidePanelInfoRequest(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
		if (type != CallType.Server || !GetGame().IsServer()) return;

		ref TStringArray playerListS = new TStringArray();
		ref TIntArray plyIData = new TIntArray();
		ref TFloatArray plyFData = new TFloatArray();
		vector plyPos;

		array<Man> players = new array<Man>();
		GetGame().GetPlayers(players);

		bool displayPlayerList = g_ServerConfig && g_ServerConfig.DISPLAYPLAYERLIST;
		
		// Collect all player pseudonyms if displayPlayerList is true
		if (displayPlayerList) {
			for (int i = 0; i < players.Count(); ++i) {
				PlayerBase player = PlayerBase.Cast(players.Get(i));
				if (!player) {
					ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelStatsRPC", "Failed to cast player at index " + i);
					continue;
				}

				PlayerIdentity plyIdent = player.GetIdentity();
				if (!plyIdent) {
					ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelStatsRPC", "Player identity is null for player at index " + i);
					continue;
				}

				playerListS.Insert(plyIdent.GetName());
			}
		} else {
			playerListS=new TStringArray();
		}

		// Corrected string assignment using standard if-else
		string playerName;
		string playerId;

		// Collect stats for the requesting player only
		if (sender) {
			playerName = sender.GetName();
			playerId = sender.GetId();
			PlayerBase requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
			if (requestingPlayer) {
				plyIData.Insert(GetGame().GetTime());
				plyIData.Insert(requestingPlayer.GetHealth());
				plyIData.Insert(requestingPlayer.GetHealth("", "Blood"));
				plyFData.Insert(requestingPlayer.GetStatWater().Get());
				plyFData.Insert(requestingPlayer.GetStatEnergy().Get());
				plyPos = requestingPlayer.GetPosition();
			} 
			else {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelStatsRPC", "Failed to cast sender's player.");
			}
		} 
		else {
			playerName = "Unknown";
			playerId = "Unknown ID";
		}

		// Send the data back to the client
		GetRPCManager().SendRPC("ServerPanelStatsRPC", "SyncSidePanelInfo", new Param5<ref TStringArray, ref TIntArray, ref TFloatArray, vector, string>(playerListS, plyIData, plyFData, plyPos, playerName), true, sender);
		
		if (m_LogLevel) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelStatsRPC", playerName + " (" + playerId + ") - Player Minimum Stats sync");
		}
	}
};
