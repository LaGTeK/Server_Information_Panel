modded class MissionGameplay {

	void MissionGameplay()
	{
		//InfoPanel
		m_ServerPanelBase = NULL;
		GetServerPanelBase();
	}

	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		GetUIManagemer().OnKeyRelease(key);
	}
};