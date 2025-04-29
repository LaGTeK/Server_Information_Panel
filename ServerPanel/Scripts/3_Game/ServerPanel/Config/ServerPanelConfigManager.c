class ServerPanelConfigManager {
	private static ref ServerPanelServerConfig m_Config = NULL; // Static configuration instance

	static ServerPanelServerConfig GetConfig() {
		if (!m_Config) {
			SetConfig();
		}
		return m_Config;
	}

	static void SetConfig()
	{
		m_Config = LoadConfig();
	}

	static void SetConfig(ServerPanelServerConfig config)
	{
		if (!m_Config) {
			m_Config = config;
			return;
		}

		if (m_Config.VERSION == config.VERSION) {
			return; // Même version déjà chargée, inutile de remplacer
		}

		m_Config = config; // Sinon on met à jour
	}


	private static ServerPanelServerConfig LoadConfig() 
	{
		ServerPanelServerConfig config = new ServerPanelServerConfig;

		if (FileExist(SP_FILE_PATH)) 
		{
			Print("[ServerPanel] 'ServerPanelConfigManager' Configuration file found...");

			JsonFileLoader<ServerPanelServerConfig>.JsonLoadFile(SP_FILE_PATH, config);


			if (config.VERSION.ToFloat() != SP_CONFIG_VERSION.ToFloat())
			{
				BackupOldConfig();
				Print("[ServerPanel] 'ServerPanelConfigManager' Upgrading configuration file...");
				UpgradeConfig(config); // Upgrade après lecture
			}
			else
			{
				Print("[ServerPanel] 'ServerPanelConfigManager' Configuration loaded.");
			}
		} 
		else 
		{
			Print("[ServerPanel] 'ServerPanelConfigManager' Configuration file not found, creating a default configuration.");
			EnsureDirectoriesExist();
			WriteDefaultServer(config); // Créer la config par défaut
		}

		FixMissingOrInvalidFields(config);

		return config;
	}

	static void FixMissingOrInvalidFields(ServerPanelServerConfig config)
	{
		// Booleans (false by default)
		if (config.DISPLAYPLAYERINFO != true && config.DISPLAYPLAYERINFO != false) config.DISPLAYPLAYERINFO = false;
		if (config.DISPLAYPLAYERTAB != true && config.DISPLAYPLAYERTAB != false) config.DISPLAYPLAYERTAB = false;
		if (config.DISPLAYPLAYERLIST != true && config.DISPLAYPLAYERLIST != false) config.DISPLAYPLAYERLIST = false;
		if (config.DISPLAYPLAYERPOSITION != true && config.DISPLAYPLAYERPOSITION != false) config.DISPLAYPLAYERPOSITION = false;
		if (config.DISPLAYCRAFTTAB != true && config.DISPLAYCRAFTTAB != false) config.DISPLAYCRAFTTAB = false;
		if (config.DISPLAYCURRENCY != true && config.DISPLAYCURRENCY != false) config.DISPLAYCURRENCY = false;
		if (config.DISPLAYPLOGO != true && config.DISPLAYPLOGO != false) config.DISPLAYPLOGO = false;

		// Strings
		if (!config.SERVERNAME) config.SERVERNAME = "";
		if (!config.BUTTON1NAME) config.BUTTON1NAME = "";
		if (!config.BUTTON1LINK) config.BUTTON1LINK = "";
		if (!config.BUTTON2NAME) config.BUTTON2NAME = "";
		if (!config.BUTTON2LINK) config.BUTTON2LINK = "";
		if (!config.BUTTON3NAME) config.BUTTON3NAME = "";
		if (!config.BUTTON3LINK) config.BUTTON3LINK = "";
		if (!config.CURRENCYNAME) config.CURRENCYNAME = "";
		if (!config.LOGOPATH) config.LOGOPATH = "";
		if (!config.BUTTONTAB0NAME) config.BUTTONTAB0NAME = "";
		if (!config.BUTTONTAB1NAME) config.BUTTONTAB1NAME = "";
		if (!config.BUTTONTAB2NAME) config.BUTTONTAB2NAME = "";
		if (!config.BUTTONTAB3NAME) config.BUTTONTAB3NAME = "";

		// Numeric
		if (config.LOGLEVEL < 0) config.LOGLEVEL = 0;
		if (config.LOGO_WIDTH_PERCENTAGE < 0) config.LOGO_WIDTH_PERCENTAGE = 0.0;
		if (config.LOGO_HEIGHT_PERCENTAGE < 0) config.LOGO_HEIGHT_PERCENTAGE = 0.0;
		
		// Arrays
		if (!config.sServerTab0) config.sServerTab0 = new array<string>();
		if (!config.sServerTab1) config.sServerTab1 = new array<string>();
		if (!config.sServerTab2) config.sServerTab2 = new array<string>();
		if (!config.sServerTab3) config.sServerTab3 = new array<string>();
	}


	static void EnsureDirectoriesExist() 
	{
		if (!FileExist(SP_DIR_PATH)) {
			bool dirCreated = MakeDirectory(SP_DIR_PATH);
			if (dirCreated) {
				Print("[ServerPanel] 'ServerPanelConfig' Created directory: " + SP_DIR_PATH);
			} else {
				Print("[ServerPanel] 'ServerPanelConfig' Failed to create directory: " + SP_DIR_PATH);
			}
		} else {
			Print("[ServerPanel] 'ServerPanelConfigManager' Directory already exists: " + SP_DIR_PATH);
		}

		if (!FileExist(SP_LOG_PATH)) {
			bool logDirCreated = MakeDirectory(SP_LOG_PATH);
			if (logDirCreated) {
				Print("[ServerPanel] 'ServerPanelConfig' Created log directory: " + SP_LOG_PATH);
			} else {
				Print("[ServerPanel] 'ServerPanelConfig' Failed to create log directory: " + SP_LOG_PATH);
			}
		} else {
			Print("[ServerPanel] 'ServerPanelConfigManager' Log directory already exists: " + SP_LOG_PATH);
		}
	}

	private static void WriteDefaultServer(ServerPanelServerConfig config) 
	{
		Print("[ServerPanel] 'ServerPanelConfigManager' Writing Default Server Config");

		config.VERSION = SP_CONFIG_VERSION; // Set the default version for new configs
		config.SERVERNAME = "Welcome on MyDayZ server !! - Hosted By MyDayZ.eu";
		config.LOGLEVEL = 1;
		config.BUTTON1NAME = "DISCORD";
		config.BUTTON1LINK = "https://discord.gg/KAgNn6K";
		config.BUTTON2NAME = "WEBSITE";
		config.BUTTON2LINK = "https://mydayz.eu";
		config.BUTTON3NAME = "DONATE";
		config.BUTTON3LINK = "https://www.paypal.me/MyDayZ";
		config.DISPLAYPLAYERINFO = true;
		config.DISPLAYPLAYERTAB = true;
		config.DISPLAYCRAFTTAB = true;
		config.DISPLAYPLAYERLIST = true;
		config.DISPLAYPLAYERPOSITION = true;
		config.DISPLAYCURRENCY = true;
		config.CURRENCYNAME = "Rubles";
		config.DISPLAYPLOGO = true;
		config.LOGOPATH = "set:dayz_gui image:ProgressDayZFull"; // Default logo link updated here
		config.LOGO_WIDTH_PERCENTAGE = 87.0;
		config.LOGO_HEIGHT_PERCENTAGE = 83.0;
		config.BUTTONTAB0NAME = "TAB0";
		config.BUTTONTAB1NAME = "TAB1";
		config.BUTTONTAB2NAME = "TAB2";
		config.BUTTONTAB3NAME = "TAB3";

		config.sServerTab0 = new array<string>();
		config.sServerTab1 = new array<string>();
		config.sServerTab2 = new array<string>();
		config.sServerTab3 = new array<string>();

		// Populate the default values
		for (int i = 0; i < 60; i++) {
			if (i == 0) {
				config.sServerTab0.Insert("<h1>Write your h1 Title " + i + "</h1>");
				config.sServerTab1.Insert("<h1>Write your h1 Title " + i + "</h1>");
				config.sServerTab2.Insert("<h1>Write your h1 Title " + i + "</h1>");
				config.sServerTab3.Insert("<h1>Write your h1 Title " + i + "</h1>");
			}
			else if (i > 0 && i < 5) {
				config.sServerTab0.Insert("<p>Write your <b>information Tab0 " + i + "</b></p>");
				config.sServerTab1.Insert("<p>Write your <b>information Tab1 " + i + "</b></p>");
				config.sServerTab2.Insert("<p>Write your <b>information Tab2 " + i + "</b></p>");
				config.sServerTab3.Insert("<p>Write your <b>information Tab3 " + i + "</b></p>");
			}
			else if (i == 5) {
				config.sServerTab0.Insert("<h2>Write your h2 Title " + i + "</h2>");
				config.sServerTab1.Insert("<h2>Write your h2 Title " + i + "</h2>");
				config.sServerTab2.Insert("<h2>Write your h2 Title " + i + "</h2>");
				config.sServerTab3.Insert("<h2>Write your h2 Title " + i + "</h2>");
			}
			else if (i > 5 && i < 10) {
				config.sServerTab0.Insert("<p>Write your <i>information Tab0 " + i + "</i></p>");
				config.sServerTab1.Insert("<p>Write your <i>information Tab1 " + i + "</i></p>");
				config.sServerTab2.Insert("<p>Write your <i>information Tab2 " + i + "</i></p>");
				config.sServerTab3.Insert("<p>Write your <i>information Tab3 " + i + "</i></p>");
			}
			else if (i == 10) {
				config.sServerTab0.Insert("<h2>Write your h2 Title " + i + "</h2>");
				config.sServerTab1.Insert("<h2>Write your h2 Title " + i + "</h2>");
				config.sServerTab2.Insert("<h2>Write your h2 Title " + i + "</h2>");
				config.sServerTab3.Insert("<h2>Write your h2 Title " + i + "</h2>");
			}
			else if (i > 15 && i < 20) {
				config.sServerTab0.Insert("<p>Write your <b>information Tab0 " + i + "</b></p>");
				config.sServerTab1.Insert("<p>Write your <b>information Tab1 " + i + "</b></p>");
				config.sServerTab2.Insert("<p>Write your <b>information Tab2 " + i + "</b></p>");
				config.sServerTab3.Insert("<p>Write your <b>information Tab3 " + i + "</b></p>");
			}
			else if (i == 15) {
				config.sServerTab0.Insert("<h2>Write your h2 Title " + i + "</h2>");
				config.sServerTab1.Insert("<h2>Write your h2 Title " + i + "</h2>");
				config.sServerTab2.Insert("<h2>Write your h2 Title " + i + "</h2>");
				config.sServerTab3.Insert("<h2>Write your h2 Title " + i + "</h2>");
			}
			else {
				config.sServerTab0.Insert("<p>Write your <i>information Tab0 " + i + "</i></p>");
				config.sServerTab1.Insert("<p>Write your <i>information Tab1 " + i + "</i></p>");
				config.sServerTab2.Insert("<p>Write your <i>information Tab2 " + i + "</i></p>");
				config.sServerTab3.Insert("<p>Write your <i>information Tab3 " + i + "</i></p>");
			}
		}

		// Save configuration to file		
        JsonFileLoader<ServerPanelServerConfig>.JsonSaveFile(SP_FILE_PATH, config);
	}

	static void UpgradeConfig(ServerPanelServerConfig config) 
	{
		Print("[ServerPanel] 'ServerPanelConfigManager' Upgrading configuration file...");

		if (config.VERSION.ToFloat() < SP_CONFIG_VERSION.ToFloat()) {			
			if (config.VERSION.ToFloat() <= 1.6) {
				if (!config.CURRENCYNAME) {
					config.CURRENCYNAME = "Rubles";	
				}
				if (!config.DISPLAYCURRENCY) {
					config.DISPLAYCURRENCY = true;	
				}
				config.VERSION = SP_CONFIG_VERSION;	
			}
			if (config.VERSION.ToFloat() <= 1.5) {
				if (!config.DISPLAYCRAFTTAB) {
					config.DISPLAYCRAFTTAB = true;
				}
			}
			if (config.VERSION.ToFloat() <= 1.4) {
				// Vérification et mise à jour de la configuration existante
				AddHtmlTagsToTabs(config.sServerTab0);  // Utilisation du nom correct de la méthode
				AddHtmlTagsToTabs(config.sServerTab1);
				AddHtmlTagsToTabs(config.sServerTab2);
				AddHtmlTagsToTabs(config.sServerTab3);

				// LOGLEVEL
				if (!config.LOGLEVEL) {
					config.LOGLEVEL = 1;
				}

				// LOGOPATH
				if (!config.LOGOPATH) {
					config.LOGOPATH = "set:dayz_gui image:ProgressDayZFull";
				}

				// LOGO_WIDTH_PERCENTAGE
				if (!config.LOGO_WIDTH_PERCENTAGE) {
					config.LOGO_WIDTH_PERCENTAGE = 87.0;
				}

				// LOGO_HEIGHT_PERCENTAGE
				if (!config.LOGO_HEIGHT_PERCENTAGE) {
					config.LOGO_HEIGHT_PERCENTAGE = 83.0;
				}

				// Consolidation des vérifications booléennes
				if (!config.DISPLAYPLAYERLIST) {
					config.DISPLAYPLAYERLIST = true;
				}

				if (!config.DISPLAYPLAYERPOSITION) {
					config.DISPLAYPLAYERPOSITION = true;
				}

				if (!config.DISPLAYPLOGO) {				
					config.DISPLAYPLOGO = true;				
				}
			}

			// Mettre à jour la version de configuration
			config.VERSION = SP_CONFIG_VERSION;
		}

        JsonFileLoader<ServerPanelServerConfig>.JsonSaveFile(SP_FILE_PATH, config);		

		Print("[ServerPanel] 'ServerPanelConfigManager' Configuration file upgraded to version " + SP_CONFIG_VERSION);
	}
	static void BackupOldConfig()
	{
		string backupPath = SP_FILE_PATH + ".bak";
		if (CopyFile(SP_FILE_PATH, backupPath))
		{
			Print("[ServerPanel] 'ServerPanelConfigManager' Backup created: " + backupPath);
		}
		else
		{
			Print("[ServerPanel] 'ServerPanelConfigManager' WARNING: Backup failed !");
		}
	}

	// Méthode renommée pour être plus explicite
	static void AddHtmlTagsToTabs(TStringArray tab) 
	{
		TStringArray upgradedTab = new TStringArray;

		for (int i = 0; i < tab.Count(); i++) {
			string updatedLine = tab[i] + "<br>"; // Correction de la balise
			upgradedTab.Insert(updatedLine);
		}

		// Remplacer le contenu original du tableau avec le nouveau contenu mis à jour
		tab.Clear();
		foreach (string line: upgradedTab) {
			tab.Insert(line);
		}
	}
}
