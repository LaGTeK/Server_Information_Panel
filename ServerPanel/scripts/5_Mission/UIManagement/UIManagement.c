/* 
	Easy class to set things that link to multiple UI's for 
	shit like setting if the user is typing in another ui's text box 
*/
class UIManagemer	{

	void UIManagemer()	{
	}

	bool m_IsTyping = false;

	UIManager uiManager = g_Game.GetUIManager();

	void SetIsTyping(bool value)	{
		m_IsTyping = value;
	}

	bool GetIsTyping()	{
		return m_IsTyping;
	}


	void OnKeyRelease(int key)	{
		if (uiManager.IsMenuOpen(MENU_CHAT_INPUT))
			return;

		if (key == KeyCode.KC_ESCAPE)	{
			HideCurrentMenu();
			return;
		}

		if (key == GetServerPanelClientConfig().SPMENUKEY)	{
			if (!uiManager.IsMenuOpen(MENU_INGAME))	{
				uiManager.CloseAll();
				uiManager.ShowScriptedMenu(GetServerPanelMenu(), NULL);
			}
			else	{
				GetServerPanelMenu().Hide();
				uiManager.CloseAll();
		}
			return;
		}

		if (m_IsTyping)
			return;

	}

	void OpenInfoMenu()	{
		if (!m_ServerPanelMenu)	{
			if (!uiManager.IsMenuOpen(MENU_INGAME))	{
				uiManager.CloseAll();
				uiManager.ShowScriptedMenu(GetServerPanelMenu(), NULL);
			}
		}
		else	{
			GetServerPanelMenu().Hide();
			uiManager.CloseAll();
		}
	}

	void HideCurrentMenu()	{
		if (!uiManager.IsMenuOpen(MENU_INGAME))	{
			uiManager.CloseAll();
			GetGame().GetInput().ResetGameFocus();
			GetGame().GetUIManager().ShowUICursor(false);
			GetGame().GetMission().GetHud().Show(true);
		}
	}
}

static ref UIManagemer g_UIManagemer;
static ref UIManagemer GetUIManagemer()	{
	if (!g_UIManagemer)
		g_UIManagemer = new ref UIManagemer();
	return g_UIManagemer;
}