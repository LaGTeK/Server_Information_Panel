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
	
	ref array<string> sServerTab0;
	ref array<string> sServerTab1;
	ref array<string> sServerTab2;
	ref array<string> sServerTab3;
}
