modded class DayZGame {

	/*private ref map<int,string>   m_KeyBindMap;
	private ref SPKeybindConfig     m_SPKeybindConfig;*/

	void DayZGame()	{
		Print("SERVER PANEL OPENNING!");

		/*m_SPKeybindConfig = new SPKeybindConfig();

		m_KeyBindMap = new map<int,string>;
		m_KeyBindMap.Insert(KeyCode.KC_ESCAPE,"KC_ESCAPE");
		m_KeyBindMap.Insert(KeyCode.KC_1,"KC_1");
		m_KeyBindMap.Insert(KeyCode.KC_2,"KC_2");
		m_KeyBindMap.Insert(KeyCode.KC_3,"KC_3");
		m_KeyBindMap.Insert(KeyCode.KC_4,"KC_4");
		m_KeyBindMap.Insert(KeyCode.KC_5,"KC_5");
		m_KeyBindMap.Insert(KeyCode.KC_6,"KC_6");
		m_KeyBindMap.Insert(KeyCode.KC_7,"KC_7");
		m_KeyBindMap.Insert(KeyCode.KC_8,"KC_8");
		m_KeyBindMap.Insert(KeyCode.KC_9,"KC_9");
		m_KeyBindMap.Insert(KeyCode.KC_0,"KC_0");
		m_KeyBindMap.Insert(KeyCode.KC_MINUS,"KC_MINUS");
		m_KeyBindMap.Insert(KeyCode.KC_EQUALS,"KC_EQUALS");
		m_KeyBindMap.Insert(KeyCode.KC_BACK,"KC_BACK");
		m_KeyBindMap.Insert(KeyCode.KC_TAB,"KC_TAB");
		m_KeyBindMap.Insert(KeyCode.KC_Q,"KC_Q");
		m_KeyBindMap.Insert(KeyCode.KC_W,"KC_W");
		m_KeyBindMap.Insert(KeyCode.KC_E,"KC_E");
		m_KeyBindMap.Insert(KeyCode.KC_R,"KC_R");
		m_KeyBindMap.Insert(KeyCode.KC_T,"KC_T");
		m_KeyBindMap.Insert(KeyCode.KC_Y,"KC_Y");
		m_KeyBindMap.Insert(KeyCode.KC_U,"KC_U");
		m_KeyBindMap.Insert(KeyCode.KC_I,"KC_I");
		m_KeyBindMap.Insert(KeyCode.KC_O,"KC_O");
		m_KeyBindMap.Insert(KeyCode.KC_P,"KC_P");
		m_KeyBindMap.Insert(KeyCode.KC_LBRACKET,"KC_LBRACKET");
		m_KeyBindMap.Insert(KeyCode.KC_RBRACKET,"KC_RBRACKET");
		m_KeyBindMap.Insert(KeyCode.KC_RETURN,"KC_RETURN");
		m_KeyBindMap.Insert(KeyCode.KC_LCONTROL,"KC_LCONTROL");
		m_KeyBindMap.Insert(KeyCode.KC_A,"KC_A");
		m_KeyBindMap.Insert(KeyCode.KC_S,"KC_S");
		m_KeyBindMap.Insert(KeyCode.KC_D,"KC_D");
		m_KeyBindMap.Insert(KeyCode.KC_F,"KC_F");
		m_KeyBindMap.Insert(KeyCode.KC_G,"KC_G");
		m_KeyBindMap.Insert(KeyCode.KC_H,"KC_H");
		m_KeyBindMap.Insert(KeyCode.KC_J,"KC_J");
		m_KeyBindMap.Insert(KeyCode.KC_K,"KC_K");
		m_KeyBindMap.Insert(KeyCode.KC_L,"KC_L");
		m_KeyBindMap.Insert(KeyCode.KC_SEMICOLON,"KC_SEMICOLON");
		m_KeyBindMap.Insert(KeyCode.KC_APOSTROPHE,"KC_APOSTROPHE");
		m_KeyBindMap.Insert(KeyCode.KC_GRAVE,"KC_GRAVE");
		m_KeyBindMap.Insert(KeyCode.KC_LSHIFT,"KC_LSHIFT");
		m_KeyBindMap.Insert(KeyCode.KC_BACKSLASH,"KC_BACKSLASH");
		m_KeyBindMap.Insert(KeyCode.KC_Z,"KC_Z");
		m_KeyBindMap.Insert(KeyCode.KC_X,"KC_X");
		m_KeyBindMap.Insert(KeyCode.KC_C,"KC_C");
		m_KeyBindMap.Insert(KeyCode.KC_V,"KC_V");
		m_KeyBindMap.Insert(KeyCode.KC_B,"KC_B");
		m_KeyBindMap.Insert(KeyCode.KC_N,"KC_N");
		m_KeyBindMap.Insert(KeyCode.KC_M,"KC_M");
		m_KeyBindMap.Insert(KeyCode.KC_COMMA,"KC_COMMA");
		m_KeyBindMap.Insert(KeyCode.KC_PERIOD,"KC_PERIOD");
		m_KeyBindMap.Insert(KeyCode.KC_SLASH,"KC_SLASH");
		m_KeyBindMap.Insert(KeyCode.KC_RSHIFT,"KC_RSHIFT");
		m_KeyBindMap.Insert(KeyCode.KC_MULTIPLY,"KC_MULTIPLY");
		m_KeyBindMap.Insert(KeyCode.KC_LMENU,"KC_LMENU");
		m_KeyBindMap.Insert(KeyCode.KC_SPACE,"KC_SPACE");
		m_KeyBindMap.Insert(KeyCode.KC_CAPITAL,"KC_CAPITAL");
		m_KeyBindMap.Insert(KeyCode.KC_F1,"KC_F1");
		m_KeyBindMap.Insert(KeyCode.KC_F2,"KC_F2");
		m_KeyBindMap.Insert(KeyCode.KC_F3,"KC_F3");
		m_KeyBindMap.Insert(KeyCode.KC_F4,"KC_F4");
		m_KeyBindMap.Insert(KeyCode.KC_F5,"KC_F5");
		m_KeyBindMap.Insert(KeyCode.KC_F6,"KC_F6");
		m_KeyBindMap.Insert(KeyCode.KC_F7,"KC_F7");
		m_KeyBindMap.Insert(KeyCode.KC_F8,"KC_F8");
		m_KeyBindMap.Insert(KeyCode.KC_F9,"KC_F9");
		m_KeyBindMap.Insert(KeyCode.KC_F10,"KC_F10");
		m_KeyBindMap.Insert(KeyCode.KC_NUMLOCK,"KC_NUMLOCK");
		m_KeyBindMap.Insert(KeyCode.KC_SCROLL,"KC_SCROLL");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD7,"KC_NUMPAD7");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD8,"KC_NUMPAD8");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD9,"KC_NUMPAD9");
		m_KeyBindMap.Insert(KeyCode.KC_SUBTRACT,"KC_SUBTRACT");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD4,"KC_NUMPAD4");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD5,"KC_NUMPAD5");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD6,"KC_NUMPAD6");
		m_KeyBindMap.Insert(KeyCode.KC_ADD,"KC_ADD");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD1,"KC_NUMPAD1");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD2,"KC_NUMPAD2");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD3,"KC_NUMPAD3");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPAD0,"KC_NUMPAD0");
		m_KeyBindMap.Insert(KeyCode.KC_DECIMAL,"KC_DECIMAL");
		m_KeyBindMap.Insert(KeyCode.KC_OEM_102,"KC_OEM_102");
		m_KeyBindMap.Insert(KeyCode.KC_F11,"KC_F11");
		m_KeyBindMap.Insert(KeyCode.KC_F12,"KC_F12");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPADEQUALS,"KC_NUMPADEQUALS");
		m_KeyBindMap.Insert(KeyCode.KC_PREVTRACK,"KC_PREVTRACK");
		m_KeyBindMap.Insert(KeyCode.KC_AT,"KC_AT");
		m_KeyBindMap.Insert(KeyCode.KC_COLON,"KC_COLON");
		m_KeyBindMap.Insert(KeyCode.KC_UNDERLINE,"KC_UNDERLINE");
		m_KeyBindMap.Insert(KeyCode.KC_STOP,"KC_STOP");
		m_KeyBindMap.Insert(KeyCode.KC_AX,"KC_AX");
		m_KeyBindMap.Insert(KeyCode.KC_UNLABELED,"KC_UNLABELED");
		m_KeyBindMap.Insert(KeyCode.KC_NEXTTRACK,"KC_NEXTTRACK");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPADENTER,"KC_NUMPADENTER");
		m_KeyBindMap.Insert(KeyCode.KC_RCONTROL,"KC_RCONTROL");
		m_KeyBindMap.Insert(KeyCode.KC_MUTE,"KC_MUTE");
		m_KeyBindMap.Insert(KeyCode.KC_CALCULATOR,"KC_CALCULATOR");
		m_KeyBindMap.Insert(KeyCode.KC_PLAYPAUSE,"KC_PLAYPAUSE");
		m_KeyBindMap.Insert(KeyCode.KC_MEDIASTOP,"KC_MEDIASTOP");
		m_KeyBindMap.Insert(KeyCode.KC_VOLUMEDOWN,"KC_VOLUMEDOWN");
		m_KeyBindMap.Insert(KeyCode.KC_VOLUMEUP,"KC_VOLUMEUP");
		m_KeyBindMap.Insert(KeyCode.KC_WEBHOME,"KC_WEBHOME");
		m_KeyBindMap.Insert(KeyCode.KC_NUMPADCOMMA,"KC_NUMPADCOMMA");
		m_KeyBindMap.Insert(KeyCode.KC_DIVIDE,"KC_DIVIDE");
		m_KeyBindMap.Insert(KeyCode.KC_SYSRQ,"KC_SYSRQ");
		m_KeyBindMap.Insert(KeyCode.KC_RMENU,"KC_RMENU");
		m_KeyBindMap.Insert(KeyCode.KC_PAUSE,"KC_PAUSE");
		m_KeyBindMap.Insert(KeyCode.KC_HOME,"KC_HOME");
		m_KeyBindMap.Insert(KeyCode.KC_UP,"KC_UP");
		m_KeyBindMap.Insert(KeyCode.KC_PRIOR,"KC_PRIOR");
		m_KeyBindMap.Insert(KeyCode.KC_LEFT,"KC_LEFT");
		m_KeyBindMap.Insert(KeyCode.KC_RIGHT,"KC_RIGHT");
		m_KeyBindMap.Insert(KeyCode.KC_END,"KC_END");
		m_KeyBindMap.Insert(KeyCode.KC_DOWN,"KC_DOWN");
		m_KeyBindMap.Insert(KeyCode.KC_NEXT,"KC_NEXT");
		m_KeyBindMap.Insert(KeyCode.KC_INSERT,"KC_INSERT");
		m_KeyBindMap.Insert(KeyCode.KC_DELETE,"KC_DELETE");
		m_KeyBindMap.Insert(KeyCode.KC_LWIN,"KC_LWIN");
		m_KeyBindMap.Insert(KeyCode.KC_RWIN,"KC_RWIN");
		m_KeyBindMap.Insert(KeyCode.KC_APPS,"KC_APPS");
		m_KeyBindMap.Insert(KeyCode.KC_POWER,"KC_POWER");
		m_KeyBindMap.Insert(KeyCode.KC_SLEEP,"KC_SLEEP");
		m_KeyBindMap.Insert(KeyCode.KC_WAKE,"KC_WAKE");
		m_KeyBindMap.Insert(KeyCode.KC_MEDIASELECT,"KC_MEDIASELECT");*/
	}

	/*ref SPKeybindConfig getKeyBindConfig()
	{
		return m_SPKeybindConfig;
	}

	ref map<int,string> getKeyBindMap()
	{
		return m_KeyBindMap;
	}*/

	void DisplayPanel() {

		//GetRPCManager().SendRPC( "ServerPanelI", "RPC_ServerPanelMenu", new Param1< bool >( true ), true, NULL );
		/*UIManager UIMgr = GetGame().GetUIManager();
		UIMgr.ShowScriptedMenu( GetServerPanelMenu() , NULL )*/
	}
}

/*modded class LoadingScreen
{
	void LoadingScreen(DayZGame game)
	{
		m_ImageLogoMid.LoadImageFile( 0, "set:dayz_gui_vpp image:vpp_white" );
		m_ImageLogoCorner.LoadImageFile( 0, "set:dayz_gui_vpp image:vpp_white" );
	}
}*/
