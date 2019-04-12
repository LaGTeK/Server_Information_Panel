static PlayerBase SPGetPlayerById (int plyId) {
	array<Man> players = new array<Man>;
	PlayerBase result = NULL;

	if (GetGame().IsMultiplayer()) {
		GetGame().GetPlayers(players);

		for (int i = 0; i < players.Count(); i++) {
			if (players.Get(i).GetIdentity().GetPlayerId() == plyId) {
				result = PlayerBase.Cast(players.Get(i));
			}
		}
	} else {
		result = PlayerBase.Cast(GetGame().GetPlayer());
	}

	return result;
}
