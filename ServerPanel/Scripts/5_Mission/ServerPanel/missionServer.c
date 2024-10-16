modded class MissionServer {

    void MissionServer() {
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
};
