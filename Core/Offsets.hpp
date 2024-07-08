#pragma once
#include <string>
// https://www.unknowncheats.me/forum/apex-legends/319804-apex-legends-reversal-structs-offsets.html
// GameVersion = v3.0.74.20

std::string CheatVersion = "Version 1.1.4";
std::string GameVersion = "v3.0.74.20";

// Core
ULONG64 OFF_REGION;//= 0x140000000; linux    //[Static]->Region
constexpr ULONG64 OFF_LEVEL = 0x17e8d34;        //[Miscellaneous]->LevelName
constexpr ULONG64 OFF_LOCAL_PLAYER = 0x22b0328; //[Miscellaneous]->LocalPlayer
constexpr ULONG64 OFF_ENTITY_LIST = 0x1ef7c38;  //[Miscellaneous]->cl_entitylist
constexpr ULONG64 OFF_NAME_INDEX = 0x38;        //nameIndex
constexpr ULONG64 OFF_NAME_LIST = 0xd2e2260;    //[Miscellaneous]->NameList
constexpr ULONG64 OFF_GAMEMODE = 0x022e8360;    // mp_gamemode
constexpr ULONG64 OFF_SQUAD_ID = 0x0344;        //m_squadID
constexpr ULONG64 OFF_GLOBAL_VARS = 0x17e8830;  //[Miscellaneous]->GlobalVars

// HUD
constexpr ULONG64 OFF_VIEWRENDER = 0x7542c00; //[Miscellaneous]->ViewRender
constexpr ULONG64 OFF_VIEWMATRIX = 0x11a350;  //[Miscellaneous]->ViewMatrix

// Buttons
constexpr ULONG64 OFF_INATTACK = 0x07542d28;         //[Buttons]->in_attack
constexpr ULONG64 OFF_IN_JUMP = 0x07542e28;          //[Buttons]->in_jump
constexpr ULONG64 OFF_IN_DUCK = 0x07542f18;          //[Buttons]->in_duck
constexpr ULONG64 OFF_IN_FORWARD = 0x07542c58;       //[Buttons]->in_forward
constexpr ULONG64 OFF_IN_BACKWARD = 0x07542c80;    //[Buttons]->in_backward
constexpr ULONG64 OFF_TRAVERSAL_START_TIME = 0x2b80; //[RecvTable.DT_LocalPlayerExclusive]->m_traversalStartTime
constexpr ULONG64 OFF_TRAVERSAL_PROGRESS = 0x2b7c;   //[RecvTable.DT_LocalPlayerExclusive]->m_traversalProgress
constexpr ULONG64 OFF_WALL_RUN_START_TIME = 0x3624;  //[RecvTable.DT_LocalPlayerExclusive]->m_wallRunStartTime
constexpr ULONG64 OFF_WALL_RUN_CLEAR_TIME = 0x3628;  //[RecvTable.DT_LocalPlayerExclusive]->m_wallRunClearTime

// Player
constexpr ULONG64 OFF_HEALTH = 0x0328;             //[RecvTable.DT_Player]->m_iHealth
constexpr ULONG64 OFF_MAXHEALTH = 0x0470;          //[RecvTable.DT_Player]->m_iMaxHealth
constexpr ULONG64 OFF_SHIELD = 0x01a0;             //[RecvTable.DT_TitanSoul]->m_shieldHealth
constexpr ULONG64 OFF_MAXSHIELD = 0x01a4;          //[RecvTable.DT_TitanSoul]->m_shieldHealthMax
constexpr ULONG64 OFF_CAMERAORIGIN = 0x1ee0;       //[Miscellaneous]->CPlayer!camera_origin
constexpr ULONG64 OFF_STUDIOHDR = 0x1000;           //[Miscellaneous]->CBaseAnimating!m_pStudioHdr
constexpr ULONG64 OFF_BONES = 0x0db0 + 0x48;       //m_nForceBone
constexpr ULONG64 OFF_LOCAL_ORIGIN = 0x017c;       //[DataMap.C_BaseEntity]->m_vecAbsOrigin
constexpr ULONG64 OFF_ABSVELOCITY = 0x0170;        //[DataMap.C_BaseEntity]->m_vecAbsVelocity
constexpr ULONG64 OFF_ZOOMING = 0x1be1;            //[RecvTable.DT_Player]->m_bZooming
constexpr ULONG64 OFF_TEAM_NUMBER = 0x0338;        //[RecvTable.DT_BaseEntity]->m_iTeamNum
constexpr ULONG64 OFF_NAME = 0x0481;               //[RecvTable.DT_BaseEntity]->m_iName
constexpr ULONG64 OFF_LIFE_STATE = 0x0690;         //[RecvTable.DT_Player]->m_lifeState
constexpr ULONG64 OFF_BLEEDOUT_STATE = 0x2770;     //[RecvTable.DT_Player]->m_bleedoutState
constexpr ULONG64 OFF_LAST_VISIBLE_TIME = 0x19a0;  //[Miscellaneous]->CPlayer!lastVisibleTime
constexpr ULONG64 OFF_LAST_AIMEDAT_TIME = 0x19a8;  //[Miscellaneous]->CWeaponX!lastCrosshairTargetTime
constexpr ULONG64 OFF_VIEW_ANGLES = 0x2544 - 0x14; //[DataMap.C_Player]-> m_ammoPoolCapacity - 0x14
constexpr ULONG64 OFF_PUNCH_ANGLES = 0x2448;       //[DataMap.C_Player]->m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
constexpr ULONG64 OFF_YAW = 0x224c - 0x8;          //m_currentFramePlayer.m_ammoPoolCount - 0x8
constexpr ULONG64 OFF_MODELNAME = 0x0030;          //m_ModelName
constexpr ULONG64 OFF_OBSERVER_LIST = 0x1ef9c58;   //observerList: 48 8B 0D ? ? ? ? 48 85 C9 74 ? 48 8B 01 FF ? ? 48 85 C0 74 ? 48 63 4E 38
constexpr ULONG64 OFF_OBSERVER_LIST_IN_ARRAY = 0x974; // 0x964 before
constexpr ULONG64 OFF_SKY_DIVE_STATUS = 0x4734;   //m_skydiveState
constexpr ULONG64 OFF_DUCK_STATUS = 0x2a70;   // m_duckState
constexpr ULONG64 OFF_CENTITY_FLAGS = 0x00c8;   //m_fFlags

// Weapon
constexpr ULONG64 OFF_WEAPON_HANDLE = 0x1944;            //[RecvTable.DT_Player]->m_latestPrimaryWeapons
constexpr ULONG64 OFF_WEAPON_INDEX = 0x1788;             //[RecvTable.DT_WeaponX]->m_weaponNameIndex
constexpr ULONG64 OFF_PROJECTILESCALE = 0x04ec + 0x19d0; //projectile_gravity_scale + [WeaponSettingsMeta]base
constexpr ULONG64 OFF_PROJECTILESPEED = 0x04e4 + 0x19d0; //projectile_launch_speed + [WeaponSettingsMeta]base
constexpr ULONG64 OFF_OFFHAND_WEAPON = 0x1954;           //m_latestNonOffhandWeapons
constexpr ULONG64 OFF_CURRENTZOOMFOV = 0x15e0 + 0x00b8;  //m_playerData + m_curZoomFOV
constexpr ULONG64 OFF_TARGETZOOMFOV = 0x15e0 + 0x00bc;   //m_playerData + m_targetZoomFOV
constexpr ULONG64 OFF_SKIN = 0x0d68;                     //m_nSkin
constexpr ULONG64 OFF_TIME_BASE = 0x2098;                //m_currentFramePlayer.timeBase
constexpr ULONG64 OFF_WEAPON_DISCARDED = 0x15a9;         //[RecvTable.DT_WeaponX]->m_discarded
constexpr ULONG64 OFF_VIEWMODELS = 0x2da8;               //m_hViewModels

// Glow
constexpr ULONG64 OFF_HIGHLIGHT_TYPE_SIZE = 0x34;
constexpr ULONG64 OFF_GLOW_THROUGH_WALL = 0x26c; //[DT_HighlightSettings].?
constexpr ULONG64 OFF_GLOW_FIX = 0x278;
constexpr ULONG64 OFF_GLOW_HIGHLIGHT_ID = 0x29C; //[DT_HighlightSettings].m_highlightServerActiveStates
constexpr ULONG64 OFF_GLOW_HIGHLIGHTS = 0xb0d8ff0; //
constexpr ULONG64 OFF_GLOW_ENABLE = 0x26c;
