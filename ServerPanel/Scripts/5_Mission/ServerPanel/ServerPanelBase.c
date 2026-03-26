class ServerPanelBase 
{
	int m_LogLevel;
	private int m_AutoOpenTryCount;
	private const int SP_AUTOOPEN_MAX_TRIES = 240; // 240 * 250ms = 60s max
	// Client: one auto-open eligibility request per mission (does not rely on modded MissionServer / InvokeOnConnect).
	private bool m_SPAutoOpenClientRequestScheduled;

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
			GetRPCManager().AddRPC("ServerPanelAutoOpenRPC", "RequestAutoOpenIfEligible", this, SingeplayerExecutionType.Server);

		}
		else	{
			//Client calls
			if (m_LogLevel) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfigRPC", "ConfigResponse");
			}
			GetRPCManager().AddRPC("ServerPanelConfigRPC", "GetConfigResponse", this, SingeplayerExecutionType.Client);
			GetRPCManager().SendRPC("ServerPanelConfigRPC", "GetConfigRequest", NULL, true, NULL);
		}

		if (g_Game.IsClient()) {
			GetRPCManager().AddRPC("ServerPanelAutoOpenRPC", "OpenPanel", this, SingeplayerExecutionType.Client);
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

		ScheduleClientAutoOpenRequestIfNeeded(cached);
	}

	// Client: ask server to open panel once (server uses AutoOpenSeen.json + config). Works even if MissionServer.InvokeOnConnect is not chained by other mods.
	private void ScheduleClientAutoOpenRequestIfNeeded(ServerPanelServerConfig cfg)
	{
		if (!cfg) {
			return;
		}
		if (!cfg.AUTO_OPEN_ON_FIRST_JOIN) {
			return;
		}
		if (m_SPAutoOpenClientRequestScheduled) {
			return;
		}
		m_SPAutoOpenClientRequestScheduled = true;
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SendAutoOpenRequestToServer, 4000, false);
	}

	private void SendAutoOpenRequestToServer()
	{
		GetRPCManager().SendRPC("ServerPanelAutoOpenRPC", "RequestAutoOpenIfEligible", NULL, true, NULL);
	}

	// Server: client asks if first-join auto-open should run; no dependency on obfuscated MissionServer overrides.
	void RequestAutoOpenIfEligible(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Server || !g_Game.IsServer()) {
			return;
		}
		if (!sender) {
			return;
		}

		ServerPanelServerConfig cfg = ServerPanelConfigManager.GetConfig();
		if (!cfg || !cfg.AUTO_OPEN_ON_FIRST_JOIN) {
			return;
		}

		string pid = sender.GetId();
		if (ServerPanelAutoOpenStateManager.HasSeen(pid)) {
			return;
		}

		GetRPCManager().SendRPC("ServerPanelAutoOpenRPC", "OpenPanel", NULL, true, sender);
		ServerPanelAutoOpenStateManager.MarkSeen(pid);
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

	// Client-side: invoked by server to open the panel.
	void OpenPanel(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client || !g_Game.IsClient()) {
			return;
		}

		m_AutoOpenTryCount = 0;
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(TryOpenPanelWhenReady, 250, true);
	}

	private void TryOpenPanelWhenReady()
	{
		m_AutoOpenTryCount++;
		if (m_AutoOpenTryCount > SP_AUTOOPEN_MAX_TRIES) {
			g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(TryOpenPanelWhenReady);
			return;
		}

		MissionGameplay gameplayMission = MissionGameplay.Cast(g_Game.GetMission());
		if (!gameplayMission) {
			return;
		}

		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player) {
			return;
		}
		if (!player.IsPlayerLoaded()) {
			return;
		}
		if (!player.IsAlive()) {
			return;
		}
		if (!player.GetIdentity()) {
			return;
		}
		if (!g_Game.GetMission() || !g_Game.GetMission().GetHud()) {
			return;
		}
		if (g_Game.GetUIManager().IsMenuOpen(SERVER_PANEL)) {
			g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(TryOpenPanelWhenReady);
			return;
		}
		// LBmaster_Core / LBmaster_Spawnsystem: SpawnSelectMenu extends LBMenuBase -> UIScriptedMenu and is shown via
		// LBMenuManager.OpenMenu -> GetUIManager().ShowScriptedMenu. GetOpenLBMenu() is Cast(GetMenu()), so any open LB menu
		// already makes GetMenu() non-null and is blocked here (no #ifdef LBMASTER_SPAWN_SELECT needed).
		if (g_Game.GetUIManager().GetMenu() != NULL) {
			return;
		}

		// Expansion script-view menus use ExpansionUIManager, not vanilla UIManager (GetMenu() can be null).
		// EXPANSIONMODCORE: 0_DayZExpansion_Core_Preload / DayZExpansion_Core_Defines.c
		// EXPANSIONMODSPAWNSELECTION: 0_DayZExpansion_SpawnSelection_Preload / DayZExpansion_SpawnSelection_Defines.c (m_Expansion_SpawnSelect)
#ifdef EXPANSIONMODCORE
		DayZGame expansionDayZGame = GetDayZGame();
		if (expansionDayZGame)
		{
			ExpansionGame expansionGame = expansionDayZGame.GetExpansionGame();
			if (expansionGame)
			{
				ExpansionUIManager expansionUiMgr = expansionGame.GetExpansionUIManager();
				if (expansionUiMgr && expansionUiMgr.GetMenu())
				{
					return;
				}
			}
		}
#ifdef EXPANSIONMODSPAWNSELECTION
		if (player.m_Expansion_SpawnSelect)
		{
			return;
		}
#endif
#endif

		g_Game.GetUIManager().EnterScriptedMenu(SERVER_PANEL, NULL);
		g_Game.GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
		g_Game.GetInput().ChangeGameFocus(1);
		g_Game.GetUIManager().ShowCursor(true);
		g_Game.GetMission().GetHud().Show(false);
		player.GetInputController().SetDisabled(true);

		g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(TryOpenPanelWhenReady);
	}
};
