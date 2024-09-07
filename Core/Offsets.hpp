#pragma once
#include <string>
// https://www.unknowncheats.me/forum/apex-legends/319804-apex-legends-reversal-structs-offsets.html
// GameVersion = v3.0.79.44
 
std::string CheatVersion = "Version 1.1.4";
std::string GameVersion = "v3.0.79.44"; // [Miscellaneous]->GameVersion

// Core
constexpr ULONG64 OFF_REGION = 0x140000000; // [Static]->Region
constexpr ULONG64 OFF_LEVEL = 0x17ec544; // [Miscellaneous]->LevelName
constexpr ULONG64 OFF_LOCAL_PLAYER = 0x23e91f8; // [Miscellaneous]->LocalPlayer
constexpr ULONG64 OFF_ENTITY_LIST = 0x1f15f88; // [Miscellaneous]->cl_entitylist
constexpr ULONG64 OFF_NAME_INDEX = 0x38; // NameIndex
constexpr ULONG64 OFF_NAME_LIST = 0xd388450; // [Miscellaneous]->NameList
constexpr ULONG64 OFF_GAMEMODE = 0x02421250; // [ConVars]->mp_gamemode
constexpr ULONG64 OFF_SQUAD_ID = 0x0344; // [RecvTable.DT_BaseEntity]->m_squadID
constexpr ULONG64 OFF_GLOBAL_VARS = 0x17ec040; // [Miscellaneous]->GlobalVars

// HUD
constexpr ULONG64 OFF_VIEWRENDER = 0x769b558; // [Miscellaneous]->ViewRender
constexpr ULONG64 OFF_VIEWMATRIX = 0x11a350; // [Miscellaneous]->ViewMatrix

// Buttons
constexpr ULONG64 OFF_INATTACK = 0x0769b658; // [Buttons]->in_attack
constexpr ULONG64 OFF_IN_JUMP = 0x0769b778; // [Buttons]->in_jump
constexpr ULONG64 OFF_IN_DUCK = 0x0769b868; // [Buttons]->in_duck
constexpr ULONG64 OFF_IN_FORWARD = 0x0769b5a8; // [Buttons]->in_forward
constexpr ULONG64 OFF_IN_BACKWARD = 0x0769b5d0; // [Buttons]->in_backward
constexpr ULONG64 OFF_TRAVERSAL_START_TIME = 0x2b70; // [RecvTable.DT_LocalPlayerExclusive]->m_traversalStartTime
constexpr ULONG64 OFF_TRAVERSAL_PROGRESS = 0x2b6c; // [RecvTable.DT_LocalPlayerExclusive]->m_traversalProgress
constexpr ULONG64 OFF_WALL_RUN_START_TIME = 0x3614; // [RecvTable.DT_LocalPlayerExclusive]->m_wallRunStartTime
constexpr ULONG64 OFF_WALL_RUN_CLEAR_TIME = 0x3618; // [RecvTable.DT_LocalPlayerExclusive]->m_wallRunClearTime

// Player
constexpr ULONG64 OFF_HEALTH = 0x0328; // [RecvTable.DT_Player]->m_iHealth
constexpr ULONG64 OFF_MAXHEALTH = 0x0470; // [RecvTable.DT_Player]->m_iMaxHealth
constexpr ULONG64 OFF_SHIELD = 0x01a0; // [RecvTable.DT_TitanSoul]->m_shieldHealth
constexpr ULONG64 OFF_MAXSHIELD = 0x01a4; // [RecvTable.DT_TitanSoul]->m_shieldHealthMax
constexpr ULONG64 OFF_CAMERAORIGIN = 0x1ee0; // [Miscellaneous]->CPlayer!camera_origin
constexpr ULONG64 OFF_STUDIOHDR = 0x1000; // [Miscellaneous]->CBaseAnimating!m_pStudioHdr
constexpr ULONG64 OFF_BONES = 0x0db0 + 0x48; // [RecvTable.DT_BaseAnimating]->m_nForceBone
constexpr ULONG64 OFF_LOCAL_ORIGIN = 0x017c; // [DataMap.C_BaseEntity]->m_vecAbsOrigin
constexpr ULONG64 OFF_ABSVELOCITY = 0x0170; // [DataMap.C_BaseEntity]->m_vecAbsVelocity
constexpr ULONG64 OFF_ZOOMING = 0x1be1; // [RecvTable.DT_Player]->m_bZooming
constexpr ULONG64 OFF_TEAM_NUMBER = 0x0338; // [RecvTable.DT_BaseEntity]->m_iTeamNum
constexpr ULONG64 OFF_NAME = 0x0481; // [RecvTable.DT_BaseEntity]->m_iName
constexpr ULONG64 OFF_LIFE_STATE = 0x0690; // [RecvTable.DT_Player]->m_lifeState
constexpr ULONG64 OFF_BLEEDOUT_STATE = 0x2760; // [RecvTable.DT_Player]->m_bleedoutState
constexpr ULONG64 OFF_LAST_VISIBLE_TIME = 0x19a0; // [Miscellaneous]->CPlayer!lastVisibleTime
constexpr ULONG64 OFF_LAST_AIMEDAT_TIME = 0x19a8; // [Miscellaneous]->CWeaponX!lastCrosshairTargetTime
constexpr ULONG64 OFF_VIEW_ANGLES = 0x2534 - 0x14; // [DataMap.C_Player]->m_ammoPoolCapacity - 0x14
constexpr ULONG64 OFF_PUNCH_ANGLES = 0x2438; // [DataMap.C_Player]->m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
constexpr ULONG64 OFF_YAW = 0x223c - 0x8; // [DataMap.C_Player]->m_currentFramePlayer.m_ammoPoolCount - 0x8
constexpr ULONG64 OFF_MODELNAME = 0x0030; // [DataMap.C_BaseEntity]->m_ModelName
constexpr ULONG64 OFF_OBSERVER_LIST = 0x1f17ee8;   //observerList: 48 8B 0D ? ? ? ? 48 85 C9 74 ? 48 8B 01 FF ? ? 48 85 C0 74 ? 48 63 4E 38
constexpr ULONG64 OFF_OBSERVER_LIST_IN_ARRAY = 0x974; // 0x964 before
constexpr ULONG64 OFF_SKY_DIVE_STATUS = 0x4724; // [DataMap.C_Player]->m_skydiveState
constexpr ULONG64 OFF_DUCK_STATUS = 0x2a60; // [DataMap.C_Player]->m_duckState
constexpr ULONG64 OFF_CENTITY_FLAGS = 0x00c8; // [DataMap.C_Player]->m_fFlags
constexpr ULONG64 OFF_GRAPPLE = 0x2cc0; // [RecvTable.DT_Player].m_grapple
constexpr ULONG64 OFF_GRAPPLE_ATTACHED = 0x2d50; // [RecvTable.DT_Player]->m_grappleActive

// Weapon
constexpr ULONG64 OFF_WEAPON_HANDLE = 0x1944; // [RecvTable.DT_Player]->m_latestPrimaryWeapons
constexpr ULONG64 OFF_WEAPON_INDEX = 0x1788; // [RecvTable.DT_WeaponX]->m_weaponNameIndex
constexpr ULONG64 OFF_PROJECTILESCALE = 0x04f4 + 0x19d8; // [WeaponSettings]->projectile_gravity_scale + 0x8
constexpr ULONG64 OFF_PROJECTILESPEED = 0x04ec + 0x19d8; // [WeaponSettings]->projectile_launch_speed
constexpr ULONG64 OFF_OFFHAND_WEAPON = 0x1954; // [RecvTable.DT_BaseCombatCharacter]->m_latestNonOffhandWeapons
constexpr ULONG64 OFF_CURRENTZOOMFOV = 0x15e0 + 0x00b8; // [RecvTable.DT_WeaponX]->m_playerData + [RecvTable.DT_WeaponPlayerData]->m_curZoomFOV
constexpr ULONG64 OFF_TARGETZOOMFOV = 0x15e0 + 0x00bc; // [RecvTable.DT_WeaponX]->m_playerData + [RecvTable.DT_WeaponPlayerData]->m_targetZoomFOV
constexpr ULONG64 OFF_SKIN = 0x0d68; // [DataMap.C_BaseAnimating]->m_nSkin
constexpr ULONG64 OFF_TIME_BASE = 0x2088; // [DataMap.C_Player]->m_currentFramePlayer.timeBase
constexpr ULONG64 OFF_WEAPON_DISCARDED = 0x15a9; // [RecvTable.DT_WeaponX]->m_discarded
constexpr ULONG64 OFF_VIEWMODELS = 0x2d98; // [RecvTable.DT_Player]->m_hViewModels
constexpr ULONG64 OFF_IN_RELOAD = 0x15aa; // [RecvTable.DT_WeaponX_LocalWeaponData]->m_bInReload
constexpr ULONG64 OFF_NEXT_READY_TIME = 0x1568; // [DataMap.CWeaponX]->m_nextReadyTime

// Glow
constexpr ULONG64 OFF_HIGHLIGHT_TYPE_SIZE = 0x34;
constexpr ULONG64 OFF_GLOW_THROUGH_WALL = 0x26c; //[DT_HighlightSettings].?
constexpr ULONG64 OFF_GLOW_FIX = 0x278;
constexpr ULONG64 OFF_GLOW_HIGHLIGHT_ID = 0x29C; //[DT_HighlightSettings].m_highlightServerActiveStates
constexpr ULONG64 OFF_GLOW_HIGHLIGHTS = 0xb13c6a0; // [Miscellaneous]->HighlightSettings
constexpr ULONG64 OFF_GLOW_ENABLE = 0x26c; //

// Item
constexpr ULONG64 OFF_CUSTOM_SCRIPT_INT = 0x1568; // [RecvTable.DT_PropSurvival]->m_customScriptInt
