class ServerPanelServerConfig
{
	string VERSION;  // Use text for versioning, now at the top
	string SERVERNAME;
	int LOGLEVEL;
	string BUTTON1NAME;
	string BUTTON1LINK;
	string BUTTON2NAME;
	string BUTTON2LINK;
	string BUTTON3NAME;
	string BUTTON3LINK;
	bool DISPLAYPLAYERINFO;
	bool DISPLAYPLAYERTAB;
	bool DISPLAYPLAYERLIST;
	bool DISPLAYPLAYERPOSITION;
    bool DISPLAYCRAFTTAB;
	bool DISPLAYCURRENCY;
	string CURRENCYNAME;
	bool DISPLAYPLOGO;
	string LOGOPATH;  
	float LOGO_WIDTH_PERCENTAGE;
	float LOGO_HEIGHT_PERCENTAGE;
	string BUTTONTAB0NAME;
	string BUTTONTAB1NAME;
	string BUTTONTAB2NAME;
	string BUTTONTAB3NAME;

	ref TStringArray sServerTab0= new ref TStringArray;
	ref TStringArray sServerTab1 = new ref TStringArray;
	ref TStringArray sServerTab2 = new ref TStringArray;
	ref TStringArray sServerTab3 = new ref TStringArray;

	void Save(string m_SP_FILE_PATH) {
		string errorMessage;
		if (JsonFileLoader<ServerPanelServerConfig>.SaveFile(m_SP_FILE_PATH, this, errorMessage)) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Configuration saved successfully.");
		} else {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfig", "Failed to save configuration: " + errorMessage);
		}
	}

	static ref ServerPanelServerConfig Load(string configPath)
	{
		ref ServerPanelServerConfig config = new ref ServerPanelServerConfig;
		JsonFileLoader<ServerPanelServerConfig>.JsonLoadFile(configPath, config);
		return config;
	}
}
