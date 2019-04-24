class ServerPanelConfig {
	static const string SP_OLD_CONFIG_PATH = "$profile:\\ServerPanel\\ServerPanelNew.cfg";
	static const string SP_CONFIGKEY_PATH = "$profile:\\ServerPanel\\ServerPanelKey.json";
	static const string SP_CONFIG_PATH = "$profile:\\ServerPanel\\ServerPanelConfig.json";
	static const string DESCRIPTION_PATH = "$profile:\\ServerPanel\\ServerDescription.txt";
	static const string RULES_PATH = "$profile:\\ServerPanel\\ServerRules.txt";
	static const string TAB2_PATH = "$profile:\\ServerPanel\\ServerTab2.txt";
	static const string TAB3_PATH = "$profile:\\ServerPanel\\ServerTab3.txt";
	static const string PROFILE_PATH = "$profile:\\ServerPanel\\";
	private string CFG_PATH = "$saves:";
	private string CFG_PATH_SERVER = "$profile:";
	protected string realProfilesPath = "";

	private string SERVERNAME ="Server Panel";
	private string BUTTON1NAME;
	private string BUTTON1LINK;
	private string BUTTON2NAME;
	private string BUTTON2LINK;
	private string BUTTON3NAME;
	private string BUTTON3LINK;
	private string BUTTONTAB2NAME;
	private string BUTTONTAB3NAME;
	private int SPMENUKEY = KeyCode.KC_PAUSE;
	private int PLAYERINFO = 1;
	protected bool DEFAULTIOFLAG = false;
	//private int PLAYERSTAT;
	//private int SPMENUKEY;
	private ref TStringArray sServerDescription = new TStringArray;
	private ref TStringArray sServerRules = new TStringArray;
	private ref TStringArray sServerTab2 = new TStringArray;
	private ref TStringArray sServerTab3 = new TStringArray;
	

	void ServerPanelConfig() {
		if (GetGame().IsMultiplayer() && GetGame().IsServer()) {
			if (!GetCLIParam("profiles", realProfilesPath)) ServerPanelBase.Log( "ServerPanelConfig", "WARN: \"-profiles=<FOLDERNAME>\" launch parameter is NOT set!!!" );
				else ServerPanelBase.Log( "ServerPanelConfig", "INFO: Profile dir is: " + realProfilesPath);

			CFG_PATH = CFG_PATH_SERVER;

			if (!FileExist(CFG_PATH + "ServerPanel\\")) MakeDirectory(CFG_PATH + "\\ServerPanel\\");
			if (FileExist(CFG_PATH + "ServerPanel\\")) {
				if (FileExist(CFG_PATH + "ServerPanelNew.cfg")) CopyFile(CFG_PATH + "ServerPanelNew.cfg", CFG_PATH + "ServerPanel\\ServerPanelNew.cfg");
				if (FileExist(CFG_PATH + "ServerPanelConfig.json")) CopyFile(CFG_PATH + "ServerPanelConfig.json", CFG_PATH + "ServerPanel\\ServerPanelConfig.json");
				DeleteFile(CFG_PATH + "ServerPanelNew.cfg");
				DeleteFile(CFG_PATH + "ServerPanelConfig.json");

				CFG_PATH += "ServerPanel\\";
			} else {
				if (realProfilesPath != "") ServerPanelBase.Log( "ServerPanelConfig", "WARN: Can't create ServerPanel subfolder (" + realProfilesPath + "\\ServerPanel\\), please create one manually!" );
					else ServerPanelBase.Log( "ServerPanelConfig", "WARN: Can't create ServerPanel subfolder (" + CFG_PATH + "ServerPanel\\), please create one manually!" );
			}
		}

		if (realProfilesPath != "") ServerPanelBase.Log( "ServerPanelConfig", "INFO: Config files will be loaded from: " + realProfilesPath );
			else ServerPanelBase.Log( "ServerPanelConfig", "INFO: Config files will be loaded from: " + CFG_PATH );
		reloadTab();
		reloadConfig();

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
	string GetButtonTab2Name() {
		return BUTTONTAB2NAME;
	}
	string GetButtonTab3Name() {
		return BUTTONTAB3NAME;
	}
	int GetSPMenuKey() {
		return SPMENUKEY;
	}
	int GetPlayerInfo() {
		return PLAYERINFO;
	}
	bool IsDefaultIO() {
		return DEFAULTIOFLAG;
	}
	ref TStringArray GetDescriptionData(){
		return sServerDescription;
	}
	ref TStringArray GetRulesData(){
		return sServerRules;
	}
	ref TStringArray GetTab2Data(){
		return sServerTab2;
	}
	ref TStringArray GetTab3Data(){
		return sServerTab3;
	}

	void readOldServername(){
		FileHandle configOldNameFile = OpenFile(PROFILE_PATH + "ServerName.txt", FileMode.READ);
		if (configOldNameFile != 0) {
			string sLine = "";
			while ( FGets(configOldNameFile,sLine) > 0 ) {
				SERVERNAME=sLine;
			}
		}
		CloseFile(configOldNameFile);
		DeleteFile(PROFILE_PATH + "ServerName.txt");
		ServerPanelBase.Log("ServerPanelConfig: Name",SERVERNAME);
	}
	void readOldConfig(){
		FileHandle configOldButtonFile;
		int idx = 0;

		ServerPanelBase.Log("ServerPanelConfig","Reading old Config File.cfg");

		configOldButtonFile = OpenFile(SP_OLD_CONFIG_PATH, FileMode.READ);
		if (configOldButtonFile != 0) {
			string sLine = "";
			TStringArray sParams = new TStringArray;
			while ( FGets(configOldButtonFile,sLine) > 0 ) {
				++idx;
				sLine.Replace(" ", ""); sLine.Replace(";", "");
				sLine.Split("=", sParams);
				if (sParams.Count() != 2) {
					ServerPanelBase.Log( "ServerPanelConfig", "WARN: config line " + idx.ToString() + " (param " + sParams[0] + ") - parse error (not key = value), " + sParams.Count() + " tokens" );
					sParams = {};
					continue;
				}

				switch (sParams[0]) {
					case "displayPlayerInformation":
					if (sParams[1].ToInt() > 0 && sParams[1].ToInt() < 3) {
						PLAYERINFO = sParams[1].ToInt();
						//ServerPanelBase.Log( "ServerPanelButton", "INFO: displayPlayerInformation: " + sParams[1] );
					}
					break;
					case "button1Name":
					if (sParams[1] != "") {
						BUTTON1NAME = sParams[1];
						//ServerPanelBase.Log( "ServerPanelButton", "INFO: button1Name: " + sParams[1] );
					}
					break;
					case "button1Link":
					if (sParams[1] != "") {
						BUTTON1LINK = sParams[1];
						//ServerPanelBase.Log( "ServerPanelButton", "INFO: button1Link: " + sParams[1] );
					}
					break;
					case "button2Name":
					if (sParams[1] != "") {
						BUTTON2NAME = sParams[1];
						//ServerPanelBase.Log( "ServerPanelButton", "INFO: button2Name: " + sParams[1] );
					}
					break;
					case "button2Link":
					if (sParams[1] != "") {
						BUTTON2LINK = sParams[1];
						//ServerPanelBase.Log( "ServerPanelButton", "INFO: button2Link: " + sParams[1] );
					}
					break;
					case "button3Name":
					if (sParams[1] != "") {
						BUTTON3NAME = sParams[1];
						//ServerPanelBase.Log( "ServerPanelButton", "INFO: button3Name: " + sParams[1] );
					}
					break;
					case "button3Link":
					if (sParams[1] != "") {
						BUTTON3LINK = sParams[1];
						//ServerPanelBase.Log( "ServerPanelButton", "INFO: button3Link: " + sParams[1] );
					}
					break;
					case "buttonTab2Name":
					if (sParams[1] != "") {
						BUTTONTAB2NAME = sParams[1];
						//ServerPanelBase.Log( "ServerPanelButton", "INFO: ButtonTab2Name: " + sParams[1] );
					}
					break;
					case "buttonTab3Name":
					if (sParams[1] != "") {
						BUTTONTAB3NAME = sParams[1];
						//ServerPanelBase.Log( "ServerPanelButton", "INFO: buttonTab3Name: " + sParams[1] );
					}
					break;
				}

				ServerPanelBase.Log( "ServerPanelButton", "INFO: sParams[1]: " + sParams[1] );
				sParams = {};
			}
			CloseFile(configOldButtonFile);
			DeleteFile(SP_OLD_CONFIG_PATH);
		}
	}

	private void createDefaultCFG()	{

		ServerPanelBase.Log( "ServerPanelConfig", "Creating ServerPanelConfig.json" );

		ref SPJsonConfig newSPConfigData = new SPJsonConfig();

		newSPConfigData.ServerName = "Welcome on MyDAyZ server !! - Hosted By MyDayZ.eu";
		newSPConfigData.Button1Name = "DISCORD";
		newSPConfigData.Button1Link = "https://mydayz.eu";
		newSPConfigData.Button2Name = "WEBSITE";
		newSPConfigData.Button2Link = "https://mydayz.eu";
		newSPConfigData.Button3Name = "DONATE";
		newSPConfigData.Button3Link = "https://paypal.com";
		newSPConfigData.ButtonTab2Name = "TEST1";
		newSPConfigData.ButtonTab3Name = "TEST2";		
		newSPConfigData.PlayerInfo = 1;
		newSPConfigData.UseScriptLog = DEFAULTIOFLAG;

		JsonFileLoader<SPJsonConfig>.JsonSaveFile(SP_CONFIG_PATH, newSPConfigData);
	}

	/*private void createDefaultKey()	{
		ServerPanelBase.Log( "ServerPanelConfig", "Creating ServerPanelKey.json" );

		ref SPJsonKeyConfig newSPConfigKey = new SPJsonKeyConfig();

		newSPConfigKey.SPMenuKey = "KC_PAUSE";

		JsonFileLoader<SPJsonKeyConfig>.JsonSaveFile(SP_CONFIGKEY_PATH, newSPConfigKey);
	}*/

	private void createOldDefaultCFG()	{

		ServerPanelBase.Log( "ServerPanelConfig", "Creating default ServerPanelConfig.json with old config" );

		ref SPJsonConfig newSPConfigData = new SPJsonConfig();

		newSPConfigData.ServerName = SERVERNAME;
		newSPConfigData.Button1Name = BUTTON1NAME;
		newSPConfigData.Button1Link = BUTTON1LINK;
		newSPConfigData.Button2Name = BUTTON2NAME;
		newSPConfigData.Button2Link = BUTTON2LINK;
		newSPConfigData.Button3Name = BUTTON3NAME;
		newSPConfigData.Button3Link = BUTTON3LINK;
		newSPConfigData.ButtonTab2Name = BUTTONTAB2NAME;
		newSPConfigData.ButtonTab3Name = BUTTONTAB3NAME;		
		newSPConfigData.PlayerInfo = PLAYERINFO;
		newSPConfigData.UseScriptLog = DEFAULTIOFLAG;

		JsonFileLoader<SPJsonConfig>.JsonSaveFile(SP_CONFIG_PATH, newSPConfigData);
	}

	void getDescriptionContent(){
		ref TStringArray serverTab2 = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int serverTab2Counter = 0;
		bool skipLine = false;
		FileHandle configTab2File = OpenFile(TAB2_PATH, FileMode.READ);
		if (configTab2File != 0) {
			while (configTab2File>0)
			{
				char_count = FGets(configTab2File,sLine);

				if (char_count == -1 || serverTab2Counter > 8000)
				{
					break;
				}
				serverTab2.Insert(sLine);

				serverTab2Counter++;
			}
			CloseFile(configTab2File);
		}
		sServerTab2 = serverTab2;
	}
	void getRulesContent(){
		ref TStringArray serverTab3 = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int serverTab3Counter = 0;
		bool skipLine = false;
		FileHandle configTab3File = OpenFile(TAB3_PATH, FileMode.READ);
		if (configTab3File != 0) {
			while (configTab3File>0)
			{
				char_count = FGets(configTab3File,sLine);

				if (char_count == -1 || serverTab3Counter > 8000)
				{
					break;
				}
				serverTab3.Insert(sLine);

				serverTab3Counter++;
			}
			CloseFile(configTab3File);
		}
		sServerTab3 = serverTab3;
	}
	void getTab2Content(){
		ref TStringArray serverDesc = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int DescriptionCounter = 0;
		bool skipLine = false;
		FileHandle configDescriptionFile = OpenFile(DESCRIPTION_PATH, FileMode.READ);
		if (configDescriptionFile != 0) {
			while (configDescriptionFile>0)
			{
				char_count = FGets(configDescriptionFile,sLine);

				if (char_count == -1 || DescriptionCounter > 8000)
				{
					break;
				}
				serverDesc.Insert(sLine);

				DescriptionCounter++;
			}
			CloseFile(configDescriptionFile);
		}
		sServerDescription = serverDesc;
	}
	void getTab3Content(){
		ref TStringArray serverRules = new TStringArray;
		string sLine = "";
		int char_count = 0;
		int RulesCounter = 0;
		bool skipLine = false;
		FileHandle configRulesFile = OpenFile(RULES_PATH, FileMode.READ);
		if (configRulesFile != 0) {
			while (configRulesFile>0)
			{
				char_count = FGets(configRulesFile,sLine);

				if (char_count == -1 || RulesCounter > 8000)
				{
					break;
				}
				serverRules.Insert(sLine);
				//	}
				RulesCounter++;
			}
			CloseFile(configRulesFile);
		}
		sServerRules = serverRules;
	}

	void reloadTab(){

		if (!FileExist(DESCRIPTION_PATH)) CreateNewServerDescription(PROFILE_PATH);
		if (!FileExist(RULES_PATH)) CreateNewServerRules(PROFILE_PATH);
		if (!FileExist(TAB3_PATH)) CreateNewServerTab3(PROFILE_PATH);
		if (!FileExist(TAB2_PATH)) CreateNewServerTab2(PROFILE_PATH);

		if (FileExist(DESCRIPTION_PATH) && FileExist(RULES_PATH) && FileExist(TAB2_PATH) && FileExist(TAB3_PATH)) {
			getDescriptionContent();
			getRulesContent();
			getTab2Content();
			getTab3Content();
		}
	}

	void reloadConfig()	{
		ref SPJsonConfig newSPConfigData;

		if (FileExist(SP_CONFIG_PATH)) {
			//ServerPanelBase.Log( "ServerPanelConfig", "All Configuration files have been found" );
			JsonFileLoader<SPJsonConfig>.JsonLoadFile(SP_CONFIG_PATH, newSPConfigData);
		}
		else if (FileExist(SP_OLD_CONFIG_PATH) && FileExist(PROFILE_PATH + "ServerName.txt") && !FileExist(SP_CONFIG_PATH)) {
			ServerPanelBase.Log( "ServerPanelConfig", "Old Configuration & Server Name found" );
			readOldConfig();
			readOldServername();
			createOldDefaultCFG();
			JsonFileLoader<SPJsonConfig>.JsonLoadFile(SP_CONFIG_PATH, newSPConfigData);
		}
		else{
			ServerPanelBase.Log( "ServerPanelConfig", "Trying to Create default ServerPanelConfig.json" );
			createDefaultCFG();
			JsonFileLoader<SPJsonConfig>.JsonLoadFile(SP_CONFIG_PATH, newSPConfigData);
		}

		SERVERNAME = newSPConfigData.ServerName;
		BUTTON1NAME = newSPConfigData.Button1Name;
		BUTTON1LINK = newSPConfigData.Button1Link;
		BUTTON2NAME = newSPConfigData.Button2Name;
		BUTTON2LINK = newSPConfigData.Button2Link;
		BUTTON3NAME = newSPConfigData.Button3Name;
		BUTTON3LINK = newSPConfigData.Button3Link;
		BUTTONTAB2NAME = newSPConfigData.ButtonTab2Name;
		BUTTONTAB3NAME = newSPConfigData.ButtonTab3Name;
		PLAYERINFO = newSPConfigData.PlayerInfo;
		DEFAULTIOFLAG = newSPConfigData.UseScriptLog;
	}

	/*void reloadKey()	{
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

		//if (GetGame().IsClient() || !GetGame().IsMultiplayer()) { //TO BE CHANGED v0.6 - GUI CFG
		string tempKeyCode;
		for (int i = 0; i < 126; ++i) {
			tempKeyCode = typename.EnumToString(KeyCode, i);
			if (newSPConfigKey.SPMenuKey == tempKeyCode) {
				SPMENUKEY = i;
				ServerPanelBase.Log( "ServerPanelConfig", "INFO: Menu key set to " + tempKeyCode );
				break;
			}
		}
		if ((SPMENUKEY == KeyCode.KC_PAUSE) && (newSPConfigKey.SPMenuKey != "KC_PAUSE"))
			ServerPanelBase.Log( "ServerPanelConfig", "WARN: Cannot set menu key to " + newSPConfigKey.SPMenuKey + " - unknown keycode" );
	}*/

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
				FPrintln(configFile, "Your server Rules Title");
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
				FPrintln(configFile, "Your server Tab3 Title Your server Rules Title");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Tab3 Max 95 chars per line ..............");
				FPrintln(configFile, "Your server Rules Title");
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
	private void CreateNewServerDescription(string dPath) {
		if (!FileExist(dPath + "ServerDescription.txt")) {
			FileHandle configFile = OpenFile(dPath + "ServerDescription.txt", FileMode.WRITE);
			ServerPanelBase.Log( "ServerPanelConfig", "INFO: ServerDescription.txt file not found, trying to create new one in " + dPath + "ServerDescription.txt" );
			if (configFile != 0) {
				FPrintln(configFile, "-- FEATURES --");
				FPrintln(configFile, "- No Stamina");
				FPrintln(configFile, "- Inventory Plus");
				FPrintln(configFile, "- Base Building");
				FPrintln(configFile, "- More Weapons");
				FPrintln(configFile, "- Custom NEAF, NWEAF, Balota, ...");
				FPrintln(configFile, "- Your server Description Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Description Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Description Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Description Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Description Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Description Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Description Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Description Max 95 chars per line ..............");
				FPrintln(configFile, "- YOU CAN PUT SOME SPECIAL CHARACTERS");
				FPrintln(configFile, "*ùà$^ù*!:;.?/§µ%¨£123+°456789-*/+&é'(-è_çà)='");

				CloseFile(configFile);
			}
		}
	}
	private void CreateNewServerRules(string dPath) {
		if (!FileExist(dPath + "ServerRules.txt")) {
			FileHandle configFile = OpenFile(dPath + "ServerRules.txt", FileMode.WRITE);
			ServerPanelBase.Log( "ServerPanelConfig", "INFO: ServerRules.txt file not found, trying to create new one in " + dPath + "ServerRules.txt" );
			if (configFile != 0) {
				FPrintln(configFile, "Your server Rules Title Your server Rules Title");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server TEST 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "Your server Rules Title");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- Your server Rules Max 95 chars per line ..............");
				FPrintln(configFile, "- YOU CAN PUT SOME SPECIAL CHARACTERS");
				FPrintln(configFile, "*ùà$^ù*!:;.?/§µ%¨£123+°456789-*/+&é'(-è_çà)='");
				CloseFile(configFile);
			}
		}
	}
}
