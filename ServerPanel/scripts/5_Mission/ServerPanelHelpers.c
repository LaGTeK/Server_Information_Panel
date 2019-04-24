typedef array<ref SPanelPlayer> SPanelPlayerArray;

class SPanelPlayer {
	int m_PlayerID;
	string m_PlayerName;
	vector m_PlayerPos;
	int m_PlayerHealth;
	int m_PlayerBlood;

	void SPanelPlayer( int uid, string plyName, vector plyPos, int plyHP, int plyBld ) {
		m_PlayerID = uid;
		m_PlayerName = plyName;
		m_PlayerPos = plyPos;
		m_PlayerHealth = plyHP;
		m_PlayerBlood = plyBld;
	}
}

class SPJsonConfig {
	string ServerName, Button1Name, Button1Link, Button2Name, Button2Link, Button3Name, Button3Link, ButtonTab2Name, ButtonTab3Name;
	int PlayerInfo;
	bool UseScriptLog;
};

class SPJsonKeyConfig {
	string SPMenuKey;
};
