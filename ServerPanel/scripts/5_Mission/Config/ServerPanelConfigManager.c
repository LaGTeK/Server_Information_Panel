class ServerPanelConfigManager	{
	private string SERVERNAME;
	private string BUTTON1NAME;
	private string BUTTON1LINK;
	private string BUTTON2NAME;
	private string BUTTON2LINK;
	private string BUTTON3NAME;
	private string BUTTON3LINK;
	private string BUTTONTAB0NAME;
	private string BUTTONTAB1NAME;
	private string BUTTONTAB2NAME;
	private string BUTTONTAB3NAME;
	private bool DISPLAYPLAYERINFO;
	private bool DEFAULTIOFLAG;

	private ref TStringArray sServerTab0 = new ref TStringArray;
	private ref TStringArray sServerTab1 = new ref TStringArray;
	private ref TStringArray sServerTab2 = new ref TStringArray;
	private ref TStringArray sServerTab3 = new ref TStringArray;

	ServerPanelServerConfig ReadServerConfig()	{
		string fileName;
		FileAttr fileAttributes;
		FindFileHandle file = FindFile(SP_CONFIG_PATH, fileName, fileAttributes, 0);

		if (!file) {
			if (FileExist(SP_OLD_CONFIG_PATH) && FileExist(TAB0_PATH) && FileExist(TAB1_PATH) && FileExist(TAB2_PATH) && FileExist(TAB3_PATH))	{
				return OldConfig();
			}	
			else {
				return WriteDefaultServer();
			}
		}
		ServerPanelBase.Log("ServerPanelConfig", "Config File not found, trying to create Default Server Config");
		return ServerPanelServerConfig.Load();
	}

	ServerPanelClientConfig ReadClientConfig()	{
		string fileName;
		FileAttr fileAttributes;
		FindFileHandle file = FindFile(SP_CONFIGKEY_PATH, fileName, fileAttributes, 0);
		if (!file) {
			ServerPanelBase.Log("ServerPanelConfig", "Config File not found, trying to create Default Client Config");
			return WriteDefaultClient();
		}
		return ServerPanelClientConfig.Load();
	}

	ServerPanelServerConfig OldConfig()	{

		readOldJson();

		getTab0Content();
		getTab1Content();
		getTab2Content();
		getTab3Content();

		ServerPanelBase.Log("ServerPanelConfig", "Writting Default Server Config");
		ref ServerPanelServerConfig config = new ref ServerPanelServerConfig;
			
		config.SERVERNAME 			= SERVERNAME;
		config.BUTTON1NAME 			= BUTTON1NAME;
		config.BUTTON1LINK 			= BUTTON1LINK;
		config.BUTTON2NAME 			= BUTTON2NAME;
		config.BUTTON2LINK 			= BUTTON2LINK;
		config.BUTTON3NAME 			= BUTTON3NAME;
		config.BUTTON3LINK 			= BUTTON3LINK;
		config.BUTTONTAB0NAME 		= BUTTONTAB0NAME;
		config.BUTTONTAB1NAME 		= BUTTONTAB1NAME;
		config.BUTTONTAB2NAME 		= BUTTONTAB2NAME;
		config.BUTTONTAB3NAME 		= BUTTONTAB3NAME;
		config.DISPLAYPLAYERINFO	= DISPLAYPLAYERINFO;
		config.DISPLAYPLAYERTAB		= DEFAULTIOFLAG;

		int i;
		for (i = 0; i < sServerTab0.Count(); i++)
		config.sServerTab0.Insert(sServerTab0[i]);

		for (i = 0; i < sServerTab1.Count(); i++)
		config.sServerTab1.Insert(sServerTab1[i]);

		for (i = 0; i < sServerTab2.Count(); i++)
		config.sServerTab2.Insert(sServerTab2[i]);

		for (i = 0; i < sServerTab3.Count(); i++)
		config.sServerTab3.Insert(sServerTab3[i]);

		config.Save();
		return config;
	}


	ServerPanelServerConfig WriteDefaultServer()	{
		ServerPanelBase.Log("ServerPanelConfig", "Writting Default Server Config");
		ref ServerPanelServerConfig config = new ref ServerPanelServerConfig;
		for (int i = 0; i < 10; i++)	{
			config.sServerTab0.Insert("Tab0 " + i);
			config.sServerTab1.Insert("Tab1 " + i);
			config.sServerTab2.Insert("Tab2 " + i);
			config.sServerTab3.Insert("Tab3 " + i);
		}
		config.SERVERNAME 		= "Welcome on MyDAyZ server !! - Hosted By MyDayZ.eu";
		config.BUTTON1NAME 		= "DISCORD";
		config.BUTTON1LINK 		= "https://discord.gg/KAgNn6K";
		config.BUTTON2NAME 		= "WEBSITE";
		config.BUTTON2LINK 		= "https://mydayz.eu";
		config.BUTTON3NAME 		= "DONATE";
		config.BUTTON3LINK 		= "https://www.paypal.me/MyDayZ";
		config.BUTTONTAB0NAME 	= "TAB0";
		config.BUTTONTAB1NAME 	= "TAB1";
		config.BUTTONTAB2NAME 	= "TAB2";
		config.BUTTONTAB3NAME 	= "TAB3";
		config.DISPLAYPLAYERINFO= true;
		config.DISPLAYPLAYERTAB	= true;
		config.Save();
		return config;
	}

	ServerPanelClientConfig WriteDefaultClient()	{
		ServerPanelBase.Log("ServerPanelConfig", "Writting Default Client Config");
		ref ServerPanelClientConfig config = new ref ServerPanelClientConfig;
		config.SPMENUKEY = KeyCode.KC_PAUSE;

		config.Save();
		return config;
	}

	void readOldJson()	{
		ServerPanelBase.Log( "ServerPanelConfig", "Reading old json config file" );

		ref SPOldJsonConfig oldSPConfigData = new SPOldJsonConfig();

		JsonFileLoader<SPOldJsonConfig>.JsonLoadFile(SP_OLD_CONFIG_PATH, oldSPConfigData);

		SERVERNAME					= oldSPConfigData.ServerName;
		BUTTON1NAME					= oldSPConfigData.Button1Name;
		BUTTON1LINK					= oldSPConfigData.Button1Link;
		BUTTON2NAME					= oldSPConfigData.Button2Name;
		BUTTON2LINK					= oldSPConfigData.Button2Link;
		BUTTON3NAME					= oldSPConfigData.Button3Name;
		BUTTON3LINK					= oldSPConfigData.Button3Link;
		BUTTONTAB0NAME				= oldSPConfigData.ButtonTab0Name;
		BUTTONTAB1NAME				= oldSPConfigData.ButtonTab1Name;
		BUTTONTAB2NAME				= oldSPConfigData.ButtonTab2Name;
		BUTTONTAB3NAME				= oldSPConfigData.ButtonTab3Name;
		DISPLAYPLAYERINFO			= oldSPConfigData.PlayerInfo;
		DEFAULTIOFLAG 				= oldSPConfigData.UseScriptLog;

		ServerPanelBase.Log( "ServerPanelConfig", "Deleting old json file" );

		DeleteFile(SP_OLD_CONFIG_PATH);
	}

	void getTab0Content(){
		ref TStringArray serverTab0 = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int serverCounter = 0;
		bool skipLine = false;
		FileHandle configFile = OpenFile(TAB0_PATH, FileMode.READ);
		if (configFile != 0) {
			while (configFile>0)	{
				char_count = FGets(configFile,sLine);
				if (char_count == -1 || serverCounter > 8000)	{
					break;
				}
				serverTab0.Insert(sLine);

				serverCounter++;
			}
			CloseFile(configFile);
		}
		sServerTab0 = serverTab0;
		DeleteFile(TAB0_PATH);
	}
	void getTab1Content(){
		ref TStringArray serverTab1 = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int serverCounter = 0;
		bool skipLine = false;
		FileHandle configFile = OpenFile(TAB1_PATH, FileMode.READ);
		if (configFile != 0) {
			while (configFile>0)	{
				char_count = FGets(configFile,sLine);

				if (char_count == -1 || serverCounter > 8000)	{
					break;
				}
				serverTab1.Insert(sLine);

				serverCounter++;
			}
			CloseFile(configFile);
		}
		sServerTab1 = serverTab1;
		DeleteFile(TAB1_PATH);
	}
	void getTab2Content(){
		ref TStringArray serverTab2 = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int serverCounter = 0;
		bool skipLine = false;
		FileHandle configFile = OpenFile(TAB2_PATH, FileMode.READ);
		if (configFile != 0) {
			while (configFile>0)		{
				char_count = FGets(configFile,sLine);

				if (char_count == -1 || serverCounter > 8000)	{
					break;
				}
				serverTab2.Insert(sLine);

				serverCounter++;
			}
			CloseFile(configFile);
		}
		sServerTab2 = serverTab2;
		DeleteFile(TAB2_PATH);
	}
	void getTab3Content(){
		ref TStringArray serverTab3 = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int serverCounter = 0;
		bool skipLine = false;
		FileHandle configFile = OpenFile(TAB3_PATH, FileMode.READ);
		if (configFile != 0) {
			while (configFile>0)		{
				char_count = FGets(configFile,sLine);

				if (char_count == -1 || serverCounter > 8000)	{
					break;
				}
				serverTab3.Insert(sLine);

				serverCounter++;
			}
			CloseFile(configFile);
		}
		sServerTab3 = serverTab3;
		DeleteFile(TAB3_PATH);
	}
}