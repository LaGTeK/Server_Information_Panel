class ServerPanelMenu extends UIScriptedMenu {
	PlayerBase Player;
	private Widget m_WidgetRoot;
	private ButtonWidget m_BtnCancel, m_BtnRight, m_BtnLeft, m_BtnClose, m_BtnDonate, m_btnDescription, m_btnRules, m_btnTabTitle0, m_btnTabTitle1, m_btnTabTitle2, m_btnTabTitle3;
	private TextListboxWidget m_PlayersList, m_DescriptionList, m_RulesList, m_Tab2List, m_Tab3List;
	private MultilineTextWidget m_ServerName;
	private ImageWidget m_ImagePlayerInfo, m_IconHealth, m_IconBlood, m_IconWater, m_IconFood;
	private TextWidget m_TitlePanel, m_PlayerTitle, m_TextPlayerNickname, m_PlayTime, m_TextPlayerBlood, m_TextPlayerHealth, m_TextPlayerWater, m_TextPlayerEnergy, m_TextPlayerPos;
	private string m_Link1, m_Link2, m_Link3, m_Tab1name, m_Tab2name, m_Tab3name, m_Tab4name;
	private int SPMENUKEY;

	// Colors
	private const int 					WHITE			= ARGB(255, 255, 255, 255);
	private const int 					ORANGE			= ARGB(255, 255, 165, 0);
	private const int 					GREEN			= ARGB(255, 0, 206, 0);
	private const int 					RED				= ARGB(255, 255, 0, 0);
	private const int 					YELLOW			= ARGB(255, 255, 255, 0);
	protected bool m_IsVisible = false;

	void ServerPanelMenu()	{	
		
	}

	void ~ServerPanelMenu()	{	
	}

	override Widget Init()	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "ServerPanel/scripts/5_Mission/gui/layouts/ServerPanel.layout" );

		m_TitlePanel 		= TextWidget.Cast( layoutRoot.FindAnyWidget( "title_text" ) );
		m_BtnDonate	 		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_donate" ) );
		m_BtnRight	 		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_discord" ) );
		m_BtnLeft	 		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_website" ) );
		m_BtnCancel	 		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_cancel" ) );
		m_BtnClose	 		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_close_widget" ) );


		//Player Information
		m_ImagePlayerInfo 	= ImageWidget.Cast( layoutRoot.FindAnyWidget( "ImagePlayerInfo" ) );
		m_IconHealth 		= ImageWidget.Cast( layoutRoot.FindAnyWidget( "IconHealth" ) );
		m_IconBlood 		= ImageWidget.Cast( layoutRoot.FindAnyWidget( "IconBlood" ) );
		m_IconWater 		= ImageWidget.Cast( layoutRoot.FindAnyWidget( "IconWater" ) );
		m_IconFood 			= ImageWidget.Cast( layoutRoot.FindAnyWidget( "IconFood" ) );
		m_PlayerTitle 		= TextWidget.Cast( layoutRoot.FindAnyWidget( "OnlinePlayerTitle" ) );
		m_TextPlayerNickname= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_Nickname" ) );
		m_TextPlayerBlood 	= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_blood" ) );
		m_TextPlayerHealth 	= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_health" ) );
		m_TextPlayerWater 	= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_water" ) );
		m_TextPlayerEnergy 	= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_food" ) );
		m_TextPlayerPos 	= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_position" ) );
		m_PlayTime 			= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_playtime" ) );
		m_PlayersList 		= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Player_List" ) );

		//Tab
		m_btnTabTitle0		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_0" ) );
		m_btnTabTitle1 		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_1" ) );
		m_btnTabTitle2		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_2" ) );
		m_btnTabTitle3 		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_3" ) );

		m_ServerName 		= MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "text_name" ) );
		m_DescriptionList 	= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Tab_0" ) );
		m_RulesList 		= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Tab_1" ) );
		m_Tab2List 			= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Tab_2" ) );
		m_Tab3List 			= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Tab_3" ) );

		m_DescriptionList.Show(true);
		m_RulesList.Show(false);
		m_Tab2List.Show(false);
		m_Tab3List.Show(false);
		m_ImagePlayerInfo.Show(false);

		m_TitlePanel.SetText( "Server Panel Information by LaGTeK" + " | " + GetDate());

		return layoutRoot;
	}

	override void OnShow()	{
		super.OnShow();

		PPEffects.SetBlurMenu(0.5);

		GetGame().GetInput().ChangeGameFocus(1);

		GetGame().GetMission().PlayerControlEnable();

		GetRPCManager().SendRPC( "ServerPanelI", "SyncConfigRequest", new Param1< int >( 0 ), true, NULL );
		GetRPCManager().SendRPC( "ServerPanelI", "SyncTabsRequest", new Param1< int >( 0 ), true, NULL );
		GetRPCManager().SendRPC( "ServerPanelI", "SyncPlayersRequest", new Param1< int >( 0 ), true, NULL );
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

	void SyncConfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param2<ref TStringArray, int> syncConfig;
		ref TStringArray sPanelConfig;
		string sBtn1name, sBtn1link, sBtn2name, sBtn2link, sBtn3name, sBtn3link, sServerName, sTab0name, sTab1name, sTab2name, sTab3name;
		int sPlayerInfo;

		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( syncConfig ) ) {
				ServerPanelBase.Log("ServerPanelFile", "Config sync files read error - possible version mismatch");
				return;
			}
			sPanelConfig 	= syncConfig.param1;
			sPlayerInfo 	= syncConfig.param2;

		}

		sBtn1name 	= sPanelConfig[0];
		sBtn1link 	= sPanelConfig[1];
		sBtn2name 	= sPanelConfig[2];
		sBtn2link 	= sPanelConfig[3];
		sBtn3name 	= sPanelConfig[4];
		sBtn3link 	= sPanelConfig[5];
		sServerName = sPanelConfig[6];
		sTab0name 	= sPanelConfig[7];
		sTab1name 	= sPanelConfig[8];
		sTab2name 	= sPanelConfig[9];
		sTab3name 	= sPanelConfig[10];

		m_Link1 	= sBtn1link;
		m_Link2 	= sBtn2link;
		m_Link3 	= sBtn3link;
		m_Tab1name 	= sTab0name;
		m_Tab2name 	= sTab1name;
		m_Tab3name 	= sTab2name;
		m_Tab4name 	= sTab3name;

		if (layoutRoot.IsVisible()) {
			m_ServerName.SetText(sServerName);

			if (sPlayerInfo == 0)	{
				m_ImagePlayerInfo.Show(true);
				m_PlayerTitle.Show(false);
				m_TextPlayerBlood.Show(false);
				m_TextPlayerHealth.Show(false);
				m_TextPlayerPos.Show(false);
				m_PlayersList.Show(false);
			}
			if (m_Tab1name != "") {
				m_btnTabTitle0.SetText(m_Tab1name);
				m_btnTabTitle0.Show(true);
			}
			else{
				m_btnTabTitle0.Show(false);
			}
			if (m_Tab2name != "") {
				m_btnTabTitle1.SetText(m_Tab2name);
				m_btnTabTitle1.Show(true);
			}
			else{
				m_btnTabTitle1.Show(false);
			}
			if (m_Tab3name != "") {
				m_btnTabTitle2.SetText(m_Tab3name);
				m_btnTabTitle2.Show(true);
			}
			else{
				m_btnTabTitle2.Show(false);
			}
			if (m_Tab4name != "") {
				m_btnTabTitle3.SetText(m_Tab4name);
				m_btnTabTitle3.Show(true);
			}
			else{
				m_btnTabTitle3.Show(false);
			}
			if (m_Link1 != "" && sBtn1name != "") {
				m_BtnRight.SetText(sBtn1name);
				m_BtnRight.Show(true);
			}
			else{
				m_BtnRight.Show(false);
			}
			if (m_Link2 != "" && sBtn2name != "") {
				m_BtnLeft.SetText(sBtn2name);
				m_BtnLeft.Show(true);
			}
			else{
				m_BtnLeft.Show(false);
			}
			if (m_Link3 != "" && sBtn3name != "") {
				m_BtnDonate.SetText(sBtn3name);
				m_BtnDonate.Show(true);
			}
			else{
				m_BtnDonate.Show(false);
			}
		}
	}

	void SyncTab( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param4<ref TStringArray, ref TStringArray, ref TStringArray, ref TStringArray> syncTabs;

		ref TStringArray ssServerDesc	= new TStringArray;
		ref TStringArray ssServerRules	= new TStringArray;
		ref TStringArray ssServerTab2	= new TStringArray;
		ref TStringArray ssServerTab3	= new TStringArray;

		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( syncTabs ) ) {
				ServerPanelBase.Log("ServerPanelFile", "Tab sync files read error - possible version mismatch");
				return;
			}
			ssServerDesc	= syncTabs.param1;
			ssServerRules	= syncTabs.param2;
			ssServerTab2	= syncTabs.param3;
			ssServerTab3	= syncTabs.param4;
		}

		int i;

		if (layoutRoot.IsVisible()) {
			for ( i = 0; i < ssServerDesc.Count(); ++i ) {
				m_DescriptionList.AddItem(ssServerDesc.Get(i), new Param1<string>(ssServerDesc.Get(i)), 0);
			}

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
		Param4<ref TStringArray, ref TIntArray, vector, TFloatArray> syncDataS;
		ref TStringArray playerListC;
		ref TIntArray playerDataC;
		ref TFloatArray playerDataF;
		int sUpTime = 0;
		int sHealth;
		int sBlood;
		float sEnergy;
		float sWater;

		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( syncDataS ) ) {
				ServerPanelBase.Log("SyncPlayer","Player sync data read error - possible version mismatch");
				return;
			}

			m_PlayersList.ClearItems();
			playerListC = syncDataS.param1;
			playerDataC = syncDataS.param2;
			playerDataF = syncDataS.param4;
			if (playerDataC.Count() == 0) return;

			sUpTime = Math.Round(playerDataC[0]/1000);
		}

		sHealth = playerDataC[2];
		sBlood 	= playerDataC[3];
		sEnergy = playerDataF[1];
		sWater 	= playerDataF[0];

		m_TextPlayerHealth.SetText(" " + sHealth.ToString());
		m_TextPlayerBlood.SetText(" " + sBlood.ToString());

		int y =1;
		for ( int i = 0; i < playerListC.Count(); ++i ) {
			m_PlayersList.AddItem(" " + y.ToString() + ": " + playerListC.Get(i), new Param1<string>(playerListC.Get(i)), 0);
			y++;
		}
		m_PlayTime.SetText(Math.Floor(sUpTime / 3600).ToString() + "h " + ((sUpTime / 60) % 60).ToString() + "min");
		m_PlayerTitle.SetText("Online Players: " + playerListC.Count());
		m_TextPlayerNickname.SetText(playerListC.Get(playerDataC[1]));
		vector playerPos = syncDataS.param3;
		//m_TextPlayerPos.SetText("Pos. X: " + Math.Floor(playerPos[0]).ToString() + "  Y: " + Math.Floor(playerPos[2]).ToString() + "  Alt: " + Math.Floor(playerPos[1]).ToString() + " m");
		m_TextPlayerPos.SetText("Pos. X: " + Math.Floor(playerPos[0]).ToString() + "  Y: " + Math.Floor(playerPos[2]).ToString());

		if (layoutRoot.IsVisible()) {
			if (sHealth <= 20)	{
				m_TextPlayerHealth.SetColor(RED);
			}
			if (sHealth <= 40 && sHealth > 20)	{
				m_TextPlayerHealth.SetColor(ORANGE);
			}
			if (sHealth <= 60 && sHealth > 40)	{
				m_TextPlayerHealth.SetColor(YELLOW);
			}
			if (sHealth > 60 && sHealth <= 90)	{
				m_TextPlayerHealth.SetColor(GREEN);
			}
			if (sHealth > 90)	{
				m_TextPlayerHealth.SetColor(WHITE);
			}
			
			if (sBlood <= 3000)		{
				m_TextPlayerBlood.SetColor(RED);
			}
			if (sBlood <= 3500 && sBlood > 3000)	{
				m_TextPlayerBlood.SetColor(ORANGE);
			}
			if (sBlood <= 4000 && sBlood > 3500)	{
				m_TextPlayerBlood.SetColor(YELLOW);
			}
			if (sBlood > 4000 && sBlood <= 4500)	{
				
				m_TextPlayerBlood.SetColor(GREEN);
			}
			if (sBlood >= 4500)	{
				m_TextPlayerBlood.SetColor(WHITE);
			}
			
			if (sEnergy <= 200)	{	
				m_TextPlayerEnergy.SetColor(RED);
				m_TextPlayerEnergy.SetText(" Starved !");
			}
			if (sEnergy <= 400 && sEnergy > 200)	{
				m_TextPlayerEnergy.SetColor(YELLOW);
				m_TextPlayerEnergy.SetText(" Feel Starved");
			}
			if (sEnergy > 400 && sEnergy <= 1000)	{
				m_TextPlayerEnergy.SetColor(WHITE);
				m_TextPlayerEnergy.SetText(" Good");
			}
			if (sEnergy > 1000)	{
				m_TextPlayerEnergy.SetColor(WHITE);
				m_TextPlayerEnergy.SetText(" Excellent");
			}
			
			if (sWater <= 300)	{
				m_TextPlayerWater.SetColor(RED);
				m_TextPlayerWater.SetText(" Thirsty !");
			}
			if (sWater <= 600 && sWater > 300)	{
				m_TextPlayerWater.SetColor(YELLOW);
				m_TextPlayerWater.SetText(" Feel Thirsty");
			}
			if (sWater > 600 && sWater <= 1000)	{
				//m_IconWater.SetColor(WHITE);
				m_TextPlayerWater.SetColor(WHITE);
				m_TextPlayerWater.SetText(" Good");
			}
			if (sWater > 1200)	{
				m_TextPlayerWater.SetColor(WHITE);
				m_TextPlayerWater.SetText(" Excellent");
			}
		}
	}

	void OnKeyPress( int key ) {
		UIManager UIMgr = GetGame().GetUIManager();
		if (key == ServerPanelBase.GetConfig().GetSPMenuKey()) {
			if (!UIMgr.IsMenuOpen(MENU_INGAME)) UIMgr.CloseAll();
			return;
		}
	}

	override bool OnClick( Widget w, int x, int y, int button )	{
		super.OnClick(w, x, y, button);

		if ( w == m_btnTabTitle0 )	{
			m_DescriptionList.Show(true);
			m_RulesList.Show(false);
			m_Tab2List.Show(false);
			m_Tab3List.Show(false);
			Print("CLICKED FIRST TAB");
			return true;
		}
		if ( w == m_btnTabTitle1 )	{
			m_DescriptionList.Show(false);
			m_RulesList.Show(true);
			m_Tab2List.Show(false);
			m_Tab3List.Show(false);
			Print("CLICKED SECOND TAB");
			return true;
		}
		if ( w == m_btnTabTitle2 )	{
			m_DescriptionList.Show(false);
			m_RulesList.Show(false);
			m_Tab2List.Show(true);
			m_Tab3List.Show(false);
			Print("CLICKED THIRD TAB");
			return true;
		}
		if ( w == m_btnTabTitle3 )	{
			m_DescriptionList.Show(false);
			m_RulesList.Show(false);
			m_Tab2List.Show(false);
			m_Tab3List.Show(true);
			Print("CLICKED FOURTH TAB");
			return true;
		}
		if ( w == m_BtnCancel || w == m_BtnClose)	{
			GetGame().GetUIManager().Back();
			return true;
		}
		if ( w == m_BtnRight )	{
			GetGame().OpenURL( m_Link1 );
			Print("CLICKED FIRST BUTTON");
			return true;
		}
		if ( w == m_BtnLeft )	{
			GetGame().OpenURL(m_Link2);
			Print("CLICKED SECOND BUTTON");
			return true;
		}
		if ( w == m_BtnDonate)	{
			GetGame().OpenURL(m_Link3);
			Print("CLICKED THIRD BUTTON");
			return true;
		}
		return false;
	}
}
