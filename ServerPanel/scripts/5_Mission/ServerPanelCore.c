class ServerPanelBase {

	static ref ServerPanelClientConfig g_ClientConfig;
	ref ServerPanelServerConfig g_ServerConfig;

	static ref ServerPanelLogger m_ServerPanelLogger;

	void ServerPanelBase() {
		GetLogger().SwitchToCustomIO();

		GetRPCManager().AddRPC( "ServerPanelI", "SyncPlayersRequest", this, SingeplayerExecutionType.Server );
		//GetRPCManager().AddRPC( "ServerPanelI", "SyncLeaderBoardRequest", this, SingeplayerExecutionType.Server );

		ref ServerPanelConfigManager configManager = new ref ServerPanelConfigManager;

		if (GetGame().IsServer()) {
			Log("ServerPanelConfig", "Reading Server Config");
			g_ServerConfig = configManager.ReadServerConfig();
			
		}
		else {
			Log("ServerPanelConfig", "Reading Client Config");
			//g_ClientConfig = g_ClientConfig.reloadKey();
			GetRPCManager().SendRPC("ServerPanelConfig", "GetConfigRequest", NULL, true, NULL);
		}

		g_ClientConfig = new ref ServerPanelClientConfig;

		InitRPC();
	}

	static ref ServerPanelClientConfig GetConfig() {
		if ( !g_ClientConfig ) {
			g_ClientConfig = new ref ServerPanelClientConfig;
		}
		return g_ClientConfig;
	}

	static ref ServerPanelLogger GetLogger(){
		if (!m_ServerPanelLogger){
			m_ServerPanelLogger = new ref ServerPanelLogger;
		}
		return m_ServerPanelLogger;
	}

	static void Log( string module, string toLog ) {
		GetLogger().Log( module, toLog );
	}

	void InitRPC()	{
		if (GetGame().IsServer())	{
			//Server calls
			Log("ServerPanelConfig", "ConfigRequest");
			GetRPCManager().AddRPC("ServerPanelConfig", "GetConfigRequest", this, SingeplayerExecutionType.Server);
		}
		else	{
			//Client calls
			Log("ServerPanelConfig", "ConfigResponse");
			GetRPCManager().AddRPC("ServerPanelConfig", "GetConfigResponse", this, SingeplayerExecutionType.Server);
		}
	}

	 //ONLY Called on server 
	void GetConfigRequest(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)	{
		if (!GetGame().IsServer())
			return;
		GetRPCManager().SendRPC("ServerPanelConfig", "GetConfigResponse", new Param1<ref ServerPanelServerConfig>(g_ServerConfig), true, sender);
		Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - Config sync");
	}

	//Only called on client
	void GetConfigResponse(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)	{
		if (!GetGame().IsClient())
			return;
		Param1<ref ServerPanelServerConfig> data;
		if (!ctx.Read(data))
			return;
		g_ServerConfig = data.param1;
	}

	/*void SyncLeaderBoardRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		ref TStringArray playerListS 	= new TStringArray;
		ref TFloatArray plyPData 		= new TFloatArray;
		ref TFloatArray plyIData 		= new TFloatArray;
		array<Man> players 				= new array<Man>;
		PlayerBase player;
		PlayerIdentity plyIdent;

		if ( type == CallType.Server && GetGame().IsServer() ) {

			GetGame().GetPlayers(players);
			for (int i = 0; i < players.Count(); ++i) {
				player = PlayerBase.Cast(players.Get(i));
				plyIdent = player.GetIdentity();

				playerListS.Insert(plyIdent.GetName());
				//plyFData.Insert(player.StatGet("dist"));
				//plyFData.Insert(player.StatGet("playtime"));
				plyPData.Insert(player.StatGet("players_killed"));
				plyIData.Insert(player.StatGet("infected_killed"));
				//plyFData.Insert(player.StatGet("longest_survivor_hit"));
			}
			GetRPCManager().SendRPC( "ServerPanelI", "SyncPlayers", new Param3<ref TStringArray, ref TFloatArray, ref TFloatArray> (playerListS, plyPData, plyIData), true, sender );
			Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - Player LeaderBoard sync");
		}
	}*/

	void SyncPlayersRequest( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		ref TStringArray playerListS 	= new TStringArray;
		ref TIntArray plyData 			= new TIntArray;
		ref TFloatArray plyFData 		= new TFloatArray;
		string Item = "Nothing :)";
		array<Man> players 				= new array<Man>;
		PlayerBase player;
		PlayerIdentity plyIdent;

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
					plyFData.Insert(player.GetStatWater().Get());
					plyFData.Insert(player.GetStatEnergy().Get());
					plyFData.Insert(player.GetHealth( "", "Shock" ));
					plyFData.Insert(player.GetStatStamina().Get());
					plyFData.Insert(player.StatGet("dist"));
					plyFData.Insert(player.StatGet("playtime"));
					plyFData.Insert(player.StatGet("players_killed"));
					plyFData.Insert(player.StatGet("infected_killed"));
					plyFData.Insert(player.StatGet("longest_survivor_hit"));
					vector plyPos = player.GetPosition();
					bool m_HasDisease = player.HasDisease();

					if (player.GetItemInHands() && !player.GetCommand_Vehicle()) {Item = (player.GetItemInHands().GetInventoryItemType().GetName())}
					if (player.GetCommand_Vehicle()) {Item = (player.GetCommand_Vehicle().GetTransport().GetDisplayName())}
				}
				playerListS.Insert(plyIdent.GetName());				
			}
			GetRPCManager().SendRPC( "ServerPanelI", "SyncPlayers", new Param6<ref TStringArray, ref TIntArray, vector, ref TFloatArray, string, bool> (playerListS, plyData, plyPos, plyFData, Item, m_HasDisease), true, sender );
			Log("ServerPanelI", "" + sender.GetName() + " (" + sender.GetId() + ") - Player Stats sync");
		}
	}
};