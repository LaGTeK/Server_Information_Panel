class ServerPanelMenu extends UIScriptedMenu {
	PlayerBase Player;

	private Widget 								m_WidgetRoot;

	private Widget								m_PanelTabs;
	private Widget								m_PlayerInfo;

	//Tabs
	private Widget 								m_Tab0;
	private Widget 								m_Tab1;
	private Widget 								m_Tab2;
	private Widget 								m_Tab3;
	private Widget 								m_Tab4;

	//Current Tab
	Widget 										m_CurrentTabPanel;
	ServerPanelTab 								m_CurrentTab;

	//Buttons Tab
	private ButtonWidget 						m_btnTabTitle0;
	private ButtonWidget 						m_btnTabTitle1;
	private ButtonWidget 						m_btnTabTitle2;
	private ButtonWidget 						m_btnTabTitle3;
	private ButtonWidget 						m_btnTabTitle4;

	//Buttons
	private ButtonWidget 						m_BtnCancel;
	private ButtonWidget 						m_BtnRight;
	private ButtonWidget 						m_BtnLeft;
	private ButtonWidget 						m_BtnClose;
	private ButtonWidget 						m_BtnDonate;
	private ButtonWidget 						m_btnDescription;
	private ButtonWidget 						m_btnRules;
	

	private MultilineTextWidget 				m_ServerName;

	protected TextWidget 						m_Sex;
	protected TextWidget 						m_Weight;
	protected TextWidget 						m_BloodType;
	protected TextWidget 						m_SurvivalTime;
	protected TextWidget 						m_DistanceTravelled;
	protected TextWidget 						m_TitlePanel;
	protected TextWidget 						m_PlayerTitle;
	protected TextWidget 						m_TextPlayerNickname;
	protected TextWidget 						m_PlayTime;
	protected TextWidget 						m_TextPlayerBlood;
	protected TextWidget 						m_TextPlayerHealth;
	protected TextWidget 						m_TextPlayerWater;
	protected TextWidget 						m_TextPlayerEnergy;
	protected TextWidget 						m_TextPlayerPos;
	protected TextWidget 						m_ItemHands;
	protected TextWidget 						m_ServerTime;
	protected TextWidget 						m_Condition;
	protected TextWidget 						m_Direction;
	protected TextWidget 						m_ZKilled;
	protected TextWidget 						m_PKilled;

	protected ImageWidget 						m_ImgNight;
	protected ImageWidget 						m_ImgSun;
	protected ImageWidget 						m_ImgCloud;
	protected ImageWidget 						m_ImgStorm;
	protected ImageWidget 						m_ImgRain;
	protected ImageWidget 						m_ImgFog;
	protected ImageWidget 						m_ImgWind;

	protected ProgressBarWidget					m_HealthBar;
	protected ProgressBarWidget					m_BloodBar;
	protected ProgressBarWidget					m_ShockBar;
	protected ProgressBarWidget					m_StaminaBar;

	//Player Preview
	protected PlayerPreviewWidget				m_PlayerPreview;

	//Item Preview
	protected ItemPreviewWidget					m_ItemPreview;

	private TextListboxWidget 					m_PlayersList;
	private TextListboxWidget 					m_Tab0List;
	private TextListboxWidget 					m_Tab1List;
	private TextListboxWidget 					m_Tab2List;
	private TextListboxWidget 					m_Tab3List;

	private string m_Link1, m_Link2, m_Link3, m_Tab0name, m_Tab1name, m_Tab2name, m_Tab3name;
	private int SPMENUKEY;

	//Player Preview
	protected vector m_CharacterOrientation;
	protected int m_CharacterRotationX;
	protected int m_CharacterRotationY;

	// Colors
	private const int 					WHITE			= ARGB(255, 255, 255, 255);
	private const int 					ORANGE			= ARGB(255, 255, 165, 0);
	private const int 					GREEN			= ARGB(255, 0, 206, 0);
	private const int 					RED				= ARGB(255, 255, 0, 0);
	private const int 					YELLOW			= ARGB(255, 255, 255, 0);

	//Transition
	int currentTransitionStep;
	float centerX, leftX;
	bool Transitioning = false;
	const int TRANSITION_ANIMATION_STEPS = 40;
	const float TAB_OFFSET = 0.05;


	void ServerPanelMenu()	{
		//GetRPCManager().AddRPC( "ServerPanelI", "SyncConfig", this, SingeplayerExecutionType.Server );
		//GetRPCManager().AddRPC( "ServerPanelI", "SyncTab", this, SingeplayerExecutionType.Server );
		//GetRPCManager().AddRPC( "ServerPanelI", "SyncPlayers", this, SingeplayerExecutionType.Server );
		
	}

	void ~ServerPanelMenu()	{	
	}

	override Widget Init()	{
		layoutRoot 						= GetGame().GetWorkspace().CreateWidgets( "ServerPanel/scripts/gui/layouts/ServerPanel.layout" );
		layoutRoot.Show(false);

		WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( layoutRoot.FindAnyWidget( "PlayerPreview" ),  this, "MouseButtonDown" );
		
		m_PlayerInfo					= Widget.Cast(layoutRoot.FindAnyWidget("PanelPlayerInformation"));

		m_PanelTabs						= Widget.Cast(layoutRoot.FindAnyWidget("PanelTabs"));

		m_TitlePanel 					= TextWidget.Cast( layoutRoot.FindAnyWidget( "title_text" ) );

		m_ServerName 					= MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "text_name" ) );

		m_BtnDonate	 					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_donate" ) );
		m_BtnRight	 					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_discord" ) );
		m_BtnLeft	 					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_website" ) );
		m_BtnCancel	 					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_cancel" ) );
		m_BtnClose	 					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_close_widget" ) );

		//BtnTab
		m_btnTabTitle0					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_0" ) );
		m_btnTabTitle1 					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_1" ) );
		m_btnTabTitle2					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_2" ) );
		m_btnTabTitle3					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_3" ) );
		m_btnTabTitle4 					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_4" ) );

		//Tabs
		m_Tab0							= Widget.Cast(layoutRoot.FindAnyWidget("Tab_0"));
		m_Tab1							= Widget.Cast(layoutRoot.FindAnyWidget("Tab_1"));
		m_Tab2							= Widget.Cast(layoutRoot.FindAnyWidget("Tab_2"));
		m_Tab3							= Widget.Cast(layoutRoot.FindAnyWidget("Tab_3"));		
		m_Tab4							= Widget.Cast(layoutRoot.FindAnyWidget("Tab_4"));

		m_Tab0List 						= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "ListBox_Tab0" ) );
		m_Tab1List 						= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "ListBox_Tab1" ) );
		m_Tab2List 						= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "ListBox_Tab2" ) );
		m_Tab3List 						= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "ListBox_Tab3" ) );

		//Player Information
		m_PlayerTitle 					= TextWidget.Cast( layoutRoot.FindAnyWidget( "OnlinePlayerTitle" ) );
		m_TextPlayerNickname			= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_Nickname" ) );
		m_TextPlayerBlood 				= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_blood" ) );
		m_TextPlayerHealth 				= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_health" ) );
		m_TextPlayerWater 				= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_water" ) );
		m_TextPlayerEnergy 				= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_food" ) );
		m_TextPlayerPos 				= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_position" ) );
		m_ItemHands						= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_itemhands" ) );
		m_Sex							= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_sex" ) );
		m_Weight 						= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_weight" ) );
		m_BloodType						= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_bloodtype" ) );
		m_PlayTime 						= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_playtime" ) );
		m_ServerTime					= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_sTime" ) );
		m_Condition 					= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_disease" ) );
		m_SurvivalTime 					= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_survivaltime" ) );
		m_DistanceTravelled 			= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_distance" ) );
		m_Direction						= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_direction" ) );
		//m_ZKilled						= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_zKilled" ) );
		//m_PKilled						= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_pKilled" ) );

		//ProgressBar
		m_HealthBar 					= ProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "HealthBar" ) );
		m_BloodBar 						= ProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "BloodBar" ) );
		m_ShockBar 						= ProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "ShockBar" ) );
		m_StaminaBar 					= ProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "StaminaBar" ) );

		m_PlayersList 					= TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "Player_List" ) );

		//Preview Widget
		m_PlayerPreview 				= PlayerPreviewWidget.Cast( layoutRoot.FindAnyWidget( "PlayerPreview" ) );
		m_ItemPreview					= ItemPreviewWidget.Cast( layoutRoot.FindAnyWidget( "ItemPreview" ) );

		m_CurrentTab = ServerPanelTab.Tab0;
		m_CurrentTabPanel = m_Tab0;

		float x, y, w, h;
		m_CurrentTabPanel.GetPos(x, y);
		m_CurrentTabPanel.GetSize(w, h);

		centerX = x;

		float neededX = (x - w) - TAB_OFFSET;
		leftX = neededX;
		m_Tab1.SetPos(neededX, y, true);
		m_Tab2.SetPos(neededX, y, true);
		m_Tab3.SetPos(neededX, y, true);
		m_Tab4.SetPos(neededX, y, true);

		int shour, sminute, ssecond, syear, smonth, sday;
		GetHourMinuteSecond(shour, sminute, ssecond);
		GetYearMonthDay(syear, smonth, sday);
		string header = "Server Panel Information by LaGTeK | " + sday + "/" + smonth + "/" + syear + " | " + shour + ":" + sminute + ":" + ssecond;
		m_TitlePanel.SetText(header);

		SPBloodName();
		SPServerDate();
		SPGetDirection();

		return layoutRoot;
	}

	void Show()
	{
		SetFocus(NULL);
		layoutRoot.Show(true);

		OnShow();
	}

	void Hide()
	{
		SetFocus(NULL);
		OnHide();
		layoutRoot.Show(false);
	}

	override void OnShow()	{

		GetRPCManager().SendRPC( "ServerPanelI", "SyncConfigRequest", new Param1< int >( 0 ), true, NULL );
		GetRPCManager().SendRPC( "ServerPanelI", "SyncTabsRequest", new Param1< int >( 0 ), true, NULL );
		GetRPCManager().SendRPC( "ServerPanelI", "SyncPlayersRequest", new Param1< int >( 0 ), true, NULL );

		PPEffects.SetBlurMenu(0.5);
		GetGame().GetInput().ChangeGameFocus(1);
		GetGame().GetUIManager().ShowUICursor(true);
		GetGame().GetMission().GetHud().Show(false);
		GetGame().GetMission().PlayerControlEnable();

		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(UpdateHeader, 1000, true);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(SPServerDate, 1000, true );
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(SPGetDirection, 1000, false );
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(SPCalculatePlayerLoad, 500, false );
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(SPGender, 500, false );
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(SPPlayerPreview, 500, false );
		
		
	}

	override void OnHide()	{
		//super.OnHide();
		//m_ServerPanelMenu = NULL;

		PPEffects.SetBlurMenu(0);
		GetGame().GetUIManager().ShowUICursor(false);
		GetGame().GetMission().GetHud().Show(true);

		GetGame().GetInput().ResetGameFocus();

		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(UpdateHeader);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(SPCalculatePlayerLoad);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(SPGetDirection);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(SPGender);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(SPPlayerPreview);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(SPServerDate);
	}

	void SPGetDirection ()	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player)	{
			vector playerOrientation = player.GetOrientation();
			//float position = playerOrientation[0] / -180;
			float position = playerOrientation[0]/-180;

			m_Direction.SetText(position.ToString());

			if (position > -0.875 && position <= -0.625)m_Direction.SetText("South East");
			if (position > -0.625 && position <= -0.375)m_Direction.SetText("East");
			if (position > -0.375 && position <= -0.125)m_Direction.SetText("North East");
			if (position > -0.125 && position <= 0.125)m_Direction.SetText("North");
			if (position > 0.125  && position <= 0.375)m_Direction.SetText("North West");
			if (position > 0.375  && position <= 0.625)m_Direction.SetText("West");
			if (position > 0.625  && position <= 0.875)m_Direction.SetText("South West");
			if (position > 0.875  || position <= -0.875)m_Direction.SetText("South");
		}
	}

	void SPItemPreview()	{
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())	{
			if (Player.GetItemInHands()) m_ItemPreview.SetItem(Player.GetItemInHands());
		}
	}

	void SPServerDate()	{
		private int		sOrigYear;
		private int		sOrigMonth;
		private int		sOrigDay;
		private int		sOrigHour;
		private int		sOrigMinute;

		if(GetGame().IsClient() || !GetGame().IsMultiplayer())	{
			GetGame().GetWorld().GetDate( sOrigDay, sOrigMonth, sOrigDay, sOrigHour, sOrigMinute );
			m_ServerTime.SetText("" + sOrigDay + "/" + sOrigMonth + "/" + sOrigDay + " | " + sOrigHour + ":" + sOrigMinute);
		}
	}
	void SPPlayerPreview()	{
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())	{
			m_PlayerPreview.SetPlayer( GetGame().GetPlayer() );
			m_PlayerPreview.SetModelPosition( "0 0 0.605" );
			//m_PlayerPreview.SetSize( 1.34, 1.34 );

			// item in hands update
			m_PlayerPreview.UpdateItemInHands(GetGame().GetPlayer().GetHumanInventory().GetEntityInHands());
			
			PlayerBase realPlayer = PlayerBase.Cast(GetGame().GetPlayer());
			DayZPlayer dummyPlayer = m_PlayerPreview.GetDummyPlayer();
			if( realPlayer && dummyPlayer )	{
				// injury animation update
				HumanCommandAdditives hca = dummyPlayer.GetCommandModifier_Additives();
				if( hca && realPlayer.m_InjuryHandler )
					hca.SetInjured(realPlayer.m_InjuryHandler.GetInjuryAnimValue(), realPlayer.m_InjuryHandler.IsInjuryAnimEnabled());
			}
		}
	}
	void UpdateRotation( int mouse_x, int mouse_y, bool is_dragging )	{
		vector orientation = m_CharacterOrientation;
		orientation[1] = orientation[1] - ( m_CharacterRotationX - mouse_x );
		m_PlayerPreview.SetModelOrientation( orientation );

		if ( !is_dragging )
		{	
			m_CharacterOrientation = orientation;
		}
	}
	bool MouseButtonDown()	{
		g_Game.GetMousePos( m_CharacterRotationX, m_CharacterRotationY );
		GetGame().GetDragQueue().Call( this, "UpdateRotation" );
		return true;
	}
	void UpdateHeader()	{
		int hour, minute, second, year, month, day;
		GetHourMinuteSecond(hour, minute, second);
		GetYearMonthDay(year, month, day);
		string header = "Server Panel Information by LaGTeK | " + day + "/" + month + "/" + year + " | " + hour + ":" + minute + ":" + second;
		m_TitlePanel.SetText(header);
	}
	void SPGender()	{
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())	{
			if (Player){
				if (Player.IsMale() )	m_Sex.SetText("Man");
				else	m_Sex.SetText("Woman");
			}
		}
	}
	void SPCalculatePlayerLoad()	{
		EntityAI attachment;
		ItemBase itemHands;
		
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())	{
			itemHands			= Player.GetItemInHands();
			int attcount		= Player.GetInventory().AttachmentCount();
			int total_load		= 0;
			
			for (int att = 0; att < attcount; att++)	{	
				attachment = Player.GetInventory().GetAttachmentFromIndex(att);
				if ( attachment.IsItemBase() )	{
					ItemBase attachmentIB;
					Class.CastTo(attachmentIB, attachment);
					total_load += attachmentIB.GetItemWeight();
				}
			}

			if ( itemHands ) // adds weight of item carried in hands
				total_load += itemHands.GetItemWeight();

			//int a1 = sDistance / 10;
			float totalWeight = (float) total_load / 1000.0;

			m_Weight.SetText("" + totalWeight + " Kg");
		}
	}
	void SPBloodName()	{
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())	{
			Class.CastTo(Player, GetGame().GetPlayer() );
			
			if( Player )	{
				string blood_name;
				bool positive;
				BloodTypes.GetBloodTypeName( Player.GetBloodType(), blood_name, positive );
				bool blood_type_visible = Player.HasBloodTypeVisible();
				
				if( blood_type_visible )	{
					if( positive )
						m_BloodType.SetText( blood_name + "+");
					else
						m_BloodType.SetText( blood_name + "-");
				}
				else	{
					m_BloodType.SetText( "Unknown" );
				}
			}
		}
	}

	void SyncConfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param2<ref TStringArray, ref TBoolArray> syncConfig;
		ref TStringArray sPanelConfig;
		ref TBoolArray sConfigBool
		string sBtn1name, sBtn1link, sBtn2name, sBtn2link, sBtn3name, sBtn3link, sServerName, sTab0name, sTab1name, sTab2name, sTab3name;
		bool sPlayerInfo;
		bool sPlayerTab;

		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( syncConfig ) ) {
				ServerPanelBase.Log("ServerPanelFile", "Config sync files read error - possible version mismatch");
				return;
			}
			sPanelConfig 	= syncConfig.param1;
			sConfigBool 	= syncConfig.param2;
		}

		if (layoutRoot.IsVisible()) {
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

			sPlayerInfo 	= sConfigBool[0];
			sPlayerTab 		= sConfigBool[1];

			m_Link1		= sBtn1link;
			m_Link2		= sBtn2link;
			m_Link3		= sBtn3link;
			m_Tab0name	= sTab0name;
			m_Tab1name	= sTab1name;
			m_Tab2name	= sTab2name;
			m_Tab3name	= sTab3name;

			m_ServerName.SetText(sServerName);

			if (!sPlayerInfo) {
				float new_x = 98/100;
				float new_y = 77/100;
				m_PlayerInfo.Show(false);
				m_PanelTabs.SetSize(new_x,new_y);
			}

			if (!sPlayerTab) {
				//m_Tab4.Show(false);
				m_btnTabTitle4.Show(false);
			}

			if (m_Tab0name != "") {
				m_btnTabTitle0.SetText(m_Tab0name);
				m_btnTabTitle0.Show(true);
			}
			else m_btnTabTitle0.Show(false);

			if (m_Tab1name != "") {
				m_btnTabTitle1.SetText(m_Tab1name);
				m_btnTabTitle1.Show(true);
			}
			else m_btnTabTitle1.Show(false);

			if (m_Tab2name != "") {
				m_btnTabTitle2.SetText(m_Tab2name);
				m_btnTabTitle2.Show(true);
			}
			else m_btnTabTitle2.Show(false);

			if (m_Tab3name != "") {
				m_btnTabTitle3.SetText(m_Tab3name);
				m_btnTabTitle3.Show(true);
			}
			else m_btnTabTitle3.Show(false);

			if (m_Link1 != "" && sBtn1name != "") {
				m_BtnRight.SetText(sBtn1name);
				m_BtnRight.Show(true);
			}
			else m_BtnRight.Show(false);

			if (m_Link2 != "" && sBtn2name != "") {
				m_BtnLeft.SetText(sBtn2name);
				m_BtnLeft.Show(true);
			}
			else m_BtnLeft.Show(false);

			if (m_Link3 != "" && sBtn3name != "") {
				m_BtnDonate.SetText(sBtn3name);
				m_BtnDonate.Show(true);
			}
			else m_BtnDonate.Show(false);
		}
	}
	void SyncTab( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param4<ref TStringArray, ref TStringArray, ref TStringArray, ref TStringArray> syncTabs;

		ref TStringArray sServerTab0	= new TStringArray;
		ref TStringArray sServerTab1	= new TStringArray;
		ref TStringArray sServerTab2	= new TStringArray;
		ref TStringArray sServerTab3	= new TStringArray;

		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( syncTabs ) ) {
				ServerPanelBase.Log("ServerPanelFile", "Tab sync files read error - possible version mismatch");
				return;
			}
			sServerTab0	= syncTabs.param1;
			sServerTab1	= syncTabs.param2;
			sServerTab2	= syncTabs.param3;
			sServerTab3	= syncTabs.param3;
		}

		int i;

		for ( i = 0; i < sServerTab0.Count(); ++i ) 	m_Tab0List.AddItem(sServerTab0.Get(i), new Param1<string>(sServerTab0.Get(i)), 0);
		for ( i = 0; i < sServerTab1.Count(); ++i ) 	m_Tab1List.AddItem(sServerTab1.Get(i), new Param1<string>(sServerTab1.Get(i)), 0);
		for ( i = 0; i < sServerTab2.Count(); ++i ) 	m_Tab2List.AddItem(sServerTab2.Get(i), new Param1<string>(sServerTab2.Get(i)), 0);
		for ( i = 0; i < sServerTab3.Count(); ++i ) 	m_Tab3List.AddItem(sServerTab3.Get(i), new Param1<string>(sServerTab3.Get(i)), 0);
	}

	void SyncPlayers( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param6<ref TStringArray, ref TIntArray, vector, TFloatArray, string, bool> syncDataS;
		ref TStringArray PlayerListC		= new TStringArray;
		ref TIntArray PlayerDataC			= new TIntArray;
		ref TFloatArray PlayerDataF			= new TFloatArray;

		int sUpTime 		= 	0;
		int sHealth 		=	0;
		int sBlood 			=	0;
		//int sAvgPing		=	0;
		float sEnergy 		=	0;
		float sWater 		=	0;
		float sDistance 	=	0;
		float sPlaytime 	=	0;
		float sShock		=	0;
		float sStamina		=	0;

		if ( type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			if ( !ctx.Read( syncDataS ) ) {
				ServerPanelBase.Log("SyncPlayer","Player sync data read error - possible version mismatch");
				return;
			}

			m_PlayersList.ClearItems();
			PlayerListC			= syncDataS.param1;
			PlayerDataC			= syncDataS.param2;
			vector PlayerPos	= syncDataS.param3;
			PlayerDataF			= syncDataS.param4;
			string sItemHands	= syncDataS.param5;
			bool sDisease		= syncDataS.param6;

			if (PlayerDataC.Count() == 0) return;

			sUpTime = Math.Round(PlayerDataC[0]/1000);
		}

		sHealth 		=	PlayerDataC[2];
		sBlood 			=	PlayerDataC[3];
		//sAvgPing		=	PlayerDataC[4];
		sEnergy 		=	PlayerDataF[1];
		sWater 			=	PlayerDataF[0];
		sDistance 		=	PlayerDataF[2];
		sPlaytime 		=	PlayerDataF[3];
		sShock			=	PlayerDataF[4];
		sStamina		=	PlayerDataF[5];

		if (layoutRoot.IsVisible()) {

			m_HealthBar.SetCurrent(sHealth);
			m_BloodBar.SetCurrent(sBlood);
			m_ShockBar.SetCurrent(sShock);
			m_StaminaBar.SetCurrent(sStamina);

			m_TextPlayerHealth.SetText(" " + sHealth.ToString());
			m_TextPlayerBlood.SetText(" " + sBlood.ToString());
			//m_AvgPing.SetText(" " + sAvgPing + "ms");

			if (sDisease) m_Condition.SetText("Sick !");
			else m_Condition.SetText("Healthy");

			if (sItemHands == "")	m_ItemHands.SetText("Nothing :)");
			else {m_ItemHands.SetText(sItemHands);SPItemPreview();}

			int hours 			= sPlaytime / 3600;
			int minutes 		= sPlaytime / 60;
			int seconds 		= sPlaytime - minutes * 60;
			minutes 			= minutes - hours * 60;
			m_SurvivalTime.SetText("" + hours + "h " + minutes + "m " + seconds + "s");

			int a1 				= sDistance / 10;
			float ran 			= (float) a1 / 100.0;
			m_DistanceTravelled.SetText("" + ran + " Km");

			int y =1;
			for ( int i = 0; i < PlayerListC.Count(); ++i ) {
				m_PlayersList.AddItem(" " + y.ToString() + ": " + PlayerListC.Get(i), new Param1<string>(PlayerListC.Get(i)), 0);
				y++;
			}
			int sHours 			= Math.Floor(sUpTime / 3600);
			int sMinutes 		= ((sUpTime / 60) % 60);
			int sSeconds 		= sUpTime - sMinutes * 60;
			m_PlayTime.SetText(sHours.ToString() + "h " + sMinutes.ToString() + "m" + sSeconds.ToString() + "s");
			//m_PlayerTitle.SetText("Online Players: " + PlayerListC.Count());
			m_TextPlayerNickname.SetText(PlayerListC.Get(PlayerDataC[1]));
			m_TextPlayerPos.SetText("Pos. X: " + Math.Floor(PlayerPos[0]).ToString() + "  Y: " + Math.Floor(PlayerPos[2]).ToString());

			if	(sHealth <= 20)	{m_TextPlayerHealth.SetColor(RED);}
			else if	(sHealth <= 40 && sHealth > 20)	{m_TextPlayerHealth.SetColor(ORANGE);m_HealthBar.SetColor(ORANGE);}
			else if	(sHealth <= 60 && sHealth > 40)	{m_TextPlayerHealth.SetColor(YELLOW);m_HealthBar.SetColor(YELLOW);}
			else if	(sHealth > 60 && sHealth <= 90)	{m_TextPlayerHealth.SetColor(GREEN);}
			else if	(sHealth > 90)	{m_TextPlayerHealth.SetColor(WHITE);}
			
			if	(sBlood <= 3000)		{m_TextPlayerBlood.SetColor(RED);}
			else if	(sBlood <= 3500 && sBlood > 3000)	{m_TextPlayerBlood.SetColor(ORANGE);m_BloodBar.SetColor(GREEN);}
			else if	(sBlood <= 4000 && sBlood > 3500)	{m_TextPlayerBlood.SetColor(YELLOW);m_BloodBar.SetColor(YELLOW);}
			else if	(sBlood > 4000 && sBlood <= 4500)	{m_TextPlayerBlood.SetColor(GREEN);m_BloodBar.SetColor(ORANGE);}
			else if	(sBlood > 4500)	{m_TextPlayerBlood.SetColor(WHITE);}
			
			if	(sEnergy <= 200)	{m_TextPlayerEnergy.SetColor(RED);m_TextPlayerEnergy.SetText(" Starved !");}
			else if	(sEnergy <= 400 && sEnergy > 200)	{m_TextPlayerEnergy.SetColor(YELLOW);m_TextPlayerEnergy.SetText(" Feel Starved");}
			else if	(sEnergy > 400 && sEnergy <= 1000)	{m_TextPlayerEnergy.SetColor(WHITE);m_TextPlayerEnergy.SetText(" Good");}
			else if	(sEnergy > 1000)	{m_TextPlayerEnergy.SetColor(WHITE);m_TextPlayerEnergy.SetText(" Excellent");}
			
			if	(sWater <= 300)	{m_TextPlayerWater.SetColor(RED);m_TextPlayerWater.SetText(" Thirsty !");}
			else if (sWater <= 600 && sWater > 300)		{m_TextPlayerWater.SetColor(YELLOW);m_TextPlayerWater.SetText(" Feel Thirsty");}
			else if (sWater > 600 && sWater <= 1000)	{m_TextPlayerWater.SetColor(WHITE);m_TextPlayerWater.SetText(" Good");}
			else if (sWater > 1000)	{m_TextPlayerWater.SetColor(WHITE);m_TextPlayerWater.SetText(" Excellent");}
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

		switch (w)	{
		case m_BtnCancel:
		case m_BtnClose:
			return OnBtnCloseClick();
		case m_BtnRight:
			return OnBtnRightClick();
		case m_BtnLeft:
			return OnBtnLeftClick();
		case m_BtnDonate:
			return OnDiscordBtnClick();
		case m_btnTabTitle0:
		case m_btnTabTitle1:
		case m_btnTabTitle2:
		case m_btnTabTitle3:
		case m_btnTabTitle4:
			return OnBtnTabClick(w);
		default:
			break;
		}
		return true;
	}

	bool OnDiscordBtnClick()	{
		GetGame().OpenURL(m_Link3);
		Print("CLICKED THIRD BUTTON");
		return true;
	}
	bool OnBtnLeftClick()	{
		GetGame().OpenURL(m_Link2);
		Print("CLICKED SECOND BUTTON");
		return true;
	}
	bool OnBtnRightClick()	{
		GetGame().OpenURL( m_Link1 );
		Print("CLICKED FIRST BUTTON");
		return true;
	}
	bool OnBtnCloseClick()	{
		Hide();
		UIManager uiManager = GetGame().GetUIManager();
		uiManager.CloseAll();
		return true;
	}
	bool OnBtnTabClick(Widget w)	{
		if (Transitioning)
			return true;

		if (w == m_btnTabTitle0)	{
			if (m_CurrentTabPanel != m_Tab0)
				TransitionTab(m_Tab0, m_CurrentTabPanel);
		}
		else if (w == m_btnTabTitle1)	{
			if (m_CurrentTabPanel != m_Tab1)
				TransitionTab(m_Tab1, m_CurrentTabPanel);
		}
		else if (w == m_btnTabTitle2)	{
			if (m_CurrentTabPanel != m_Tab2)
				TransitionTab(m_Tab2, m_CurrentTabPanel);
		}
		else if (w == m_btnTabTitle3)	{
			if (m_CurrentTabPanel != m_Tab3)
				TransitionTab(m_Tab3, m_CurrentTabPanel);
		}
		else if (w == m_btnTabTitle4)	{
			if (m_CurrentTabPanel != m_Tab4)
				TransitionTab(m_Tab4, m_CurrentTabPanel);
		}
		return true;
	}
	void TransitionTab(Widget newTab, Widget oldTab)	{
		Transitioning = true;
		float width, height, x, y;
		m_CurrentTabPanel.GetSize(width, height);
		m_CurrentTabPanel.GetPos(x, y);
		float neededX = (x - width) - TAB_OFFSET;

		float stepSize = neededX / TRANSITION_ANIMATION_STEPS;

		currentTransitionStep = 0;
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(TransitionStep, 10, true, newTab, oldTab, stepSize);

		m_CurrentTabPanel = newTab;
	}
	void TransitionStep(Widget newTab, Widget oldTab, float stepSize)	{
		currentTransitionStep++;
		float x, y;
		oldTab.GetPos(x, y);
		oldTab.SetPos((x - stepSize), y, true);
		newTab.GetPos(x, y);
		newTab.SetPos((x - stepSize), y, true);
		//Don't even fucking ask .... callLater seems to break if statement number comparison
		if (currentTransitionStep.ToString() == TRANSITION_ANIMATION_STEPS.ToString())		{
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(TransitionStep);
			newTab.SetPos(centerX, y, true);
			oldTab.SetPos(leftX, y, true);
			Transitioning = false;
		}
	}
}