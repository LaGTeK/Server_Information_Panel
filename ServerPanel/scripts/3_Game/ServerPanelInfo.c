modded class DayZGame {

	void DayZGame()	{
		Print("SERVER PANEL OPENNING!");
	}

	void DisplayPanel() {
		GetRPCManager().SendRPC( "RPC_ShowPanelRemote", "ShowPanelRemote", NULL, true);
		//GetRPCManager().SendRPC( "ServerPanelI", "RPC_ServerPanelMenu", new Param1< bool >( true ), true, NULL );
		//UIManager UIMgr = GetGame().GetUIManager();
		//UIMgr.ShowScriptedMenu( GetServerPanelMenu() , NULL )
	}
}
