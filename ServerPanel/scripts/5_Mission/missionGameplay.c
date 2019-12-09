modded class MissionGameplay {

	//const int SP_KEY = KeyCode.KC_PAUSE;

	void MissionGameplay()	{
		//InfoPanel
		m_ServerPanelBase = NULL;
		GetServerPanelBase();		
	}

	//override void OnKeyPress( int key ) {
	//	super.OnKeyPress( key );
	//	m_Hud.KeyPress(key);
//
	//	//UIManager UIMgr = GetGame().GetUIManager();
//
	//	switch ( key ) {
	//		case ServerPanelBase.GetConfig().GetSPMenuKey(): {
	//			if (!GetUIManager().IsMenuOpen( SERVER_PANEL ) && g_Game.GetUIManager().GetMenu() == NULL)	{
	//				GetUIManager().EnterScriptedMenu(SERVER_PANEL, NULL);
	//				GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
	//				g_Game.GetUIManager().ShowUICursor(true);
	//				g_Game.GetUIManager().ShowCursor(true);
	//				GetGame().GetInput().ChangeGameFocus( 1 );
	//				GetGame().GetMission().GetHud().Show( false );
	//			}
	//			else if (GetUIManager().IsMenuOpen( SERVER_PANEL ))	{
	//				g_Game.GetUIManager().ShowCursor(false);
	//				g_Game.GetUIManager().ShowUICursor(false);
	//				GetGame().GetInput().ResetGameFocus();
	//				GetGame().GetMission().PlayerControlEnable();
	//				GetGame().GetUIManager().Back();
	//				GetGame().GetMission().GetHud().Show( true );
	//			}
	//			break;
	//		}
	//		case KeyCode.KC_ESCAPE: {
	//			GetUIManager().HideDialog(); GetUIManager().CloseAll();
	//			if (GetUIManager().IsMenuOpen( SERVER_PANEL )) {
	//				g_Game.GetUIManager().ShowCursor(false);
	//				g_Game.GetUIManager().ShowUICursor(false);
	//				GetGame().GetInput().ResetGameFocus();
	//				GetGame().GetMission().PlayerControlEnable();
	//				GetGame().GetUIManager().Back();
	//				GetGame().GetMission().GetHud().Show( true );
	//			}
	//			break;
	//		}
	//	}
	//}

	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		m_Hud.KeyPress(key);

		SPMenu(key);
	}

	void SPMenu(int key)
	{
		if ( key == KeyCode.KC_ESCAPE && GetUIManager().IsMenuOpen( SERVER_PANEL ) )
			closeServerPanelMenu();
		return;
	}

	void closeServerPanelMenu()
	{
		g_Game.GetUIManager().ShowCursor(false);
		g_Game.GetUIManager().ShowUICursor(false);
		g_Game.GetInput().ResetGameFocus();
		g_Game.GetMission().PlayerControlEnable(true);
		g_Game.GetUIManager().Back();
		g_Game.GetMission().GetHud().Show( true );
		return;
	}

};
