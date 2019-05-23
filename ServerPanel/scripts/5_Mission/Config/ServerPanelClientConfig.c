class ServerPanelClientConfig {
	private 	int SPMENUKEY						= KeyCode.KC_PAUSE;

	void ServerPanelClientConfig() {
		if (GetGame().IsMultiplayer() && GetGame().IsClient()) {
			reloadKey();
		}
		
	}

	int GetSPMenuKey() {
		return SPMENUKEY;
	}

	private void createDefaultKey()	{
		ServerPanelBase.Log( "ServerPanelClientConfig", "Creating ServerPanelKey.json" );

		ref SPJsonKeyConfig newSPConfigKey = new SPJsonKeyConfig();

		newSPConfigKey.SPMenuKey = "KC_PAUSE";		

		JsonFileLoader<SPJsonKeyConfig>.JsonSaveFile(SP_CONFIGKEY_PATH, newSPConfigKey);
	}

	void reloadKey()	{
		ref SPJsonKeyConfig newSPConfigKey;

		if (FileExist(SP_CONFIGKEY_PATH)) {
			ServerPanelBase.Log( "ServerPanelClientConfig", "ConfigKey" );
			JsonFileLoader<SPJsonKeyConfig>.JsonLoadFile(SP_CONFIGKEY_PATH, newSPConfigKey);
		}
		else{
			ServerPanelBase.Log( "ServerPanelClientConfig", "File not found creating ConfigKey file " );
			createDefaultKey();
			JsonFileLoader<SPJsonKeyConfig>.JsonLoadFile(SP_CONFIGKEY_PATH, newSPConfigKey);
		}

		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) { //TO BE CHANGED v0.6 - GUI CFG
		string tempKeyCode;
		for (int i = 0; i < 126; ++i) {
			tempKeyCode = typename.EnumToString(KeyCode, i);
			if (newSPConfigKey.SPMenuKey == tempKeyCode) {
				SPMENUKEY = i;
				//ServerPanelBase.Log( "ServerPanelClientConfig", "INFO: Menu key set to " + SPMENUKEY.ToString() );
				ServerPanelBase.Log( "ServerPanelClientConfig", "INFO: Menu key set to " + tempKeyCode );
				break;
			}
		}
		if ((SPMENUKEY == KeyCode.KC_PAUSE) && (newSPConfigKey.SPMenuKey != "KC_PAUSE"))
		ServerPanelBase.Log( "ServerPanelClientConfig", "WARN: Cannot set menu key to " + newSPConfigKey.SPMenuKey + " - unknown keycode" );
		if ((SPMENUKEY == KeyCode.KC_PAUSE) && (newSPConfigKey.SPMenuKey == "KC_PAUSE"))
		ServerPanelBase.Log( "ServerPanelClientConfig", "Menu key is set to " + newSPConfigKey.SPMenuKey );
		}
	}
}
