class ServerPanelBase {

	static ref ServerPanelConfig m_ServerPanelConfig;
	static ref ServerPanelLogger m_ServerPanelLogger;

	ref TStringArray sServerTab0 = new TStringArray;
	ref TStringArray sServerTab1 = new TStringArray;
	ref TStringArray sServerTab2 = new TStringArray;
	ref TStringArray sServerTab3 = new TStringArray;

	bool	DisplayPlayerTab;
	bool	playerInfo;

	void ServerPanelBase() {
		if (!GetConfig().IsDefaultIO()) {
			GetLogger().SwitchToCustomIO();
		}
		GetRPCManager().AddRPC( "ServerPanelI", "SyncConfigRequest", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "ServerPanelI", "SyncTabsRequest", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "ServerPanelI", "SyncPlayersRequest", this, SingeplayerExecutionType.Server );
		//GetRPCManager().AddRPC( "ServerPanelI", "SyncWeatherRequest", this, SingeplayerExecutionType.Server );

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
		sServerTab0				= GetConfig().GetTab0Data();
		sServerTab1				= GetConfig().GetTab1Data();
		sServerTab2				= GetConfig().GetTab2Data();
		sServerTab3				= GetConfig().GetTab3Data();

		DisplayPlayerTab		= GetConfig().GetDisplayPlayerTab();

		string buttonTab0Name	= GetConfig().GetButtonTab0Name();
		string buttonTab1Name	= GetConfig().GetButtonTab1Name();
		string buttonTab2Name	= GetConfig().GetButtonTab2Name();
		string buttonTab3Name	= GetConfig().GetButtonTab3Name();

		if (buttonTab0Name == "")	sServerTab0 = NULL;
		else sServerTab0 = GetConfig().GetTab0Data();

		if (buttonTab1Name == "") sServerTab1 = NULL;
		else sServerTab1 = GetConfig().GetTab1Data();

		if (buttonTab2Name == "") sServerTab2 = NULL;
		else sServerTab2 = GetConfig().GetTab2Data();

		if (buttonTab3Name == "") sServerTab3 = NULL;
		else sServerTab3 = GetConfig().GetTab3Data();
		
		ServerPanelBase.Log("ServerPanelI", "SERVER READY");
	}

	void OnClientReady() {
		
		ServerPanelBase.Log("ServerPanelI", "CLIENT READY");
	}

	void SyncConfigRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		ref TStringArray configListS = new TStringArray;
		ref TBoolArray configListB = new TBoolArray;

		if ( type == CallType.Server && GetGame().IsServer() ) {
			GetConfig().reloadConfig();
			configListS.Insert(GetConfig().GetButton1Name());
			configListS.Insert(GetConfig().GetButton1Link());
			configListS.Insert(GetConfig().GetButton2Name());
			configListS.Insert(GetConfig().GetButton2Link());
			configListS.Insert(GetConfig().GetButton3Name());
			configListS.Insert(GetConfig().GetButton3Link());
			configListS.Insert(GetConfig().GetServerName());
			configListS.Insert(GetConfig().GetButtonTab0Name());
			configListS.Insert(GetConfig().GetButtonTab1Name());
			configListS.Insert(GetConfig().GetButtonTab2Name());
			configListS.Insert(GetConfig().GetButtonTab3Name());
			configListB.Insert(GetConfig().GetDisplayPlayerInfo());
			configListB.Insert(GetConfig().GetDisplayPlayerTab());

			ref Param2<ref TStringArray, ref TBoolArray> m_DataTAB =  new Param2 <ref TStringArray, ref TBoolArray> (configListS, configListB);
			GetRPCManager().SendRPC( "ServerPanelI", "SyncConfig", m_DataTAB, true, sender );
			ServerPanelBase.Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - Config sync");
		}
	}

	void SyncTabsRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) 	{
		if ( type == CallType.Server && GetGame().IsServer() ) {
			ref Param4<ref TStringArray,ref TStringArray,ref TStringArray,ref TStringArray> m_DataContent = new Param4<ref TStringArray,ref TStringArray,ref TStringArray,ref TStringArray>(sServerTab0,sServerTab1,sServerTab2,sServerTab3);
			GetRPCManager().SendRPC( "ServerPanelI", "SyncTab", m_DataContent, true, sender );
			ServerPanelBase.Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - Tabs sync");
		}
	}

	void SyncPlayersRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		ref TStringArray playerListS 	= new TStringArray;
		ref TIntArray plyData 			= new TIntArray;
		ref TFloatArray plyFData 		= new TFloatArray;
		//ref TBoolArray PlyBData			= new TBoolArray;
		string Item = "Nothing :)";
		array<Man> players 				= new array<Man>;
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
					plyData.Insert(player.GetHealth());
					plyData.Insert(player.GetHealth("", "Blood"));
					//plyData.Insert(player.StatGet("killdist"));
					//plyData.Insert(player.StatGet("kills"));
					//plyData.Insert(player.StatGet("killszombies");
					plyFData.Insert(player.GetStatWater().Get());
					plyFData.Insert(player.GetStatEnergy().Get());
					plyFData.Insert(player.StatGet("dist"));
					plyFData.Insert(player.StatGet("playtime"));
					plyPos = player.GetPosition();
					plyFData.Insert(player.GetHealth( "", "Shock" ));
					plyFData.Insert(player.GetStatStamina().Get());
					bool m_HasDisease = player.HasDisease();

					if (player.GetItemInHands() && !player.GetCommand_Vehicle()) {Item = (player.GetItemInHands().GetInventoryItemType().GetName())}
					if (player.GetCommand_Vehicle()) {Item = (player.GetCommand_Vehicle().GetTransport().GetDisplayName())}
				}
				playerListS.Insert(plyIdent.GetName());				
			}
			GetRPCManager().SendRPC( "ServerPanelI", "SyncPlayers", new Param6<ref TStringArray, ref TIntArray, vector, ref TFloatArray, string, bool> (playerListS, plyData, plyPos, plyFData, Item, m_HasDisease), true, sender );
			ServerPanelBase.Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - player list sync");
		}
	}
};