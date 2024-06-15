#pragma once
//#include <X11/X.h> linux
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <numeric>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/GlowMode.hpp"
#include "../Core/Camera.hpp"
#include "../Core/Level.hpp"

#include "../Features/Legitbot.hpp"
#include "../Features/Ragebot.hpp"
#include "../Features/Triggerbot.hpp"
#include "../Features/Misc.hpp"

#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/Color.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/InputTypes.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Geometry
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))
#define ABS(x) ((x < 0) ? (-x) : (x))

struct Sense {
	// Variables
	//XDisplay* X11Display;
	DriverHID* DHID;
	Camera* GameCamera;
	LocalPlayer* Myself;
	std::vector<Player*>* Players;
	std::chrono::milliseconds LastSpectatorUpdateTime;
	std::vector<std::string> Spectators;
	std::chrono::milliseconds LastUpdateTime;

	std::chrono::milliseconds processingLastUpdate;
	std::vector<double> processingTimes;
	double processingTime;

	std::chrono::milliseconds FpsUpdate;
	int FpsLastFrame;
	int Fps;

	bool VisWarning;

	Level* Map;

	Sense(Level* Map, std::vector<Player*>* Players, Camera* GameCamera, LocalPlayer* Myself, DriverHID* DHID) {
		this->Players = Players;
		this->GameCamera = GameCamera;
		this->Map = Map;
		this->Myself = Myself;
		this->DHID = DHID;
	}

	static bool Save() {
		try {

			Config::Sense::Enabled = Features::Sense::Enabled;
			Config::Sense::DrawFOVCircle = Features::Sense::DrawFOVCircle;
			Config::Sense::DrawFilledFOVCircle = Features::Sense::DrawFilledFOVCircle;
			Config::Sense::FOVThickness = Features::Sense::FOVThickness;
			Config::Sense::GameFOV = Features::Sense::GameFOV;
			Config::Sense::DrawTargetLine = Features::Sense::DrawTargetLine;
			Config::Sense::DrawTargetDot = Features::Sense::DrawTargetDot;
			Config::Sense::DrawTargetBox = Features::Sense::DrawTargetBox;
			Config::Sense::TargetMode = Features::Sense::TargetMode;
			Config::Sense::TargetBoneMode = Features::Sense::TargetBoneMode;
			Config::Sense::TargetSelectedBone = Features::Sense::TargetSelectedBone;
			Config::Sense::TargetBone = Features::Sense::TargetBone;
			Config::Sense::TargetHitbox = static_cast<int>(Features::Sense::TargetHitbox);
			Config::Sense::TargetLineThickness = Features::Sense::TargetLineThickness;
			Config::Sense::TargetDotRadius = Features::Sense::TargetDotRadius;
			Config::Sense::TargetBoxMode = Features::Sense::TargetBoxMode;
			Config::Sense::TargetBoxThickness = Features::Sense::TargetBoxThickness;
			Config::Sense::TargetBoxSize = Features::Sense::TargetBoxSize;
			Config::Sense::DrawTargetInfo = Features::Sense::DrawTargetInfo;
			Config::Sense::TargetInfoDisplayMode = Features::Sense::TargetInfoDisplayMode;
			Config::Sense::DrawTargetInfoName = Features::Sense::DrawTargetInfoName;
			Config::Sense::TargetInfoNamePos = Features::Sense::TargetInfoNamePos;
			Config::Sense::DrawTargetInfoLegend = Features::Sense::DrawTargetInfoLegend;
			Config::Sense::TargetInfoLegendPos = Features::Sense::TargetInfoLegendPos;
			Config::Sense::DrawTargetInfoTeamID = Features::Sense::DrawTargetInfoTeamID;
			Config::Sense::DrawTargetInfoDistance = Features::Sense::DrawTargetInfoDistance;
			Config::Sense::DrawTargetInfoWeapon = Features::Sense::DrawTargetInfoWeapon;
			Config::Sense::TargetInfoWeaponPos = Features::Sense::TargetInfoWeaponPos;
			Config::Sense::DrawTargetInfoHealth = Features::Sense::DrawTargetInfoHealth;
			Config::Sense::TargetInfoHealthPos = Features::Sense::TargetInfoHealthPos;
			Config::Sense::DrawTargetInfoShield = Features::Sense::DrawTargetInfoShield;
			Config::Sense::TargetInfoShieldPos = Features::Sense::TargetInfoShieldPos;
			Config::Sense::TargetInfoColorMode = Features::Sense::TargetInfoColorMode;
			Config::Sense::TargetInfoPosX = Features::Sense::TargetInfoPosX;
			Config::Sense::TargetInfoPosY = Features::Sense::TargetInfoPosY;
			Config::Sense::TargetInfoOffset = Features::Sense::TargetInfoOffset;
			Config::Sense::DrawCrosshair = Features::Sense::DrawCrosshair;
			Config::Sense::CrosshairSize = Features::Sense::CrosshairSize;
			Config::Sense::CrosshairThickness = Features::Sense::CrosshairThickness;
			Config::Sense::ShowSpectators = Features::Sense::ShowSpectators;
			Config::Sense::DrawSpectatorWarning = Features::Sense::DrawSpectatorWarning;
			Config::Sense::DrawVisibleWarning = Features::Sense::DrawVisibleWarning;
			Config::Sense::WarningTextOutline = Features::Sense::WarningTextOutline;
			Config::Sense::WarningTextX = Features::Sense::WarningTextX;
			Config::Sense::WarningTextY = Features::Sense::WarningTextY;
			Config::Sense::TextOutline = Features::Sense::TextOutline;
			Config::Sense::VisibilityCheck = Features::Sense::VisibilityCheck;
			Config::Sense::KnockedCheck = Features::Sense::KnockedCheck;
			Config::Sense::ESPMaxDistance = Features::Sense::ESPMaxDistance;

			Config::SenseEnemy::DrawEnemy = Features::Sense::Enemy::DrawEnemy;
			Config::SenseEnemy::DrawBoxes = Features::Sense::Enemy::DrawBoxes;
			Config::SenseEnemy::BoxOutline = Features::Sense::Enemy::BoxOutline;
			Config::SenseEnemy::BoxType = Features::Sense::Enemy::BoxType;
			Config::SenseEnemy::BoxStyle = Features::Sense::Enemy::BoxStyle;
			Config::SenseEnemy::BoxThickness = Features::Sense::Enemy::BoxThickness;
			Config::SenseEnemy::DrawSkeleton = Features::Sense::Enemy::DrawSkeleton;
			Config::SenseEnemy::SkeletonOutline = Features::Sense::Enemy::SkeletonOutline;
			Config::SenseEnemy::SkeletonDetail = Features::Sense::Enemy::SkeletonDetail;
			Config::SenseEnemy::SkeletonThickness = Features::Sense::Enemy::SkeletonThickness;
			Config::SenseEnemy::DrawHeadCircle = Features::Sense::Enemy::DrawHeadCircle;
			Config::SenseEnemy::HeadCircleOutline = Features::Sense::Enemy::HeadCircleOutline;
			Config::SenseEnemy::HeadCircleThickness = Features::Sense::Enemy::HeadCircleThickness;
			Config::SenseEnemy::DrawBars = Features::Sense::Enemy::DrawBars;
			Config::SenseEnemy::HealthBar = Features::Sense::Enemy::HealthBar;
			Config::SenseEnemy::ShieldBar = Features::Sense::Enemy::ShieldBar;
			Config::SenseEnemy::BarMode = Features::Sense::Enemy::BarMode;
			Config::SenseEnemy::BarStyle = Features::Sense::Enemy::BarStyle;
			Config::SenseEnemy::BarThickness = Features::Sense::Enemy::BarThickness;
			Config::SenseEnemy::BarThickness2 = Features::Sense::Enemy::BarThickness2;
			Config::SenseEnemy::BarHeight = Features::Sense::Enemy::BarHeight;
			Config::SenseEnemy::BarWidth = Features::Sense::Enemy::BarWidth;
			Config::SenseEnemy::BarColorMode = Features::Sense::Enemy::BarColorMode;
			Config::SenseEnemy::WeaponColorType = Features::Sense::Enemy::WeaponColorType;
			Config::SenseEnemy::DrawDistance = Features::Sense::Enemy::DrawDistance;
			Config::SenseEnemy::TracerPosition = Features::Sense::Enemy::TracerPosition;
			Config::SenseEnemy::TracerBone = Features::Sense::Enemy::TracerBone;
			Config::SenseEnemy::DrawTracers = Features::Sense::Enemy::DrawTracers;
			Config::SenseEnemy::TracerThickness = Features::Sense::Enemy::TracerThickness;
			Config::SenseEnemy::DrawNames = Features::Sense::Enemy::DrawNames;
			Config::SenseEnemy::DrawSeer = Features::Sense::Enemy::DrawSeer;
			Config::SenseEnemy::DrawStatus = Features::Sense::Enemy::DrawStatus;
			Config::SenseEnemy::ShowMaxStatusValues = Features::Sense::Enemy::ShowMaxStatusValues;
			Config::SenseEnemy::DrawWeapon = Features::Sense::Enemy::DrawWeapon;
			Config::SenseEnemy::DrawLegend = Features::Sense::Enemy::DrawLegend;

			Config::SenseTeammate::DrawTeam = Features::Sense::Teammate::DrawTeam;
			Config::SenseTeammate::DrawBoxes = Features::Sense::Teammate::DrawBoxes;
			Config::SenseTeammate::BoxOutline = Features::Sense::Teammate::BoxOutline;
			Config::SenseTeammate::BoxType = Features::Sense::Teammate::BoxType;
			Config::SenseTeammate::BoxStyle = Features::Sense::Teammate::BoxStyle;
			Config::SenseTeammate::BoxThickness = Features::Sense::Teammate::BoxThickness;
			Config::SenseTeammate::DrawSkeleton = Features::Sense::Teammate::DrawSkeleton;
			Config::SenseTeammate::SkeletonOutline = Features::Sense::Teammate::SkeletonOutline;
			Config::SenseTeammate::SkeletonDetail = Features::Sense::Teammate::SkeletonDetail;
			Config::SenseTeammate::SkeletonThickness = Features::Sense::Teammate::SkeletonThickness;
			Config::SenseTeammate::DrawHeadCircle = Features::Sense::Teammate::DrawHeadCircle;
			Config::SenseTeammate::HeadCircleOutline = Features::Sense::Teammate::HeadCircleOutline;
			Config::SenseTeammate::HeadCircleThickness = Features::Sense::Teammate::HeadCircleThickness;
			Config::SenseTeammate::DrawBars = Features::Sense::Teammate::DrawBars;
			Config::SenseTeammate::HealthBar = Features::Sense::Teammate::HealthBar;
			Config::SenseTeammate::ShieldBar = Features::Sense::Teammate::ShieldBar;
			Config::SenseTeammate::BarMode = Features::Sense::Teammate::BarMode;
			Config::SenseTeammate::BarStyle = Features::Sense::Teammate::BarStyle;
			Config::SenseTeammate::BarThickness = Features::Sense::Teammate::BarThickness;
			Config::SenseTeammate::BarThickness2 = Features::Sense::Teammate::BarThickness2;
			Config::SenseTeammate::BarHeight = Features::Sense::Teammate::BarHeight;
			Config::SenseTeammate::BarWidth = Features::Sense::Teammate::BarWidth;
			Config::SenseTeammate::BarColorMode = Features::Sense::Teammate::BarColorMode;
			Config::SenseTeammate::WeaponColorType = Features::Sense::Teammate::WeaponColorType;
			Config::SenseTeammate::DrawDistance = Features::Sense::Teammate::DrawDistance;
			Config::SenseTeammate::TracerPosition = Features::Sense::Teammate::TracerPosition;
			Config::SenseTeammate::TracerBone = Features::Sense::Teammate::TracerBone;
			Config::SenseTeammate::DrawTracers = Features::Sense::Teammate::DrawTracers;
			Config::SenseTeammate::TracerThickness = Features::Sense::Teammate::TracerThickness;
			Config::SenseTeammate::DrawNames = Features::Sense::Teammate::DrawNames;
			Config::SenseTeammate::DrawSeer = Features::Sense::Teammate::DrawSeer;
			Config::SenseTeammate::DrawStatus = Features::Sense::Teammate::DrawStatus;
			Config::SenseTeammate::ShowMaxStatusValues = Features::Sense::Teammate::ShowMaxStatusValues;
			Config::SenseTeammate::DrawWeapon = Features::Sense::Teammate::DrawWeapon;
			Config::SenseTeammate::DrawLegend = Features::Sense::Teammate::DrawLegend;


			Config::SensePositions::NamePosition = Features::Sense::Positions::NamePosition;
			Config::SensePositions::DistancePosition = Features::Sense::Positions::DistancePosition;
			Config::SensePositions::LegendPosition = Features::Sense::Positions::LegendPosition;
			Config::SensePositions::WeaponPosition = Features::Sense::Positions::WeaponPosition;
			Config::SensePositions::StatusPosition = Features::Sense::Positions::StatusPosition;

			// Colors
			Config::SenseEnemy::WeaponColorType = Features::Sense::Enemy::WeaponColorType;
			Config::EnemyColors::InvisibleBoxColorR = Features::Colors::Enemy::InvisibleBoxColor[0];
			Config::EnemyColors::InvisibleBoxColorG = Features::Colors::Enemy::InvisibleBoxColor[1];
			Config::EnemyColors::InvisibleBoxColorB = Features::Colors::Enemy::InvisibleBoxColor[2];
			Config::EnemyColors::InvisibleBoxColorA = Features::Colors::Enemy::InvisibleBoxColor[3];
			Config::EnemyColors::VisibleBoxColorR = Features::Colors::Enemy::VisibleBoxColor[0];
			Config::EnemyColors::VisibleBoxColorG = Features::Colors::Enemy::VisibleBoxColor[1];
			Config::EnemyColors::VisibleBoxColorB = Features::Colors::Enemy::VisibleBoxColor[2];
			Config::EnemyColors::VisibleBoxColorA = Features::Colors::Enemy::VisibleBoxColor[3];
			Config::EnemyColors::KnockedBoxColorR = Features::Colors::Enemy::KnockedBoxColor[0];
			Config::EnemyColors::KnockedBoxColorG = Features::Colors::Enemy::KnockedBoxColor[1];
			Config::EnemyColors::KnockedBoxColorB = Features::Colors::Enemy::KnockedBoxColor[2];
			Config::EnemyColors::KnockedBoxColorA = Features::Colors::Enemy::KnockedBoxColor[3];
			Config::EnemyColors::InvisibleFilledBoxColorR = Features::Colors::Enemy::InvisibleFilledBoxColor[0];
			Config::EnemyColors::InvisibleFilledBoxColorG = Features::Colors::Enemy::InvisibleFilledBoxColor[1];
			Config::EnemyColors::InvisibleFilledBoxColorB = Features::Colors::Enemy::InvisibleFilledBoxColor[2];
			Config::EnemyColors::InvisibleFilledBoxColorA = Features::Colors::Enemy::InvisibleFilledBoxColor[3];
			Config::EnemyColors::VisibleFilledBoxColorR = Features::Colors::Enemy::VisibleFilledBoxColor[0];
			Config::EnemyColors::VisibleFilledBoxColorG = Features::Colors::Enemy::VisibleFilledBoxColor[1];
			Config::EnemyColors::VisibleFilledBoxColorB = Features::Colors::Enemy::VisibleFilledBoxColor[2];
			Config::EnemyColors::VisibleFilledBoxColorA = Features::Colors::Enemy::VisibleFilledBoxColor[3];
			Config::EnemyColors::KnockedFilledBoxColorR = Features::Colors::Enemy::KnockedFilledBoxColor[0];
			Config::EnemyColors::KnockedFilledBoxColorG = Features::Colors::Enemy::KnockedFilledBoxColor[1];
			Config::EnemyColors::KnockedFilledBoxColorB = Features::Colors::Enemy::KnockedFilledBoxColor[2];
			Config::EnemyColors::KnockedFilledBoxColorA = Features::Colors::Enemy::KnockedFilledBoxColor[3];
			Config::EnemyColors::InvisibleTracerColorR = Features::Colors::Enemy::InvisibleTracerColor[0];
			Config::EnemyColors::InvisibleTracerColorG = Features::Colors::Enemy::InvisibleTracerColor[1];
			Config::EnemyColors::InvisibleTracerColorB = Features::Colors::Enemy::InvisibleTracerColor[2];
			Config::EnemyColors::InvisibleTracerColorA = Features::Colors::Enemy::InvisibleTracerColor[3];
			Config::EnemyColors::VisibleTracerColorR = Features::Colors::Enemy::VisibleTracerColor[0];
			Config::EnemyColors::VisibleTracerColorG = Features::Colors::Enemy::VisibleTracerColor[1];
			Config::EnemyColors::VisibleTracerColorB = Features::Colors::Enemy::VisibleTracerColor[2];
			Config::EnemyColors::VisibleTracerColorA = Features::Colors::Enemy::VisibleTracerColor[3];
			Config::EnemyColors::KnockedTracerColorR = Features::Colors::Enemy::KnockedTracerColor[0];
			Config::EnemyColors::KnockedTracerColorG = Features::Colors::Enemy::KnockedTracerColor[1];
			Config::EnemyColors::KnockedTracerColorB = Features::Colors::Enemy::KnockedTracerColor[2];
			Config::EnemyColors::KnockedTracerColorA = Features::Colors::Enemy::KnockedTracerColor[3];
			Config::EnemyColors::InvisibleSkeletonColorR = Features::Colors::Enemy::InvisibleSkeletonColor[0];
			Config::EnemyColors::InvisibleSkeletonColorG = Features::Colors::Enemy::InvisibleSkeletonColor[1];
			Config::EnemyColors::InvisibleSkeletonColorB = Features::Colors::Enemy::InvisibleSkeletonColor[2];
			Config::EnemyColors::InvisibleSkeletonColorA = Features::Colors::Enemy::InvisibleSkeletonColor[3];
			Config::EnemyColors::VisibleSkeletonColorR = Features::Colors::Enemy::VisibleSkeletonColor[0];
			Config::EnemyColors::VisibleSkeletonColorG = Features::Colors::Enemy::VisibleSkeletonColor[1];
			Config::EnemyColors::VisibleSkeletonColorB = Features::Colors::Enemy::VisibleSkeletonColor[2];
			Config::EnemyColors::VisibleSkeletonColorA = Features::Colors::Enemy::VisibleSkeletonColor[3];
			Config::EnemyColors::KnockedSkeletonColorR = Features::Colors::Enemy::KnockedSkeletonColor[0];
			Config::EnemyColors::KnockedSkeletonColorG = Features::Colors::Enemy::KnockedSkeletonColor[1];
			Config::EnemyColors::KnockedSkeletonColorB = Features::Colors::Enemy::KnockedSkeletonColor[2];
			Config::EnemyColors::KnockedSkeletonColorA = Features::Colors::Enemy::KnockedSkeletonColor[3];
			Config::EnemyColors::InvisibleHeadCircleColorR = Features::Colors::Enemy::InvisibleHeadCircleColor[0];
			Config::EnemyColors::InvisibleHeadCircleColorG = Features::Colors::Enemy::InvisibleHeadCircleColor[1];
			Config::EnemyColors::InvisibleHeadCircleColorB = Features::Colors::Enemy::InvisibleHeadCircleColor[2];
			Config::EnemyColors::InvisibleHeadCircleColorA = Features::Colors::Enemy::InvisibleHeadCircleColor[3];
			Config::EnemyColors::VisibleHeadCircleColorR = Features::Colors::Enemy::VisibleHeadCircleColor[0];
			Config::EnemyColors::VisibleHeadCircleColorG = Features::Colors::Enemy::VisibleHeadCircleColor[1];
			Config::EnemyColors::VisibleHeadCircleColorB = Features::Colors::Enemy::VisibleHeadCircleColor[2];
			Config::EnemyColors::VisibleHeadCircleColorA = Features::Colors::Enemy::VisibleHeadCircleColor[3];
			Config::EnemyColors::KnockedHeadCircleColorR = Features::Colors::Enemy::KnockedHeadCircleColor[0];
			Config::EnemyColors::KnockedHeadCircleColorG = Features::Colors::Enemy::KnockedHeadCircleColor[1];
			Config::EnemyColors::KnockedHeadCircleColorB = Features::Colors::Enemy::KnockedHeadCircleColor[2];
			Config::EnemyColors::KnockedHeadCircleColorA = Features::Colors::Enemy::KnockedHeadCircleColor[3];
			Config::EnemyColors::InvisibleNameColorR = Features::Colors::Enemy::InvisibleNameColor[0];
			Config::EnemyColors::InvisibleNameColorG = Features::Colors::Enemy::InvisibleNameColor[1];
			Config::EnemyColors::InvisibleNameColorB = Features::Colors::Enemy::InvisibleNameColor[2];
			Config::EnemyColors::InvisibleNameColorA = Features::Colors::Enemy::InvisibleNameColor[3];
			Config::EnemyColors::VisibleNameColorR = Features::Colors::Enemy::VisibleNameColor[0];
			Config::EnemyColors::VisibleNameColorG = Features::Colors::Enemy::VisibleNameColor[1];
			Config::EnemyColors::VisibleNameColorB = Features::Colors::Enemy::VisibleNameColor[2];
			Config::EnemyColors::VisibleNameColorA = Features::Colors::Enemy::VisibleNameColor[3];
			Config::EnemyColors::KnockedNameColorR = Features::Colors::Enemy::KnockedNameColor[0];
			Config::EnemyColors::KnockedNameColorG = Features::Colors::Enemy::KnockedNameColor[1];
			Config::EnemyColors::KnockedNameColorB = Features::Colors::Enemy::KnockedNameColor[2];
			Config::EnemyColors::KnockedNameColorA = Features::Colors::Enemy::KnockedNameColor[3];
			Config::EnemyColors::InvisibleDistanceColorR = Features::Colors::Enemy::InvisibleDistanceColor[0];
			Config::EnemyColors::InvisibleDistanceColorG = Features::Colors::Enemy::InvisibleDistanceColor[1];
			Config::EnemyColors::InvisibleDistanceColorB = Features::Colors::Enemy::InvisibleDistanceColor[2];
			Config::EnemyColors::InvisibleDistanceColorA = Features::Colors::Enemy::InvisibleDistanceColor[3];
			Config::EnemyColors::VisibleDistanceColorR = Features::Colors::Enemy::VisibleDistanceColor[0];
			Config::EnemyColors::VisibleDistanceColorG = Features::Colors::Enemy::VisibleDistanceColor[1];
			Config::EnemyColors::VisibleDistanceColorB = Features::Colors::Enemy::VisibleDistanceColor[2];
			Config::EnemyColors::VisibleDistanceColorA = Features::Colors::Enemy::VisibleDistanceColor[3];
			Config::EnemyColors::KnockedDistanceColorR = Features::Colors::Enemy::KnockedDistanceColor[0];
			Config::EnemyColors::KnockedDistanceColorG = Features::Colors::Enemy::KnockedDistanceColor[1];
			Config::EnemyColors::KnockedDistanceColorB = Features::Colors::Enemy::KnockedDistanceColor[2];
			Config::EnemyColors::KnockedDistanceColorA = Features::Colors::Enemy::KnockedDistanceColor[3];
			Config::EnemyColors::InvisibleLegendColorR = Features::Colors::Enemy::InvisibleLegendColor[0];
			Config::EnemyColors::InvisibleLegendColorG = Features::Colors::Enemy::InvisibleLegendColor[1];
			Config::EnemyColors::InvisibleLegendColorB = Features::Colors::Enemy::InvisibleLegendColor[2];
			Config::EnemyColors::InvisibleLegendColorA = Features::Colors::Enemy::InvisibleLegendColor[3];
			Config::EnemyColors::VisibleLegendColorR = Features::Colors::Enemy::VisibleLegendColor[0];
			Config::EnemyColors::VisibleLegendColorG = Features::Colors::Enemy::VisibleLegendColor[1];
			Config::EnemyColors::VisibleLegendColorB = Features::Colors::Enemy::VisibleLegendColor[2];
			Config::EnemyColors::VisibleLegendColorA = Features::Colors::Enemy::VisibleLegendColor[3];
			Config::EnemyColors::KnockedLegendColorR = Features::Colors::Enemy::KnockedLegendColor[0];
			Config::EnemyColors::KnockedLegendColorG = Features::Colors::Enemy::KnockedLegendColor[1];
			Config::EnemyColors::KnockedLegendColorB = Features::Colors::Enemy::KnockedLegendColor[2];
			Config::EnemyColors::KnockedLegendColorA = Features::Colors::Enemy::KnockedLegendColor[3];
			Config::EnemyColors::InvisibleWeaponColorR = Features::Colors::Enemy::InvisibleWeaponColor[0];
			Config::EnemyColors::InvisibleWeaponColorG = Features::Colors::Enemy::InvisibleWeaponColor[1];
			Config::EnemyColors::InvisibleWeaponColorB = Features::Colors::Enemy::InvisibleWeaponColor[2];
			Config::EnemyColors::InvisibleWeaponColorA = Features::Colors::Enemy::InvisibleWeaponColor[3];
			Config::EnemyColors::VisibleWeaponColorR = Features::Colors::Enemy::VisibleWeaponColor[0];
			Config::EnemyColors::VisibleWeaponColorG = Features::Colors::Enemy::VisibleWeaponColor[1];
			Config::EnemyColors::VisibleWeaponColorB = Features::Colors::Enemy::VisibleWeaponColor[2];
			Config::EnemyColors::VisibleWeaponColorA = Features::Colors::Enemy::VisibleWeaponColor[3];
			Config::EnemyColors::KnockedWeaponColorR = Features::Colors::Enemy::KnockedWeaponColor[0];
			Config::EnemyColors::KnockedWeaponColorG = Features::Colors::Enemy::KnockedWeaponColor[1];
			Config::EnemyColors::KnockedWeaponColorB = Features::Colors::Enemy::KnockedWeaponColor[2];
			Config::EnemyColors::KnockedWeaponColorA = Features::Colors::Enemy::KnockedWeaponColor[3];

			Config::Colors::TargetLineColorR = Features::Colors::TargetLineColor[0];
			Config::Colors::TargetLineColorG = Features::Colors::TargetLineColor[1];
			Config::Colors::TargetLineColorB = Features::Colors::TargetLineColor[2];
			Config::Colors::TargetLineColorA = Features::Colors::TargetLineColor[3];
			Config::Colors::TargetLineLockedColorR = Features::Colors::TargetLineLockedColor[0];
			Config::Colors::TargetLineLockedColorG = Features::Colors::TargetLineLockedColor[1];
			Config::Colors::TargetLineLockedColorB = Features::Colors::TargetLineLockedColor[2];
			Config::Colors::TargetLineLockedColorA = Features::Colors::TargetLineLockedColor[3];
			Config::Colors::TargetDotColorR = Features::Colors::TargetDotColor[0];
			Config::Colors::TargetDotColorG = Features::Colors::TargetDotColor[1];
			Config::Colors::TargetDotColorB = Features::Colors::TargetDotColor[2];
			Config::Colors::TargetDotColorA = Features::Colors::TargetDotColor[3];
			Config::Colors::TargetDotLockedColorR = Features::Colors::TargetDotLockedColor[0];
			Config::Colors::TargetDotLockedColorG = Features::Colors::TargetDotLockedColor[1];
			Config::Colors::TargetDotLockedColorB = Features::Colors::TargetDotLockedColor[2];
			Config::Colors::TargetDotLockedColorA = Features::Colors::TargetDotLockedColor[3];
			Config::Colors::TargetBoxColorR = Features::Colors::TargetBoxColor[0];
			Config::Colors::TargetBoxColorG = Features::Colors::TargetBoxColor[1];
			Config::Colors::TargetBoxColorB = Features::Colors::TargetBoxColor[2];
			Config::Colors::TargetBoxColorA = Features::Colors::TargetBoxColor[3];
			Config::Colors::TargetBoxLockedColorR = Features::Colors::TargetBoxLockedColor[0];
			Config::Colors::TargetBoxLockedColorG = Features::Colors::TargetBoxLockedColor[1];
			Config::Colors::TargetBoxLockedColorB = Features::Colors::TargetBoxLockedColor[2];
			Config::Colors::TargetBoxLockedColorA = Features::Colors::TargetBoxLockedColor[3];

			Config::Colors::TargetInfoColorR = Features::Colors::TargetInfoColor[0];
			Config::Colors::TargetInfoColorG = Features::Colors::TargetInfoColor[1];
			Config::Colors::TargetInfoColorB = Features::Colors::TargetInfoColor[2];
			Config::Colors::TargetInfoColorA = Features::Colors::TargetInfoColor[3];
			Config::Colors::TargetInfoLockedColorR = Features::Colors::TargetInfoLockedColor[0];
			Config::Colors::TargetInfoLockedColorG = Features::Colors::TargetInfoLockedColor[1];
			Config::Colors::TargetInfoLockedColorB = Features::Colors::TargetInfoLockedColor[2];
			Config::Colors::TargetInfoLockedColorA = Features::Colors::TargetInfoLockedColor[3];

			Config::Colors::FOVColorR = Features::Colors::FOVColor[0];
			Config::Colors::FOVColorG = Features::Colors::FOVColor[1];
			Config::Colors::FOVColorB = Features::Colors::FOVColor[2];
			Config::Colors::FOVColorA = Features::Colors::FOVColor[3];
			Config::Colors::FilledFOVColorR = Features::Colors::FilledFOVColor[0];
			Config::Colors::FilledFOVColorG = Features::Colors::FilledFOVColor[1];
			Config::Colors::FilledFOVColorB = Features::Colors::FilledFOVColor[2];
			Config::Colors::FilledFOVColorA = Features::Colors::FilledFOVColor[3];
			Config::Colors::CrosshairColorR = Features::Colors::CrosshairColor[0];
			Config::Colors::CrosshairColorG = Features::Colors::CrosshairColor[1];
			Config::Colors::CrosshairColorB = Features::Colors::CrosshairColor[2];
			Config::Colors::CrosshairColorA = Features::Colors::CrosshairColor[3];
			// Weapon Colors
			Config::EnemyColors::LightWeaponColorR = Features::Colors::Enemy::LightWeaponColor[0];
			Config::EnemyColors::LightWeaponColorG = Features::Colors::Enemy::LightWeaponColor[1];
			Config::EnemyColors::LightWeaponColorB = Features::Colors::Enemy::LightWeaponColor[2];
			Config::EnemyColors::LightWeaponColorA = Features::Colors::Enemy::LightWeaponColor[3];
			Config::EnemyColors::HeavyWeaponColorR = Features::Colors::Enemy::HeavyWeaponColor[0];
			Config::EnemyColors::HeavyWeaponColorG = Features::Colors::Enemy::HeavyWeaponColor[1];
			Config::EnemyColors::HeavyWeaponColorB = Features::Colors::Enemy::HeavyWeaponColor[2];
			Config::EnemyColors::HeavyWeaponColorA = Features::Colors::Enemy::HeavyWeaponColor[3];
			Config::EnemyColors::EnergyWeaponColorR = Features::Colors::Enemy::EnergyWeaponColor[0];
			Config::EnemyColors::EnergyWeaponColorG = Features::Colors::Enemy::EnergyWeaponColor[1];
			Config::EnemyColors::EnergyWeaponColorB = Features::Colors::Enemy::EnergyWeaponColor[2];
			Config::EnemyColors::EnergyWeaponColorA = Features::Colors::Enemy::EnergyWeaponColor[3];
			Config::EnemyColors::ShotgunWeaponColorR = Features::Colors::Enemy::ShotgunWeaponColor[0];
			Config::EnemyColors::ShotgunWeaponColorG = Features::Colors::Enemy::ShotgunWeaponColor[1];
			Config::EnemyColors::ShotgunWeaponColorB = Features::Colors::Enemy::ShotgunWeaponColor[2];
			Config::EnemyColors::ShotgunWeaponColorA = Features::Colors::Enemy::ShotgunWeaponColor[3];
			Config::EnemyColors::SniperWeaponColorR = Features::Colors::Enemy::SniperWeaponColor[0];
			Config::EnemyColors::SniperWeaponColorG = Features::Colors::Enemy::SniperWeaponColor[1];
			Config::EnemyColors::SniperWeaponColorB = Features::Colors::Enemy::SniperWeaponColor[2];
			Config::EnemyColors::SniperWeaponColorA = Features::Colors::Enemy::SniperWeaponColor[3];
			Config::EnemyColors::LegendaryWeaponColorR = Features::Colors::Enemy::LegendaryWeaponColor[0];
			Config::EnemyColors::LegendaryWeaponColorG = Features::Colors::Enemy::LegendaryWeaponColor[1];
			Config::EnemyColors::LegendaryWeaponColorB = Features::Colors::Enemy::LegendaryWeaponColor[2];
			Config::EnemyColors::LegendaryWeaponColorA = Features::Colors::Enemy::LegendaryWeaponColor[3];
			Config::EnemyColors::MeleeWeaponColorR = Features::Colors::Enemy::MeleeWeaponColor[0];
			Config::EnemyColors::MeleeWeaponColorG = Features::Colors::Enemy::MeleeWeaponColor[1];
			Config::EnemyColors::MeleeWeaponColorB = Features::Colors::Enemy::MeleeWeaponColor[2];
			Config::EnemyColors::MeleeWeaponColorA = Features::Colors::Enemy::MeleeWeaponColor[3];
			Config::EnemyColors::ThrowableWeaponColorR = Features::Colors::Enemy::ThrowableWeaponColor[0];
			Config::EnemyColors::ThrowableWeaponColorG = Features::Colors::Enemy::ThrowableWeaponColor[1];
			Config::EnemyColors::ThrowableWeaponColorB = Features::Colors::Enemy::ThrowableWeaponColor[2];
			Config::EnemyColors::ThrowableWeaponColorA = Features::Colors::Enemy::ThrowableWeaponColor[3];

			// Colors
			Config::SenseTeammate::WeaponColorType = Features::Sense::Teammate::WeaponColorType;
			Config::TeammateColors::InvisibleBoxColorR = Features::Colors::Teammate::InvisibleBoxColor[0];
			Config::TeammateColors::InvisibleBoxColorG = Features::Colors::Teammate::InvisibleBoxColor[1];
			Config::TeammateColors::InvisibleBoxColorB = Features::Colors::Teammate::InvisibleBoxColor[2];
			Config::TeammateColors::InvisibleBoxColorA = Features::Colors::Teammate::InvisibleBoxColor[3];
			Config::TeammateColors::VisibleBoxColorR = Features::Colors::Teammate::VisibleBoxColor[0];
			Config::TeammateColors::VisibleBoxColorG = Features::Colors::Teammate::VisibleBoxColor[1];
			Config::TeammateColors::VisibleBoxColorB = Features::Colors::Teammate::VisibleBoxColor[2];
			Config::TeammateColors::VisibleBoxColorA = Features::Colors::Teammate::VisibleBoxColor[3];
			Config::TeammateColors::KnockedBoxColorR = Features::Colors::Teammate::KnockedBoxColor[0];
			Config::TeammateColors::KnockedBoxColorG = Features::Colors::Teammate::KnockedBoxColor[1];
			Config::TeammateColors::KnockedBoxColorB = Features::Colors::Teammate::KnockedBoxColor[2];
			Config::TeammateColors::KnockedBoxColorA = Features::Colors::Teammate::KnockedBoxColor[3];
			Config::TeammateColors::InvisibleFilledBoxColorR = Features::Colors::Teammate::InvisibleFilledBoxColor[0];
			Config::TeammateColors::InvisibleFilledBoxColorG = Features::Colors::Teammate::InvisibleFilledBoxColor[1];
			Config::TeammateColors::InvisibleFilledBoxColorB = Features::Colors::Teammate::InvisibleFilledBoxColor[2];
			Config::TeammateColors::InvisibleFilledBoxColorA = Features::Colors::Teammate::InvisibleFilledBoxColor[3];
			Config::TeammateColors::VisibleFilledBoxColorR = Features::Colors::Teammate::VisibleFilledBoxColor[0];
			Config::TeammateColors::VisibleFilledBoxColorG = Features::Colors::Teammate::VisibleFilledBoxColor[1];
			Config::TeammateColors::VisibleFilledBoxColorB = Features::Colors::Teammate::VisibleFilledBoxColor[2];
			Config::TeammateColors::VisibleFilledBoxColorA = Features::Colors::Teammate::VisibleFilledBoxColor[3];
			Config::TeammateColors::KnockedFilledBoxColorR = Features::Colors::Teammate::KnockedFilledBoxColor[0];
			Config::TeammateColors::KnockedFilledBoxColorG = Features::Colors::Teammate::KnockedFilledBoxColor[1];
			Config::TeammateColors::KnockedFilledBoxColorB = Features::Colors::Teammate::KnockedFilledBoxColor[2];
			Config::TeammateColors::KnockedFilledBoxColorA = Features::Colors::Teammate::KnockedFilledBoxColor[3];
			Config::TeammateColors::InvisibleTracerColorR = Features::Colors::Teammate::InvisibleTracerColor[0];
			Config::TeammateColors::InvisibleTracerColorG = Features::Colors::Teammate::InvisibleTracerColor[1];
			Config::TeammateColors::InvisibleTracerColorB = Features::Colors::Teammate::InvisibleTracerColor[2];
			Config::TeammateColors::InvisibleTracerColorA = Features::Colors::Teammate::InvisibleTracerColor[3];
			Config::TeammateColors::VisibleTracerColorR = Features::Colors::Teammate::VisibleTracerColor[0];
			Config::TeammateColors::VisibleTracerColorG = Features::Colors::Teammate::VisibleTracerColor[1];
			Config::TeammateColors::VisibleTracerColorB = Features::Colors::Teammate::VisibleTracerColor[2];
			Config::TeammateColors::VisibleTracerColorA = Features::Colors::Teammate::VisibleTracerColor[3];
			Config::TeammateColors::KnockedTracerColorR = Features::Colors::Teammate::KnockedTracerColor[0];
			Config::TeammateColors::KnockedTracerColorG = Features::Colors::Teammate::KnockedTracerColor[1];
			Config::TeammateColors::KnockedTracerColorB = Features::Colors::Teammate::KnockedTracerColor[2];
			Config::TeammateColors::KnockedTracerColorA = Features::Colors::Teammate::KnockedTracerColor[3];
			Config::TeammateColors::InvisibleSkeletonColorR = Features::Colors::Teammate::InvisibleSkeletonColor[0];
			Config::TeammateColors::InvisibleSkeletonColorG = Features::Colors::Teammate::InvisibleSkeletonColor[1];
			Config::TeammateColors::InvisibleSkeletonColorB = Features::Colors::Teammate::InvisibleSkeletonColor[2];
			Config::TeammateColors::InvisibleSkeletonColorA = Features::Colors::Teammate::InvisibleSkeletonColor[3];
			Config::TeammateColors::VisibleSkeletonColorR = Features::Colors::Teammate::VisibleSkeletonColor[0];
			Config::TeammateColors::VisibleSkeletonColorG = Features::Colors::Teammate::VisibleSkeletonColor[1];
			Config::TeammateColors::VisibleSkeletonColorB = Features::Colors::Teammate::VisibleSkeletonColor[2];
			Config::TeammateColors::VisibleSkeletonColorA = Features::Colors::Teammate::VisibleSkeletonColor[3];
			Config::TeammateColors::KnockedSkeletonColorR = Features::Colors::Teammate::KnockedSkeletonColor[0];
			Config::TeammateColors::KnockedSkeletonColorG = Features::Colors::Teammate::KnockedSkeletonColor[1];
			Config::TeammateColors::KnockedSkeletonColorB = Features::Colors::Teammate::KnockedSkeletonColor[2];
			Config::TeammateColors::KnockedSkeletonColorA = Features::Colors::Teammate::KnockedSkeletonColor[3];
			Config::TeammateColors::InvisibleHeadCircleColorR = Features::Colors::Teammate::InvisibleHeadCircleColor[0];
			Config::TeammateColors::InvisibleHeadCircleColorG = Features::Colors::Teammate::InvisibleHeadCircleColor[1];
			Config::TeammateColors::InvisibleHeadCircleColorB = Features::Colors::Teammate::InvisibleHeadCircleColor[2];
			Config::TeammateColors::InvisibleHeadCircleColorA = Features::Colors::Teammate::InvisibleHeadCircleColor[3];
			Config::TeammateColors::VisibleHeadCircleColorR = Features::Colors::Teammate::VisibleHeadCircleColor[0];
			Config::TeammateColors::VisibleHeadCircleColorG = Features::Colors::Teammate::VisibleHeadCircleColor[1];
			Config::TeammateColors::VisibleHeadCircleColorB = Features::Colors::Teammate::VisibleHeadCircleColor[2];
			Config::TeammateColors::VisibleHeadCircleColorA = Features::Colors::Teammate::VisibleHeadCircleColor[3];
			Config::TeammateColors::KnockedHeadCircleColorR = Features::Colors::Teammate::KnockedHeadCircleColor[0];
			Config::TeammateColors::KnockedHeadCircleColorG = Features::Colors::Teammate::KnockedHeadCircleColor[1];
			Config::TeammateColors::KnockedHeadCircleColorB = Features::Colors::Teammate::KnockedHeadCircleColor[2];
			Config::TeammateColors::KnockedHeadCircleColorA = Features::Colors::Teammate::KnockedHeadCircleColor[3];
			Config::TeammateColors::InvisibleNameColorR = Features::Colors::Teammate::InvisibleNameColor[0];
			Config::TeammateColors::InvisibleNameColorG = Features::Colors::Teammate::InvisibleNameColor[1];
			Config::TeammateColors::InvisibleNameColorB = Features::Colors::Teammate::InvisibleNameColor[2];
			Config::TeammateColors::InvisibleNameColorA = Features::Colors::Teammate::InvisibleNameColor[3];
			Config::TeammateColors::VisibleNameColorR = Features::Colors::Teammate::VisibleNameColor[0];
			Config::TeammateColors::VisibleNameColorG = Features::Colors::Teammate::VisibleNameColor[1];
			Config::TeammateColors::VisibleNameColorB = Features::Colors::Teammate::VisibleNameColor[2];
			Config::TeammateColors::VisibleNameColorA = Features::Colors::Teammate::VisibleNameColor[3];
			Config::TeammateColors::KnockedNameColorR = Features::Colors::Teammate::KnockedNameColor[0];
			Config::TeammateColors::KnockedNameColorG = Features::Colors::Teammate::KnockedNameColor[1];
			Config::TeammateColors::KnockedNameColorB = Features::Colors::Teammate::KnockedNameColor[2];
			Config::TeammateColors::KnockedNameColorA = Features::Colors::Teammate::KnockedNameColor[3];
			Config::TeammateColors::InvisibleDistanceColorR = Features::Colors::Teammate::InvisibleDistanceColor[0];
			Config::TeammateColors::InvisibleDistanceColorG = Features::Colors::Teammate::InvisibleDistanceColor[1];
			Config::TeammateColors::InvisibleDistanceColorB = Features::Colors::Teammate::InvisibleDistanceColor[2];
			Config::TeammateColors::InvisibleDistanceColorA = Features::Colors::Teammate::InvisibleDistanceColor[3];
			Config::TeammateColors::VisibleDistanceColorR = Features::Colors::Teammate::VisibleDistanceColor[0];
			Config::TeammateColors::VisibleDistanceColorG = Features::Colors::Teammate::VisibleDistanceColor[1];
			Config::TeammateColors::VisibleDistanceColorB = Features::Colors::Teammate::VisibleDistanceColor[2];
			Config::TeammateColors::VisibleDistanceColorA = Features::Colors::Teammate::VisibleDistanceColor[3];
			Config::TeammateColors::KnockedDistanceColorR = Features::Colors::Teammate::KnockedDistanceColor[0];
			Config::TeammateColors::KnockedDistanceColorG = Features::Colors::Teammate::KnockedDistanceColor[1];
			Config::TeammateColors::KnockedDistanceColorB = Features::Colors::Teammate::KnockedDistanceColor[2];
			Config::TeammateColors::KnockedDistanceColorA = Features::Colors::Teammate::KnockedDistanceColor[3];
			Config::TeammateColors::InvisibleLegendColorR = Features::Colors::Teammate::InvisibleLegendColor[0];
			Config::TeammateColors::InvisibleLegendColorG = Features::Colors::Teammate::InvisibleLegendColor[1];
			Config::TeammateColors::InvisibleLegendColorB = Features::Colors::Teammate::InvisibleLegendColor[2];
			Config::TeammateColors::InvisibleLegendColorA = Features::Colors::Teammate::InvisibleLegendColor[3];
			Config::TeammateColors::VisibleLegendColorR = Features::Colors::Teammate::VisibleLegendColor[0];
			Config::TeammateColors::VisibleLegendColorG = Features::Colors::Teammate::VisibleLegendColor[1];
			Config::TeammateColors::VisibleLegendColorB = Features::Colors::Teammate::VisibleLegendColor[2];
			Config::TeammateColors::VisibleLegendColorA = Features::Colors::Teammate::VisibleLegendColor[3];
			Config::TeammateColors::KnockedLegendColorR = Features::Colors::Teammate::KnockedLegendColor[0];
			Config::TeammateColors::KnockedLegendColorG = Features::Colors::Teammate::KnockedLegendColor[1];
			Config::TeammateColors::KnockedLegendColorB = Features::Colors::Teammate::KnockedLegendColor[2];
			Config::TeammateColors::KnockedLegendColorA = Features::Colors::Teammate::KnockedLegendColor[3];
			Config::TeammateColors::InvisibleWeaponColorR = Features::Colors::Teammate::InvisibleWeaponColor[0];
			Config::TeammateColors::InvisibleWeaponColorG = Features::Colors::Teammate::InvisibleWeaponColor[1];
			Config::TeammateColors::InvisibleWeaponColorB = Features::Colors::Teammate::InvisibleWeaponColor[2];
			Config::TeammateColors::InvisibleWeaponColorA = Features::Colors::Teammate::InvisibleWeaponColor[3];
			Config::TeammateColors::VisibleWeaponColorR = Features::Colors::Teammate::VisibleWeaponColor[0];
			Config::TeammateColors::VisibleWeaponColorG = Features::Colors::Teammate::VisibleWeaponColor[1];
			Config::TeammateColors::VisibleWeaponColorB = Features::Colors::Teammate::VisibleWeaponColor[2];
			Config::TeammateColors::VisibleWeaponColorA = Features::Colors::Teammate::VisibleWeaponColor[3];
			Config::TeammateColors::KnockedWeaponColorR = Features::Colors::Teammate::KnockedWeaponColor[0];
			Config::TeammateColors::KnockedWeaponColorG = Features::Colors::Teammate::KnockedWeaponColor[1];
			Config::TeammateColors::KnockedWeaponColorB = Features::Colors::Teammate::KnockedWeaponColor[2];
			Config::TeammateColors::KnockedWeaponColorA = Features::Colors::Teammate::KnockedWeaponColor[3];
			Config::Colors::FOVColorR = Features::Colors::FOVColor[0];
			Config::Colors::FOVColorG = Features::Colors::FOVColor[1];
			Config::Colors::FOVColorB = Features::Colors::FOVColor[2];
			Config::Colors::FOVColorA = Features::Colors::FOVColor[3];
			Config::Colors::FilledFOVColorR = Features::Colors::FilledFOVColor[0];
			Config::Colors::FilledFOVColorG = Features::Colors::FilledFOVColor[1];
			Config::Colors::FilledFOVColorB = Features::Colors::FilledFOVColor[2];
			Config::Colors::FilledFOVColorA = Features::Colors::FilledFOVColor[3];
			Config::Colors::CrosshairColorR = Features::Colors::CrosshairColor[0];
			Config::Colors::CrosshairColorG = Features::Colors::CrosshairColor[1];
			Config::Colors::CrosshairColorB = Features::Colors::CrosshairColor[2];
			Config::Colors::CrosshairColorA = Features::Colors::CrosshairColor[3];
			// Weapon Colors
			Config::TeammateColors::LightWeaponColorR = Features::Colors::Teammate::LightWeaponColor[0];
			Config::TeammateColors::LightWeaponColorG = Features::Colors::Teammate::LightWeaponColor[1];
			Config::TeammateColors::LightWeaponColorB = Features::Colors::Teammate::LightWeaponColor[2];
			Config::TeammateColors::LightWeaponColorA = Features::Colors::Teammate::LightWeaponColor[3];
			Config::TeammateColors::HeavyWeaponColorR = Features::Colors::Teammate::HeavyWeaponColor[0];
			Config::TeammateColors::HeavyWeaponColorG = Features::Colors::Teammate::HeavyWeaponColor[1];
			Config::TeammateColors::HeavyWeaponColorB = Features::Colors::Teammate::HeavyWeaponColor[2];
			Config::TeammateColors::HeavyWeaponColorA = Features::Colors::Teammate::HeavyWeaponColor[3];
			Config::TeammateColors::EnergyWeaponColorR = Features::Colors::Teammate::EnergyWeaponColor[0];
			Config::TeammateColors::EnergyWeaponColorG = Features::Colors::Teammate::EnergyWeaponColor[1];
			Config::TeammateColors::EnergyWeaponColorB = Features::Colors::Teammate::EnergyWeaponColor[2];
			Config::TeammateColors::EnergyWeaponColorA = Features::Colors::Teammate::EnergyWeaponColor[3];
			Config::TeammateColors::ShotgunWeaponColorR = Features::Colors::Teammate::ShotgunWeaponColor[0];
			Config::TeammateColors::ShotgunWeaponColorG = Features::Colors::Teammate::ShotgunWeaponColor[1];
			Config::TeammateColors::ShotgunWeaponColorB = Features::Colors::Teammate::ShotgunWeaponColor[2];
			Config::TeammateColors::ShotgunWeaponColorA = Features::Colors::Teammate::ShotgunWeaponColor[3];
			Config::TeammateColors::SniperWeaponColorR = Features::Colors::Teammate::SniperWeaponColor[0];
			Config::TeammateColors::SniperWeaponColorG = Features::Colors::Teammate::SniperWeaponColor[1];
			Config::TeammateColors::SniperWeaponColorB = Features::Colors::Teammate::SniperWeaponColor[2];
			Config::TeammateColors::SniperWeaponColorA = Features::Colors::Teammate::SniperWeaponColor[3];
			Config::TeammateColors::LegendaryWeaponColorR = Features::Colors::Teammate::LegendaryWeaponColor[0];
			Config::TeammateColors::LegendaryWeaponColorG = Features::Colors::Teammate::LegendaryWeaponColor[1];
			Config::TeammateColors::LegendaryWeaponColorB = Features::Colors::Teammate::LegendaryWeaponColor[2];
			Config::TeammateColors::LegendaryWeaponColorA = Features::Colors::Teammate::LegendaryWeaponColor[3];
			Config::TeammateColors::MeleeWeaponColorR = Features::Colors::Teammate::MeleeWeaponColor[0];
			Config::TeammateColors::MeleeWeaponColorG = Features::Colors::Teammate::MeleeWeaponColor[1];
			Config::TeammateColors::MeleeWeaponColorB = Features::Colors::Teammate::MeleeWeaponColor[2];
			Config::TeammateColors::MeleeWeaponColorA = Features::Colors::Teammate::MeleeWeaponColor[3];
			Config::TeammateColors::ThrowableWeaponColorR = Features::Colors::Teammate::ThrowableWeaponColor[0];
			Config::TeammateColors::ThrowableWeaponColorG = Features::Colors::Teammate::ThrowableWeaponColor[1];
			Config::TeammateColors::ThrowableWeaponColorB = Features::Colors::Teammate::ThrowableWeaponColor[2];
			Config::TeammateColors::ThrowableWeaponColorA = Features::Colors::Teammate::ThrowableWeaponColor[3];

			Config::Colors::SpectatorWarningColorR = Features::Colors::SpectatorWarningColor[0];
			Config::Colors::SpectatorWarningColorG = Features::Colors::SpectatorWarningColor[1];
			Config::Colors::SpectatorWarningColorB = Features::Colors::SpectatorWarningColor[2];
			Config::Colors::SpectatorWarningColorA = Features::Colors::SpectatorWarningColor[3];
			Config::Colors::VisibleWarningColorR = Features::Colors::VisibleWarningColor[0];;
			Config::Colors::VisibleWarningColorG = Features::Colors::VisibleWarningColor[1];
			Config::Colors::VisibleWarningColorB = Features::Colors::VisibleWarningColor[2];
			Config::Colors::VisibleWarningColorA = Features::Colors::VisibleWarningColor[3];

			return true;
		}
		catch (...) {
			return false;
		}
	}

	void UpdateSpectators() {
		std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		if (Now >= LastUpdateTime + std::chrono::milliseconds(500)) {
			int TempTotalSpectators = 0;
			std::vector<std::string> TempSpectators;

			for (auto p : *Players) {
				if (p->IsSpectating()) {
					TempTotalSpectators++;
					TempSpectators.push_back(p->GetPlayerName());
				}
			}

			Features::TotalSpectators = TempTotalSpectators;
			Spectators = TempSpectators;
			LastUpdateTime = Now;
		}
	}

	void RenderWatermark(ImDrawList* Canvas, LocalPlayer* Myself, Overlay OverlayWindow) {
		int ScreenWidth;
		int ScreenHeight;
		OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);

		if (Features::Watermark::Watermark) {
			if (Features::Watermark::WatermarkPosition == 0) { // Top Left
				ImGui::SetNextWindowPos(ImVec2(15.0f, 24.0f), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
			}
			ImGui::SetNextWindowBgAlpha(0.50f);
			ImGui::Begin("Watermark", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

			const ImGuiStyle& style = ImGui::GetStyle();

			if (Features::Watermark::Name) {
				ImGui::TextColored(ImVec4(Features::Watermark::NameColor[0], Features::Watermark::NameColor[1], Features::Watermark::NameColor[2], Features::Watermark::NameColor[3]), "zap-client ");
				ImGui::SameLine();
				ImGui::Text(" - ");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(Features::Watermark::NameColor[0], Features::Watermark::NameColor[1], Features::Watermark::NameColor[2], Features::Watermark::NameColor[3]), CheatVersion.c_str());

				if (Features::Watermark::Spectators || Features::Watermark::ProcessingSpeed || Features::Watermark::GameFPS) {
					ImGui::SameLine();
					ImGui::Text(" - ");
					ImGui::SameLine();
				}
			}

			if (Features::Watermark::Spectators) {
				UpdateSpectators();
				ImGui::Text("Spectators: ");
				ImGui::SameLine();
				ImGui::TextColored(Features::TotalSpectators > 0 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1), "%d", Features::TotalSpectators);

				if (Features::Watermark::ProcessingSpeed || Features::Watermark::GameFPS) {
					ImGui::SameLine();
					ImGui::Text(" - ");
					ImGui::SameLine();
				}
			}

			if (Features::Watermark::ProcessingSpeed) {
				if (const std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); now >= processingLastUpdate + std::chrono::milliseconds(750)) {
					const double averageProcessingTime = std::accumulate(processingTimes.begin(), processingTimes.end(), 0.0) / processingTimes.size();
					processingTime = averageProcessingTime;
					processingLastUpdate = now;
				}

				if (processingTimes.size() >= 10)
					processingTimes.erase(processingTimes.begin());

				processingTimes.push_back(OverlayWindow.ProcessingTime);

				const ImVec4 ProcessingTimeColor = processingTime > 20 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1);
				ImGui::Text("Performance: ");
				ImGui::SameLine();
				ImGui::TextColored(ProcessingTimeColor, "%.2fms", processingTime);

				if (Features::Watermark::GameFPS) {
					ImGui::SameLine();
					ImGui::Text(" - ");
					ImGui::SameLine();
				}
			}

			if (Features::Watermark::GameFPS) {
				int FrameNumber = 0;
				FrameNumber = Memory::Read<int>(OFF_REGION + OFF_GLOBAL_VARS + 0x0008);

				if (const std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); now >= FpsUpdate + std::chrono::milliseconds(300)) {
					const int FramesSince = FrameNumber - FpsLastFrame;
					const auto Duration = now - FpsUpdate;
					Fps = FramesSince * 1000 / Duration.count();

					FpsLastFrame = FrameNumber;
					FpsUpdate = now;
				}

				const ImVec4 FpsColor = Fps < 60 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1);
				ImGui::Text("FPS: ");
				ImGui::SameLine();
				ImGui::TextColored(FpsColor, "%i", Fps);
			}

			ImGui::End();
		}
	}

	void RenderKeybinds(ImDrawList* Canvas, Legitbot* Aimbot, Ragebot* Rage, Triggerbot* Trigger, Misc* Misc, Overlay OverlayWindow) {
		int ScreenWidth, ScreenHeight;
		OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);

		if (!Features::Settings::ShowKeybinds) 
			return;

		ImVec4 HeldColor = ImVec4(Features::Settings::KeybindColor[0], Features::Settings::KeybindColor[1], Features::Settings::KeybindColor[2], Features::Settings::KeybindColor[3]);

		ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y - 200), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
		ImGui::SetNextWindowBgAlpha(0.3f);
		ImGui::Begin("Keybinds", nullptr, ImGuiWindowFlags_AlwaysAutoResize |
				ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoScrollbar);
			
		if (!Map->IsPlayable)
			return;
		if (!Myself->IsValid())
			return;
		if (Myself->IsDead)
			return;
		if (Features::Aimbot::AimbotEnabled && Features::Aimbot::AimList.find(Myself->WeaponIndex) != Features::Aimbot::AimList.end()) {
			ImGui::Text("Aimbot: ");
			if ((Features::Aimbot::SpectatorCheck || !Features::Aimbot::SpectatorCheck) && Features::TotalSpectators == 0) {
				if (Features::Aimbot::BindMethod == 0) {
					if (Features::Aimbot::OnFire && Myself->IsInAttack) {
						ImGui::SameLine();
						ImGui::TextColored(HeldColor,"Firing ");
					}
					if (Features::Aimbot::OnADS && Myself->IsZooming) {
						ImGui::SameLine();
						ImGui::TextColored(HeldColor, "Zooming");
					}
				} else if (Features::Aimbot::BindMethod == 1) {
					if (InputManager::isKeyDownOrPress(Features::AimbotBinds::AimBind)) {
						ImGui::SameLine();
						ImGui::TextColored(HeldColor, "Key Bind ");
					} else if (InputManager::isKeyDownOrPress(Features::AimbotBinds::ExtraBind)) {
						ImGui::SameLine();
						ImGui::TextColored(HeldColor, "Extra Bind");
					}
				}
			} else if (Features::Aimbot::SpectatorCheck && Features::TotalSpectators >= 1) {
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "DISABLED - SPECTATORS");
			}
		}

		if (Features::Ragebot::RageAimbot && Features::Ragebot::RageList.find(Myself->WeaponIndex) != Features::Ragebot::RageList.end()) {
			ImGui::Text("Ragebot: ");
			if (Features::Ragebot::BindMethod == 0) {
				if (Features::Ragebot::OnFire && Myself->IsInAttack) {
					ImGui::SameLine();
					ImGui::TextColored(HeldColor, "Firing");
				}
				if (Features::Ragebot::OnADS && Myself->IsZooming) {
					ImGui::SameLine();
					ImGui::TextColored(HeldColor, "Zooming");
				}
			} else if (Features::Ragebot::BindMethod == 1) {
				if (InputManager::isKeyDownOrPress(Features::Ragebot::AimBind)) {
					ImGui::SameLine();
					ImGui::TextColored(HeldColor, "Key Bind ");
				} else if (InputManager::isKeyDownOrPress(Features::Ragebot::ExtraBind)) {
					ImGui::SameLine();
					ImGui::TextColored(HeldColor, "Extra Bind");
				}
			}
		}

		if (Features::Triggerbot::Enabled && Trigger->WeaponList.find(Myself->WeaponIndex) != Trigger->WeaponList.end()) {
			ImGui::Text("Triggerbot: ");
			if (Features::Triggerbot::BindMethod == 0) {
				if (Features::Triggerbot::HipfireShotguns && (Myself->WeaponIndex == WeaponIDs::MOZAMBIQUE or Myself->WeaponIndex == WeaponIDs::EVA8 or Myself->WeaponIndex == WeaponIDs::PEACEKEEPER or Myself->WeaponIndex == WeaponIDs::MASTIFF)) {
					ImGui::SameLine();
					ImGui::TextColored(HeldColor, "Shotgun Held ");
				}
				if (Features::Triggerbot::OnADS && Myself->IsZooming) {
					ImGui::SameLine();
					ImGui::TextColored(HeldColor, "Zooming");
				}
			} else if (Features::Triggerbot::BindMethod == 1) {
				if (InputManager::isKeyDownOrPress(Features::Triggerbot::TriggerBind)) {
					ImGui::SameLine();
					ImGui::TextColored(HeldColor, "Key Bind");
				}
			}
		}

		if (Features::Misc::BHop) {
			ImGui::Text("BHop: ");
			if (InputManager::isKeyDownOrPress(Features::Misc::BHopBind)) {
				ImGui::SameLine();
				ImGui::TextColored(HeldColor, "Key Bind");
			}
		}
		if (Features::Misc::WallJump ) {
			ImGui::Text("Wall Jump: ");
			if (InputManager::isKeyDownOrPress(Features::Misc::WallJumpBind)) {
				ImGui::SameLine();
				ImGui::TextColored(HeldColor, "Key Bind");
			}
		}
		if (Features::Misc::QuickTurn) {
			ImGui::Text("QuickTurn: ");
			if (InputManager::isKeyDownOrPress(Features::Misc::QuickTurnBind)) {
				ImGui::SameLine();
				ImGui::TextColored(HeldColor, "Key Bind");
			}
		}
		if (Features::Misc::RapidFire && Misc->RapidFireList.find(Myself->WeaponIndex) == Misc->RapidFireList.end()) {
			ImGui::Text("RapidFire: ");
			if (InputManager::isKeyDownOrPress(Features::Misc::RapidFireBind)) {
				ImGui::SameLine();
				ImGui::TextColored(HeldColor, "Key Bind");
			}
		}

		ImGui::End();

	}

	void RenderDrawings(ImDrawList* Canvas, Legitbot* Aimbot, LocalPlayer* Myself, Overlay OverlayWindow) {
		int ScreenWidth, ScreenHeight;
		OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);

		if (!Map->IsPlayable)
			return;

		// Spectator List
		if (Features::Sense::ShowSpectators) {
			ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
			ImGui::SetNextWindowBgAlpha(0.3f);
			ImGui::Begin("Spectators", nullptr, ImGuiWindowFlags_AlwaysAutoResize |
				ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoScrollbar);
			UpdateSpectators(); // Updates Spectator List
			ImGui::Text("Spectators: ");
			ImGui::SameLine(); ImGui::TextColored(Features::TotalSpectators > 0 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1), "%d", Features::TotalSpectators);
			if (static_cast<int>(Spectators.size()) > 0) {
				ImGui::Separator();
				for (int i = 0; i < static_cast<int>(Spectators.size()); i++) {
					ImGui::TextColored(ImVec4(1, 0.343, 0.475, 1), "> %s", Spectators.at(i).c_str());
				}
			}
			ImGui::End();
		}

		// Legitbot Spectator Check Notifier
		if (Features::Aimbot::SpectatorCheck && Features::Aimbot::SpectatorNotifier && Features::TotalSpectators >= 1) {
			int x = (int) (ScreenWidth * 0.5f);
			int y = (int) (ScreenHeight * 0.5f);
			Renderer::DrawText(Canvas, Vector2D(x, y - 200), "YOU ARE BEING WATCHED - AIMBOT DISABLED", ImColor(255, 0, 0), true, true, false);
		}

		// Draw Crosshair
		if (Features::Sense::DrawCrosshair) {
			int x = (int) (ScreenWidth * 0.5f);
			int y = (int) (ScreenHeight * 0.5f);
			Renderer::DrawLine(Canvas, Vector2D(x - Features::Sense::CrosshairSize, y), Vector2D(x + Features::Sense::CrosshairSize, y), Features::Sense::CrosshairThickness, ImColor(Features::Colors::CrosshairColor[0], Features::Colors::CrosshairColor[1], Features::Colors::CrosshairColor[2], Features::Colors::CrosshairColor[3])); // Left - right
			Renderer::DrawLine(Canvas, Vector2D(x, y - Features::Sense::CrosshairSize), Vector2D(x, y + Features::Sense::CrosshairSize), Features::Sense::CrosshairThickness, ImColor(Features::Colors::CrosshairColor[0], Features::Colors::CrosshairColor[1], Features::Colors::CrosshairColor[2], Features::Colors::CrosshairColor[3])); // Top - bottom
		}

		// Draw FOV Circle (Legitbot)
		if (Features::Sense::DrawFOVCircle && Features::Aimbot::AimbotEnabled && (Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 2) && Myself->IsCombatReady()) {
			float FOV = (std::min)(Features::Aimbot::FOV, Features::Aimbot::FOV * (Aimbot->GetFOVScale() * Features::Aimbot::ZoomScale));
			float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(Features::Sense::GameFOV) / 2) * ScreenWidth;
			Renderer::DrawCircle(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(Features::Colors::FOVColor[0], Features::Colors::FOVColor[1], Features::Colors::FOVColor[2], Features::Colors::FOVColor[3]), Features::Sense::FOVThickness);
		}

		// Draw Filled FOV Circle (Legitbot)
		if (Features::Sense::DrawFilledFOVCircle && Features::Aimbot::AimbotEnabled && (Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 2) && Myself->IsCombatReady()) {
			float FOV = (std::min)(Features::Aimbot::FOV, Features::Aimbot::FOV * (Aimbot->GetFOVScale() * Features::Aimbot::ZoomScale));
			float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(Features::Sense::GameFOV) / 2) * ScreenWidth;
			Renderer::DrawCircleFilled(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(Features::Colors::FilledFOVColor[0], Features::Colors::FilledFOVColor[1], Features::Colors::FilledFOVColor[2], Features::Colors::FilledFOVColor[3]));
		}

		// Draw FOV Circle (Ragebot)
		if (Features::Sense::DrawFOVCircle && Features::Ragebot::RageAimbot && Myself->IsCombatReady()) {
			float FOV = (std::min)(Features::Ragebot::FOV, Features::Ragebot::FOV * (Aimbot->GetFOVScale() * Features::Ragebot::ZoomScale));
			float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(Features::Sense::GameFOV) / 2) * ScreenWidth;
			Renderer::DrawCircle(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(Features::Colors::FOVColor[0], Features::Colors::FOVColor[1], Features::Colors::FOVColor[2], Features::Colors::FOVColor[3]), Features::Sense::FOVThickness);
		}

		// Draw Filled FOV Circle (Ragebot)
		if (Features::Sense::DrawFilledFOVCircle && Features::Ragebot::RageAimbot && Myself->IsCombatReady()) {
			float FOV = (std::min)(Features::Ragebot::FOV, Features::Ragebot::FOV * (Aimbot->GetFOVScale() * Features::Ragebot::ZoomScale));
			float Radius = tanf(DEG2RAD(FOV) / 2) / tanf(DEG2RAD(Features::Sense::GameFOV) / 2) * ScreenWidth;
			Renderer::DrawCircleFilled(Canvas, Vector2D(ScreenWidth / 2, ScreenHeight / 2), Radius, 40, ImColor(Features::Colors::FilledFOVColor[0], Features::Colors::FilledFOVColor[1], Features::Colors::FilledFOVColor[2], Features::Colors::FilledFOVColor[3]));
		}

		if (!Features::Settings::ESPEnabled)
			return;

		// Draw Warning Text - Spectators
		if (Features::Sense::DrawSpectatorWarning && Features::TotalSpectators >= 1) {
			std::stringstream WarningTextStart, Space1, Amount, Space2;
			WarningTextStart << "SPECTATOR WARNING";
			Space1 << " [";
			Amount << Features::TotalSpectators;
			Space2 << "]";
			std::string combined = WarningTextStart.str() + Space1.str() + Amount.str() + Space2.str();
			const char* CombinedText = combined.c_str();

			Vector2D TextPos = Vector2D(Features::Sense::WarningTextX, Features::Sense::WarningTextY - 12);
			Renderer::DrawText(Canvas, TextPos, CombinedText, ImColor(Features::Colors::SpectatorWarningColor[0], Features::Colors::SpectatorWarningColor[1], Features::Colors::SpectatorWarningColor[2], Features::Colors::SpectatorWarningColor[3]), Features::Sense::WarningTextOutline ? true : false, true, false);
		}

		// Draw Warning Text - Visible
		if (Features::Sense::DrawVisibleWarning && VisWarning) {
			const char* Text = "VISIBLE WARNING!";
			Vector2D TextPos = Vector2D(Features::Sense::WarningTextX, Features::Sense::WarningTextY);
			Renderer::DrawText(Canvas, TextPos, Text, ImColor(Features::Colors::VisibleWarningColor[0], Features::Colors::VisibleWarningColor[1], Features::Colors::VisibleWarningColor[2], Features::Colors::VisibleWarningColor[3]), Features::Sense::WarningTextOutline ? true : false, true, false);
		}

		for (Player* p : *Players) {
			if (!Features::Sense::Enemy::DrawEnemy && p->IsHostile)
				return;
			if (p->IsLocal) // Make sure not to draw the local player
				continue;
			if (!p->IsValid()) // Check that the player is valid - not dead && is player
				continue;
			if (p->DistanceToLocalPlayer > Conversion::ToGameUnits(Features::Sense::ESPMaxDistance)) // Distance Check
				continue;
			if (Features::Sense::VisibilityCheck && !p->IsVisible) // Visibility Check - Only Draw If Visible
				continue;
			if (!Features::Sense::Teammate::DrawTeam && p->IsAlly) // Team Check
				continue;
			if (Features::Sense::KnockedCheck && p->IsKnocked) // Knocked Check
				continue;

			Vector3D LocalOrigin3D = p->LocalOrigin; // Local Origin - 3D
			Vector3D Head3D = p->GetBonePosition(HitboxType::Head); // Head - 3D
			Vector2D LocalOriginW2S, HeadPositionW2S;
			bool bLocalOriginW2SValid = GameCamera->WorldToScreen(LocalOrigin3D, LocalOriginW2S); // WorldToScreen - LocalOrigin
			bool bHeadPositionW2SValid = GameCamera->WorldToScreen(Head3D, HeadPositionW2S); // WorldToScreen - Head

			// Function To Get Required Colors Based On Player State && Cheat Configuration
			auto GetColor = [p](const float* Teammate_VisColor, const float* Teammate_InvisColor, const float* Teammate_KnockedColor, const float* Enemy_VisColor, const float* Enemy_InvisColor, const float* Enemy_KnockedColor) {
				const float* Teammate_Color = p->IsKnocked ? Teammate_KnockedColor : p->IsVisible ? Teammate_VisColor : Teammate_InvisColor;
				const float* Enemy_Color = p->IsKnocked ? Enemy_KnockedColor : p->IsVisible ? Enemy_VisColor : Enemy_InvisColor;
				const float* ChosenColor = p->IsAlly ? Teammate_Color : Enemy_Color;
				return ImVec4(ChosenColor[0], ChosenColor[1], ChosenColor[2], ChosenColor[3]);
			};

			// Declaring And Getting Colors
			ImVec4 BoxColor = GetColor(Features::Colors::Teammate::VisibleBoxColor, Features::Colors::Teammate::InvisibleBoxColor, Features::Colors::Teammate::KnockedBoxColor, Features::Colors::Enemy::VisibleBoxColor, Features::Colors::Enemy::InvisibleBoxColor, Features::Colors::Enemy::KnockedBoxColor);
			ImVec4 FilledBoxColor = GetColor(Features::Colors::Teammate::VisibleFilledBoxColor, Features::Colors::Teammate::InvisibleFilledBoxColor, Features::Colors::Teammate::KnockedFilledBoxColor, Features::Colors::Enemy::VisibleFilledBoxColor, Features::Colors::Enemy::InvisibleFilledBoxColor, Features::Colors::Enemy::KnockedFilledBoxColor);
			ImVec4 TracerColor = GetColor(Features::Colors::Teammate::VisibleTracerColor, Features::Colors::Teammate::InvisibleTracerColor, Features::Colors::Teammate::KnockedTracerColor, Features::Colors::Enemy::VisibleTracerColor, Features::Colors::Enemy::InvisibleTracerColor, Features::Colors::Enemy::KnockedTracerColor);
			ImVec4 SkeletonColor = GetColor(Features::Colors::Teammate::VisibleSkeletonColor, Features::Colors::Teammate::InvisibleSkeletonColor, Features::Colors::Teammate::KnockedSkeletonColor, Features::Colors::Enemy::VisibleSkeletonColor, Features::Colors::Enemy::InvisibleSkeletonColor, Features::Colors::Enemy::KnockedSkeletonColor);
			ImVec4 HeadCircleColor = GetColor(Features::Colors::Teammate::VisibleHeadCircleColor, Features::Colors::Teammate::InvisibleHeadCircleColor, Features::Colors::Teammate::KnockedHeadCircleColor, Features::Colors::Enemy::VisibleHeadCircleColor, Features::Colors::Enemy::InvisibleHeadCircleColor, Features::Colors::Enemy::KnockedHeadCircleColor);
			ImVec4 NameColor = GetColor(Features::Colors::Teammate::VisibleNameColor, Features::Colors::Teammate::InvisibleNameColor, Features::Colors::Teammate::KnockedNameColor, Features::Colors::Enemy::VisibleNameColor, Features::Colors::Enemy::InvisibleNameColor, Features::Colors::Enemy::KnockedNameColor);
			ImVec4 DistanceColor = GetColor(Features::Colors::Teammate::VisibleDistanceColor, Features::Colors::Teammate::InvisibleDistanceColor, Features::Colors::Teammate::KnockedDistanceColor, Features::Colors::Enemy::VisibleDistanceColor, Features::Colors::Enemy::InvisibleDistanceColor, Features::Colors::Enemy::KnockedDistanceColor);
			ImVec4 LegendColor = GetColor(Features::Colors::Teammate::VisibleLegendColor, Features::Colors::Teammate::InvisibleLegendColor, Features::Colors::Teammate::KnockedLegendColor, Features::Colors::Enemy::VisibleLegendColor, Features::Colors::Enemy::InvisibleLegendColor, Features::Colors::Enemy::KnockedLegendColor);
			ImVec4 WeaponColor = GetColor(Features::Colors::Teammate::VisibleWeaponColor, Features::Colors::Teammate::InvisibleWeaponColor, Features::Colors::Teammate::KnockedWeaponColor, Features::Colors::Enemy::VisibleWeaponColor, Features::Colors::Enemy::InvisibleWeaponColor, Features::Colors::Enemy::KnockedWeaponColor);

			// Function To Get Required Text Positions Based Cheat Configuration
			auto CalcTextPosition = [](const int PositionIndex, const Vector2D& Head, const Vector2D& LocalOrigin) {
				switch (PositionIndex) {
					case 0: // Top 1
						return Head.Add(Vector2D(0, ((Head.y - LocalOrigin.y) * 0.2) - 14));
					case 1: // Top 2
						return Head.Add(Vector2D(0, ((Head.y - LocalOrigin.y) * 0.2) - 28));
					case 2: // Bottom 1
						return LocalOrigin;
					case 3: // Bottom 2
						return LocalOrigin.Add(Vector2D(0, 10));
					case 4: // Bottom 3
						return LocalOrigin.Add(Vector2D(0, 20));
					default:
						return Vector2D();
				}
			};

			// Declaring And Getting Position
			Vector2D NamePosition = CalcTextPosition(Features::Sense::Positions::NamePosition, HeadPositionW2S, LocalOriginW2S);
			Vector2D DistancePosition = CalcTextPosition(Features::Sense::Positions::DistancePosition, HeadPositionW2S, LocalOriginW2S);
			Vector2D LegendPosition = CalcTextPosition(Features::Sense::Positions::LegendPosition, HeadPositionW2S, LocalOriginW2S);
			Vector2D WeaponPosition = CalcTextPosition(Features::Sense::Positions::WeaponPosition, HeadPositionW2S, LocalOriginW2S);
			Vector2D StatusPosition = CalcTextPosition(Features::Sense::Positions::StatusPosition, HeadPositionW2S, LocalOriginW2S);

			// Variables Based On Cheat Configuration && Player Relation To The LocalPlayer
			bool DrawBoxes = p->IsAlly ? Features::Sense::Teammate::DrawBoxes : Features::Sense::Enemy::DrawBoxes;
			bool DrawTracers = p->IsAlly ? Features::Sense::Teammate::DrawTracers : Features::Sense::Enemy::DrawTracers;
			bool DrawSkeleton = p->IsAlly ? Features::Sense::Teammate::DrawSkeleton : Features::Sense::Enemy::DrawSkeleton;
			bool DrawHeadCircle = p->IsAlly ? Features::Sense::Teammate::DrawHeadCircle : Features::Sense::Enemy::DrawHeadCircle;
			bool DrawBars = p->IsAlly ? Features::Sense::Teammate::DrawBars : Features::Sense::Enemy::DrawBars;
			bool DrawNames = p->IsAlly ? Features::Sense::Teammate::DrawNames : Features::Sense::Enemy::DrawNames;
			bool DrawDistance = p->IsAlly ? Features::Sense::Teammate::DrawDistance : Features::Sense::Enemy::DrawDistance;
			bool DrawLegend = p->IsAlly ? Features::Sense::Teammate::DrawLegend : Features::Sense::Enemy::DrawLegend;
			bool DrawWeapon = p->IsAlly ? Features::Sense::Teammate::DrawWeapon : Features::Sense::Enemy::DrawWeapon;
			bool DrawStatus = p->IsAlly ? Features::Sense::Teammate::DrawStatus : Features::Sense::Enemy::DrawStatus;
			bool DrawSeer = p->IsAlly ? Features::Sense::Teammate::DrawSeer : Features::Sense::Enemy::DrawSeer;
			// Visibile Warning
			VisWarning = p->IsVisible;

			// ESP Features
			if (DrawTracers) { // Tracers (Snaplines) - Draws A Line To Players From A Screen Point
				Vector2D ScreenPosition;
				int TracerBone = p->IsAlly ? Features::Sense::Teammate::TracerBone : Features::Sense::Enemy::TracerBone;
				int TracerPosition = p->IsAlly ? Features::Sense::Teammate::TracerPosition : Features::Sense::Enemy::TracerPosition;
				float TracerThickness = p->IsAlly ? Features::Sense::Teammate::TracerThickness : Features::Sense::Enemy::TracerThickness;
				GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, TracerBone == 0 ? 66 : 0)), ScreenPosition);

				Vector2D Position = Vector2D(ScreenWidth * 0.5f, TracerPosition == 0 ? 0 : TracerPosition == 1 ? ScreenHeight / 2 : ScreenHeight);
				if (!ScreenPosition.IsZeroVector())
					Renderer::DrawLine(Canvas, Position, ScreenPosition, TracerThickness, ImColor(TracerColor));
			}

			if (!bLocalOriginW2SValid) // Tracers Will Be Drawn If Player Is Off Screen, Anything Else Will Not Be Drawn
				continue;
			if (!bHeadPositionW2SValid) // Same Thing Applies Here
				continue;
			
			if (DrawBoxes) { // Boxes - Draws A Box (Rect) Around A Player
				int BoxType = p->IsAlly ? Features::Sense::Teammate::BoxType : Features::Sense::Enemy::BoxType;
				int BoxStyle = p->IsAlly ? Features::Sense::Teammate::BoxStyle : Features::Sense::Enemy::BoxStyle;
				bool BoxOutline = p->IsAlly ? Features::Sense::Teammate::BoxOutline : Features::Sense::Enemy::BoxOutline;
				float BoxThickness = p->IsAlly ? Features::Sense::Teammate::BoxThickness : Features::Sense::Enemy::BoxThickness;
				Renderer::Draw2DBox(Canvas, BoxType, BoxStyle, BoxOutline, LocalOriginW2S, HeadPositionW2S, ImColor(BoxColor), ImColor(FilledBoxColor), BoxThickness);
			}

			if (DrawSkeleton) { // Skeleton - Draw The Players Skeleton Using Lines
				int SkeletonDetail = p->IsAlly ? Features::Sense::Teammate::SkeletonDetail : Features::Sense::Enemy::SkeletonDetail;
				if (SkeletonDetail == 0) { // Detailed
					Vector2D Neck, UpperChest, LowerChest, Stomach, Leftshoulder, Leftelbow, LeftHand, Rightshoulder, RightelbowBone, RightHand, LeftThighs, Leftknees, Leftleg, RightThighs, Rightknees, Rightleg;
					// Head bone is HeadPositionW2S
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Neck), Neck);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::UpperChest), UpperChest);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LowerChest), LowerChest);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Stomach), Stomach);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftshoulder), Leftshoulder);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftelbow), Leftelbow);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Lefthand), LeftHand);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightshoulder), Rightshoulder);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightelbowBone), RightelbowBone);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Righthand), RightHand);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftThighs), LeftThighs);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftknees), Leftknees);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftleg), Leftleg);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightThighs), RightThighs);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightknees), Rightknees);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightleg), Rightleg);

					bool Outline = p->IsAlly ? Features::Sense::Teammate::SkeletonOutline : Features::Sense::Enemy::SkeletonOutline;
					int Thickness = p->IsAlly ? Features::Sense::Teammate::SkeletonThickness : Features::Sense::Enemy::SkeletonThickness;
					if (Outline) {
						Renderer::DrawLine(Canvas, HeadPositionW2S, Neck, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Neck, UpperChest, Thickness + 1, ImColor(0, 0, 0));

						Renderer::DrawLine(Canvas, UpperChest, LowerChest, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, LowerChest, Stomach, Thickness + 1, ImColor(0, 0, 0));

						Renderer::DrawLine(Canvas, Neck, Leftshoulder, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Leftelbow, LeftHand, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, RightelbowBone, RightHand, Thickness + 1, ImColor(0, 0, 0));

						Renderer::DrawLine(Canvas, Stomach, LeftThighs, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, Thickness + 1, ImColor(0, 0, 0));
					}
					Renderer::DrawLine(Canvas, HeadPositionW2S, Neck, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Neck, UpperChest, Thickness, ImColor(SkeletonColor));

					Renderer::DrawLine(Canvas, UpperChest, LowerChest, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, LowerChest, Stomach, Thickness, ImColor(SkeletonColor));

					Renderer::DrawLine(Canvas, Neck, Leftshoulder, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Leftelbow, LeftHand, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Neck, Rightshoulder, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, RightelbowBone, RightHand, Thickness, ImColor(SkeletonColor));

					Renderer::DrawLine(Canvas, Stomach, LeftThighs, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, LeftThighs, Leftknees, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Leftknees, Leftleg, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Stomach, RightThighs, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, RightThighs, Rightknees, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Rightknees, Rightleg, Thickness, ImColor(SkeletonColor));
				}
				else if (SkeletonDetail == 1) { // Simple
					Vector2D Neck, Stomach, Leftshoulder, Leftelbow, Lefthand, Rightshoulder, RightelbowBone, Righthand, LeftThighs, Leftknees, Leftleg, RightThighs, Rightknees, Rightleg;
					// Head bone is HeadPositionW2S
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Neck), Neck);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Stomach), Stomach);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftshoulder), Leftshoulder);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftelbow), Leftelbow);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Lefthand), Lefthand);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightshoulder), Rightshoulder);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightelbowBone), RightelbowBone);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Righthand), Righthand);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftThighs), LeftThighs);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftknees), Leftknees);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftleg), Leftleg);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightThighs), RightThighs);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightknees), Rightknees);
					GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightleg), Rightleg);

					bool Outline = p->IsAlly ? Features::Sense::Teammate::SkeletonOutline : Features::Sense::Enemy::SkeletonOutline;
					int Thickness = p->IsAlly ? Features::Sense::Teammate::SkeletonThickness : Features::Sense::Enemy::SkeletonThickness;
					if (Outline) {
						Renderer::DrawLine(Canvas, Neck, Stomach, Thickness + 1, ImColor(0, 0, 0));

						Renderer::DrawLine(Canvas, Neck, Leftshoulder, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Leftelbow, Lefthand, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Neck, Rightshoulder, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, RightelbowBone, Righthand, Thickness + 1, ImColor(0, 0, 0));

						Renderer::DrawLine(Canvas, Stomach, LeftThighs, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, LeftThighs, Leftknees, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Leftknees, Leftleg, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Stomach, RightThighs, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, RightThighs, Rightknees, Thickness + 1, ImColor(0, 0, 0));
						Renderer::DrawLine(Canvas, Rightknees, Rightleg, Thickness + 1, ImColor(0, 0, 0));

					}
					Renderer::DrawLine(Canvas, Neck, Stomach, Thickness, ImColor(SkeletonColor));

					Renderer::DrawLine(Canvas, Neck, Leftshoulder, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Leftelbow, Lefthand, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Neck, Rightshoulder, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, RightelbowBone, Righthand, Thickness, ImColor(SkeletonColor));

					Renderer::DrawLine(Canvas, Stomach, LeftThighs, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, LeftThighs, Leftknees, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Leftknees, Leftleg, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Stomach, RightThighs, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, RightThighs, Rightknees, Thickness, ImColor(SkeletonColor));
					Renderer::DrawLine(Canvas, Rightknees, Rightleg, Thickness, ImColor(SkeletonColor));
				}
			}

			if (DrawHeadCircle) { // Head Circle - Draws A Circle Around The Players Head
				Vector3D HeadPoint = Head3D;
				HeadPoint.z += 4.0f;
				Vector2D HeadPointW2S;
				GameCamera->WorldToScreen(HeadPoint, HeadPointW2S);
				bool Outline = p->IsAlly ? Features::Sense::Teammate::HeadCircleOutline : Features::Sense::Enemy::HeadCircleOutline;
				int Thickness = p->IsAlly ? Features::Sense::Teammate::HeadCircleThickness : Features::Sense::Enemy::HeadCircleThickness;
				if (Outline)
					Renderer::DrawCircle(Canvas, HeadPointW2S, 3650 / p->DistanceToLocalPlayer, 255, ImColor(0, 0, 0), Thickness + 1);
				Renderer::DrawCircle(Canvas, HeadPointW2S, 3650 / p->DistanceToLocalPlayer, 255, ImColor(HeadCircleColor), Thickness);
			}

			if (DrawBars && !DrawSeer) {
				int health = p->Health;
				int maxHealth = p->MaxHealth;
				int shield = p->Shield;
				int maxShield = p->MaxShield;
				int BarMode = p->IsAlly ? Features::Sense::Teammate::BarMode : Features::Sense::Enemy::BarMode;
				int BarStyle = p->IsAlly ? Features::Sense::Teammate::BarStyle : Features::Sense::Enemy::BarStyle;
				int BarColorMode = p->IsAlly ? Features::Sense::Teammate::BarColorMode : Features::Sense::Enemy::BarColorMode;
				float BarThickness = p->IsAlly ? Features::Sense::Teammate::BarThickness : Features::Sense::Enemy::BarThickness;
				float BarThickness2 = p->IsAlly ? Features::Sense::Teammate::BarThickness2 : Features::Sense::Enemy::BarThickness2;
				float BarWidth = p->IsAlly ? Features::Sense::Teammate::BarWidth : Features::Sense::Enemy::BarWidth;
				float BarHeight = p->IsAlly ? Features::Sense::Teammate::BarHeight : Features::Sense::Enemy::BarHeight;
				// Renderer::Draw2DBar(Canvas, BarMode, BarStyle, BarColorMode, LocalOriginW2S, HeadPositionW2S, health, maxHealth, shield, maxShield, BarThickness, BarThickness2, BarWidth, BarHeight);
				// testing
				Renderer::Draw2DBarTest(Canvas, Features::Sense::Enemy::HealthBar, Features::Sense::Enemy::ShieldBar, BarStyle, BarColorMode, LocalOriginW2S, HeadPositionW2S, health, maxHealth, shield, maxShield, BarThickness, BarThickness2, BarWidth, BarHeight);
			}

			if (DrawDistance && !DrawNames) {
				std::string Distance = std::to_string(static_cast<int>(Conversion::ToMeters(p->DistanceToLocalPlayer)));
				std::string Buffer = "[" + Distance + " M]";

				if (!LocalOriginW2S.IsZeroVector())
					Renderer::DrawText(Canvas, DistancePosition, Buffer.c_str(), ImColor(DistanceColor), Features::Sense::TextOutline, true, false);
			}

			if (!DrawDistance && DrawNames)
				Renderer::DrawText(Canvas, NamePosition, p->GetPlayerName().c_str(), ImColor(NameColor), Features::Sense::TextOutline, true, false);

			if (DrawDistance && DrawNames) {
				std::stringstream TextStream;
				TextStream << p->GetPlayerName() << " [" << static_cast<int>(Conversion::ToMeters(p->DistanceToLocalPlayer)) << " M]";
				std::string Combined = TextStream.str();

				Renderer::DrawText(Canvas, NamePosition, Combined.c_str(), ImColor(NameColor), Features::Sense::TextOutline, true, false);
			}

			if (DrawLegend)
				Renderer::DrawText(Canvas, LegendPosition, p->getPlayerModelName().c_str(), ImColor(LegendColor), Features::Sense::TextOutline, true, false);

			if (DrawWeapon) {
				// Variables
				std::string WeaponHeldText;
				ImColor WeaponHeldColor;

				// GetWeaponName and GetWeaponColor
				WeaponHeldText = p->GetWeaponHeldName();
				WeaponHeldColor = p->GetWeaponHeldColor();

				if (Features::Colors::WeaponColorMode == 1) // Changes color to ammo type
					Renderer::DrawText(Canvas, WeaponPosition, WeaponHeldText.c_str(), WeaponHeldColor, Features::Sense::TextOutline, true, false);
				if (Features::Colors::WeaponColorMode == 0) // Single Color
					Renderer::DrawText(Canvas, WeaponPosition, WeaponHeldText.c_str(), WeaponColor, Features::Sense::TextOutline, true, false);
			}

			if (DrawStatus) {
				std::stringstream healthValue, shieldValue, maxHealthValue, maxShieldValue;
				healthValue << p->Health;
				shieldValue << p->Shield;
				maxHealthValue << p->MaxHealth;
				maxShieldValue << p->MaxShield;
				std::string healthInt = healthValue.str() + " HP";
				std::string shieldInt = shieldValue.str() + " AP";
				const char* healthText = const_cast<char*>(healthInt.c_str());
				const char* shieldText = const_cast<char*>(shieldInt.c_str());
				std::string combinedHealth = healthValue.str() + " / " + maxHealthValue.str() + " HP";
				const char* combinedHealthText = combinedHealth.c_str();
				std::string combinedShield = shieldValue.str() + " / " + maxShieldValue.str() + " AP";
				const char* combinedShieldText = combinedShield.c_str();

				ImColor ShieldColor;
				switch (p->MaxShield) {
					case 75:
						ShieldColor = ImColor(39, 178, 255); // Blue
						break;
					case 100:
						ShieldColor = ImColor(206, 59, 255); // Purple
						break;
					case 125:
						ShieldColor = ImColor(219, 2, 2); // Red
						break;
					default:
						ShieldColor = ImColor(247, 247, 247); // White
						break;
				}

				bool ShowMaxStatusValues = p->IsAlly ? Features::Sense::Teammate::ShowMaxStatusValues : Features::Sense::Enemy::ShowMaxStatusValues;
				Renderer::DrawText(Canvas, StatusPosition, ShowMaxStatusValues ? combinedHealthText : healthText, ImColor(0, 255, 0), Features::Sense::TextOutline, true, false);
				Renderer::DrawText(Canvas, StatusPosition.Add(Vector2D(0, 0 + 10)), ShowMaxStatusValues ? combinedShieldText : shieldText, ShieldColor, Features::Sense::TextOutline, true, false);
			}

			// Seer
			if (DrawSeer && DrawBars && bHeadPositionW2SValid) {
				if (!HeadPositionW2S.IsZeroVector()) {
					Renderer::DrawSeer(Canvas, HeadPositionW2S.x, HeadPositionW2S.y - 20, p->Shield, p->MaxShield, p->Health);
				}
			}

			// Target Visuals
			bool TargetVisualsEnabled;
			if ((Features::Aimbot::SpectatorCheck || !Features::Aimbot::SpectatorCheck) && Features::TotalSpectators == 0) {
				if (Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 2) {
					if (Features::Sense::DrawTargetLine or Features::Sense::DrawTargetDot or Features::Sense::DrawTargetBox) {
						if (Features::Sense::TargetMode == 0) // Current Target
						{
							if (Aimbot->TargetSelected) {
								TargetVisualsEnabled = true;
							}
							else if (!Aimbot->TargetSelected) {
								TargetVisualsEnabled = false;
							}
						}
						if (Features::Sense::TargetMode == 1) // Best Target
						{
							bool TargetAvaliable = Aimbot->IsBestTarget();
							if (TargetAvaliable) {
								TargetVisualsEnabled = true;
							}
							else if (!TargetAvaliable) {
								TargetVisualsEnabled = false;
							}
						}
					}
				}
				else if (Features::Aimbot::AimbotMode == 1) {
					TargetVisualsEnabled = false;
				}

				// Target Line
				if (Features::Sense::DrawTargetLine && TargetVisualsEnabled) {
					ImVec4 TargetLineColor;
					if (Features::Sense::TargetMode == 1 && Aimbot->TargetSelected) {
						TargetLineColor = ImVec4(Features::Colors::TargetLineLockedColor[0], Features::Colors::TargetLineLockedColor[1], Features::Colors::TargetLineLockedColor[2], Features::Colors::TargetLineLockedColor[3]);
					}
					else {
						TargetLineColor = ImVec4(Features::Colors::TargetLineColor[0], Features::Colors::TargetLineColor[1], Features::Colors::TargetLineColor[2], Features::Colors::TargetLineColor[3]);
					}

					int x = (int) (ScreenWidth * 0.5f);
					Vector2D TargetPos;

					if (Features::Sense::TargetMode == 0) // Current Target
					{
						if (Features::Sense::TargetBoneMode == 0) // Depends on selected aimbot setting
						{
							Vector3D TargetBone;
							if (Features::Aimbot::ClosestHitbox) {
								TargetBone = Aimbot->CurrentTarget->GetBonePosition(static_cast<HitboxType>(Aimbot->GetBestBone(Aimbot->CurrentTarget)));
							}
							else if (!Features::Aimbot::ClosestHitbox) {
								TargetBone = Aimbot->CurrentTarget->GetBonePosition(Features::AimbotHitboxes::Hitbox);
							}

							GameCamera->WorldToScreen(TargetBone, TargetPos);
						}

						else if (Features::Sense::TargetBoneMode == 1) // Custom
						{
							Vector3D TargetBone;
							TargetBone = Aimbot->CurrentTarget->GetBonePosition(Features::Sense::TargetHitbox);

							GameCamera->WorldToScreen(TargetBone, TargetPos);
						}
					}

					if (Features::Sense::TargetMode == 1) // Best Target
					{
						if (Features::Sense::TargetBoneMode == 0) // Depends on selected aimbot setting
						{
							Vector3D TargetBone;
							if (Features::Aimbot::ClosestHitbox) {
								TargetBone = Aimbot->BestTarget->GetBonePosition(static_cast<HitboxType>(Aimbot->GetBestBone(Aimbot->BestTarget)));
							}
							else if (!Features::Aimbot::ClosestHitbox) {
								TargetBone = Aimbot->BestTarget->GetBonePosition(Features::AimbotHitboxes::Hitbox);
							}

							GameCamera->WorldToScreen(TargetBone, TargetPos);
						}

						else if (Features::Sense::TargetBoneMode == 1) // Custom
						{
							Vector3D TargetBone;
							TargetBone = Aimbot->BestTarget->GetBonePosition(Features::Sense::TargetHitbox);

							GameCamera->WorldToScreen(TargetBone, TargetPos);
						}
					}

					Renderer::DrawLine(Canvas, Vector2D(x, ScreenHeight / 2), Vector2D(TargetPos), Features::Sense::TargetLineThickness, ImColor(TargetLineColor));
				}

				// Target Dot
				if (Features::Sense::DrawTargetDot && TargetVisualsEnabled) {
					ImVec4 TargetDotColor;
					if (Features::Sense::TargetMode == 1 && Aimbot->TargetSelected) {
						TargetDotColor = ImVec4(Features::Colors::TargetDotLockedColor[0], Features::Colors::TargetDotLockedColor[1], Features::Colors::TargetDotLockedColor[2], Features::Colors::TargetDotLockedColor[3]);
					}
					else {
						TargetDotColor = ImVec4(Features::Colors::TargetDotColor[0], Features::Colors::TargetDotColor[1], Features::Colors::TargetDotColor[2], Features::Colors::TargetDotColor[3]);
					}

					Vector2D TargetPos;
					if (Features::Sense::TargetMode == 0) // Current Target
					{
						if (Features::Sense::TargetBoneMode == 0) // Depends on selected aimbot setting
						{
							Vector3D TargetBone;
							if (Features::Aimbot::ClosestHitbox) {
								TargetBone = Aimbot->CurrentTarget->GetBonePosition(static_cast<HitboxType>(Aimbot->GetBestBone(Aimbot->CurrentTarget)));
							}
							else if (!Features::Aimbot::ClosestHitbox) {
								TargetBone = Aimbot->CurrentTarget->GetBonePosition(Features::AimbotHitboxes::Hitbox);
							}

							GameCamera->WorldToScreen(TargetBone, TargetPos);
						}

						else if (Features::Sense::TargetBoneMode == 1) // Custom
						{
							Vector3D TargetBone;
							TargetBone = Aimbot->CurrentTarget->GetBonePosition(Features::Sense::TargetHitbox);

							GameCamera->WorldToScreen(TargetBone, TargetPos);
						}
					}

					if (Features::Sense::TargetMode == 1) // Best Target
					{
						if (Features::Sense::TargetBoneMode == 0) // Depends on selected aimbot setting
						{
							Vector3D TargetBone;
							if (Features::Aimbot::ClosestHitbox) {
								TargetBone = Aimbot->BestTarget->GetBonePosition(static_cast<HitboxType>(Aimbot->GetBestBone(Aimbot->BestTarget)));
							}
							else if (!Features::Aimbot::ClosestHitbox) {
								TargetBone = Aimbot->BestTarget->GetBonePosition(Features::AimbotHitboxes::Hitbox);
							}

							GameCamera->WorldToScreen(TargetBone, TargetPos);
						}

						else if (Features::Sense::TargetBoneMode == 1) // Custom
						{
							Vector3D TargetBone;
							TargetBone = Aimbot->BestTarget->GetBonePosition(Features::Sense::TargetHitbox);

							GameCamera->WorldToScreen(TargetBone, TargetPos);
						}
					}

					Renderer::DrawCircleFilled(Canvas, TargetPos, Features::Sense::TargetDotRadius / p->DistanceToLocalPlayer, 255, ImColor(TargetDotColor));
				}

				// Target Box
				if (Features::Sense::DrawTargetBox && TargetVisualsEnabled) {
					ImVec4 TargetBoxColor;
					if (Features::Sense::TargetMode == 1 && Aimbot->TargetSelected) {
						TargetBoxColor = ImVec4(Features::Colors::TargetBoxLockedColor[0], Features::Colors::TargetBoxLockedColor[1], Features::Colors::TargetBoxLockedColor[2], Features::Colors::TargetBoxLockedColor[3]);
					}
					else {
						TargetBoxColor = ImVec4(Features::Colors::TargetBoxColor[0], Features::Colors::TargetBoxColor[1], Features::Colors::TargetBoxColor[2], Features::Colors::TargetBoxColor[3]);
					}
					if (Features::Sense::TargetBoxMode == 0) // Custom
					{

						Vector2D TargetPos;
						if (Features::Sense::TargetMode == 0) // Current Target
						{
							if (Features::Sense::TargetBoneMode == 0) // Depends on selected aimbot setting
							{
								Vector3D TargetBone;
								if (Features::Aimbot::ClosestHitbox) {
									TargetBone = Aimbot->CurrentTarget->GetBonePosition(static_cast<HitboxType>(Aimbot->GetBestBone(Aimbot->CurrentTarget)));
								}
								else if (!Features::Aimbot::ClosestHitbox) {
									TargetBone = Aimbot->CurrentTarget->GetBonePosition(Features::AimbotHitboxes::Hitbox);
								}

								GameCamera->WorldToScreen(TargetBone, TargetPos);
							}

							else if (Features::Sense::TargetBoneMode == 1) // Custom
							{
								Vector3D TargetBone;
								TargetBone = Aimbot->CurrentTarget->GetBonePosition(Features::Sense::TargetHitbox);

								GameCamera->WorldToScreen(TargetBone, TargetPos);
							}
						}

						if (Features::Sense::TargetMode == 1) // Best Target
						{
							if (Features::Sense::TargetBoneMode == 0) // Depends on selected aimbot setting
							{
								Vector3D TargetBone;
								if (Features::Aimbot::ClosestHitbox) {
									TargetBone = Aimbot->BestTarget->GetBonePosition(static_cast<HitboxType>(Aimbot->GetBestBone(Aimbot->BestTarget)));
								}
								else if (!Features::Aimbot::ClosestHitbox) {
									TargetBone = Aimbot->BestTarget->GetBonePosition(Features::AimbotHitboxes::Hitbox);
								}

								GameCamera->WorldToScreen(TargetBone, TargetPos);
							}

							else if (Features::Sense::TargetBoneMode == 1) // Custom
							{
								Vector3D TargetBone;
								TargetBone = Aimbot->BestTarget->GetBonePosition(Features::Sense::TargetHitbox);

								GameCamera->WorldToScreen(TargetBone, TargetPos);
							}
						}

						Canvas->AddRect(ImVec2(TargetPos.x - Features::Sense::TargetBoxSize, TargetPos.y - Features::Sense::TargetBoxSize), ImVec2(TargetPos.x + Features::Sense::TargetBoxSize, TargetPos.y + Features::Sense::TargetBoxSize), ImColor(TargetBoxColor), 0, 0, Features::Sense::TargetBoxThickness);
					}

					if (Features::Sense::TargetBoxMode == 1) // ESP Box
					{
						Vector2D TargetOriginW2S, TargetHeadPositionW2S;
						Vector3D TargetOrigin3D;
						Vector3D TargetHead3D;
						if (Features::Sense::TargetMode == 0) // Current Target
						{
							TargetOrigin3D = Aimbot->CurrentTarget->LocalOrigin;
							TargetHead3D = Aimbot->CurrentTarget->GetBonePosition(HitboxType::Head);
						}

						if (Features::Sense::TargetMode == 1) // Best Target
						{
							TargetOrigin3D = Aimbot->BestTarget->LocalOrigin;
							TargetHead3D = Aimbot->BestTarget->GetBonePosition(HitboxType::Head);
						}

						bool TargetOriginW2SValid = GameCamera->WorldToScreen(TargetOrigin3D, TargetOriginW2S);
						bool TargetHeadPositionW2SValid = GameCamera->WorldToScreen(TargetHead3D, TargetHeadPositionW2S);
						if (TargetOriginW2SValid && TargetHeadPositionW2SValid) {
							Renderer::Draw2DBox(Canvas, Features::Sense::Enemy::BoxType, Features::Sense::Enemy::BoxStyle, Features::Sense::Enemy::BoxOutline, TargetOriginW2S, TargetHeadPositionW2S, ImColor(TargetBoxColor), ImColor(FilledBoxColor), Features::Sense::Enemy::BoxThickness);
						}
					}
				}
			}

			// END OF ESP / SENSE
			// DEV STUFF
			if (Features::Dev::Enabled) {
				if (Features::Dev::LocalWeapon) {
					if (!Myself->IsDead) {
						ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
						ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y + 100), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
						ImGui::SetNextWindowBgAlpha(0.4f);
						ImGui::Begin("Current Weapon ID", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

						std::stringstream LocalwepID;
						LocalwepID << Myself->WeaponIndex;
						std::string LocalwepInt = LocalwepID.str() + " ";
						const char* LocalwepText = (char*)LocalwepInt.c_str();

						ImGui::Text("Current ID: ");
						ImGui::SameLine();
						ImGui::Text(LocalwepText);
						ImGui::End();
					}
				}
				if (Features::Dev::EnemyWeapon) {
					if (p->IsHostile) {
						std::stringstream wepID;
						wepID << p->WeaponIndex;
						std::string wepInt = wepID.str() + " ";
						const char* wepText = (char*)wepInt.c_str();

						ImColor weaponWHeldColor;
						weaponWHeldColor = ImColor(255, 255, 255);

						Renderer::DrawText(Canvas, LocalOriginW2S.Add(Vector2D(0, 35)), wepText, ImColor(weaponWHeldColor), true, true, false);
					}
				}
				if (Features::Dev::SkeletonIDs) {
					for (int i = 0; i < Features::Dev::BoneRange; i++) {
						Vector2D BonePos;
						GameCamera->WorldToScreen(p->GetBonePositionID(i), BonePos);
						std::stringstream temp;
						temp << i;
						std::string BoneID = temp.str();
						Renderer::DrawText(Canvas, BonePos, BoneID.c_str(), ImColor(255, 255, 255), Features::Sense::TextOutline ? true : false, true, false);
					}
				}
			} // End Of Dev
		} // End Of Loop
	}

	void RenderTargetInformation(ImDrawList* Canvas, Legitbot* Aimbot, Overlay OverlayWindow) {
		if (!Map->IsPlayable)
			return;
		if (Myself->IsDead)
			return;
		if (!Features::Settings::OverlayEnabled)
			return;
		if (!Features::Aimbot::AimbotEnabled)
			return;
		if (Features::Aimbot::SpectatorCheck && Features::TotalSpectators >= 1)
			return;
		if (Features::Aimbot::AimbotMode == 1)
			return;

		bool TargetInfoEnabled;
		if (Features::Sense::DrawTargetInfo) {
			if (Features::Sense::TargetMode == 0) // Current Target
			{
				if (Aimbot->TargetSelected) {
					TargetInfoEnabled = true;
				}
				else if (!Aimbot->TargetSelected) {
					TargetInfoEnabled = false;
				}
			}
			if (Features::Sense::TargetMode == 1) // Best Target
			{
				bool TargetAvaliable = Aimbot->IsBestTarget();
				if (TargetAvaliable) {
					TargetInfoEnabled = true;
				}
				else if (!TargetAvaliable) {
					TargetInfoEnabled = false;
				}
			}
		}

		// Target Information
		if (Features::Sense::DrawTargetInfo && TargetInfoEnabled) {
			// Wanted to create a seperate window for it like spectator list, but failed & was restricted

			int ScreenWidth;
			int ScreenHeight;
			OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);

			int PosX = Features::Sense::TargetInfoPosX;
			int PosY = Features::Sense::TargetInfoPosY;

			// Text
			std::stringstream Target, Name, Distance, TeamID, Weapon, Legend, HPValue, HPMaxValue, APValue, APMaxValue;
			const char* TargetText;
			const char* LegendText;
			const char* WeaponText;
			const char* HPText;
			const char* APText;

			// Colors
			ImVec4 TargetInfoColor, TargetInfoWeaponColor, TargetInfoHealthColor, TargetInfoShieldColor;
			if (Features::Sense::TargetInfoColorMode == 0) // Simple
			{
				if (Aimbot->TargetSelected) {
					TargetInfoColor = ImVec4(Features::Colors::TargetInfoLockedColor[0], Features::Colors::TargetInfoLockedColor[1], Features::Colors::TargetInfoLockedColor[2], Features::Colors::TargetInfoLockedColor[3]);
					TargetInfoWeaponColor = ImVec4(Features::Colors::TargetInfoLockedColor[0], Features::Colors::TargetInfoLockedColor[1], Features::Colors::TargetInfoLockedColor[2], Features::Colors::TargetInfoLockedColor[3]);
					TargetInfoHealthColor = ImVec4(Features::Colors::TargetInfoLockedColor[0], Features::Colors::TargetInfoLockedColor[1], Features::Colors::TargetInfoLockedColor[2], Features::Colors::TargetInfoLockedColor[3]);
					TargetInfoShieldColor = ImVec4(Features::Colors::TargetInfoLockedColor[0], Features::Colors::TargetInfoLockedColor[1], Features::Colors::TargetInfoLockedColor[2], Features::Colors::TargetInfoLockedColor[3]);
				}
				else {
					TargetInfoColor = ImVec4(Features::Colors::TargetInfoColor[0], Features::Colors::TargetInfoColor[1], Features::Colors::TargetInfoColor[2], Features::Colors::TargetInfoColor[3]);
					TargetInfoWeaponColor = ImVec4(Features::Colors::TargetInfoColor[0], Features::Colors::TargetInfoColor[1], Features::Colors::TargetInfoColor[2], Features::Colors::TargetInfoColor[3]);
					TargetInfoHealthColor = ImVec4(Features::Colors::TargetInfoColor[0], Features::Colors::TargetInfoColor[1], Features::Colors::TargetInfoColor[2], Features::Colors::TargetInfoColor[3]);
					TargetInfoShieldColor = ImVec4(Features::Colors::TargetInfoColor[0], Features::Colors::TargetInfoColor[1], Features::Colors::TargetInfoColor[2], Features::Colors::TargetInfoColor[3]);
				}
			}
			if (Features::Sense::TargetInfoColorMode == 1) // Advanced
			{
				if (Aimbot->TargetSelected) {
					TargetInfoColor = ImVec4(Features::Colors::TargetInfoLockedColor[0], Features::Colors::TargetInfoLockedColor[1], Features::Colors::TargetInfoLockedColor[2], Features::Colors::TargetInfoLockedColor[3]);
				}
				else {
					TargetInfoColor = ImVec4(Features::Colors::TargetInfoColor[0], Features::Colors::TargetInfoColor[1], Features::Colors::TargetInfoColor[2], Features::Colors::TargetInfoColor[3]);
				}
			}

			if (Features::Sense::TargetMode == 0) // Current Target
			{
				Target << "Target: ";
				Distance << std::to_string((int) Conversion::ToMeters(Aimbot->CurrentTarget->DistanceToLocalPlayer)).c_str();
				Name << Aimbot->CurrentTarget->GetPlayerName().c_str();
				TeamID << Aimbot->CurrentTarget->Team;
				Weapon << Aimbot->CurrentTarget->GetWeaponHeldName().c_str();
				Legend << Aimbot->CurrentTarget->getPlayerModelName().c_str();
				HPValue << Aimbot->CurrentTarget->Health;
				HPMaxValue << Aimbot->CurrentTarget->MaxHealth;
				APValue << Aimbot->CurrentTarget->Shield;
				APMaxValue << Aimbot->CurrentTarget->MaxShield;

				if (Features::Sense::TargetInfoColorMode == 1) {
					TargetInfoWeaponColor = Aimbot->CurrentTarget->GetWeaponHeldColor();
					TargetInfoHealthColor = ImVec4(0, 255, 0, 255);
					TargetInfoShieldColor = Aimbot->CurrentTarget->GetShieldColor();
				}
			}

			if (Features::Sense::TargetMode == 1) // Best Target
			{
				Target << "Target: ";
				Distance << std::to_string((int) Conversion::ToMeters(Aimbot->BestTarget->DistanceToLocalPlayer)).c_str();
				Name << Aimbot->BestTarget->GetPlayerName().c_str();
				TeamID << Aimbot->BestTarget->Team;
				Weapon << Aimbot->BestTarget->GetWeaponHeldName().c_str();
				Legend << Aimbot->BestTarget->getPlayerModelName().c_str();
				HPValue << Aimbot->BestTarget->Health;
				HPMaxValue << Aimbot->BestTarget->MaxHealth;
				APValue << Aimbot->BestTarget->Shield;
				APMaxValue << Aimbot->BestTarget->MaxShield;

				if (Features::Sense::TargetInfoColorMode == 1) {
					TargetInfoWeaponColor = Aimbot->BestTarget->GetWeaponHeldColor();
					TargetInfoHealthColor = ImVec4(0, 255, 0, 255);
					TargetInfoShieldColor = Aimbot->BestTarget->GetShieldColor();
				}
			}

			if (Features::Sense::DrawTargetInfoName && Features::Sense::DrawTargetInfoLegend) {
				std::stringstream Temp1, Temp2;
				if (Features::Sense::DrawTargetInfoTeamID) {
					Temp1 << "[" + TeamID.str() + "] ";
				}
				if (Features::Sense::DrawTargetInfoDistance) {
					Temp2 << " [" + Distance.str() + " M]";
				}

				std::stringstream Temp3, Temp4;
				Temp3 << "Legend: ";
				Temp4 << "Name: ";

				if (Features::Sense::TargetInfoDisplayMode == 0) // Name First, Legend Second
				{
					std::string Temp = Target.str() + Temp1.str() + Name.str() + Temp2.str();
					const char* CombinedTargetText = Temp.c_str();
					Renderer::DrawText(Canvas, Vector2D(GetTargetInfoPosition(Vector2D(PosX, PosY), Features::Sense::TargetInfoNamePos)), CombinedTargetText, ImColor(TargetInfoColor), Features::Sense::TextOutline ? true : false, true, false);


					std::string Temp5 = Temp3.str() + Legend.str();
					const char* CombinedLegendText = Temp5.c_str();
					Renderer::DrawText(Canvas, Vector2D(GetTargetInfoPosition(Vector2D(PosX, PosY), Features::Sense::TargetInfoLegendPos)), CombinedLegendText, ImColor(TargetInfoColor), Features::Sense::TextOutline ? true : false, true, false);
				}

				if (Features::Sense::TargetInfoDisplayMode == 1) // Legend First, Name Second
				{
					std::string Temp = Target.str() + Temp1.str() + Legend.str() + Temp2.str();
					const char* CombinedTargetText = Temp.c_str();
					Renderer::DrawText(Canvas, Vector2D(GetTargetInfoPosition(Vector2D(PosX, PosY), Features::Sense::TargetInfoLegendPos)), CombinedTargetText, ImColor(TargetInfoColor), Features::Sense::TextOutline ? true : false, true, false);


					std::string Temp5 = Temp4.str() + Name.str();
					const char* CombinedNameText = Temp5.c_str();
					Renderer::DrawText(Canvas, Vector2D(GetTargetInfoPosition(Vector2D(PosX, PosY), Features::Sense::TargetInfoNamePos)), CombinedNameText, ImColor(TargetInfoColor), Features::Sense::TextOutline ? true : false, true, false);
				}
			}

			else if (Features::Sense::DrawTargetInfoName && !Features::Sense::DrawTargetInfoLegend) {
				std::stringstream Temp1, Temp2;
				if (Features::Sense::DrawTargetInfoTeamID) {
					Temp1 << " [" + TeamID.str() + "] ";
				}
				if (Features::Sense::DrawTargetInfoDistance) {
					Temp2 << " [" + Distance.str() + " M]";
				}

				std::string Temp = Target.str() + Temp1.str() + Name.str() + Temp2.str();
				const char* CombinedTargetText = Temp.c_str();
				Renderer::DrawText(Canvas, Vector2D(GetTargetInfoPosition(Vector2D(PosX, PosY), Features::Sense::TargetInfoNamePos)), CombinedTargetText, ImColor(TargetInfoColor), Features::Sense::TextOutline ? true : false, true, false);
			}
			else if (!Features::Sense::DrawTargetInfoName && Features::Sense::DrawTargetInfoLegend) {
				std::stringstream Temp1, Temp2;
				if (Features::Sense::DrawTargetInfoTeamID) {
					Temp1 << "[" + TeamID.str() + "]";
				}
				if (Features::Sense::DrawTargetInfoDistance) {
					Temp2 << " [" + Distance.str() + " M]";
				}

				std::string Temp = Target.str() + Temp1.str() + Legend.str() + Temp2.str();
				const char* CombinedTargetText = Temp.c_str();
				Renderer::DrawText(Canvas, Vector2D(GetTargetInfoPosition(Vector2D(PosX, PosY), Features::Sense::TargetInfoLegendPos)), CombinedTargetText, ImColor(TargetInfoColor), Features::Sense::TextOutline ? true : false, true, false);
			}

			if (Features::Sense::DrawTargetInfoWeapon) {
				std::stringstream Temp1;
				Temp1 << Weapon.str();
				std::string Temp = "Weapon: " + Temp1.str();
				const char* CombinedWeaponText = Temp.c_str();
				Renderer::DrawText(Canvas, Vector2D(GetTargetInfoPosition(Vector2D(PosX, PosY), Features::Sense::TargetInfoWeaponPos)), CombinedWeaponText, ImColor(TargetInfoWeaponColor), Features::Sense::TextOutline ? true : false, true, false);
			}

			if (Features::Sense::DrawTargetInfoHealth) {
				std::stringstream Temp1, Temp2;
				Temp1 << HPValue.str();
				Temp2 << HPMaxValue.str();
				std::string Temp = "Health: " + Temp1.str() + " / " + Temp2.str();;
				const char* CombinedWeaponText = Temp.c_str();
				Renderer::DrawText(Canvas, Vector2D(GetTargetInfoPosition(Vector2D(PosX, PosY), Features::Sense::TargetInfoHealthPos)), CombinedWeaponText, ImColor(TargetInfoHealthColor), Features::Sense::TextOutline ? true : false, true, false);
			}

			if (Features::Sense::DrawTargetInfoShield) {
				std::stringstream Temp1, Temp2;
				Temp1 << APValue.str();
				Temp2 << APMaxValue.str();
				std::string Temp = "Shield: " + Temp1.str() + " / " + Temp2.str();;
				const char* CombinedWeaponText = Temp.c_str();
				Renderer::DrawText(Canvas, Vector2D(GetTargetInfoPosition(Vector2D(PosX, PosY), Features::Sense::TargetInfoShieldPos)), CombinedWeaponText, ImColor(TargetInfoShieldColor), Features::Sense::TextOutline ? true : false, true, false);
			}
		}
	}

	Vector2D GetTargetInfoPosition(Vector2D MainPosition, int Position) {
		if (Position == 0) {
			MainPosition = Vector2D(MainPosition.x, MainPosition.y + 0);
		}
		else if (Position == 1) {
			MainPosition = Vector2D(MainPosition.x, MainPosition.y + Features::Sense::TargetInfoOffset);
		}
		else if (Position == 2) {
			MainPosition = Vector2D(MainPosition.x, MainPosition.y + (Features::Sense::TargetInfoOffset * 2));
		}
		else if (Position == 3) {
			MainPosition = Vector2D(MainPosition.x, MainPosition.y + (Features::Sense::TargetInfoOffset * 3));
		}
		else if (Position == 4) {
			MainPosition = Vector2D(MainPosition.x, MainPosition.y + (Features::Sense::TargetInfoOffset * 4));
		}

		return MainPosition;
	}

	Vector2D GetTargetTextPosition(Vector2D MainPosition, Vector2D LocalOriginW2S, Vector2D AboveHeadW2S, int Position) {
		if (Position == 0) { // Top 1
			MainPosition = AboveHeadW2S.Subtract(Vector2D(0, 16));
		}
		else if (Position == 1) { // Top 2
			MainPosition = AboveHeadW2S.Subtract(Vector2D(0, 32));
		}
		else if (Position == 2) { // Bottom 1
			MainPosition = LocalOriginW2S;
		}
		else if (Position == 3) { // Bottom 2
			MainPosition = LocalOriginW2S.Add(Vector2D(0, 11));
		}
		else if (Position == 4) { // Bottom 1
			MainPosition = LocalOriginW2S.Add(Vector2D(0, 22));
		}
		else {
			MainPosition = MainPosition;
		}
		return MainPosition;
	}
};
