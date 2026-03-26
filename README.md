# Server_Information_Panel

## Usage

### Installation:

-   Make sure that you have installed [Community Framework](https://github.com/Jacob-Mango/DayZ-Community-Framework) by Jacob_Mango, Arkensor and Kegan Hollern
-   Download latest release
-   Add `CF` (Community Framework) and `Server_Information_Panel` to your game and server launch options. For example:
    `-mod=@CF;@Server_Information_Panel;`

**Use the same mod version on client and server** (RPC / config sync must match).

On server:

-   Copy file `ServerPanel_V3.bikey` from `ServerPanel\keys` into server `keys` folder
-   When the server starts, config will be created automatically if not found under **`$profile:\ServerPanel\`**
-   **`ServerPanel.json`** is generated or upgraded on first start. The **authoritative** file for multiplayer is on the **server**; clients receive settings from the server.
-   On version upgrade, the mod copies the current file to **`ServerPanel.json.bak`** before saving. If a backup cannot be used, it may be moved to **`ServerPanel.json.bak.rejected`**.
-   You can leave a link blank and the button will disappear, same for tabs

## Recent changes (high-level)

- **Config recovery and stability**
  - The mod can recover configuration from `ServerPanel.json.bak` when the main file is missing/invalid.
  - Invalid backups may be quarantined as `ServerPanel.json.bak.rejected` to avoid retry loops.
- **UI performance**
  - Reduced unnecessary UI updates (side panel snapshots, fewer redraws) for better responsiveness.
- **Tab UX**
  - Lightweight tab transitions when switching tabs.
  - RichText content is fitted more reliably and tab scroll positions reset correctly.
- **Auto-open on first join**
  - Optional server setting to auto-open the panel once per player on that server (server-side persistence).

### Json file — [`ServerPanel.json`](https://github.com/LaGTeK/Server_Information_Panel/blob/master/Profiles/ServerPanel/ServerPanel.json)

The file name is **`ServerPanel.json`** (not `ServerPanelConfig.json`).

**`LOGLEVEL`** (module logger only; some `Print("[ServerPanel] …")` boot lines may still appear):

| Value | Effect |
|-------|--------|
| `0` | No `ServerPanelLogger` output |
| `1` | Info, warnings, errors |
| `2` | Warnings and errors only |
| `3` | Errors only |

**`DISABLE_PANEL_LOG_FILE`**: `true` = do not create `ServerPanel_*.log` under `Profiles\...\ServerPanel\Logs\` (logging goes to console only, still filtered by `LOGLEVEL`). `false` = log file when possible.

Standard JSON does **not** allow `//` comments inside the file. Use the **field reference** table below the example for what each key does.

```
{
    "VERSION": "1.8",
    "SERVERNAME": "Welcome on MyDayZ server !! - Hosted By MyDayZ.eu",
    "AUTO_OPEN_ON_FIRST_JOIN": true,
    "LOGLEVEL": 1,
    "DISABLE_PANEL_LOG_FILE": false,
    "BUTTON1NAME": "DISCORD",
    "BUTTON1LINK": "https://discord.gg/KAgNn6K",
    "BUTTON2NAME": "WEBSITE",
    "BUTTON2LINK": "https://mydayz.eu",
    "BUTTON3NAME": "DONATE",
    "BUTTON3LINK": "https://www.paypal.me/MyDayZ",
    "DISPLAYPLAYERINFO": true,
    "DISPLAYPLAYERTAB": true,
    "DISPLAYPLAYERLIST": true,
    "DISPLAYPLAYERPOSITION": true,
    "DISPLAYCRAFTTAB": true,
    "DISPLAYCURRENCY": true,
    "CURRENCYNAME": "Rubles",
    "DISPLAYPLOGO": true,
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

### Field reference (`ServerPanel.json`)

| Key | Type | Description |
|-----|------|-------------|
| `VERSION` | string | Config format version the mod expects; used when loading, upgrading, and merging defaults. Should match the version shipped with your mod build (see release notes). |
| `SERVERNAME` | string | Title shown in the panel header. |
| `AUTO_OPEN_ON_FIRST_JOIN` | bool | If `true`, the panel auto-opens **once per player** (first join) on this server. The server tracks seen player IDs in `AutoOpenSeen.json` under `$profile:\ServerPanel\`. |
| `LOGLEVEL` | int `0`–`3` | Filters `ServerPanelLogger` output only; see the table earlier in this README. Some boot `Print("[ServerPanel] …")` lines may still appear on the server. |
| `DISABLE_PANEL_LOG_FILE` | bool | `true` = no `ServerPanel_*.log` files under `ServerPanel\Logs\` (console only when `LOGLEVEL` allows). `false` = write log files when possible. |
| `BUTTON1NAME` … `BUTTON3NAME` | string | Label for each of the three top link buttons. |
| `BUTTON1LINK` … `BUTTON3LINK` | string | URL for each button. If a link is empty, that button is hidden. |
| `DISPLAYPLAYERINFO` | bool | `true` = show the **left side panel** (player quick info / layout slot). |
| `DISPLAYPLAYERTAB` | bool | `true` = show the **player stats** tab. |
| `DISPLAYPLAYERLIST` | bool | `true` = show the **player list** in the side area (only meaningful when `DISPLAYPLAYERINFO` is `true`). |
| `DISPLAYPLAYERPOSITION` | bool | `true` = show the player’s **world coordinates** where the UI supports it. |
| `DISPLAYCRAFTTAB` | bool | `true` = show the **crafting / recipes** tab. |
| `DISPLAYCURRENCY` | bool | `true` = show the **currency / money** block **only if** the mod was built with Expansion Market support (`EXPANSIONMODMARKET`). Otherwise the block stays hidden. |
| `CURRENCYNAME` | string | Display name for the currency (e.g. `Rubles`) when the currency block is shown. |
| `DISPLAYPLOGO` | bool | `true` = show the **logo** above the player list when the list layout is active; `false` = no logo area. |
| `LOGOPATH` | string | Path to the logo: DayZ **imageset** string, or `.edds` / `.paa` path. Example: `"set:dayz_gui image:ProgressDayZFull"` or a path to your own asset in the pack. |
| `LOGO_WIDTH_PERCENTAGE` | float | Logo width as a **percentage** of the logo widget (e.g. `87.0` → 87%). |
| `LOGO_HEIGHT_PERCENTAGE` | float | Logo height as a **percentage** of the logo widget (e.g. `83.0` → 83%). |
| `BUTTONTAB0NAME` … `BUTTONTAB3NAME` | string | Tab button labels for the four **custom HTML** tabs. Empty or unused names can be adjusted to match your content. |
| `sServerTab0` … `sServerTab3` | array of strings | Each entry is an **HTML fragment** (`<h1>`, `<p>`, `<b>`, `<i>`, etc.) rendered as lines in that tab’s content. Tab `0` uses `sServerTab0`, and so on. |

Booleans can be written as JSON `true` / `false`. Older files may still use `1` / `0`; the mod normalizes them when loading.

## Q: Can i change default menu key ?

A: Yes — change the binding in **DayZ → Settings → Controls** for the mod action **`SPOpenPanelMenu`**. The default preset uses **Pause** (`KC_PAUSE`).

This is WIP, It's my first mod and I work on this in my spare time. I will my best try to bring updates frequently!

-   No reuploads or repacking allowed.

## Contributor

- Special Thanks to Shix from Aftermath server for the tab effect.
- Special Thanks to [Da0ne](https://github.com/Da0ne) from [Vanilla++](https://github.com/VanillaPlusPlus) for his help too :)
- Special Thanks to [Vaker](https://github.com/Moondarker) from [ZomBerry Admin Tools](https://steamcommunity.com/sharedfiles/filedetails/?id=1582756848) for his help.
- Special Thanks to HunterZ, TripleZ and Connor for your help with some translations :)
