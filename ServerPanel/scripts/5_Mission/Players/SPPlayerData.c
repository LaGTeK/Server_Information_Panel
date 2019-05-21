/*class SPPlayerData {
	string SName;
	string sHandName;

	int IPingMax;
	int IPingMin;
	int IPingAvg;

	vector sPlyPos;

	float sHealth;
	float sBlood;
	float sShock;
	float sEnergy;
	float sWater;
	float sStamina;
	float sDistance;
	float sPlaytime;
	float sPlayers_killed;
	float sInfected_killed;
	float sLongest_survivor_hit;
	
	bool sSick;

	static void Load( out SPPlayerData data, ref PlayerBase player )
	{
		data.VPosition 				= player.GetPosition();
		data.sHealth 				= player.GetHealth( "GlobalHealth","Health" );
		data.sBlood 				= player.GetHealth( "GlobalHealth", "Blood" );
		data.sShock 				= player.GetHealth( "GlobalHealth", "Shock" );
		data.sEnergy 				= player.GetStatEnergy().Get();
		data.sWater					= player.GetStatWater().Get();
		data.sStamina 				= player.GetStatStamina().Get();
		data.sDistance 				= plyFData.Insert(player.StatGet("dist"));
		data.sPlaytime 				= plyFData.Insert(player.StatGet("playtime"));
		data.sPlyPos 				= player.GetPosition();
		data.sPlayers_killed 		= plyFData.Insert(player.StatGet("players_killed"));
		data.sInfected_killed 		= plyFData.Insert(player.StatGet("infected_killed"));
		data.sLongest_survivor_hit 	= plyFData.Insert(player.StatGet("longest_survivor_hit"));
		data.sSick 					= player.HasDisease();
		data.sHandName				= player.GetItemInHands().GetInventoryItemType().GetName()
	}
}*/