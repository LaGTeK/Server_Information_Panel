class CfgPatches
{
	class ServerPanel_Scripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Scripts",
			"JM_CF_Scripts"
		};
	};
};
class CfgMods
{
	class ServerPanel
	{
		dir="ServerPanel";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="ServerPanel";
		credits="LaGTeK";
		author="LaGTeK";
		authorID="0";
		version="0.1";
		extra=0;
		type="mod";

		inputs = "ServerPanel/SP_inputs.xml";

		dependencies[]=
		{
			"Game","World","Mission"
		};
		class defs
		{
			class imageSets
			{
				files[] = {"ServerPanel/scripts/gui/imageset/SP_Icons.imageset"};
			};
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"ServerPanel/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"ServerPanel/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"ServerPanel/scripts/5_Mission"
				};
			};
		};
	};
};
