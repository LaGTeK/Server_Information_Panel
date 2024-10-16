class CfgPatches
{
	class ServerPanel
	{
		requiredAddons[] = { "DZ_Scripts","JM_CF_Scripts" };
	};
};
// class CfgAddons
// {
//     class PreloadAddons
//     {
//         class ServerPanel
//         {
//             list[]={};
//         };
//     };
// };
class CfgMods
{
    class ServerPanel
    {
		name = "ServerPanel";
        dir="ServerPanel";
		action="";
        picture="";
		hideName=1;
		hidePicture=1;
		author = "LaGTeK";
        overview = "";
		creditsJson="ServerPanel/Scripts/Data/Credits.json";		
		inputs = "ServerPanel/Inputs.xml";
		type = "mod";
		defines[] = {"SERVERPANEL"};
		dependencies[] = {"Game","World","Mission"};

        class defs
		{
			class imageSets
			{
				files[] = {"ServerPanel/GUI/imageset/SP_Icons.imageset"};
			};
			class gameScriptModule
			{
				files[] = { "ServerPanel/Scripts/3_Game" };
			};
			class worldScriptModule
			{
				files[] = { "ServerPanel/Scripts/4_World" };
			};
			class missionScriptModule 
			{
				files[] = { "ServerPanel/Scripts/5_Mission" };
			};
		};
    };
};
