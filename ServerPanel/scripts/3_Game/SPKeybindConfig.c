/*class SPKeybindConfig
{
	const string SAVE_PATH = "$profile:\\ServerPanel\\SPKeyBind.json";

	private string KEY_SERVER_PANEL;

 	void SPKeybindConfig()
 	{
 		if ( FileExist(SAVE_PATH) )
 		{
 			JsonFileLoader<SPKeybindConfig>.JsonLoadFile(SAVE_PATH, this);
 		}else{
 			makeDefaults();
 		}
 	}

 	void ~SPKeybindConfig()
 	{

 	}

 	void saveConfig()
 	{
 		JsonFileLoader<SPKeybindConfig>.JsonSaveFile(SAVE_PATH, this);
 		//Reload after save.
 		JsonFileLoader<SPKeybindConfig>.JsonLoadFile(SAVE_PATH, this);
 	}

 	void makeDefaults()
 	{
 		KEY_SERVER_PANEL 		= "KC_PAUSE";

		saveConfig();
 	}

 	string getActionKey(string actionName)
 	{
 		switch(actionName)
 		{
 			case "AdminTools":
 			return KEY_SERVER_PANEL;
 			break;
 		}
 		return "NULL";
 	}

 	int getKeyEnum(string keyBindName){
 		ref map<int,string> keyMap = g_Game.getKeyBindsMap();
 		int keyEnum;
 		string keyName;
		for(int i = 0; i < keyMap.Count(); i++){
			keyEnum = keyMap.GetKey(i);
			keyName = keyMap.Get(keyEnum);
			if(keyBindName == keyName){
				return keyEnum;
			}
		}
		return -1;
	}
}*/