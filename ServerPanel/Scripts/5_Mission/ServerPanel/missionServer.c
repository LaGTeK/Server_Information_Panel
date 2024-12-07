modded class MissionServer
{
    private float m_ServerUptimeInSeconds = 0; // Compteur d'uptime en secondes

    void MissionServer() 
    {
        // Initialisation de l'uptime
        m_ServerUptimeInSeconds = 0;

        // InfoPanel
        m_ServerPanelBase = NULL;
        GetServerPanelBase();
    }

    void ~MissionServer() {
        // Nettoyage des objets pour éviter les fuites de mémoire
        if (m_ServerPanelBase) {
            delete m_ServerPanelBase;
        }
    }

    // Fonction OnUpdate appelée régulièrement
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // Incrémente l'uptime par le temps écoulé depuis la dernière mise à jour
        m_ServerUptimeInSeconds += timeslice;
    }

    // Accesseur pour récupérer l'uptime en secondes
    float GetServerUptime() {
        return m_ServerUptimeInSeconds;
    }
};
