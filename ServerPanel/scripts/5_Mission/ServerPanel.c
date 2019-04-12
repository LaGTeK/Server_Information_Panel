class ServerPanelBase {

	static ref ServerPanelConfig m_ServerPanelConfig;
	static ref ServerPanelLogger m_ServerPanelLogger;

	ref TStringArray sServerRules = new TStringArray;
	ref TStringArray sServerDescription = new TStringArray;
	ref TStringArray sServerTab2 = new TStringArray;
	ref TStringArray sServerTab3 = new TStringArray;

	//string btn1name, btn2name, btn1link, btn2link, btn3link, btn3name, buttonTab2Name, buttonTab3Name, sServerName;
	int playerInfo, SPmenuKey;

	void ServerPanelBase() {
		//GetRPCManager().AddRPC( "ServerPanelI", "SyncKeyRequest", this, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "ServerPanelI", "SyncButtonRequest", this, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "ServerPanelI", "SyncSNameTabsRequest", this, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "ServerPanelI", "SyncTabsRequest", this, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "ServerPanelI", "SyncPlayersRequest", this, SingeplayerExecutionType.Client );

		m_ServerPanelConfig = new ref ServerPanelConfig;
	}

	static ref ServerPanelConfig GetConfig() {
		if ( !m_ServerPanelConfig ) {
			m_ServerPanelConfig = new ref ServerPanelConfig;
		}
		return m_ServerPanelConfig;
	}

	static ref ServerPanelLogger GetLogger(){
		if (!m_ServerPanelLogger){
			m_ServerPanelLogger = new ref ServerPanelLogger;
		}
		return m_ServerPanelLogger;
	}


	static void Log( string module, string toLog ) {
		GetLogger().Log( module, toLog );//need fonction to log my data i can't debug because i don't know values
	}

	void OnServerReady() {
		GetConfig().reloadConfig();
		GetConfig().reloadTab();		

		sServerDescription = GetConfig().GetDescriptionData();
		sServerRules = GetConfig().GetRulesData();

		string buttonTab2Name = GetConfig().GetButtonTab2Name();; 
		string buttonTab3Name = GetConfig().GetButtonTab3Name();

		if (buttonTab2Name == "") {
			sServerTab2 = NULL;
		}
		else {
			sServerTab2 = GetConfig().GetTab2Data();
		}
		if (buttonTab3Name == "") {
			sServerTab3 = NULL;
		}
		else {
			sServerTab3 = GetConfig().GetTab3Data();
		}
		
		ServerPanelBase.Log("ServerPanelI", "SERVER READY");
	}

	void OnClientReady() {
		//GetRPCManager().SendRPC( "ServerPanelI", "SyncTabsRequest", new Param1< int >( 0 ), true, NULL );
		ServerPanelBase.Log("ServerPanelI", "CLIENT READY");
	}

	/*void SyncKeyRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {

		if (type == CallType.Server && sender != NULL) {
			GetConfig().reloadKey();
			ref Param1<int> m_KeyBTN =  new Param1 <int> (GetConfig().GetSPMenuKey());
			GetRPCManager().SendRPC( "ServerPanelI", "SyncKey", m_KeyBTN , true, sender );
			ServerPanelBase.Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - Key sync");
		}
	}*/

	void SyncButtonRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {

		if (type == CallType.Server && sender != NULL) {
			GetConfig().reloadConfig();
			ref Param6<string, string, string, string, string, string> m_DataBTN =  new Param6 <string, string, string, string, string, string> (GetConfig().GetButton1Name(), GetConfig().GetButton1Link(), GetConfig().GetButton2Name(), GetConfig().GetButton2Link(), GetConfig().GetButton3Name(), GetConfig().GetButton3Link());
			GetRPCManager().SendRPC( "ServerPanelI", "SyncButtons", m_DataBTN , true, sender );
			ServerPanelBase.Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - Button sync");
		}
	}

	void SyncSNameTabsRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {

		if (type == CallType.Server && sender != NULL){
			GetConfig().reloadConfig();
			ref Param4<string, string, string, int> m_DataTAB =  new Param4 <string, string, string, int> (GetConfig().GetServerName(), GetConfig().GetButtonTab2Name(), GetConfig().GetButtonTab3Name(), GetConfig().GetPlayerInfo());
			GetRPCManager().SendRPC( "ServerPanelI", "SyncSNameTabs", m_DataTAB, true, sender );
			ServerPanelBase.Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - NameTabs sync");
		}
	}

	void SyncTabsRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) 	{

		if (type == CallType.Server && sender != NULL) {
			ref Param4<ref TStringArray,ref TStringArray,ref TStringArray,ref TStringArray> m_DataContent = new Param4<ref TStringArray,ref TStringArray,ref TStringArray,ref TStringArray>(sServerDescription,sServerRules,sServerTab2,sServerTab3);
			GetRPCManager().SendRPC( "ServerPanelI", "SyncTab", m_DataContent, true, sender );
			ServerPanelBase.Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - Tabs sync");
		}
	}

	void SyncPlayersRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		ref TStringArray playerListS = new TStringArray;
		ref TIntArray plyData = new TIntArray;
		array<Man> players = new array<Man>;
		PlayerBase player;
		PlayerIdentity plyIdent;
		vector plyPos;

		if ( type == CallType.Server && GetGame().IsServer() ) {
			GetGame().GetPlayers(players);
			for (int i = 0; i < players.Count(); ++i) {
				player = PlayerBase.Cast(players.Get(i));
				plyIdent = player.GetIdentity();
				if (plyIdent.GetPlayerId() == sender.GetPlayerId()) {
					plyData.Insert(GetGame().GetTime());
					plyData.Insert(i);
					plyData.Insert(player.GetHealth("", "Health"));
					plyData.Insert(player.GetHealth("", "Blood"));
					plyPos = player.GetPosition();
				}
				playerListS.Insert(plyIdent.GetName());
			}
			GetRPCManager().SendRPC( "ServerPanelI", "SyncPlayers", new Param3<ref TStringArray, ref TIntArray, vector> (playerListS, plyData, plyPos), true, sender );
			ServerPanelBase.Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - player list sync");
		}
	}
};



