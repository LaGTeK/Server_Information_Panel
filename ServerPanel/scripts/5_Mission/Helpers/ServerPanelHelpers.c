class SPOldJsonConfig {
	string ServerName, Button1Name, Button1Link, Button2Name, Button2Link, Button3Name, Button3Link, ButtonTab0Name, ButtonTab1Name, ButtonTab2Name, ButtonTab3Name;
	int		PlayerInfo;
	bool	UseScriptLog;
};

static ref ServerPanelBase m_ServerPanelBase;
static ref ServerPanelBase GetServerPanelBase() {
	if ( !m_ServerPanelBase ) {
		m_ServerPanelBase = new ref ServerPanelBase;


	}
	return m_ServerPanelBase;
}

static ref ServerPanelMenu m_ServerPanelMenu;
static ref ServerPanelMenu GetServerPanelMenu() {
	if ( !m_ServerPanelMenu ) {
		m_ServerPanelMenu = new ref ServerPanelMenu;

		GetRPCManager().AddRPC( "ServerPanelI", "SyncPlayers", m_ServerPanelMenu, SingeplayerExecutionType.Client );
	}
	return m_ServerPanelMenu;
}	

static ref ServerPanelServerConfig GetServerPanelServerConfig()	{
	return GetServerPanelBase().g_ServerConfig;
}

static ref ServerPanelClientConfig GetServerPanelClientConfig()	{
	return GetServerPanelBase().g_ClientConfig;
}