class ServerPanelConfigManager {
	private static ref ServerPanelServerConfig m_Config = NULL; // Static configuration instance
	private static const string SP_FILE_BACKUP = SP_FILE_PATH + ".bak";
	private static const string SP_FILE_BACKUP_REJECTED = SP_FILE_PATH + ".bak.rejected";

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
		if (!config) {
			return;
		}

		if (!m_Config) {
			m_Config = config;
			FixMissingOrInvalidFields(m_Config);
			return;
		}

		// Même VERSION: on fusionne quand même (RPC / hot reload) pour ne pas garder une config client périmée.
		if (m_Config.VERSION == config.VERSION) {
			MergeConfigSnapshot(m_Config, config);
			FixMissingOrInvalidFields(m_Config);
			return;
		}

		m_Config = config;
		FixMissingOrInvalidFields(m_Config);
	}

	private static void MergeStringTabs(ServerPanelServerConfig dest, ServerPanelServerConfig src)
	{
		if (!dest.sServerTab0) {
			dest.sServerTab0 = new array<string>();
		}
		if (!dest.sServerTab1) {
			dest.sServerTab1 = new array<string>();
		}
		if (!dest.sServerTab2) {
			dest.sServerTab2 = new array<string>();
		}
		if (!dest.sServerTab3) {
			dest.sServerTab3 = new array<string>();
		}

		dest.sServerTab0.Clear();
		dest.sServerTab1.Clear();
		dest.sServerTab2.Clear();
		dest.sServerTab3.Clear();

		if (src.sServerTab0) {
			foreach (string line0 : src.sServerTab0) {
				dest.sServerTab0.Insert(line0);
			}
		}
		if (src.sServerTab1) {
			foreach (string line1 : src.sServerTab1) {
				dest.sServerTab1.Insert(line1);
			}
		}
		if (src.sServerTab2) {
			foreach (string line2 : src.sServerTab2) {
				dest.sServerTab2.Insert(line2);
			}
		}
		if (src.sServerTab3) {
			foreach (string line3 : src.sServerTab3) {
				dest.sServerTab3.Insert(line3);
			}
		}
	}

	private static void MergeConfigSnapshot(ServerPanelServerConfig dest, ServerPanelServerConfig src)
	{
		if (!dest || !src) {
			return;
		}

		dest.VERSION = src.VERSION;
		dest.SERVERNAME = src.SERVERNAME;
		dest.LOGLEVEL = src.LOGLEVEL;
		dest.DISABLE_PANEL_LOG_FILE = src.DISABLE_PANEL_LOG_FILE;
		dest.BUTTON1NAME = src.BUTTON1NAME;
		dest.BUTTON1LINK = src.BUTTON1LINK;
		dest.BUTTON2NAME = src.BUTTON2NAME;
		dest.BUTTON2LINK = src.BUTTON2LINK;
		dest.BUTTON3NAME = src.BUTTON3NAME;
		dest.BUTTON3LINK = src.BUTTON3LINK;
		dest.DISPLAYPLAYERINFO = src.DISPLAYPLAYERINFO;
		dest.DISPLAYPLAYERTAB = src.DISPLAYPLAYERTAB;
		dest.DISPLAYPLAYERLIST = src.DISPLAYPLAYERLIST;
		dest.DISPLAYPLAYERPOSITION = src.DISPLAYPLAYERPOSITION;
		dest.DISPLAYCRAFTTAB = src.DISPLAYCRAFTTAB;
		dest.DISPLAYCURRENCY = src.DISPLAYCURRENCY;
		dest.CURRENCYNAME = src.CURRENCYNAME;
		dest.DISPLAYPLOGO = src.DISPLAYPLOGO;
		dest.LOGOPATH = src.LOGOPATH;
		dest.LOGO_WIDTH_PERCENTAGE = src.LOGO_WIDTH_PERCENTAGE;
		dest.LOGO_HEIGHT_PERCENTAGE = src.LOGO_HEIGHT_PERCENTAGE;
		dest.BUTTONTAB0NAME = src.BUTTONTAB0NAME;
		dest.BUTTONTAB1NAME = src.BUTTONTAB1NAME;
		dest.BUTTONTAB2NAME = src.BUTTONTAB2NAME;
		dest.BUTTONTAB3NAME = src.BUTTONTAB3NAME;

		MergeStringTabs(dest, src);
	}


	private static bool IsLoadedConfigUsable(ServerPanelServerConfig config)
	{
		if (!config) {
			return false;
		}
		if (config.VERSION && config.VERSION != "") {
			return true;
		}
		if (config.SERVERNAME && config.SERVERNAME != "") {
			return true;
		}
		if (config.sServerTab0 && config.sServerTab0.Count() > 0) {
			return true;
		}
		if (config.sServerTab1 && config.sServerTab1.Count() > 0) {
			return true;
		}
		if (config.sServerTab2 && config.sServerTab2.Count() > 0) {
			return true;
		}
		if (config.sServerTab3 && config.sServerTab3.Count() > 0) {
			return true;
		}
		return false;
	}

	// Evite de retenter le meme .bak corrompu a chaque demarrage (pas de boucle dans LoadConfig, mais spam / faux espoir).
	private static void MoveCorruptBackupAside(string reason)
	{
		if (!FileExist(SP_FILE_BACKUP)) {
			return;
		}
		if (FileExist(SP_FILE_BACKUP_REJECTED)) {
			DeleteFile(SP_FILE_BACKUP_REJECTED);
		}
		if (!CopyFile(SP_FILE_BACKUP, SP_FILE_BACKUP_REJECTED)) {
			Print("[ServerPanel] 'ServerPanelConfigManager' WARNING: Could not quarantine bad backup (" + reason + ").");
			return;
		}
		DeleteFile(SP_FILE_BACKUP);
		Print("[ServerPanel] 'ServerPanelConfigManager' Invalid backup moved to " + SP_FILE_BACKUP_REJECTED + " (" + reason + ").");
	}

	private static bool TryRecoverConfigFromBackup(ServerPanelServerConfig intoConfig)
	{
		if (!FileExist(SP_FILE_BACKUP) || !intoConfig) {
			return false;
		}

		ServerPanelServerConfig recovered = new ServerPanelServerConfig();
		JsonFileLoader<ServerPanelServerConfig>.JsonLoadFile(SP_FILE_BACKUP, recovered);
		if (!IsLoadedConfigUsable(recovered)) {
			Print("[ServerPanel] 'ServerPanelConfigManager' WARNING: Backup " + SP_FILE_BACKUP + " exists but is empty or invalid.");
			MoveCorruptBackupAside("merge recovery");
			return false;
		}

		Print("[ServerPanel] 'ServerPanelConfigManager' Recovered configuration from backup (previous data merged).");
		MergeConfigSnapshot(intoConfig, recovered);
		return true;
	}

	private static void RestoreMainConfigFromBackupFile()
	{
		EnsureDirectoriesExist();

		ServerPanelServerConfig config = new ServerPanelServerConfig();
		JsonFileLoader<ServerPanelServerConfig>.JsonLoadFile(SP_FILE_BACKUP, config);

		if (!IsLoadedConfigUsable(config)) {
			Print("[ServerPanel] 'ServerPanelConfigManager' Backup unusable, writing default configuration.");
			MoveCorruptBackupAside("main missing, restore failed");
			WriteDefaultServer(config);
			return;
		}

		FixMissingOrInvalidFields(config);

		if (config.VERSION != SP_CONFIG_VERSION) {
			UpgradeConfig(config);
		} else {
			JsonFileLoader<ServerPanelServerConfig>.JsonSaveFile(SP_FILE_PATH, config);
			Print("[ServerPanel] 'ServerPanelConfigManager' Main config recreated from backup (same VERSION).");
		}
	}

	private static ServerPanelServerConfig LoadConfig() 
	{
		ServerPanelServerConfig config = new ServerPanelServerConfig;

		if (FileExist(SP_FILE_PATH)) 
		{
			Print("[ServerPanel] 'ServerPanelConfigManager' Configuration file found...");

			JsonFileLoader<ServerPanelServerConfig>.JsonLoadFile(SP_FILE_PATH, config);

			bool repairedMainFromBackup = false;
			if (!IsLoadedConfigUsable(config) && TryRecoverConfigFromBackup(config)) {
				Print("[ServerPanel] 'ServerPanelConfigManager' Main file was empty or invalid; using merged data from " + SP_FILE_BACKUP + ".");
				repairedMainFromBackup = true;
			} else if (!IsLoadedConfigUsable(config)) {
				Print("[ServerPanel] 'ServerPanelConfigManager' WARNING: Main config unusable and no valid backup; defaults will fill missing fields.");
			}

			if (config.VERSION != SP_CONFIG_VERSION)
			{
				BackupOldConfig();
				UpgradeConfig(config); // Upgrade après lecture (conserve les champs existants, ajoute les nouveaux via Upgrade + FixMissing)
			}
			else
			{
				Print("[ServerPanel] 'ServerPanelConfigManager' Configuration loaded.");
				if (repairedMainFromBackup) {
					JsonFileLoader<ServerPanelServerConfig>.JsonSaveFile(SP_FILE_PATH, config);
				}
			}
		}
		else 
		{
			Print("[ServerPanel] 'ServerPanelConfigManager' Configuration file not found.");
			EnsureDirectoriesExist();
			if (FileExist(SP_FILE_BACKUP)) {
				Print("[ServerPanel] 'ServerPanelConfigManager' Restoring from " + SP_FILE_BACKUP + " (copying previous data into new main file).");
				RestoreMainConfigFromBackupFile();
				JsonFileLoader<ServerPanelServerConfig>.JsonLoadFile(SP_FILE_PATH, config);
			} else {
				Print("[ServerPanel] 'ServerPanelConfigManager' No backup; creating a default configuration.");
				WriteDefaultServer(config);
			}
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

		// Numeric (LOGLEVEL: 0 = aucun log via ServerPanelLogger ; 1–3 = info / warn / error)
		if (config.LOGLEVEL < 0) config.LOGLEVEL = 0;
		if (config.LOGLEVEL > 3) config.LOGLEVEL = 3;
		if (config.DISABLE_PANEL_LOG_FILE != true && config.DISABLE_PANEL_LOG_FILE != false) config.DISABLE_PANEL_LOG_FILE = false;
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
		config.DISABLE_PANEL_LOG_FILE = false;
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

	// Lors d'un bump de SP_CONFIG_VERSION : ajouter ici uniquement des defauts pour les *nouveaux* champs.
	// Ne jamais ecraser les donnees utilisateur ; le JSON est deja charge dans `config` (ou fusionne depuis .bak).
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

				// LOGLEVEL : ne pas remplacer 0 (désactivé) ; seulement valeurs invalides
				if (config.LOGLEVEL < 0) {
					config.LOGLEVEL = 1;
				}
				if (config.LOGLEVEL > 3) {
					config.LOGLEVEL = 3;
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
