class ServerPanelLogger {
	private string file_path;
	private bool defaultIO = true;

	void ServerPanelLogger() {
	}

	void Log(string module, string txt) {
		if (defaultIO) {
			Print(GetDate() + " [" + module + "]: " + txt);
		} 
		else {
			FileHandle logFile = OpenFile(file_path, FileMode.APPEND);
			if (logFile != 0) {
				FPrintln(logFile, GetDate() + " [" + module + "]: " + txt);
				CloseFile(logFile);
			} 
			else {
				defaultIO = true;
				Log("ServerPanelLogger", "WARN: !!! Falling back to scripts.txt, can't write to " + file_path);
				Log(module, txt);
			}
		}
	}

	void SwitchToCustomIO() {
		string tempPath = LOG_PATH;
		string realProfiles = "";
		//if (!defaultIO) return;
		if (FileExist(tempPath)) {
			SetDir(tempPath);
			Log("ServerPanelLogger", "INFO: Will try to create ServerPanel log file in " + tempPath);
		}
		else {
			tempPath = "$profile:";
			SetDir(tempPath);
			Log("ServerPanelLogger", "INFO: Will try to create ServerPanel log file in " + tempPath);
		}

		//if (defaultIO) {
		//	tempPath = "$profile:";
		//	if (realProfiles != "") Log("ServerPanelLogger", "INFO: Will try to create ServerPanel log file in profile root: " + realProfiles);
		//		else Log("ServerPanelLogger", "INFO: Will try to create ServerPanel log file in profile root: " + tempPath);
		//	SetDir(tempPath);
		//}
		//if (defaultIO) Log("ServerPanelLogger", "WARN: All attempts to use custom log file failed, using script.log");
	}

	private void SetDir(string fPath) {
		string tPath = fPath + "ServerPanel_" + GetDate(true) + ".log";
		if (!FileExist(fPath)) MakeDirectory(fPath);

		FileHandle logFile = OpenFile(tPath, FileMode.APPEND);
		if (logFile != 0) {
			Log("ServerPanelLogger", "INFO: Switching to logfile: " + tPath);
			defaultIO = false;
			file_path = tPath;
			FPrintln(logFile, "---------------------------------------------");
			FPrintln(logFile, "ServerPanel log started at " + GetDate());
			FPrintln(logFile, "");
			CloseFile(logFile);
		} 
		else {
			if (FileExist(tPath)) {
				Log("ServerPanelLogger", "INFO: Can't write to file " + tPath);
			} 
			else {
				Log("ServerPanelLogger", "INFO: Can't create file " + tPath + " (files per directory limit exceeded?)");
			}
		}
	}

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
