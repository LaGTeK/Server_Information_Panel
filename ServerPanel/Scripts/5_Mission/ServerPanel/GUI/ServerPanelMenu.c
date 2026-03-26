class ServerPanelMenu extends UIScriptedMenu {
	private static ServerPanelServerConfig config;

	PlayerBase Player;
	
	//CRAFT TAB
    private ref CraftingDisplay m_CraftingDisplay;
	//PLAYER TAB
    private ref PlayerInfoDisplay m_PlayerInfoDisplay;

#ifdef EXPANSIONMODMARKET
	protected ref ExpansionMarketModule m_MarketModule;
#endif

	private bool m_DisplayPlayerTab,m_DisplayCraftingTab,m_DisplayPlayerList,m_DisplaySidePanel;

	private Widget 						m_WidgetRoot;

	//MONEYMARKET
	protected 	Widget 					m_MoneyPanelWidget;
	protected 	TextWidget 				m_CurrencyTextWidget;
	protected 	ImageWidget 			m_CurrencyIconWidget;

	//Main Widgets
	private Widget						m_PanelTabs,m_PlayerInfo,m_PlayerListWidget,m_LogoPanelWidget;
	//Tabs
	private Widget 						m_Tab0,m_Tab1,m_Tab2,m_Tab3,m_Tab4,m_Tab5;

	//Tab scroll areas
	private ScrollWidget				m_TabScroll0, m_TabScroll1, m_TabScroll2, m_TabScroll3;

	//Buttons Tab
	private ButtonWidget 				m_btnTabTitle0,m_btnTabTitle1,m_btnTabTitle2,m_btnTabTitle3,m_btnTabTitle4,m_btnTabTitle5;

	//Buttons
	private ButtonWidget 				m_BtnCancel,m_BtnRight,m_BtnLeft,m_BtnClose,m_BtnDonate,m_btnDescription,m_btnRules;
	
	private ScrollWidget				m_PlayerListScrollWidget;

	private MultilineTextWidget 		m_ServerName,m_PlayersList;

	protected TextWidget 				m_TitlePanel,m_PlayerTitle,m_TextPlayerNickname,m_PlayTime,m_TextPlayerBlood,m_TextPlayerHealth,m_TextPlayerWater,m_TextPlayerEnergy,m_TextPlayerPos,m_ItemHands,m_ServerTime,m_Condition,m_ZKilled,m_PKilled,m_LongestShot;

	//New Tabs
	private RichTextWidget				m_TextTab0,m_TextTab1,m_TextTab2,m_TextTab3;
	private int 						m_Tab0LineCount, m_Tab1LineCount, m_Tab2LineCount, m_Tab3LineCount;

	private string 						m_Link1, m_Link2, m_Link3, m_Tab0name, m_Tab1name, m_Tab2name, m_Tab3name, m_LogoPath;
	
	protected ImageWidget 				m_LogoImageWidget;
	private float 						m_LogoWidth,m_LogoHeight;

	// Side panel icon caches (widgets + last rendered state)
	private ref array<ImageWidget> 		m_BloodIcons;
	private ref array<ImageWidget> 		m_WaterIcons;
	private ref array<ImageWidget> 		m_FoodIcons;
	private ref TStringArray 			m_BloodIconPathsCache;
	private ref TStringArray 			m_WaterIconPathsCache;
	private ref TStringArray 			m_FoodIconPathsCache;
	private ref TIntArray 				m_BloodIconColorsCache;
	private ref TIntArray 				m_WaterIconColorsCache;
	private ref TIntArray 				m_FoodIconColorsCache;

	private ref array<Widget> 			m_TabPanels;
	private ref array<ButtonWidget> 	m_TabButtons;
	private int 						m_ActiveTabIndex;

	//Tab transition (lightweight, only on switch)
	private bool						m_TabTransitioning;
	private int							m_TabTransitionStep;
	private Widget						m_TabTransitionOld;
	private Widget						m_TabTransitionNew;
	private float						m_TabTransitionY;
	private float						m_TabTransitionOffX;
	private const int					TAB_TRANSITION_STEPS = 18;
	private const int					TAB_TRANSITION_MS = 10;

	// Static tab content should be fitted once per menu open.
	private bool						m_TabContentFitted0;
	private bool						m_TabContentFitted1;
	private bool						m_TabContentFitted2;
	private bool						m_TabContentFitted3;

	private bool 						m_SidePanelHaveSnapshot;
	private string 						m_SidePanelCachedHealthText;
	private int 						m_SidePanelCachedHealthColor;
	private string 						m_SidePanelCachedNick;
	private string 						m_SidePanelCachedPlayerTitleText;
	private string 						m_SidePanelCachedPlayerListText;
	private string 						m_SidePanelCachedPosText;
	private bool 						m_SidePanelCachedShowPos;
	private int 						m_SidePanelCachedBlood;
	private float 						m_SidePanelCachedWater;
	private float 						m_SidePanelCachedEnergy;
	//bool m_LogLevel;//Current Tab

	//Widget 								m_CurrentTabPanel;
	//ServerPanelTab 						m_CurrentTab;

	//Transition
	//int currentTransitionStep;
	//float centerX, leftX;
	//bool Transitioning 						= false;
	//const int TRANSITION_ANIMATION_STEPS 	= 40;
	//const float TAB_OFFSET 					= 0.05;

	void ServerPanelMenu()	{
		config = GetServerPanelServerConfig();	
		m_DisplayPlayerTab 		= config.DISPLAYPLAYERTAB;	
		m_DisplayCraftingTab 	= config.DISPLAYCRAFTTAB;	
		m_DisplayPlayerList 	= config.DISPLAYPLAYERLIST;		
		m_DisplaySidePanel		= config.DISPLAYPLAYERINFO;

		// Force initial SetActiveTab(...) to apply visibility correctly.
		m_ActiveTabIndex = -1;

		// Initialiser le Player une seule fois dans le constructeur
		Player = PlayerBase.Cast(g_Game.GetPlayer());

        m_CraftingDisplay = new CraftingDisplay(); // Initialize crafting display

        m_PlayerInfoDisplay = new PlayerInfoDisplay(Player);  // Passe l'instance du joueur à PlayerInfoDisplay
	}

	override Widget Init()	{	
		layoutRoot 						=	g_Game.GetWorkspace().CreateWidgets( "ServerPanel/GUI/layouts/ServerPanel.layout" );
		layoutRoot.Show(false);
		
		m_PlayerInfo					=	Widget.Cast(layoutRoot.FindAnyWidget("PanelPlayerInformation"));

		m_PlayerListWidget				=	Widget.Cast(layoutRoot.FindAnyWidget("PlayerListPanelWidget"));

		m_PanelTabs						=	Widget.Cast(layoutRoot.FindAnyWidget("PanelTabs"));

		m_TitlePanel 					=	TextWidget.Cast( layoutRoot.FindAnyWidget( "title_text" ));

		m_ServerName 					=	MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "text_name" ));

		m_LogoPanelWidget				=	Widget.Cast(layoutRoot.FindAnyWidget("LogoPanelWidget"));
		m_LogoImageWidget				=	ImageWidget.Cast(layoutRoot.FindAnyWidget("LogoImageWidget"));

		m_BtnDonate	 					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_donate" ));
		m_BtnRight	 					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_discord" ));
		m_BtnLeft	 					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_website" ));
		m_BtnCancel	 					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_cancel" ));
		m_BtnClose	 					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_close_widget" ));

		//BtnTab
		m_btnTabTitle0					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_0" ));
		m_btnTabTitle1 					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_1" ));
		m_btnTabTitle2					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_2" ));
		m_btnTabTitle3					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_3" ));
		m_btnTabTitle4 					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_4" ));
		m_btnTabTitle5					=	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonTab_5" ));

		//Tabs
		m_Tab0							=	Widget.Cast(layoutRoot.FindAnyWidget("Tab_0"));
		m_Tab1							=	Widget.Cast(layoutRoot.FindAnyWidget("Tab_1"));
		m_Tab2							=	Widget.Cast(layoutRoot.FindAnyWidget("Tab_2"));
		m_Tab3							=	Widget.Cast(layoutRoot.FindAnyWidget("Tab_3"));
		m_Tab4							=	Widget.Cast(layoutRoot.FindAnyWidget("Tab_4"));				
		m_Tab5							=	Widget.Cast(layoutRoot.FindAnyWidget("Tab_5"));

		//New Tabs
		m_TextTab0						=	RichTextWidget.Cast(layoutRoot.FindAnyWidget("Text_Tab0"));
		m_TextTab1						=	RichTextWidget.Cast(layoutRoot.FindAnyWidget("Text_Tab1"));
		m_TextTab2						=	RichTextWidget.Cast(layoutRoot.FindAnyWidget("Text_Tab2"));
		m_TextTab3						=	RichTextWidget.Cast(layoutRoot.FindAnyWidget("Text_Tab3"));

		m_TabScroll0						=	ScrollWidget.Cast(layoutRoot.FindAnyWidget("ScrollWidget0"));
		m_TabScroll1						=	ScrollWidget.Cast(layoutRoot.FindAnyWidget("ScrollWidget1"));
		m_TabScroll2						=	ScrollWidget.Cast(layoutRoot.FindAnyWidget("ScrollWidget2"));
		m_TabScroll3						=	ScrollWidget.Cast(layoutRoot.FindAnyWidget("ScrollWidget3"));

		//Player Information Right Side
		m_TextPlayerNickname			=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_Nickname" ) );
		m_TextPlayerHealth 				=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_health" ) );
		m_TextPlayerPos 				=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_position" ) );
		m_PlayerTitle 					=	TextWidget.Cast( layoutRoot.FindAnyWidget( "OnlinePlayerTitle" ) );
		//m_TextPlayerBlood 			=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_blood" ) );
		//m_TextPlayerWater 			=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_water" ) );
		//m_TextPlayerEnergy 			=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_food" ) );

		m_PlayerListScrollWidget		=	ScrollWidget.Cast( layoutRoot.FindAnyWidget( "PlayerListScrollWidget" ) );
		m_PlayersList 					=	MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "Player_List" ) );
		InitSidePanelIconCache();

		//Tab Transisition
		//m_CurrentTab 					=	ServerPanelTab.Tab0;
		//m_CurrentTabPanel 				=	m_Tab0;

		//float x, y, w, h;
		//m_CurrentTabPanel.GetPos(x, y);
		//m_CurrentTabPanel.GetSize(w, h);

		//centerX = x;

		//float neededX = (x - w) - TAB_OFFSET;
		//leftX = neededX;
		//m_Tab1.SetPos(neededX, y, true);
		//m_Tab2.SetPos(neededX, y, true);
		//m_Tab3.SetPos(neededX, y, true);
		//m_Tab4.SetPos(neededX, y, true);
		//m_Tab5.SetPos(neededX, y, true);
		
		InitTabArrays();
		SetActiveTab(0);

		//Money Widget
		//EXPANSIONMARKET
		m_MoneyPanelWidget				=	Widget.Cast(layoutRoot.FindAnyWidget("MoneyPanelWidget"));
		m_CurrencyTextWidget 			=	TextWidget.Cast( layoutRoot.FindAnyWidget("CurrencyTextWidget"));
		m_CurrencyIconWidget			=	ImageWidget.Cast(layoutRoot.FindAnyWidget("CurrencyIconWidget"));
		
		m_MoneyPanelWidget.Show(false);

		//Settings & Title
		UpdateHeader();
		FillFilesInformations();		
		ScheduleTabScrollResets();

		if (m_DisplayCraftingTab) 
		{
            m_CraftingDisplay.Init(layoutRoot);  // Delegate crafting UI to the CraftingDisplay class
        } 
		else 
		{
            m_Tab4.Show(false);
            m_btnTabTitle4.Show(false);
        }

		if (m_DisplayPlayerTab) 
		{
            m_PlayerInfoDisplay.Init(layoutRoot);  // Delegate crafting UI to the CraftingDisplay class
        } 
		else 
		{
            m_Tab5.Show(false);
            m_btnTabTitle5.Show(false);
        }

		return layoutRoot;
	}

#ifdef EXPANSIONMODMARKET
	void DisplayPlayerMoney()
	{
		// Initialize the market module if not already done
		if (!m_MarketModule)
		{
			m_MarketModule = ExpansionMarketModule.Cast(CF_ModuleCoreManager.Get(ExpansionMarketModule));
		}

		// Check if the module is valid
		if (m_MarketModule)
		{
			array<int> monies = new array<int>;
			int playerWorth = m_MarketModule.GetPlayerWorth(PlayerBase.Cast(g_Game.GetPlayer()), monies);

			// Convert playerWorth into a formatted string
			string currencyString = ExpansionStatic.IntToCurrencyString(playerWorth, ",");
			// Retrieve the display currency name from the market settings
			string displayCurrencyName = config.CURRENCYNAME;  // Get the first currency in the array

			m_MoneyPanelWidget.Show(true);
			
			// Display this string on your panel, now including the display currency name
			m_CurrencyTextWidget.SetText(currencyString + " " + displayCurrencyName);

			if (GetExpansionSettings().GetMarket().CurrencyIcon != "")
				m_CurrencyIconWidget.LoadImageFile(0, GetExpansionSettings().GetMarket().CurrencyIcon);
			else                 
				m_CurrencyIconWidget.LoadImageFile(0, "set:spicons image:Money");
		}	
	}
#endif

	void FillFilesInformations()	{
		if (!config)
			return;

		// Tab texts are static; re-fit once on next menu open/reset.
		m_TabContentFitted0 = false;
		m_TabContentFitted1 = false;
		m_TabContentFitted2 = false;
		m_TabContentFitted3 = false;

		m_ServerName.SetText(config.SERVERNAME);

		if (!m_DisplayPlayerTab) m_btnTabTitle5.Show(false);

		if (!m_DisplayCraftingTab) m_btnTabTitle4.Show(false);

		m_Link1 				= config.BUTTON1LINK;
		m_Link2 				= config.BUTTON2LINK;
		m_Link3 				= config.BUTTON3LINK;
		m_Tab0name				= config.BUTTONTAB0NAME;
		m_Tab1name				= config.BUTTONTAB1NAME;
		m_Tab2name				= config.BUTTONTAB2NAME;
		m_Tab3name				= config.BUTTONTAB3NAME;
		m_LogoPath				= config.LOGOPATH;
		m_LogoWidth				= config.LOGO_WIDTH_PERCENTAGE/100;
		m_LogoHeight			= config.LOGO_HEIGHT_PERCENTAGE/100;

		
		if (config.DISPLAYCURRENCY)
		{
#ifdef EXPANSIONMODMARKET
			DisplayPlayerMoney();
#endif	
		}
		else{
			m_MoneyPanelWidget.Show(false);
		}
	
		if (m_DisplaySidePanel) {
			if (m_DisplayPlayerList) {
				if (config.DISPLAYPLOGO)
				{
					if (m_LogoPath != "" && m_LogoWidth != 0 && m_LogoHeight != 0)
					{
						m_PlayerListScrollWidget.Show(true);
						m_PlayerListScrollWidget.SetSize(98/100, 44/100);
						m_LogoPanelWidget.Show(true);
						m_LogoImageWidget.SetSize(m_LogoWidth, m_LogoHeight);
						m_LogoImageWidget.LoadImageFile(0, m_LogoPath);
					}
					else {
						m_PlayerListScrollWidget.Show(true);
						m_PlayerListScrollWidget.SetSize(98/100, 90/100);
						m_LogoPanelWidget.Show(false);
					}
				}
				else {
					m_PlayerListScrollWidget.Show(true);
					m_PlayerListScrollWidget.SetSize(98/100, 90/100);
					m_LogoPanelWidget.Show(false);
				}
			}
			else {
				if (config.DISPLAYPLOGO)
				{
					if (m_LogoPath != "" && m_LogoWidth != 0 && m_LogoHeight != 0)
					{
						m_PlayerListWidget.Show(false);
						m_LogoPanelWidget.Show(true);
						m_LogoImageWidget.SetSize(m_LogoWidth, m_LogoHeight);
						m_LogoImageWidget.LoadImageFile(0, m_LogoPath);
					}
					else {
						m_PlayerListWidget.Show(false);
						m_LogoPanelWidget.Show(false);
					}
				}
				else {
					m_PlayerListWidget.Show(false);
					m_LogoPanelWidget.Show(false);
				}
			}
		} else {
			float new_x = 98/100;
			float new_y = 77/100;
			m_PlayerInfo.Show(false);
			m_PanelTabs.SetSize(new_x,new_y);
		}

		if (m_Tab0name != "") {
			m_btnTabTitle0.SetText(m_Tab0name);
			m_btnTabTitle0.Show(true);
			m_Tab0LineCount = config.sServerTab0.Count();
			// Tab 0
			string m_TabText0 = "";
			for (int m = 0; m < m_Tab0LineCount; m++) {
				m_TabText0 += config.sServerTab0[m];
			}
			m_TextTab0.SetText(m_TabText0);
			ScheduleTabScrollResets();
			
			if (m_TabText0=="") {
				m_btnTabTitle0.Show(false);
			}
		}
		else m_btnTabTitle0.Show(false);

		if (m_Tab1name != "") {
			m_btnTabTitle1.SetText(m_Tab1name);
			m_btnTabTitle1.Show(true);
			m_Tab1LineCount = config.sServerTab1.Count();
			// Tab 1
			string m_TabText1 = "";
			for (int n = 0; n < m_Tab1LineCount; n++) {
				m_TabText1 += config.sServerTab1[n];
			}
			m_TextTab1.SetText(m_TabText1);
			ScheduleTabScrollResets();
			
			if (m_TabText1=="") {
				m_btnTabTitle1.Show(false);
			}
		}
		else m_btnTabTitle1.Show(false);

		if (m_Tab2name != "") {
			m_btnTabTitle2.SetText(m_Tab2name);
			m_btnTabTitle2.Show(true);
			m_Tab2LineCount = config.sServerTab2.Count();
			// Tab 2
			string m_TabText2 = "";
			for (int o = 0; o < m_Tab2LineCount; o++) {
				m_TabText2 += config.sServerTab2[o];
			}
			m_TextTab2.SetText(m_TabText2);
			ScheduleTabScrollResets();
			
			if (m_TabText2=="") {
				m_btnTabTitle2.Show(false);
			}
		}
		else m_btnTabTitle2.Show(false);

		if (m_Tab3name != "") {
			m_btnTabTitle3.SetText(m_Tab3name);
			m_btnTabTitle3.Show(true);
			m_Tab3LineCount = config.sServerTab3.Count();
			// Tab 3
			string m_TabText3 = "";
			for (int p = 0; p < m_Tab3LineCount; p++) {
				m_TabText3 += config.sServerTab3[p];
			}
			m_TextTab3.SetText(m_TabText3);
			ScheduleTabScrollResets();
			
			if (m_TabText3=="") {
				m_btnTabTitle3.Show(false);
			}
		}
		else m_btnTabTitle3.Show(false);

		if (m_Link1 != "" && config.BUTTON1NAME != "") {
			m_BtnRight.SetText(config.BUTTON1NAME);
			m_BtnRight.Show(true);
		}
		else m_BtnRight.Show(false);

		if (m_Link2 != "" && config.BUTTON2NAME != "") {
			m_BtnLeft.SetText(config.BUTTON2NAME);
			m_BtnLeft.Show(true);
		}
		else m_BtnLeft.Show(false);

		if (m_Link3 != "" && config.BUTTON3NAME != "") {
			m_BtnDonate.SetText(config.BUTTON3NAME);
			m_BtnDonate.Show(true);
		}
		else m_BtnDonate.Show(false);
	}

	void SyncPanelStats(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param7<ref TStringArray, ref TIntArray, ref TFloatArray, ref TFloatArray, vector, string, bool> syncData;

		ref TStringArray playerListC = new TStringArray;
		ref TIntArray sideInts = new TIntArray;
		ref TFloatArray playerTabFloats = new TFloatArray;
		ref TFloatArray sideHydration = new TFloatArray;
		vector playerPos;
		string playerNick = "";
		bool sDisease = false;

		if ((type == CallType.Client && g_Game.IsClient()) || !g_Game.IsMultiplayer()) {
			if (!ctx.Read(syncData)) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "SyncPanelStats", "Panel stats read error - possible version mismatch");
				return;
			}

			playerListC = syncData.param1;
			sideInts = syncData.param2;
			playerTabFloats = syncData.param3;
			sideHydration = syncData.param4;
			playerPos = syncData.param5;
			playerNick = syncData.param6;
			sDisease = syncData.param7;
		}

		if (m_DisplayPlayerTab && m_PlayerInfoDisplay && sideInts && playerTabFloats && playerTabFloats.Count() >= 8) {
			ref TIntArray playerInfoInts = new TIntArray;
			if (m_DisplaySidePanel && sideInts.Count() >= 3) {
				playerInfoInts.Insert(sideInts[1]);
				playerInfoInts.Insert(sideInts[2]);
			} else if (sideInts.Count() >= 2) {
				playerInfoInts.Insert(sideInts[0]);
				playerInfoInts.Insert(sideInts[1]);
			}
			if (playerInfoInts.Count() == 2) {
				m_PlayerInfoDisplay.UpdatePlayerInfo(playerInfoInts, playerTabFloats, sDisease);
			}
		}

		if (m_DisplaySidePanel && sideInts && sideHydration && sideInts.Count() >= 3 && sideHydration.Count() >= 2) {
			ApplySidePanelFromSync(playerListC, sideInts, sideHydration, playerPos, playerNick);
		}
	}

	private void ApplySidePanelFromSync(TStringArray playerListC, TIntArray sideInts, TFloatArray hydration, vector PlayerPos, string m_playerName)
	{
		int sHealth = sideInts[1];
		int sBlood = sideInts[2];
		float sWater = hydration[0];
		float sEnergy = hydration[1];

		if (!layoutRoot.IsVisible()) {
			return;
		}

		bool fullRefresh = !m_SidePanelHaveSnapshot;

		string healthText = " " + sHealth.ToString();
		if (fullRefresh || healthText != m_SidePanelCachedHealthText) {
			m_TextPlayerHealth.SetText(healthText);
			m_SidePanelCachedHealthText = healthText;
		}

		int healthColor = GetSidePanelHealthColor(sHealth);
		if (fullRefresh || healthColor != m_SidePanelCachedHealthColor) {
			m_TextPlayerHealth.SetColor(healthColor);
			m_SidePanelCachedHealthColor = healthColor;
		}

		if (fullRefresh || m_playerName != m_SidePanelCachedNick) {
			m_TextPlayerNickname.SetText(m_playerName);
			m_SidePanelCachedNick = m_playerName;
		}

		if (m_DisplayPlayerList && playerListC) {
			string playerTitleText = "#STR_SP_ONLINE_PLAYERS_TXT" + ": " + playerListC.Count();
			int y = 1;
			string playerListText = "";
			for (int i = 0; i < playerListC.Count(); ++i) {
				playerListText += " " + y.ToString() + ": " + playerListC.Get(i) + "\n";
				y++;
			}

			if (fullRefresh || playerTitleText != m_SidePanelCachedPlayerTitleText) {
				m_PlayerTitle.SetText(playerTitleText);
				m_SidePanelCachedPlayerTitleText = playerTitleText;
			}

			if (fullRefresh || playerListText != m_SidePanelCachedPlayerListText) {
				m_PlayersList.SetText(playerListText);
				m_SidePanelCachedPlayerListText = playerListText;
			}
		}

		bool showPos = config.DISPLAYPLAYERPOSITION;
		if (fullRefresh || showPos != m_SidePanelCachedShowPos) {
			m_TextPlayerPos.Show(showPos);
			m_SidePanelCachedShowPos = showPos;
		}

		if (showPos) {
			string posText = "#STR_SP_POS_TXT" + " X: " + Math.Floor(PlayerPos[0]).ToString() + "  Y: " + Math.Floor(PlayerPos[2]).ToString();
			if (fullRefresh || posText != m_SidePanelCachedPosText) {
				m_TextPlayerPos.SetText(posText);
				m_SidePanelCachedPosText = posText;
			}
		}

		if (fullRefresh || sBlood != m_SidePanelCachedBlood) {
			UpdateBloodDisplay(sBlood);
			m_SidePanelCachedBlood = sBlood;
		}

		if (fullRefresh || sWater != m_SidePanelCachedWater) {
			UpdateWaterDisplay(sWater);
			m_SidePanelCachedWater = sWater;
		}

		if (fullRefresh || sEnergy != m_SidePanelCachedEnergy) {
			UpdateFoodDisplay(sEnergy);
			m_SidePanelCachedEnergy = sEnergy;
		}

		m_SidePanelHaveSnapshot = true;
	}

	private int GetSidePanelHealthColor(int sHealth)
	{
		if (sHealth <= PlayerConstants.SL_HEALTH_CRITICAL) {
			return ServerPanelConstants.RED;
		}
		if (sHealth <= PlayerConstants.SL_HEALTH_LOW) {
			return ServerPanelConstants.ORANGE;
		}
		if (sHealth <= PlayerConstants.SL_HEALTH_NORMAL) {
			return ServerPanelConstants.YELLOW;
		}
		if (sHealth <= PlayerConstants.SL_HEALTH_HIGH) {
			return ServerPanelConstants.WHITE;
		}
		return ServerPanelConstants.WHITE;
	}

	private void ResetSidePanelUiCache()
	{
		m_SidePanelHaveSnapshot = false;
	}

	override void Update(float timeslice) {
		super.Update(timeslice);

		if (KeyState(KeyCode.KC_ESCAPE) == 1 || g_Game.GetInput().LocalRelease("SPOpenPanelMenu"))
			Back();

        if (m_DisplayCraftingTab && m_ActiveTabIndex == 4) {
            m_CraftingDisplay.Update(timeslice);
        }

        if (m_DisplayPlayerTab && m_ActiveTabIndex == 5) {
            m_PlayerInfoDisplay.Update(timeslice);
        }
	}
	override bool OnClick(Widget w, int x, int y, int button) 
	{
		if (button == MouseState.LEFT)
		{
			if (w == m_BtnCancel || w == m_BtnClose)
			{
				Back();
				return true;
			}
			else if (w == m_BtnRight)
			{
				OnBtnRightClick();
				return true;
			}
			else if (w == m_BtnLeft)
			{
				OnBtnLeftClick();
				return true;
			}
			else if (w == m_BtnDonate)
			{
				OnDiscordBtnClick();
				return true;
			}
			else if (m_TabButtons)
			{
				for (int tb = 0; tb < m_TabButtons.Count(); tb++)
				{
					if (w == m_TabButtons.Get(tb))
					{
						SetActiveTab(tb);
						return true;
					}
				}
			}
		}
		return false;
	}

	protected bool OnDiscordBtnClick()	{
		g_Game.OpenURL(m_Link3);
		//Print("CLICKED THIRD BUTTON");
		return true;
	}

	protected bool OnBtnLeftClick()	{
		g_Game.OpenURL(m_Link2);
		//Print("CLICKED SECOND BUTTON");
		return true;
	}

	protected bool OnBtnRightClick()	{
		g_Game.OpenURL( m_Link1 );
		//Print("CLICKED FIRST BUTTON");
		return true;
	}

	protected bool OnBtnCloseClick()	{
		Back();
		return true;
	}

	private void InitTabArrays()
	{
		m_TabPanels = new array<Widget>();
		m_TabPanels.Insert(m_Tab0);
		m_TabPanels.Insert(m_Tab1);
		m_TabPanels.Insert(m_Tab2);
		m_TabPanels.Insert(m_Tab3);
		m_TabPanels.Insert(m_Tab4);
		m_TabPanels.Insert(m_Tab5);

		m_TabButtons = new array<ButtonWidget>();
		m_TabButtons.Insert(m_btnTabTitle0);
		m_TabButtons.Insert(m_btnTabTitle1);
		m_TabButtons.Insert(m_btnTabTitle2);
		m_TabButtons.Insert(m_btnTabTitle3);
		m_TabButtons.Insert(m_btnTabTitle4);
		m_TabButtons.Insert(m_btnTabTitle5);
	}

	private void SetActiveTab(int activeIndex)
	{
		if (!m_TabPanels || !m_TabButtons)
			return;

		if (activeIndex < 0 || activeIndex >= m_TabPanels.Count() || activeIndex >= m_TabButtons.Count())
			return;

		if (activeIndex == m_ActiveTabIndex && m_ActiveTabIndex >= 0)
			return;

		Widget oldTab = null;
		if (m_ActiveTabIndex >= 0 && m_ActiveTabIndex < m_TabPanels.Count())
			oldTab = m_TabPanels.Get(m_ActiveTabIndex);

		Widget newTab = m_TabPanels.Get(activeIndex);
		if (!newTab)
			return;

		StopTabTransition();

		// Ensure only the relevant tabs are visible for transition.
		for (int i = 0; i < m_TabPanels.Count(); i++)
		{
			Widget tab = m_TabPanels.Get(i);
			if (!tab)
				continue;
			tab.Show(false);
		}

		if (oldTab)
			oldTab.Show(true);
		newTab.Show(true);

		for (int j = 0; j < m_TabButtons.Count(); j++)
		{
			ButtonWidget btn = m_TabButtons.Get(j);
			if (btn)
			{
				if (j == activeIndex)
					btn.SetColor(ServerPanelConstants.ACTIVE_BUTTON_COLOR);
				else
					btn.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
			}
		}

		m_ActiveTabIndex = activeIndex;
		ScheduleTabScrollResets();

		if (activeIndex == 4 && m_DisplayCraftingTab && m_CraftingDisplay) {
			m_CraftingDisplay.EnsureRecipesLoadedOnce();
		}

		StartTabTransition(oldTab, newTab);
	}

	private void StartTabTransition(Widget oldTab, Widget newTab)
	{
		// If there is no old tab (first open), just snap.
		if (!newTab)
			return;

		float y;
		float dummy;
		newTab.GetPos(dummy, y);
		m_TabTransitionY = y;
		m_TabTransitionOffX = 1.02; // slightly offscreen

		// Start positions
		newTab.SetPos(m_TabTransitionOffX, m_TabTransitionY, true);
		if (oldTab)
			oldTab.SetPos(0, m_TabTransitionY, true);

		m_TabTransitionOld = oldTab;
		m_TabTransitionNew = newTab;
		m_TabTransitionStep = 0;
		m_TabTransitioning = true;

		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(DoTabTransitionStep, TAB_TRANSITION_MS, true);
	}

	private void StopTabTransition()
	{
		if (!m_TabTransitioning)
			return;

		g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(DoTabTransitionStep);
		m_TabTransitioning = false;
		m_TabTransitionStep = 0;
		m_TabTransitionOld = null;
		m_TabTransitionNew = null;
	}

	private void DoTabTransitionStep()
	{
		if (!m_TabTransitioning || !m_TabTransitionNew)
		{
			StopTabTransition();
			return;
		}

		m_TabTransitionStep++;

		float t = m_TabTransitionStep / (float)TAB_TRANSITION_STEPS;
		if (t > 1)
			t = 1;

		float newX = m_TabTransitionOffX + ((0 - m_TabTransitionOffX) * t);
		m_TabTransitionNew.SetPos(newX, m_TabTransitionY, true);

		if (m_TabTransitionOld)
		{
			float oldX = 0 + ((-m_TabTransitionOffX) * t);
			m_TabTransitionOld.SetPos(oldX, m_TabTransitionY, true);
		}

		if (m_TabTransitionStep >= TAB_TRANSITION_STEPS)
		{
			// Snap and cleanup
			m_TabTransitionNew.SetPos(0, m_TabTransitionY, true);
			if (m_TabTransitionOld)
			{
				m_TabTransitionOld.SetPos(-m_TabTransitionOffX, m_TabTransitionY, true);
				m_TabTransitionOld.Show(false);
			}

			g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(DoTabTransitionStep);
			m_TabTransitioning = false;
			m_TabTransitionStep = 0;
			m_TabTransitionOld = null;
			m_TabTransitionNew = null;
		}
	}

	private void ScheduleTabScrollResets()
	{
		// Defer scroll reset so content sizes are valid.
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(ApplyTabScrollResets);
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(ApplyTabScrollResetsDelayed);
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(ApplyTabScrollResets, 0, false);
		// Second pass: fit RichText + reset scroll after layout (HTML / tab visibility).
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(ApplyTabScrollResetsDelayed, 50, false);
	}

	private void ApplyTabScrollResets()
	{
		if (m_TabScroll0)
			m_TabScroll0.VScrollToPos01(0);
		if (m_TabScroll1)
			m_TabScroll1.VScrollToPos01(0);
		if (m_TabScroll2)
			m_TabScroll2.VScrollToPos01(0);
		if (m_TabScroll3)
			m_TabScroll3.VScrollToPos01(0);
	}

	private void ApplyTabScrollResetsDelayed()
	{
		// Long HTML RichText can update its layout a frame later.
		// Fit the RichText height to content once, per tab, when it is actually visible.
		if (m_ActiveTabIndex == 0 && !m_TabContentFitted0)
		{
			FitRichTextToContent(m_TextTab0, m_TabScroll0);
			m_TabContentFitted0 = true;
		}
		else if (m_ActiveTabIndex == 1 && !m_TabContentFitted1)
		{
			FitRichTextToContent(m_TextTab1, m_TabScroll1);
			m_TabContentFitted1 = true;
		}
		else if (m_ActiveTabIndex == 2 && !m_TabContentFitted2)
		{
			FitRichTextToContent(m_TextTab2, m_TabScroll2);
			m_TabContentFitted2 = true;
		}
		else if (m_ActiveTabIndex == 3 && !m_TabContentFitted3)
		{
			FitRichTextToContent(m_TextTab3, m_TabScroll3);
			m_TabContentFitted3 = true;
		}
		ApplyTabScrollResets();
	}

	private void FitRichTextToContent(RichTextWidget widget, ScrollWidget scrollParent)
	{
		if (!widget)
			return;

		// Layout must not use "size to text v" or it overrides scripted height.
		float wPx;
		float hPx;
		widget.GetScreenSize(wPx, hPx);
		if (wPx <= 1)
			return;

		widget.ClearFlags(WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE);
		widget.SetFlags(WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE);
		widget.SetSize(wPx, hPx);
		widget.Update();

		float contentH = widget.GetContentHeight();
		if (contentH <= 0)
			return;

		int numLines = widget.GetNumLines();
		float pad = 16.0;
		if (numLines > 0)
		{
			float lineH = contentH / numLines;
			float extra = lineH * 2.0;
			if (extra > pad)
				pad = extra;
		}

		float targetH = Math.Ceil(contentH + pad);
		widget.SetSize(wPx, targetH);
		widget.Update();
		if (scrollParent)
			scrollParent.Update();
	}

	void Back() {
		// Reset input and re-enable player controls when closing the menu
		g_Game.GetInput().ResetGameFocus();
		g_Game.GetMission().PlayerControlEnable(true);
		g_Game.GetUIManager().Back();
		g_Game.GetMission().GetHud().Show(true);
		g_Game.GetUIManager().ShowCursor(false);

		//Player = PlayerBase.Cast(g_Game.GetPlayer());

		// Re-enable all player actions
		if (Player)
			Player.GetInputController().SetDisabled(false);
	}

	void Hide()	
	{
		//SetFocus(NULL);
		OnHide();
		//layoutRoot.Show(false);
	}

	override void OnHide() 
	{
		super.OnHide();

		// Hide the layout
		layoutRoot.Show(false);

		// Stop any scheduled UI updates
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(UpdateHeader);

		if (m_DisplayPlayerTab && m_PlayerInfoDisplay) {
			m_PlayerInfoDisplay.OnMenuHide();
		}
	}

	override void OnShow() 
	{

		super.OnShow();

		// Re-fit static tab content once per menu open (per tab, when shown).
		m_TabContentFitted0 = false;
		m_TabContentFitted1 = false;
		m_TabContentFitted2 = false;
		m_TabContentFitted3 = false;

		ResetSidePanelUiCache();

		if (m_DisplayPlayerTab && m_PlayerInfoDisplay) {
			m_PlayerInfoDisplay.OnMenuShow();
		}

		if (m_DisplayCraftingTab && m_CraftingDisplay && m_ActiveTabIndex == 4) {
			m_CraftingDisplay.EnsureRecipesLoadedOnce();
		}

		// Re-initialiser le joueur au cas où l'objet aurait changé
		//Player = PlayerBase.Cast(g_Game.GetPlayer());

		if (m_DisplayPlayerTab || m_DisplaySidePanel) {
			GetRPCManager().SendRPC("ServerPanelStatsRPC", "SyncPanelStatsRequest", new Param1<int>(0), true, NULL);
		}

		layoutRoot.Show(true); // Show the layout

		ScheduleTabScrollResets();

		// Schedule updates and refreshing UI elements
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(UpdateHeader, 1000, true);

		if (config.DISPLAYCURRENCY)
		{
#ifdef EXPANSIONMODMARKET
			DisplayPlayerMoney();
#endif	
		}
	}

	/*private void TransitionTab(Widget newTab, Widget oldTab)	{
		Transitioning = true;
		float width, height, x, y;
		m_CurrentTabPanel.GetSize(width, height); 
		m_CurrentTabPanel.GetPos(x, y);
		float neededX = (x - width) - TAB_OFFSET;

		float stepSize = neededX / TRANSITION_ANIMATION_STEPS;

		currentTransitionStep = 0;
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(TransitionStep, 10, true, newTab, oldTab, stepSize);

		m_CurrentTabPanel = newTab;
	}*/

	/*private void TransitionStep(Widget newTab, Widget oldTab, float stepSize)	{
		currentTransitionStep++;
		float x, y;
		oldTab.GetPos(x, y);
		oldTab.SetPos((x - stepSize), y, true);
		newTab.GetPos(x, y);
		newTab.SetPos((x - stepSize), y, true);
		//Don't even fucking ask .... callLater seems to break if statement number comparison
		if (currentTransitionStep.ToString() == TRANSITION_ANIMATION_STEPS.ToString())		{
			g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(TransitionStep);
			newTab.SetPos(centerX, y, true);
			oldTab.SetPos(leftX, y, true);
			Transitioning = false;
		}
	}*/

	void UpdateBloodDisplay(float sBlood) 
	{
		// Mettre à jour les icônes de gouttes de sang en fonction des niveaux de sang
		if (sBlood > PlayerConstants.SL_BLOOD_HIGH) {
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 0, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 1, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 2, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 3, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
		} else if (sBlood > PlayerConstants.SL_BLOOD_NORMAL) {
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 0, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 1, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 2, "set:dayz_gui image:iconBlood2", ServerPanelConstants.WHITE);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 3, "set:dayz_gui image:iconBlood4", ServerPanelConstants.WHITE);
		} else if (sBlood > PlayerConstants.SL_BLOOD_LOW) {
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 0, "set:dayz_gui image:iconBlood0", ServerPanelConstants.YELLOW);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 1, "set:dayz_gui image:iconBlood2", ServerPanelConstants.YELLOW);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 2, "set:dayz_gui image:iconBlood4", ServerPanelConstants.YELLOW);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 3, "set:dayz_gui image:iconBlood4", ServerPanelConstants.YELLOW);
		} else if (sBlood > PlayerConstants.SL_BLOOD_CRITICAL) {
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 0, "set:dayz_gui image:iconBlood2", ServerPanelConstants.ORANGE);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 1, "set:dayz_gui image:iconBlood4", ServerPanelConstants.ORANGE);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 2, "set:dayz_gui image:iconBlood4", ServerPanelConstants.ORANGE);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 3, "set:dayz_gui image:iconBlood4", ServerPanelConstants.ORANGE);
		} else {
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 0, "set:dayz_gui image:iconBlood4", ServerPanelConstants.RED);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 1, "set:dayz_gui image:iconBlood4", ServerPanelConstants.RED);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 2, "set:dayz_gui image:iconBlood4", ServerPanelConstants.RED);
			SetIconState(m_BloodIcons, m_BloodIconPathsCache, m_BloodIconColorsCache, 3, "set:dayz_gui image:iconBlood4", ServerPanelConstants.RED);
		}
	}	
	void UpdateWaterDisplay(float sWater) 
	{
		// Mettre à jour les icônes de bouteilles d'eau en fonction des niveaux d'eau
		if (sWater >= PlayerConstants.SL_WATER_HIGH) {
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 0, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 1, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 2, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 3, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
		} else if (sWater > PlayerConstants.SL_WATER_NORMAL) {
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 0, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 1, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 2, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 3, "set:dayz_gui image:iconThirsty2", ServerPanelConstants.WHITE);
		} else if (sWater > PlayerConstants.SL_WATER_LOW) {
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 0, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.YELLOW);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 1, "set:dayz_gui image:iconThirsty2", ServerPanelConstants.YELLOW);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 2, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.YELLOW);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 3, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.YELLOW);
		} else if (sWater > PlayerConstants.SL_WATER_CRITICAL) {
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 0, "set:dayz_gui image:iconThirsty2", ServerPanelConstants.ORANGE);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 1, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.ORANGE);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 2, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.ORANGE);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 3, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.ORANGE);
		} else {
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 0, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.RED);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 1, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.RED);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 2, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.RED);
			SetIconState(m_WaterIcons, m_WaterIconPathsCache, m_WaterIconColorsCache, 3, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.RED);
		}
	}
	void UpdateFoodDisplay(float sEnergy) 
	{
		// Mettre à jour les icônes de nourriture en fonction des niveaux d'énergie
		if (sEnergy >= PlayerConstants.SL_ENERGY_HIGH) {
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 0, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 1, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 2, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 3, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);

		} else if (sEnergy >= PlayerConstants.SL_ENERGY_NORMAL) {
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 0, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 1, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 2, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 3, "set:dayz_gui image:iconHungry4", ServerPanelConstants.WHITE);

		} else if (sEnergy >= PlayerConstants.SL_ENERGY_LOW) {
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 0, "set:dayz_gui image:iconHungry0", ServerPanelConstants.YELLOW);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 1, "set:dayz_gui image:iconHungry2", ServerPanelConstants.YELLOW);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 2, "set:dayz_gui image:iconHungry4", ServerPanelConstants.YELLOW);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 3, "set:dayz_gui image:iconHungry4", ServerPanelConstants.YELLOW);

		} else if (sEnergy > PlayerConstants.SL_ENERGY_CRITICAL) {
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 0, "set:dayz_gui image:iconHungry2", ServerPanelConstants.ORANGE);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 1, "set:dayz_gui image:iconHungry4", ServerPanelConstants.ORANGE);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 2, "set:dayz_gui image:iconHungry4", ServerPanelConstants.ORANGE);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 3, "set:dayz_gui image:iconHungry4", ServerPanelConstants.ORANGE);

		} else {
			// Critical state: set blinking
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 0, "set:dayz_gui image:iconHungry4", ServerPanelConstants.RED);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 1, "set:dayz_gui image:iconHungry4", ServerPanelConstants.RED);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 2, "set:dayz_gui image:iconHungry4", ServerPanelConstants.RED);
			SetIconState(m_FoodIcons, m_FoodIconPathsCache, m_FoodIconColorsCache, 3, "set:dayz_gui image:iconHungry4", ServerPanelConstants.RED);
		}
	}
	void SetIconState(array<ImageWidget> icons, TStringArray pathCache, TIntArray colorCache, int index, string imagePath, int color) 
	{
		if (!icons || !pathCache || !colorCache) {
			return;
		}

		if (index < 0 || index >= icons.Count() || index >= pathCache.Count() || index >= colorCache.Count()) {
			return;
		}

		ImageWidget icon = icons.Get(index);
		if (!icon) {
			return;
		}

		if (pathCache.Get(index) != imagePath) {
			icon.LoadImageFile(0, imagePath);
			pathCache.Set(index, imagePath);
		}

		if (colorCache.Get(index) != color) {
			icon.SetColor(color);
			colorCache.Set(index, color);
		}
	}

	private void InitSidePanelIconCache()
	{
		m_BloodIcons = new array<ImageWidget>();
		m_WaterIcons = new array<ImageWidget>();
		m_FoodIcons = new array<ImageWidget>();
		m_BloodIconPathsCache = new TStringArray();
		m_WaterIconPathsCache = new TStringArray();
		m_FoodIconPathsCache = new TStringArray();
		m_BloodIconColorsCache = new TIntArray();
		m_WaterIconColorsCache = new TIntArray();
		m_FoodIconColorsCache = new TIntArray();

		for (int i = 0; i < 4; i++) {
			m_BloodIcons.Insert(ImageWidget.Cast(layoutRoot.FindAnyWidget("BloodImageWidget" + i.ToString())));
			m_WaterIcons.Insert(ImageWidget.Cast(layoutRoot.FindAnyWidget("WaterImageWidget" + i.ToString())));
			m_FoodIcons.Insert(ImageWidget.Cast(layoutRoot.FindAnyWidget("FoodImageWidget" + i.ToString())));

			m_BloodIconPathsCache.Insert("");
			m_WaterIconPathsCache.Insert("");
			m_FoodIconPathsCache.Insert("");

			m_BloodIconColorsCache.Insert(-1);
			m_WaterIconColorsCache.Insert(-1);
			m_FoodIconColorsCache.Insert(-1);
		}
	}

	private void UpdateHeader() 
	{		
		string header = "#STR_SP_TITLE" + " | " + GetFormattedDateTime();
		m_TitlePanel.SetText(header);
	}

	string GetFormattedDateTime()
	{
		int year, month, day, hour, minute, second;
		GetHourMinuteSecond(hour, minute, second);
		GetYearMonthDay(year, month, day);

		//DayZGame game = DayZGame.Cast(g_Game);
		int langIdx = g_Game.GetDisplayLanguage();
		string formattedDate;

		switch (langIdx)
		{
			// MM/DD/YYYY | HH:MM
			case 0: // ENGLISH
			case 1: // FRENCH
			case 2: // SPANISH
			case 3: // ITALIAN
			case 11: // PORTUGUESE
				formattedDate = day.ToString() + "/" + month.ToString() + "/" + year.ToString() + " | " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
				break;

			// DD.MM.YYYY | HH:MM
			case 4: // GERMAN
			case 5: // CZECH
			case 6: // RUSSIAN
			case 9: // POLISH
				formattedDate = day.ToString() + "." + month.ToString() + "." + year.ToString() + " | " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
				break;

			// YYYY年MM月DD日 | HH:MM
			case 7: // CHINESE_TRADITIONAL
			case 8: // CHINESE_SIMPLIFIED
			case 10: // JAPANESE
				formattedDate = year.ToString() + "年" + month.ToString() + "月" + day.ToString() + "日 | " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
				break;

			// Default format if none matches
			default:
				formattedDate = day.ToString() + "/" + month.ToString() + "/" + year.ToString() + " | " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
				break;
		}

		return formattedDate;
	}
};