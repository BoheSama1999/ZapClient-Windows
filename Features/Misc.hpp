#pragma once
#include "../Core/Level.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/Player.hpp"
#include <glfw3.h>
//#include <X11/Xlib.h> linux
//#include <X11/Xutil.h> linux
//#include <X11/extensions/XInput2.h> linux
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
//#include <unistd.h> linux
#include <vector>

#include "../Math/QAngle.hpp"
#include "../Math/Resolver.hpp"
#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"

#include "../Utils/Config.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/InputTypes.hpp"
#include "../Utils/Memory.hpp"
#include "../Utils/Weapons.hpp"
#include "../Utils/XDisplay.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

typedef void* PVOID;

struct Misc {

  std::set<int> RapidFireList = {};

  float HangOnWall1;
  float HangOnWall2;
  float TraversalProgress1;
  float HangOnWall3;
  float HangOnWall4;
  float StartJumpTime1;

  //XDisplay* X11Display; linux
  DriverHID* DHID;
  Level* Map;
  LocalPlayer* Myself;
  std::vector<Player*>* Players;

  Misc(DriverHID* DHID, Level* Map, LocalPlayer* Myself,
       std::vector<Player*>* GamePlayers) {
    this->DHID = DHID;
    this->Map = Map;
    this->Myself = Myself;
    this->Players = GamePlayers;
  }

  static bool Save() {
    try {
      Config::Misc::SuperGlide = Features::Misc::SuperGlide;
      Config::Misc::SuperGlideMode = Features::Misc::SuperGlideMode;
      Config::Misc::SuperGlideFPS = Features::Misc::SuperGlideFPS;

      Config::Misc::QuickTurn = Features::Misc::QuickTurn;
      Config::Misc::QuickTurnAngle = Features::Misc::QuickTurnAngle;
      Config::Misc::QuickTurnBind =
        static_cast<int>(Features::Misc::QuickTurnBind);

      Config::Misc::BHop = Features::Misc::BHop;
      Config::Misc::BHopDelay = Features::Misc::BHopDelay;
      Config::Misc::BHopBind = static_cast<int>(Features::Misc::BHopBind);

      Config::Misc::WallJump = Features::Misc::WallJump;
      Config::Misc::WallJumpBind = static_cast<int>(Features::Misc::WallJumpBind);

      Config::Misc::AutoTapStrafe = Features::Misc::AutoTapStrafe;

      Config::Misc::RapidFire = Features::Misc::RapidFire;
      Config::Misc::RapidFireDelay = Features::Misc::RapidFireDelay;
      Config::Misc::RapidFireBind =
        static_cast<int>(Features::Misc::RapidFireBind);
    // Rapid Fire Weapons
      Config::Misc::RapidP2020 = Features::Misc::RapidP2020;
      Config::Misc::RapidR301 = Features::Misc::RapidR301;
      Config::Misc::RapidG7 = Features::Misc::RapidG7;
      Config::Misc::RapidFlatline = Features::Misc::RapidFlatline;
      Config::Misc::RapidHemlock = Features::Misc::RapidHemlock;
      Config::Misc::RapidProwler = Features::Misc::RapidProwler;
      Config::Misc::RapidNemesis = Features::Misc::RapidNemesis;
      Config::Misc::RapidMozambique = Features::Misc::RapidMozambique;
      Config::Misc::RapidEVA8 = Features::Misc::RapidEVA8;
      Config::Misc::RapidWingman = Features::Misc::RapidWingman;

      Config::Misc::SkinChanger = Features::Misc::SkinChanger;
      // Weapon IDs
      // Light
      Config::Misc::SkinP2020 = Features::Misc::SkinP2020;
      Config::Misc::SkinRE45 = Features::Misc::SkinRE45;
      Config::Misc::SkinALTERNATOR = Features::Misc::SkinALTERNATOR;
      Config::Misc::SkinR99 = Features::Misc::SkinR99;
      Config::Misc::SkinR301 = Features::Misc::SkinR301;
      Config::Misc::SkinSPITFIRE = Features::Misc::SkinSPITFIRE;
      Config::Misc::SkinG7 = Features::Misc::SkinG7;

      // Heavy
      Config::Misc::SkinFLATLINE = Features::Misc::SkinFLATLINE;
      Config::Misc::SkinHEMLOCK = Features::Misc::SkinHEMLOCK;
      Config::Misc::SkinREPEATER = Features::Misc::SkinREPEATER;
      Config::Misc::SkinRAMPAGE = Features::Misc::SkinRAMPAGE;
      Config::Misc::SkinCAR = Features::Misc::SkinCAR;

      // Energy
      Config::Misc::SkinHAVOC = Features::Misc::SkinHAVOC;
      Config::Misc::SkinDEVOTION = Features::Misc::SkinDEVOTION;
      Config::Misc::SkinLSTAR = Features::Misc::SkinLSTAR;
      Config::Misc::SkinTRIPLETAKE = Features::Misc::SkinTRIPLETAKE;
      Config::Misc::SkinVOLT = Features::Misc::SkinVOLT;
      Config::Misc::SkinNEMESIS = Features::Misc::SkinNEMESIS;

      // Shotgun
      Config::Misc::SkinMOZAMBIQUE = Features::Misc::SkinMOZAMBIQUE;
      Config::Misc::SkinEVA8 = Features::Misc::SkinEVA8;
      Config::Misc::SkinPEACEKEEPER = Features::Misc::SkinPEACEKEEPER;
      Config::Misc::SkinMASTIFF = Features::Misc::SkinMASTIFF;

      // Snipers
      Config::Misc::SkinLONGBOW = Features::Misc::SkinLONGBOW;
      Config::Misc::SkinCHARGE_RIFLE = Features::Misc::SkinCHARGE_RIFLE;
      Config::Misc::SkinSENTINEL = Features::Misc::SkinSENTINEL;

      // Legendary
      Config::Misc::SkinWINGMAN = Features::Misc::SkinWINGMAN;
      Config::Misc::SkinPROWLER = Features::Misc::SkinPROWLER;
      Config::Misc::SkinBOCEK = Features::Misc::SkinBOCEK;
      Config::Misc::SkinKRABER = Features::Misc::SkinKRABER;
      return true;
    }
    catch (...) {
      return false;
    }
  }

  void UpdateRapidFireList() {
    // Update RapidFireList
    RapidFireList.clear();
    if (Features::Misc::RapidP2020)
      RapidFireList.insert(WeaponIDs::P2020);
    if (Features::Misc::RapidR301)
      RapidFireList.insert(WeaponIDs::R301);
    if (Features::Misc::RapidG7)
      RapidFireList.insert(WeaponIDs::G7);
    if (Features::Misc::RapidFlatline)
      RapidFireList.insert(WeaponIDs::FLATLINE);
    if (Features::Misc::RapidHemlock)
      RapidFireList.insert(WeaponIDs::HEMLOCK);
    if (Features::Misc::RapidProwler)
      RapidFireList.insert(WeaponIDs::PROWLER);
    if (Features::Misc::RapidNemesis)
      RapidFireList.insert(WeaponIDs::NEMESIS);
    if (Features::Misc::RapidMozambique)
      RapidFireList.insert(WeaponIDs::MOZAMBIQUE);
    if (Features::Misc::RapidWingman)
      RapidFireList.insert(WeaponIDs::WINGMAN);
    if (Features::Misc::RapidEVA8)
      RapidFireList.insert(WeaponIDs::EVA8);
  }

  void Update() {
    if (!Map->IsPlayable)
      return;
    if (Myself->IsDead)
      return;

    if (Features::Misc::SkinChanger) {
      ULONG64 wephandle = Memory::Read<ULONG64>(Myself->BasePointer + OFF_WEAPON_HANDLE);
      wephandle &= 0xffff;
      ULONG64 wep_entity = Myself->WeaponEntity;
      std::map<int, int> weaponSkinMap;
      // Light ammo weapons
      weaponSkinMap[WeaponIDs::P2020] = Features::Misc::SkinP2020;
      weaponSkinMap[WeaponIDs::RE45] = Features::Misc::SkinRE45;
      weaponSkinMap[WeaponIDs::ALTERNATOR] = Features::Misc::SkinALTERNATOR;
      weaponSkinMap[WeaponIDs::R99] = Features::Misc::SkinR99;
      weaponSkinMap[WeaponIDs::R301] = Features::Misc::SkinR301;
      weaponSkinMap[WeaponIDs::SPITFIRE] = Features::Misc::SkinSPITFIRE;
      weaponSkinMap[WeaponIDs::G7] = Features::Misc::SkinG7;
      // Heavy ammo weapons
      weaponSkinMap[WeaponIDs::CAR] = Features::Misc::SkinCAR;
      weaponSkinMap[WeaponIDs::RAMPAGE] = Features::Misc::SkinRAMPAGE;
      weaponSkinMap[WeaponIDs::REPEATER] = Features::Misc::SkinREPEATER;
      weaponSkinMap[WeaponIDs::HEMLOCK] = Features::Misc::SkinHEMLOCK;
      weaponSkinMap[WeaponIDs::FLATLINE] = Features::Misc::SkinFLATLINE;
      // Energy ammo weapons
      weaponSkinMap[WeaponIDs::NEMESIS] = Features::Misc::SkinNEMESIS;
      weaponSkinMap[WeaponIDs::VOLT] = Features::Misc::SkinVOLT;
      weaponSkinMap[WeaponIDs::TRIPLETAKE] = Features::Misc::SkinTRIPLETAKE;
      weaponSkinMap[WeaponIDs::LSTAR] = Features::Misc::SkinLSTAR;
      weaponSkinMap[WeaponIDs::DEVOTION] = Features::Misc::SkinDEVOTION;
      weaponSkinMap[WeaponIDs::HAVOC] = Features::Misc::SkinHAVOC;
      // Sniper ammo weapons
      weaponSkinMap[WeaponIDs::SENTINEL] = Features::Misc::SkinSENTINEL;
      weaponSkinMap[WeaponIDs::CHARGE_RIFLE] = Features::Misc::SkinCHARGE_RIFLE;
      weaponSkinMap[WeaponIDs::LONGBOW] = Features::Misc::SkinLONGBOW;
      // Shotgun ammo weapons
      weaponSkinMap[WeaponIDs::MOZAMBIQUE] = Features::Misc::SkinMOZAMBIQUE;
      weaponSkinMap[WeaponIDs::EVA8] = Features::Misc::SkinEVA8;
      weaponSkinMap[WeaponIDs::PEACEKEEPER] = Features::Misc::SkinPEACEKEEPER;
      weaponSkinMap[WeaponIDs::MASTIFF] = Features::Misc::SkinMASTIFF;
      // Legendary ammo weapons
      weaponSkinMap[WeaponIDs::WINGMAN] = Features::Misc::SkinWINGMAN;
      weaponSkinMap[WeaponIDs::PROWLER] = Features::Misc::SkinPROWLER;
      weaponSkinMap[WeaponIDs::BOCEK] = Features::Misc::SkinBOCEK;
      weaponSkinMap[WeaponIDs::KRABER] = Features::Misc::SkinKRABER;

      int waponIndex = Memory::Read<int>(wep_entity + OFF_WEAPON_INDEX);
      if (weaponSkinMap.count(waponIndex) == 0)
        return;
      int skinID = weaponSkinMap[waponIndex];
      // printf("Weapon: %s Activated Skin ID: %d \n",
      // WeaponName(waponIndex).c_str(), skinID);
      Memory::Write<int>(wep_entity + OFF_SKIN, skinID);
    }
  } // End of update

  void SuperGlide() {
    UpdateSuperGlide();
    if (Features::Misc::SuperGlideMode == 0) { // Requires Space Held, Keyboard Only
      if (InputManager::isKeyDownOrPress(InputKeyType::KEYBOARD_SPACE)) {
        static float startjumpTime = 0;
        static bool startSg = false;
        static float traversalProgressTmp = 0.0;

        float worldtime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE); // Current time
        float traversalStartTime = Memory::Read<float>(Myself->BasePointer + OFF_TRAVERSAL_START_TIME); // Time to start wall climbing
        float traversalProgress = Memory::Read<float>(Myself->BasePointer + OFF_TRAVERSAL_PROGRESS); // Wall climbing, if > 0.87 it is almost over.
        float HangOnWall = -(traversalStartTime - worldtime);

        if (HangOnWall > HangOnWall1 && HangOnWall < HangOnWall2) {
          Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
        }
        if (traversalProgress > TraversalProgress1 && !startSg && HangOnWall > HangOnWall3 && HangOnWall < HangOnWall4) {
          // start SG
          startjumpTime = worldtime;
          startSg = true;
        }
        if (startSg) {
          Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
          while (Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE) - startjumpTime < StartJumpTime1)
            ; // why is this here...
          {
            Memory::Write<int>(OFF_REGION + OFF_IN_DUCK + 0x8, 6);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
          }
          startSg = false;
        }
      }
    }

    if (Features::Misc::SuperGlideMode == 1) { // Automatic, Controller Support
      static float startjumpTime = 0;
      static bool startSg = false;
      static float traversalProgressTmp = 0.0;

      float worldtime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE); // Current time
      float traversalStartTime = Memory::Read<float>(Myself->BasePointer + OFF_TRAVERSAL_START_TIME); // Time to start wall climbing
      float traversalProgress = Memory::Read<float>(Myself->BasePointer + OFF_TRAVERSAL_PROGRESS); // Wall climbing, if > 0.87 it is almost
                                   // over.
      float HangOnWall = -(traversalStartTime - worldtime);

      if (HangOnWall > HangOnWall1 && HangOnWall < HangOnWall2) {
        Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
      }
      if (traversalProgress > TraversalProgress1 && !startSg && HangOnWall > HangOnWall3 && HangOnWall < HangOnWall4) {
        // start SG
        startjumpTime = worldtime;
        startSg = true;
      }
      if (startSg) {
        Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
        while (Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE) - startjumpTime < StartJumpTime1)
          ; // why is this here...
        {
          Memory::Write<int>(OFF_REGION + OFF_IN_DUCK + 0x8, 6);
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
          Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
          std::this_thread::sleep_for(std::chrono::milliseconds(600));
        }
        startSg = false;
      }
    }
  }

  void UpdateSuperGlide() {
    if (Features::Misc::SuperGlideFPS == 0) // 75 FPS
    {
      HangOnWall1 = 0.1;
      HangOnWall2 = 0.12;
      TraversalProgress1 = 0.87f;
      HangOnWall3 = 0.1f;
      HangOnWall4 = 1.5f;
      StartJumpTime1 = 0.011;
    }

    else if (Features::Misc::SuperGlideFPS == 1) // 144 FPS
    {
      HangOnWall1 = 0.05;
      HangOnWall2 = 0.07;
      TraversalProgress1 = 0.90f;
      HangOnWall3 = 0.05f;
      HangOnWall4 = 0.75f;
      StartJumpTime1 = 0.007;
    }

    else if (Features::Misc::SuperGlideFPS == 1) // 240 FPS
    {
      HangOnWall1 = 0.033;
      HangOnWall2 = 0.04;
      TraversalProgress1 = 0.95f;
      HangOnWall3 = 0.033f;
      HangOnWall4 = 0.2f;
      StartJumpTime1 = 0.004;
    }
  }

  void BHop() {
    if (InputManager::isKeyDownOrPress(Features::Misc::BHopBind) &&
        InputManager::isKeyDownOrPress(InputKeyType::KEYBOARD_SPACE)) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(Features::Misc::BHopDelay));
      Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x08, 5);
      std::this_thread::sleep_for(
          std::chrono::milliseconds(Features::Misc::BHopDelay));
      Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x08, 4);
    }
  }

  void QuickTurn() {
    if (Features::Misc::QuickTurn) {
      FloatVector2D localYawtoClamp = Myself->viewAngles;
      localYawtoClamp.clamp();
      float localYaw = localYawtoClamp.y;
      // quickTurn
      if (InputManager::isKeyDown(Features::Misc::QuickTurnBind)) {
        Myself->setYaw((localYaw + Features::Misc::QuickTurnAngle));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }
    }
  }

  void RapidFire() {
    if (!Myself->IsCombatReady())
      return;
    if (RapidFireList.find(Myself->WeaponIndex) == RapidFireList.end())
      return;
    if (InputManager::isKeyDownOrPress(Features::Misc::RapidFireBind)) {
        DHID->MouseClickLeft();
      std::this_thread::sleep_for(
          std::chrono::milliseconds(Features::Misc::RapidFireDelay));
    }
  }

  void WallJump() {
    if (InputManager::isKeyDownOrPress(Features::Misc::WallJumpBind)) {

      float wallStartTime = Memory::Read<float>(Myself->BasePointer + OFF_WALL_RUN_START_TIME);
      float wallProgress = Memory::Read<float>(Myself->BasePointer + OFF_TRAVERSAL_PROGRESS);

      static float onWallTmp = 0;
      if (wallStartTime > onWallTmp + 0.1)
      {
        int forward = Memory::Read<int>(OFF_REGION + OFF_IN_FORWARD);
        if (forward == 0)
        {
          Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
          std::this_thread::sleep_for(std::chrono::milliseconds(300));
          Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
        }
      }
      onWallTmp = wallStartTime;

      static float onEdgeTmp = 0;
      if (wallProgress > onEdgeTmp + 0.1)
      {
        int forward = Memory::Read<int>(OFF_REGION + OFF_IN_FORWARD);
        if (forward == 0)
        {
          Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
          std::this_thread::sleep_for(std::chrono::milliseconds(300));
          Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
        }
      }
      onEdgeTmp = wallProgress;
    }
  }

 //Credits to chettoy/apexsky
  void AutoTapStrafe() {
    bool ts_start = true;
    bool longclimb = false;
    // AutoTapStrafe
    float wallrun_start = Memory::Read<float>(Myself->BasePointer + OFF_WALL_RUN_START_TIME);
    float wallrun_clear = Memory::Read<float>(Myself->BasePointer + OFF_WALL_RUN_CLEAR_TIME);
    float world_time = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);

    if (wallrun_start > wallrun_clear) {
      float climbTime = world_time - wallrun_start;
      if (climbTime > 0.8) {
        longclimb = true;
        ts_start = false;
      }
      else {
        ts_start = true;
      }
    }
    if (ts_start) {
      if (longclimb) {
        if (world_time > wallrun_clear + 0.1)
          longclimb = false;
      }

      int flags = Memory::Read<int>(Myself->BasePointer + OFF_CENTITY_FLAGS);
      int backward_state = Memory::Read<int>(OFF_REGION + OFF_IN_BACKWARD);
      int forward_state = Memory::Read<int>(OFF_REGION + OFF_IN_FORWARD);
      int force_forward = Memory::Read<int>(OFF_REGION + OFF_IN_FORWARD + 0x8);
      int skydrive_state = Memory::Read<int>(Myself->BasePointer + OFF_SKY_DIVE_STATUS);
      int duck_state = Memory::Read<int>(Myself->BasePointer + OFF_DUCK_STATUS);

      if (((flags & 0x1) == 0) && !(skydrive_state > 0) && !longclimb &&
          !(backward_state > 0)) {
        if (((duck_state > 0) && (forward_state == 33))) { // Previously 33
          if (force_forward == 0) {
            Memory::Write<int>(OFF_REGION + OFF_IN_FORWARD + 0x8, 1);
          }
          else {
            Memory::Write<int>(OFF_REGION + OFF_IN_FORWARD + 0x8, 0);
          }
        }
      }
      else if ((flags & 0x1) != 0) {
        if (forward_state == 0) {
          Memory::Write<int>(OFF_REGION + OFF_IN_FORWARD + 0x8, 0);
        }
        else if (forward_state == 33) {
          Memory::Write<int>(OFF_REGION + OFF_IN_FORWARD + 0x8, 1);
        }
      }
    }
  }
};
