class SPRecipeManager {
    private ref array<ref CraftingRecipe> m_AllRecipes;
    private ref array<string> m_ExcludedTerms;
    private ref array<string> m_ExcludedClasses;

    void SPRecipeManager() {
        m_AllRecipes = new array<ref CraftingRecipe>();
        m_ExcludedTerms = new array<string>();
        m_ExcludedClasses = new array<string>();

        // Ajouter des termes génériques à exclure
        m_ExcludedTerms.Insert("Repair");
        //m_ExcludedTerms.Insert("Split");
        //m_ExcludedTerms.Insert("Sharpen");
        //m_ExcludedTerms.Insert("Poke");
        //m_ExcludedTerms.Insert("Clean");
        // Ajoutez plus de termes génériques si nécessaire

        // Ajouter des noms de classes à exclure
        m_ExcludedClasses.Insert("OpenCan");
        m_ExcludedClasses.Insert("FuelChainsaw");
        m_ExcludedClasses.Insert("ExtinguishTorch");
        m_ExcludedClasses.Insert("FillSyringe");
        m_ExcludedClasses.Insert("AttachHolsterPouch");
        m_ExcludedClasses.Insert("AttachPouchesHolster");
        // Ajoutez plus de classes à exclure si nécessaire

        LoadRecipes();
    }

    void LoadRecipes() {
        PluginRecipesManager recipes = PluginRecipesManager.Cast(GetPlugin(PluginRecipesManager));
        foreach (RecipeBase recipeBase : recipes.m_RecipeList) {
            if (recipeBase && IsValidRecipe(recipeBase)) {
                CraftingRecipe craftingRecipe = new CraftingRecipe(recipeBase); // Convert RecipeBase to CraftingRecipe
                m_AllRecipes.Insert(craftingRecipe);
            }
        }
    }

    // Vérifie si une recette est valide (non exclue) en fonction des termes génériques et des noms de classes
    bool IsValidRecipe(RecipeBase recipe)
    {
        // Vérifier si le nom de la recette contient un terme générique exclu
        
        string recipeClassName = recipe.Type().ToString();  // Récupère le nom de la classe de la recette
        foreach (string term : m_ExcludedTerms) {            
            if (recipeClassName.Contains(term)) {
                return false;  // Exclure cette recette
            }
        }

        // Vérifier si la classe de la recette est dans les classes à exclure
        foreach (string className : m_ExcludedClasses) {
            if (recipeClassName == className) {
                return false;  // Exclure cette recette
            }
        }

        if (!recipe.CanBeShownInCraftingTab()) {
            return false;  // Exclure cette recette
        }

        // Vérifier si la recette produit au moins un résultat (pour les crafts)
        return recipe.m_NumberOfResults > 0;
    }

    // Retourne toutes les recettes sous forme de CraftingRecipe
    array<ref CraftingRecipe> GetAllRecipes() {
        return m_AllRecipes;
    }
}
