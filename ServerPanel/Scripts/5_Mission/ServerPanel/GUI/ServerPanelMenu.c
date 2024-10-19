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
	//bool m_LogLevel;//Current Tab

	Widget 								m_CurrentTabPanel;
	ServerPanelTab 						m_CurrentTab;

	//Transition
	int currentTransitionStep;
	float centerX, leftX;
	bool Transitioning 						= false;
	const int TRANSITION_ANIMATION_STEPS 	= 40;
	const float TAB_OFFSET 					= 0.05;

	void ServerPanelMenu()	{
		config = GetServerPanelServerConfig();	
		m_DisplayPlayerTab 		= config.DISPLAYPLAYERTAB;	
		m_DisplayCraftingTab 	= config.DISPLAYCRAFTTAB;	
		m_DisplayPlayerList 	= config.DISPLAYPLAYERLIST;		
		m_DisplaySidePanel		= config.DISPLAYPLAYERINFO;

		// Initialiser le Player une seule fois dans le constructeur
		Player = PlayerBase.Cast(g_Game.GetPlayer());

        m_CraftingDisplay = new CraftingDisplay(); // Initialize crafting display

        m_PlayerInfoDisplay = new PlayerInfoDisplay(Player);  // Passe l'instance du joueur à PlayerInfoDisplay
	}

	override Widget Init()	{	
		layoutRoot 						=	GetGame().GetWorkspace().CreateWidgets( "ServerPanel/GUI/layouts/ServerPanel.layout" );
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

		//Player Information Right Side
		m_TextPlayerNickname			=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_Nickname" ) );
		m_TextPlayerHealth 				=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_health" ) );
		m_TextPlayerPos 				=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_position" ) );
		m_PlayerTitle 					=	TextWidget.Cast( layoutRoot.FindAnyWidget( "OnlinePlayerTitle" ) );
		//m_TextPlayerBlood 				=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_blood" ) );
		//m_TextPlayerWater 				=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_water" ) );
		//m_TextPlayerEnergy 				=	TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_food" ) );

		m_PlayerListScrollWidget		=	ScrollWidget.Cast( layoutRoot.FindAnyWidget( "PlayerListScrollWidget" ) );
		m_PlayersList 					=	MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "Player_List" ) );

		//Tab Transisition
		m_CurrentTab 					=	ServerPanelTab.Tab0;
		m_CurrentTabPanel 				=	m_Tab0;

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
		m_Tab5.SetPos(neededX, y, true);

		//Money Widget
		//EXPANSIONMARKET
		m_MoneyPanelWidget				=	Widget.Cast(layoutRoot.FindAnyWidget("MoneyPanelWidget"));
		m_CurrencyTextWidget 			=	TextWidget.Cast( layoutRoot.FindAnyWidget("CurrencyTextWidget"));
		m_CurrencyIconWidget			=	ImageWidget.Cast(layoutRoot.FindAnyWidget("CurrencyIconWidget"));
		
		m_MoneyPanelWidget.Show(false);

		//Settings & Title
		UpdateHeader();
		FillFilesInformations();		

		if (m_DisplayCraftingTab) {
            m_CraftingDisplay.Init(layoutRoot);  // Delegate crafting UI to the CraftingDisplay class
        } else {
            m_Tab4.Show(false);
            m_btnTabTitle4.Show(false);
        }

		if (m_DisplayPlayerTab) {
            m_PlayerInfoDisplay.Init(layoutRoot);  // Delegate crafting UI to the CraftingDisplay class
        } else {
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
			int playerWorth = m_MarketModule.GetPlayerWorth(PlayerBase.Cast(GetGame().GetPlayer()), monies);

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

	void SyncPlayerStats(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) 
	{
		Param3<ref TIntArray, ref TFloatArray, bool> syncDataS;

		ref TIntArray PlayerDataI = new TIntArray;
		ref TFloatArray PlayerDataF = new TFloatArray;

		if (type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			if (!ctx.Read(syncDataS)) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "SyncPlayerStats", "Players sync data read error - possible version mismatch");
				return;
			}

			PlayerDataI = syncDataS.param1;
			PlayerDataF = syncDataS.param2;
			bool sDisease = syncDataS.param3;
		}

		m_PlayerInfoDisplay.UpdatePlayerInfo(PlayerDataI, PlayerDataF, sDisease);
	}

	void SyncSidePanelInfo(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) 
	{
		Param5<ref TStringArray, ref TIntArray, ref TFloatArray, vector, string> syncDataS;
		ref TStringArray PlayerListC = new TStringArray;
		ref TIntArray PlayerDataI = new TIntArray;
		ref TFloatArray PlayerDataF = new TFloatArray;

		int sHealth = 0;
		int sBlood = 0;
		float sEnergy = 0;
		float sWater = 0;
		string m_playerName ="";

		if (type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			if (!ctx.Read(syncDataS)) {
				ServerPanelLogger.Log(ServerPanelLogger.LOG_LEVEL_ERROR, "SyncSidePanelInfo", "Player sync data read error - possible version mismatch");
				return;
			}

			PlayerListC = syncDataS.param1;
			PlayerDataI = syncDataS.param2;
			PlayerDataF = syncDataS.param3;
			vector PlayerPos = syncDataS.param4;
			m_playerName = syncDataS.param5;

			if (PlayerDataI.Count() == 0) return;
		}

		// Set current player's stats
		sHealth = PlayerDataI[1];
		sBlood = PlayerDataI[2];
		sWater = PlayerDataF[0];
		sEnergy = PlayerDataF[1];

		if (layoutRoot.IsVisible()) {

			m_TextPlayerHealth.SetText(" " + sHealth.ToString());
			//m_TextPlayerBlood.SetText(" " + sBlood.ToString());

			m_TextPlayerNickname.SetText(m_playerName);

			if (m_DisplayPlayerList) {
				m_PlayerTitle.SetText("#STR_SP_ONLINE_PLAYERS_TXT" + ": " + PlayerListC.Count());
				int y = 1;
				string m_PlayerListText = "";
				for (int i = 0; i < PlayerListC.Count(); ++i) {
					m_PlayerListText += " " + y.ToString() + ": " + PlayerListC.Get(i) + "\n";  // Ajoutez \n pour un saut de ligne
					y++;
				}
				m_PlayersList.SetText(m_PlayerListText);
			}
			
			if (config.DISPLAYPLAYERPOSITION){
				m_TextPlayerPos.Show(true);
				m_TextPlayerPos.SetText("#STR_SP_POS_TXT" + " X: " + Math.Floor(PlayerPos[0]).ToString() + "  Y: " + Math.Floor(PlayerPos[2]).ToString());
			} else {
				m_TextPlayerPos.Show(false);
			}	

			// Health Color Coding based on PlayerConstants thresholds
			if (sHealth <= PlayerConstants.SL_HEALTH_CRITICAL) { 
				m_TextPlayerHealth.SetColor(ServerPanelConstants.RED); // Critical health
			} else if (sHealth <= PlayerConstants.SL_HEALTH_LOW) {
				m_TextPlayerHealth.SetColor(ServerPanelConstants.ORANGE); // Low health
			} else if (sHealth <= PlayerConstants.SL_HEALTH_NORMAL) {
				m_TextPlayerHealth.SetColor(ServerPanelConstants.YELLOW); // Normal health (moderate)
			} else if (sHealth <= PlayerConstants.SL_HEALTH_HIGH) {
				m_TextPlayerHealth.SetColor(ServerPanelConstants.WHITE); // High health
			} else {
				m_TextPlayerHealth.SetColor(ServerPanelConstants.WHITE); // Full health or above normal
			}

			// Blood Color Coding
			UpdateBloodDisplay(sBlood);

			// Energy Color Coding
			UpdateWaterDisplay(sWater);

			// Water Color Coding
			UpdateFoodDisplay(sEnergy);
		}
	}

	override void Update(float timeslice) {
		super.Update(timeslice);

		if (KeyState(KeyCode.KC_ESCAPE) == 1 || GetGame().GetInput().LocalRelease("SPOpenPanelMenu"))
			Back();

        // Update crafting display as needed
        if (m_DisplayCraftingTab) {
            m_CraftingDisplay.Update(timeslice);
        }

        // Autres mises à jour...
        if (m_DisplayPlayerTab) {
            m_PlayerInfoDisplay.Update(timeslice);  // Met à jour les infos du joueur
        }
	}
	override bool OnClick(Widget w, int x, int y, int button) {
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
			else if (w == m_btnTabTitle0 || w == m_btnTabTitle1 || w == m_btnTabTitle2 || w == m_btnTabTitle3 || w == m_btnTabTitle4 || w == m_btnTabTitle5)
			{
				OnBtnTabClick(w);
				return true;
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
	protected bool OnBtnTabClick(Widget w)	{
		if (Transitioning)
			return true;

		if (w == m_btnTabTitle0)	{
			if (m_CurrentTabPanel != m_Tab0){
				TransitionTab(m_Tab0, m_CurrentTabPanel);
				m_btnTabTitle0.SetColor(ServerPanelConstants.ACTIVE_BUTTON_COLOR);
				m_btnTabTitle1.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle2.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle3.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle4.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle5.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
			}

		}
		else if (w == m_btnTabTitle1)	{
			if (m_CurrentTabPanel != m_Tab1){
				TransitionTab(m_Tab1, m_CurrentTabPanel);
				m_btnTabTitle0.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle1.SetColor(ServerPanelConstants.ACTIVE_BUTTON_COLOR);
				m_btnTabTitle2.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle3.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle4.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle5.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
			}
		}
		else if (w == m_btnTabTitle2)	{
			if (m_CurrentTabPanel != m_Tab2){				
				TransitionTab(m_Tab2, m_CurrentTabPanel);
				m_btnTabTitle0.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle1.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle2.SetColor(ServerPanelConstants.ACTIVE_BUTTON_COLOR);
				m_btnTabTitle3.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle4.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle5.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
			}
		}
		else if (w == m_btnTabTitle3)	{
			if (m_CurrentTabPanel != m_Tab3) {
				TransitionTab(m_Tab3, m_CurrentTabPanel);
				m_btnTabTitle0.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle1.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle2.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle3.SetColor(ServerPanelConstants.ACTIVE_BUTTON_COLOR);
				m_btnTabTitle4.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle5.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
			}
		}
		else if (w == m_btnTabTitle4)	{
			if (m_CurrentTabPanel != m_Tab4){
				TransitionTab(m_Tab4, m_CurrentTabPanel);
				m_btnTabTitle0.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle1.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle2.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle3.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle4.SetColor(ServerPanelConstants.ACTIVE_BUTTON_COLOR);
				m_btnTabTitle5.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
			}
		}
		else if (w == m_btnTabTitle5)	{
			if (m_CurrentTabPanel != m_Tab5) {
				TransitionTab(m_Tab5, m_CurrentTabPanel);
				m_btnTabTitle0.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle1.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle2.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle3.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle4.SetColor(ServerPanelConstants.NORMAL_BUTTON_COLOR);
				m_btnTabTitle5.SetColor(ServerPanelConstants.ACTIVE_BUTTON_COLOR);
			}
		}
		return true;
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
	void Hide()	{
		//SetFocus(NULL);
		OnHide();
		//layoutRoot.Show(false);
	}
	override void OnHide() {
		super.OnHide();

		// Hide the layout
		layoutRoot.Show(false);

		// Stop any scheduled UI updates
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(UpdateHeader);
	}
	override void OnShow() {

		super.OnShow();

		// Re-initialiser le joueur au cas où l'objet aurait changé
		//Player = PlayerBase.Cast(g_Game.GetPlayer());

		// Request synchronization of player stats, as required for the panel display
		if (m_DisplayPlayerTab) {
			GetRPCManager().SendRPC("ServerPanelStatsRPC", "SyncPlayerStatsRequest", new Param1<int>(0), true, NULL);
		}

		if (m_DisplaySidePanel) {
			GetRPCManager().SendRPC("ServerPanelStatsRPC", "SyncSidePanelInfoRequest", new Param1<int>(0), true, NULL);
		}

		PerformWidgetAdjustments();

		layoutRoot.Show(true); // Show the layout

		// Schedule updates and refreshing UI elements
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(UpdateHeader, 1000, true);

		if (config.DISPLAYCURRENCY)
		{
#ifdef EXPANSIONMODMARKET
			DisplayPlayerMoney();
#endif	
		}
	}

	private void TransitionTab(Widget newTab, Widget oldTab)	{
		Transitioning = true;
		float width, height, x, y;
		m_CurrentTabPanel.GetSize(width, height); 
		m_CurrentTabPanel.GetPos(x, y);
		float neededX = (x - width) - TAB_OFFSET;

		float stepSize = neededX / TRANSITION_ANIMATION_STEPS;

		currentTransitionStep = 0;
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(TransitionStep, 10, true, newTab, oldTab, stepSize);

		m_CurrentTabPanel = newTab;
	}

	private void TransitionStep(Widget newTab, Widget oldTab, float stepSize)	{
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
	}

	void UpdateBloodDisplay(float sBlood) {
		// Création des widgets d'image pour le sang
		ImageWidget bloodIcon0 = ImageWidget.Cast(layoutRoot.FindAnyWidget("BloodImageWidget0"));
		ImageWidget bloodIcon1 = ImageWidget.Cast(layoutRoot.FindAnyWidget("BloodImageWidget1"));
		ImageWidget bloodIcon2 = ImageWidget.Cast(layoutRoot.FindAnyWidget("BloodImageWidget2"));
		ImageWidget bloodIcon3 = ImageWidget.Cast(layoutRoot.FindAnyWidget("BloodImageWidget3"));

		// Mettre à jour les icônes de gouttes de sang en fonction des niveaux de sang
		if (sBlood > PlayerConstants.SL_BLOOD_HIGH) {
			SetIconState(bloodIcon0, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(bloodIcon1, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(bloodIcon2, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(bloodIcon3, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
		} else if (sBlood > PlayerConstants.SL_BLOOD_NORMAL) {
			SetIconState(bloodIcon0, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(bloodIcon1, "set:dayz_gui image:iconBlood0", ServerPanelConstants.WHITE);
			SetIconState(bloodIcon2, "set:dayz_gui image:iconBlood2", ServerPanelConstants.WHITE);
			SetIconState(bloodIcon3, "set:dayz_gui image:iconBlood4", ServerPanelConstants.WHITE);
		} else if (sBlood > PlayerConstants.SL_BLOOD_LOW) {
			SetIconState(bloodIcon0, "set:dayz_gui image:iconBlood0", ServerPanelConstants.YELLOW);
			SetIconState(bloodIcon1, "set:dayz_gui image:iconBlood2", ServerPanelConstants.YELLOW);
			SetIconState(bloodIcon2, "set:dayz_gui image:iconBlood4", ServerPanelConstants.YELLOW);
			SetIconState(bloodIcon3, "set:dayz_gui image:iconBlood4", ServerPanelConstants.YELLOW);
		} else if (sBlood > PlayerConstants.SL_BLOOD_CRITICAL) {
			SetIconState(bloodIcon0, "set:dayz_gui image:iconBlood2", ServerPanelConstants.ORANGE);
			SetIconState(bloodIcon1, "set:dayz_gui image:iconBlood4", ServerPanelConstants.ORANGE);
			SetIconState(bloodIcon2, "set:dayz_gui image:iconBlood4", ServerPanelConstants.ORANGE);
			SetIconState(bloodIcon3, "set:dayz_gui image:iconBlood4", ServerPanelConstants.ORANGE);
		} else {
			SetIconState(bloodIcon0, "set:dayz_gui image:iconBlood4", ServerPanelConstants.RED);
			SetIconState(bloodIcon1, "set:dayz_gui image:iconBlood4", ServerPanelConstants.RED);
			SetIconState(bloodIcon2, "set:dayz_gui image:iconBlood4", ServerPanelConstants.RED);
			SetIconState(bloodIcon3, "set:dayz_gui image:iconBlood4", ServerPanelConstants.RED);
		}
	}	
	void UpdateWaterDisplay(float sWater) {
		// Création des widgets d'image pour l'eau
		ImageWidget waterIcon0 = ImageWidget.Cast(layoutRoot.FindAnyWidget("WaterImageWidget0"));
		ImageWidget waterIcon1 = ImageWidget.Cast(layoutRoot.FindAnyWidget("WaterImageWidget1"));
		ImageWidget waterIcon2 = ImageWidget.Cast(layoutRoot.FindAnyWidget("WaterImageWidget2"));
		ImageWidget waterIcon3 = ImageWidget.Cast(layoutRoot.FindAnyWidget("WaterImageWidget3"));

		// Mettre à jour les icônes de bouteilles d'eau en fonction des niveaux d'eau
		if (sWater >= PlayerConstants.SL_WATER_HIGH) {
			SetIconState(waterIcon0, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(waterIcon1, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(waterIcon2, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(waterIcon3, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
		} else if (sWater > PlayerConstants.SL_WATER_NORMAL) {
			SetIconState(waterIcon0, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(waterIcon1, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(waterIcon2, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.WHITE);
			SetIconState(waterIcon3, "set:dayz_gui image:iconThirsty2", ServerPanelConstants.WHITE);
		} else if (sWater > PlayerConstants.SL_WATER_LOW) {
			SetIconState(waterIcon0, "set:dayz_gui image:iconThirsty0", ServerPanelConstants.YELLOW);
			SetIconState(waterIcon1, "set:dayz_gui image:iconThirsty2", ServerPanelConstants.YELLOW);
			SetIconState(waterIcon2, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.YELLOW);
			SetIconState(waterIcon3, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.YELLOW);
		} else if (sWater > PlayerConstants.SL_WATER_CRITICAL) {
			SetIconState(waterIcon0, "set:dayz_gui image:iconThirsty2", ServerPanelConstants.ORANGE);
			SetIconState(waterIcon1, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.ORANGE);
			SetIconState(waterIcon2, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.ORANGE);
			SetIconState(waterIcon3, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.ORANGE);
		} else {
			SetIconState(waterIcon0, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.RED);
			SetIconState(waterIcon1, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.RED);
			SetIconState(waterIcon2, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.RED);
			SetIconState(waterIcon3, "set:dayz_gui image:iconThirsty4", ServerPanelConstants.RED);
		}
	}
	void UpdateFoodDisplay(float sEnergy) {
		// Création des widgets d'image pour la nourriture
		ImageWidget foodIcon0 = ImageWidget.Cast(layoutRoot.FindAnyWidget("FoodImageWidget0"));
		ImageWidget foodIcon1 = ImageWidget.Cast(layoutRoot.FindAnyWidget("FoodImageWidget1"));
		ImageWidget foodIcon2 = ImageWidget.Cast(layoutRoot.FindAnyWidget("FoodImageWidget2"));
		ImageWidget foodIcon3 = ImageWidget.Cast(layoutRoot.FindAnyWidget("FoodImageWidget3"));

		// Mettre à jour les icônes de nourriture en fonction des niveaux d'énergie
		if (sEnergy >= PlayerConstants.SL_ENERGY_HIGH) {
			SetIconState(foodIcon0, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(foodIcon1, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(foodIcon2, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(foodIcon3, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);

		} else if (sEnergy >= PlayerConstants.SL_ENERGY_NORMAL) {
			SetIconState(foodIcon0, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(foodIcon1, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(foodIcon2, "set:dayz_gui image:iconHungry0", ServerPanelConstants.WHITE);
			SetIconState(foodIcon3, "set:dayz_gui image:iconHungry4", ServerPanelConstants.WHITE);

		} else if (sEnergy >= PlayerConstants.SL_ENERGY_LOW) {
			SetIconState(foodIcon0, "set:dayz_gui image:iconHungry0", ServerPanelConstants.YELLOW);
			SetIconState(foodIcon1, "set:dayz_gui image:iconHungry2", ServerPanelConstants.YELLOW);
			SetIconState(foodIcon2, "set:dayz_gui image:iconHungry4", ServerPanelConstants.YELLOW);
			SetIconState(foodIcon3, "set:dayz_gui image:iconHungry4", ServerPanelConstants.YELLOW);

		} else if (sEnergy > PlayerConstants.SL_ENERGY_CRITICAL) {
			SetIconState(foodIcon0, "set:dayz_gui image:iconHungry2", ServerPanelConstants.ORANGE);
			SetIconState(foodIcon1, "set:dayz_gui image:iconHungry4", ServerPanelConstants.ORANGE);
			SetIconState(foodIcon2, "set:dayz_gui image:iconHungry4", ServerPanelConstants.ORANGE);
			SetIconState(foodIcon3, "set:dayz_gui image:iconHungry4", ServerPanelConstants.ORANGE);

		} else {
			// Critical state: set blinking
			SetIconState(foodIcon0, "set:dayz_gui image:iconHungry4", ServerPanelConstants.RED);
			SetIconState(foodIcon1, "set:dayz_gui image:iconHungry4", ServerPanelConstants.RED);
			SetIconState(foodIcon2, "set:dayz_gui image:iconHungry4", ServerPanelConstants.RED);
			SetIconState(foodIcon3, "set:dayz_gui image:iconHungry4", ServerPanelConstants.RED);
		}
	}
	void SetIconState(ImageWidget icon, string imagePath, int color) {
		icon.LoadImageFile(0, imagePath);
		icon.SetColor(color);
	}

	//Due to wrong v size with some test i've to try to set up the height by myself
	// Fonction qui retourne la hauteur en pourcentage pour chaque ligne en fonction de son contenu
	float GetLineHeightPercentage(string lineText) {
		if (lineText.Contains("<h1>")) {
			return 12.15; // 5% pour <h1>
		} else if (lineText.Contains("<h2>")) {
			return 9.1; // 4% pour <h2>
		} else if (lineText.Contains("<p>")) {
			return 6.4; // 2% pour <p>
		} else {
			return 3.5; // 1% par défaut pour du texte sans balises spécifiques
		}
	}
	// Fonction pour ajuster la hauteur du widget RichText en fonction des balises HTML et du nombre de lignes
	void AdjustRichTextWidgetHeight(RichTextWidget widget, TStringArray lines) {
		float totalHeightPercentage = 0.0;

		// On parcourt chaque ligne du tableau `lines` pour calculer la hauteur totale en %
		for (int i = 0; i < lines.Count(); i++) {
			string line = lines.Get(i);
			totalHeightPercentage += GetLineHeightPercentage(line);
		}

		// Appliquer la nouvelle taille calculée au widget
		float width, currentHeight;
		widget.GetSize(width, currentHeight);
		widget.SetSize(width, totalHeightPercentage/100);
	}
	// Fonction pour appeler l'ajustement des widgets, avec les variables stockant le nombre de lignes
	void PerformWidgetAdjustments() {
		// Ajuster en fonction du contenu de chaque widget
		AdjustRichTextWidgetHeight(m_TextTab0, config.sServerTab0); // S'il s'agit d'un tableau de lignes
		AdjustRichTextWidgetHeight(m_TextTab1, config.sServerTab1);
		AdjustRichTextWidgetHeight(m_TextTab2, config.sServerTab2);
		AdjustRichTextWidgetHeight(m_TextTab3, config.sServerTab3);
	}

	private void UpdateHeader() {		
		string header = "#STR_SP_TITLE" + " | " + GetFormattedDateTime();
		m_TitlePanel.SetText(header);
	}

	string GetFormattedDateTime()
	{
		int year, month, day, hour, minute, second;
		GetHourMinuteSecond(hour, minute, second);
		GetYearMonthDay(year, month, day);

		//DayZGame game = DayZGame.Cast(GetGame());
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