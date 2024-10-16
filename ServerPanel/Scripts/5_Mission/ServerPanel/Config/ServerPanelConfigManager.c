class ServerPanelConfigManager {
	private static ref ServerPanelServerConfig m_Config; // Static configuration instance

	static ServerPanelServerConfig GetConfig() {
		if (!m_Config) {
			EnsureDirectoriesExist();
			m_Config = LoadConfig();
		}
		return m_Config;
	}

	static ServerPanelServerConfig LoadConfig() {
		if (FileExist(SP_FILE_PATH)) {
			// Charger le fichier de configuration existant
			ref ServerPanelServerConfig config = ServerPanelServerConfig.Load(SP_FILE_PATH);

			if (config) {
				// Vérifier et gérer la compatibilité des versions
				if (config.VERSION.ToFloat() == 0 || config.VERSION.ToFloat() < SP_CONFIG_VERSION.ToFloat()) {
					ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Upgrading configuration file...");
					UpgradeConfig(config); // Passer config en référence pour effectuer les mises à niveau
					config.Save(SP_FILE_PATH); // Sauvegarde de la nouvelle configuration

					m_Config = config;
				} else {
					m_Config = config;
				}
			} else {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfig", "Failed to load configuration from file, loading default configuration.");
				m_Config = WriteDefaultServer(); // Créer et retourner une configuration par défaut
			}
		} else {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfig", "Configuration file not found, creating a default configuration.");
			m_Config = WriteDefaultServer(); // Créer et retourner une configuration par défaut
		}

		return m_Config;
	}

	static void SaveConfig() {
		if (m_Config) {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Saving configuration to file: " + SP_FILE_PATH);
			m_Config.Save(SP_FILE_PATH);
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Configuration saved successfully.");
		} else {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfig", "Failed to save configuration because m_Config is null.");
		}
	}

	static void EnsureDirectoriesExist() {
		if (!FileExist(SP_DIR_PATH)) {
			bool dirCreated = MakeDirectory(SP_DIR_PATH);
			if (dirCreated) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Created directory: " + SP_DIR_PATH);
			} else {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfig", "Failed to create directory: " + SP_DIR_PATH);
			}
		} else {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_WARN, "ServerPanelConfig", "Directory already exists: " + SP_DIR_PATH);
		}

		if (!FileExist(SP_LOG_PATH)) {
			bool logDirCreated = MakeDirectory(SP_LOG_PATH);
			if (logDirCreated) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Created log directory: " + SP_LOG_PATH);
			} else {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "ServerPanelConfig", "Failed to create log directory: " + SP_LOG_PATH);
			}
		} else {
			ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_WARN, "ServerPanelConfig", "Log directory already exists: " + SP_LOG_PATH);
		}
	}

	static ServerPanelServerConfig WriteDefaultServer() {
		ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Writing Default Server Config");

		// Create a new configuration object
		ref ServerPanelServerConfig config = new ref ServerPanelServerConfig;
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

		// Populate the default values
		for (int i = 0; i < 20; i++) {
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
		config.Save(SP_FILE_PATH);

		return config;
	}

	static void UpgradeConfig(ref ServerPanelServerConfig config) {
		ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Upgrading configuration file...");

		if (config.VERSION.ToFloat() < SP_CONFIG_VERSION.ToFloat()) {			
			if (config.VERSION.ToFloat() <= 1.6) {
				if (!config.CURRENCYNAME) {
					config.CURRENCYNAME = "Rubles";	
				}
				if (!config.DISPLAYCURRENCY) {
					config.DISPLAYCURRENCY = true;	
				}
				if (!config.VERSION) {
					config.VERSION = SP_CONFIG_VERSION;	
				}
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

		ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_INFO, "ServerPanelConfig", "Configuration file upgraded to version " + SP_CONFIG_VERSION);
	}

	// Méthode renommée pour être plus explicite
	static void AddHtmlTagsToTabs(ref TStringArray tab) {
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
