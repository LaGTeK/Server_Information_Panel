class ServerPanelServerConfig
{
	string VERSION;  // Use text for versioning, now at the top
	string SERVERNAME;
	// If true, the panel auto-opens once per player on this server (server-side persistence).
	bool AUTO_OPEN_ON_FIRST_JOIN;
	// 0 = aucun message ServerPanelLogger ; 1 = info+ ; 2 = warn+ ; 3 = erreurs seules. Les Print("[ServerPanel] ...") au demarrage restent cote serveur.
	int LOGLEVEL;
	// true = pas de fichier ServerPanel_*.log (Profiles/.../ServerPanel/Logs/) ; avec LOGLEVEL>0 les logs vont en console ; avec LOGLEVEL 0, quasi silencieux hors Print boot.
	bool DISABLE_PANEL_LOG_FILE;
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
	
	ref array<string> sServerTab0;
	ref array<string> sServerTab1;
	ref array<string> sServerTab2;
	ref array<string> sServerTab3;
}
