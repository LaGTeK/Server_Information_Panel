modded class InGameMenu {
	override void RegisterButtons() {
		super.RegisterButtons();
		
		RegisterButton( "SERVER INFORMATIONS", "EnterServerPanelMenu" );
		}

	void EnterServerPanelMenu() {
		EnterScriptedMenu(SERVER_PANEL);
		}
}
