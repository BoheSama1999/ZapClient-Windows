#pragma once
#include <string>
// https://www.unknowncheats.me/forum/apex-legends/319804-apex-legends-reversal-structs-offsets.html
// GameVersion = v3.0.70.55

std::string CheatVersion = "Version 1.1.3";
std::string GameVersion = "v3.0.70.55";

// Core
ULONG64 OFF_REGION;//= 0x140000000; linux     //[Static]->Region
constexpr ULONG64 OFF_LEVEL = 0x17c7160;        //[Miscellaneous]->LevelName
constexpr ULONG64 OFF_LOCAL_PLAYER = 0x225a8a8; //[Miscellaneous]->LocalPlayer
constexpr ULONG64 OFF_ENTITY_LIST = 0x1eabd08;  //[Miscellaneous]->cl_entitylist
constexpr ULONG64 OFF_NAME_INDEX = 0x38;        //nameIndex
constexpr ULONG64 OFF_NAME_LIST = 0xc7912b0;    //[Miscellaneous]->NameList
constexpr ULONG64 OFF_GAMEMODE = 0x22921b0;    // mp_gamemode
constexpr ULONG64 OFF_SQUAD_ID = 0x0334;        //m_squadID
constexpr ULONG64 OFF_GLOBAL_VARS = 0x17c6c60;  //[Miscellaneous]->GlobalVars

// HUD
constexpr ULONG64 OFF_VIEWRENDER = 0x74dd028; //[Miscellaneous]->ViewRenderer
constexpr ULONG64 OFF_VIEWMATRIX = 0x11a350;  //[Miscellaneous]->ViewMatrix

// Buttons
constexpr ULONG64 OFF_INATTACK = 0x74de2a0;         //[Buttons]->in_attack
constexpr ULONG64 OFF_IN_JUMP = 0x74de3a0;          //[Buttons]->in_jump
constexpr ULONG64 OFF_IN_DUCK = 0x74de4a0;          //[Buttons]->in_duck
constexpr ULONG64 OFF_IN_FORWARD = 0x74de1f0;       //[Buttons]->in_forward
constexpr ULONG64 OFF_IN_BACKWARD = 0x074de218;    //[Buttons]->in_backward
constexpr ULONG64 OFF_TRAVERSAL_START_TIME = 0x2af0; //[RecvTable.DT_LocalPlayerExclusive]->m_traversalStartTime
constexpr ULONG64 OFF_TRAVERSAL_PROGRESS = 0x2aec;   //[RecvTable.DT_LocalPlayerExclusive]->m_traversalProgress
constexpr ULONG64 OFF_WALL_RUN_START_TIME = 0x3594;  //[RecvTable.DT_LocalPlayerExclusive]->m_wallRunStartTime
constexpr ULONG64 OFF_WALL_RUN_CLEAR_TIME = 0x3598;  //[RecvTable.DT_LocalPlayerExclusive]->m_wallRunClearTime

// Player
constexpr ULONG64 OFF_HEALTH = 0x0318;             //[RecvTable.DT_Player]->m_iHealth
constexpr ULONG64 OFF_MAXHEALTH = 0x0460;          //[RecvTable.DT_Player]->m_iMaxHealth
constexpr ULONG64 OFF_SHIELD = 0x01a0;             //[RecvTable.DT_TitanSoul]->m_shieldHealth
constexpr ULONG64 OFF_MAXSHIELD = 0x01a4;          //[RecvTable.DT_TitanSoul]->m_shieldHealthMax
constexpr ULONG64 OFF_CAMERAORIGIN = 0x1ed0;       //[Miscellaneous]->CPlayer!camera_origin
constexpr ULONG64 OFF_STUDIOHDR = 0xff0;           //[Miscellaneous]->CBaseAnimating!m_pStudioHdr
constexpr ULONG64 OFF_BONES = 0x0da0 + 0x48;       //m_nForceBone
constexpr ULONG64 OFF_LOCAL_ORIGIN = 0x017c;       //[DataMap.C_BaseEntity]->m_vecAbsOrigin
constexpr ULONG64 OFF_ABSVELOCITY = 0x0170;        //[DataMap.C_BaseEntity]->m_vecAbsVelocity
constexpr ULONG64 OFF_ZOOMING = 0x1bd1;            //[RecvTable.DT_Player]->m_bZooming
constexpr ULONG64 OFF_TEAM_NUMBER = 0x0328;        //[RecvTable.DT_BaseEntity]->m_iTeamNum
constexpr ULONG64 OFF_NAME = 0x0471;               //[RecvTable.DT_BaseEntity]->m_iName
constexpr ULONG64 OFF_LIFE_STATE = 0x0680;         //[RecvTable.DT_Player]->m_lifeState
constexpr ULONG64 OFF_BLEEDOUT_STATE = 0x26e0;     //[RecvTable.DT_Player]->m_bleedoutState
constexpr ULONG64 OFF_LAST_VISIBLE_TIME = 0x1990;  //[Miscellaneous]->CPlayer!lastVisibleTime
constexpr ULONG64 OFF_LAST_AIMEDAT_TIME = 0x1998;  //[Miscellaneous]->CWeaponX!lastCrosshairTargetTime
constexpr ULONG64 OFF_VIEW_ANGLES = 0x2534 - 0x14; //[DataMap.C_Player]-> m_ammoPoolCapacity - 0x14
constexpr ULONG64 OFF_PUNCH_ANGLES = 0x2438;       //[DataMap.C_Player]->m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
constexpr ULONG64 OFF_YAW = 0x223c - 0x8;          //m_currentFramePlayer.m_ammoPoolCount - 0x8
constexpr ULONG64 OFF_MODELNAME = 0x0030;          //m_ModelName
constexpr ULONG64 OFF_OBSERVER_LIST = 0x1EADD28;   //observerList: 48 8B 0D ? ? ? ? 48 85 C9 74 ? 48 8B 01 FF ? ? 48 85 C0 74 ? 48 63 4E 38     22.05.24
constexpr ULONG64 OFF_SKY_DIVE_STATUS = 0x469c;   //m_skydiveState
constexpr ULONG64 OFF_DUCK_STATUS = 0x29e0;   // m_duckState=0x29e0
constexpr ULONG64 OFF_CENTITY_FLAGS = 0x00c8;   //m_fFlags

// Weapon
constexpr ULONG64 OFF_WEAPON_HANDLE = 0x1934;            //[RecvTable.DT_Player]->m_latestPrimaryWeapons
constexpr ULONG64 OFF_WEAPON_INDEX = 0x1778;             //[RecvTable.DT_WeaponX]->m_weaponNameIndex
constexpr ULONG64 OFF_PROJECTILESCALE = 0x04ec + 0x19c0; //projectile_gravity_scale + [WeaponSettingsMeta]base
constexpr ULONG64 OFF_PROJECTILESPEED = 0x04e4 + 0x19c0; //projectile_launch_speed + [WeaponSettingsMeta]base
constexpr ULONG64 OFF_OFFHAND_WEAPON = 0x1944;           //m_latestNonOffhandWeapons
constexpr ULONG64 OFF_CURRENTZOOMFOV = 0x15d0 + 0x00b8;  //m_playerData + m_curZoomFOV
constexpr ULONG64 OFF_TARGETZOOMFOV = 0x15d0 + 0x00bc;   //m_playerData + m_targetZoomFOV
constexpr ULONG64 OFF_SKIN = 0x0d58;                     //m_nSkin
constexpr ULONG64 OFF_TIME_BASE = 0x2088;                //m_currentFramePlayer.timeBase
constexpr ULONG64 OFF_WEAPON_DISCARDED = 0x1599;         //[RecvTable.DT_WeaponX]->m_discarded
constexpr ULONG64 OFF_VIEWMODELS = 0x2d18;               //m_hViewModels

// Glow
constexpr ULONG64 OFF_HIGHLIGHT_TYPE_SIZE = 0x34;  //
constexpr ULONG64 OFF_GLOW_ENABLE = 0x26c;         //Script_Highlight_GetCurrentContext
constexpr ULONG64 OFF_GLOW_THROUGH_WALL = 0x26c;   //Script_Highlight_SetVisibilityType
constexpr ULONG64 OFF_GLOW_FIX = 0x268;            //
constexpr ULONG64 OFF_GLOW_HIGHLIGHT_ID = 0x28C;   //[DT_HighlightSettings].m_highlightServerActiveStates
constexpr ULONG64 OFF_GLOW_HIGHLIGHTS = 0xade5c40; //highlightsettings
