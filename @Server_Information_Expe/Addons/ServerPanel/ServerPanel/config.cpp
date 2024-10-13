////////////////////////////////////////////////////////////////////
//DeRap: config.bin
//Produced from mikero's Dos Tools Dll version 9.57
//https://mikero.bytex.digital/Downloads
//'now' is Tue Sep 03 22:39:58 2024 : 'file' last modified on Thu Nov 14 00:25:00 2019
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class ServerPanel_Scripts
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Scripts","JM_CF_Scripts"};
	};
};
class CfgMods
{
	class ServerPanel
	{
		dir = "ServerPanel";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ServerPanel";
		credits = "LaGTeK";
		author = "LaGTeK";
		authorID = "0";
		version = "0.1";
		extra = 0;
		type = "mod";
		inputs = "ServerPanel/SP_inputs.xml";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class imageSets
			{
				files[] = {"ServerPanel/scripts/gui/imageset/SP_Icons.imageset"};
			};
			class gameScriptModule
			{
				value = "";
				files[] = {"ServerPanel/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"ServerPanel/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"ServerPanel/scripts/5_Mission"};
			};
		};
	};
};
