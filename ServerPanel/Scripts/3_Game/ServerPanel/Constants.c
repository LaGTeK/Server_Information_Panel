
static const int SERVER_PANEL			=	69613;

static const string SP_PROFILE_ROOT		= "$profile:";
static const string SP_DIRECTORY		= "ServerPanel";
static const string SP_LOGS_DIRECTORY	= "Logs";
static const string SP_FILENAME			= "ServerPanel.json";

static const string SP_CONFIG_VERSION    = "1.7";

static const string SP_DIR_PATH 		= SP_PROFILE_ROOT + "/" + SP_DIRECTORY;
static const string SP_LOG_PATH 		= SP_DIR_PATH + "/" + SP_LOGS_DIRECTORY + "/";
static const string SP_FILE_PATH 		= SP_DIR_PATH + "/" + SP_FILENAME;

class ServerPanelConstants
{
    // Colors
    static const int 			WHITE				= ARGB(255, 255, 255, 255);
    static const int 			ORANGE				= ARGB(255, 255, 165, 0);
    static const int 			GREEN				= ARGB(255, 0, 206, 0);
    static const int 			RED					= ARGB(255, 255, 0, 0);
    static const int 			YELLOW				= ARGB(255, 255, 255, 0);
    static const int 			ACTIVE_BUTTON_COLOR	= ARGB(255, 153, 153, 153);
    static const int 			NORMAL_BUTTON_COLOR	= ARGB(255, 51, 51, 51);
}