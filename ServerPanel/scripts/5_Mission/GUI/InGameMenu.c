modded class InGameMenu {
	override void RegisterButtons() {

		RegisterButton( "#main_menu_continue", "ContinueMission" );
		RegisterButton( "#main_menu_exit", "QuitMission" );

        if ( GetGame().IsMultiplayer() )
        {
		    RegisterButton( "#main_menu_respawn", "RespawnMission", 2 );
        } else
        {
		    RegisterButton( "#main_menu_restart", "RestartMission" );
        }

		RegisterButton( "#layout_xbox_ingame_menu_options", "EnterOptionsMenu" );

		RegisterButton( "CREDITS", "EnterCreditsMenu" );

		RegisterButton( "SERVER'S INFORMATIONS", "EnterServerPanelMenu" );
    }

	void EnterServerPanelMenu() {
		EnterScriptedMenu(SERVER_PANEL);
    }
}
