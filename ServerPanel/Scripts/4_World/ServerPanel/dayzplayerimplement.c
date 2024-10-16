modded class DayZPlayerImplement
{

	//! DayZPlayer Command handler override
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		// call parent
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);

		UAInput SPKey = GetUApi().GetInputByName("SPOpenPanelMenu");
		
		if( SPKey.LocalPress() )
			ServerPanelMenuHandler();
	}

	void ServerPanelMenuHandler()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !player.IsAlive())  // Check if the player is alive
		{
			return;  // Don't open the menu if the player is not alive
		}

		// Ensure no other menus are open and no game UI elements are active
		if (!g_Game.GetUIManager().IsMenuOpen(MENU_CHAT) && !g_Game.GetUIManager().IsMenuOpen(SERVER_PANEL) && g_Game.GetUIManager().GetMenu() == NULL)
		{
			// Open the server panel menu
			g_Game.GetUIManager().EnterScriptedMenu(SERVER_PANEL, NULL);

			// Disable player controls fully
			g_Game.GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);

			// Redirect all input to the UI
			g_Game.GetInput().ChangeGameFocus(1);
			g_Game.GetUIManager().ShowCursor(true);
			g_Game.GetMission().GetHud().Show(false);

			// Disable all player actions (including weapon handling and item use)
			if (player)
				player.GetInputController().SetDisabled(true);
		}
		else if (!g_Game.GetUIManager().IsMenuOpen(MENU_CHAT) && g_Game.GetUIManager().IsMenuOpen(SERVER_PANEL))
		{
			// Reset input and re-enable player controls when closing the menu
			g_Game.GetInput().ResetGameFocus();
			g_Game.GetMission().PlayerControlEnable(true);
			g_Game.GetUIManager().Back();
			g_Game.GetMission().GetHud().Show(true);
			g_Game.GetUIManager().ShowCursor(false);

			// Re-enable all player actions
			if (player)
				player.GetInputController().SetDisabled(false);
		}
		else {
			// Reset input and re-enable player controls when closing the menu
			g_Game.GetInput().ResetGameFocus();
			g_Game.GetMission().PlayerControlEnable(true);
			g_Game.GetUIManager().Back();
			g_Game.GetMission().GetHud().Show(true);
			g_Game.GetUIManager().ShowCursor(false);

			// Re-enable all player actions
			if (player)
				player.GetInputController().SetDisabled(false);
		}
	}
}