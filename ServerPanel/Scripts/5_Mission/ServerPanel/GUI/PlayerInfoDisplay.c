class PlayerInfoDisplay {
	private Widget m_RootWidget;
	private PlayerBase m_Player; // Référence au joueur

	protected TextWidget 						m_Sex,m_Weight,m_BloodType,m_SurvivalTime,m_DistanceTravelled,m_PlayTime,m_TextPlayerBlood,m_TextPlayerHealth,m_ItemHands,m_ServerTime,m_Condition,m_ZKilled,m_PKilled,m_LongestShot;

	protected ProgressBarWidget					m_HealthBar,m_BloodBar,m_ShockBar,m_StaminaBar;
	
	//Player Preview
	protected PlayerPreviewWidget				m_PlayerPreview;
	
	protected vector m_ItemOrientation;
	protected int m_ItemRotationX;
	protected int m_ItemRotationY;
	protected Widget m_SelectedPreviewWidget;

	//Item Preview
	protected ItemPreviewWidget					m_ItemPreview;
	protected ImageWidget 						m_ImgNight,m_ImgSun,m_ImgCloud,m_ImgStorm,m_ImgRain,m_ImgFog,m_ImgWind;

	void PlayerInfoDisplay(PlayerBase player) {
		m_Player = player;
		
		// Appels à CallLater pour des mises à jour périodiques ou uniques
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.ServerDate, 10000, true);  // Appelle ServerDate toutes les 10 secondes
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SessionTime, 1000, true);     // Appelle SessionTime une seule fois après 10000 ms soit 10s
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SPPlayerPreview, 500, false); // Appelle SPPlayerPreview une seule fois après 500 ms
		
	}

	void ~PlayerInfoDisplay() {
		// Retirer les appels CallLater lorsqu'on détruit l'instance
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(this.ServerDate);
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(this.SessionTime);
		g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(this.SPPlayerPreview);
	}

	void Init(Widget rootWidget) {
		m_RootWidget = GetGame().GetWorkspace().CreateWidgets("ServerPanel/GUI/layouts/PlayerInfoDisplay.layout", rootWidget.FindAnyWidget("Tab_5"));
		
		// Initialize UI elements
		m_Sex                           = TextWidget.Cast(m_RootWidget.FindAnyWidget("txt_sex"));
		m_Weight                        = TextWidget.Cast(m_RootWidget.FindAnyWidget("txt_weight"));
		m_BloodType                     = TextWidget.Cast(m_RootWidget.FindAnyWidget("txt_bloodType"));
		m_SurvivalTime                  = TextWidget.Cast(m_RootWidget.FindAnyWidget("txt_survivalTime"));
		m_DistanceTravelled             = TextWidget.Cast(m_RootWidget.FindAnyWidget("txt_distance"));

		m_ItemHands 					=	TextWidget.Cast(m_RootWidget.FindAnyWidget("txt_itemhands"));
		m_PlayTime 						=	TextWidget.Cast( m_RootWidget.FindAnyWidget( "txt_playtime" ) );
		m_Condition 					=	TextWidget.Cast( m_RootWidget.FindAnyWidget( "txt_disease" ) );
		//m_Direction					=	TextWidget.Cast( m_RootWidget.FindAnyWidget( "txt_direction" ) );
		m_ZKilled						=	TextWidget.Cast( m_RootWidget.FindAnyWidget( "txt_zKilled" ) );
		m_PKilled						=	TextWidget.Cast( m_RootWidget.FindAnyWidget( "txt_pKilled" ) );
		m_LongestShot					=	TextWidget.Cast( m_RootWidget.FindAnyWidget( "txt_longestShot" ) );
		m_ServerTime					=	TextWidget.Cast( m_RootWidget.FindAnyWidget( "txt_serverTime" ));

		// Health, Blood, and other progress bars
		m_HealthBar                     = ProgressBarWidget.Cast(m_RootWidget.FindAnyWidget("HealthBar"));
		m_BloodBar                      = ProgressBarWidget.Cast(m_RootWidget.FindAnyWidget("BloodBar"));
		m_ShockBar                      = ProgressBarWidget.Cast(m_RootWidget.FindAnyWidget("ShockBar"));
		m_StaminaBar                    = ProgressBarWidget.Cast(m_RootWidget.FindAnyWidget("StaminaBar"));
		
		//Preview Widget
		m_PlayerPreview 				=	PlayerPreviewWidget.Cast( m_RootWidget.FindAnyWidget( "PlayerPreview" ) );
		m_ItemPreview					=	ItemPreviewWidget.Cast( m_RootWidget.FindAnyWidget( "ItemPreview" ) );
		
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(m_ItemPreview, this, "OnMouseButtonDown");
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(m_PlayerPreview, this, "OnMouseButtonDown");		

		DisplayPlayerTotalWeight();
		SPBloodName();
		ServerDate();
		SessionTime();
		SPGender();
	}

	// Méthode pour recevoir les données du joueur
	void UpdatePlayerInfo(ref TIntArray PlayerDataI, ref TFloatArray PlayerDataF, bool sDisease)
	{
		int sHealth = PlayerDataI[0];
		int sBlood = PlayerDataI[1];
		float sShock = PlayerDataF[0];
		float sStamina = PlayerDataF[1];
		float sDistance = PlayerDataF[2];
		float sPlaytime = PlayerDataF[3];
		float sPlayers_killed = PlayerDataF[4];
		float sInfected_killed = PlayerDataF[5];
		float sLongest_survivor_hit = PlayerDataF[6];

		m_HealthBar.SetCurrent(sHealth);
		m_BloodBar.SetCurrent(sBlood);
		m_ShockBar.SetCurrent(sShock);
		m_StaminaBar.SetCurrent(sStamina);

		m_LongestShot.SetText(GetDistanceString(sLongest_survivor_hit));
		m_PKilled.SetText(GetValueString(sPlayers_killed));
		m_ZKilled.SetText(GetValueString(sInfected_killed));
		m_DistanceTravelled.SetText(GetDistanceString(sDistance));

		
		if (sDisease)
			m_Condition.SetText("#STR_SP_DISEASE_SICK");
		else
			m_Condition.SetText("#STR_SP_DISEASE_GOOD");


		int days = sPlaytime / 86400; // 86400 = nombre de secondes dans une journée
		int remainingTime = sPlaytime - (days * 86400); // Soustraire le temps utilisé pour les jours

		int hours = remainingTime / 3600; // 3600 = nombre de secondes dans une heure
		remainingTime = remainingTime - (hours * 3600); // Soustraire le temps utilisé pour les heures

		int minutes = remainingTime / 60; // 60 = nombre de secondes dans une minute
		int seconds = remainingTime - (minutes * 60); // Ce qui reste sont les secondes

		m_SurvivalTime.SetText("" + days + "#STR_time_unit_abbrev_day_0 " + hours + "#STR_time_unit_abbrev_hour_0 " + minutes + "#STR_time_unit_abbrev_minute_0 " + seconds + "#STR_time_unit_abbrev_second_0");

		// Blood Color Coding
		if (sBlood <= 3000) {
			//m_TextPlayerBlood.SetColor(ServerPanelConstants.RED);
		} else if (sBlood <= 3500) {
			m_BloodBar.SetColor(ServerPanelConstants.ORANGE);
		} else if (sBlood <= 4000) {
			m_BloodBar.SetColor(ServerPanelConstants.YELLOW);
		} else if (sBlood <= 4500) {
			m_BloodBar.SetColor(ServerPanelConstants.GREEN);
		}			

		// Health Color Coding based on PlayerConstants thresholds
		if (sHealth <= PlayerConstants.SL_HEALTH_LOW) {
			m_HealthBar.SetColor(ServerPanelConstants.ORANGE);
		} else if (sHealth <= PlayerConstants.SL_HEALTH_NORMAL) {
			m_HealthBar.SetColor(ServerPanelConstants.YELLOW);
		}
	}

	void Update(float timeslice) {
		// Logic for updating player information dynamically
	}

	// Other methods to handle player info display updates

	private void DisplayPlayerTotalWeight()
	{
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			// Récupérer le poids total en incluant l'objet en main
			float totalWeight = m_Player.GetPlayerLoad(); // Le poids est en grammes

			string weightText = "";

			// Afficher le poids de manière lisible
			if (totalWeight >= 1000) {
				int kilos = Math.Round(totalWeight / 1000.0);
				weightText = "#inv_inspect_about" + " " + kilos.ToString() + " " + "#inv_inspect_kg";
			} else if (totalWeight >= 500) {
				weightText = "#inv_inspect_under_1";
			} else if (totalWeight >= 250) {
				weightText = "#inv_inspect_under_05";
			} else {
				weightText = "#inv_inspect_under_025";
			}

			// Mettre à jour l'affichage du poids
			m_Weight.SetText(weightText);

			// Vérifier si le joueur est en surcharge
			if (m_Player.IsOverloaded()) {
				m_Weight.SetColor(ServerPanelConstants.RED);
			} else {
				m_Weight.SetColor(ServerPanelConstants.WHITE);
			}
		}
	}

	private void SPGender()	{
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())	{
			if (m_Player){
				if (m_Player.IsMale() )
					m_Sex.SetText("#STR_SP_MALE_GENDER");
				else
					m_Sex.SetText("#STR_SP_FEMALE_GENDER");
			}
		}
	}

	private void SPBloodName()	{
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())	{
			Class.CastTo(m_Player, g_Game.GetPlayer() );
			
			if( m_Player )	{
				string blood_name;
				bool positive;
				BloodTypes.GetBloodTypeName( m_Player.GetBloodType(), blood_name, positive );
				bool blood_type_visible = m_Player.HasBloodTypeVisible();
				
				if( blood_type_visible )	{
					if( positive )
						m_BloodType.SetText( blood_name + "+");
					else
						m_BloodType.SetText( blood_name + "-");
				}
				else	{
					m_BloodType.SetText("#STR_SP_UNKNOWN_BLOOD_GROUP");
				}
			}
		}
	}

	private void ServerDate() {
		string m_ServerDateTime = GetFormattedServerDateTime();
		m_ServerTime.SetText(m_ServerDateTime);
	}

	string GetFormattedServerDateTime()
	{
		int year, month, day, hour, minute;
		g_Game.GetWorld().GetDate(year, month, day, hour, minute);

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
				formattedDate = day.ToString() + "/" + month.ToString() + "/" + year.ToString() + " | " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
				break;

			// DD.MM.YYYY | HH:MM
			case 4: // GERMAN
			case 5: // CZECH
			case 6: // RUSSIAN
			case 9: // POLISH
				formattedDate = day.ToString() + "." + month.ToString() + "." + year.ToString() + " | " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
				break;

			// YYYY年MM月DD日 | HH:MM
			case 7: // CHINESE_TRADITIONAL
			case 8: // CHINESE_SIMPLIFIED
			case 10: // JAPANESE
				formattedDate = year.ToString() + "年" + month.ToString() + "月" + day.ToString() + "日 | " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
				break;

			// Default format if none matches
			default:
				formattedDate = day.ToString() + "/" + month.ToString() + "/" + year.ToString() + " | " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
				break;
		}

		return formattedDate;
	}

	private void SessionTime() {
		int sUpTimeBis = Math.Round(g_Game.GetTime() / 1000);

		int sHours = Math.Floor(sUpTimeBis / 3600);
		int sMinutes = Math.Floor(sUpTimeBis / 60) - (sHours * 60);  // Utilise une soustraction au lieu de %
		int sSeconds = sUpTimeBis - (sHours * 3600) - (sMinutes * 60);

		m_PlayTime.SetText("" + sHours.ToStringLen(2) + "#STR_time_unit_abbrev_hour_0" + " " + sMinutes.ToStringLen(2) + "#STR_time_unit_abbrev_minute_0" + " " + sSeconds.ToStringLen(2) + "#STR_time_unit_abbrev_second_0");
	}

	/*private void SPItemPreview()	{
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())	{
			if (m_Player.GetItemInHands()) m_ItemPreview.SetItem(m_Player.GetItemInHands());
		}
	}*/

	/*private void UpdateItemPreview(ItemPreviewWidget widget, EntityAI item) {
		if(GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			if (widget && item) {
				widget.SetItem(item);
			} else {
				widget.SetItem(null);  // Effacer si l'élément n'existe pas
			}
		}
	}*/

	private void SPPlayerPreview() {
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			// Obtient le joueur actuel
			//PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
			if (m_Player) {
				// Met à jour la prévisualisation du joueur
				m_PlayerPreview.SetPlayer(m_Player);
				m_PlayerPreview.SetModelPosition("0 0 0.605");

				// Vérifie si le joueur est dans un véhicule
				HumanCommandVehicle vehCommand = m_Player.GetCommand_Vehicle();
				if (vehCommand) {
					// Le joueur est dans un véhicule, obtient le nom du véhicule
					Transport transport = vehCommand.GetTransport();
					if (transport) {
						m_ItemHands.SetText(transport.GetDisplayName());  // Met à jour le texte avec le nom du véhicule
						m_ItemPreview.SetItem(null);  // Efface la prévisualisation de l'objet
					}
				} else {
					// Le joueur n'est pas dans un véhicule, obtient l'objet dans les mains
					EntityAI itemInHands = m_Player.GetHumanInventory().GetEntityInHands();
					if (itemInHands) {
						m_ItemHands.SetText(itemInHands.GetDisplayName());  // Met à jour le texte avec le nom de l'objet
						m_ItemPreview.SetItem(itemInHands);  // Met à jour la prévisualisation de l'objet
					} else {
						m_ItemHands.SetText("#STR_EVAL_TYPENOTHING");  // Affiche un message indiquant que les mains sont vides
						m_ItemPreview.SetItem(null);  // Efface la prévisualisation de l'objet
					}
				}

				// Met à jour les animations de blessure (si applicable)
				DayZPlayer dummyPlayer = m_PlayerPreview.GetDummyPlayer();
				if (dummyPlayer) {
					HumanCommandAdditives hca = dummyPlayer.GetCommandModifier_Additives();
					if (hca && m_Player.m_InjuryHandler) {
						hca.SetInjured(m_Player.m_InjuryHandler.GetInjuryAnimValue(), m_Player.m_InjuryHandler.IsInjuryAnimEnabled());
					}
				}
			}
		}
	}

	// Gestion du clic de souris pour la rotation
	private bool OnMouseButtonDown(Widget w, int x, int y, int button) {
		if (w == m_PlayerPreview || w == m_ItemPreview)
		{
			m_SelectedPreviewWidget = w;  // Stocke le widget sélectionné
			GetMousePos(m_ItemRotationX, m_ItemRotationY);  // Utilisation de m_ItemRotationX et m_ItemRotationY pour la rotation
			g_Game.GetDragQueue().Call(this, "UpdateRotation");
			return true;
		}
		return false;
	}

	// Gestion de la rotation pendant le glissement de la souris
	private void UpdateRotation(int mouse_x, int mouse_y, bool is_dragging)
	{
		if (!m_SelectedPreviewWidget) return;  // Si aucun widget n'a été sélectionné, ne fais rien

		vector o = m_ItemOrientation;  // Utilise m_ItemOrientation pour la rotation
		// Applique la rotation uniquement sur l'axe Y (ou autre selon besoin)
		o[1] = o[1] - (m_ItemRotationX - mouse_x);

		// Applique la rotation uniquement au widget sélectionné
		if (m_SelectedPreviewWidget == m_PlayerPreview) {
			PlayerPreviewWidget previewWidget = PlayerPreviewWidget.Cast(m_PlayerPreview);
			if (previewWidget) {
				previewWidget.SetModelOrientation(o);  // Applique la rotation uniquement sur le player preview
			}
		}
		else if (m_SelectedPreviewWidget == m_ItemPreview) {
			ItemPreviewWidget itemWidget = ItemPreviewWidget.Cast(m_ItemPreview);
			if (itemWidget) {
				itemWidget.SetModelOrientation(o);  // Applique la rotation uniquement sur l'item preview
			}
		}

		// Mémorise l'orientation si on arrête de faire glisser la souris
		if (!is_dragging)
		{
			m_ItemOrientation = o;
		}
	}

	protected string GetDistanceString( float total_distance, bool meters_only = false )	{
		if( total_distance < 0 )
			return "0" + "#STR_distance_unit_abbrev_meter_0";
	
		int distance_meters = total_distance;
		string distance_string;
		
		int kilometers = distance_meters / 1000;
		if ( kilometers > 0 && !meters_only )	{
			distance_string += GetValueString( kilometers ) + "#STR_distance_unit_abbrev_kilometer_0";			//kilometers
			distance_string += " ";																				//separator
		}
		else	{
			distance_string += GetValueString( distance_meters ) + "#STR_distance_unit_abbrev_meter_0";			//meters
		}
		
		return distance_string;
	}

	protected string GetValueString( float total_value )	{
		if( total_value < 0 )
			return "0";
	
		int value = total_value;
		string out_string;
		
		if ( value >= 1000 )	{
			string value_string = value.ToString();
			
			int count;		
			int first_length = value_string.Length() % 3;		//calculate position of the first separator
			if ( first_length > 0 )	{
				count = 3 - first_length;
			}
			
			for ( int i = 0; i < value_string.Length(); ++i )	{
				out_string += value_string.Get( i );
				count ++;
				
				if ( count >= 3 )	{
					out_string += " ";			//separator
					count = 0;
				}
			}
		}
		else	{
			out_string = value.ToString();
		}
		return out_string;
	}
}
