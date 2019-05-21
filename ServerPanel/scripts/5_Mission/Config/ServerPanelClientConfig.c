class ServerPanelClientConfig
{
	int SPMENUKEY;

	void Save()
	{
		JsonFileLoader<ServerPanelClientConfig>.JsonSaveFile(SP_CONFIGKEY_PATH, this);
	}

	static ref ServerPanelClientConfig Load()
	{
		ref ServerPanelClientConfig config = new ref ServerPanelClientConfig;
		JsonFileLoader<ServerPanelClientConfig>.JsonLoadFile(SP_CONFIGKEY_PATH, config);
		return config;
	}
}