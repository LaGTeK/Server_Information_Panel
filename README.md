# Server_Information_Panel

## Usage

### Installation:

-   Make sure that you have installed [Community Framework](https://github.com/Jacob-Mango/DayZ-Community-Framework) by Jacob_Mango, Arkensor and Kegan Hollern
-   Download latest release
-   Add `CF` (Community Framework) and `Server_Information_Panel` to your game and server launch options. For example:
    `-mod=@CF;@Server_Information_Panel;`

On server:

-   Copy file `ServerPanel_V3.bikey` from `ServerPanel\keys` into server `keys` folder
-   When servr will start config will be created automaticalty if not found (`ServerPanel`).
-   `ServerPanel.json` will be generated automaticatly at first start or updated from the previous config
-   U can also leave a link blank & the button will disapear, same for tabs

### Json File - [ServerPanelConfig.json](@Server_Information_Panel/ServerPanel/ServerPanel.json)
```
{
    "VERSION": "1.7",
    "SERVERNAME": "Welcome on MyDayZ server !! - Hosted By MyDayZ.eu",
    "LOGLEVEL": 1,
    "BUTTON1NAME": "DISCORD",
    "BUTTON1LINK": "https://discord.gg/KAgNn6K",
    "BUTTON2NAME": "WEBSITE",
    "BUTTON2LINK": "https://mydayz.eu",
    "BUTTON3NAME": "DONATE",
    "BUTTON3LINK": "https://www.paypal.me/MyDayZ",
    "DISPLAYPLAYERINFO": 1,
    "DISPLAYPLAYERTAB": 1,
    "DISPLAYPLAYERLIST": 1,
    "DISPLAYPLAYERPOSITION": 1,
    "DISPLAYCRAFTTAB": 1,
    "DISPLAYCURRENCY": 1,
    "CURRENCYNAME": "Rubles",
    "DISPLAYPLOGO": 1,
    "LOGOPATH": "set:dayz_gui image:ProgressDayZFull",
    "LOGO_WIDTH_PERCENTAGE": 87.0,
    "LOGO_HEIGHT_PERCENTAGE": 83.0,
    "BUTTONTAB0NAME": "TAB0",
    "BUTTONTAB1NAME": "TAB1",
    "BUTTONTAB2NAME": "TAB2",
    "BUTTONTAB3NAME": "TAB3",
    "sServerTab0": [
        "<h1>Write your h1 Title 0</h1>",
        "<p>Write your <b>information Tab0 1</b></p>",
        "<p>Write your <b>information Tab0 2</b></p>",
        "<p>Write your <b>information Tab0 3</b></p>",
        "<p>Write your <b>information Tab0 4</b></p>",
        "<h2>Write your h2 Title 5</h2>",
        "<p>Write your <i>information Tab0 6</i></p>",
        "<p>Write your <i>information Tab0 7</i></p>",
        "<p>Write your <i>information Tab0 8</i></p>",
        "<p>Write your <i>information Tab0 9</i></p>",
        "<h2>Write your h2 Title 10</h2>",
        "<p>Write your <i>information Tab0 11</i></p>",
        "<p>Write your <i>information Tab0 12</i></p>",
        "<p>Write your <i>information Tab0 13</i></p>",
        "<p>Write your <i>information Tab0 14</i></p>",
        "<h2>Write your h2 Title 15</h2>",
        "<p>Write your <b>information Tab0 16</b></p>",
        "<p>Write your <b>information Tab0 17</b></p>",
        "<p>Write your <b>information Tab0 18</b></p>",
        "<p>Write your <b>information Tab0 19</b></p>"
    ],
    "sServerTab1": [
        "<h1>Write your h1 Title 0</h1>",
        "<p>Write your <b>information Tab1 1</b></p>",
        "<p>Write your <b>information Tab1 2</b></p>",
        "<p>Write your <b>information Tab1 3</b></p>",
        "<p>Write your <b>information Tab1 4</b></p>",
        "<h2>Write your h2 Title 5</h2>",
        "<p>Write your <i>information Tab1 6</i></p>",
        "<p>Write your <i>information Tab1 7</i></p>",
        "<p>Write your <i>information Tab1 8</i></p>",
        "<p>Write your <i>information Tab1 9</i></p>",
        "<h2>Write your h2 Title 10</h2>",
        "<p>Write your <i>information Tab1 11</i></p>",
        "<p>Write your <i>information Tab1 12</i></p>",
        "<p>Write your <i>information Tab1 13</i></p>",
        "<p>Write your <i>information Tab1 14</i></p>",
        "<h2>Write your h2 Title 15</h2>",
        "<p>Write your <b>information Tab1 16</b></p>",
        "<p>Write your <b>information Tab1 17</b></p>",
        "<p>Write your <b>information Tab1 18</b></p>",
        "<p>Write your <b>information Tab1 19</b></p>"
    ],
    "sServerTab2": [
        "<h1>Write your h1 Title 0</h1>",
        "<p>Write your <b>information Tab2 1</b></p>",
        "<p>Write your <b>information Tab2 2</b></p>",
        "<p>Write your <b>information Tab2 3</b></p>",
        "<p>Write your <b>information Tab2 4</b></p>",
        "<h2>Write your h2 Title 5</h2>",
        "<p>Write your <i>information Tab2 6</i></p>",
        "<p>Write your <i>information Tab2 7</i></p>",
        "<p>Write your <i>information Tab2 8</i></p>",
        "<p>Write your <i>information Tab2 9</i></p>",
        "<h2>Write your h2 Title 10</h2>",
        "<p>Write your <i>information Tab2 11</i></p>",
        "<p>Write your <i>information Tab2 12</i></p>",
        "<p>Write your <i>information Tab2 13</i></p>",
        "<p>Write your <i>information Tab2 14</i></p>",
        "<h2>Write your h2 Title 15</h2>",
        "<p>Write your <b>information Tab2 16</b></p>",
        "<p>Write your <b>information Tab2 17</b></p>",
        "<p>Write your <b>information Tab2 18</b></p>",
        "<p>Write your <b>information Tab2 19</b></p>"
    ],
    "sServerTab3": [
        "<h1>Write your h1 Title 0</h1>",
        "<p>Write your <b>information Tab3 1</b></p>",
        "<p>Write your <b>information Tab3 2</b></p>",
        "<p>Write your <b>information Tab3 3</b></p>",
        "<p>Write your <b>information Tab3 4</b></p>",
        "<h2>Write your h2 Title 5</h2>",
        "<p>Write your <i>information Tab3 6</i></p>",
        "<p>Write your <i>information Tab3 7</i></p>",
        "<p>Write your <i>information Tab3 8</i></p>",
        "<p>Write your <i>information Tab3 9</i></p>",
        "<h2>Write your h2 Title 10</h2>",
        "<p>Write your <i>information Tab3 11</i></p>",
        "<p>Write your <i>information Tab3 12</i></p>",
        "<p>Write your <i>information Tab3 13</i></p>",
        "<p>Write your <i>information Tab3 14</i></p>",
        "<h2>Write your h2 Title 15</h2>",
        "<p>Write your <b>information Tab3 16</b></p>",
        "<p>Write your <b>information Tab3 17</b></p>",
        "<p>Write your <b>information Tab3 18</b></p>",
        "<p>Write your <b>information Tab3 19</b></p>"
    ]
}
```

## Q: Can i change default menu key ?

A: Sure, U can now change default key in your Dayz Settings, by default key is `KC_PAUSE`.
[Here is full list of available keys](https://github.com/DannyDog/DayZSAEnfScript/blob/master/dta/scripts.pbo/1_Core/proto/EnSystem.c#L156).

This is WIP, It's my first mod and I work on this in my spare time. I will my best try to bring updates frequently!

-   No reuploads or repacking allowed.

## Contributor

- Special Thanks to Shix from Aftermath server for the tab effect.
- Special Thanks to [Da0ne](https://github.com/Da0ne) from [Vanilla++](https://github.com/VanillaPlusPlus) for his help too :)
- Special Thanks to [Vaker](https://github.com/Moondarker) from [ZomBerry Admin Tools](https://steamcommunity.com/sharedfiles/filedetails/?id=1582756848) for his help.
- Special Thanks to HunterZ, TripleZ and Connor for your help with some translations :)

