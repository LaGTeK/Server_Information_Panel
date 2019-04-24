class ServerPanelMenu extends UIScriptedMenu {
	PlayerBase Player;
	private Widget m_WidgetRoot;
	protected ButtonWidget m_BtnCancel, m_BtnRight, m_BtnLeft, m_BtnClose, m_BtnDonate, m_btnDescription, m_btnRules, m_btnTabTitle2, m_btnTabTitle3;
	protected TextListboxWidget m_PlayersList, m_DescriptionList, m_RulesList, m_Tab2List, m_Tab3List;
	protected MultilineTextWidget m_ServerName;
	protected ImageWidget m_ImagePlayerInfo;
	protected TextWidget m_TitlePanel, m_PlayerTitle, m_TextPlayerNickname, m_TextPlayerBlood, m_TextPlayerHealth, m_TextPlayerPos, m_tabTitle2, m_tabTitle3;
	private string m_Link1, m_Link2, m_Link3, m_Tab1name, m_Tab2name;
	private int SPMENUKEY;

	protected bool m_IsVisible = false;

	override Widget Init()	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "ServerPanel/scripts/5_Mission/gui/layouts/ServerPanel.layout" );

		m_TitlePanel = TextWidget.Cast( layoutRoot.FindAnyWidget( "title_text" ) );
		m_BtnDonate = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_donate" ) );
		m_BtnRight = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_discord" ) );
		m_BtnLeft = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_website" ) );
		m_BtnCancel = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_cancel" ) );
		m_BtnClose = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_close_widget" ) );


		//Player Information
		m_ImagePlayerInfo = ImageWidget.Cast( layoutRoot.FindAnyWidget( "ImagePlayerInfo" ) );
		m_PlayerTitle = TextWidget.Cast( layoutRoot.FindAnyWidget( "OnlinePlayerTitle" ) );
		m_TextPlayerNickname = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_Nickname" ) );
		m_TextPlayerBlood = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_health" ) );
		m_TextPlayerHealth = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_blood" ) );
		m_TextPlayerPos = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_position" ) );
		m_PlayersList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Player_List" ) );

		//Tab
		m_btnDescription = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_Description" ) );
		m_btnRules = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_Rules" ) );
		m_btnTabTitle2 = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_2" ) );
		m_btnTabTitle3 = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_3" ) );


		//HTML Element
		/*Class.CastTo(m_DescriptionList, layoutRoot.FindAnyWidget("Tab_0"));
		Class.CastTo(m_RulesList, layoutRoot.FindAnyWidget("Tab_1"));
		Class.CastTo(m_Tab2List, layoutRoot.FindAnyWidget("Tab_2"));
		Class.CastTo(m_Tab3List, layoutRoot.FindAnyWidget("Tab_3"));*/

		m_ServerName = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "text_name" ) );
		m_DescriptionList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Tab_0" ) );
		m_RulesList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Tab_1" ) );
		m_Tab2List = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Tab_2" ) );
		m_Tab3List = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Tab_3" ) );

		m_DescriptionList.Show(true);
		m_RulesList.Show(false);
		m_Tab2List.Show(false);
		m_Tab3List.Show(false);
		m_ImagePlayerInfo.Show(false);

		return layoutRoot;
	}

	void ServerPanelMenu()	{
		m_TitlePanel.SetText( "Server Panel Information by LaGTeK" + GetDate());
	}

	override void OnShow()	{
		super.OnShow();

		PPEffects.SetBlurMenu(0.5);

		GetGame().GetInput().ChangeGameFocus(1);

		GetGame().GetMission().PlayerControlEnable();
		
		//GetRPCManager().SendRPC( "ServerPanelI", "SyncMenuKeyRequest", new Param1< int >( 0 ), true, NULL );
		GetRPCManager().SendRPC( "ServerPanelI", "SyncSNameTabsRequest", new Param1< int >( 0 ), true, NULL );
		GetRPCManager().SendRPC( "ServerPanelI", "SyncPlayersRequest", new Param1< int >( 0 ), true, NULL );
		GetRPCManager().SendRPC( "ServerPanelI", "SyncButtonRequest", new Param1< int >( 0 ), true, NULL );
		GetRPCManager().SendRPC( "ServerPanelI", "SyncTabsRequest", new Param1< int >( 0 ), true, NULL );

		//PlayerBase player = GetGame().GetPlayer();
	}

	override void OnHide()	{
		super.OnHide();

		PPEffects.SetBlurMenu(0);

		GetGame().GetInput().ResetGameFocus();
	}

	static private string GetDate() {
		int year, month, day, hour, minute, second;

		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);

		string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);

		return date;
	}

	/*void SyncKey( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param1<int> SyncKey;
		int SPMenuKey;

		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( SyncKey ) ) {
				ServerPanelBase.Log("ServerPanelFile", "Name sync files read error - possible version mismatch");
				return;
			}
			SPMenuKey = SyncKey.param1;

		}
		SPMENUKEY = SPMenuKey;

		ServerPanelBase.Log("ServerPanelFile: SPMENUKEY = ", SPMENUKEY.ToString());
	}*/

	void SyncButtons( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param6<string, string, string, string, string, string> syncConfig;

		string sbtn1name;
		string sbtn1link;
		string sbtn2name;
		string sbtn2link;
		string sbtn3name;
		string sbtn3link;


		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( syncConfig ) ) {
				ServerPanelBase.Log("ServerPanelFile", "config sync files read error - possible version mismatch");
				return;
			}
			sbtn1name = syncConfig.param1;
			sbtn1link = syncConfig.param2;
			sbtn2name = syncConfig.param3;
			sbtn2link = syncConfig.param4;
			sbtn3name = syncConfig.param5;
			sbtn3link = syncConfig.param6;

		}
		m_Link1 = sbtn1link;
		m_Link2 = sbtn2link;
		m_Link3 = sbtn3link;

		if (layoutRoot.IsVisible()) {

			if (m_Link1 != "" && sbtn1name != "") {
				m_BtnRight.SetText(sbtn1name);
				m_BtnRight.Show(true);
			}
			else{
				m_BtnRight.Show(false);
			}
			if (m_Link2 != "" && sbtn2name != "") {
				m_BtnLeft.SetText(sbtn2name);
				m_BtnLeft.Show(true);
			}
			else{
				m_BtnLeft.Show(false);
			}
			if (m_Link3 != "" && sbtn3name != "") {
				m_BtnDonate.SetText(sbtn3name);
				m_BtnDonate.Show(true);
			}
			else{
				m_BtnDonate.Show(false);
			}
		}
	}

	void SyncSNameTabs( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param4<string, string, string, int> SyncSNameTabS;
		string sServerName;
		string sTab1name;
		string sTab2name;
		int splayerInfo;
		int SPMenuKey;


		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( SyncSNameTabS ) ) {
				ServerPanelBase.Log("ServerPanelFile", "Name sync files read error - possible version mismatch");
				return;
			}
			sServerName = SyncSNameTabS.param1;
			sTab1name = SyncSNameTabS.param2;
			sTab2name = SyncSNameTabS.param3;
			splayerInfo = SyncSNameTabS.param4;

		}
		m_Tab1name = sTab1name;
		m_Tab2name = sTab2name;


		if (layoutRoot.IsVisible()) {
			m_ServerName.SetText(sServerName);

			if (splayerInfo == 0)
			{
				m_ImagePlayerInfo.Show(true);
				m_PlayerTitle.Show(false);
				m_TextPlayerBlood.Show(false);
				m_TextPlayerHealth.Show(false);
				m_TextPlayerPos.Show(false);
				m_PlayersList.Show(false);
			}

			if (m_Tab2name != "") {
				m_tabTitle3.SetText(m_Tab2name);
				m_btnTabTitle3.SetText(m_Tab2name);
				m_btnTabTitle3.Show(true);
			}
			else{
				m_btnTabTitle3.Show(false);
			}
			if (m_Tab1name != "") {
				m_tabTitle2.SetText(m_Tab1name);
				m_btnTabTitle2.SetText(m_Tab1name);
				m_btnTabTitle2.Show(true);
			}
			else{
				m_btnTabTitle2.Show(false);
			}
		}
	}

	void SyncTab( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param4<ref TStringArray, ref TStringArray, ref TStringArray, ref TStringArray> syncTabs;

		ref TStringArray ssServerDesc = new TStringArray;
		ref TStringArray ssServerRules = new TStringArray;
		ref TStringArray ssServerTab2 = new TStringArray;
		ref TStringArray ssServerTab3 = new TStringArray;

		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( syncTabs ) ) {
				ServerPanelBase.Log("ServerPanelFile", "Tab sync files read error - possible version mismatch");
				return;
			}
			ssServerDesc = syncTabs.param1;
			ssServerRules = syncTabs.param2;
			ssServerTab2 = syncTabs.param3;
			ssServerTab3 = syncTabs.param4;
		}

		//ref TStringArray sTest = new TStringArray;
		int i;

		if (layoutRoot.IsVisible()) {
			//m_DescriptionList.SetText( new Param1<string>(ssServerDesc));
			for ( i = 0; i < ssServerDesc.Count(); ++i ) {
				m_DescriptionList.AddItem(ssServerDesc.Get(i), new Param1<string>(ssServerDesc.Get(i)), 0);
				//sTest.Insert(ssServerDesc.Get(i));
			}
			//m_DescriptionList.SetText(sTest.ToString());

			for ( i = 0; i < ssServerRules.Count(); ++i ) {
				m_RulesList.AddItem(ssServerRules.Get(i), new Param1<string>(ssServerRules.Get(i)), 0);
			}
			for ( i = 0; i < ssServerTab2.Count(); ++i ) {
				m_Tab2List.AddItem(ssServerTab2.Get(i), new Param1<string>(ssServerTab2.Get(i)), 0);
			}
			for ( i = 0; i < ssServerTab3.Count(); ++i ) {
				m_Tab3List.AddItem(ssServerTab3.Get(i), new Param1<string>(ssServerTab3.Get(i)), 0);
			}
		}
	}

	void SyncPlayers( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param3<ref TStringArray, ref TIntArray, vector> syncDataS;
		ref TStringArray playerListC;
		ref TIntArray playerDataC;
		int sUpTime = 0;

		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( syncDataS ) ) {
				ServerPanelBase.Log("SyncPlayer","Player sync data read error - possible version mismatch");
				return;
			}

			m_PlayersList.ClearItems();
			playerListC = syncDataS.param1;
			playerDataC = syncDataS.param2;
			if (playerDataC.Count() == 0) return;

			sUpTime = Math.Round(playerDataC[0]/1000);
		}

		if (layoutRoot.IsVisible()) {
			int y =1;
			for ( int i = 0; i < playerListC.Count(); ++i ) {
				m_PlayersList.AddItem(" " + y.ToString() + ": " + playerListC.Get(i), new Param1<string>(playerListC.Get(i)), 0);
				y++;
			}
			m_PlayerTitle.SetText("Online Players: " + playerListC.Count());
			m_TextPlayerNickname.SetText(playerListC.Get(playerDataC[1]));
			vector playerPos = syncDataS.param3;
			m_TextPlayerPos.SetText("X: " + Math.Floor(playerPos[0]).ToString() + "  Y: " + Math.Floor(playerPos[2]).ToString());
			m_TextPlayerHealth.SetText(playerDataC[3].ToString());
			m_TextPlayerBlood.SetText(playerDataC[2].ToString());
		}
	}

	void OnKeyPress( int key ) {
		UIManager UIMgr = GetGame().GetUIManager();
		if (key == ServerPanelBase.GetConfig().GetSPMenuKey()) {
			if (!UIMgr.IsMenuOpen(MENU_INGAME)) UIMgr.CloseAll();
			return;
		}
	}

	/*void OnKeyPress( int key ) {
		UIManager UIMgr = GetGame().GetUIManager();
		if (key == SPMENUKEY) {
			if (!UIMgr.IsMenuOpen(MENU_INGAME)) UIMgr.CloseAll();
			return;
		}
	}*/

	override bool OnClick( Widget w, int x, int y, int button )	{
		super.OnClick(w, x, y, button);

		if ( w == m_btnDescription )
		{
			m_DescriptionList.Show(true);
			m_RulesList.Show(false);
			m_Tab2List.Show(false);
			m_Tab3List.Show(false);
			Print("CLICKED FIRST TAB");
			return true;
		}
		if ( w == m_btnRules )
		{
			m_DescriptionList.Show(false);
			m_RulesList.Show(true);
			m_Tab2List.Show(false);
			m_Tab3List.Show(false);
			Print("CLICKED SECOND TAB");
			return true;
		}
		if ( w == m_btnTabTitle2 )
		{
			m_DescriptionList.Show(false);
			m_RulesList.Show(false);
			m_Tab2List.Show(true);
			m_Tab3List.Show(false);
			Print("CLICKED THIRD TAB");
			return true;
		}
		if ( w == m_btnTabTitle3 )
		{
			m_DescriptionList.Show(false);
			m_RulesList.Show(false);
			m_Tab2List.Show(false);
			m_Tab3List.Show(true);
			Print("CLICKED FOURTH TAB");
			return true;
		}
		if ( w == m_BtnCancel || w == m_BtnClose)
		{
			GetGame().GetUIManager().Back();
			return true;
		}
		if ( w == m_BtnRight )
		{
			GetGame().OpenURL( m_Link1 );
			Print("CLICKED FIRST BUTTON");
			return true;
		}
		if ( w == m_BtnLeft )
		{
			GetGame().OpenURL(m_Link2);
			Print("CLICKED SECOND BUTTON");
			return true;
		}
		if ( w == m_BtnDonate)
		{
			GetGame().OpenURL(m_Link3);
			Print("CLICKED THIRD BUTTON");
			return true;
		}
		return false;
	}
}
