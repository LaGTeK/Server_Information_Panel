class ServerPanelLogger {
	private string file_path;
	private bool defaultIO = true;

	void ServerPanelLogger() {
		FindFP();
	}

	void Log(string module, string txt) {
		if (defaultIO) {
			Print(GetDate() + " [" + module + "]: " + txt);
		} else {
			FileHandle logFile = OpenFile(file_path, FileMode.APPEND);
			if (logFile != 0) {
				FPrintln(logFile, GetDate() + " [" + module + "]: " + txt);
				CloseFile(logFile);
			} else {
				defaultIO = true;
				Log("ServerPanelLogger", "WARN: !!! Falling back to scripts.txt, can't write to " + file_path);
				Log(module, txt);
			}
		}
	}

	private void FindFP() {
		string temp_path = "";
		/*if (GetCLIParam("spanelDir", temp_path)) {
			Log("ServerPanelLogger", "INFO: Will try to create log file SP_Log.txt in custom directory: " + temp_path);
			SetDir(temp_path);
		}*/
		/*if (defaultIO) {
			temp_path = "$profile:ServerPanel\\";
			Log("ServerPanelLogger", "INFO: Will try to create log file SP_Log.txt in profile directory: " + temp_path);
			SetDir(temp_path);
		}*/
		if (defaultIO) {
			temp_path = "$profile:";
			Log("ServerPanelLogger", "INFO: Will try to create log file SP_Log.txt in profile root: " + temp_path);
			SetDir(temp_path);
		}
		//if (defaultIO) Log("ServerPanelLogger", "WARN: All attempts to use custom log file failed, using script.log");
	}

	private void SetDir(string fPath) {
		string tPath = fPath + "SP_Log.txt";
		if (!FileExist(fPath)) MakeDirectory(fPath);

		FileHandle logFile = OpenFile(tPath, FileMode.APPEND);
		if (logFile != 0) {
			file_path = tPath;
			FPrintln(logFile, "---------------------------------------------");
			FPrintln(logFile, "ServerPanel log started at " + GetDate());
			FPrintln(logFile, "");
			FPrintln(logFile, "Will use script.log");
			CloseFile(logFile);
		} else {
			if (FileExist(tPath)) {
				Log("ServerPanelLogger", "INFO: Can't write to file " + tPath);
			} else {
				Log("ServerPanelLogger", "INFO: Can't create file " + tPath + " (try creating one manually)");
			}
		}
	}

	static string GetDate() {
		int year, month, day, hour, minute, second;

		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);

		string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);

		return date;
	}
};
