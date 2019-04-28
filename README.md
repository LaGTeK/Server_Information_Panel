# Server_Information_Panel

## Usage

### Installation:

-   Make sure that you have installed [Community Framework](https://github.com/Jacob-Mango/DayZ-Community-Framework) by Jacob_Mango, Arkensor and Kegan Hollern
-   Download latest release
-   Add `Community Framework` and `Server_Information_Panel` to your game and server launch options. For example:
    `-mod=@Community-Framework;@Server_Information_Panel;`

On server:

-   Copy file `LaGTeK.bikey` from `ServerPanel\keys` into server `keys` folder
-   Copy folder `ServerPanel` from mod folder to `[ServerProfilesFolder]`.
-   Customize your informations from `ServerDescription.txt` and `ServerRules.txt`
    (You are now able to add what u want, i've tried with some special character and only `|` and `#` can't be used ! ) Don't put more than 110 chars per line !
-   You can now add some Tabs like About or Crafting tab, Customize your informations from `ServerTab2.txt` file, and `ServerTab3.txt`
    (You are now able to add what u want, i've tried with some special character and only `|` and `#` can't be used ! ) Don't put more than 110 chars per line !
-   `ServerPanelConfig.json` is now used to configure your buttons, links and ur Server Name, Don't leave any blank space in Button name & Button Link, follow the exemple. U Can now add more buttons and Tabs are now here. U can also hide player information, it will show just ingame name and a magnific picture :)
-   U can also leave link blank, the button will disapear, same for tabs

### Json File - [ServerPanel.json](@Server_Information_Panel/ServerPanel/ServerPanel.json)

 - `ServerName = Your Server name`
 - `Button1Name = Your Button1Name`
 - `Button1Link = Your Button1Link`
 - `Button2Name = Your Button2Name`
 - `Button2Link = Your Button2Link`
 - `Button3Name = Your Button3Name`
 - `Button3Link = Your Button3Link`
 - `ButtonTab0Name = Name of the First Tab`
 - `ButtonTab1Name = Name of the Second Tab`
 - `ButtonTab2Name = Name of the Third Tab`
 - `ButtonTab3Name = Name of the Fourth Tab`
 - `PlayerInfo = You can display or hide player information with this parameter`
 - `UseScriptLog = You can use separate log from script.log for Server Panel Mod `

### Old installation
- `UseScriptLog` param has been added, u have to set it up manualy in ur json file 
- You can also change the name of the two first Tab now
(Exemple here: [@Server_Information_Panel/ServerPanel/ServerPanel.json](@Server_Information_Panel/ServerPanel/ServerPanel.json))
-   `ServerName.txt` & `ServerConfigNew.cfg` are not used used anymore, these files should be deleted and remplaced with `ServerPanelConfig.json` automaticatly


## Q: Can i change default menu key ?

A: Sure, U can now change default menu key client side with editing `ServerPanelKey.json` file in your `Documents` folder (`C:\Users\%username%\Documents`).

```"SPMenuKey": "KC_NUMPAD6"```

And change `KC_PAUSE` (which stands for `PAUSE|BREAK` key on keyboard) to any key you want.
[Here is full list of available keys](https://github.com/DannyDog/DayZSAEnfScript/blob/master/dta/scripts.pbo/1_Core/proto/EnSystem.c#L156).

Example of resulting line:
* ```"SPMenuKey": "KC_BACKSLASH"```

This is WIP, It's my first mod and I work on this in my spare time. I will my best try to bring updates frequently!

-   No reuploads or repacking allowed.

## Contributor

- Special Thanks to [Vaker](https://github.com/Moondarker) from [ZomBerry Admin Tools](https://steamcommunity.com/sharedfiles/filedetails/?id=1582756848) for his help.
- Special Thanks to [Da0ne](https://github.com/Da0ne) from [Vanilla++](https://github.com/VanillaPlusPlus) for his help too :)
