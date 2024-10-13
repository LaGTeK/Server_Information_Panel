class ServerPanelServerConfig
{
	string SERVERNAME;
	string BUTTON1NAME;
	string BUTTON1LINK;
	string BUTTON2NAME;
	string BUTTON2LINK;
	string BUTTON3NAME;
	string BUTTON3LINK;
	string BUTTONTAB0NAME;
	string BUTTONTAB1NAME;
	string BUTTONTAB2NAME;
	string BUTTONTAB3NAME;
	bool DISPLAYPLAYERINFO;
	bool DISPLAYPLAYERTAB;

	ref TStringArray sServerTab0 = new ref TStringArray;
	ref TStringArray sServerTab1 = new ref TStringArray;
	ref TStringArray sServerTab2 = new ref TStringArray;
	ref TStringArray sServerTab3 = new ref TStringArray;


	void Save()
	{
		JsonFileLoader<ServerPanelServerConfig>.JsonSaveFile(SP_CONFIG_PATH, this);
	}

	static ref ServerPanelServerConfig Load()
	{
		ref ServerPanelServerConfig config = new ref ServerPanelServerConfig;
		JsonFileLoader<ServerPanelServerConfig>.JsonLoadFile(SP_CONFIG_PATH, config);
		return config;
	}
}