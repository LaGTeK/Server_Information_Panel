modded class MissionGameplay {

	void MissionGameplay()	{
		//InfoPanel
		m_ServerPanelBase = NULL;
		GetServerPanelBase();		
	}

	override void OnKeyPress( int key ) {
		super.OnKeyPress( key );
		m_Hud.KeyPress(key);

		//UIManager UIMgr = GetGame().GetUIManager();

		switch ( key ) {
			case ServerPanelBase.GetConfig().GetSPMenuKey(): {
				if (!GetUIManager().IsMenuOpen( SERVER_PANEL ) && g_Game.GetUIManager().GetMenu() == NULL)	{
					GetUIManager().EnterScriptedMenu(SERVER_PANEL, NULL);
					GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
					g_Game.GetUIManager().ShowUICursor(true);
					g_Game.GetUIManager().ShowCursor(true);
					GetGame().GetInput().ChangeGameFocus( 1 );
					GetGame().GetMission().GetHud().Show( false );
				}
				else if (GetUIManager().IsMenuOpen( SERVER_PANEL ) && !g_Game.KeyBoardStatus())	{
					g_Game.GetUIManager().ShowCursor(false);
					g_Game.GetUIManager().ShowUICursor(false);
					GetGame().GetInput().ResetGameFocus();
					GetGame().GetMission().PlayerControlEnable();
					GetGame().GetUIManager().Back();
					GetGame().GetMission().GetHud().Show( true );
				}
				break;
			}
			case KeyCode.KC_ESCAPE: {
				GetUIManager().HideDialog(); GetUIManager().CloseAll();
				if (GetUIManager().IsMenuOpen( SERVER_PANEL )) {
					g_Game.GetUIManager().ShowCursor(false);
					g_Game.GetUIManager().ShowUICursor(false);
					GetGame().GetInput().ResetGameFocus();
					GetGame().GetMission().PlayerControlEnable();
					GetGame().GetUIManager().Back();
					GetGame().GetMission().GetHud().Show( true );
				}
				break;
			}
		}
	}
};
