#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputTypes.hpp"
#include "XDisplay.hpp"

namespace Features {

    int TotalSpectators = 0;

    namespace Home {
        bool IsMenuOpened = true;
    };

    namespace Settings {
        InputKeyType MenuBind = InputKeyType::KEYBOARD_INSERT;
        bool ESPEnabled = true;
        bool DeadCheck = false;
        bool OverlayEnabled = true;
        bool AntiAliasedLines = true;
        bool FPSCap = false;
        int CappedFPS = 144;
        bool ShowKeybinds = false;
        float KeybindColor[4] = { 0.99, 0, 0, 0.99 };
    };

    namespace Dev {
        bool Enabled = false;
        bool LocalWeapon = false;
        bool EnemyWeapon = false;
        bool SkeletonIDs = false;
        int BoneRange = 20;
    };
    
    namespace AimbotHitboxes {
        HitboxType Hitbox = HitboxType::UpperChest;

        //Advanced Hitboxes
        HitboxType P2020Hitbox = HitboxType::UpperChest;
        HitboxType RE45Hitbox = HitboxType::UpperChest;
        HitboxType AlternatorHitbox = HitboxType::UpperChest;
        HitboxType R99Hitbox = HitboxType::UpperChest;
        HitboxType R301Hitbox = HitboxType::UpperChest;
        HitboxType SpitfireHitbox = HitboxType::UpperChest;
        HitboxType G7Hitbox = HitboxType::UpperChest;
        HitboxType FlatlineHitbox = HitboxType::UpperChest;
        HitboxType HemlockHitbox = HitboxType::UpperChest;
        HitboxType RepeaterHitbox = HitboxType::UpperChest;
        HitboxType RampageHitbox = HitboxType::UpperChest;
        HitboxType CARSMGHitbox = HitboxType::UpperChest;
        HitboxType HavocHitbox = HitboxType::UpperChest;
        HitboxType DevotionHitbox = HitboxType::UpperChest;
        HitboxType LSTARHitbox = HitboxType::UpperChest;
        HitboxType TripleTakeHitbox = HitboxType::UpperChest;
        HitboxType VoltHitbox = HitboxType::UpperChest;
        HitboxType NemesisHitbox = HitboxType::UpperChest;
        HitboxType MozambiqueHitbox = HitboxType::UpperChest;
        HitboxType EVA8Hitbox = HitboxType::UpperChest;
        HitboxType PeacekeeperHitbox = HitboxType::UpperChest;
        HitboxType MastiffHitbox = HitboxType::UpperChest;
        HitboxType LongbowHitbox = HitboxType::UpperChest;
        HitboxType ChargeRifleHitbox = HitboxType::UpperChest;
        HitboxType SentinelHitbox = HitboxType::UpperChest;
        HitboxType WingmanHitbox = HitboxType::UpperChest;
        HitboxType ProwlerHitbox = HitboxType::UpperChest;
        HitboxType BocekHitbox = HitboxType::UpperChest;
        HitboxType KraberHitbox = HitboxType::UpperChest;
        HitboxType ThrowingKnifeHitbox = HitboxType::UpperChest;
    };

    namespace AimbotBinds {
        InputKeyType AimBind = InputKeyType::MOUSE_Left;
        InputKeyType ExtraBind = InputKeyType::MOUSE_Right;

        //Advanced Binds
        InputKeyType P2020AimBind = InputKeyType::MOUSE_Left;
        InputKeyType P2020ExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType RE45AimBind = InputKeyType::MOUSE_Left;
        InputKeyType RE45ExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType AlternatorAimBind = InputKeyType::MOUSE_Left;
        InputKeyType AlternatorExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType R99AimBind = InputKeyType::MOUSE_Left;
        InputKeyType R99ExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType R301AimBind = InputKeyType::MOUSE_Left;
        InputKeyType R301ExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType SpitfireAimBind = InputKeyType::MOUSE_Left;
        InputKeyType SpitfireExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType G7AimBind = InputKeyType::MOUSE_Left;
        InputKeyType G7ExtraBind = InputKeyType::MOUSE_Right;

        InputKeyType FlatlineAimBind = InputKeyType::MOUSE_Left;
        InputKeyType FlatlineExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType HemlockAimBind = InputKeyType::MOUSE_Left;
        InputKeyType HemlockExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType RepeaterAimBind = InputKeyType::MOUSE_Left;
        InputKeyType RepeaterExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType RampageAimBind = InputKeyType::MOUSE_Left;
        InputKeyType RampageExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType CARSMGAimBind = InputKeyType::MOUSE_Left;
        InputKeyType CARSMGExtraBind = InputKeyType::INPUT_NONE;
        
        InputKeyType HavocAimBind = InputKeyType::MOUSE_Left;
        InputKeyType HavocExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType DevotionAimBind = InputKeyType::MOUSE_Left;
        InputKeyType DevotionExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType LSTARAimBind = InputKeyType::MOUSE_Left;
        InputKeyType LSTARExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType TripleTakeAimBind = InputKeyType::MOUSE_Left;
        InputKeyType TripleTakeExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType VoltAimBind = InputKeyType::MOUSE_Left;
        InputKeyType VoltExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType NemesisAimBind = InputKeyType::MOUSE_Left;
        InputKeyType NemesisExtraBind = InputKeyType::INPUT_NONE;

        InputKeyType MozambiqueAimBind = InputKeyType::MOUSE_Left;
        InputKeyType MozambiqueExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType EVA8AimBind = InputKeyType::MOUSE_Left;
        InputKeyType EVA8ExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType PeacekeeperAimBind = InputKeyType::MOUSE_Left;
        InputKeyType PeacekeeperExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType MastiffAimBind = InputKeyType::MOUSE_Left;
        InputKeyType MastiffExtraBind = InputKeyType::MOUSE_Right;

        InputKeyType LongbowAimBind = InputKeyType::MOUSE_Left;
        InputKeyType LongbowExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType ChargeRifleAimBind = InputKeyType::MOUSE_Left;
        InputKeyType ChargeRifleExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType SentinelAimBind = InputKeyType::MOUSE_Left;
        InputKeyType SentinelExtraBind = InputKeyType::MOUSE_Right;

        InputKeyType WingmanAimBind = InputKeyType::MOUSE_Left;
        InputKeyType WingmanExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType ProwlerAimBind = InputKeyType::MOUSE_Left;
        InputKeyType ProwlerExtraBind = InputKeyType::INPUT_NONE;
        InputKeyType BocekAimBind = InputKeyType::MOUSE_Left;
        InputKeyType BocekExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType KraberAimBind = InputKeyType::MOUSE_Left;
        InputKeyType KraberExtraBind = InputKeyType::MOUSE_Right;
        InputKeyType ThrowingKnifeAimBind = InputKeyType::MOUSE_Left;
        InputKeyType ThrowingKnifeExtraBind = InputKeyType::INPUT_NONE;
    }

    namespace Aimbot {      
        bool AimbotEnabled = false;
        int BindMethod = 0;
        int AimbotMode = 0; // Cubic Beizer (xap-client) or Grinder (Possibly linear?) or [New] Cubic Beizer (Testing)
        int InputMethod = 0; // MoveMouse or Controller (Write To ViewAngles)

        bool ClosestHitbox = false;

        bool SpectatorCheck = false;
        bool SpectatorNotifier = true;

        bool OnFire = true;
        bool OnADS = true;
        bool VisCheck = true;
        bool TeamCheck = true;
        bool TargetSwitching = true;
        int Priority = 0;

        bool PredictMovement = true;
        bool PredictBulletDrop = true;

        float FinalDistance = 0;
        float Smooth = 0.9;

        float Speed = 16;
        int SmoothingMethod = 0; // 0 = Static, 1 = Random

        float HipfireSmooth = 0.9;
        float ADSSmooth = 0.99;
        float MinHipfireSmooth = 0.9;
        float MaxHipfireSmooth = 0.99;
        float MinADSSmooth = 0.9;
        float MaxADSSmooth = 0.99;

        //AimMode 3 (Testing)
        float MouseHipfireSmoothing = 300;
        float MouseADSSmoothing = 350;
        float MouseExtraSmoothing = 5000;
        float MinMouseHipfireSmoothing = 300;
        float MaxMouseHipfireSmoothing = 315;
        float MinMouseADSSmoothing = 350;
        float MaxMouseADSSmoothing = 360;

        int Delay = 10;
        float FOV = 15;
        float ZoomScale = 3.3;
        float MinDistance = 1;
        float HipfireDistance = 60;
        float ZoomDistance = 160;
        
        //AimMode 2
        float HipfireSmooth1 = 250;
        float ADSSmooth1 = 230;
        float MinHipfireSmooth1 = 250;
        float MaxHipfireSmooth1 = 300;
        float MinADSSmooth1 = 290;
        float MaxADSSmooth1 = 325;
        float ExtraSmoothing = 1000;
        float Deadzone = 0.5;
        float FOV1 = 10;
        float MinDistance2 = 1;
        float MaxDistance2 = 200;

        
        //Weapon Toggles
        std::set<int> AimList = {};
        //Light
        bool P2020 = true;
        bool RE45 = true;
        bool Alternator = true;
        bool R99 = true;
        bool R301 = true;
        bool Spitfire = true;
        bool G7 = true;
        
        //Heavy
        bool Flatline = true;
        bool Hemlock = true;
        bool Repeater = true;
        bool Rampage = true;
        bool CARSMG = true;
        
        //Energy
        bool Havoc = true;
        bool Devotion = true;
        bool LSTAR = true;
        bool TripleTake = true;
        bool Volt = true;
        bool Nemesis = true;
        
        //Shotgun
        bool Mozambique = true;
        bool EVA8 = true;
        bool Peacekeeper = true;
        bool Mastiff = true;
        
        //Snipers
        bool Longbow = true;
        bool ChargeRifle = true;
        bool Sentinel = true; 
        
        //Legendary
        bool Wingman = true;
        bool Prowler = true;
        bool Bocek = true;
        bool Kraber = true;
        bool Knife = true;
        
        //---------------Advanced---------------//
        bool AdvancedAim = false;
        bool AdvancedFire = true;
        bool AdvancedADS = false;
        int AdvancedSmoothingMethod = 0; // 0 = Static, 1 = Random
        //Aimbot Mode 0 - xap-client
        bool AdvancedClosestHitbox = true;
        float AdvancedHitbox = 2;
        float AdvancedSpeed = 20;
        float AdvancedSmooth = 0.99;
        float AdvancedHipfireSmooth = 0.99;
        float AdvancedADSSmooth = 0.99;
        float AdvancedMinHipfireSmooth = 0.98;
        float AdvancedMaxHipfireSmooth = 0.99;
        float AdvancedMinADSSmooth = 0.98;
        float AdvancedMaxADSSmooth = 0.99;
        //Aimbot Mode 1 - Grinder
        float AdvancedHipfireSmooth1 = 250;
        float AdvancedADSSmooth1 = 275;
        float AdvancedMinHipfireSmooth1 = 0.98;
        float AdvancedMaxHipfireSmooth1 = 0.99;
        float AdvancedMinADSSmooth1 = 0.98;
        float AdvancedMaxADSSmooth1 = 0.99;
        float AdvancedExtraSmooth1 = 5000;
        float AdvancedFOV1 = 10;
        float AdvancedDeadzone = 0.5;
        float AdvancedMinDistance1 = 1;
        float AdvancedMaxDistance1 = 200;

        //Advanced OnFire & OnADS - Aimbot Mode 0 & 1 - xap-client & grinder
        bool P2020Fire = true;
        bool P2020ADS = false;
        bool RE45Fire = true;
        bool RE45ADS = false;
        bool AlternatorFire = true;
        bool AlternatorADS = false;
        bool R99Fire = true;
        bool R99ADS = false;
        bool R301Fire = true;
        bool R301ADS = false;
        bool SpitfireFire = true;
        bool SpitfireADS = false;
        bool G7Fire = true;
        bool G7ADS = false;
        bool FlatlineFire = true;
        bool FlatlineADS = false;
        bool HemlockFire = true;
        bool HemlockADS = false;
        bool RepeaterFire = true;
        bool RepeaterADS = false;
        bool RampageFire = true;
        bool RampageADS = false;
        bool CARSMGFire = true;
        bool CARSMGADS = false;
        bool HavocFire = true;
        bool HavocADS = false;
        bool DevotionFire = true;
        bool DevotionADS = false;
        bool LSTARFire = true;
        bool LSTARADS = false;
        bool TripleTakeFire = true;
        bool TripleTakeADS = false;
        bool VoltFire = true;
        bool VoltADS = false;
        bool NemesisFire = true;
        bool NemesisADS = false;
        bool MozambiqueFire = true;
        bool MozambiqueADS = false;
        bool EVA8Fire = true;
        bool EVA8ADS = false;
        bool PeacekeeperFire = true;
        bool PeacekeeperADS = false;
        bool MastiffFire = true;
        bool MastiffADS = false;
        bool LongbowFire = true;
        bool LongbowADS = false;
        bool ChargeRifleFire = true;
        bool ChargeRifleADS = false;
        bool SentinelFire = true;
        bool SentinelADS = false;
        bool WingmanFire = true;
        bool WingmanADS = false;
        bool ProwlerFire = true;
        bool ProwlerADS = false;
        bool KraberFire = true;
        bool KraberADS = false;
        bool BocekFire = true;
        bool BocekADS = false;
        bool ThrowingKnifeFire = true;
        bool ThrowingKnifeADS = false;
        
        //Advanced Speed, Smooth + Hitbox - Aimbot Mode 0 - xap-client
        bool P2020ClosestHitbox = true;
        float P2020Hitbox = 2;
        float P2020Speed = 10;
        float P2020HipfireSmooth = 0.99;
        float P2020ADSSmooth = 0.99;
        int P2020SmoothingMethod = 0;
        float P2020MinHipfireSmooth = 0.98;
        float P2020MaxHipfireSmooth = 0.99;
        float P2020MinADSSmooth = 0.98;
        float P2020MaxADSSmooth = 0.99;
        float P2020FOV = 10;
        float P2020ZoomScale = 3.0;
        bool RE45ClosestHitbox = true;
        float RE45Hitbox = 2;
        float RE45Speed = 10;
        float RE45HipfireSmooth = 0.99;
        float RE45ADSSmooth = 0.99;
        int RE45SmoothingMethod = 0;
        float RE45MinHipfireSmooth = 0.98;
        float RE45MaxHipfireSmooth = 0.99;
        float RE45MinADSSmooth = 0.98;
        float RE45MaxADSSmooth = 0.99;
        float RE45FOV = 10;
        float RE45ZoomScale = 3.0;
        bool AlternatorClosestHitbox = true;
        float AlternatorHitbox = 2;
        float AlternatorSpeed = 10;
        float AlternatorHipfireSmooth = 0.99;
        float AlternatorADSSmooth = 0.99;
        int AlternatorSmoothingMethod = 0;
        float AlternatorMinHipfireSmooth = 0.98;
        float AlternatorMaxHipfireSmooth = 0.99;
        float AlternatorMinADSSmooth = 0.98;
        float AlternatorMaxADSSmooth = 0.99;
        float AlternatorFOV = 10;
        float AlternatorZoomScale = 3.0;
        bool R99ClosestHitbox = true;
        float R99Hitbox = 2;
        float R99Speed = 10;
        float R99HipfireSmooth = 0.99;
        float R99ADSSmooth = 0.99;
        int R99SmoothingMethod = 0;
        float R99MinHipfireSmooth = 0.98;
        float R99MaxHipfireSmooth = 0.99;
        float R99MinADSSmooth = 0.98;
        float R99MaxADSSmooth = 0.99;
        float R99FOV = 10;
        float R99ZoomScale = 3.0;
        bool R301ClosestHitbox = true;
        float R301Hitbox = 2;
        float R301Speed = 10;
        float R301HipfireSmooth = 0.99;
        float R301ADSSmooth = 0.99;
        int R301SmoothingMethod = 0;
        float R301MinHipfireSmooth = 0.98;
        float R301MaxHipfireSmooth = 0.99;
        float R301MinADSSmooth = 0.98;
        float R301MaxADSSmooth = 0.99;
        float R301FOV = 10;
        float R301ZoomScale = 3.0;
        bool SpitfireClosestHitbox = true;
        float SpitfireHitbox = 2;
        float SpitfireSpeed = 10;
        float SpitfireHipfireSmooth = 0.99;
        float SpitfireADSSmooth = 0.99;
        int SpitfireSmoothingMethod = 0;
        float SpitfireMinHipfireSmooth = 0.98;
        float SpitfireMaxHipfireSmooth = 0.99;
        float SpitfireMinADSSmooth = 0.98;
        float SpitfireMaxADSSmooth = 0.99;
        float SpitfireFOV = 10;
        float SpitfireZoomScale = 3.0;
        bool G7ClosestHitbox = true;
        float G7Hitbox = 2;
        float G7Speed = 10;
        float G7HipfireSmooth = 0.99;
        float G7ADSSmooth = 0.99;
        int G7SmoothingMethod = 0;
        float G7MinHipfireSmooth = 0.98;
        float G7MaxHipfireSmooth = 0.99;
        float G7MinADSSmooth = 0.98;
        float G7MaxADSSmooth = 0.99;
        float G7FOV = 10;
        float G7ZoomScale = 3.0;
        //Heavy
        bool FlatlineClosestHitbox = true;
        float FlatlineHitbox = 2;
        float FlatlineSpeed = 10;
        float FlatlineHipfireSmooth = 0.99;
        float FlatlineADSSmooth = 0.99;
        int FlatlineSmoothingMethod = 0;
        float FlatlineMinHipfireSmooth = 0.98;
        float FlatlineMaxHipfireSmooth = 0.99;
        float FlatlineMinADSSmooth = 0.98;
        float FlatlineMaxADSSmooth = 0.99;
        float FlatlineFOV = 10;
        float FlatlineZoomScale = 3.0;
        bool HemlockClosestHitbox = true;
        float HemlockHitbox = 2;
        float HemlockSpeed = 10;
        float HemlockHipfireSmooth = 0.99;
        float HemlockADSSmooth = 0.99;
        int HemlockSmoothingMethod = 0;
        float HemlockMinHipfireSmooth = 0.98;
        float HemlockMaxHipfireSmooth = 0.99;
        float HemlockMinADSSmooth = 0.98;
        float HemlockMaxADSSmooth = 0.99;
        float HemlockFOV = 10;
        float HemlockZoomScale = 3.0;
        bool RepeaterClosestHitbox = true;
        float RepeaterHitbox = 2;
        float RepeaterSpeed = 10;
        float RepeaterHipfireSmooth = 0.99;
        float RepeaterADSSmooth = 0.99;
        int RepeaterSmoothingMethod = 0;
        float RepeaterMinHipfireSmooth = 0.98;
        float RepeaterMaxHipfireSmooth = 0.99;
        float RepeaterMinADSSmooth = 0.98;
        float RepeaterMaxADSSmooth = 0.99;
        float RepeaterFOV = 10;
        float RepeaterZoomScale = 3.0;
        bool RampageClosestHitbox = true;
        float RampageHitbox = 2;
        float RampageSpeed = 10;
        float RampageHipfireSmooth = 0.99;
        float RampageADSSmooth = 0.99;
        int RampageSmoothingMethod = 0;
        float RampageMinHipfireSmooth = 0.98;
        float RampageMaxHipfireSmooth = 0.99;
        float RampageMinADSSmooth = 0.98;
        float RampageMaxADSSmooth = 0.99;
        float RampageFOV = 10;
        float RampageZoomScale = 3.0;
        bool CARSMGClosestHitbox = true;
        float CARSMGHitbox = 2;
        float CARSMGSpeed = 10;
        float CARSMGHipfireSmooth = 0.99;
        float CARSMGADSSmooth = 0.99;
        int CARSMGSmoothingMethod = 0;
        float CARSMGMinHipfireSmooth = 0.98;
        float CARSMGMaxHipfireSmooth = 0.99;
        float CARSMGMinADSSmooth = 0.98;
        float CARSMGMaxADSSmooth = 0.99;
        float CARSMGFOV = 10;
        float CARSMGZoomScale = 3.0;
        //Energy
        bool HavocClosestHitbox = true;
        float HavocHitbox = 2;
        float HavocSpeed = 10;
        float HavocHipfireSmooth = 0.99;
        float HavocADSSmooth = 0.99;
        int HavocSmoothingMethod = 0;
        float HavocMinHipfireSmooth = 0.98;
        float HavocMaxHipfireSmooth = 0.99;
        float HavocMinADSSmooth = 0.98;
        float HavocMaxADSSmooth = 0.99;
        float HavocFOV = 10;
        float HavocZoomScale = 3.0;
        bool DevotionClosestHitbox = true;
        float DevotionHitbox = 2;
        float DevotionSpeed = 10;
        float DevotionHipfireSmooth = 0.99;
        float DevotionADSSmooth = 0.99;
        int DevotionSmoothingMethod = 0;
        float DevotionMinHipfireSmooth = 0.98;
        float DevotionMaxHipfireSmooth = 0.99;
        float DevotionMinADSSmooth = 0.98;
        float DevotionMaxADSSmooth = 0.99;
        float DevotionFOV = 10;
        float DevotionZoomScale = 3.0;
        bool LSTARClosestHitbox = true;
        float LSTARHitbox = 2;
        float LSTARSpeed = 10;
        float LSTARHipfireSmooth = 0.99;
        float LSTARADSSmooth = 0.99;
        int LSTARSmoothingMethod = 0;
        float LSTARMinHipfireSmooth = 0.98;
        float LSTARMaxHipfireSmooth = 0.99;
        float LSTARMinADSSmooth = 0.98;
        float LSTARMaxADSSmooth = 0.99;
        float LSTARFOV = 10;
        float LSTARZoomScale = 3.0;
        bool TripleTakeClosestHitbox = true;
        float TripleTakeHitbox = 2;
        float TripleTakeSpeed = 10;
        float TripleTakeHipfireSmooth = 0.99;
        float TripleTakeADSSmooth = 0.99;
        int TripleTakeSmoothingMethod = 0;
        float TripleTakeMinHipfireSmooth = 0.98;
        float TripleTakeMaxHipfireSmooth = 0.99;
        float TripleTakeMinADSSmooth = 0.98;
        float TripleTakeMaxADSSmooth = 0.99;
        float TripleTakeFOV = 10;
        float TripleTakeZoomScale = 3.0;
        bool VoltClosestHitbox = true;
        float VoltHitbox = 2;
        float VoltSpeed = 10;
        float VoltHipfireSmooth = 0.99;
        float VoltADSSmooth = 0.99;
        int VoltSmoothingMethod = 0;
        float VoltMinHipfireSmooth = 0.98;
        float VoltMaxHipfireSmooth = 0.99;
        float VoltMinADSSmooth = 0.98;
        float VoltMaxADSSmooth = 0.99;
        float VoltFOV = 10;
        float VoltZoomScale = 3.0;
        bool NemesisClosestHitbox = true;
        float NemesisHitbox = 2;
        float NemesisSpeed = 10;
        float NemesisHipfireSmooth = 0.99;
        float NemesisADSSmooth = 0.99;
        int NemesisSmoothingMethod = 0;
        float NemesisMinHipfireSmooth = 0.98;
        float NemesisMaxHipfireSmooth = 0.99;
        float NemesisMinADSSmooth = 0.98;
        float NemesisMaxADSSmooth = 0.99;
        float NemesisFOV = 10;
        float NemesisZoomScale = 3.0;
        //Shotguns
        bool MozambiqueClosestHitbox = true;
        float MozambiqueHitbox = 2;
        float MozambiqueSpeed = 10;
        float MozambiqueHipfireSmooth = 0.99;
        float MozambiqueADSSmooth = 0.99;
        int MozambiqueSmoothingMethod = 0;
        float MozambiqueMinHipfireSmooth = 0.98;
        float MozambiqueMaxHipfireSmooth = 0.99;
        float MozambiqueMinADSSmooth = 0.98;
        float MozambiqueMaxADSSmooth = 0.99;
        float MozambiqueFOV = 10;
        float MozambiqueZoomScale = 3.0;
        bool EVA8ClosestHitbox = true;
        float EVA8Hitbox = 2;
        float EVA8Speed = 10;
        float EVA8HipfireSmooth = 0.99;
        float EVA8ADSSmooth = 0.99;
        int EVA8SmoothingMethod = 0;
        float EVA8MinHipfireSmooth = 0.98;
        float EVA8MaxHipfireSmooth = 0.99;
        float EVA8MinADSSmooth = 0.98;
        float EVA8MaxADSSmooth = 0.99;
        float EVA8FOV = 10;
        float EVA8ZoomScale = 3.0;
        bool PeacekeeperClosestHitbox = true;
        float PeacekeeperHitbox = 2;
        float PeacekeeperSpeed = 10;
        float PeacekeeperHipfireSmooth = 0.99;
        float PeacekeeperADSSmooth = 0.99;
        int PeacekeeperSmoothingMethod = 0;
        float PeacekeeperMinHipfireSmooth = 0.98;
        float PeacekeeperMaxHipfireSmooth = 0.99;
        float PeacekeeperMinADSSmooth = 0.98;
        float PeacekeeperMaxADSSmooth = 0.99;
        float PeacekeeperFOV = 10;
        float PeacekeeperZoomScale = 3.0;
        bool MastiffClosestHitbox = true;
        float MastiffHitbox = 2;
        float MastiffSpeed = 10;
        float MastiffHipfireSmooth = 0.99;
        float MastiffADSSmooth = 0.99;
        int MastiffSmoothingMethod = 0;
        float MastiffMinHipfireSmooth = 0.98;
        float MastiffMaxHipfireSmooth = 0.99;
        float MastiffMinADSSmooth = 0.98;
        float MastiffMaxADSSmooth = 0.99;
        float MastiffFOV = 10;
        float MastiffZoomScale = 3.0;
        //Snipers
        bool LongbowClosestHitbox = true;
        float LongbowHitbox = 2;
        float LongbowSpeed = 10;
        float LongbowHipfireSmooth = 0.99;
        float LongbowADSSmooth = 0.99;
        int LongbowSmoothingMethod = 0;
        float LongbowMinHipfireSmooth = 0.98;
        float LongbowMaxHipfireSmooth = 0.99;
        float LongbowMinADSSmooth = 0.98;
        float LongbowMaxADSSmooth = 0.99;
        float LongbowFOV = 10;
        float LongbowZoomScale = 3.0;
        bool ChargeRifleClosestHitbox = true;
        float ChargeRifleHitbox = 2;
        float ChargeRifleSpeed = 10;
        float ChargeRifleHipfireSmooth = 0.99;
        float ChargeRifleADSSmooth = 0.99;
        int ChargeRifleSmoothingMethod = 0;
        float ChargeRifleMinHipfireSmooth = 0.98;
        float ChargeRifleMaxHipfireSmooth = 0.99;
        float ChargeRifleMinADSSmooth = 0.98;
        float ChargeRifleMaxADSSmooth = 0.99;
        float ChargeRifleFOV = 10;
        float ChargeRifleZoomScale = 3.0;
        bool SentinelClosestHitbox = true;
        float SentinelHitbox = 2;
        float SentinelSpeed = 10;
        float SentinelHipfireSmooth = 0.99;
        float SentinelADSSmooth = 0.99;
        int SentinelSmoothingMethod = 0;
        float SentinelMinHipfireSmooth = 0.98;
        float SentinelMaxHipfireSmooth = 0.99;
        float SentinelMinADSSmooth = 0.98;
        float SentinelMaxADSSmooth = 0.99;
        float SentinelFOV = 10;
        float SentinelZoomScale = 3.0;
        //Legendary
        bool WingmanClosestHitbox = true;
        float WingmanHitbox = 2;
        float WingmanSpeed = 10;
        float WingmanHipfireSmooth = 0.99;
        float WingmanADSSmooth = 0.99;
        int WingmanSmoothingMethod = 0;
        float WingmanMinHipfireSmooth = 0.98;
        float WingmanMaxHipfireSmooth = 0.99;
        float WingmanMinADSSmooth = 0.98;
        float WingmanMaxADSSmooth = 0.99;
        float WingmanFOV = 10;
        float WingmanZoomScale = 3.0;
        bool ProwlerClosestHitbox = true;
        float ProwlerHitbox = 2;
        float ProwlerSpeed = 10;
        float ProwlerHipfireSmooth = 0.99;
        float ProwlerADSSmooth = 0.99;
        int ProwlerSmoothingMethod = 0;
        float ProwlerMinHipfireSmooth = 0.98;
        float ProwlerMaxHipfireSmooth = 0.99;
        float ProwlerMinADSSmooth = 0.98;
        float ProwlerMaxADSSmooth = 0.99;
        float ProwlerFOV = 10;
        float ProwlerZoomScale = 3.0;
        bool KraberClosestHitbox = true;
        float KraberHitbox = 2;
        float KraberSpeed = 10;
        float KraberHipfireSmooth = 0.99;
        float KraberADSSmooth = 0.99;
        int KraberSmoothingMethod = 0;
        float KraberMinHipfireSmooth = 0.98;
        float KraberMaxHipfireSmooth = 0.99;
        float KraberMinADSSmooth = 0.98;
        float KraberMaxADSSmooth = 0.99;
        float KraberFOV = 10;
        float KraberZoomScale = 3.0;
        bool BocekClosestHitbox = true;
        float BocekHitbox = 2;
        float BocekSpeed = 10;
        float BocekHipfireSmooth = 0.99;
        float BocekADSSmooth = 0.99;
        int BocekSmoothingMethod = 0;
        float BocekMinHipfireSmooth = 0.98;
        float BocekMaxHipfireSmooth = 0.99;
        float BocekMinADSSmooth = 0.98;
        float BocekMaxADSSmooth = 0.99;
        float BocekFOV = 10;
        float BocekZoomScale = 3.0;
        bool ThrowingKnifeClosestHitbox = true;
        float ThrowingKnifeHitbox = 2;
        float ThrowingKnifeSpeed = 10;
        float ThrowingKnifeHipfireSmooth = 0.99;
        float ThrowingKnifeADSSmooth = 0.99;
        int ThrowingKnifeSmoothingMethod = 0;
        float ThrowingKnifeMinHipfireSmooth = 0.98;
        float ThrowingKnifeMaxHipfireSmooth = 0.99;
        float ThrowingKnifeMinADSSmooth = 0.98;
        float ThrowingKnifeMaxADSSmooth = 0.99;
        float ThrowingKnifeFOV = 10;
        float ThrowingKnifeZoomScale = 3.0;
        
        //Advanced Smooth - Aimbot Mode 1 - Grinder
        float P2020HipfireSmooth1 = 250;
        float P2020ADSSmooth1 = 275;
        float P2020MinHipfireSmooth1 = 250;
        float P2020MaxHipfireSmooth1 = 275;
        float P2020MinADSSmooth1 = 275;
        float P2020MaxADSSmooth1 = 300;
        float P2020ExtraSmooth1 = 5000;
        float P2020Deadzone = 0.5;
        float P2020FOV1 = 10;
        float P2020MinDistance1 = 1;
        float P2020MaxDistance1 = 200;
        float RE45HipfireSmooth1 = 250;
        float RE45ADSSmooth1 = 275;
        float RE45MinHipfireSmooth1 = 250;
        float RE45MaxHipfireSmooth1 = 275;
        float RE45MinADSSmooth1 = 275;
        float RE45MaxADSSmooth1 = 300;
        float RE45ExtraSmooth1 = 5000;
        float RE45Deadzone = 0.5;
        float RE45FOV1 = 10;
        float RE45MinDistance1 = 1;
        float RE45MaxDistance1 = 200;
        float AlternatorHipfireSmooth1 = 250;
        float AlternatorADSSmooth1 = 275;
        float AlternatorMinHipfireSmooth1 = 250;
        float AlternatorMaxHipfireSmooth1 = 275;
        float AlternatorMinADSSmooth1 = 275;
        float AlternatorMaxADSSmooth1 = 300;
        float AlternatorExtraSmooth1 = 5000;
        float AlternatorDeadzone = 0.5;
        float AlternatorFOV1 = 10;
        float AlternatorMinDistance1 = 1;
        float AlternatorMaxDistance1 = 200;
        float R99HipfireSmooth1 = 250;
        float R99ADSSmooth1 = 275;
        float R99MinHipfireSmooth1 = 250;
        float R99MaxHipfireSmooth1 = 275;
        float R99MinADSSmooth1 = 275;
        float R99MaxADSSmooth1 = 300;
        float R99ExtraSmooth1 = 5000;
        float R99Deadzone = 0.5;
        float R99FOV1 = 10;
        float R99MinDistance1 = 1;
        float R99MaxDistance1 = 200;
        float R301HipfireSmooth1 = 250;
        float R301ADSSmooth1 = 275;
        float R301MinHipfireSmooth1 = 250;
        float R301MaxHipfireSmooth1 = 275;
        float R301MinADSSmooth1 = 275;
        float R301MaxADSSmooth1 = 300;
        float R301ExtraSmooth1 = 5000;
        float R301Deadzone = 0.5;
        float R301FOV1 = 10;
        float R301MinDistance1 = 1;
        float R301MaxDistance1 = 200;
        float SpitfireHipfireSmooth1 = 250;
        float SpitfireADSSmooth1 = 275;
        float SpitfireMinHipfireSmooth1 = 250;
        float SpitfireMaxHipfireSmooth1 = 275;
        float SpitfireMinADSSmooth1 = 275;
        float SpitfireMaxADSSmooth1 = 300;
        float SpitfireExtraSmooth1 = 5000;
        float SpitfireDeadzone = 0.5;
        float SpitfireFOV1 = 10;
        float SpitfireMinDistance1 = 1;
        float SpitfireMaxDistance1 = 200;
        float G7HipfireSmooth1 = 250;
        float G7ADSSmooth1 = 275;
        float G7MinHipfireSmooth1 = 250;
        float G7MaxHipfireSmooth1 = 275;
        float G7MinADSSmooth1 = 275;
        float G7MaxADSSmooth1 = 300;
        float G7ExtraSmooth1 = 5000;
        float G7Deadzone = 0.5;
        float G7FOV1 = 10;
        float G7MinDistance1 = 1;
        float G7MaxDistance1 = 200;
        
        float FlatlineHipfireSmooth1 = 250;
        float FlatlineADSSmooth1 = 275;
        float FlatlineMinHipfireSmooth1 = 250;
        float FlatlineMaxHipfireSmooth1 = 275;
        float FlatlineMinADSSmooth1 = 275;
        float FlatlineMaxADSSmooth1 = 300;
        float FlatlineExtraSmooth1 = 5000;
        float FlatlineDeadzone = 0.5;
        float FlatlineFOV1 = 10;
        float FlatlineMinDistance1 = 1;
        float FlatlineMaxDistance1 = 200;
        float HemlockHipfireSmooth1 = 250;
        float HemlockADSSmooth1 = 275;
        float HemlockMinHipfireSmooth1 = 250;
        float HemlockMaxHipfireSmooth1 = 275;
        float HemlockMinADSSmooth1 = 275;
        float HemlockMaxADSSmooth1 = 300;
        float HemlockExtraSmooth1 = 5000;
        float HemlockDeadzone = 0.5;
        float HemlockFOV1 = 10;
        float HemlockMinDistance1 = 1;
        float HemlockMaxDistance1 = 200;
        float RepeaterHipfireSmooth1 = 250;
        float RepeaterADSSmooth1 = 275;
        float RepeaterMinHipfireSmooth1 = 250;
        float RepeaterMaxHipfireSmooth1 = 275;
        float RepeaterMinADSSmooth1 = 275;
        float RepeaterMaxADSSmooth1 = 300;
        float RepeaterExtraSmooth1 = 5000;
        float RepeaterDeadzone = 0.5;
        float RepeaterFOV1 = 10;
        float RepeaterMinDistance1 = 1;
        float RepeaterMaxDistance1 = 200;
        float RampageHipfireSmooth1 = 250;
        float RampageMinHipfireSmooth1 = 250;
        float RampageMaxHipfireSmooth1 = 275;
        float RampageMinADSSmooth1 = 275;
        float RampageMaxADSSmooth1 = 300;
        float RampageADSSmooth1 = 275;
        float RampageExtraSmooth1 = 5000;
        float RampageDeadzone = 0.5;
        float RampageFOV1 = 10;
        float RampageMinDistance1 = 1;
        float RampageMaxDistance1 = 200;
        float CARSMGHipfireSmooth1 = 250;
        float CARSMGADSSmooth1 = 275;
        float CARSMGMinHipfireSmooth1 = 250;
        float CARSMGMaxHipfireSmooth1 = 275;
        float CARSMGMinADSSmooth1 = 275;
        float CARSMGMaxADSSmooth1 = 300;
        float CARSMGExtraSmooth1 = 5000;
        float CARSMGDeadzone = 0.5;
        float CARSMGFOV1 = 10;
        float CARSMGMinDistance1 = 1;
        float CARSMGMaxDistance1 = 200;
        
        float HavocHipfireSmooth1 = 250;
        float HavocADSSmooth1 = 275;
        float HavocMinHipfireSmooth1 = 250;
        float HavocMaxHipfireSmooth1 = 275;
        float HavocMinADSSmooth1 = 275;
        float HavocMaxADSSmooth1 = 300;
        float HavocExtraSmooth1 = 5000;
        float HavocDeadzone = 0.5;
        float HavocFOV1 = 10;
        float HavocMinDistance1 = 1;
        float HavocMaxDistance1 = 200;
        float DevotionHipfireSmooth1 = 250;
        float DevotionADSSmooth1 = 275;
        float DevotionMinHipfireSmooth1 = 250;
        float DevotionMaxHipfireSmooth1 = 275;
        float DevotionMinADSSmooth1 = 275;
        float DevotionMaxADSSmooth1 = 300;
        float DevotionExtraSmooth1 = 5000;
        float DevotionDeadzone = 0.5;
        float DevotionFOV1 = 10;
        float DevotionMinDistance1 = 1;
        float DevotionMaxDistance1 = 200;
        float LSTARHipfireSmooth1 = 250;
        float LSTARADSSmooth1 = 275;
        float LSTARMinHipfireSmooth1 = 250;
        float LSTARMaxHipfireSmooth1 = 275;
        float LSTARMinADSSmooth1 = 275;
        float LSTARMaxADSSmooth1 = 300;
        float LSTARExtraSmooth1 = 5000;
        float LSTARDeadzone = 0.5;
        float LSTARFOV1 = 10;
        float LSTARMinDistance1 = 1;
        float LSTARMaxDistance1 = 200;
        float TripleTakeHipfireSmooth1 = 250;
        float TripleTakeADSSmooth1 = 275;
        float TripleTakeMinHipfireSmooth1 = 250;
        float TripleTakeMaxHipfireSmooth1 = 275;
        float TripleTakeMinADSSmooth1 = 275;
        float TripleTakeMaxADSSmooth1 = 300;
        float TripleTakeExtraSmooth1 = 5000;
        float TripleTakeDeadzone = 0.5;
        float TripleTakeFOV1 = 10;
        float TripleTakeMinDistance1 = 1;
        float TripleTakeMaxDistance1 = 200;
        float VoltHipfireSmooth1 = 250;
        float VoltADSSmooth1 = 275;
        float VoltMinHipfireSmooth1 = 250;
        float VoltMaxHipfireSmooth1 = 275;
        float VoltMinADSSmooth1 = 275;
        float VoltMaxADSSmooth1 = 300;
        float VoltExtraSmooth1 = 5000;
        float VoltDeadzone = 0.5;
        float VoltFOV1 = 10;
        float VoltMinDistance1 = 1;
        float VoltMaxDistance1 = 200;
        float NemesisHipfireSmooth1 = 250;
        float NemesisADSSmooth1 = 275;
        float NemesisMinHipfireSmooth1 = 250;
        float NemesisMaxHipfireSmooth1 = 275;
        float NemesisMinADSSmooth1 = 275;
        float NemesisMaxADSSmooth1 = 300;
        float NemesisExtraSmooth1 = 5000;
        float NemesisDeadzone = 0.5;
        float NemesisFOV1 = 10;
        float NemesisMinDistance1 = 1;
        float NemesisMaxDistance1 = 200;
        
        float MozambiqueHipfireSmooth1 = 250;
        float MozambiqueADSSmooth1 = 275;
        float MozambiqueMinHipfireSmooth1 = 250;
        float MozambiqueMaxHipfireSmooth1 = 275;
        float MozambiqueMinADSSmooth1 = 275;
        float MozambiqueMaxADSSmooth1 = 300;
        float MozambiqueExtraSmooth1 = 5000;
        float MozambiqueDeadzone = 0.5;
        float MozambiqueFOV1 = 10;
        float MozambiqueMinDistance1 = 1;
        float MozambiqueMaxDistance1 = 200;
        float EVA8HipfireSmooth1 = 250;
        float EVA8ADSSmooth1 = 275;
        float EVA8MinHipfireSmooth1 = 250;
        float EVA8MaxHipfireSmooth1 = 275;
        float EVA8MinADSSmooth1 = 275;
        float EVA8MaxADSSmooth1 = 300;
        float EVA8ExtraSmooth1 = 5000;
        float EVA8Deadzone = 0.5;
        float EVA8FOV1 = 10;
        float EVA8MinDistance1 = 1;
        float EVA8MaxDistance1 = 200;
        float PeacekeeperHipfireSmooth1 = 250;
        float PeacekeeperADSSmooth1 = 275;
        float PeacekeeperMinHipfireSmooth1 = 250;
        float PeacekeeperMaxHipfireSmooth1 = 275;
        float PeacekeeperMinADSSmooth1 = 275;
        float PeacekeeperMaxADSSmooth1 = 300;
        float PeacekeeperExtraSmooth1 = 5000;
        float PeacekeeperDeadzone = 0.5;
        float PeacekeeperFOV1 = 10;
        float PeacekeeperMinDistance1 = 1;
        float PeacekeeperMaxDistance1 = 200;
        float MastiffHipfireSmooth1 = 250;
        float MastiffADSSmooth1 = 275;
        float MastiffMinHipfireSmooth1 = 250;
        float MastiffMaxHipfireSmooth1 = 275;
        float MastiffMinADSSmooth1 = 275;
        float MastiffMaxADSSmooth1 = 300;
        float MastiffExtraSmooth1 = 5000;
        float MastiffDeadzone = 0.5;
        float MastiffFOV1 = 10;
        float MastiffMinDistance1 = 1;
        float MastiffMaxDistance1 = 200;
        
        float LongbowHipfireSmooth1 = 250;
        float LongbowADSSmooth1 = 275;
        float LongbowMinHipfireSmooth1 = 250;
        float LongbowMaxHipfireSmooth1 = 275;
        float LongbowMinADSSmooth1 = 275;
        float LongbowMaxADSSmooth1 = 300;
        float LongbowExtraSmooth1 = 5000;
        float LongbowDeadzone = 0.5;
        float LongbowFOV1 = 10;
        float LongbowMinDistance1 = 1;
        float LongbowMaxDistance1 = 200;
        float ChargeRifleHipfireSmooth1 = 250;
        float ChargeRifleADSSmooth1 = 275;
        float ChargeRifleMinHipfireSmooth1 = 250;
        float ChargeRifleMaxHipfireSmooth1 = 275;
        float ChargeRifleMinADSSmooth1 = 275;
        float ChargeRifleMaxADSSmooth1 = 300;
        float ChargeRifleExtraSmooth1 = 5000;
        float ChargeRifleDeadzone = 0.5;
        float ChargeRifleFOV1 = 10;
        float ChargeRifleMinDistance1 = 1;
        float ChargeRifleMaxDistance1 = 200;
        float SentinelHipfireSmooth1 = 250;
        float SentinelADSSmooth1 = 275;
        float SentinelMinHipfireSmooth1 = 250;
        float SentinelMaxHipfireSmooth1 = 275;
        float SentinelMinADSSmooth1 = 275;
        float SentinelMaxADSSmooth1 = 300;
        float SentinelExtraSmooth1 = 5000;
        float SentinelDeadzone = 0.5;
        float SentinelFOV1 = 10;
        float SentinelMinDistance1 = 1;
        float SentinelMaxDistance1 = 200;
        
        float WingmanHipfireSmooth1 = 250;
        float WingmanADSSmooth1 = 275;
        float WingmanMinHipfireSmooth1 = 250;
        float WingmanMaxHipfireSmooth1 = 275;
        float WingmanMinADSSmooth1 = 275;
        float WingmanMaxADSSmooth1 = 300;
        float WingmanExtraSmooth1 = 5000;
        float WingmanDeadzone = 0.5;
        float WingmanFOV1 = 10;
        float WingmanMinDistance1 = 1;
        float WingmanMaxDistance1 = 200;
        float ProwlerHipfireSmooth1 = 250;
        float ProwlerADSSmooth1 = 275;
        float ProwlerMinHipfireSmooth1 = 250;
        float ProwlerMaxHipfireSmooth1 = 275;
        float ProwlerMinADSSmooth1 = 275;
        float ProwlerMaxADSSmooth1 = 300;
        float ProwlerExtraSmooth1 = 5000;
        float ProwlerDeadzone = 0.5;
        float ProwlerFOV1 = 10;
        float ProwlerMinDistance1 = 1;
        float ProwlerMaxDistance1 = 200;
        float BocekHipfireSmooth1 = 250;
        float BocekADSSmooth1 = 275;
        float BocekMinHipfireSmooth1 = 250;
        float BocekMaxHipfireSmooth1 = 275;
        float BocekMinADSSmooth1 = 275;
        float BocekMaxADSSmooth1 = 300;
        float BocekExtraSmooth1 = 5000;
        float BocekDeadzone = 0.5;
        float BocekFOV1 = 10;
        float BocekMinDistance1 = 1;
        float BocekMaxDistance1 = 200;
        float KraberHipfireSmooth1 = 250;
        float KraberADSSmooth1 = 275;
        float KraberMinHipfireSmooth1 = 250;
        float KraberMaxHipfireSmooth1 = 275;
        float KraberMinADSSmooth1 = 275;
        float KraberMaxADSSmooth1 = 300;
        float KraberExtraSmooth1 = 5000;
        float KraberDeadzone = 0.5;
        float KraberFOV1 = 10;
        float KraberMinDistance1 = 1;
        float KraberMaxDistance1 = 200;
        float ThrowingKnifeHipfireSmooth1 = 250;
        float ThrowingKnifeADSSmooth1 = 275;
        float ThrowingKnifeMinHipfireSmooth1 = 250;
        float ThrowingKnifeMaxHipfireSmooth1 = 275;
        float ThrowingKnifeMinADSSmooth1 = 275;
        float ThrowingKnifeMaxADSSmooth1 = 300;
        float ThrowingKnifeExtraSmooth1 = 5000;
        float ThrowingKnifeDeadzone = 0.5;
        float ThrowingKnifeFOV1 = 10;
        float ThrowingKnifeMinDistance1 = 1;    
        float ThrowingKnifeMaxDistance1 = 200;
    };

    namespace Ragebot {
        bool RagebotEnabled = false;

        bool RageAimbot = false;
        int AimMethod = 0;
        bool ClosestHitbox = false;
        HitboxType Hitbox = HitboxType::Head;
        int BindMethod = 0;
        bool OnFire = true;
        bool OnADS = true;
        InputKeyType AimBind = InputKeyType::MOUSE_Left;
        InputKeyType ExtraBind = InputKeyType::MOUSE_Right;
        bool VisCheck = true;
        bool TeamCheck = true;
        int Priority = 0;
        bool AutoShoot = false;
        bool PredictMovement = true;
        bool PredictBulletDrop = true;
        float PreditcionAmount = 255;
        float FinalDistance = 0;
        float Speed = 1;
        float Smooth = 0.9;
        float HipfireSmooth = 0.9;
        float ADSSmooth = 0.99;
        float SmoothDistance = 100;
        int Delay = 10;
        float FOV = 10;
        float ZoomScale = 3.0;
        float MinDistance = 1;
        float HipfireDistance = 60;
        float ZoomDistance = 160;

        //Weapon Toggles
        std::set<int> RageList = {};
        //Light
        bool P2020 = true;
        bool RE45 = true;
        bool Alternator = true;
        bool R99 = true;
        bool R301 = true;
        bool Spitfire = true;
        bool G7 = true;
        
        //Heavy
        bool Flatline = true;
        bool Hemlock = true;
        bool Repeater = true;
        bool Rampage = true;
        bool CARSMG = true;
        
        //Energy
        bool Havoc = true;
        bool Devotion = true;
        bool LSTAR = true;
        bool TripleTake = true;
        bool Volt = true;
        bool Nemesis = true;
        
        //Shotgun
        bool Mozambique = true;
        bool EVA8 = true;
        bool Peacekeeper = true;
        bool Mastiff = true;
        
        //Snipers
        bool Longbow = true;
        bool ChargeRifle = true;
        bool Sentinel = true; 
        
        //Legendary
        bool Wingman = true;
        bool Prowler = true;
        bool Bocek = true;
        bool Kraber = true;
        bool Knife = true;

        bool RageRCS = true;
        float RecoilRate = 100.0f;
    };

    namespace Flickbot {
        bool Flickbot = false;
        int FlickbotMethod = 0; //0 = Mouse, 1 = Memory
        InputKeyType FlickBind = InputKeyType::KEYBOARD_X;
        bool ClosestHitbox = false;
        HitboxType Hitbox = HitboxType::UpperChest;
        int Priority = 0;
        bool AutoShoot = true;
        int AutoShootDelay = 16;
        bool FlickBack = false;
        int FlickBackDelay = 16;
        float FlickBackSmoothing = 0.001;
        bool PredictMovement = true;
        bool PredictBulletDrop = true;
        bool TeamCheck = true;
        float PreditcionAmount = 255;
        float FinalDistance = 0;
        float HipfireSmooth = 0.9;
        float ADSSmooth = 0.99;
        float SmoothDistance = 100;
        int Delay = 10;
        float FOV = 10;
        float ZoomScale = 3.0;
        float MinDistance = 1;
        float HipfireDistance = 60;
        float ZoomDistance = 160;

        float Smooth = 0.9;
        float FlickBackSmooth = 0.9;

        //Weapon Toggles
        std::set<int> FlickList = {};
        //Light
        bool P2020 = false;
        bool RE45 = false;
        bool Alternator = false;
        bool R99 = false;
        bool R301 = false;
        bool Spitfire = false;
        bool G7 = false;
        
        //Heavy
        bool Flatline = false;
        bool Hemlock = false;
        bool Repeater = false;
        bool Rampage = false;
        bool CARSMG = false;
        
        //Energy
        bool Havoc = false;
        bool Devotion = false;
        bool LSTAR = false;
        bool TripleTake = false;
        bool Volt = false;
        bool Nemesis = false;
        
        //Shotgun
        bool Mozambique = true;
        bool EVA8 = true;
        bool Peacekeeper = true;
        bool Mastiff = true;
        
        //Snipers
        bool Longbow = false;
        bool ChargeRifle = false;
        bool Sentinel = false; 
        
        //Legendary
        bool Wingman = true;
        bool Prowler = false;
        bool Bocek = false;
        bool Kraber = false;
        bool Knife = false;
    };
    
    namespace RCS {
        bool RCSEnabled = false;
        std::set<int> RCSList = {};
        int RCSMode = 0;

        bool OnADS = true;

        float PitchPower = 3;
        float YawPower = 3;
        float PitchReduction = 50;
        float YawReduction = 50;
        
        //Weapon Toggles
        //Light
        bool P2020 = true;
        bool RE45 = true;
        bool Alternator = true;
        bool R99 = true;
        bool R301 = true;
        bool Spitfire = true;
        bool G7 = true;
        
        //Heavy
        bool Flatline = true;
        bool Hemlock = true;
        bool Repeater = true;
        bool Rampage = true;
        bool CARSMG = true;
        
        //Energy
        bool Havoc = true;
        bool Devotion = true;
        bool LSTAR = true;
        bool TripleTake = true;
        bool Volt = true;
        bool Nemesis = true;
        
        //Shotgun
        bool Mozambique = true;
        bool EVA8 = true;
        bool Peacekeeper = true;
        bool Mastiff = true;
        
        //Snipers
        bool Longbow = true;
        bool ChargeRifle = true;
        bool Sentinel = true; 
        
        //Legendary
        bool Wingman = true; //Emotional damage!
        bool Prowler = true;
        bool Kraber = false;
        
        //---------------Advanced---------------//
        bool AdvancedRCS = false;
        float AdvancedPitchPower = 10;
        float AdvancedYawPower = 10;
        float AdvancedPitchReduction = 25;
        float AdvancedYawReduction = 25;
        
        //Weapons
        //Light
        float P2020Pitch = 10;
        float P2020Yaw = 10;
        float P2020PitchReduction = 25;
        float P2020YawReduction = 25;
        float RE45Pitch = 10;
        float RE45Yaw = 10;
        float RE45PitchReduction = 25;
        float RE45YawReduction = 25;
        float AlternatorPitch = 10;
        float AlternatorYaw = 10;
        float AlternatorPitchReduction = 25;
        float AlternatorYawReduction = 25;
        float R99Pitch = 10;
        float R99Yaw = 10;
        float R99PitchReduction = 25;
        float R99YawReduction = 25;
        float R301Pitch = 10;
        float R301Yaw = 10;
        float R301PitchReduction = 25;
        float R301YawReduction = 25;
        float SpitfirePitch = 10;
        float SpitfireYaw = 10;
        float SpitfirePitchReduction = 25;
        float SpitfireYawReduction = 25;
        float G7Pitch = 10;
        float G7Yaw = 10;
        float G7PitchReduction = 25;
        float G7YawReduction = 25;
        //Heavy
        float FlatlinePitch = 10;
        float FlatlineYaw = 10;
        float FlatlinePitchReduction = 25;
        float FlatlineYawReduction = 25;
        float HemlockPitch = 10;
        float HemlockYaw = 10;
        float HemlockPitchReduction = 25;
        float HemlockYawReduction = 25;
        float RepeaterPitch = 10;
        float RepeaterYaw = 10;
        float RepeaterPitchReduction = 25;
        float RepeaterYawReduction = 25;
        float RampagePitch = 10;
        float RampageYaw = 10;
        float RampagePitchReduction = 25;
        float RampageYawReduction = 25;
        float CARSMGPitch = 10;
        float CARSMGYaw = 10;
        float CARSMGPitchReduction = 25;
        float CARSMGYawReduction = 25;
        //Energy
        float HavocPitch = 10;
        float HavocYaw = 10;
        float HavocPitchReduction = 25;
        float HavocYawReduction = 25;
        float DevotionPitch = 10;
        float DevotionYaw = 10;
        float DevotionPitchReduction = 25;
        float DevotionYawReduction = 25;
        float LSTARPitch = 10;
        float LSTARYaw = 10;
        float LSTARPitchReduction = 25;
        float LSTARYawReduction = 25;
        float TripleTakePitch = 10;
        float TripleTakeYaw = 10;
        float TripleTakePitchReduction = 25;
        float TripleTakeYawReduction = 25;
        float VoltPitch = 10;
        float VoltYaw = 10;
        float VoltPitchReduction = 25;
        float VoltYawReduction = 25;
        float NemesisPitch = 10;
        float NemesisYaw = 10;
        float NemesisPitchReduction = 25;
        float NemesisYawReduction = 25;
        //Shotguns
        float MozambiquePitch = 10;
        float MozambiqueYaw = 10;
        float MozambiquePitchReduction = 25;
        float MozambiqueYawReduction = 25;
        float EVA8Pitch = 10;
        float EVA8Yaw = 10;
        float EVA8PitchReduction = 25;
        float EVA8YawReduction = 25;
        float PeacekeeperPitch = 10;
        float PeacekeeperYaw = 10;
        float PeacekeeperPitchReduction = 25;
        float PeacekeeperYawReduction = 25;
        float MastiffPitch = 10;
        float MastiffYaw = 10;
        float MastiffPitchReduction = 25;
        float MastiffYawReduction = 25;
        //Snipers
        float LongbowPitch = 10;
        float LongbowYaw = 10;
        float LongbowPitchReduction = 25;
        float LongbowYawReduction = 25;
        float ChargeRiflePitch = 10;
        float ChargeRifleYaw = 10;
        float ChargeRiflePitchReduction = 25;
        float ChargeRifleYawReduction = 25;
        float SentinelPitch = 10;
        float SentinelYaw = 10;
        float SentinelPitchReduction = 25;
        float SentinelYawReduction = 25;
        //Legendary
        float WingmanPitch = 10;
        float WingmanYaw = 10;
        float WingmanPitchReduction = 25;
        float WingmanYawReduction = 25;
        float ProwlerPitch = 10;
        float ProwlerYaw = 10;
        float ProwlerPitchReduction = 25;
        float ProwlerYawReduction = 25;
        float KraberPitch = 10;
        float KraberYaw = 10;
        float KraberPitchReduction = 25;
        float KraberYawReduction = 25;
    };
    
    namespace Triggerbot {
        bool Enabled = false;
        int BindMethod = 0;
        int AttackMethod = 1; // 0 = Mouse, 1 = Memory
        InputKeyType TriggerBind = InputKeyType::MOUSE_Right;
        bool OnADS = true;
        bool HipfireShotguns = false;
        int Delay = 40;
        float Range = 200;

        //Weapon Toggles

        //Light
        bool P2020 = false;
        bool RE45 = false;
        bool Alternator = false;
        bool R99 = false;
        bool R301 = false;
        bool Spitfire = false;
        bool G7 = true;
        
        //Heavy
        bool Flatline = false;
        bool Hemlock = false;
        bool Repeater = true;
        bool Rampage = false;
        bool CARSMG = false;
        
        //Energy
        bool Havoc = false;
        bool Devotion = false;
        bool LSTAR = false;
        bool TripleTake = true;
        bool Volt = false;
        bool Nemesis = false;
        
        //Shotgun
        bool Mozambique = true;
        bool EVA8 = true;
        bool Peacekeeper = true;
        bool Mastiff = true;
        
        //Snipers
        bool Longbow = true;
        bool ChargeRifle = true;
        bool Sentinel = true; 
        
        //Legendary
        bool Wingman = true;
        bool Prowler = false;
        bool Bocek = true;
        bool Kraber = true;
        bool Knife = true;

        // Advanced Triggerbot
        bool AdvancedTriggerbot = false;
        
        float P2020Range = 150;
        float RE45Range = 150;
        float AlternatorRange = 150;
        float R99Range = 150;
        float R301Range = 150;
        float SpitfireRange = 150;
        float G7Range = 150;

        float FlatlineRange = 150;
        float HemlockRange = 150;
        float ProwlerRange = 150;
        float RepeaterRange = 150;
        float RampageRange = 150;
        float CARSMGRange = 150;

        float HavocRange = 150;
        float DevotionRange = 150;
        float LSTARRange = 150;
        float TripleTakeRange = 150;
        float VoltRange = 150;
        float NemesisRange = 150;

        float MozambiqueRange = 150;
        float PeacekeeperRange = 150;
        float MastiffRange = 150;

        float LongbowRange = 150;
        float ChargeRifleRange = 150;
        float SentinelRange = 150;

        float WingmanRange = 150;
        float EVA8Range = 150;
        float BocekRange = 150;
        float KraberRange = 150;
        float ThrowingKnifeRange = 150;
    };
    
    namespace Glow {
        // Glow
        bool NewGlow = false;
        bool KnockedCheck = false;
        float GlowMaxDistance = 200;
        
        int GlowColorMode = 1;
        int GlowColorShieldMode = 0;
        int GlowRadius = 64;
        int InsideFunction = 2; //Leave
        int OutlineFunction = 125; //Leave
        int BodyStyle = 15;
        int OutlineStyle = 1;
        
        bool ViewModelGlow = false;
        static int ViewModelGlowSetting = 65;
        static int ViewModelGlowCombo;

        namespace Item {
            bool ItemGlow = false;
            bool Common = true;
            bool Rare = true;
            bool Epic = true;
            bool Gold = true;
            bool Legendary = true;
            bool Weapons = false;
            bool Ammo = false;
            bool Deathbox = true;

            int ItemGlowThickness = 35;

            int SelectedInsideStyle = 2;
            int SelectedOutlineStyle = 3;
        };
    };

    namespace Sense {
        bool Enabled = true;

        namespace Enemy {
            bool DrawEnemy = true;

            bool DrawBoxes = true;
            bool BoxOutline = true;
            int BoxType = 0;
            int BoxStyle = 1;
            float BoxThickness = 1.0;

            bool DrawSkeleton = true;
            bool SkeletonOutline = false;
            int SkeletonDetail = 0; // 0 = Detailed, 1 = Simple
            float SkeletonThickness = 1.0;
            bool DrawHeadCircle = true;
            bool HeadCircleOutline = false;
            float HeadCircleThickness = 1.0;

            bool DrawBars = true;
            bool HealthBar = true;
            bool ShieldBar = true;
            int BarMode = 2;
            int BarStyle = 0;
            float BarThickness = 1.0f;
            float BarThickness2 = 1.05f;
            float BarHeight = 5.0f;
            float BarWidth = 60.0f;
            int BarColorMode = 0;

            int WeaponColorType = 1;
            bool DrawDistance = true;
            
            int TracerPosition = 0;
            int TracerBone = 0;
            bool DrawTracers = false;
            float TracerThickness = 2.0;
            bool DrawNames = true;
            bool DrawSeer = false;
            bool DrawStatus = false;
            bool DrawWeapon = true;
            bool DrawLegend = true;
            bool ShowMaxStatusValues = true;
        };

        namespace Teammate {
            bool DrawTeam = false;

            bool DrawBoxes = true;
            bool BoxOutline = true;
            int BoxType = 0;
            int BoxStyle = 0;
            float BoxThickness = 1.0;

            bool DrawSkeleton = true;
            bool SkeletonOutline = false;
            int SkeletonDetail = 0; // 0 = Detailed, 1 = Simple
            float SkeletonThickness = 1.0;
            bool DrawHeadCircle = true;
            bool HeadCircleOutline = false;
            float HeadCircleThickness = 1.0;

            bool DrawBars = true;
            bool HealthBar = true;
            bool ShieldBar = true;
            int BarMode = 2;
            int BarStyle = 0;
            float BarThickness = 1.0f;
            float BarThickness2 = 0.05f;
            float BarHeight = 5.0f;
            float BarWidth = 60.0f;
            int BarColorMode = 0;
            bool BarBackground = false;

            int WeaponColorType = 1;
            bool DrawDistance = true;
            
            int TracerPosition = 0;
            int TracerBone = 0;
            bool DrawTracers = true;
            float TracerThickness = 2.0;
            bool DrawNames = true;
            bool DrawSeer = false;
            bool DrawStatus = true;
            bool DrawWeapon = false;
            bool DrawLegend = false;
            bool ShowMaxStatusValues = true;
        };

        namespace Positions {
            // 0 = Top 1, 1 = Top 2, 2 = Bottom 1, 3 = Bottom 2, 4 = Bottom 3
            int NamePosition = 0;
            int DistancePosition = 0;
            int LegendPosition = 2;
            int WeaponPosition = 3;
            int StatusPosition = 4;
        };

        // Aimbot
        bool DrawFOVCircle = true;
        bool DrawFilledFOVCircle = false;
        float FOVThickness = 1.0;
        float GameFOV = 120;

        bool DrawTargetLine = false;
        bool DrawTargetDot = false;
        bool DrawTargetBox = false;
        int TargetMode = 0; // 0 = Aimbot Target, 1 = Best Target
        int TargetBoneMode = 0; // 0 = Aimbot Settings, 1 = Custom
        int TargetSelectedBone = 0;
        int TargetBone = 0;
        HitboxType TargetHitbox = HitboxType::Head;
        int TargetLineThickness = 1;
        int TargetDotRadius = 1500;
        int TargetBoxMode = 0;
        int TargetBoxThickness = 1;
        int TargetBoxSize = 4;

        bool DrawTargetInfo = false;
        int TargetInfoDisplayMode = 0;
        bool DrawTargetInfoName = false;
        int TargetInfoNamePos = 0;
        bool DrawTargetInfoLegend = false;
        int TargetInfoLegendPos = 1;
        bool DrawTargetInfoTeamID = false;
        bool DrawTargetInfoDistance = false;
        bool DrawTargetInfoWeapon = false;
        int TargetInfoWeaponPos = 2;
        bool DrawTargetInfoHealth = false;
        int TargetInfoHealthPos = 3;
        bool DrawTargetInfoShield = false;
        int TargetInfoShieldPos = 4;

        int TargetInfoColorMode = 0; // 0 = Simple, 1 = Custom

        int TargetInfoPosX = 0;
        int TargetInfoPosY = 0;
        int TargetInfoOffset = 15;

        //Other
        bool DrawCrosshair = true;
        float CrosshairSize = 7.0;
        float CrosshairThickness = 1.0;

        bool ShowSpectators = false;

        bool DrawSpectatorWarning = false;
        bool DrawVisibleWarning = false;
        bool WarningTextOutline = true;
        int WarningTextX;
        int WarningTextY;
        int WarningTextScale = 50;

        // Settings
        bool TextOutline = true;
        bool VisibilityCheck = false;
        bool KnockedCheck = false;
        float ESPMaxDistance = 200;
        
    };

    namespace Radar {
        bool MiniMap = false;
        float MiniMapRange = 200;
        int MiniMapScaleX = 215;
        int MiniMapScaleY = 215;
        bool MiniMapGuides = true;

        int IdentifierSize = 7;
        int MiniMapBlackBGSize = 0;
        int EnemyIdentifier = 1;
        bool EnemyViewAngles = true;
        float EnemyViewAnglesLength = 15.0f;
        float EnemyViewAnglesColor[4] = { 0, 0, 0, 0.999 };
        float RadarRounding = 15.0f;
        
        bool BigMap = false;
        InputKeyType BigMapBind = InputKeyType::KEYBOARD_K;
        float CircleColor[4] = { 0.999, 0, 0, 0.999 };
        float BackgroundColor[4] = { 0, 0, 0, 0.1 };
    };
    
    namespace Misc {
        bool SuperGlide = true;
        int SuperGlideMode = 0; // 0 = Manual, 1 = Auto
        int SuperGlideFPS = 1; // 0 = 75, 1 = 144, 2 = 240

        bool BHop = false;
        int BHopDelay = 25;
        InputKeyType BHopBind = InputKeyType::KEYBOARD_X;

        bool WallJump = false;
        InputKeyType WallJumpBind = InputKeyType::KEYBOARD_X;

        bool AutoTapStrafe = false;

        bool QuickTurn = false;
        int QuickTurnAngle = 180;
        InputKeyType QuickTurnBind = InputKeyType::MOUSE_Middle;

        bool RapidFire = false;
        int RapidFireDelay = 75;
        InputKeyType RapidFireBind = InputKeyType::KEYBOARD_X;

        //Rapid Fire Weapon Toggles
        //Light
        bool RapidP2020 = true;
        bool RapidR301 = true;
        bool RapidG7 = true;
        //Heavy
        bool RapidFlatline = true;
        bool RapidHemlock = true;
        bool RapidProwler = true;
        //Energy
        bool RapidNemesis = true;
        //Shotgun
        bool RapidMozambique = true;
        bool RapidEVA8 = true;
        //Legendary
        bool RapidWingman = true;

        bool SkinChanger = false;
        //Weapon IDs
        //Light
        int SkinP2020 = 1;
        int SkinRE45 = 1;
        int SkinALTERNATOR = 1;
        int SkinR99 = 1;
        int SkinR301 = 1;
        int SkinSPITFIRE = 1;
        int SkinG7 = 1;
        
        //Heavy
        int SkinFLATLINE = 1;
        int SkinHEMLOCK = 1;
        int SkinREPEATER = 1;
        int SkinRAMPAGE = 1;
        int SkinCAR = 1;
        
        //Energy
        int SkinHAVOC = 1;
        int SkinDEVOTION = 1;
        int SkinLSTAR = 1;
        int SkinTRIPLETAKE = 1;
        int SkinVOLT = 1;
        int SkinNEMESIS = 1;
        
        //Shotgun
        int SkinMOZAMBIQUE = 1;
        int SkinEVA8 = 1;
        int SkinPEACEKEEPER = 1;
        int SkinMASTIFF = 1;
        
        //Snipers
        int SkinLONGBOW = 1;
        int SkinCHARGE_RIFLE = 1;
        int SkinSENTINEL = 1; 
        
        //Legendary
        int SkinWINGMAN = 1;
        int SkinPROWLER = 1;
        int SkinBOCEK = 1;
        int SkinKRABER = 1;
    };
    
    namespace Colors {
    	int WeaponColorMode = 0;

        namespace Enemy {
            //ESP
            float InvisibleBoxColor[4] = { 0.99, 0, 0, 0.99 };
            float VisibleBoxColor[4] = { 0, 0.99, 0, 0.99 };
            float KnockedBoxColor[4] = { 0.990, 0.671, 0.119, 0.99 };
            float InvisibleFilledBoxColor[4] = { 0, 0, 0, 0.11 };
            float VisibleFilledBoxColor[4] = { 0, 0, 0, 0.11 };
            float KnockedFilledBoxColor[4] = { 0, 0, 0, 0.11 };
            float InvisibleTracerColor[4] = { 0.99, 0, 0, 0.99 };
            float VisibleTracerColor[4] = { 0, 0.99, 0, 0.99 };
            float KnockedTracerColor[4] = { 0.990, 0.671, 0.119, 0.99 };
            float InvisibleSkeletonColor[4] = { 0.99, 0, 0, 0.99 };
            float VisibleSkeletonColor[4] = { 0, 0.99, 0, 0.99 };
            float KnockedSkeletonColor[4] = { 0.990, 0.671, 0.119, 0.99 };
            float InvisibleHeadCircleColor[4] = { 0.99, 0, 0, 0.99 };
            float VisibleHeadCircleColor[4] = { 0, 0.99, 0, 0.99 };
            float KnockedHeadCircleColor[4] = { 0.990, 0.671, 0.119, 0.99 };
            float InvisibleNameColor[4] = { 0.99, 0, 0, 0.99 };
            float VisibleNameColor[4] = { 0, 0.99, 0, 0.99 };
            float KnockedNameColor[4] = { 0.990, 0.671, 0.119, 0.99 };
            float InvisibleDistanceColor[4] = { 0.99, 0, 0, 0.99 };
            float VisibleDistanceColor[4] = { 0, 0.99, 0, 0.99 };
            float KnockedDistanceColor[4] = { 0.990, 0.671, 0.119, 0.99 };
            float InvisibleLegendColor[4] = { 0.99, 0, 0, 0.99 };
            float VisibleLegendColor[4] = { 0, 0.99, 0, 0.99 };
            float KnockedLegendColor[4] = { 0.990, 0.671, 0.119, 0.99 };
            float NearColor[4] = { 0.99, 0.99, 0.99, 0.99 };
            //Bar
            int BarColorMode = 2;
            //WeaponESP Colors
            float InvisibleWeaponColor[4] = { 0.99, 0, 0, 0.99 };
            float VisibleWeaponColor[4] = { 0, 0.99, 0, 0.99 };
            float KnockedWeaponColor[4] = { 0.990, 0.671, 0.119, 0.99 };
            //Multiple
            float LightWeaponColor[4] = { 0.990, 0.768, 0.039, 0.99 };
            float HeavyWeaponColor[4] = { 0.00990, 0.990, 0.761 };
            float EnergyWeaponColor[4] = { 0, 0.99, 0, 0.99 };
            float ShotgunWeaponColor[4] = { 0.99, 0, 0, 0.99 };
            float SniperWeaponColor[4] = { 0.00990, 0.337, 0.990, 0.99 };
            float LegendaryWeaponColor[4] = { 0.99, 0.530, 0.945 };
            float MeleeWeaponColor[4] = { 0.99, 0.99, 0.99, 0.99 };
            float ThrowableWeaponColor[4] = { 0.990, 0.974, 0.0495, 0.99 };

            //Glow
            float InvisibleGlowColor[3] = {1, 0, 0};
            float VisibleGlowColor[3] = {0, 1, 0};
            float LowGlowColor[3] = {1, 1, 0};
            float KnockedGlowColor[3] = { 0.99, 0.67, 0.12};
            
            float RedShieldColor[3] = {1, 0, 0};
            float PurpleShieldColor[3] = {0.5, 0, 0.5};
            float BlueShieldColor[3] = {0, 0.5, 1};
            float GreyShieldColor[3] = {0.540, 0.545, 0.545};
        };

        namespace Teammate {
            float InvisibleBoxColor[4] = { 0.0846, 0.0693, 0.990, 0.99 };
            float VisibleBoxColor[4] = { 0.00990, 0.827, 0.990, 0.99 };
            float KnockedBoxColor[4] = { 0.484, 0, 0.990, 0.99 };
            float InvisibleFilledBoxColor[4] = { 0.0846, 0.0693, 0.990, 0.99 };
            float VisibleFilledBoxColor[4] = { 0.00990, 0.827, 0.990, 0.99 };
            float KnockedFilledBoxColor[4] = { 0.484, 0, 0.990, 0.99 };
            float InvisibleTracerColor[4] = { 0.0846, 0.0693, 0.990, 0.99 };
            float VisibleTracerColor[4] = { 0.00990, 0.827, 0.990, 0.99 };
            float KnockedTracerColor[4] = { 0.484, 0, 0.990, 0.99 };
            float InvisibleSkeletonColor[4] = { 0.0846, 0.0693, 0.990, 0.99 };
            float VisibleSkeletonColor[4] = { 0.00990, 0.827, 0.990, 0.99 };
            float KnockedSkeletonColor[4] = { 0.484, 0, 0.990, 0.99 };
            float InvisibleHeadCircleColor[4] = { 0.0846, 0.0693, 0.990, 0.99 };
            float VisibleHeadCircleColor[4] = { 0.00990, 0.827, 0.990, 0.99 };
            float KnockedHeadCircleColor[4] = { 0.484, 0, 0.990, 0.99 };
            float InvisibleNameColor[4] = { 0.0846, 0.0693, 0.990, 0.99 };
            float VisibleNameColor[4] = { 0.00990, 0.827, 0.990, 0.99 };
            float KnockedNameColor[4] = { 0.484, 0, 0.990, 0.99 };
            float InvisibleDistanceColor[4] = { 0.0846, 0.0693, 0.990, 0.99 };
            float VisibleDistanceColor[4] = { 0.00990, 0.827, 0.990, 0.99 };
            float KnockedDistanceColor[4] = { 0.484, 0, 0.990, 0.99 };
            float InvisibleLegendColor[4] = { 0.0846, 0.0693, 0.990, 0.99 };
            float VisibleLegendColor[4] = { 0.00990, 0.827, 0.990, 0.99 };
            float KnockedLegendColor[4] = { 0.484, 0, 0.990, 0.99 };
            
            //Bar
            int BarColorMode = 2;
            
            //WeaponESP Colors
            float InvisibleWeaponColor[4] = { 0.0846, 0.0693, 0.990, 0.99 };
            float VisibleWeaponColor[4] = { 0.00990, 0.827, 0.990, 0.99 };
            float KnockedWeaponColor[4] = { 0.484, 0, 0.990, 0.99 };
            //Multiple
            float LightWeaponColor[4] = { 0.990, 0.768, 0.039, 0.99 };
            float HeavyWeaponColor[4] = { 0.00990, 0.990, 0.761 };
            float EnergyWeaponColor[4] = { 0, 0.99, 0, 0.99 };
            float ShotgunWeaponColor[4] = { 0.99, 0, 0, 0.99 };
            float SniperWeaponColor[4] = { 0.00990, 0.337, 0.990, 0.99 };
            float LegendaryWeaponColor[4] = { 0.99, 0.530, 0.945 };
            float MeleeWeaponColor[4] = { 0.99, 0.99, 0.99, 0.99 };
            float ThrowableWeaponColor[4] = { 0.990, 0.974, 0.0495, 0.99 };
        };

        // Aimbot
        float TargetLineColor[4] = { 0.99, 0.99, 0.99, 0.99 };
        float TargetDotColor[4] = { 0.99, 0.99, 0.99, 0.99 };
        float TargetBoxColor[4] = { 0.99, 0.99, 0.99, 0.99 };
        float TargetLineLockedColor[4] = { 0.99, 0, 0, 0.99 };
        float TargetDotLockedColor[4] = { 0.99, 0, 0, 0.99 };
        float TargetBoxLockedColor[4] = { 0.99, 0, 0, 0.99 };

        float TargetInfoColor[4] = { 0.99, 0.99, 0.99, 0.99 };
        float TargetInfoLockedColor[4] = { 0.99, 0, 0, 0.99 };

    	float FOVColor[4] = { 0.99, 0.99, 0.99, 0.99 };
    	float FilledFOVColor[4] = { 0, 0, 0, 0.11 };
    	float CrosshairColor[4] = { 0.99, 0.99, 0.99, 0.99 };

        float SpectatorWarningColor[4] = { 0.99, 0, 0, 0.99};
        float VisibleWarningColor[4] = { 0, 0.99, 0, 0.99 };
    };
    
    namespace Watermark {
        bool Watermark = true;
	    int WatermarkPosition = 0;
	    bool Name = true;
        float NameColor[4] = { 0.4, 1, 0.343, 1};
        bool Spectators = false;
	    bool ProcessingSpeed = true;
        bool GameFPS = true;
    };
}; //End of namespace Features
