//typedef array<ref SPJsonConfig> SPJsonConfigArray;
//typedef array<ref SPOldJsonConfig> SPOldJsonConfigArray;
//typedef array<ref SPJsonKeyConfig> SPJsonKeyConfigArray;

class SPJsonConfig {
	string	ServerName;
	string	Button1Name;
	string	Button1Link;
	string	Button2Name;
	string	Button2Link;
	string	Button3Name;
	string	Button3Link;
	string	ButtonTab0Name;
	string	ButtonTab1Name;
	string	ButtonTab2Name;
	string	ButtonTab3Name;
	bool	PlayerInfo;
	bool	PlayerTab;
	bool	UseScriptLog;
};

class SPOldJsonConfig {
	string ServerName, Button1Name, Button1Link, Button2Name, Button2Link, Button3Name, Button3Link, ButtonTab0Name, ButtonTab1Name, ButtonTab2Name, ButtonTab3Name;
	int		PlayerInfo;
	bool	UseScriptLog;
};

class SPJsonKeyConfig {
	string SPMenuKey;
};

ref ServerPanelMenu m_ServerPanelMenu;
ref ServerPanelMenu GetServerPanelMenu() {
	if ( !m_ServerPanelMenu ) {
		m_ServerPanelMenu = new ref ServerPanelMenu;
		m_ServerPanelMenu.Init();
		
		GetRPCManager().AddRPC( "ServerPanelI", "SyncConfig", m_ServerPanelMenu, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "ServerPanelI", "SyncTab", m_ServerPanelMenu, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "ServerPanelI", "SyncPlayers", m_ServerPanelMenu, SingeplayerExecutionType.Client );
		//GetRPCManager().AddRPC( "ServerPanelI", "SyncWeather", m_ServerPanelMenu, SingeplayerExecutionType.Client );
	}
	return m_ServerPanelMenu;
}	
