class CraftingRecipe
{
	ref RecipeBase Recipe;
    int m_TempMainIndex;  // Define the index here
	ref array<ref CraftingItem> Results;
	ref array<ref array<ref CraftingItem>> Ingredients;


    void CraftingRecipe(RecipeBase recipeBase)
    {
		Recipe = recipeBase;

		Results = recipeBase.GetResults();
		Ingredients = recipeBase.GetIngredients();

		if (!IsValid())
			return;
    }

	bool IsValid()
	{
		//! Discard invalid recipes with no results
		if (Results.Count() == 0)
			return false;

		foreach (array<ref CraftingItem> items : Ingredients )
		{
			//! Discard invalid recipes with no ingredients
			if (items.Count() == 0)
				return false;
		}

		return true;
	}

    // Ajoute une classe d'item à la liste des classes associées à cet item
    /*void AddClassName(string className)
    {
        classNames.Insert(className);
    }*/

    // Renvoie le nom d'affichage de cet item
    string GetDisplayName()
    {
        string recipeNameLower = Recipe.m_Name;
        recipeNameLower.ToLower();

        string displayName = Recipe.m_Name;

        switch (recipeNameLower)
        {
            case "#fill":
            case "#mount":
            case "#pack_tent":
                displayName += " " + Results[m_TempMainIndex].displayName;
                break;
            case "#str_breakdown0":
			case "#str_gutandprepare0":
			case "#str_prepare0":
			case "#str_split0":
            case "#sharpen":
                if (Results.Count() > 1 && GetGame().IsKindOf(Results[m_TempMainIndex].classNames[0], "SeedBase"))
                {
                    recipeNameLower = "#str_cutoutseeds0";
                    displayName = "#str_cutoutseeds0";
                }
                else
                {
                    displayName += " " + Ingredients[0][0].displayName;
                    break;
                }
            case "#str_cutoutseeds0":
                if (Results[m_TempMainIndex].amount > 1)
                    displayName += " (" + Results[m_TempMainIndex].amount + "x)";
                displayName = Ingredients[0][0].displayName + ": " + displayName;
                break;
            case "#str_craftgutsrope0":
            case "#str_craftragrope0":
                displayName = Ingredients[0][0].displayName + ": " + displayName;
                break;
            default:
                if (recipeNameLower.IndexOf("#str_craft") == 0 || recipeNameLower.IndexOf("#craft") == 0 || recipeNameLower == "#str_sawwoodenlog0")
                {
                    //! Localiser "Craft" si nécessaire
                    displayName = "Craft " + Results[m_TempMainIndex].displayName;
                    if (Results[m_TempMainIndex].amount > 1)
                        displayName += " (" + Results[m_TempMainIndex].amount + "x)";
                }
                break;
        }

        return Widget.TranslateString(displayName);
    }
}
