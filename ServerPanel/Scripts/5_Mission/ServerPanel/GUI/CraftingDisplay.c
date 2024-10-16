class CraftingDisplay 
{
    private Widget m_RootWidget;
    private TextListboxWidget m_CraftListTextListboxWidget;
    private EditBoxWidget m_SearchEditBoxWidget;
	private Widget m_ResultCraft0PanelWidget;
	private Widget m_ResultCraft1PanelWidget;
	private Widget m_ResultCraft2PanelWidget;
    private ItemPreviewWidget m_ResultCraft0ItemPreviewWidget;
    private ItemPreviewWidget m_ResultCraft1ItemPreviewWidget;
    private ItemPreviewWidget m_ResultCraft2ItemPreviewWidget;
    private TextListboxWidget m_Ingredient1Label;
    private TextListboxWidget m_Ingredient2Label;
    private ItemPreviewWidget m_Ingredient1ItemPreviewWidget;
    private ItemPreviewWidget m_Ingredient2ItemPreviewWidget;
    private TextWidget m_ResultCraft0Label;
    private TextWidget m_ResultCraft1Label;
    private TextWidget m_ResultCraft2Label;
	protected ImageWidget m_SortImageWidget;
	private ButtonWidget m_SortButtonWidget;

    private ref array<ref CraftingRecipe> m_AllRecipes;
	private ref array<ref CraftingRecipe> m_FilteredRecipes;
    
    private string m_SearchText;

	// Variables pour stocker la rotation et l'échelle	
	protected vector m_ItemOrientation;
	protected int m_ItemRotationX;
	protected int m_ItemRotationY;
	protected Widget m_SelectedPreviewWidget;

	private bool m_IsAscendingSort = true;  // Indique si le tri est en mode A-Z (true) ou Z-A (false)

    void CraftingDisplay() {
        m_AllRecipes = new array<ref CraftingRecipe>;
        m_FilteredRecipes = new array<ref CraftingRecipe>;
        m_SearchText = "";
    }

    // Initialize the UI components from layout
    void Init(Widget rootWidget) {
		
		m_RootWidget = GetGame().GetWorkspace().CreateWidgets("ServerPanel/GUI/layouts/CraftingDisplay.layout", rootWidget.FindAnyWidget("Tab_4"));

        m_CraftListTextListboxWidget = TextListboxWidget.Cast(m_RootWidget.FindAnyWidget("CraftListTextListboxWidget"));

        m_SearchEditBoxWidget = EditBoxWidget.Cast(m_RootWidget.FindAnyWidget("SearchEditBoxWidget"));

        m_Ingredient1Label = TextListboxWidget.Cast(m_RootWidget.FindAnyWidget("Ingredient1Label"));
        m_Ingredient1ItemPreviewWidget = ItemPreviewWidget.Cast(m_RootWidget.FindAnyWidget("Ingredient1ItemPreviewWidget"));

        m_Ingredient2Label = TextListboxWidget.Cast(m_RootWidget.FindAnyWidget("Ingredient2Label"));
        m_Ingredient2ItemPreviewWidget = ItemPreviewWidget.Cast(m_RootWidget.FindAnyWidget("Ingredient2ItemPreviewWidget"));

		m_ResultCraft0PanelWidget = Widget.Cast(m_RootWidget.FindAnyWidget("ResultCraft0PanelWidget"));
        m_ResultCraft0ItemPreviewWidget = ItemPreviewWidget.Cast(m_RootWidget.FindAnyWidget("ResultCraft0ItemPreviewWidget"));
        m_ResultCraft0Label = TextWidget.Cast(m_RootWidget.FindAnyWidget("ResultCraft0Label"));

		m_ResultCraft1PanelWidget = Widget.Cast(m_RootWidget.FindAnyWidget("ResultCraft1PanelWidget"));
        m_ResultCraft1ItemPreviewWidget = ItemPreviewWidget.Cast(m_RootWidget.FindAnyWidget("ResultCraft1ItemPreviewWidget"));
        m_ResultCraft1Label = TextWidget.Cast(m_RootWidget.FindAnyWidget("ResultCraft1Label"));

		m_ResultCraft2PanelWidget = Widget.Cast(m_RootWidget.FindAnyWidget("ResultCraft2PanelWidget"));
        m_ResultCraft2ItemPreviewWidget = ItemPreviewWidget.Cast(m_RootWidget.FindAnyWidget("ResultCraft2ItemPreviewWidget"));
        m_ResultCraft2Label = TextWidget.Cast(m_RootWidget.FindAnyWidget("ResultCraft2Label"));

		m_SortImageWidget	=	ImageWidget.Cast(m_RootWidget.FindAnyWidget("SortImageWidget"));
		m_SortButtonWidget	=	ButtonWidget.Cast( m_RootWidget.FindAnyWidget( "SortButtonWidget" ));

        // Register event handlers for when a recipe or ingredient is selected
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(m_CraftListTextListboxWidget, this, "OnRecipeSelected");
        // Register event handlers for ingredient selection
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(m_Ingredient1Label, this, "OnIngredient1Selected");
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(m_Ingredient2Label, this, "OnIngredient2Selected");

		// Enregistre les événements de souris
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(m_ResultCraft0ItemPreviewWidget, this, "OnMouseButtonDown");
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(m_ResultCraft1ItemPreviewWidget, this, "OnMouseButtonDown");
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(m_ResultCraft2ItemPreviewWidget, this, "OnMouseButtonDown");
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(m_Ingredient1ItemPreviewWidget, this, "OnMouseButtonDown");
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(m_Ingredient2ItemPreviewWidget, this, "OnMouseButtonDown");	

		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(m_SortButtonWidget, this, "OnSortButtonClicked");

        // Charger toutes les recettes dans la liste
		LoadAllRecipes();
		
		// Copie manuelle des recettes dans m_FilteredRecipes
		m_FilteredRecipes.Clear();  // S'assurer que la liste est vide avant de remplir
		foreach (CraftingRecipe recipe : m_AllRecipes) {
			m_FilteredRecipes.Insert(recipe);
		}
		
		DisplayFilteredRecipes();  // Afficher les recettes immédiatement

		// Sélection automatique de la première recette
		if (m_FilteredRecipes.Count() > 0) {
			m_CraftListTextListboxWidget.SelectRow(0);
			DisplayRecipeDetails(m_FilteredRecipes[0]);
		}
    }

    // Load all recipes dynamically
    void LoadAllRecipes() {
        SPRecipeManager recipeManager = new SPRecipeManager();
        m_AllRecipes = recipeManager.GetAllRecipes();  // Assuming SPRecipeManager handles the filtering
    }

    // Update method to handle search
    void Update(float timeslice) {
        if (m_SearchText != m_SearchEditBoxWidget.GetText()) {
            m_SearchText = m_SearchEditBoxWidget.GetText();
            FilterRecipes();
            DisplayFilteredRecipes();
        }
    }

	// Function to remove unwanted characters
	string RemoveSpecialCharacters(string text) {
		// Replace special characters with an empty string
		text.Replace("<", "");
		text.Replace(">", "");
		text.Replace(";", "");
		text.Replace("/", "");
		text.Replace("!", "");
		text.Replace("?", "");
		text.Replace(",", "");
		
		return text;
	}

	// Filter recipes based on the search text
	void FilterRecipes() {
		m_FilteredRecipes.Clear();
		
		// Convert the search text to lowercase in place, then remove special characters
		m_SearchText.ToLower();
		string lowerSearchText = RemoveSpecialCharacters(m_SearchText);
		
		if (lowerSearchText == "") {
			// Manually copy all items from m_AllRecipes to m_FilteredRecipes
			foreach (CraftingRecipe craftingRecipe : m_AllRecipes) {
				m_FilteredRecipes.Insert(craftingRecipe);
			}
		} else {
			foreach (CraftingRecipe filteredRecipe : m_AllRecipes) {
				// Convert the display name to lowercase in place, then remove special characters
				string displayName = filteredRecipe.GetDisplayName();
				displayName.ToLower();
				string lowerDisplayName = RemoveSpecialCharacters(displayName);
				
				if (lowerDisplayName.Contains(lowerSearchText)) {
					m_FilteredRecipes.Insert(filteredRecipe);
				}
			}
		}
	}

	// Sort the recipes alphabetically by display name without using map
	/*void SortRecipesAlphabetically(ref array<ref CraftingRecipe> recipesArray) {
		// Boucle simple de tri par sélection
		for (int i = 0; i < recipesArray.Count() - 1; i++) {
			for (int j = i + 1; j < recipesArray.Count(); j++) {
				// Comparaison des noms de recettes
				string recipeNameI = recipesArray[i].GetDisplayName();
				recipeNameI.ToLower();  // Modifier directement la chaîne en minuscules

				string recipeNameJ = recipesArray[j].GetDisplayName();
				recipeNameJ.ToLower();  // Modifier directement la chaîne en minuscules

				// Si la recette à la position j est alphabétiquement avant la recette à la position i, on les échange
				if (recipeNameJ < recipeNameI) {
					CraftingRecipe temp = recipesArray[i];
					recipesArray[i] = recipesArray[j];
					recipesArray[j] = temp;
				}
			}
		}
	}*/
	// Sort the recipes alphabetically by display name in either ascending (A-Z) or descending (Z-A) order
	void SortRecipesAlphabetically(ref array<ref CraftingRecipe> recipesArray, bool isAscending) {
		for (int i = 0; i < recipesArray.Count() - 1; i++) {
			for (int j = i + 1; j < recipesArray.Count(); j++) {
				string recipeNameI = recipesArray[i].GetDisplayName();
				recipeNameI.ToLower();  // Modifier directement la chaîne en minuscules

				string recipeNameJ = recipesArray[j].GetDisplayName();
				recipeNameJ.ToLower();  // Modifier directement la chaîne en minuscules

				// Comparer en fonction de l'ordre croissant ou décroissant
				bool shouldSwap = false;

				if (isAscending) {
					if (recipeNameJ < recipeNameI) {
						shouldSwap = true;
					}
				} else {
					if (recipeNameJ > recipeNameI) {
						shouldSwap = true;
					}
				}

				// Si on doit échanger les éléments, on le fait ici
				if (shouldSwap) {
					CraftingRecipe temp = recipesArray[i];
					recipesArray[i] = recipesArray[j];
					recipesArray[j] = temp;
				}
			}
		}
	}

	// Called when the sort button is clicked
	void OnSortButtonClicked() {
		// Inverser l'état du tri (A-Z ou Z-A)
		m_IsAscendingSort = !m_IsAscendingSort;

		// Changer l'image du bouton en fonction de l'état du tri
		if (m_IsAscendingSort) {
			m_SortImageWidget.LoadImageFile(0, "set:spicons image:sortAZ");
		} else {
			m_SortImageWidget.LoadImageFile(0, "set:spicons image:sortZA");
		}

		// Réafficher les recettes triées
		DisplayFilteredRecipes();
	}

	// Display filtered recipes in the listbox
	/*void DisplayFilteredRecipes() {
		// Trier les recettes avant de les afficher
		SortRecipesAlphabetically(m_FilteredRecipes);
		
		m_CraftListTextListboxWidget.ClearItems();
		
		foreach (CraftingRecipe recipe : m_FilteredRecipes) {
			m_CraftListTextListboxWidget.AddItem(recipe.GetDisplayName(), recipe, 0);
		}
	}*/
	// Display filtered recipes in the listbox
	void DisplayFilteredRecipes() {
		// Trier les recettes en fonction de l'état actuel (A-Z ou Z-A)
		SortRecipesAlphabetically(m_FilteredRecipes, m_IsAscendingSort);
		
		m_CraftListTextListboxWidget.ClearItems();
		
		foreach (CraftingRecipe recipe : m_FilteredRecipes) {
			m_CraftListTextListboxWidget.AddItem(recipe.GetDisplayName(), recipe, 0);
		}
	}


    // Handle recipe selection
    void OnRecipeSelected() {
        int selectedIndex = m_CraftListTextListboxWidget.GetSelectedRow();
        if (selectedIndex >= 0) {
			// Réinitialiser l'orientation de l'élément lorsque la recette change
			m_ItemOrientation = vector.Zero;  // Réinitialise la rotation
			m_ItemRotationX = 0;
			m_ItemRotationY = 0;

			// Appliquer la réinitialisation à tous les widgets de prévisualisation
			if (m_ResultCraft0ItemPreviewWidget) {
				m_ResultCraft0ItemPreviewWidget.SetModelOrientation(m_ItemOrientation);
			}
			if (m_ResultCraft1ItemPreviewWidget) {
				m_ResultCraft1ItemPreviewWidget.SetModelOrientation(m_ItemOrientation);
			}
			if (m_ResultCraft2ItemPreviewWidget) {
				m_ResultCraft2ItemPreviewWidget.SetModelOrientation(m_ItemOrientation);
			}
			if (m_Ingredient1ItemPreviewWidget) {
				m_Ingredient1ItemPreviewWidget.SetModelOrientation(m_ItemOrientation);
			}
			if (m_Ingredient2ItemPreviewWidget) {
				m_Ingredient2ItemPreviewWidget.SetModelOrientation(m_ItemOrientation);
			}

            CraftingRecipe selectedRecipe;
            m_CraftListTextListboxWidget.GetItemData(selectedIndex, 0, selectedRecipe);
            DisplayRecipeDetails(selectedRecipe);
        }
    }

	void DisplayRecipeDetails(CraftingRecipe recipe) {
		// Afficher les ingrédients
		DisplayIngredients(recipe);

		int numResults = recipe.Results.Count(); // Get the number of results

    	// Variables pour stocker les résultats
    	CraftingItem resultItem0, resultItem1, resultItem2;

		// Variables pour stocker les résultats
		string resultClassName0;
		string resultClassName1;
		string resultClassName2;
		EntityAI previewResultItem0, previewResultItem1, previewResultItem2;

		// Ajuster dynamiquement la taille des panels en fonction du nombre de résultats
		if (numResults == 1) {
			m_ResultCraft0PanelWidget.SetSize(1, 1);  // 100% de l'espace
			m_ResultCraft1PanelWidget.Show(false);  // Cacher panel 1
			m_ResultCraft1PanelWidget.SetSize(1, 0);  // Cacher panel 1
			m_ResultCraft2PanelWidget.Show(false);  // Cacher panel 2
			m_ResultCraft2PanelWidget.SetSize(1, 0);  // Cacher panel 2

			// Set the preview and label for the first result
			//resultItem0 = recipe.Results[0].displayName;
			resultItem0 = recipe.Results[0];
			resultClassName0 = recipe.Results[0].classNames[0];
			m_ResultCraft0Label.SetText(resultItem0.Format());

			DisplayResultPreview0(resultClassName0);
		} else if (numResults == 2) {
			m_ResultCraft0PanelWidget.SetSize(1, 1/2);  // 50% de l'espace
			m_ResultCraft1PanelWidget.SetSize(1, 1/2);  // 50% de l'espace			
			m_ResultCraft1PanelWidget.SetPos(0, 1/2);
			m_ResultCraft1PanelWidget.Show(true);  // Montrer panel 1
			m_ResultCraft2PanelWidget.SetSize(1, 0);    // Cacher panel 2
			m_ResultCraft2PanelWidget.Show(false);    // Cacher panel 2

			// Set the preview and label for the first result
			//resultItem0 = recipe.Results[0].displayName;
			resultItem0 = recipe.Results[0];
			resultClassName0 = recipe.Results[0].classNames[0];	
			m_ResultCraft0Label.SetText(resultItem0.Format());

			DisplayResultPreview0(resultClassName0);

			// Set the preview and label for the second result
			//resultItem1 = recipe.Results[1].displayName;
			resultItem1 = recipe.Results[1];
			resultClassName1 = recipe.Results[1].classNames[0];
			m_ResultCraft1Label.SetText(resultItem1.Format());
						
			DisplayResultPreview1(resultClassName1);
		} else if (numResults == 3) {
			m_ResultCraft0PanelWidget.SetSize(1, 1/3);  // 33% de l'espace
			m_ResultCraft1PanelWidget.SetSize(1, 1/3);  // 33% de l'espace
			m_ResultCraft1PanelWidget.Show(true);  // Montrer panel 1		
			m_ResultCraft1PanelWidget.SetPos(0, 1/3);
			m_ResultCraft2PanelWidget.SetSize(1, 1/3);  // 33% de l'espace
			m_ResultCraft2PanelWidget.Show(true);    // Cacher panel 2

			// Set the preview and label for the first result
			
			EntityAI currentResultItem0 = m_ResultCraft0ItemPreviewWidget.GetItem();
			if (currentResultItem0) {
				GetGame().ObjectDelete(currentResultItem0);  // Supprimer l'objet actuel si existant
				m_ResultCraft0ItemPreviewWidget.SetItem(null);  // Réinitialiser l'aperçu pour éviter tout conflit
			}
			//resultItem0 = recipe.Results[0].displayName;
			resultItem0 = recipe.Results[0];
			resultClassName0 = recipe.Results[0].classNames[0];	
			m_ResultCraft0Label.SetText(resultItem0.Format());
						
			DisplayResultPreview0(resultClassName0);

			// Set the preview and label for the second result
			//resultItem1 = recipe.Results[1].displayName;
			resultItem1 = recipe.Results[1];
			resultClassName1 = recipe.Results[1].classNames[0];	
			m_ResultCraft1Label.SetText(resultItem1.Format());
						
			DisplayResultPreview1(resultClassName1);

			// Set the preview and label for the third result
			//resultItem2 = recipe.Results[2].displayName;
			resultItem2 = recipe.Results[2];
			resultClassName2 = recipe.Results[2].classNames[0];	
			m_ResultCraft2Label.SetText(resultItem2.Format());
						
			DisplayResultPreview2(resultClassName2);
		} else {
			m_ResultCraft0PanelWidget.SetSize(1, 1);  // 100% de l'espace
			m_ResultCraft1PanelWidget.Show(false);  // Cacher panel 1
			m_ResultCraft2PanelWidget.Show(false);  // Cacher panel 2

			// Set the preview and label for the first result
			//resultItem0 = recipe.Results[0].displayName;
			resultItem0 = recipe.Results[0];
			resultClassName0 = recipe.Results[0].classNames[0];
			m_ResultCraft0Label.SetText(resultItem0.Format());
						
			DisplayResultPreview0(resultClassName0);
		}
	}

    // Display ingredients in the listbox
	void DisplayIngredients(CraftingRecipe recipe) {
		m_Ingredient1Label.ClearItems();
		m_Ingredient2Label.ClearItems();

		// Affichage des noms formatés des ingrédients avec les quantités pour l'ingrédient 1
		foreach (CraftingItem ingredient1 : recipe.Ingredients[0]) {
			string ingredientClassName1;
			if (ingredient1.classNames && ingredient1.classNames.Count() > 0) {
				ingredientClassName1 = ingredient1.classNames[0];  // Récupérer le nom de la classe
			} else {
				ingredientClassName1 = ingredient1.displayName;  // Utiliser le nom d'affichage si aucune classe n'est disponible
			}

			if (ingredientClassName1.Contains("Ammo_SharpStick") || ingredient1.Format().Contains("Ammo_SharpStick"))
				continue;
			
			if (ingredientClassName1.Contains("Inventory_Base") || ingredient1.Format().Contains("Inventory_Base"))
				continue;

			if (ingredientClassName1.Contains("$UNT$"))
				ingredientClassName1.Replace("$UNT$","");

			// Ajouter l'ingrédient dans la liste avec le nom modifié
			m_Ingredient1Label.AddItem(ingredient1.Format(), ingredient1, 0);  
		}

		// Affichage des noms formatés des ingrédients avec les quantités pour l'ingrédient 2
		foreach (CraftingItem ingredient2 : recipe.Ingredients[1]) {
			string ingredientClassName2;
			if (ingredient2.classNames && ingredient2.classNames.Count() > 0) {
				ingredientClassName2 = ingredient2.classNames[0];  // Récupérer le nom de la classe
			} else {
				ingredientClassName2 = ingredient2.displayName;  // Utiliser le nom d'affichage si aucune classe n'est disponible
			}

			if (ingredientClassName2.Contains("Ammo_SharpStick") || ingredient2.Format().Contains("Ammo_SharpStick"))
				continue;
			
			if (ingredientClassName2.Contains("Inventory_Base") || ingredient2.Format().Contains("Inventory_Base"))
				continue;
			
			if (ingredientClassName2.Contains("$UNT$"))
				ingredientClassName2.Replace("$UNT$","");

			// Ajouter l'ingrédient dans la liste avec le nom modifié
			m_Ingredient2Label.AddItem(ingredient2.Format(), ingredient2, 0);
		}

		// Sélection automatique et aperçu pour le premier ingrédient dans chaque liste
		if (recipe.Ingredients[0].Count() > 0) {
			m_Ingredient1Label.SelectRow(0);
			OnIngredient1Selected();  // Appeler la fonction de sélection pour gérer l'aperçu
		}

		if (recipe.Ingredients[1].Count() > 0) {
			m_Ingredient2Label.SelectRow(0);
			OnIngredient2Selected();  // Appeler la fonction de sélection pour gérer l'aperçu
		}
	}

	// Handle ingredient selection for preview
	void OnIngredient1Selected() {
		CraftingItem selectedIngredient = null;
		GetSelectedIngredientData(m_Ingredient1Label, selectedIngredient);  // Utiliser la méthode pour récupérer les données
		
		if (selectedIngredient) {
			if (selectedIngredient.classNames && selectedIngredient.classNames.Count() > 0) {
				string ingredientClassName = selectedIngredient.classNames[0];
				//Print("Ingrédient 1 sélectionné : " + selectedIngredient.displayName + " (Classe : " + ingredientClassName + ")");
				
				DisplayIngredientPreview1(ingredientClassName);
			} else {
				//Print("Erreur : selectedIngredient.classNames est vide ou nul.");
			}
		} else {
			//Print("Erreur : Aucun ingrédient 1 sélectionné ou sélection invalide.");
		}
	}

	void OnIngredient2Selected() {
		CraftingItem selectedIngredient = null;
		GetSelectedIngredientData(m_Ingredient2Label, selectedIngredient);  // Utiliser la méthode pour récupérer les données
		
		if (selectedIngredient) {
			if (selectedIngredient.classNames && selectedIngredient.classNames.Count() > 0) {
				string ingredientClassName = selectedIngredient.classNames[0];
				//Print("Ingrédient 2 sélectionné : " + selectedIngredient.displayName + " (Classe : " + ingredientClassName + ")");

				DisplayIngredientPreview2(ingredientClassName);
			} else {
				//Print("Erreur : selectedIngredient.classNames est vide ou nul.");
			}
		} else {
			//Print("Erreur : Aucun ingrédient 2 sélectionné ou sélection invalide.");
		}
	}

	void GetSelectedIngredientData(TextListboxWidget widget, out CraftingItem data) {
		int selectedIndex = widget.GetSelectedRow();
		if (selectedIndex != -1) {
			widget.GetItemData(selectedIndex, 0, data);  // Récupérer les données
		} else {
			data = null;  // Si aucune ligne n'est sélectionnée, définir les données comme null
		}
	}

	static string FilterClassName(string className)
	{
		// Vérifie si le nom de classe contient "Flag_Base" et remplace-le par "Flag_Chernarus"
		if (className == "Flag_Base")
		{
			return "Flag_Chernarus";
		}	
		if (className == "Pelt_Base")
		{
			return "BearPelt";
		}
		if (className == "Spear")
		{
			return "SpearBone";
		}			
		if (className == "MetalWireColorBase")
		{
			return "MetalWire";
		}				
		if (className == "DeadChicken_ColorBase")
		{
			return "DeadChicken_Brown";
		}	
		if (className == "DrysackBag_ColorBase")
		{
			return "DrysackBag_Orange";
		}		
		if (className == "WaterproofBag_ColorBase")
		{
			return "WaterproofBag_Orange";
		}	
		if (className == "GhillieAtt_ColorBase")
		{
			return "GhillieAtt_Mossy";
		}
		if (className == "GhillieHood_ColorBase")
		{
			return "GhillieHood_Mossy";
		}
		if (className == "GhillieTop_ColorBase")
		{
			return "GhillieTop_Mossy";
		}
		if (className == "GhillieSuit_ColorBase")
		{
			return "GhillieSuit_Mossy";
		}
		if (className == "GhillieBushrag_ColorBase")
		{
			return "GhillieBushrag_Mossy";
		}
		if (className == "Armband_ColorBase")
		{
			return "Armband_White";
		}
		if (className == "LeatherSack_ColorBase")
		{
			return "LeatherSack_Natural";
		}		
		if (className.Contains("_Base"))
		{
			className.Replace("_Base", "");
			return className;
		}
		if (className.Contains("_ColorBase"))
		{
			className.Replace("_ColorBase", "_Red");
			return className;
		}

		// Ajoute d'autres filtres ici si nécessaire

		// Si aucun filtre ne s'applique, retourne le nom de classe original
		return className;
	}

	void DisplayIngredientPreview1(string ingredientClassName) {
		EntityAI currentItem = m_Ingredient1ItemPreviewWidget.GetItem();
		if (currentItem) {
			GetGame().ObjectDelete(currentItem);  // Supprimer l'objet actuel si existant
			m_Ingredient1ItemPreviewWidget.SetItem(null);  // Réinitialiser l'aperçu pour éviter tout conflit
		}
		
		EntityAI previewItem = GetGame().CreateObjectEx(FilterClassName(ingredientClassName), "0 0 0", ECE_LOCAL);
		if (previewItem) {
			m_Ingredient1ItemPreviewWidget.SetItem(EntityAI.Cast(previewItem));  // Afficher l'aperçu du nouvel ingrédient
		} else {
			Print("Erreur DisplayIngredientPreview1 : Impossible de créer un aperçu pour la classe : " + ingredientClassName);
		}
	}

	void DisplayIngredientPreview2(string ingredientClassName) {
		EntityAI currentItem = m_Ingredient2ItemPreviewWidget.GetItem();
		if (currentItem) {
			GetGame().ObjectDelete(currentItem);  // Supprimer l'objet actuel si existant
			m_Ingredient2ItemPreviewWidget.SetItem(null);  // Réinitialiser l'aperçu pour éviter tout conflit
		}
		
		EntityAI previewItem = GetGame().CreateObjectEx(FilterClassName(ingredientClassName), "0 0 0", ECE_LOCAL);
		if (previewItem) {
			m_Ingredient2ItemPreviewWidget.SetItem(EntityAI.Cast(previewItem));  // Afficher l'aperçu du nouvel ingrédient
		} else {
			Print("Erreur DisplayIngredientPreview2 : Impossible de créer un aperçu pour la classe : " + ingredientClassName);
		}
	}

	void DisplayResultPreview0(string resultClassName) {
		EntityAI currentItem = m_ResultCraft0ItemPreviewWidget.GetItem();
		if (currentItem) {
			GetGame().ObjectDelete(currentItem);  // Supprimer l'objet actuel si existant
			m_ResultCraft0ItemPreviewWidget.SetItem(null);  // Réinitialiser l'aperçu pour éviter tout conflit
		}
		
		EntityAI previewItem = GetGame().CreateObjectEx(FilterClassName(resultClassName), "0 0 0", ECE_LOCAL);
		if (previewItem) {
			m_ResultCraft0ItemPreviewWidget.SetItem(EntityAI.Cast(previewItem));  // Afficher l'aperçu du nouvel ingrédient
		} else {
			Print("Erreur DisplayResultPreview0 : Impossible de créer un aperçu pour la classe : " + resultClassName);
		}
	}

	void DisplayResultPreview1(string resultClassName) {
		EntityAI currentItem = m_ResultCraft1ItemPreviewWidget.GetItem();
		if (currentItem) {
			GetGame().ObjectDelete(currentItem);  // Supprimer l'objet actuel si existant
			m_ResultCraft1ItemPreviewWidget.SetItem(null);  // Réinitialiser l'aperçu pour éviter tout conflit
		}
		
		EntityAI previewItem = GetGame().CreateObjectEx(FilterClassName(resultClassName), "0 0 0", ECE_LOCAL);
		if (previewItem) {
			m_ResultCraft1ItemPreviewWidget.SetItem(EntityAI.Cast(previewItem));  // Afficher l'aperçu du nouvel ingrédient
		} else {
			Print("Erreur DisplayResultPreview1 : Impossible de créer un aperçu pour la classe : " + resultClassName);
		}
	}

	void DisplayResultPreview2(string resultClassName) {
		EntityAI currentItem = m_ResultCraft2ItemPreviewWidget.GetItem();
		if (currentItem) {
			GetGame().ObjectDelete(currentItem);  // Supprimer l'objet actuel si existant
			m_ResultCraft2ItemPreviewWidget.SetItem(null);  // Réinitialiser l'aperçu pour éviter tout conflit
		}
		
		EntityAI previewItem = GetGame().CreateObjectEx(FilterClassName(resultClassName), "0 0 0", ECE_LOCAL);
		if (previewItem) {
			m_ResultCraft2ItemPreviewWidget.SetItem(EntityAI.Cast(previewItem));  // Afficher l'aperçu du nouvel ingrédient
		} else {
			Print("Erreur DisplayResultPreview2 : Impossible de créer un aperçu pour la classe : " + resultClassName);
		}
	}

	// Gestion du clic de souris pour la rotation
	private bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		if (w == m_ResultCraft0ItemPreviewWidget || w == m_ResultCraft1ItemPreviewWidget || w == m_ResultCraft2ItemPreviewWidget || w == m_Ingredient1ItemPreviewWidget || w == m_Ingredient2ItemPreviewWidget)
		{
        	m_SelectedPreviewWidget = w;  // Stocke le widget sélectionné
			GetMousePos(m_ItemRotationX, m_ItemRotationY);
			g_Game.GetDragQueue().Call(this, "UpdateRotation");
			return true;
		}
		return false;
	}

	// Gestion de la rotation pendant le glissement de la souris
	private void UpdateRotation(int mouse_x, int mouse_y, bool is_dragging)
	{
		if (!m_SelectedPreviewWidget) return;  // Si aucun widget n'a été sélectionné, ne fais rien

		vector o = m_ItemOrientation;
		// Applique la rotation uniquement sur l'axe Y (ou autre selon besoin)
		o[1] = o[1] - (m_ItemRotationX - mouse_x);

		// Applique la rotation uniquement au widget sélectionné
		ItemPreviewWidget previewWidget = ItemPreviewWidget.Cast(m_SelectedPreviewWidget);
		if (previewWidget) {
			previewWidget.SetModelOrientation(o);  // Applique la rotation uniquement sur le widget cliqué
		}

		// Mémorise l'orientation si on arrête de faire glisser la souris
		if (!is_dragging)
		{
			m_ItemOrientation = o;
		}
	}
}
