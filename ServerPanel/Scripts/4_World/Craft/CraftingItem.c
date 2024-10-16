class CraftingItem
{
	ref RecipeBase Recipe;
	string displayName;
	int amount;
	ref array<string> classNames;

	void CraftingItem(string name, int qty, array<string> classes = null, int tempMainIndex = 0)
	{
		displayName = name;
		amount = qty;
		classNames = new array<string>();

		// Si un tableau de classes est fourni, l'ajouter
		if (classes) {
			foreach (string className : classes) {  
				classNames.Insert(className);
			}
		}
	}

	string Format(bool includeAmount = true)
	{
		if (includeAmount && amount > 1)
			return amount.ToString() + "x " + displayName;
		else
			return displayName;
	}

	// Renvoie la quantité
	int GetAmount()
	{
		return amount;
	}
}
