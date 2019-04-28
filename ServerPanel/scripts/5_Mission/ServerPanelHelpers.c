//typedef array<ref SPanelPlayer> SPanelPlayerArray;
typedef array<ref SPOldJsonConfig> SPOldJsonConfigArray;
typedef array<ref SPJsonConfig> SPJsonConfigArray;

/*class SPanelPlayer {
	int m_PlayerID;
	string m_PlayerName;
	vector m_PlayerPos;
	int m_PlayerHealth;
	int m_PlayerBlood;
	float m_PlayerWater;
	float m_PlayerFood;

	void SPanelPlayer( int uid, string plyName, vector plyPos, int plyHP, int plyBld, float plyWat, float plyFod ) {
		m_PlayerID = uid;
		m_PlayerName = plyName;
		m_PlayerPos = plyPos;
		m_PlayerHealth = plyHP;
		m_PlayerBlood = plyBld;
		m_PlayerWater = plyWat;
		m_PlayerFood = plyFod;
	}
}*/

class SPOldJsonConfig {
	string ServerName, Button1Name, Button1Link, Button2Name, Button2Link, Button3Name, Button3Link, ButtonTab2Name, ButtonTab3Name;
	int PlayerInfo;
};

class SPJsonConfig {
	string ServerName, Button1Name, Button1Link, Button2Name, Button2Link, Button3Name, Button3Link, ButtonTab0Name, ButtonTab1Name, ButtonTab2Name, ButtonTab3Name;
	int PlayerInfo;
	bool UseScriptLog;
};

class SPJsonKeyConfig {
	string SPMenuKey;
};
