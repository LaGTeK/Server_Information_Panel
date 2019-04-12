modded class MissionServer {
	ref ServerPanelBase m_ServerPanelBase;

	void MissionServer() {
		ServerPanelBase.Log("ServerPanelValue","ServerPanel Loaded Server side");
	}

    void ~MissionServer() {
        
	}

	private ref ServerPanelBase GetServerPanelBase() {
		if ( !m_ServerPanelBase ) {
			m_ServerPanelBase = new ref ServerPanelBase;
		}
		return m_ServerPanelBase;
	}

	override void OnInit() {
		super.OnInit();
		ServerPanelBase.Log("ServerPanelI", "SERVER PANEL INIT");
		GetServerPanelBase().OnServerReady();
		//GetRPCManager().AddRPC( "ServerPanelI", "SyncMenuKeyRequest", this, SingeplayerExecutionType.Client );
	}
};