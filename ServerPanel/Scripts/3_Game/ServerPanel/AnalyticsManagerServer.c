modded class AnalyticsManagerServer
{
    const string STAT_CONNECTION_TIME = "connection_time"; // Nouveau paramètre pour l'heure de connexion

    // Lors de la connexion du joueur
    override void OnPlayerConnect(Man player)
    {
		player.StatRegister(STAT_DISTANCE);
		player.StatRegister(STAT_PLAYTIME);
		player.StatRegister(STAT_PLAYERS_KILLED);
		player.StatRegister(STAT_INFECTED_KILLED);
		player.StatRegister(STAT_LONGEST_SURVIVOR_HIT);

        // Enregistrer le temps de connexion
        player.StatRegister(STAT_CONNECTION_TIME);
        
        // Récupérer l'heure actuelle du serveur en secondes et la stocker comme temps de connexion
        float connectionTime = Math.Round(g_Game.GetTime() / 1000); // Temps en secondes
        player.StatUpdate(STAT_CONNECTION_TIME, connectionTime);
    }

    // Lors de la déconnexion du joueur
    /*override void OnPlayerDisconnect(Man player)
    {
        super.OnPlayerDisconnect(player); // Appel à la méthode d'origine pour mettre à jour les autres stats
        
        // Calculer la durée de connexion
        float disconnectTime = Math.Round(g_Game.GetTime() / 1000); // Heure actuelle en secondes
        float connectionTime = player.StatGet(STAT_CONNECTION_TIME); // Récupérer l'heure de connexion enregistrée
        
        // Calculer la durée de session (temps passé connecté)
        float sessionDuration = disconnectTime - connectionTime;

        // Mettre à jour le temps total de jeu
        player.StatUpdate(STAT_CONNECTION_TIME, sessionDuration);
    }*/
};
