modded class MissionGameplay {
	ref ServerPanelBase m_ServerPanelBase;
	ref ServerPanelMenu m_ServerPanelMenu;

	void MissionGameplay() {
		ServerPanelBase.Log("ServerPanelI", "ServerPanel Loaded Client side");
		//GetRPCManager().AddRPC( "ServerPanelI", "SyncKey", m_ServerPanelMenu, SingeplayerExecutionType.Client );

		//GetRPCManager().SendRPC( "ServerPanelI", "SyncSNameTabsRequest", new Param1< int >( 0 ), true, NULL );
		//GetRPCManager().SendRPC( "ServerPanelI", "SyncPlayersRequest", new Param1< int >( 0 ), true, NULL );
		//GetRPCManager().SendRPC( "ServerPanelI", "SyncButtonRequest", new Param1< int >( 0 ), true, NULL );
		
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
			m_ServerPanelMenu.Init();
			//GetRPCManager().AddRPC( "ServerPanelI", "SyncKey", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			GetRPCManager().AddRPC( "ServerPanelI", "SyncButtons", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			GetRPCManager().AddRPC( "ServerPanelI", "SyncSNameTabs", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			GetRPCManager().AddRPC( "ServerPanelI", "SyncTab", m_ServerPanelMenu, SingeplayerExecutionType.Client );
			GetRPCManager().AddRPC( "ServerPanelI", "SyncPlayers", m_ServerPanelMenu, SingeplayerExecutionType.Client );

			
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
};