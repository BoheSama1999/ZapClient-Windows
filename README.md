# Zap Client for Windows [Apex External Cheat for Windows]
**Updated to Game Version v3.0.79.44 (Season 22) (2024.09.01)**

By **BoheSama** (Windows) and **Gerosity** (Linux)

All credits go to the original owners.

Instructions are provided below.

**It is not advisable to cheat on your main account as it is not worth the consequences.**

**This project will be regularly updated in line with the game and the main project (zap-client).**

# Information

To do list: </br>
    I may not have time to maintain the project because of my studies, but I will try to make time to update offsets and fix bugs
    
    1.A lot of things need to fix >_<
    </br>
    2.API and Lua/script System
        Users can use Lua scripts to call built-in APIs or nested API libraries to perform features that are not built-in by default,
        And may later change some features to Lua scripts to be loaded on demand to extend stability and richness as well as performance.
    </br>
    3.Using engine render (big challenge) 
    </br>
    4.Make it be a dll version and should be inject into apex with apc injection(then u just need a driver with apc inject or whatever to use it)
    </br>

<details>
<summary><b>Feature List (Outdated)</b></summary>

    Legitbot - Aimbot, RCS, Visuals
    Ragebot - Aimbot, RCS
    Flickbot
    Triggerbot
    Glow - Player, Viewmodel & Item
    ESP - Enemy & Teammate, Spectator List, Crosshair, Radar
    Misc - Movement, Camera (Quick Turn), Rapid Fire (For Semi-Auto & Burst Weapons), Skin Changer (Basic, not to be confused with a model changer)
    Settings - Disable Overlay, Disable ESP, FPS Cap
    Configs - Custom Configs, Premade Configs

</details>

<details>
<summary><b>Changelog</b></summary>

    24.09.07 - Offsets update
    Updated Offsets To Latest Version (Game Version v3.0.79.44)

    08.07.24 - Version 1.1.4
    Updated Offsets To Latest Version (Game Version v3.0.72.12)
    
    01.06.24 - Version 1.1.3
    Legitbot:
        - Added Spectator Check (Disables Aimbot When Being Spectated)
            - Added Spectator Notifier
    Glow:
        - Fixed Item Glow
    Sense:
        - Separated Health Bar & Shield Bar
        - Added Skeleton Detail (Detailed Or Simple)
        - Optimized And Cleaned Up File - Credits To hir0xygen
        - Spectator List & Watermark Can be Moved Anywhere Now
    Radar:
        - Radar Can Be Moved Anywhere
        - Added Two Different Identifiers - Circle & Arrowhead
        - Identifier Colors Are Now Based On Team IDs
        - Separated Identifiers And View Angle Lines
        - Radar Settings (Background, Rounding, etc)
    Misc:
        - Added Wall Jump - Credits To BoheSama
        - Added Tap Strafe (?) - Credits To BoheSama/chettoy/apexsky
    Settings:
        - Added Custom Menu Bind
        - Added Keybind Notifier
        - Added Dev Options (For Experimenting/Development/Updating)
            - Draw Local Player Weapon IDs (For Updating Weapons.hpp)
            - Draw Player Weapon IDs (For Updating/Testing Weapons.hpp)
            - Draw Player Bone IDs (For Finding Bone IDs - HitboxType.hpp)
    Configs:
        - Added Default Configs (Loads A Selected Config On Cheat Initialization)
    Other:
        - Improved Performance In Firing Range (20+ms -> 15ms)
        - Optimizations By Adding Read Delays For Info That Isn't Required - Credits To hir0xygen

    22.05.24 - Version 1.1.2
    - Updated To The Latest Version - Game Version v3.0.70.55
    - Going To "Begin" On A Full Rewrite/Brand New Cheat - Hoping For Optimization,
    Cleaner & Smoother GUI, Item ESP, And A Less Shitty Cheat Overall
    
    10.05.24 - Version 1.1.1
    - Updated offsets to latest version (Game Version v3.0.68.50)
    - Fixed Item Glow Crashes (I think...)
    - Fixed Spectator List (Might get patched sooner or later)

    07.05.24 - Version 1.1.0 - Season 21 Update
    Updated offsets to latest version (Game Version v3.0.67.34)
    
    Legitbot:
        - Added Target Visuals (Draw Line, Dot & Box On/To Aimbot Current or Best Target)
        - Added Target Information (Draw Information About Aimbot Current or Best Target)
        - Fixed Standalone RCS
    Triggerbot:
        - Added Attack Methods (Mouse or Memory, Both Support Controller, Memory has not been thoroughly tested)
        - Added Triggerbot Delay (Note: Processing Speed Affects This, Its Not Perfect & Depending On Attack Method, It Will Be Different)
    Glow:
        - Fixed Glow Max Distance (Now ACTUALLY works)
        - Added Knocked Check & Knocked Color
        - Fixed Glow Sheild Based Color Mode
        - Fixed Custom Item Glow (?)
    Sense:
        - Added Knocked Check & Knocked Color
        - Added Box, Skeleton & Head Circle Outlines
        - Re-designed Watermark And Spectator List (Still Patched) (Credits: hir0xy)
        - Fixed Position Changer
    Misc:
        - Added Superglide Modes (Manual Or Automatic, Automatic Supports Controller)
        - Re-designed Misc Tab (Credits: hir0xy)
    Settings:
        - Overlay Now Runs At An Uncapped Refresh Rate
        - If FPS Cap Is Disabled, Cheat Will Run At Refresh Rate (Recommened)
        - Added Toggle For Anti Aliased Lines - For ESP
        - Added Dead Check - Displays ESP & Glow If You Are Dead/Spectating
    Configs:
        - Added Premade Configs (Note: Not Perfect & Should Be Used As A Base For Creating Your Own
        Legit Config, Fine Tune To Your Liking!)
    Other:
        - Added Version Check (Can Be Skipped) (Credits: hir0xy)
        - Fixed A Couple Error Messages (Credits: hir0xy)
        - Optimizations (Untested) & Cleaner Code  (Credits: hir0xy)
        - Fixed Overlay Errors (Credits: hir0xy)
    
    22.04.24 - Version 1.0.6.1
    Updated offsets to latest version (Game Version v3.0.65.42)
    Busy atm but will eventually start working on a better and more optimised version of this

    8.04.24 - Version 1.0.6
    Updated offsets to latest version (Game Version v3.0.63.32)

    1.04.24
    Updated offsets to latest version (Game version v3.0.62.30)

    30.03.24 - Version 1.0.5
    Legitbot:
        New Aimbot Mode (An old xap-client smoothing method), testing for now
        Smoothing Modes (Static and randomised) (For randomised I recommend setting the values close together!)
    Ragebot:
        Fixes
    Flickbot:
        Fixes
    Misc:
        SuperGlide FPS (Set it to your in-game FPS, 75 is probably the best)
    Settings:
        Removed Gamemode Toggle - It now automatically switches based on what 
        gamemode your playing
    Other:
        Randomised Overlay Name now actually works
        Added a run.sh script which randomises the zapclient binary and hides PID once 
        executed - use this instead of ./zapclient

    26.03.24 - Version 1.0.3
    Updated to latest game version (Game Version v3.0.62.29)

    24.03.24 - Version 1.0.2
    
    Complete GUI Overhaul
    Fixed issues with aimbot & triggerbot
    Added Ragebot, Flickbot, Viewmodel Glow, Glow Customizations, ESP Features, BHop, QuickTurn, RapidFire, Overlay Settings
    Bunch a stuff that I cant remember all at once
</details>

<details>
<summary><b>Video Previews</b></summary>

</details>

# Other Repositories:
https://github.com/Gerosity/zap-client - Linux Version

https://github.com/Gerosity/zap-client-Read-Only-   - A read memory only version for Linux

# Installation
Driver API on Utils/Driver.hpp, DriverHID.hpp.

Please build it using Visual Studio. (You will need to have your own driver.)

Finally, ensure that there is a folder named "Configs" located next to the executable file.

**6.Please press the "Insert" key to toggle the menu. You can only interact with the menu and the game when the menu is active.**

# Credits:
    https://github.com/Gerosity/zap-client - Linux Version
    https://github.com/Nexilist/xap-client - for the base, massive credits to them
    https://github.com/arturzxc/grinder - alternate aimbot mode, most of the misc features
    https://github.com/Braziliana/T_TApe - custom config system
    https://www.unknowncheats.me/forum/apex-legends/ - A TON of help, offsets, many additional features & more
    wafflesgaming - aimbot help, Extra ESP Features such as 2D Corners
    0xAgartha & ghostrazzor - run.sh script (Randomises zapclient binary & Hides PID before execution)
    hir0xy - Version Checker, Overlay Fixes, Cleaner GUI & optimizations here and there

# !<< Disclaimer / 免责声明 >>!
# English
  This is a disclaimer regarding the use of the software. Please read and ensure that you fully understand the following terms before using the software:

1. This software is provided based on open-source principles and is intended solely for academic research and technical exploration. Users are free to access, use, modify, and distribute the software, but must comply with relevant laws and terms.

2. Users bear full responsibility for any consequences and liabilities arising from the use, modification, or exploitation of this software. The providers, contributors, and copyright owners of this software disclaim all responsibility, including but not limited to the applicability, security, and integrity of the software.

3. This software is provided without any form of express or implied warranty, including but not limited to the warranties of fitness for a particular purpose and non-infringement. Users should assume the risks when using this software.

4. This software may include components or code contributed by third parties, which may be subject to separate license agreements. Users should carefully read and comply with the relevant third-party license agreements.

5. In no event, whether in contract, tort, or otherwise, shall the providers, contributors, and copyright owners of this software be liable for any direct, indirect, incidental, special, or consequential damages, even if advised of the possibility of such damages.

By downloading, installing, or using this software, you agree to accept all the terms and conditions of this disclaimer. If you do not agree with any part of this disclaimer, please refrain from using this software.

The disclaimer may be modified based on software version updates, and users are advised to regularly review the latest version. We reserve the right to modify and interpret the disclaimer at any time.

# Chinese  
  特此声明，以下是有关使用本软件的免责声明。请在使用本软件之前仔细阅读并确保您完全理解以下条款：

1. 本软件是基于开源原则提供的，仅供学术研究和技术探讨之用。使用者可自由获取、使用、修改和分发本软件，但需遵循相关法规和条款。

2. 使用者对于使用、修改或利用本软件所产生的一切后果和责任负全部责任。本软件的提供者、贡献者及版权所有者概不负责，包括但不限于软件的适用性、安全性和完整性。

3. 本软件不提供任何形式的明示或暗示保证，包括但不限于对特定用途的适用性和不侵权的保证。使用者在使用本软件时应当自行承担风险。

4. 本软件可能包含第三方贡献的组件或代码，这些组件或代码可能受到单独的许可协议约束。使用者需仔细阅读并遵守相关的第三方许可协议。

5. 在任何情况下，无论是在合同、侵权或对软件的不当使用和其他方面，本软件的提供者、贡献者及版权所有者均不对任何直接、间接、附带、特殊或间接损害承担责任，即使事先被告知有可能发生此类损害。

通过下载、安装、使用本软件，即表示您同意接受此免责声明的全部条款和条件。如您不同意本免责声明的任何部分，请不要使用本软件。

免责声明可能会根据软件版本的更新而进行修改，敬请使用者定期查阅最新版本。我们保留在任何时候对免责声明进行修改和解释的权利。

