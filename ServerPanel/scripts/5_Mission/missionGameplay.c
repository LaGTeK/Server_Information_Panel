modded class MissionGameplay {
	ref ServerPanelBase m_ServerPanelBase;
	ref ServerPanelMenu m_ServerPanelMenu;

	void MissionGameplay() {
		ServerPanelBase.Log("ServerPanelI", "ServerPanel Loaded Client side");

		//GetRPCManager().AddRPC( "RPC_ShowPanelRemote", "ShowPanelRemote", this, SingeplayerExecutionType.Client );
	}

    void ~MissionGameplay()	{
		
	}

	private ref ServerPanelBase GetServerPanelBase() {
		if ( !m_ServerPanelBase ) {
			m_ServerPanelBase = new ref ServerPanelBase;
		}
		return m_ServerPanelBase;
	}

	private ref ServerPanelMenu GetServerPanelMenu() {
		if ( !m_ServerPanelMenu ) {
			m_ServerPanelMenu = new ref ServerPanelMenu;
			if (m_ServerPanelMenu != NULL)
			{
			m_ServerPanelMenu.Init();
			GetRPCManager().AddRPC( "RPC_ShowPanelRemote", "ShowPanelRemote", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			//GetRPCManager().AddRPC( "ServerPanelI", "SyncKey", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			GetRPCManager().AddRPC( "ServerPanelI", "SyncButtons", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			GetRPCManager().AddRPC( "ServerPanelI", "SyncSNameTabs", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			GetRPCManager().AddRPC( "ServerPanelI", "SyncTab", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			GetRPCManager().AddRPC( "ServerPanelI", "SyncPlayers", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			}
		}
		return m_ServerPanelMenu;
	}

	override void OnKeyPress( int key ) {
		super.OnKeyPress( key );
		UIManager UIMgr = GetGame().GetUIManager();
		if (GetServerPanelMenu().GetLayoutRoot().IsVisible()) {
			GetServerPanelMenu().OnKeyPress( key );
		}
		switch ( key ) {
			case ServerPanelBase.GetConfig().GetSPMenuKey(): {
				if (!GetServerPanelMenu().GetLayoutRoot().IsVisible() && !UIMgr.IsMenuOpen(MENU_INGAME)) {
					UIMgr.HideDialog(); UIMgr.CloseAll();
					UIMgr.ShowScriptedMenu( GetServerPanelMenu() , NULL );
					PlayerControlEnable();
				}
				break;
			}
			case KeyCode.KC_ESCAPE: {
				UIMgr.HideDialog(); UIMgr.CloseAll();
				break;
			}
		}
	}

	void ShowPanelRemote( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
        //Answer call only when client...MissionGameplay runs client only anyway but still add it :P
        if (type == CallType.Client)
        {
        	//Check if sender is still connected to not trigger an Null pointers
        	if (sender != NULL){
        		//Show menu ( you can call another function from here to show menu if you have made a custom one )
        		//you might need to make a loop to check if player's screen is not black or has another GUI....then display yours
				ServerPanelBase.Log("ServerPanelI", "ShowPanelRemote");
        		GetGame().GetUIManager().ShowScriptedMenu( GetServerPanelMenu() , NULL );
				PlayerControlEnable();
        	}
        }
	}
};