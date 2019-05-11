class ServerPanelConfig {
	private 	string CFG_PATH 					= "$saves:";
	private 	string CFG_PATH_SERVER				= "$profile:";
	private 	string realProfilesPath				= "";
	private 	string SERVERNAME					= "Welcome on MyDAyZ server !! - Hosted By MyDayZ.eu";
	private 	string BUTTON1NAME					= "DISCORD";
	private 	string BUTTON1LINK					= "https://discord.gg/KAgNn6K";
	private 	string BUTTON2NAME					= "WEBSITE";
	private 	string BUTTON2LINK					= "https://mydayz.eu";
	private 	string BUTTON3NAME					= "DONATE";
	private 	string BUTTON3LINK					= "https://www.paypal.me/MyDayZ";
	private 	string BUTTONTAB0NAME				= "TAB0";
	private 	string BUTTONTAB1NAME				= "TAB1";
	private 	string BUTTONTAB2NAME				= "TAB2";
	private 	string BUTTONTAB3NAME				= "TAB3";
	private 	int SPMENUKEY						= KeyCode.KC_PAUSE;
	private 	bool DEFAULTIOFLAG					= false;
	private		bool DISPLAYPLAYERINFO				= true;
	private		bool DISPLAYPLAYERTAB				= true;
	private ref TStringArray sServerTab0			= new TStringArray;
	private ref TStringArray sServerTab1			= new TStringArray;
	private ref TStringArray sServerTab2			= new TStringArray;
	private ref TStringArray sServerTab3			= new TStringArray;


	void ServerPanelConfig() {
		if (GetGame().IsMultiplayer() && GetGame().IsServer()) {
			if (!GetCLIParam("profiles", realProfilesPath)) ServerPanelBase.Log( "ServerPanelConfig", "WARN: \"-profiles=<FOLDERNAME>\" launch parameter is NOT set!!!" );
				else ServerPanelBase.Log( "ServerPanelConfig", "INFO: Profile dir is: " + realProfilesPath);

			CFG_PATH = CFG_PATH_SERVER;

			if (FileExist(CFG_PATH + "ServerPanel\\")) {

				CFG_PATH += "ServerPanel\\";
			} else {
				if (realProfilesPath != "") ServerPanelBase.Log( "ServerPanelConfig", "WARN: Can't create ServerPanel subfolder (" + realProfilesPath + "\\ServerPanel\\), please create one manually!" );
				else ServerPanelBase.Log( "ServerPanelConfig", "WARN: Can't create ServerPanel subfolder (" + CFG_PATH + "ServerPanel\\), please create one manually!" );
			}
		reloadTab();
		reloadConfig();
		}

		if (realProfilesPath != "") ServerPanelBase.Log( "ServerPanelConfig", "INFO: Config files will be loaded from: " + realProfilesPath );
		else ServerPanelBase.Log( "ServerPanelConfig", "INFO: Config files will be loaded from: " + CFG_PATH );
		if (GetGame().IsMultiplayer() && GetGame().IsClient()) {
			reloadKey();
		}
		
	}

	string GetProfilesPath() {
		return realProfilesPath;
	}
	string GetServerName() {
		return SERVERNAME;
	}
	string GetButton1Name() {
		return BUTTON1NAME;
	}
	string GetButton1Link() {
		return BUTTON1LINK;
	}
	string GetButton2Name() {
		return BUTTON2NAME;
	}
	string GetButton2Link() {
		return BUTTON2LINK;
	}
	string GetButton3Name() {
		return BUTTON3NAME;
	}
	string GetButton3Link() {
		return BUTTON3LINK;
	}
	string GetButtonTab0Name() {
		return BUTTONTAB0NAME;
	}
	string GetButtonTab1Name() {
		return BUTTONTAB1NAME;
	}
	string GetButtonTab2Name() {
		return BUTTONTAB2NAME;
	}
	string GetButtonTab3Name() {
		return BUTTONTAB3NAME;
	}
	int GetSPMenuKey() {
		return SPMENUKEY;
	}
	bool IsDefaultIO() {
		return DEFAULTIOFLAG;
	}
	bool GetDisplayPlayerInfo() {
		return DISPLAYPLAYERINFO;
	}
	bool GetDisplayPlayerTab() {
		return DISPLAYPLAYERTAB;
	}
	ref TStringArray GetTab0Data(){
		return sServerTab0;
	}
	ref TStringArray GetTab1Data(){
		return sServerTab1;
	}
	ref TStringArray GetTab2Data(){
		return sServerTab2;
	}
	ref TStringArray GetTab3Data(){
		return sServerTab3;
	}

	private void readOldJson()	{

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

		createDefaultCFGOldJson();

		ServerPanelBase.Log( "ServerPanelConfig", "Deleting old json file" );

		DeleteFile(SP_OLD_CONFIG_PATH);
	}

	private void createDefaultCFGOldJson()	{

		ServerPanelBase.Log( "ServerPanelConfig", "Creating new json config file with old json" );

		ref SPJsonConfig newSPConfigData = new SPJsonConfig();

		newSPConfigData.ServerName 		= SERVERNAME ;
		newSPConfigData.Button1Name 	= BUTTON1NAME;
		newSPConfigData.Button1Link 	= BUTTON1LINK;
		newSPConfigData.Button2Name 	= BUTTON2NAME;
		newSPConfigData.Button2Link 	= BUTTON2LINK;
		newSPConfigData.Button3Name 	= BUTTON3NAME;
		newSPConfigData.Button3Link 	= BUTTON3LINK;
		newSPConfigData.ButtonTab0Name 	= BUTTONTAB0NAME;
		newSPConfigData.ButtonTab1Name 	= BUTTONTAB1NAME;
		newSPConfigData.ButtonTab2Name 	= BUTTONTAB2NAME;
		newSPConfigData.ButtonTab3Name 	= BUTTONTAB3NAME;
		newSPConfigData.PlayerInfo		= DISPLAYPLAYERINFO;
		newSPConfigData.PlayerTab		= DISPLAYPLAYERTAB;
		newSPConfigData.UseScriptLog 	= DEFAULTIOFLAG;

		JsonFileLoader<SPJsonConfig>.JsonSaveFile(SP_CONFIG_PATH, newSPConfigData);
	}

	private void createDefaultCFG()	{

		ServerPanelBase.Log( "ServerPanelConfig", "Creating ServerPanelConfig.json" );

		ref SPJsonConfig newSPConfigData = new SPJsonConfig();

		newSPConfigData.ServerName 		= SERVERNAME ;
		newSPConfigData.Button1Name 	= BUTTON1NAME;
		newSPConfigData.Button1Link 	= BUTTON1LINK;
		newSPConfigData.Button2Name 	= BUTTON2NAME;
		newSPConfigData.Button2Link 	= BUTTON2LINK;
		newSPConfigData.Button3Name 	= BUTTON3NAME;
		newSPConfigData.Button3Link 	= BUTTON3LINK;
		newSPConfigData.ButtonTab0Name 	= BUTTONTAB0NAME;
		newSPConfigData.ButtonTab1Name 	= BUTTONTAB1NAME;
		newSPConfigData.ButtonTab2Name 	= BUTTONTAB2NAME;
		newSPConfigData.ButtonTab3Name 	= BUTTONTAB3NAME;
		newSPConfigData.PlayerInfo		= DISPLAYPLAYERINFO;
		newSPConfigData.PlayerTab		= DISPLAYPLAYERTAB;
		newSPConfigData.UseScriptLog 	= DEFAULTIOFLAG;

		JsonFileLoader<SPJsonConfig>.JsonSaveFile(SP_CONFIG_PATH, newSPConfigData);

		ServerPanelBase.Log( "ServerPanelConfig", "ServerPanelConfig.json = OK" );
	}

	private void createDefaultKey()	{
		ServerPanelBase.Log( "ServerPanelConfig", "Creating ServerPanelKey.json" );

		ref SPJsonKeyConfig newSPConfigKey = new SPJsonKeyConfig();

		newSPConfigKey.SPMenuKey = "KC_PAUSE";		

		JsonFileLoader<SPJsonKeyConfig>.JsonSaveFile(SP_CONFIGKEY_PATH, newSPConfigKey);
	}

	void readOldDescription(){
		ref TStringArray serverDes = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int serverCounter = 0;
		bool skipLine = false;
		FileHandle configFile = OpenFile(SP_OLD_DESCRIPTION_PATH, FileMode.READ);
		if (configFile != 0) {
			while (configFile>0)	{
				char_count = FGets(configFile,sLine);
				if (char_count == -1 || serverCounter > 8000)	{
					break;
				}
				serverDes.Insert(sLine);

				serverCounter++;
			}
			CloseFile(configFile);
		}
		sServerTab0 = serverDes;

		FileHandle newconfigFile = OpenFile(TAB0_PATH, FileMode.WRITE);
		ServerPanelBase.Log( "ServerPanelConfig", "INFO: ServerTab0.txt file not found, trying to create new one in " + TAB0_PATH );
		if (newconfigFile != 0) {
			for (int i = 0; i < sServerTab0.Count(); ++i ) FPrintln(newconfigFile, sServerTab0.Get(i));

			CloseFile(newconfigFile);
		}

		ServerPanelBase.Log( "ServerPanelConfig", "Deleting old serverDescription.txt" );

		DeleteFile(SP_OLD_DESCRIPTION_PATH);
	}

	void readOldRules(){
		ref TStringArray serverRules = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int serverCounter = 0;
		bool skipLine = false;
		FileHandle configFile = OpenFile(SP_OLD_RULES_PATH, FileMode.READ);
		if (configFile != 0) {
			while (configFile>0)	{
				char_count = FGets(configFile,sLine);
				if (char_count == -1 || serverCounter > 8000)	{
					break;
				}
				serverRules.Insert(sLine);

				serverCounter++;
			}
			CloseFile(configFile);
		}
		sServerTab1 = serverRules;

		FileHandle newconfigFile = OpenFile(TAB1_PATH, FileMode.WRITE);
		ServerPanelBase.Log( "ServerPanelConfig", "INFO: ServerTab1.txt file not found, trying to create new one in " + TAB1_PATH );
		if (newconfigFile != 0) {
			for (int i = 0; i < sServerTab1.Count(); ++i ) FPrintln(newconfigFile, sServerTab1.Get(i));

			CloseFile(newconfigFile);
		}

		ServerPanelBase.Log( "ServerPanelConfig", "Deleting old serverRules.txt" );

		DeleteFile(SP_OLD_RULES_PATH);
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
	}

	void reloadTab(){
		if (GetGame().IsMultiplayer() && GetGame().IsServer()) {
			if (!FileExist(TAB0_PATH)&& FileExist(SP_OLD_DESCRIPTION_PATH)) readOldDescription();
			if (!FileExist(TAB1_PATH)&& FileExist(SP_OLD_RULES_PATH)) readOldRules();

			if (!FileExist(TAB0_PATH)&& !FileExist(SP_OLD_DESCRIPTION_PATH)) CreateNewServerTab0(PROFILE_PATH);
			if (!FileExist(TAB1_PATH)&& !FileExist(SP_OLD_RULES_PATH)) CreateNewServerTab1(PROFILE_PATH);
			if (!FileExist(TAB2_PATH)) CreateNewServerTab2(PROFILE_PATH);
			if (!FileExist(TAB3_PATH)) CreateNewServerTab3(PROFILE_PATH);

			if (FileExist(TAB0_PATH) && FileExist(TAB1_PATH) && FileExist(TAB2_PATH) && FileExist(TAB3_PATH)) {
				getTab0Content();
				getTab1Content();
				getTab2Content();
				getTab3Content();
			}
		}
	}

	void reloadConfig()	{
		ref SPJsonConfig newSPConfigData;

		if (FileExist(SP_OLD_CONFIG_PATH)) {
			ServerPanelBase.Log( "ServerPanelConfig", "Old Json file have been found, trying to create a new one with old file" );
			readOldJson();
			JsonFileLoader<SPJsonConfig>.JsonLoadFile(SP_CONFIG_PATH, newSPConfigData);
		}
		else if (FileExist(SP_CONFIG_PATH)) {
			//ServerPanelBase.Log( "ServerPanelConfig", "All Configuration files have been found" );
			JsonFileLoader<SPJsonConfig>.JsonLoadFile(SP_CONFIG_PATH, newSPConfigData);
		}
		else{
			ServerPanelBase.Log( "ServerPanelConfig", "Trying to Create default ServerPanelConfig.json" );
			createDefaultCFG();
			JsonFileLoader<SPJsonConfig>.JsonLoadFile(SP_CONFIG_PATH, newSPConfigData);
		}

		SERVERNAME 			= newSPConfigData.ServerName;
		BUTTON1NAME 		= newSPConfigData.Button1Name;
		BUTTON1LINK 		= newSPConfigData.Button1Link;
		BUTTON2NAME 		= newSPConfigData.Button2Name;
		BUTTON2LINK 		= newSPConfigData.Button2Link;
		BUTTON3NAME 		= newSPConfigData.Button3Name;
		BUTTON3LINK 		= newSPConfigData.Button3Link;
		BUTTONTAB0NAME 		= newSPConfigData.ButtonTab0Name;
		BUTTONTAB1NAME 		= newSPConfigData.ButtonTab1Name;
		BUTTONTAB2NAME 		= newSPConfigData.ButtonTab2Name;
		BUTTONTAB3NAME 		= newSPConfigData.ButtonTab3Name;
		DISPLAYPLAYERTAB 	= newSPConfigData.PlayerTab;
		DISPLAYPLAYERINFO 	= newSPConfigData.PlayerInfo;
		DEFAULTIOFLAG 		= newSPConfigData.UseScriptLog;
	}

	void reloadKey()	{
		ref SPJsonKeyConfig newSPConfigKey;

		if (FileExist(SP_CONFIGKEY_PATH)) {
			ServerPanelBase.Log( "ServerPanelConfig", "ConfigKey" );
			JsonFileLoader<SPJsonKeyConfig>.JsonLoadFile(SP_CONFIGKEY_PATH, newSPConfigKey);
		}
		else{
			ServerPanelBase.Log( "ServerPanelConfig", "File not found creating ConfigKey file " );
			createDefaultKey();
			JsonFileLoader<SPJsonKeyConfig>.JsonLoadFile(SP_CONFIGKEY_PATH, newSPConfigKey);
		}

		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) { //TO BE CHANGED v0.6 - GUI CFG
		string tempKeyCode;
		for (int i = 0; i < 126; ++i) {
			tempKeyCode = typename.EnumToString(KeyCode, i);
			if (newSPConfigKey.SPMenuKey == tempKeyCode) {
				SPMENUKEY = i;
				ServerPanelBase.Log( "ServerPanelConfig", "INFO: Menu key set to " + SPMENUKEY.ToString() );
				ServerPanelBase.Log( "ServerPanelConfig", "INFO: Menu key set to " + tempKeyCode );
				break;
			}
		}
		if ((SPMENUKEY == KeyCode.KC_PAUSE) && (newSPConfigKey.SPMenuKey != "KC_PAUSE"))
		ServerPanelBase.Log( "ServerPanelConfig", "WARN: Cannot set menu key to " + newSPConfigKey.SPMenuKey + " - unknown keycode" );
		if ((SPMENUKEY == KeyCode.KC_PAUSE) && (newSPConfigKey.SPMenuKey == "KC_PAUSE"))
		ServerPanelBase.Log( "ServerPanelConfig", "Menu key is set to " + newSPConfigKey.SPMenuKey );
		}
	}

	private void CreateNewServerTab0(string dPath) {
		if (!FileExist(dPath + "ServerTab0.txt")) {
			FileHandle configFile = OpenFile(dPath + "ServerTab0.txt", FileMode.WRITE);
			ServerPanelBase.Log( "ServerPanelConfig", "INFO: ServerTab0.txt file not found, trying to create new one in " + dPath + "ServerTab1.txt" );
			if (configFile != 0) {
				FPrintln(configFile, "-- FEATURES --");
				FPrintln(configFile, "- No Stamina");
				FPrintln(configFile, "- Inventory Plus");
				FPrintln(configFile, "- Base Building");
				FPrintln(configFile, "- More Weapons");
				FPrintln(configFile, "- Custom NEAF, NWEAF, Balota, ...");
				FPrintln(configFile, "- Your server Tab0 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab0 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab0 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab0 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab0 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab0 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab0 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab0 Max 95 chars per line ..............");
				FPrintln(configFile, "- YOU CAN PUT SOME SPECIAL CHARACTERS");
				FPrintln(configFile, "*ùà$^ù*!:;.?/§µ%¨£123+°456789-*/+&é'(-è_çà)='");

				CloseFile(configFile);
			}
		}
	}
	private void CreateNewServerTab1(string dPath) {
		if (!FileExist(dPath + "ServerTab1.txt")) {
			FileHandle configFile = OpenFile(dPath + "ServerTab1.txt", FileMode.WRITE);
			ServerPanelBase.Log( "ServerPanelConfig", "INFO: ServerTab1.txt file not found, trying to create new one in " + dPath + "ServerTab2.txt" );
			if (configFile != 0) {
				FPrintln(configFile, "Your server Tab1 Title Your server Tab1 Title");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server TEST 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "Your server Tab1 Title");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab1 Max 95 chars per line ..............");
				FPrintln(configFile, "- YOU CAN PUT SOME SPECIAL CHARACTERS");
				FPrintln(configFile, "*ùà$^ù*!:;.?/§µ%¨£123+°456789-*/+&é'(-è_çà)='");
				CloseFile(configFile);
			}
		}
	}
	private void CreateNewServerTab2(string dPath) {
		if (!FileExist(dPath + "ServerTab2.txt")) {
			FileHandle configFile = OpenFile(dPath + "ServerTab2.txt", FileMode.WRITE);
			ServerPanelBase.Log( "ServerPanelConfig", "INFO: ServerTab2.txt file not found, trying to create new one in " + dPath + "ServerTab2.txt" );
			if (configFile != 0) {
				FPrintln(configFile, "Your server Tab2 Your server Tab2 Title");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "Your server Tab2 Title");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab2 Max 95 chars per line ..............");
				FPrintln(configFile, "- YOU CAN PUT SOME SPECIAL CHARACTERS");
				FPrintln(configFile, "*ùà$^ù*!:;.?/§µ%¨£123+°456789-*/+&é'(-è_çà)='");
				CloseFile(configFile);
			}
		}
	}
	private void CreateNewServerTab3(string dPath) {
		if (!FileExist(dPath + "ServerTab3.txt")) {
			FileHandle configFile = OpenFile(dPath + "ServerTab3.txt", FileMode.WRITE);
			ServerPanelBase.Log( "ServerPanelConfig", "INFO: ServerTab3.txt file not found, trying to create new one in " + dPath + "ServerTab3.txt" );
			if (configFile != 0) {
				FPrintln(configFile, "Your server Tab3 Your server Tab3 Title");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "Your server Tab3 Title");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- YOU CAN PUT SOME SPECIAL CHARACTERS");
				FPrintln(configFile, "*ùà$^ù*!:;.?/§µ%¨£123+°456789-*/+&é'(-è_çà)='");
				CloseFile(configFile);
			}
		}
	}
}
