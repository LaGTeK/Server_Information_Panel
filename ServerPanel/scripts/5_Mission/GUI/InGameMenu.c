/*modded class InGameMenu
{
	void RegisterButtons()
	{
		super.RegisterButtons();
		
		RegisterButton( "SERVER INFORMATION", "EnterServerPanelMenu" );
	}
	
	void EnterServerPanelMenu() {
		EnterScriptedMenu(SERVER_PANEL);
	}
}*/
/*modded class InGameMenu
{
	protected Widget m_ServerpanelButton;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("ServerPanel/scripts/gui/layouts/ingamemenu.layout");

		m_ServerpanelButton	= layoutRoot.FindAnyWidget( "ServerPanelbtn" );		
		m_ContinueButton	= layoutRoot.FindAnyWidget( "continuebtn" );
		m_ExitButton		= layoutRoot.FindAnyWidget( "exitbtn" );
		m_RestartButton		= layoutRoot.FindAnyWidget( "restartbtn" );
		m_RestartDeadButton	= layoutRoot.FindAnyWidget( "restartdeadbtn" );
		m_OptionsButton		= layoutRoot.FindAnyWidget( "optionsbtn" );
		m_HintPanel			= new UiHintPanel(layoutRoot.FindAnyWidget( "hint_frame" ));
		
		
		if (GetGame().IsMultiplayer())
		{
			ButtonSetText(m_RestartButton, "#main_menu_respawn");
		}
		else
		{
			ButtonSetText(m_RestartButton, "#main_menu_restart");
		}		
		
	#ifdef BULDOZER		
		delete m_RestartButton;
	#endif
		
		HudShow( false );
		
		SetGameVersion();
		
		//m_Root.SetHandler( this );
		
		return layoutRoot;
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);
		
		if ( w == m_ServerpanelButton )
		{
			EnterServerPanelMenu();
			return true;
		}

		return false;
	}
	
	void EnterServerPanelMenu() {
		EnterScriptedMenu(SERVER_PANEL);
	}
}*/

modded class InGameMenu
{
    protected Widget 	m_CustomButton;
	protected Widget 	m_Top;

    override Widget Init()
    {
        super.Init();
		
		m_Top 		     = layoutRoot.FindAnyWidget( "top" );   
		m_CustomButton	 = GetGame().GetWorkspace().CreateWidgets( "ServerPanel/scripts/gui/Layouts/InGameMenuButton.layout", m_Top);
		m_Top.Update();
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( m_CustomButton,  this, "MouseButtonDown" );
        return layoutRoot;
    }
	
	void MouseButtonDown( Widget w, int x, int y, int button)
	{
		if (w == m_CustomButton)
		{
			EnterScriptedMenu(SERVER_PANEL);
		}
	}
};
