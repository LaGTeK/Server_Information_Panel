class ServerPanelStatic
{
    static ref map<string, string> m_ItemDisplayNames;

	static bool IsItemExisting(string type_name)
	{
		return g_Game.ConfigIsExisting( CFG_VEHICLESPATH + " " + type_name ) || g_Game.ConfigIsExisting( CFG_WEAPONSPATH + " " + type_name ) || g_Game.ConfigIsExisting( CFG_MAGAZINESPATH + " " + type_name );
	}
      
	//! @note this is for the rare cases where we only have a classname, not an object.
	//! If we have an object, should use <object>.GetDisplayName() instead.
	static string GetItemDisplayNameWithType( string type_name, map<string, string> cache = NULL )
	{
		string cfg_name;
		string cfg_name_path;

		if ( cache && cache.Find( type_name, cfg_name ) )
		{
			return cfg_name;
		}
		else if ( g_Game.ConfigIsExisting( CFG_WEAPONSPATH + " " + type_name ) )
		{
			cfg_name_path = CFG_WEAPONSPATH + " " + type_name + " displayName";
			g_Game.ConfigGetText( cfg_name_path, cfg_name );
		}
		else if ( g_Game.ConfigIsExisting( CFG_VEHICLESPATH + " " + type_name ) )
		{
			cfg_name_path = CFG_VEHICLESPATH + " " + type_name + " displayName";
			g_Game.ConfigGetText( cfg_name_path, cfg_name );
		}
		else if ( g_Game.ConfigIsExisting( CFG_MAGAZINESPATH + " " + type_name ) )
		{
			cfg_name_path = CFG_MAGAZINESPATH + " " + type_name + " displayName";
			g_Game.ConfigGetText( cfg_name_path, cfg_name );
		}
		if (!cfg_name)
		{
			cfg_name = type_name;
		}

		if (cfg_name.IndexOf("$UNT$") == 0)
			cfg_name.Replace("$UNT$", "");

		if ( cache )
		{
			cache.Insert( type_name, cfg_name );
		}

		return cfg_name;
	}
}
