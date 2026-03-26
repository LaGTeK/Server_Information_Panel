class ServerPanelAutoOpenState
{
	ref array<string> SeenPlayerIds;

	void ServerPanelAutoOpenState()
	{
		SeenPlayerIds = new array<string>();
	}
}

class ServerPanelAutoOpenStateManager
{
	private static const string SP_AUTOOPEN_STATE_FILE = SP_DIR_PATH + "/AutoOpenSeen.json";
	private static ref ServerPanelAutoOpenState m_State;

	static ServerPanelAutoOpenState GetState()
	{
		if (!m_State) {
			m_State = new ServerPanelAutoOpenState();
			Load();
		}
		return m_State;
	}

	static void Load()
	{
		ServerPanelConfigManager.EnsureDirectoriesExist();

		ServerPanelAutoOpenState state = new ServerPanelAutoOpenState();
		if (FileExist(SP_AUTOOPEN_STATE_FILE)) {
			JsonFileLoader<ServerPanelAutoOpenState>.JsonLoadFile(SP_AUTOOPEN_STATE_FILE, state);
		}

		if (!state.SeenPlayerIds) {
			state.SeenPlayerIds = new array<string>();
		}

		m_State = state;
	}

	static void Save()
	{
		if (!m_State) {
			return;
		}
		ServerPanelConfigManager.EnsureDirectoriesExist();
		JsonFileLoader<ServerPanelAutoOpenState>.JsonSaveFile(SP_AUTOOPEN_STATE_FILE, m_State);
	}

	static bool HasSeen(string playerId)
	{
		if (!playerId || playerId == "") {
			return true;
		}
		ServerPanelAutoOpenState state = GetState();
		return state.SeenPlayerIds.Find(playerId) > -1;
	}

	static void MarkSeen(string playerId)
	{
		if (!playerId || playerId == "") {
			return;
		}
		ServerPanelAutoOpenState state = GetState();
		if (state.SeenPlayerIds.Find(playerId) > -1) {
			return;
		}
		state.SeenPlayerIds.Insert(playerId);
		Save();
	}
}

