modded class InGameMenu {
	override void RegisterButtons() {
		RegisterButton( "CREDITS", "OnClick_Credits" );
		RegisterButton( "SERVER INFORMATIONS", "EnterServerPanelMenu" );
		}

	void EnterServerPanelMenu() {
		EnterScriptedMenu(SERVER_PANEL);
		}
}
