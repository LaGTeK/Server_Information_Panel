modded class DayZPlayerImplement
{

	//! DayZPlayer Command handler override
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		// call parent
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);

		UAInput SPKey = GetUApi().GetInputByName("SPOpenPanelMenu");
		
		if( SPKey.LocalClick() )
			ServerPanelMenuHandler();
	}

    void ServerPanelMenuHandler()
    {
        if ( !g_Game.GetUIManager().IsMenuOpen( MENU_CHAT ) && !g_Game.GetUIManager().IsMenuOpen( SERVER_PANEL ) && g_Game.GetUIManager().GetMenu() == NULL )
		{
			g_Game.GetUIManager().EnterScriptedMenu(SERVER_PANEL, NULL);
			g_Game.GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
			g_Game.GetUIManager().ShowUICursor(true);
			g_Game.GetUIManager().ShowCursor(true);
			g_Game.GetInput().ChangeGameFocus( 1 );
			g_Game.GetMission().GetHud().Show( false );
			LockControls();
		}
		else if ( !g_Game.GetUIManager().IsMenuOpen( MENU_CHAT ) && g_Game.GetUIManager().IsMenuOpen( SERVER_PANEL ) )
		{
			closeServerPanelMenu();
			UnlockControls();
		}
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

	void LockControls()
	{
		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
		GetGame().GetUIManager().ShowUICursor( true );
		GetGame().GetMission().GetHud().Show( false );
	}
	
	void UnlockControls()
	{
		GetGame().GetMission().PlayerControlEnable(false);
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetUIManager().ShowUICursor( false );
		GetGame().GetMission().GetHud().Show( true );
	}
}