class ServerPanelLogger {
    static string file_path;
    static bool defaultIO = true;
    
    static const int NO_LOG = 0;
    static const int LOG_LEVEL_INFO = 1;
    static const int LOG_LEVEL_WARN = 2;
    static const int LOG_LEVEL_ERROR = 3;

    static int m_LogLevel = LOG_LEVEL_INFO; // Définir le niveau de log par défaut


    // Constructeur de la classe (ne doit pas être statique)
    void ServerPanelLogger() {
    }

    // Méthode de log statique
    static void Log(int level, string module, string txt) {
        // Use the server configuration log level for comparison
        if (level > NO_LOG) {  // Check log level against server config setting
            if (defaultIO) {
                // Log to console if defaultIO is true
                Print(GetDate() + " [" + module + "]: " + txt);
            } else {
                // Attempt to open the log file
                FileHandle logFile = OpenFile(file_path, FileMode.APPEND);
                if (logFile != 0) {
                    // Log to the file if it opens successfully
                    FPrintln(logFile, GetDate() + " [" + module + "]: " + txt);
                    CloseFile(logFile);
                } else {
                    // Fallback to console logging if file logging fails
                    defaultIO = true;
                    Print("!!! Falling back to scripts.txt, can't write to " + file_path);
                    Print(GetDate() + " [" + module + "]: " + txt);
                }
            }
        }
    }

    // Méthode pour changer le système IO en statique
    static void SwitchToCustomIO() {
        string tempPath = SP_LOG_PATH;
        SetFileName(tempPath);
        Log(LOG_LEVEL_INFO, "ServerPanelLogger", "Will try to create ServerPanel log file in " + tempPath);
    }

    // Méthode pour définir le nom de fichier comme statique
    static private void SetFileName(string fPath) {
        string tPath = fPath + "ServerPanel_" + GetDate(true) + ".log";
        if (!FileExist(fPath)) MakeDirectory(fPath);

        FileHandle logFile = OpenFile(tPath, FileMode.APPEND);
        if (logFile != 0) {
            Log(LOG_LEVEL_INFO, "ServerPanelLogger", "Switching to logfile: " + tPath);
            defaultIO = false;
            file_path = tPath;
            FPrintln(logFile, "---------------------------------------------");
            FPrintln(logFile, "ServerPanel log started at " + GetDate());
            FPrintln(logFile, "");
            CloseFile(logFile);
        } 
        else {
            if (FileExist(tPath)) {
                Log(LOG_LEVEL_INFO, "ServerPanelLogger", "Can't write to file " + tPath);
            } 
            else {
                Log(LOG_LEVEL_INFO, "ServerPanelLogger", "Can't create file " + tPath + " (files per directory limit exceeded?)");
            }
        }
    }

    // Méthode pour obtenir la date, reste statique
    static private string GetDate(bool fileFriendly = false) {
        int year, month, day, hour, minute, second;

        GetYearMonthDay(year, month, day);
        GetHourMinuteSecond(hour, minute, second);

        string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
        if (fileFriendly) {
            date.Replace(" ", "_");
            date.Replace(".", "-");
            date.Replace(":", "-");
        }

        return date;
    }
};
