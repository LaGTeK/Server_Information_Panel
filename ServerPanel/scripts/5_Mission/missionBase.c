modded class MissionBase
{

	override UIScriptedMenu CreateScriptedMenu(int id)
	{
		UIScriptedMenu menu = NULL;
		menu = super.CreateScriptedMenu(id);
		if (!menu)
		{
			switch (id)
			{
				case SERVER_PANEL:
				//menu = new ServerPanelMenu;
				menu = GetServerPanelMenu();
				break;
			}
			if (menu)
			{
				menu.SetID(id);
			}
		}
		return menu;
	}
};