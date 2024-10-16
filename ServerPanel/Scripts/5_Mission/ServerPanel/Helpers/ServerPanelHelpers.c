static ref ServerPanelBase m_ServerPanelBase;
static ref ServerPanelMenu m_ServerPanelMenu;

static ServerPanelBase GetServerPanelBase() {
    if (!m_ServerPanelBase) {
        m_ServerPanelBase = new ServerPanelBase();
        ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelHelpers", "Initialized ServerPanelBase");
    }
    return m_ServerPanelBase;
}

static ref ServerPanelServerConfig GetServerPanelServerConfig()	{
	return GetServerPanelBase().g_ServerConfig;
}

static ServerPanelMenu GetServerPanelMenu() {
    if (!m_ServerPanelMenu) {
        m_ServerPanelMenu = new ServerPanelMenu();
        ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelHelpers", "Initialized ServerPanelMenu");

        if (!GetRPCManager().AddRPC("ServerPanelStatsRPC", "SyncPlayerStats", m_ServerPanelMenu, SingeplayerExecutionType.Client)) {
            ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelHelpers", "Failed to add RPC: SyncPlayerStats");
        }
        if (!GetRPCManager().AddRPC("ServerPanelStatsRPC", "SyncSidePanelInfo", m_ServerPanelMenu, SingeplayerExecutionType.Client)) {
            ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelHelpers", "Failed to add RPC: SyncSidePanelInfo");
        }
    }
    return m_ServerPanelMenu;
}