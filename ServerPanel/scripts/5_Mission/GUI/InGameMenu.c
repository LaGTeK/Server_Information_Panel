modded class InGameMenu {
	override void RegisterButtons() {
		super.RegisterButtons();
		
		RegisterButton( "SERVER INFORMATION", "EnterServerPanelMenu" );
		}

	void EnterServerPanelMenu() {
		EnterScriptedMenu(SERVER_PANEL);
		}
}