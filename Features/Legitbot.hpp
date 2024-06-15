#pragma once
#include <iostream>
#include <vector>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/Level.hpp"

#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"

#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/QAngle.hpp"
#include "../Math/Resolver.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/InputTypes.hpp"
#include "../Utils/Weapons.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

// Conversion
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))

struct Legitbot
{

	float FinalDistance = 0;
	float FinalFOV = 0;
	float MinDistance = 1;

	QAngle DesiredAngles = QAngle(0, 0);
	Vector3D TargetPosition;

	//XDisplay* X11Display; LINUX
	DriverHID* DHID;
	LocalPlayer* Myself;
	std::vector<Player*>* Players;
	Level* Map;

	Player* CurrentTarget = nullptr;
	bool TargetSelected;

	Player* BestTarget = nullptr; // Used for Target Visuals

	QAngle RCSLastPunch;
	std::chrono::milliseconds LastAimTime;

	Legitbot(DriverHID* DHID, Level* Map, LocalPlayer* Myself, std::vector<Player*>* GamePlayers) {
		this->DHID = DHID;
		this->Myself = Myself;
		this->Players = GamePlayers;
		this->Map = Map;
	}

	static bool Save() {
		try {
			Config::Aimbot::AimbotEnabled = Features::Aimbot::AimbotEnabled;
			Config::Aimbot::BindMethod = Features::Aimbot::BindMethod;
			Config::Aimbot::AimbotMode = Features::Aimbot::AimbotMode;
			Config::Aimbot::InputMethod = Features::Aimbot::InputMethod;
			Config::Aimbot::ClosestHitbox = Features::Aimbot::ClosestHitbox;
			Config::Aimbot::OnFire = Features::Aimbot::OnFire;
			Config::Aimbot::OnADS = Features::Aimbot::OnADS;
			Config::Aimbot::VisCheck = Features::Aimbot::VisCheck;
			Config::Aimbot::TeamCheck = Features::Aimbot::TeamCheck;
			Config::Aimbot::SpectatorCheck = Features::Aimbot::SpectatorCheck;
			Config::Aimbot::SpectatorNotifier = Features::Aimbot::SpectatorNotifier;
			Config::Aimbot::TargetSwitching = Features::Aimbot::TargetSwitching;
			Config::Aimbot::Priority = Features::Aimbot::Priority;
			Config::Aimbot::PredictMovement = Features::Aimbot::PredictMovement;
			Config::Aimbot::PredictBulletDrop = Features::Aimbot::PredictBulletDrop;
			Config::Aimbot::FinalDistance = Features::Aimbot::FinalDistance;
			Config::Aimbot::Smooth = Features::Aimbot::Smooth;
			Config::Aimbot::Speed = Features::Aimbot::Speed;
			Config::Aimbot::SmoothingMethod = Features::Aimbot::SmoothingMethod;
			Config::Aimbot::HipfireSmooth = Features::Aimbot::HipfireSmooth;
			Config::Aimbot::ADSSmooth = Features::Aimbot::ADSSmooth;
			Config::Aimbot::MinHipfireSmooth = Features::Aimbot::MinHipfireSmooth;
			Config::Aimbot::MaxHipfireSmooth = Features::Aimbot::MaxHipfireSmooth;
			Config::Aimbot::MinADSSmooth = Features::Aimbot::MinADSSmooth;
			Config::Aimbot::MaxADSSmooth = Features::Aimbot::MaxADSSmooth;
			// Aimbot 3 Testing
			Config::Aimbot::MouseHipfireSmoothing = Features::Aimbot::MouseHipfireSmoothing;
			Config::Aimbot::MouseADSSmoothing = Features::Aimbot::MouseADSSmoothing;
			Config::Aimbot::MouseExtraSmoothing = Features::Aimbot::MouseExtraSmoothing;
			Config::Aimbot::MinMouseHipfireSmoothing = Features::Aimbot::MinMouseHipfireSmoothing;
			Config::Aimbot::MaxMouseHipfireSmoothing = Features::Aimbot::MaxMouseHipfireSmoothing;
			Config::Aimbot::MinMouseADSSmoothing = Features::Aimbot::MinMouseADSSmoothing;
			Config::Aimbot::MaxMouseADSSmoothing = Features::Aimbot::MaxMouseADSSmoothing;

			Config::Aimbot::Delay = Features::Aimbot::Delay;
			Config::Aimbot::FOV = Features::Aimbot::FOV;
			Config::Aimbot::ZoomScale = Features::Aimbot::ZoomScale;
			Config::Aimbot::MinDistance = Features::Aimbot::MinDistance;
			Config::Aimbot::HipfireDistance = Features::Aimbot::HipfireDistance;
			Config::Aimbot::ZoomDistance = Features::Aimbot::ZoomDistance;
			// AimMode 2
			Config::Aimbot::HipfireSmooth1 = Features::Aimbot::HipfireSmooth1;
			Config::Aimbot::ADSSmooth1 = Features::Aimbot::ADSSmooth1;
			Config::Aimbot::ExtraSmoothing = Features::Aimbot::ExtraSmoothing;
			Config::Aimbot::Deadzone = Features::Aimbot::Deadzone;
			Config::Aimbot::FOV1 = Features::Aimbot::FOV1;
			Config::Aimbot::MinDistance2 = Features::Aimbot::MinDistance2;
			Config::Aimbot::MaxDistance2 = Features::Aimbot::MaxDistance2;
			// Weapon Toggles
			// Light
			Config::Aimbot::P2020 = Features::Aimbot::P2020;
			Config::Aimbot::RE45 = Features::Aimbot::RE45;
			Config::Aimbot::Alternator = Features::Aimbot::Alternator;
			Config::Aimbot::R99 = Features::Aimbot::R99;
			Config::Aimbot::R301 = Features::Aimbot::R301;
			Config::Aimbot::Spitfire = Features::Aimbot::Spitfire;
			Config::Aimbot::G7 = Features::Aimbot::G7;
			// Heavy
			Config::Aimbot::Flatline = Features::Aimbot::Flatline;
			Config::Aimbot::Hemlock = Features::Aimbot::Hemlock;
			Config::Aimbot::Repeater = Features::Aimbot::Repeater;
			Config::Aimbot::Rampage = Features::Aimbot::Rampage;
			Config::Aimbot::CARSMG = Features::Aimbot::CARSMG;
			// Energy
			Config::Aimbot::Havoc = Features::Aimbot::Havoc;
			Config::Aimbot::Devotion = Features::Aimbot::Devotion;
			Config::Aimbot::LSTAR = Features::Aimbot::LSTAR;
			Config::Aimbot::TripleTake = Features::Aimbot::TripleTake;
			Config::Aimbot::Volt = Features::Aimbot::Volt;
			Config::Aimbot::Nemesis = Features::Aimbot::Nemesis;
			// Shotgun
			Config::Aimbot::Mozambique = Features::Aimbot::Mozambique;
			Config::Aimbot::EVA8 = Features::Aimbot::EVA8;
			Config::Aimbot::Peacekeeper = Features::Aimbot::Peacekeeper;
			Config::Aimbot::Mastiff = Features::Aimbot::Mastiff;
			// Snipers
			Config::Aimbot::Longbow = Features::Aimbot::Longbow;
			Config::Aimbot::ChargeRifle = Features::Aimbot::ChargeRifle;
			Config::Aimbot::Sentinel = Features::Aimbot::Sentinel;
			// Legendary
			Config::Aimbot::Wingman = Features::Aimbot::Wingman;
			Config::Aimbot::Prowler = Features::Aimbot::Prowler;
			Config::Aimbot::Bocek = Features::Aimbot::Bocek;
			Config::Aimbot::Kraber = Features::Aimbot::Kraber;
			Config::Aimbot::Knife = Features::Aimbot::Knife;
			//---------------Advanced---------------//
			Config::Aimbot::AdvancedAim = Features::Aimbot::AdvancedAim;
			Config::Aimbot::AdvancedFire = Features::Aimbot::AdvancedFire;
			Config::Aimbot::AdvancedADS = Features::Aimbot::AdvancedADS;
			// Aimbot Mode 0 - xap-client
			Config::Aimbot::AdvancedClosestHitbox = Features::Aimbot::AdvancedClosestHitbox;
			Config::Aimbot::AdvancedHitbox = Features::Aimbot::AdvancedHitbox;
			Config::Aimbot::AdvancedSpeed = Features::Aimbot::AdvancedSpeed;
			Config::Aimbot::AdvancedSmooth = Features::Aimbot::AdvancedSmooth;
			Config::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::AdvancedHipfireSmooth;
			Config::Aimbot::AdvancedADSSmooth = Features::Aimbot::AdvancedADSSmooth;
			Config::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::AdvancedMinADSSmooth;
			Config::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::AdvancedMaxADSSmooth;
			Config::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::AdvancedMinHipfireSmooth;
			Config::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::AdvancedMaxHipfireSmooth;
			// Aimbot Mode 1 - Grinder
			Config::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::AdvancedHipfireSmooth1;
			Config::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::AdvancedADSSmooth1;
			Config::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::AdvancedMinHipfireSmooth1;
			Config::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::AdvancedMaxHipfireSmooth1;
			Config::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::AdvancedMinADSSmooth1;
			Config::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::AdvancedMaxADSSmooth1;
			Config::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::AdvancedExtraSmooth1;
			Config::Aimbot::AdvancedFOV1 = Features::Aimbot::AdvancedFOV1;
			Config::Aimbot::AdvancedDeadzone = Features::Aimbot::AdvancedDeadzone;
			Config::Aimbot::AdvancedMinDistance1 = Features::Aimbot::AdvancedMinDistance1;
			Config::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::AdvancedMaxDistance1;
			// Advanced Aimbot Settings
			Config::Aimbot::P2020Fire = Features::Aimbot::P2020Fire;
			Config::Aimbot::P2020ADS = Features::Aimbot::P2020ADS;
			Config::Aimbot::P2020ClosestHitbox = Features::Aimbot::P2020ClosestHitbox;
			Config::Aimbot::P2020Hitbox = Features::Aimbot::P2020Hitbox;
			Config::Aimbot::P2020Speed = Features::Aimbot::P2020Speed;
			Config::Aimbot::P2020HipfireSmooth = Features::Aimbot::P2020HipfireSmooth;
			Config::Aimbot::P2020ADSSmooth = Features::Aimbot::P2020ADSSmooth;
			Config::Aimbot::P2020SmoothingMethod = Features::Aimbot::P2020SmoothingMethod;
			Config::Aimbot::P2020MinHipfireSmooth = Features::Aimbot::P2020MinHipfireSmooth;
			Config::Aimbot::P2020MaxHipfireSmooth = Features::Aimbot::P2020MaxHipfireSmooth;
			Config::Aimbot::P2020MinADSSmooth = Features::Aimbot::P2020MinADSSmooth;
			Config::Aimbot::P2020MaxADSSmooth = Features::Aimbot::P2020MaxADSSmooth;
			Config::Aimbot::P2020MinHipfireSmooth1 = Features::Aimbot::P2020MinHipfireSmooth1;
			Config::Aimbot::P2020MaxHipfireSmooth1 = Features::Aimbot::P2020MaxHipfireSmooth1;
			Config::Aimbot::P2020MinADSSmooth1 = Features::Aimbot::P2020MinADSSmooth1;
			Config::Aimbot::P2020MaxADSSmooth1 = Features::Aimbot::P2020MaxADSSmooth1;
			Config::Aimbot::P2020FOV = Features::Aimbot::P2020FOV;
			Config::Aimbot::P2020ZoomScale = Features::Aimbot::P2020ZoomScale;
			Config::Aimbot::P2020HipfireSmooth1 = Features::Aimbot::P2020HipfireSmooth1;
			Config::Aimbot::P2020ADSSmooth1 = Features::Aimbot::P2020ADSSmooth1;
			Config::Aimbot::P2020ExtraSmooth1 = Features::Aimbot::P2020ExtraSmooth1;
			Config::Aimbot::P2020Deadzone = Features::Aimbot::P2020Deadzone;
			Config::Aimbot::P2020FOV1 = Features::Aimbot::P2020FOV1;
			Config::Aimbot::P2020MinDistance1 = Features::Aimbot::P2020MinDistance1;
			Config::Aimbot::P2020MaxDistance1 = Features::Aimbot::P2020MaxDistance1;
			Config::Aimbot::RE45Fire = Features::Aimbot::RE45Fire;
			Config::Aimbot::RE45ADS = Features::Aimbot::RE45ADS;
			Config::Aimbot::RE45ClosestHitbox = Features::Aimbot::RE45ClosestHitbox;
			Config::Aimbot::RE45Hitbox = Features::Aimbot::RE45Hitbox;
			Config::Aimbot::RE45Speed = Features::Aimbot::RE45Speed;
			Config::Aimbot::RE45HipfireSmooth = Features::Aimbot::RE45HipfireSmooth;
			Config::Aimbot::RE45ADSSmooth = Features::Aimbot::RE45ADSSmooth;
			Config::Aimbot::RE45SmoothingMethod = Features::Aimbot::RE45SmoothingMethod;
			Config::Aimbot::RE45MinHipfireSmooth = Features::Aimbot::RE45MinHipfireSmooth;
			Config::Aimbot::RE45MaxHipfireSmooth = Features::Aimbot::RE45MaxHipfireSmooth;
			Config::Aimbot::RE45MinADSSmooth = Features::Aimbot::RE45MinADSSmooth;
			Config::Aimbot::RE45MaxADSSmooth = Features::Aimbot::RE45MaxADSSmooth;
			Config::Aimbot::RE45MinHipfireSmooth1 = Features::Aimbot::RE45MinHipfireSmooth1;
			Config::Aimbot::RE45MaxHipfireSmooth1 = Features::Aimbot::RE45MaxHipfireSmooth1;
			Config::Aimbot::RE45MinADSSmooth1 = Features::Aimbot::RE45MinADSSmooth1;
			Config::Aimbot::RE45MaxADSSmooth1 = Features::Aimbot::RE45MaxADSSmooth1;
			Config::Aimbot::RE45FOV = Features::Aimbot::RE45FOV;
			Config::Aimbot::RE45ZoomScale = Features::Aimbot::RE45ZoomScale;
			Config::Aimbot::RE45HipfireSmooth1 = Features::Aimbot::RE45HipfireSmooth1;
			Config::Aimbot::RE45ADSSmooth1 = Features::Aimbot::RE45ADSSmooth1;
			Config::Aimbot::RE45ExtraSmooth1 = Features::Aimbot::RE45ExtraSmooth1;
			Config::Aimbot::RE45Deadzone = Features::Aimbot::RE45Deadzone;
			Config::Aimbot::RE45FOV1 = Features::Aimbot::RE45FOV1;
			Config::Aimbot::RE45MinDistance1 = Features::Aimbot::RE45MinDistance1;
			Config::Aimbot::RE45MaxDistance1 = Features::Aimbot::RE45MaxDistance1;
			Config::Aimbot::AlternatorFire = Features::Aimbot::AlternatorFire;
			Config::Aimbot::AlternatorADS = Features::Aimbot::AlternatorADS;
			Config::Aimbot::AlternatorClosestHitbox = Features::Aimbot::AlternatorClosestHitbox;
			Config::Aimbot::AlternatorHitbox = Features::Aimbot::AlternatorHitbox;
			Config::Aimbot::AlternatorSpeed = Features::Aimbot::AlternatorSpeed;
			Config::Aimbot::AlternatorHipfireSmooth = Features::Aimbot::AlternatorHipfireSmooth;
			Config::Aimbot::AlternatorADSSmooth = Features::Aimbot::AlternatorADSSmooth;
			Config::Aimbot::AlternatorSmoothingMethod = Features::Aimbot::AlternatorSmoothingMethod;
			Config::Aimbot::AlternatorMinHipfireSmooth = Features::Aimbot::AlternatorMinHipfireSmooth;
			Config::Aimbot::AlternatorMaxHipfireSmooth = Features::Aimbot::AlternatorMaxHipfireSmooth;
			Config::Aimbot::AlternatorMinADSSmooth = Features::Aimbot::AlternatorMinADSSmooth;
			Config::Aimbot::AlternatorMaxADSSmooth = Features::Aimbot::AlternatorMaxADSSmooth;
			Config::Aimbot::AlternatorMinHipfireSmooth1 = Features::Aimbot::AlternatorMinHipfireSmooth1;
			Config::Aimbot::AlternatorMaxHipfireSmooth1 = Features::Aimbot::AlternatorMaxHipfireSmooth1;
			Config::Aimbot::AlternatorMinADSSmooth1 = Features::Aimbot::AlternatorMinADSSmooth1;
			Config::Aimbot::AlternatorMaxADSSmooth1 = Features::Aimbot::AlternatorMaxADSSmooth1;
			Config::Aimbot::AlternatorFOV = Features::Aimbot::AlternatorFOV;
			Config::Aimbot::AlternatorZoomScale = Features::Aimbot::AlternatorZoomScale;
			Config::Aimbot::AlternatorHipfireSmooth1 = Features::Aimbot::AlternatorHipfireSmooth1;
			Config::Aimbot::AlternatorADSSmooth1 = Features::Aimbot::AlternatorADSSmooth1;
			Config::Aimbot::AlternatorExtraSmooth1 = Features::Aimbot::AlternatorExtraSmooth1;
			Config::Aimbot::AlternatorDeadzone = Features::Aimbot::AlternatorDeadzone;
			Config::Aimbot::AlternatorFOV1 = Features::Aimbot::AlternatorFOV1;
			Config::Aimbot::AlternatorMinDistance1 = Features::Aimbot::AlternatorMinDistance1;
			Config::Aimbot::AlternatorMaxDistance1 = Features::Aimbot::AlternatorMaxDistance1;
			Config::Aimbot::R99Fire = Features::Aimbot::R99Fire;
			Config::Aimbot::R99ADS = Features::Aimbot::R99ADS;
			Config::Aimbot::R99ClosestHitbox = Features::Aimbot::R99ClosestHitbox;
			Config::Aimbot::R99Hitbox = Features::Aimbot::R99Hitbox;
			Config::Aimbot::R99Speed = Features::Aimbot::R99Speed;
			Config::Aimbot::R99HipfireSmooth = Features::Aimbot::R99HipfireSmooth;
			Config::Aimbot::R99ADSSmooth = Features::Aimbot::R99ADSSmooth;
			Config::Aimbot::R99SmoothingMethod = Features::Aimbot::R99SmoothingMethod;
			Config::Aimbot::R99MinHipfireSmooth = Features::Aimbot::R99MinHipfireSmooth;
			Config::Aimbot::R99MaxHipfireSmooth = Features::Aimbot::R99MaxHipfireSmooth;
			Config::Aimbot::R99MinADSSmooth = Features::Aimbot::R99MinADSSmooth;
			Config::Aimbot::R99MaxADSSmooth = Features::Aimbot::R99MaxADSSmooth;
			Config::Aimbot::R99MinHipfireSmooth1 = Features::Aimbot::R99MinHipfireSmooth1;
			Config::Aimbot::R99MaxHipfireSmooth1 = Features::Aimbot::R99MaxHipfireSmooth1;
			Config::Aimbot::R99MinADSSmooth1 = Features::Aimbot::R99MinADSSmooth1;
			Config::Aimbot::R99MaxADSSmooth1 = Features::Aimbot::R99MaxADSSmooth1;
			Config::Aimbot::R99FOV = Features::Aimbot::R99FOV;
			Config::Aimbot::R99ZoomScale = Features::Aimbot::R99ZoomScale;
			Config::Aimbot::R99HipfireSmooth1 = Features::Aimbot::R99HipfireSmooth1;
			Config::Aimbot::R99ADSSmooth1 = Features::Aimbot::R99ADSSmooth1;
			Config::Aimbot::R99ExtraSmooth1 = Features::Aimbot::R99ExtraSmooth1;
			Config::Aimbot::R99Deadzone = Features::Aimbot::R99Deadzone;
			Config::Aimbot::R99FOV1 = Features::Aimbot::R99FOV1;
			Config::Aimbot::R99MinDistance1 = Features::Aimbot::R99MinDistance1;
			Config::Aimbot::R99MaxDistance1 = Features::Aimbot::R99MaxDistance1;
			Config::Aimbot::R301Fire = Features::Aimbot::R301Fire;
			Config::Aimbot::R301ADS = Features::Aimbot::R301ADS;
			Config::Aimbot::R301ClosestHitbox = Features::Aimbot::R301ClosestHitbox;
			Config::Aimbot::R301Hitbox = Features::Aimbot::R301Hitbox;
			Config::Aimbot::R301Speed = Features::Aimbot::R301Speed;
			Config::Aimbot::R301HipfireSmooth = Features::Aimbot::R301HipfireSmooth;
			Config::Aimbot::R301ADSSmooth = Features::Aimbot::R301ADSSmooth;
			Config::Aimbot::R301SmoothingMethod = Features::Aimbot::R301SmoothingMethod;
			Config::Aimbot::R301MinHipfireSmooth = Features::Aimbot::R301MinHipfireSmooth;
			Config::Aimbot::R301MaxHipfireSmooth = Features::Aimbot::R301MaxHipfireSmooth;
			Config::Aimbot::R301MinADSSmooth = Features::Aimbot::R301MinADSSmooth;
			Config::Aimbot::R301MaxADSSmooth = Features::Aimbot::R301MaxADSSmooth;
			Config::Aimbot::R301MinHipfireSmooth1 = Features::Aimbot::R301MinHipfireSmooth1;
			Config::Aimbot::R301MaxHipfireSmooth1 = Features::Aimbot::R301MaxHipfireSmooth1;
			Config::Aimbot::R301MinADSSmooth1 = Features::Aimbot::R301MinADSSmooth1;
			Config::Aimbot::R301MaxADSSmooth1 = Features::Aimbot::R301MaxADSSmooth1;
			Config::Aimbot::R301FOV = Features::Aimbot::R301FOV;
			Config::Aimbot::R301ZoomScale = Features::Aimbot::R301ZoomScale;
			Config::Aimbot::R301HipfireSmooth1 = Features::Aimbot::R301HipfireSmooth1;
			Config::Aimbot::R301ADSSmooth1 = Features::Aimbot::R301ADSSmooth1;
			Config::Aimbot::R301ExtraSmooth1 = Features::Aimbot::R301ExtraSmooth1;
			Config::Aimbot::R301Deadzone = Features::Aimbot::R301Deadzone;
			Config::Aimbot::R301FOV1 = Features::Aimbot::R301FOV1;
			Config::Aimbot::R301MinDistance1 = Features::Aimbot::R301MinDistance1;
			Config::Aimbot::R301MaxDistance1 = Features::Aimbot::R301MaxDistance1;
			Config::Aimbot::SpitfireFire = Features::Aimbot::SpitfireFire;
			Config::Aimbot::SpitfireADS = Features::Aimbot::SpitfireADS;
			Config::Aimbot::SpitfireClosestHitbox = Features::Aimbot::SpitfireClosestHitbox;
			Config::Aimbot::SpitfireHitbox = Features::Aimbot::SpitfireHitbox;
			Config::Aimbot::SpitfireSpeed = Features::Aimbot::SpitfireSpeed;
			Config::Aimbot::SpitfireHipfireSmooth = Features::Aimbot::SpitfireHipfireSmooth;
			Config::Aimbot::SpitfireADSSmooth = Features::Aimbot::SpitfireADSSmooth;
			Config::Aimbot::SpitfireSmoothingMethod = Features::Aimbot::SpitfireSmoothingMethod;
			Config::Aimbot::SpitfireMinHipfireSmooth = Features::Aimbot::SpitfireMinHipfireSmooth;
			Config::Aimbot::SpitfireMaxHipfireSmooth = Features::Aimbot::SpitfireMaxHipfireSmooth;
			Config::Aimbot::SpitfireMinADSSmooth = Features::Aimbot::SpitfireMinADSSmooth;
			Config::Aimbot::SpitfireMaxADSSmooth = Features::Aimbot::SpitfireMaxADSSmooth;
			Config::Aimbot::SpitfireMinHipfireSmooth1 = Features::Aimbot::SpitfireMinHipfireSmooth1;
			Config::Aimbot::SpitfireMaxHipfireSmooth1 = Features::Aimbot::SpitfireMaxHipfireSmooth1;
			Config::Aimbot::SpitfireMinADSSmooth1 = Features::Aimbot::SpitfireMinADSSmooth1;
			Config::Aimbot::SpitfireMaxADSSmooth1 = Features::Aimbot::SpitfireMaxADSSmooth1;
			Config::Aimbot::SpitfireFOV = Features::Aimbot::SpitfireFOV;
			Config::Aimbot::SpitfireZoomScale = Features::Aimbot::SpitfireZoomScale;
			Config::Aimbot::SpitfireHipfireSmooth1 = Features::Aimbot::SpitfireHipfireSmooth1;
			Config::Aimbot::SpitfireADSSmooth1 = Features::Aimbot::SpitfireADSSmooth1;
			Config::Aimbot::SpitfireExtraSmooth1 = Features::Aimbot::SpitfireExtraSmooth1;
			Config::Aimbot::SpitfireDeadzone = Features::Aimbot::SpitfireDeadzone;
			Config::Aimbot::SpitfireFOV1 = Features::Aimbot::SpitfireFOV1;
			Config::Aimbot::SpitfireMinDistance1 = Features::Aimbot::SpitfireMinDistance1;
			Config::Aimbot::SpitfireMaxDistance1 = Features::Aimbot::SpitfireMaxDistance1;
			Config::Aimbot::G7Fire = Features::Aimbot::G7Fire;
			Config::Aimbot::G7ADS = Features::Aimbot::G7ADS;
			Config::Aimbot::G7ClosestHitbox = Features::Aimbot::G7ClosestHitbox;
			Config::Aimbot::G7Hitbox = Features::Aimbot::G7Hitbox;
			Config::Aimbot::G7Speed = Features::Aimbot::G7Speed;
			Config::Aimbot::G7HipfireSmooth = Features::Aimbot::G7HipfireSmooth;
			Config::Aimbot::G7ADSSmooth = Features::Aimbot::G7ADSSmooth;
			Config::Aimbot::G7SmoothingMethod = Features::Aimbot::G7SmoothingMethod;
			Config::Aimbot::G7MinHipfireSmooth = Features::Aimbot::G7MinHipfireSmooth;
			Config::Aimbot::G7MaxHipfireSmooth = Features::Aimbot::G7MaxHipfireSmooth;
			Config::Aimbot::G7MinADSSmooth = Features::Aimbot::G7MinADSSmooth;
			Config::Aimbot::G7MaxADSSmooth = Features::Aimbot::G7MaxADSSmooth;
			Config::Aimbot::G7MinHipfireSmooth1 = Features::Aimbot::G7MinHipfireSmooth1;
			Config::Aimbot::G7MaxHipfireSmooth1 = Features::Aimbot::G7MaxHipfireSmooth1;
			Config::Aimbot::G7MinADSSmooth1 = Features::Aimbot::G7MinADSSmooth1;
			Config::Aimbot::G7MaxADSSmooth1 = Features::Aimbot::G7MaxADSSmooth1;
			Config::Aimbot::G7FOV = Features::Aimbot::G7FOV;
			Config::Aimbot::G7ZoomScale = Features::Aimbot::G7ZoomScale;
			Config::Aimbot::G7HipfireSmooth1 = Features::Aimbot::G7HipfireSmooth1;
			Config::Aimbot::G7ADSSmooth1 = Features::Aimbot::G7ADSSmooth1;
			Config::Aimbot::G7ExtraSmooth1 = Features::Aimbot::G7ExtraSmooth1;
			Config::Aimbot::G7Deadzone = Features::Aimbot::G7Deadzone;
			Config::Aimbot::G7FOV1 = Features::Aimbot::G7FOV1;
			Config::Aimbot::G7MinDistance1 = Features::Aimbot::G7MinDistance1;
			Config::Aimbot::G7MaxDistance1 = Features::Aimbot::G7MaxDistance1;
			Config::Aimbot::FlatlineFire = Features::Aimbot::FlatlineFire;
			Config::Aimbot::FlatlineADS = Features::Aimbot::FlatlineADS;
			Config::Aimbot::FlatlineClosestHitbox = Features::Aimbot::FlatlineClosestHitbox;
			Config::Aimbot::FlatlineHitbox = Features::Aimbot::FlatlineHitbox;
			Config::Aimbot::FlatlineSpeed = Features::Aimbot::FlatlineSpeed;
			Config::Aimbot::FlatlineHipfireSmooth = Features::Aimbot::FlatlineHipfireSmooth;
			Config::Aimbot::FlatlineADSSmooth = Features::Aimbot::FlatlineADSSmooth;
			Config::Aimbot::FlatlineSmoothingMethod = Features::Aimbot::FlatlineSmoothingMethod;
			Config::Aimbot::FlatlineMinHipfireSmooth = Features::Aimbot::FlatlineMinHipfireSmooth;
			Config::Aimbot::FlatlineMaxHipfireSmooth = Features::Aimbot::FlatlineMaxHipfireSmooth;
			Config::Aimbot::FlatlineMinADSSmooth = Features::Aimbot::FlatlineMinADSSmooth;
			Config::Aimbot::FlatlineMaxADSSmooth = Features::Aimbot::FlatlineMaxADSSmooth;
			Config::Aimbot::FlatlineMinHipfireSmooth1 = Features::Aimbot::FlatlineMinHipfireSmooth1;
			Config::Aimbot::FlatlineMaxHipfireSmooth1 = Features::Aimbot::FlatlineMaxHipfireSmooth1;
			Config::Aimbot::FlatlineMinADSSmooth1 = Features::Aimbot::FlatlineMinADSSmooth1;
			Config::Aimbot::FlatlineMaxADSSmooth1 = Features::Aimbot::FlatlineMaxADSSmooth1;
			Config::Aimbot::FlatlineFOV = Features::Aimbot::FlatlineFOV;
			Config::Aimbot::FlatlineZoomScale = Features::Aimbot::FlatlineZoomScale;
			Config::Aimbot::FlatlineHipfireSmooth1 = Features::Aimbot::FlatlineHipfireSmooth1;
			Config::Aimbot::FlatlineADSSmooth1 = Features::Aimbot::FlatlineADSSmooth1;
			Config::Aimbot::FlatlineExtraSmooth1 = Features::Aimbot::FlatlineExtraSmooth1;
			Config::Aimbot::FlatlineDeadzone = Features::Aimbot::FlatlineDeadzone;
			Config::Aimbot::FlatlineFOV1 = Features::Aimbot::FlatlineFOV1;
			Config::Aimbot::FlatlineMinDistance1 = Features::Aimbot::FlatlineMinDistance1;
			Config::Aimbot::FlatlineMaxDistance1 = Features::Aimbot::FlatlineMaxDistance1;
			Config::Aimbot::HemlockFire = Features::Aimbot::HemlockFire;
			Config::Aimbot::HemlockADS = Features::Aimbot::HemlockADS;
			Config::Aimbot::HemlockClosestHitbox = Features::Aimbot::HemlockClosestHitbox;
			Config::Aimbot::HemlockHitbox = Features::Aimbot::HemlockHitbox;
			Config::Aimbot::HemlockSpeed = Features::Aimbot::HemlockSpeed;
			Config::Aimbot::HemlockHipfireSmooth = Features::Aimbot::HemlockHipfireSmooth;
			Config::Aimbot::HemlockADSSmooth = Features::Aimbot::HemlockADSSmooth;
			Config::Aimbot::HemlockSmoothingMethod = Features::Aimbot::HemlockSmoothingMethod;
			Config::Aimbot::HemlockMinHipfireSmooth = Features::Aimbot::HemlockMinHipfireSmooth;
			Config::Aimbot::HemlockMaxHipfireSmooth = Features::Aimbot::HemlockMaxHipfireSmooth;
			Config::Aimbot::HemlockMinADSSmooth = Features::Aimbot::HemlockMinADSSmooth;
			Config::Aimbot::HemlockMaxADSSmooth = Features::Aimbot::HemlockMaxADSSmooth;
			Config::Aimbot::HemlockMinHipfireSmooth1 = Features::Aimbot::HemlockMinHipfireSmooth1;
			Config::Aimbot::HemlockMaxHipfireSmooth1 = Features::Aimbot::HemlockMaxHipfireSmooth1;
			Config::Aimbot::HemlockMinADSSmooth1 = Features::Aimbot::HemlockMinADSSmooth1;
			Config::Aimbot::HemlockMaxADSSmooth1 = Features::Aimbot::HemlockMaxADSSmooth1;
			Config::Aimbot::HemlockFOV = Features::Aimbot::HemlockFOV;
			Config::Aimbot::HemlockZoomScale = Features::Aimbot::HemlockZoomScale;
			Config::Aimbot::HemlockHipfireSmooth1 = Features::Aimbot::HemlockHipfireSmooth1;
			Config::Aimbot::HemlockADSSmooth1 = Features::Aimbot::HemlockADSSmooth1;
			Config::Aimbot::HemlockExtraSmooth1 = Features::Aimbot::HemlockExtraSmooth1;
			Config::Aimbot::HemlockDeadzone = Features::Aimbot::HemlockDeadzone;
			Config::Aimbot::HemlockFOV1 = Features::Aimbot::HemlockFOV1;
			Config::Aimbot::HemlockMinDistance1 = Features::Aimbot::HemlockMinDistance1;
			Config::Aimbot::HemlockMaxDistance1 = Features::Aimbot::HemlockMaxDistance1;
			Config::Aimbot::ProwlerFire = Features::Aimbot::ProwlerFire;
			Config::Aimbot::ProwlerADS = Features::Aimbot::ProwlerADS;
			Config::Aimbot::ProwlerClosestHitbox = Features::Aimbot::ProwlerClosestHitbox;
			Config::Aimbot::ProwlerHitbox = Features::Aimbot::ProwlerHitbox;
			Config::Aimbot::ProwlerSpeed = Features::Aimbot::ProwlerSpeed;
			Config::Aimbot::ProwlerHipfireSmooth = Features::Aimbot::ProwlerHipfireSmooth;
			Config::Aimbot::ProwlerADSSmooth = Features::Aimbot::ProwlerADSSmooth;
			Config::Aimbot::ProwlerSmoothingMethod = Features::Aimbot::ProwlerSmoothingMethod;
			Config::Aimbot::ProwlerMinHipfireSmooth = Features::Aimbot::ProwlerMinHipfireSmooth;
			Config::Aimbot::ProwlerMaxHipfireSmooth = Features::Aimbot::ProwlerMaxHipfireSmooth;
			Config::Aimbot::ProwlerMinADSSmooth = Features::Aimbot::ProwlerMinADSSmooth;
			Config::Aimbot::ProwlerMaxADSSmooth = Features::Aimbot::ProwlerMaxADSSmooth;
			Config::Aimbot::ProwlerMinHipfireSmooth1 = Features::Aimbot::ProwlerMinHipfireSmooth1;
			Config::Aimbot::ProwlerMaxHipfireSmooth1 = Features::Aimbot::ProwlerMaxHipfireSmooth1;
			Config::Aimbot::ProwlerMinADSSmooth1 = Features::Aimbot::ProwlerMinADSSmooth1;
			Config::Aimbot::ProwlerMaxADSSmooth1 = Features::Aimbot::ProwlerMaxADSSmooth1;
			Config::Aimbot::ProwlerFOV = Features::Aimbot::ProwlerFOV;
			Config::Aimbot::ProwlerZoomScale = Features::Aimbot::ProwlerZoomScale;
			Config::Aimbot::ProwlerHipfireSmooth1 = Features::Aimbot::ProwlerHipfireSmooth1;
			Config::Aimbot::ProwlerADSSmooth1 = Features::Aimbot::ProwlerADSSmooth1;
			Config::Aimbot::ProwlerExtraSmooth1 = Features::Aimbot::ProwlerExtraSmooth1;
			Config::Aimbot::ProwlerDeadzone = Features::Aimbot::ProwlerDeadzone;
			Config::Aimbot::ProwlerFOV1 = Features::Aimbot::ProwlerFOV1;
			Config::Aimbot::ProwlerMinDistance1 = Features::Aimbot::ProwlerMinDistance1;
			Config::Aimbot::ProwlerMaxDistance1 = Features::Aimbot::ProwlerMaxDistance1;
			Config::Aimbot::RepeaterFire = Features::Aimbot::RepeaterFire;
			Config::Aimbot::RepeaterADS = Features::Aimbot::RepeaterADS;
			Config::Aimbot::RepeaterClosestHitbox = Features::Aimbot::RepeaterClosestHitbox;
			Config::Aimbot::RepeaterHitbox = Features::Aimbot::RepeaterHitbox;
			Config::Aimbot::RepeaterSpeed = Features::Aimbot::RepeaterSpeed;
			Config::Aimbot::RepeaterHipfireSmooth = Features::Aimbot::RepeaterHipfireSmooth;
			Config::Aimbot::RepeaterADSSmooth = Features::Aimbot::RepeaterADSSmooth;
			Config::Aimbot::RepeaterSmoothingMethod = Features::Aimbot::RepeaterSmoothingMethod;
			Config::Aimbot::RepeaterMinHipfireSmooth = Features::Aimbot::RepeaterMinHipfireSmooth;
			Config::Aimbot::RepeaterMaxHipfireSmooth = Features::Aimbot::RepeaterMaxHipfireSmooth;
			Config::Aimbot::RepeaterMinADSSmooth = Features::Aimbot::RepeaterMinADSSmooth;
			Config::Aimbot::RepeaterMaxADSSmooth = Features::Aimbot::RepeaterMaxADSSmooth;
			Config::Aimbot::RepeaterMinHipfireSmooth1 = Features::Aimbot::RepeaterMinHipfireSmooth1;
			Config::Aimbot::RepeaterMaxHipfireSmooth1 = Features::Aimbot::RepeaterMaxHipfireSmooth1;
			Config::Aimbot::RepeaterMinADSSmooth1 = Features::Aimbot::RepeaterMinADSSmooth1;
			Config::Aimbot::RepeaterMaxADSSmooth1 = Features::Aimbot::RepeaterMaxADSSmooth1;
			Config::Aimbot::RepeaterFOV = Features::Aimbot::RepeaterFOV;
			Config::Aimbot::RepeaterZoomScale = Features::Aimbot::RepeaterZoomScale;
			Config::Aimbot::RepeaterHipfireSmooth1 = Features::Aimbot::RepeaterHipfireSmooth1;
			Config::Aimbot::RepeaterADSSmooth1 = Features::Aimbot::RepeaterADSSmooth1;
			Config::Aimbot::RepeaterExtraSmooth1 = Features::Aimbot::RepeaterExtraSmooth1;
			Config::Aimbot::RepeaterDeadzone = Features::Aimbot::RepeaterDeadzone;
			Config::Aimbot::RepeaterFOV1 = Features::Aimbot::RepeaterFOV1;
			Config::Aimbot::RepeaterMinDistance1 = Features::Aimbot::RepeaterMinDistance1;
			Config::Aimbot::RepeaterMaxDistance1 = Features::Aimbot::RepeaterMaxDistance1;
			Config::Aimbot::RampageFire = Features::Aimbot::RampageFire;
			Config::Aimbot::RampageADS = Features::Aimbot::RampageADS;
			Config::Aimbot::RampageClosestHitbox = Features::Aimbot::RampageClosestHitbox;
			Config::Aimbot::RampageHitbox = Features::Aimbot::RampageHitbox;
			Config::Aimbot::RampageSpeed = Features::Aimbot::RampageSpeed;
			Config::Aimbot::RampageHipfireSmooth = Features::Aimbot::RampageHipfireSmooth;
			Config::Aimbot::RampageADSSmooth = Features::Aimbot::RampageADSSmooth;
			Config::Aimbot::RampageSmoothingMethod = Features::Aimbot::RampageSmoothingMethod;
			Config::Aimbot::RampageMinHipfireSmooth = Features::Aimbot::RampageMinHipfireSmooth;
			Config::Aimbot::RampageMaxHipfireSmooth = Features::Aimbot::RampageMaxHipfireSmooth;
			Config::Aimbot::RampageMinADSSmooth = Features::Aimbot::RampageMinADSSmooth;
			Config::Aimbot::RampageMaxADSSmooth = Features::Aimbot::RampageMaxADSSmooth;
			Config::Aimbot::RampageMinHipfireSmooth1 = Features::Aimbot::RampageMinHipfireSmooth1;
			Config::Aimbot::RampageMaxHipfireSmooth1 = Features::Aimbot::RampageMaxHipfireSmooth1;
			Config::Aimbot::RampageMinADSSmooth1 = Features::Aimbot::RampageMinADSSmooth1;
			Config::Aimbot::RampageMaxADSSmooth1 = Features::Aimbot::RampageMaxADSSmooth1;
			Config::Aimbot::RampageFOV = Features::Aimbot::RampageFOV;
			Config::Aimbot::RampageZoomScale = Features::Aimbot::RampageZoomScale;
			Config::Aimbot::RampageHipfireSmooth1 = Features::Aimbot::RampageHipfireSmooth1;
			Config::Aimbot::RampageADSSmooth1 = Features::Aimbot::RampageADSSmooth1;
			Config::Aimbot::RampageExtraSmooth1 = Features::Aimbot::RampageExtraSmooth1;
			Config::Aimbot::RampageDeadzone = Features::Aimbot::RampageDeadzone;
			Config::Aimbot::RampageFOV1 = Features::Aimbot::RampageFOV1;
			Config::Aimbot::RampageMinDistance1 = Features::Aimbot::RampageMinDistance1;
			Config::Aimbot::RampageMaxDistance1 = Features::Aimbot::RampageMaxDistance1;
			Config::Aimbot::CARSMGFire = Features::Aimbot::CARSMGFire;
			Config::Aimbot::CARSMGADS = Features::Aimbot::CARSMGADS;
			Config::Aimbot::CARSMGClosestHitbox = Features::Aimbot::CARSMGClosestHitbox;
			Config::Aimbot::CARSMGHitbox = Features::Aimbot::CARSMGHitbox;
			Config::Aimbot::CARSMGSpeed = Features::Aimbot::CARSMGSpeed;
			Config::Aimbot::CARSMGHipfireSmooth = Features::Aimbot::CARSMGHipfireSmooth;
			Config::Aimbot::CARSMGADSSmooth = Features::Aimbot::CARSMGADSSmooth;
			Config::Aimbot::CARSMGSmoothingMethod = Features::Aimbot::CARSMGSmoothingMethod;
			Config::Aimbot::CARSMGMinHipfireSmooth = Features::Aimbot::CARSMGMinHipfireSmooth;
			Config::Aimbot::CARSMGMaxHipfireSmooth = Features::Aimbot::CARSMGMaxHipfireSmooth;
			Config::Aimbot::CARSMGMinADSSmooth = Features::Aimbot::CARSMGMinADSSmooth;
			Config::Aimbot::CARSMGMaxADSSmooth = Features::Aimbot::CARSMGMaxADSSmooth;
			Config::Aimbot::CARSMGMinHipfireSmooth1 = Features::Aimbot::CARSMGMinHipfireSmooth1;
			Config::Aimbot::CARSMGMaxHipfireSmooth1 = Features::Aimbot::CARSMGMaxHipfireSmooth1;
			Config::Aimbot::CARSMGMinADSSmooth1 = Features::Aimbot::CARSMGMinADSSmooth1;
			Config::Aimbot::CARSMGMaxADSSmooth1 = Features::Aimbot::CARSMGMaxADSSmooth1;
			Config::Aimbot::CARSMGFOV = Features::Aimbot::CARSMGFOV;
			Config::Aimbot::CARSMGZoomScale = Features::Aimbot::CARSMGZoomScale;
			Config::Aimbot::CARSMGHipfireSmooth1 = Features::Aimbot::CARSMGHipfireSmooth1;
			Config::Aimbot::CARSMGADSSmooth1 = Features::Aimbot::CARSMGADSSmooth1;
			Config::Aimbot::CARSMGExtraSmooth1 = Features::Aimbot::CARSMGExtraSmooth1;
			Config::Aimbot::CARSMGDeadzone = Features::Aimbot::CARSMGDeadzone;
			Config::Aimbot::CARSMGFOV1 = Features::Aimbot::CARSMGFOV1;
			Config::Aimbot::CARSMGMinDistance1 = Features::Aimbot::CARSMGMinDistance1;
			Config::Aimbot::CARSMGMaxDistance1 = Features::Aimbot::CARSMGMaxDistance1;
			Config::Aimbot::HavocFire = Features::Aimbot::HavocFire;
			Config::Aimbot::HavocADS = Features::Aimbot::HavocADS;
			Config::Aimbot::HavocClosestHitbox = Features::Aimbot::HavocClosestHitbox;
			Config::Aimbot::HavocHitbox = Features::Aimbot::HavocHitbox;
			Config::Aimbot::HavocSpeed = Features::Aimbot::HavocSpeed;
			Config::Aimbot::HavocHipfireSmooth = Features::Aimbot::HavocHipfireSmooth;
			Config::Aimbot::HavocADSSmooth = Features::Aimbot::HavocADSSmooth;
			Config::Aimbot::HavocSmoothingMethod = Features::Aimbot::HavocSmoothingMethod;
			Config::Aimbot::HavocMinHipfireSmooth = Features::Aimbot::HavocMinHipfireSmooth;
			Config::Aimbot::HavocMaxHipfireSmooth = Features::Aimbot::HavocMaxHipfireSmooth;
			Config::Aimbot::HavocMinADSSmooth = Features::Aimbot::HavocMinADSSmooth;
			Config::Aimbot::HavocMaxADSSmooth = Features::Aimbot::HavocMaxADSSmooth;
			Config::Aimbot::HavocMinHipfireSmooth1 = Features::Aimbot::HavocMinHipfireSmooth1;
			Config::Aimbot::HavocMaxHipfireSmooth1 = Features::Aimbot::HavocMaxHipfireSmooth1;
			Config::Aimbot::HavocMinADSSmooth1 = Features::Aimbot::HavocMinADSSmooth1;
			Config::Aimbot::HavocMaxADSSmooth1 = Features::Aimbot::HavocMaxADSSmooth1;
			Config::Aimbot::HavocFOV = Features::Aimbot::HavocFOV;
			Config::Aimbot::HavocZoomScale = Features::Aimbot::HavocZoomScale;
			Config::Aimbot::HavocHipfireSmooth1 = Features::Aimbot::HavocHipfireSmooth1;
			Config::Aimbot::HavocADSSmooth1 = Features::Aimbot::HavocADSSmooth1;
			Config::Aimbot::HavocExtraSmooth1 = Features::Aimbot::HavocExtraSmooth1;
			Config::Aimbot::HavocDeadzone = Features::Aimbot::HavocDeadzone;
			Config::Aimbot::HavocFOV1 = Features::Aimbot::HavocFOV1;
			Config::Aimbot::HavocMinDistance1 = Features::Aimbot::HavocMinDistance1;
			Config::Aimbot::HavocMaxDistance1 = Features::Aimbot::HavocMaxDistance1;
			Config::Aimbot::DevotionFire = Features::Aimbot::DevotionFire;
			Config::Aimbot::DevotionADS = Features::Aimbot::DevotionADS;
			Config::Aimbot::DevotionClosestHitbox = Features::Aimbot::DevotionClosestHitbox;
			Config::Aimbot::DevotionHitbox = Features::Aimbot::DevotionHitbox;
			Config::Aimbot::DevotionSpeed = Features::Aimbot::DevotionSpeed;
			Config::Aimbot::DevotionHipfireSmooth = Features::Aimbot::DevotionHipfireSmooth;
			Config::Aimbot::DevotionADSSmooth = Features::Aimbot::DevotionADSSmooth;
			Config::Aimbot::DevotionSmoothingMethod = Features::Aimbot::DevotionSmoothingMethod;
			Config::Aimbot::DevotionMinHipfireSmooth = Features::Aimbot::DevotionMinHipfireSmooth;
			Config::Aimbot::DevotionMaxHipfireSmooth = Features::Aimbot::DevotionMaxHipfireSmooth;
			Config::Aimbot::DevotionMinADSSmooth = Features::Aimbot::DevotionMinADSSmooth;
			Config::Aimbot::DevotionMaxADSSmooth = Features::Aimbot::DevotionMaxADSSmooth;
			Config::Aimbot::DevotionMinHipfireSmooth1 = Features::Aimbot::DevotionMinHipfireSmooth1;
			Config::Aimbot::DevotionMaxHipfireSmooth1 = Features::Aimbot::DevotionMaxHipfireSmooth1;
			Config::Aimbot::DevotionMinADSSmooth1 = Features::Aimbot::DevotionMinADSSmooth1;
			Config::Aimbot::DevotionMaxADSSmooth1 = Features::Aimbot::DevotionMaxADSSmooth1;
			Config::Aimbot::DevotionFOV = Features::Aimbot::DevotionFOV;
			Config::Aimbot::DevotionZoomScale = Features::Aimbot::DevotionZoomScale;
			Config::Aimbot::DevotionHipfireSmooth1 = Features::Aimbot::DevotionHipfireSmooth1;
			Config::Aimbot::DevotionADSSmooth1 = Features::Aimbot::DevotionADSSmooth1;
			Config::Aimbot::DevotionExtraSmooth1 = Features::Aimbot::DevotionExtraSmooth1;
			Config::Aimbot::DevotionDeadzone = Features::Aimbot::DevotionDeadzone;
			Config::Aimbot::DevotionFOV1 = Features::Aimbot::DevotionFOV1;
			Config::Aimbot::DevotionMinDistance1 = Features::Aimbot::DevotionMinDistance1;
			Config::Aimbot::DevotionMaxDistance1 = Features::Aimbot::DevotionMaxDistance1;
			Config::Aimbot::LSTARFire = Features::Aimbot::LSTARFire;
			Config::Aimbot::LSTARADS = Features::Aimbot::LSTARADS;
			Config::Aimbot::LSTARClosestHitbox = Features::Aimbot::LSTARClosestHitbox;
			Config::Aimbot::LSTARHitbox = Features::Aimbot::LSTARHitbox;
			Config::Aimbot::LSTARSpeed = Features::Aimbot::LSTARSpeed;
			Config::Aimbot::LSTARHipfireSmooth = Features::Aimbot::LSTARHipfireSmooth;
			Config::Aimbot::LSTARADSSmooth = Features::Aimbot::LSTARADSSmooth;
			Config::Aimbot::LSTARSmoothingMethod = Features::Aimbot::LSTARSmoothingMethod;
			Config::Aimbot::LSTARMinHipfireSmooth = Features::Aimbot::LSTARMinHipfireSmooth;
			Config::Aimbot::LSTARMaxHipfireSmooth = Features::Aimbot::LSTARMaxHipfireSmooth;
			Config::Aimbot::LSTARMinADSSmooth = Features::Aimbot::LSTARMinADSSmooth;
			Config::Aimbot::LSTARMaxADSSmooth = Features::Aimbot::LSTARMaxADSSmooth;
			Config::Aimbot::LSTARMinHipfireSmooth1 = Features::Aimbot::LSTARMinHipfireSmooth1;
			Config::Aimbot::LSTARMaxHipfireSmooth1 = Features::Aimbot::LSTARMaxHipfireSmooth1;
			Config::Aimbot::LSTARMinADSSmooth1 = Features::Aimbot::LSTARMinADSSmooth1;
			Config::Aimbot::LSTARMaxADSSmooth1 = Features::Aimbot::LSTARMaxADSSmooth1;
			Config::Aimbot::LSTARFOV = Features::Aimbot::LSTARFOV;
			Config::Aimbot::LSTARZoomScale = Features::Aimbot::LSTARZoomScale;
			Config::Aimbot::LSTARHipfireSmooth1 = Features::Aimbot::LSTARHipfireSmooth1;
			Config::Aimbot::LSTARADSSmooth1 = Features::Aimbot::LSTARADSSmooth1;
			Config::Aimbot::LSTARExtraSmooth1 = Features::Aimbot::LSTARExtraSmooth1;
			Config::Aimbot::LSTARDeadzone = Features::Aimbot::LSTARDeadzone;
			Config::Aimbot::LSTARFOV1 = Features::Aimbot::LSTARFOV1;
			Config::Aimbot::LSTARMinDistance1 = Features::Aimbot::LSTARMinDistance1;
			Config::Aimbot::LSTARMaxDistance1 = Features::Aimbot::LSTARMaxDistance1;
			Config::Aimbot::TripleTakeFire = Features::Aimbot::TripleTakeFire;
			Config::Aimbot::TripleTakeADS = Features::Aimbot::TripleTakeADS;
			Config::Aimbot::TripleTakeClosestHitbox = Features::Aimbot::TripleTakeClosestHitbox;
			Config::Aimbot::TripleTakeHitbox = Features::Aimbot::TripleTakeHitbox;
			Config::Aimbot::TripleTakeSpeed = Features::Aimbot::TripleTakeSpeed;
			Config::Aimbot::TripleTakeHipfireSmooth = Features::Aimbot::TripleTakeHipfireSmooth;
			Config::Aimbot::TripleTakeADSSmooth = Features::Aimbot::TripleTakeADSSmooth;
			Config::Aimbot::TripleTakeSmoothingMethod = Features::Aimbot::TripleTakeSmoothingMethod;
			Config::Aimbot::TripleTakeMinHipfireSmooth = Features::Aimbot::TripleTakeMinHipfireSmooth;
			Config::Aimbot::TripleTakeMaxHipfireSmooth = Features::Aimbot::TripleTakeMaxHipfireSmooth;
			Config::Aimbot::TripleTakeMinADSSmooth = Features::Aimbot::TripleTakeMinADSSmooth;
			Config::Aimbot::TripleTakeMaxADSSmooth = Features::Aimbot::TripleTakeMaxADSSmooth;
			Config::Aimbot::TripleTakeMinHipfireSmooth1 = Features::Aimbot::TripleTakeMinHipfireSmooth1;
			Config::Aimbot::TripleTakeMaxHipfireSmooth1 = Features::Aimbot::TripleTakeMaxHipfireSmooth1;
			Config::Aimbot::TripleTakeMinADSSmooth1 = Features::Aimbot::TripleTakeMinADSSmooth1;
			Config::Aimbot::TripleTakeMaxADSSmooth1 = Features::Aimbot::TripleTakeMaxADSSmooth1;
			Config::Aimbot::TripleTakeFOV = Features::Aimbot::TripleTakeFOV;
			Config::Aimbot::TripleTakeZoomScale = Features::Aimbot::TripleTakeZoomScale;
			Config::Aimbot::TripleTakeHipfireSmooth1 = Features::Aimbot::TripleTakeHipfireSmooth1;
			Config::Aimbot::TripleTakeADSSmooth1 = Features::Aimbot::TripleTakeADSSmooth1;
			Config::Aimbot::TripleTakeExtraSmooth1 = Features::Aimbot::TripleTakeExtraSmooth1;
			Config::Aimbot::TripleTakeDeadzone = Features::Aimbot::TripleTakeDeadzone;
			Config::Aimbot::TripleTakeFOV1 = Features::Aimbot::TripleTakeFOV1;
			Config::Aimbot::TripleTakeMinDistance1 = Features::Aimbot::TripleTakeMinDistance1;
			Config::Aimbot::TripleTakeMaxDistance1 = Features::Aimbot::TripleTakeMaxDistance1;
			Config::Aimbot::VoltFire = Features::Aimbot::VoltFire;
			Config::Aimbot::VoltADS = Features::Aimbot::VoltADS;
			Config::Aimbot::VoltClosestHitbox = Features::Aimbot::VoltClosestHitbox;
			Config::Aimbot::VoltHitbox = Features::Aimbot::VoltHitbox;
			Config::Aimbot::VoltSpeed = Features::Aimbot::VoltSpeed;
			Config::Aimbot::VoltHipfireSmooth = Features::Aimbot::VoltHipfireSmooth;
			Config::Aimbot::VoltADSSmooth = Features::Aimbot::VoltADSSmooth;
			Config::Aimbot::VoltSmoothingMethod = Features::Aimbot::VoltSmoothingMethod;
			Config::Aimbot::VoltMinHipfireSmooth = Features::Aimbot::VoltMinHipfireSmooth;
			Config::Aimbot::VoltMaxHipfireSmooth = Features::Aimbot::VoltMaxHipfireSmooth;
			Config::Aimbot::VoltMinADSSmooth = Features::Aimbot::VoltMinADSSmooth;
			Config::Aimbot::VoltMaxADSSmooth = Features::Aimbot::VoltMaxADSSmooth;
			Config::Aimbot::VoltMinHipfireSmooth1 = Features::Aimbot::VoltMinHipfireSmooth1;
			Config::Aimbot::VoltMaxHipfireSmooth1 = Features::Aimbot::VoltMaxHipfireSmooth1;
			Config::Aimbot::VoltMinADSSmooth1 = Features::Aimbot::VoltMinADSSmooth1;
			Config::Aimbot::VoltMaxADSSmooth1 = Features::Aimbot::VoltMaxADSSmooth1;
			Config::Aimbot::VoltFOV = Features::Aimbot::VoltFOV;
			Config::Aimbot::VoltZoomScale = Features::Aimbot::VoltZoomScale;
			Config::Aimbot::VoltHipfireSmooth1 = Features::Aimbot::VoltHipfireSmooth1;
			Config::Aimbot::VoltADSSmooth1 = Features::Aimbot::VoltADSSmooth1;
			Config::Aimbot::VoltExtraSmooth1 = Features::Aimbot::VoltExtraSmooth1;
			Config::Aimbot::VoltDeadzone = Features::Aimbot::VoltDeadzone;
			Config::Aimbot::VoltFOV1 = Features::Aimbot::VoltFOV1;
			Config::Aimbot::VoltMinDistance1 = Features::Aimbot::VoltMinDistance1;
			Config::Aimbot::VoltMaxDistance1 = Features::Aimbot::VoltMaxDistance1;
			Config::Aimbot::NemesisFire = Features::Aimbot::NemesisFire;
			Config::Aimbot::NemesisADS = Features::Aimbot::NemesisADS;
			Config::Aimbot::NemesisClosestHitbox = Features::Aimbot::NemesisClosestHitbox;
			Config::Aimbot::NemesisHitbox = Features::Aimbot::NemesisHitbox;
			Config::Aimbot::NemesisSpeed = Features::Aimbot::NemesisSpeed;
			Config::Aimbot::NemesisHipfireSmooth = Features::Aimbot::NemesisHipfireSmooth;
			Config::Aimbot::NemesisADSSmooth = Features::Aimbot::NemesisADSSmooth;
			Config::Aimbot::NemesisSmoothingMethod = Features::Aimbot::NemesisSmoothingMethod;
			Config::Aimbot::NemesisMinHipfireSmooth = Features::Aimbot::NemesisMinHipfireSmooth;
			Config::Aimbot::NemesisMaxHipfireSmooth = Features::Aimbot::NemesisMaxHipfireSmooth;
			Config::Aimbot::NemesisMinADSSmooth = Features::Aimbot::NemesisMinADSSmooth;
			Config::Aimbot::NemesisMaxADSSmooth = Features::Aimbot::NemesisMaxADSSmooth;
			Config::Aimbot::NemesisMinHipfireSmooth1 = Features::Aimbot::NemesisMinHipfireSmooth1;
			Config::Aimbot::NemesisMaxHipfireSmooth1 = Features::Aimbot::NemesisMaxHipfireSmooth1;
			Config::Aimbot::NemesisMinADSSmooth1 = Features::Aimbot::NemesisMinADSSmooth1;
			Config::Aimbot::NemesisMaxADSSmooth1 = Features::Aimbot::NemesisMaxADSSmooth1;
			Config::Aimbot::NemesisFOV = Features::Aimbot::NemesisFOV;
			Config::Aimbot::NemesisZoomScale = Features::Aimbot::NemesisZoomScale;
			Config::Aimbot::NemesisHipfireSmooth1 = Features::Aimbot::NemesisHipfireSmooth1;
			Config::Aimbot::NemesisADSSmooth1 = Features::Aimbot::NemesisADSSmooth1;
			Config::Aimbot::NemesisExtraSmooth1 = Features::Aimbot::NemesisExtraSmooth1;
			Config::Aimbot::NemesisDeadzone = Features::Aimbot::NemesisDeadzone;
			Config::Aimbot::NemesisFOV1 = Features::Aimbot::NemesisFOV1;
			Config::Aimbot::NemesisMinDistance1 = Features::Aimbot::NemesisMinDistance1;
			Config::Aimbot::NemesisMaxDistance1 = Features::Aimbot::NemesisMaxDistance1;
			Config::Aimbot::MozambiqueFire = Features::Aimbot::MozambiqueFire;
			Config::Aimbot::MozambiqueADS = Features::Aimbot::MozambiqueADS;
			Config::Aimbot::MozambiqueClosestHitbox = Features::Aimbot::MozambiqueClosestHitbox;
			Config::Aimbot::MozambiqueHitbox = Features::Aimbot::MozambiqueHitbox;
			Config::Aimbot::MozambiqueSpeed = Features::Aimbot::MozambiqueSpeed;
			Config::Aimbot::MozambiqueHipfireSmooth = Features::Aimbot::MozambiqueHipfireSmooth;
			Config::Aimbot::MozambiqueADSSmooth = Features::Aimbot::MozambiqueADSSmooth;
			Config::Aimbot::MozambiqueSmoothingMethod = Features::Aimbot::MozambiqueSmoothingMethod;
			Config::Aimbot::MozambiqueMinHipfireSmooth = Features::Aimbot::MozambiqueMinHipfireSmooth;
			Config::Aimbot::MozambiqueMaxHipfireSmooth = Features::Aimbot::MozambiqueMaxHipfireSmooth;
			Config::Aimbot::MozambiqueMinADSSmooth = Features::Aimbot::MozambiqueMinADSSmooth;
			Config::Aimbot::MozambiqueMaxADSSmooth = Features::Aimbot::MozambiqueMaxADSSmooth;
			Config::Aimbot::MozambiqueMinHipfireSmooth1 = Features::Aimbot::MozambiqueMinHipfireSmooth1;
			Config::Aimbot::MozambiqueMaxHipfireSmooth1 = Features::Aimbot::MozambiqueMaxHipfireSmooth1;
			Config::Aimbot::MozambiqueMinADSSmooth1 = Features::Aimbot::MozambiqueMinADSSmooth1;
			Config::Aimbot::MozambiqueMaxADSSmooth1 = Features::Aimbot::MozambiqueMaxADSSmooth1;
			Config::Aimbot::MozambiqueFOV = Features::Aimbot::MozambiqueFOV;
			Config::Aimbot::MozambiqueZoomScale = Features::Aimbot::MozambiqueZoomScale;
			Config::Aimbot::MozambiqueHipfireSmooth1 = Features::Aimbot::MozambiqueHipfireSmooth1;
			Config::Aimbot::MozambiqueADSSmooth1 = Features::Aimbot::MozambiqueADSSmooth1;
			Config::Aimbot::MozambiqueExtraSmooth1 = Features::Aimbot::MozambiqueExtraSmooth1;
			Config::Aimbot::MozambiqueDeadzone = Features::Aimbot::MozambiqueDeadzone;
			Config::Aimbot::MozambiqueFOV1 = Features::Aimbot::MozambiqueFOV1;
			Config::Aimbot::MozambiqueMinDistance1 = Features::Aimbot::MozambiqueMinDistance1;
			Config::Aimbot::MozambiqueMaxDistance1 = Features::Aimbot::MozambiqueMaxDistance1;
			Config::Aimbot::PeacekeeperFire = Features::Aimbot::PeacekeeperFire;
			Config::Aimbot::PeacekeeperADS = Features::Aimbot::PeacekeeperADS;
			Config::Aimbot::PeacekeeperClosestHitbox = Features::Aimbot::PeacekeeperClosestHitbox;
			Config::Aimbot::PeacekeeperHitbox = Features::Aimbot::PeacekeeperHitbox;
			Config::Aimbot::PeacekeeperSpeed = Features::Aimbot::PeacekeeperSpeed;
			Config::Aimbot::PeacekeeperHipfireSmooth = Features::Aimbot::PeacekeeperHipfireSmooth;
			Config::Aimbot::PeacekeeperADSSmooth = Features::Aimbot::PeacekeeperADSSmooth;
			Config::Aimbot::PeacekeeperSmoothingMethod = Features::Aimbot::PeacekeeperSmoothingMethod;
			Config::Aimbot::PeacekeeperMinHipfireSmooth = Features::Aimbot::PeacekeeperMinHipfireSmooth;
			Config::Aimbot::PeacekeeperMaxHipfireSmooth = Features::Aimbot::PeacekeeperMaxHipfireSmooth;
			Config::Aimbot::PeacekeeperMinADSSmooth = Features::Aimbot::PeacekeeperMinADSSmooth;
			Config::Aimbot::PeacekeeperMaxADSSmooth = Features::Aimbot::PeacekeeperMaxADSSmooth;
			Config::Aimbot::PeacekeeperMinHipfireSmooth1 = Features::Aimbot::PeacekeeperMinHipfireSmooth1;
			Config::Aimbot::PeacekeeperMaxHipfireSmooth1 = Features::Aimbot::PeacekeeperMaxHipfireSmooth1;
			Config::Aimbot::PeacekeeperMinADSSmooth1 = Features::Aimbot::PeacekeeperMinADSSmooth1;
			Config::Aimbot::PeacekeeperMaxADSSmooth1 = Features::Aimbot::PeacekeeperMaxADSSmooth1;
			Config::Aimbot::PeacekeeperFOV = Features::Aimbot::PeacekeeperFOV;
			Config::Aimbot::PeacekeeperZoomScale = Features::Aimbot::PeacekeeperZoomScale;
			Config::Aimbot::PeacekeeperHipfireSmooth1 = Features::Aimbot::PeacekeeperHipfireSmooth1;
			Config::Aimbot::PeacekeeperADSSmooth1 = Features::Aimbot::PeacekeeperADSSmooth1;
			Config::Aimbot::PeacekeeperExtraSmooth1 = Features::Aimbot::PeacekeeperExtraSmooth1;
			Config::Aimbot::PeacekeeperDeadzone = Features::Aimbot::PeacekeeperDeadzone;
			Config::Aimbot::PeacekeeperFOV1 = Features::Aimbot::PeacekeeperFOV1;
			Config::Aimbot::PeacekeeperMinDistance1 = Features::Aimbot::PeacekeeperMinDistance1;
			Config::Aimbot::PeacekeeperMaxDistance1 = Features::Aimbot::PeacekeeperMaxDistance1;
			Config::Aimbot::MastiffFire = Features::Aimbot::MastiffFire;
			Config::Aimbot::MastiffADS = Features::Aimbot::MastiffADS;
			Config::Aimbot::MastiffClosestHitbox = Features::Aimbot::MastiffClosestHitbox;
			Config::Aimbot::MastiffHitbox = Features::Aimbot::MastiffHitbox;
			Config::Aimbot::MastiffSpeed = Features::Aimbot::MastiffSpeed;
			Config::Aimbot::MastiffHipfireSmooth = Features::Aimbot::MastiffHipfireSmooth;
			Config::Aimbot::MastiffADSSmooth = Features::Aimbot::MastiffADSSmooth;
			Config::Aimbot::MastiffSmoothingMethod = Features::Aimbot::MastiffSmoothingMethod;
			Config::Aimbot::MastiffMinHipfireSmooth = Features::Aimbot::MastiffMinHipfireSmooth;
			Config::Aimbot::MastiffMaxHipfireSmooth = Features::Aimbot::MastiffMaxHipfireSmooth;
			Config::Aimbot::MastiffMinADSSmooth = Features::Aimbot::MastiffMinADSSmooth;
			Config::Aimbot::MastiffMaxADSSmooth = Features::Aimbot::MastiffMaxADSSmooth;
			Config::Aimbot::MastiffMinHipfireSmooth1 = Features::Aimbot::MastiffMinHipfireSmooth1;
			Config::Aimbot::MastiffMaxHipfireSmooth1 = Features::Aimbot::MastiffMaxHipfireSmooth1;
			Config::Aimbot::MastiffMinADSSmooth1 = Features::Aimbot::MastiffMinADSSmooth1;
			Config::Aimbot::MastiffMaxADSSmooth1 = Features::Aimbot::MastiffMaxADSSmooth1;
			Config::Aimbot::MastiffFOV = Features::Aimbot::MastiffFOV;
			Config::Aimbot::MastiffZoomScale = Features::Aimbot::MastiffZoomScale;
			Config::Aimbot::MastiffHipfireSmooth1 = Features::Aimbot::MastiffHipfireSmooth1;
			Config::Aimbot::MastiffADSSmooth1 = Features::Aimbot::MastiffADSSmooth1;
			Config::Aimbot::MastiffExtraSmooth1 = Features::Aimbot::MastiffExtraSmooth1;
			Config::Aimbot::MastiffDeadzone = Features::Aimbot::MastiffDeadzone;
			Config::Aimbot::MastiffFOV1 = Features::Aimbot::MastiffFOV1;
			Config::Aimbot::MastiffMinDistance1 = Features::Aimbot::MastiffMinDistance1;
			Config::Aimbot::MastiffMaxDistance1 = Features::Aimbot::MastiffMaxDistance1;
			Config::Aimbot::LongbowFire = Features::Aimbot::LongbowFire;
			Config::Aimbot::LongbowADS = Features::Aimbot::LongbowADS;
			Config::Aimbot::LongbowClosestHitbox = Features::Aimbot::LongbowClosestHitbox;
			Config::Aimbot::LongbowHitbox = Features::Aimbot::LongbowHitbox;
			Config::Aimbot::LongbowSpeed = Features::Aimbot::LongbowSpeed;
			Config::Aimbot::LongbowHipfireSmooth = Features::Aimbot::LongbowHipfireSmooth;
			Config::Aimbot::LongbowADSSmooth = Features::Aimbot::LongbowADSSmooth;
			Config::Aimbot::LongbowSmoothingMethod = Features::Aimbot::LongbowSmoothingMethod;
			Config::Aimbot::LongbowMinHipfireSmooth = Features::Aimbot::LongbowMinHipfireSmooth;
			Config::Aimbot::LongbowMaxHipfireSmooth = Features::Aimbot::LongbowMaxHipfireSmooth;
			Config::Aimbot::LongbowMinADSSmooth = Features::Aimbot::LongbowMinADSSmooth;
			Config::Aimbot::LongbowMaxADSSmooth = Features::Aimbot::LongbowMaxADSSmooth;
			Config::Aimbot::LongbowMinHipfireSmooth1 = Features::Aimbot::LongbowMinHipfireSmooth1;
			Config::Aimbot::LongbowMaxHipfireSmooth1 = Features::Aimbot::LongbowMaxHipfireSmooth1;
			Config::Aimbot::LongbowMinADSSmooth1 = Features::Aimbot::LongbowMinADSSmooth1;
			Config::Aimbot::LongbowMaxADSSmooth1 = Features::Aimbot::LongbowMaxADSSmooth1;
			Config::Aimbot::LongbowFOV = Features::Aimbot::LongbowFOV;
			Config::Aimbot::LongbowZoomScale = Features::Aimbot::LongbowZoomScale;
			Config::Aimbot::LongbowHipfireSmooth1 = Features::Aimbot::LongbowHipfireSmooth1;
			Config::Aimbot::LongbowADSSmooth1 = Features::Aimbot::LongbowADSSmooth1;
			Config::Aimbot::LongbowExtraSmooth1 = Features::Aimbot::LongbowExtraSmooth1;
			Config::Aimbot::LongbowDeadzone = Features::Aimbot::LongbowDeadzone;
			Config::Aimbot::LongbowFOV1 = Features::Aimbot::LongbowFOV1;
			Config::Aimbot::LongbowMinDistance1 = Features::Aimbot::LongbowMinDistance1;
			Config::Aimbot::LongbowMaxDistance1 = Features::Aimbot::LongbowMaxDistance1;
			Config::Aimbot::ChargeRifleFire = Features::Aimbot::ChargeRifleFire;
			Config::Aimbot::ChargeRifleADS = Features::Aimbot::ChargeRifleADS;
			Config::Aimbot::ChargeRifleClosestHitbox = Features::Aimbot::ChargeRifleClosestHitbox;
			Config::Aimbot::ChargeRifleHitbox = Features::Aimbot::ChargeRifleHitbox;
			Config::Aimbot::ChargeRifleSpeed = Features::Aimbot::ChargeRifleSpeed;
			Config::Aimbot::ChargeRifleHipfireSmooth = Features::Aimbot::ChargeRifleHipfireSmooth;
			Config::Aimbot::ChargeRifleADSSmooth = Features::Aimbot::ChargeRifleADSSmooth;
			Config::Aimbot::ChargeRifleSmoothingMethod = Features::Aimbot::ChargeRifleSmoothingMethod;
			Config::Aimbot::ChargeRifleMinHipfireSmooth = Features::Aimbot::ChargeRifleMinHipfireSmooth;
			Config::Aimbot::ChargeRifleMaxHipfireSmooth = Features::Aimbot::ChargeRifleMaxHipfireSmooth;
			Config::Aimbot::ChargeRifleMinADSSmooth = Features::Aimbot::ChargeRifleMinADSSmooth;
			Config::Aimbot::ChargeRifleMaxADSSmooth = Features::Aimbot::ChargeRifleMaxADSSmooth;
			Config::Aimbot::ChargeRifleMinHipfireSmooth1 = Features::Aimbot::ChargeRifleMinHipfireSmooth1;
			Config::Aimbot::ChargeRifleMaxHipfireSmooth1 = Features::Aimbot::ChargeRifleMaxHipfireSmooth1;
			Config::Aimbot::ChargeRifleMinADSSmooth1 = Features::Aimbot::ChargeRifleMinADSSmooth1;
			Config::Aimbot::ChargeRifleMaxADSSmooth1 = Features::Aimbot::ChargeRifleMaxADSSmooth1;
			Config::Aimbot::ChargeRifleFOV = Features::Aimbot::ChargeRifleFOV;
			Config::Aimbot::ChargeRifleZoomScale = Features::Aimbot::ChargeRifleZoomScale;
			Config::Aimbot::ChargeRifleHipfireSmooth1 = Features::Aimbot::ChargeRifleHipfireSmooth1;
			Config::Aimbot::ChargeRifleADSSmooth1 = Features::Aimbot::ChargeRifleADSSmooth1;
			Config::Aimbot::ChargeRifleExtraSmooth1 = Features::Aimbot::ChargeRifleExtraSmooth1;
			Config::Aimbot::ChargeRifleDeadzone = Features::Aimbot::ChargeRifleDeadzone;
			Config::Aimbot::ChargeRifleFOV1 = Features::Aimbot::ChargeRifleFOV1;
			Config::Aimbot::ChargeRifleMinDistance1 = Features::Aimbot::ChargeRifleMinDistance1;
			Config::Aimbot::ChargeRifleMaxDistance1 = Features::Aimbot::ChargeRifleMaxDistance1;
			Config::Aimbot::SentinelFire = Features::Aimbot::SentinelFire;
			Config::Aimbot::SentinelADS = Features::Aimbot::SentinelADS;
			Config::Aimbot::SentinelClosestHitbox = Features::Aimbot::SentinelClosestHitbox;
			Config::Aimbot::SentinelHitbox = Features::Aimbot::SentinelHitbox;
			Config::Aimbot::SentinelSpeed = Features::Aimbot::SentinelSpeed;
			Config::Aimbot::SentinelHipfireSmooth = Features::Aimbot::SentinelHipfireSmooth;
			Config::Aimbot::SentinelADSSmooth = Features::Aimbot::SentinelADSSmooth;
			Config::Aimbot::SentinelSmoothingMethod = Features::Aimbot::SentinelSmoothingMethod;
			Config::Aimbot::SentinelMinHipfireSmooth = Features::Aimbot::SentinelMinHipfireSmooth;
			Config::Aimbot::SentinelMaxHipfireSmooth = Features::Aimbot::SentinelMaxHipfireSmooth;
			Config::Aimbot::SentinelMinADSSmooth = Features::Aimbot::SentinelMinADSSmooth;
			Config::Aimbot::SentinelMaxADSSmooth = Features::Aimbot::SentinelMaxADSSmooth;
			Config::Aimbot::SentinelMinHipfireSmooth1 = Features::Aimbot::SentinelMinHipfireSmooth1;
			Config::Aimbot::SentinelMaxHipfireSmooth1 = Features::Aimbot::SentinelMaxHipfireSmooth1;
			Config::Aimbot::SentinelMinADSSmooth1 = Features::Aimbot::SentinelMinADSSmooth1;
			Config::Aimbot::SentinelMaxADSSmooth1 = Features::Aimbot::SentinelMaxADSSmooth1;
			Config::Aimbot::SentinelFOV = Features::Aimbot::SentinelFOV;
			Config::Aimbot::SentinelZoomScale = Features::Aimbot::SentinelZoomScale;
			Config::Aimbot::SentinelHipfireSmooth1 = Features::Aimbot::SentinelHipfireSmooth1;
			Config::Aimbot::SentinelADSSmooth1 = Features::Aimbot::SentinelADSSmooth1;
			Config::Aimbot::SentinelExtraSmooth1 = Features::Aimbot::SentinelExtraSmooth1;
			Config::Aimbot::SentinelDeadzone = Features::Aimbot::SentinelDeadzone;
			Config::Aimbot::SentinelFOV1 = Features::Aimbot::SentinelFOV1;
			Config::Aimbot::SentinelMinDistance1 = Features::Aimbot::SentinelMinDistance1;
			Config::Aimbot::SentinelMaxDistance1 = Features::Aimbot::SentinelMaxDistance1;
			Config::Aimbot::WingmanFire = Features::Aimbot::WingmanFire;
			Config::Aimbot::WingmanADS = Features::Aimbot::WingmanADS;
			Config::Aimbot::WingmanClosestHitbox = Features::Aimbot::WingmanClosestHitbox;
			Config::Aimbot::WingmanHitbox = Features::Aimbot::WingmanHitbox;
			Config::Aimbot::WingmanSpeed = Features::Aimbot::WingmanSpeed;
			Config::Aimbot::WingmanHipfireSmooth = Features::Aimbot::WingmanHipfireSmooth;
			Config::Aimbot::WingmanADSSmooth = Features::Aimbot::WingmanADSSmooth;
			Config::Aimbot::WingmanSmoothingMethod = Features::Aimbot::WingmanSmoothingMethod;
			Config::Aimbot::WingmanMinHipfireSmooth = Features::Aimbot::WingmanMinHipfireSmooth;
			Config::Aimbot::WingmanMaxHipfireSmooth = Features::Aimbot::WingmanMaxHipfireSmooth;
			Config::Aimbot::WingmanMinADSSmooth = Features::Aimbot::WingmanMinADSSmooth;
			Config::Aimbot::WingmanMaxADSSmooth = Features::Aimbot::WingmanMaxADSSmooth;
			Config::Aimbot::WingmanMinHipfireSmooth1 = Features::Aimbot::WingmanMinHipfireSmooth1;
			Config::Aimbot::WingmanMaxHipfireSmooth1 = Features::Aimbot::WingmanMaxHipfireSmooth1;
			Config::Aimbot::WingmanMinADSSmooth1 = Features::Aimbot::WingmanMinADSSmooth1;
			Config::Aimbot::WingmanMaxADSSmooth1 = Features::Aimbot::WingmanMaxADSSmooth1;
			Config::Aimbot::WingmanFOV = Features::Aimbot::WingmanFOV;
			Config::Aimbot::WingmanZoomScale = Features::Aimbot::WingmanZoomScale;
			Config::Aimbot::WingmanHipfireSmooth1 = Features::Aimbot::WingmanHipfireSmooth1;
			Config::Aimbot::WingmanADSSmooth1 = Features::Aimbot::WingmanADSSmooth1;
			Config::Aimbot::WingmanExtraSmooth1 = Features::Aimbot::WingmanExtraSmooth1;
			Config::Aimbot::WingmanDeadzone = Features::Aimbot::WingmanDeadzone;
			Config::Aimbot::WingmanFOV1 = Features::Aimbot::WingmanFOV1;
			Config::Aimbot::WingmanMinDistance1 = Features::Aimbot::WingmanMinDistance1;
			Config::Aimbot::WingmanMaxDistance1 = Features::Aimbot::WingmanMaxDistance1;
			Config::Aimbot::EVA8Fire = Features::Aimbot::EVA8Fire;
			Config::Aimbot::EVA8ADS = Features::Aimbot::EVA8ADS;
			Config::Aimbot::EVA8ClosestHitbox = Features::Aimbot::EVA8ClosestHitbox;
			Config::Aimbot::EVA8Hitbox = Features::Aimbot::EVA8Hitbox;
			Config::Aimbot::EVA8Speed = Features::Aimbot::EVA8Speed;
			Config::Aimbot::EVA8HipfireSmooth = Features::Aimbot::EVA8HipfireSmooth;
			Config::Aimbot::EVA8ADSSmooth = Features::Aimbot::EVA8ADSSmooth;
			Config::Aimbot::EVA8SmoothingMethod = Features::Aimbot::EVA8SmoothingMethod;
			Config::Aimbot::EVA8MinHipfireSmooth = Features::Aimbot::EVA8MinHipfireSmooth;
			Config::Aimbot::EVA8MaxHipfireSmooth = Features::Aimbot::EVA8MaxHipfireSmooth;
			Config::Aimbot::EVA8MinADSSmooth = Features::Aimbot::EVA8MinADSSmooth;
			Config::Aimbot::EVA8MaxADSSmooth = Features::Aimbot::EVA8MaxADSSmooth;
			Config::Aimbot::EVA8MinHipfireSmooth1 = Features::Aimbot::EVA8MinHipfireSmooth1;
			Config::Aimbot::EVA8MaxHipfireSmooth1 = Features::Aimbot::EVA8MaxHipfireSmooth1;
			Config::Aimbot::EVA8MinADSSmooth1 = Features::Aimbot::EVA8MinADSSmooth1;
			Config::Aimbot::EVA8MaxADSSmooth1 = Features::Aimbot::EVA8MaxADSSmooth1;
			Config::Aimbot::EVA8FOV = Features::Aimbot::EVA8FOV;
			Config::Aimbot::EVA8ZoomScale = Features::Aimbot::EVA8ZoomScale;
			Config::Aimbot::EVA8HipfireSmooth1 = Features::Aimbot::EVA8HipfireSmooth1;
			Config::Aimbot::EVA8ADSSmooth1 = Features::Aimbot::EVA8ADSSmooth1;
			Config::Aimbot::EVA8ExtraSmooth1 = Features::Aimbot::EVA8ExtraSmooth1;
			Config::Aimbot::EVA8Deadzone = Features::Aimbot::EVA8Deadzone;
			Config::Aimbot::EVA8FOV1 = Features::Aimbot::EVA8FOV1;
			Config::Aimbot::EVA8MinDistance1 = Features::Aimbot::EVA8MinDistance1;
			Config::Aimbot::EVA8MaxDistance1 = Features::Aimbot::EVA8MaxDistance1;
			Config::Aimbot::BocekFire = Features::Aimbot::BocekFire;
			Config::Aimbot::BocekADS = Features::Aimbot::BocekADS;
			Config::Aimbot::BocekClosestHitbox = Features::Aimbot::BocekClosestHitbox;
			Config::Aimbot::BocekHitbox = Features::Aimbot::BocekHitbox;
			Config::Aimbot::BocekSpeed = Features::Aimbot::BocekSpeed;
			Config::Aimbot::BocekHipfireSmooth = Features::Aimbot::BocekHipfireSmooth;
			Config::Aimbot::BocekADSSmooth = Features::Aimbot::BocekADSSmooth;
			Config::Aimbot::BocekSmoothingMethod = Features::Aimbot::BocekSmoothingMethod;
			Config::Aimbot::BocekMinHipfireSmooth = Features::Aimbot::BocekMinHipfireSmooth;
			Config::Aimbot::BocekMaxHipfireSmooth = Features::Aimbot::BocekMaxHipfireSmooth;
			Config::Aimbot::BocekMinADSSmooth = Features::Aimbot::BocekMinADSSmooth;
			Config::Aimbot::BocekMaxADSSmooth = Features::Aimbot::BocekMaxADSSmooth;
			Config::Aimbot::BocekMinHipfireSmooth1 = Features::Aimbot::BocekMinHipfireSmooth1;
			Config::Aimbot::BocekMaxHipfireSmooth1 = Features::Aimbot::BocekMaxHipfireSmooth1;
			Config::Aimbot::BocekMinADSSmooth1 = Features::Aimbot::BocekMinADSSmooth1;
			Config::Aimbot::BocekMaxADSSmooth1 = Features::Aimbot::BocekMaxADSSmooth1;
			Config::Aimbot::BocekFOV = Features::Aimbot::BocekFOV;
			Config::Aimbot::BocekZoomScale = Features::Aimbot::BocekZoomScale;
			Config::Aimbot::BocekHipfireSmooth1 = Features::Aimbot::BocekHipfireSmooth1;
			Config::Aimbot::BocekADSSmooth1 = Features::Aimbot::BocekADSSmooth1;
			Config::Aimbot::BocekExtraSmooth1 = Features::Aimbot::BocekExtraSmooth1;
			Config::Aimbot::BocekDeadzone = Features::Aimbot::BocekDeadzone;
			Config::Aimbot::BocekFOV1 = Features::Aimbot::BocekFOV1;
			Config::Aimbot::BocekMinDistance1 = Features::Aimbot::BocekMinDistance1;
			Config::Aimbot::BocekMaxDistance1 = Features::Aimbot::BocekMaxDistance1;
			Config::Aimbot::KraberFire = Features::Aimbot::KraberFire;
			Config::Aimbot::KraberADS = Features::Aimbot::KraberADS;
			Config::Aimbot::KraberClosestHitbox = Features::Aimbot::KraberClosestHitbox;
			Config::Aimbot::KraberHitbox = Features::Aimbot::KraberHitbox;
			Config::Aimbot::KraberSpeed = Features::Aimbot::KraberSpeed;
			Config::Aimbot::KraberHipfireSmooth = Features::Aimbot::KraberHipfireSmooth;
			Config::Aimbot::KraberADSSmooth = Features::Aimbot::KraberADSSmooth;
			Config::Aimbot::KraberSmoothingMethod = Features::Aimbot::KraberSmoothingMethod;
			Config::Aimbot::KraberMinHipfireSmooth = Features::Aimbot::KraberMinHipfireSmooth;
			Config::Aimbot::KraberMaxHipfireSmooth = Features::Aimbot::KraberMaxHipfireSmooth;
			Config::Aimbot::KraberMinADSSmooth = Features::Aimbot::KraberMinADSSmooth;
			Config::Aimbot::KraberMaxADSSmooth = Features::Aimbot::KraberMaxADSSmooth;
			Config::Aimbot::KraberMinHipfireSmooth1 = Features::Aimbot::KraberMinHipfireSmooth1;
			Config::Aimbot::KraberMaxHipfireSmooth1 = Features::Aimbot::KraberMaxHipfireSmooth1;
			Config::Aimbot::KraberMinADSSmooth1 = Features::Aimbot::KraberMinADSSmooth1;
			Config::Aimbot::KraberMaxADSSmooth1 = Features::Aimbot::KraberMaxADSSmooth1;
			Config::Aimbot::KraberFOV = Features::Aimbot::KraberFOV;
			Config::Aimbot::KraberZoomScale = Features::Aimbot::KraberZoomScale;
			Config::Aimbot::KraberHipfireSmooth1 = Features::Aimbot::KraberHipfireSmooth1;
			Config::Aimbot::KraberADSSmooth1 = Features::Aimbot::KraberADSSmooth1;
			Config::Aimbot::KraberExtraSmooth1 = Features::Aimbot::KraberExtraSmooth1;
			Config::Aimbot::KraberDeadzone = Features::Aimbot::KraberDeadzone;
			Config::Aimbot::KraberFOV1 = Features::Aimbot::KraberFOV1;
			Config::Aimbot::KraberMinDistance1 = Features::Aimbot::KraberMinDistance1;
			Config::Aimbot::KraberMaxDistance1 = Features::Aimbot::KraberMaxDistance1;
			Config::Aimbot::ThrowingKnifeFire = Features::Aimbot::ThrowingKnifeFire;
			Config::Aimbot::ThrowingKnifeADS = Features::Aimbot::ThrowingKnifeADS;
			Config::Aimbot::ThrowingKnifeClosestHitbox = Features::Aimbot::ThrowingKnifeClosestHitbox;
			Config::Aimbot::ThrowingKnifeHitbox = Features::Aimbot::ThrowingKnifeHitbox;
			Config::Aimbot::ThrowingKnifeSpeed = Features::Aimbot::ThrowingKnifeSpeed;
			Config::Aimbot::ThrowingKnifeHipfireSmooth = Features::Aimbot::ThrowingKnifeHipfireSmooth;
			Config::Aimbot::ThrowingKnifeADSSmooth = Features::Aimbot::ThrowingKnifeADSSmooth;
			Config::Aimbot::ThrowingKnifeSmoothingMethod = Features::Aimbot::ThrowingKnifeSmoothingMethod;
			Config::Aimbot::ThrowingKnifeMinHipfireSmooth = Features::Aimbot::ThrowingKnifeMinHipfireSmooth;
			Config::Aimbot::ThrowingKnifeMaxHipfireSmooth = Features::Aimbot::ThrowingKnifeMaxHipfireSmooth;
			Config::Aimbot::ThrowingKnifeMinADSSmooth = Features::Aimbot::ThrowingKnifeMinADSSmooth;
			Config::Aimbot::ThrowingKnifeMaxADSSmooth = Features::Aimbot::ThrowingKnifeMaxADSSmooth;
			Config::Aimbot::ThrowingKnifeMinHipfireSmooth1 = Features::Aimbot::ThrowingKnifeMinHipfireSmooth1;
			Config::Aimbot::ThrowingKnifeMaxHipfireSmooth1 = Features::Aimbot::ThrowingKnifeMaxHipfireSmooth1;
			Config::Aimbot::ThrowingKnifeMinADSSmooth1 = Features::Aimbot::ThrowingKnifeMinADSSmooth1;
			Config::Aimbot::ThrowingKnifeMaxADSSmooth1 = Features::Aimbot::ThrowingKnifeMaxADSSmooth1;
			Config::Aimbot::ThrowingKnifeFOV = Features::Aimbot::ThrowingKnifeFOV;
			Config::Aimbot::ThrowingKnifeZoomScale = Features::Aimbot::ThrowingKnifeZoomScale;
			Config::Aimbot::ThrowingKnifeHipfireSmooth1 = Features::Aimbot::ThrowingKnifeHipfireSmooth1;
			Config::Aimbot::ThrowingKnifeADSSmooth1 = Features::Aimbot::ThrowingKnifeADSSmooth1;
			Config::Aimbot::ThrowingKnifeExtraSmooth1 = Features::Aimbot::ThrowingKnifeExtraSmooth1;
			Config::Aimbot::ThrowingKnifeDeadzone = Features::Aimbot::ThrowingKnifeDeadzone;
			Config::Aimbot::ThrowingKnifeFOV1 = Features::Aimbot::ThrowingKnifeFOV1;
			Config::Aimbot::ThrowingKnifeMinDistance1 = Features::Aimbot::ThrowingKnifeMinDistance1;
			Config::Aimbot::ThrowingKnifeMaxDistance1 = Features::Aimbot::ThrowingKnifeMaxDistance1;

			Config::AimbotBinds::AimBind = static_cast<int>(Features::AimbotBinds::AimBind);
			Config::AimbotBinds::ExtraBind = static_cast<int>(Features::AimbotBinds::ExtraBind);
			// Advanced
			Config::AimbotBinds::P2020AimBind = static_cast<int>(Features::AimbotBinds::P2020AimBind);
			Config::AimbotBinds::P2020ExtraBind = static_cast<int>(Features::AimbotBinds::P2020ExtraBind);
			Config::AimbotBinds::RE45AimBind = static_cast<int>(Features::AimbotBinds::RE45AimBind);
			Config::AimbotBinds::RE45ExtraBind = static_cast<int>(Features::AimbotBinds::RE45ExtraBind);
			Config::AimbotBinds::AlternatorAimBind = static_cast<int>(Features::AimbotBinds::AlternatorAimBind);
			Config::AimbotBinds::AlternatorExtraBind = static_cast<int>(Features::AimbotBinds::AlternatorExtraBind);
			Config::AimbotBinds::R99AimBind = static_cast<int>(Features::AimbotBinds::R99AimBind);
			Config::AimbotBinds::R99ExtraBind = static_cast<int>(Features::AimbotBinds::R99ExtraBind);
			Config::AimbotBinds::R301AimBind = static_cast<int>(Features::AimbotBinds::R301AimBind);
			Config::AimbotBinds::R301ExtraBind = static_cast<int>(Features::AimbotBinds::R301ExtraBind);
			Config::AimbotBinds::SpitfireAimBind = static_cast<int>(Features::AimbotBinds::SpitfireAimBind);
			Config::AimbotBinds::SpitfireExtraBind = static_cast<int>(Features::AimbotBinds::SpitfireExtraBind);
			Config::AimbotBinds::G7AimBind = static_cast<int>(Features::AimbotBinds::G7AimBind);
			Config::AimbotBinds::G7ExtraBind = static_cast<int>(Features::AimbotBinds::G7ExtraBind);
			Config::AimbotBinds::FlatlineAimBind = static_cast<int>(Features::AimbotBinds::FlatlineAimBind);
			Config::AimbotBinds::FlatlineExtraBind = static_cast<int>(Features::AimbotBinds::FlatlineExtraBind);
			Config::AimbotBinds::HemlockAimBind = static_cast<int>(Features::AimbotBinds::HemlockAimBind);
			Config::AimbotBinds::HemlockExtraBind = static_cast<int>(Features::AimbotBinds::HemlockExtraBind);
			Config::AimbotBinds::ProwlerAimBind = static_cast<int>(Features::AimbotBinds::ProwlerAimBind);
			Config::AimbotBinds::ProwlerExtraBind = static_cast<int>(Features::AimbotBinds::ProwlerExtraBind);
			Config::AimbotBinds::RepeaterAimBind = static_cast<int>(Features::AimbotBinds::RepeaterAimBind);
			Config::AimbotBinds::RepeaterExtraBind = static_cast<int>(Features::AimbotBinds::RepeaterExtraBind);
			Config::AimbotBinds::RampageAimBind = static_cast<int>(Features::AimbotBinds::RampageAimBind);
			Config::AimbotBinds::RampageExtraBind = static_cast<int>(Features::AimbotBinds::RampageExtraBind);
			Config::AimbotBinds::CARSMGAimBind = static_cast<int>(Features::AimbotBinds::CARSMGAimBind);
			Config::AimbotBinds::CARSMGExtraBind = static_cast<int>(Features::AimbotBinds::CARSMGExtraBind);
			Config::AimbotBinds::HavocAimBind = static_cast<int>(Features::AimbotBinds::HavocAimBind);
			Config::AimbotBinds::HavocExtraBind = static_cast<int>(Features::AimbotBinds::HavocExtraBind);
			Config::AimbotBinds::DevotionAimBind = static_cast<int>(Features::AimbotBinds::DevotionAimBind);
			Config::AimbotBinds::DevotionExtraBind = static_cast<int>(Features::AimbotBinds::DevotionExtraBind);
			Config::AimbotBinds::LSTARAimBind = static_cast<int>(Features::AimbotBinds::LSTARAimBind);
			Config::AimbotBinds::LSTARExtraBind = static_cast<int>(Features::AimbotBinds::LSTARExtraBind);
			Config::AimbotBinds::TripleTakeAimBind = static_cast<int>(Features::AimbotBinds::TripleTakeAimBind);
			Config::AimbotBinds::TripleTakeExtraBind = static_cast<int>(Features::AimbotBinds::TripleTakeExtraBind);
			Config::AimbotBinds::VoltAimBind = static_cast<int>(Features::AimbotBinds::VoltAimBind);
			Config::AimbotBinds::VoltExtraBind = static_cast<int>(Features::AimbotBinds::VoltExtraBind);
			Config::AimbotBinds::NemesisAimBind = static_cast<int>(Features::AimbotBinds::NemesisAimBind);
			Config::AimbotBinds::NemesisExtraBind = static_cast<int>(Features::AimbotBinds::NemesisExtraBind);
			Config::AimbotBinds::MozambiqueAimBind = static_cast<int>(Features::AimbotBinds::MozambiqueAimBind);
			Config::AimbotBinds::MozambiqueExtraBind = static_cast<int>(Features::AimbotBinds::MozambiqueExtraBind);
			Config::AimbotBinds::PeacekeeperAimBind = static_cast<int>(Features::AimbotBinds::PeacekeeperAimBind);
			Config::AimbotBinds::PeacekeeperExtraBind = static_cast<int>(Features::AimbotBinds::PeacekeeperExtraBind);
			Config::AimbotBinds::MastiffAimBind = static_cast<int>(Features::AimbotBinds::MastiffAimBind);
			Config::AimbotBinds::MastiffExtraBind = static_cast<int>(Features::AimbotBinds::MastiffExtraBind);
			Config::AimbotBinds::LongbowAimBind = static_cast<int>(Features::AimbotBinds::LongbowAimBind);
			Config::AimbotBinds::LongbowExtraBind = static_cast<int>(Features::AimbotBinds::LongbowExtraBind);
			Config::AimbotBinds::ChargeRifleAimBind = static_cast<int>(Features::AimbotBinds::ChargeRifleAimBind);
			Config::AimbotBinds::ChargeRifleExtraBind = static_cast<int>(Features::AimbotBinds::ChargeRifleExtraBind);
			Config::AimbotBinds::SentinelAimBind = static_cast<int>(Features::AimbotBinds::SentinelAimBind);
			Config::AimbotBinds::SentinelExtraBind = static_cast<int>(Features::AimbotBinds::SentinelExtraBind);
			Config::AimbotBinds::WingmanAimBind = static_cast<int>(Features::AimbotBinds::WingmanAimBind);
			Config::AimbotBinds::WingmanExtraBind = static_cast<int>(Features::AimbotBinds::WingmanExtraBind);
			Config::AimbotBinds::EVA8AimBind = static_cast<int>(Features::AimbotBinds::EVA8AimBind);
			Config::AimbotBinds::EVA8ExtraBind = static_cast<int>(Features::AimbotBinds::EVA8ExtraBind);
			Config::AimbotBinds::BocekAimBind = static_cast<int>(Features::AimbotBinds::BocekAimBind);
			Config::AimbotBinds::BocekExtraBind = static_cast<int>(Features::AimbotBinds::BocekExtraBind);
			Config::AimbotBinds::KraberAimBind = static_cast<int>(Features::AimbotBinds::KraberAimBind);
			Config::AimbotBinds::KraberExtraBind = static_cast<int>(Features::AimbotBinds::KraberExtraBind);
			Config::AimbotBinds::ThrowingKnifeAimBind = static_cast<int>(Features::AimbotBinds::ThrowingKnifeAimBind);
			Config::AimbotBinds::ThrowingKnifeExtraBind = static_cast<int>(Features::AimbotBinds::ThrowingKnifeExtraBind);

			Config::AimbotHitboxes::Hitbox = static_cast<int>(Features::AimbotHitboxes::Hitbox);
			// Advanced
			Config::AimbotHitboxes::P2020Hitbox = static_cast<int>(Features::AimbotHitboxes::P2020Hitbox);
			Config::AimbotHitboxes::RE45Hitbox = static_cast<int>(Features::AimbotHitboxes::RE45Hitbox);
			Config::AimbotHitboxes::AlternatorHitbox = static_cast<int>(Features::AimbotHitboxes::AlternatorHitbox);
			Config::AimbotHitboxes::R99Hitbox = static_cast<int>(Features::AimbotHitboxes::R99Hitbox);
			Config::AimbotHitboxes::R301Hitbox = static_cast<int>(Features::AimbotHitboxes::R301Hitbox);
			Config::AimbotHitboxes::SpitfireHitbox = static_cast<int>(Features::AimbotHitboxes::SpitfireHitbox);
			Config::AimbotHitboxes::G7Hitbox = static_cast<int>(Features::AimbotHitboxes::G7Hitbox);
			Config::AimbotHitboxes::FlatlineHitbox = static_cast<int>(Features::AimbotHitboxes::FlatlineHitbox);
			Config::AimbotHitboxes::HemlockHitbox = static_cast<int>(Features::AimbotHitboxes::HemlockHitbox);
			Config::AimbotHitboxes::ProwlerHitbox = static_cast<int>(Features::AimbotHitboxes::ProwlerHitbox);
			Config::AimbotHitboxes::RepeaterHitbox = static_cast<int>(Features::AimbotHitboxes::RepeaterHitbox);
			Config::AimbotHitboxes::RampageHitbox = static_cast<int>(Features::AimbotHitboxes::RampageHitbox);
			Config::AimbotHitboxes::CARSMGHitbox = static_cast<int>(Features::AimbotHitboxes::CARSMGHitbox);
			Config::AimbotHitboxes::HavocHitbox = static_cast<int>(Features::AimbotHitboxes::HavocHitbox);
			Config::AimbotHitboxes::DevotionHitbox = static_cast<int>(Features::AimbotHitboxes::DevotionHitbox);
			Config::AimbotHitboxes::LSTARHitbox = static_cast<int>(Features::AimbotHitboxes::LSTARHitbox);
			Config::AimbotHitboxes::TripleTakeHitbox = static_cast<int>(Features::AimbotHitboxes::TripleTakeHitbox);
			Config::AimbotHitboxes::VoltHitbox = static_cast<int>(Features::AimbotHitboxes::VoltHitbox);
			Config::AimbotHitboxes::NemesisHitbox = static_cast<int>(Features::AimbotHitboxes::NemesisHitbox);
			Config::AimbotHitboxes::MozambiqueHitbox = static_cast<int>(Features::AimbotHitboxes::MozambiqueHitbox);
			Config::AimbotHitboxes::PeacekeeperHitbox = static_cast<int>(Features::AimbotHitboxes::PeacekeeperHitbox);
			Config::AimbotHitboxes::MastiffHitbox = static_cast<int>(Features::AimbotHitboxes::MastiffHitbox);
			Config::AimbotHitboxes::LongbowHitbox = static_cast<int>(Features::AimbotHitboxes::LongbowHitbox);
			Config::AimbotHitboxes::ChargeRifleHitbox = static_cast<int>(Features::AimbotHitboxes::ChargeRifleHitbox);
			Config::AimbotHitboxes::SentinelHitbox = static_cast<int>(Features::AimbotHitboxes::SentinelHitbox);
			Config::AimbotHitboxes::WingmanHitbox = static_cast<int>(Features::AimbotHitboxes::WingmanHitbox);
			Config::AimbotHitboxes::EVA8Hitbox = static_cast<int>(Features::AimbotHitboxes::EVA8Hitbox);
			Config::AimbotHitboxes::BocekHitbox = static_cast<int>(Features::AimbotHitboxes::BocekHitbox);
			Config::AimbotHitboxes::KraberHitbox = static_cast<int>(Features::AimbotHitboxes::KraberHitbox);
			Config::AimbotHitboxes::ThrowingKnifeHitbox = static_cast<int>(Features::AimbotHitboxes::ThrowingKnifeHitbox);

			Config::RCS::RCSEnabled = Features::RCS::RCSEnabled;
			Config::RCS::RCSMode = Features::RCS::RCSMode;
			Config::RCS::OnADS = Features::RCS::OnADS;
			Config::RCS::PitchPower = Features::RCS::PitchPower;
			Config::RCS::YawPower = Features::RCS::YawPower;
			Config::RCS::PitchReduction = Features::RCS::PitchReduction;
			Config::RCS::YawReduction = Features::RCS::YawReduction;
			// Weapon Toggles
			// Light
			Config::RCS::P2020 = Features::RCS::P2020;
			Config::RCS::RE45 = Features::RCS::RE45;
			Config::RCS::Alternator = Features::RCS::Alternator;
			Config::RCS::R99 = Features::RCS::R99;
			Config::RCS::R301 = Features::RCS::R301;
			Config::RCS::Spitfire = Features::RCS::Spitfire;
			Config::RCS::G7 = Features::RCS::G7;
			// Heavy
			Config::RCS::Flatline = Features::RCS::Flatline;
			Config::RCS::Hemlock = Features::RCS::Hemlock;
			Config::RCS::Repeater = Features::RCS::Repeater;
			Config::RCS::Rampage = Features::RCS::Rampage;
			Config::RCS::CARSMG = Features::RCS::CARSMG;
			// Energy
			Config::RCS::Havoc = Features::RCS::Havoc;
			Config::RCS::Devotion = Features::RCS::Devotion;
			Config::RCS::LSTAR = Features::RCS::LSTAR;
			Config::RCS::TripleTake = Features::RCS::TripleTake;
			Config::RCS::Volt = Features::RCS::Volt;
			Config::RCS::Nemesis = Features::RCS::Nemesis;
			// Shotgun
			Config::RCS::Mozambique = Features::RCS::Mozambique;
			Config::RCS::EVA8 = Features::RCS::EVA8;
			Config::RCS::Peacekeeper = Features::RCS::Peacekeeper;
			Config::RCS::Mastiff = Features::RCS::Mastiff;
			// Snipers
			Config::RCS::Longbow = Features::RCS::Longbow;
			Config::RCS::ChargeRifle = Features::RCS::ChargeRifle;
			Config::RCS::Sentinel = Features::RCS::Sentinel;
			// Legendary
			Config::RCS::Wingman = Features::RCS::Wingman;
			Config::RCS::Prowler = Features::RCS::Prowler;
			Config::RCS::Kraber = Features::RCS::Kraber;
			// Advanced
			Config::RCS::AdvancedRCS = Features::RCS::AdvancedRCS;
			Config::RCS::AdvancedPitchPower = Features::RCS::AdvancedPitchPower;
			Config::RCS::AdvancedYawPower = Features::RCS::AdvancedYawPower;
			Config::RCS::AdvancedPitchReduction = Features::RCS::AdvancedPitchReduction;
			Config::RCS::AdvancedYawReduction = Features::RCS::AdvancedYawReduction;
			Config::RCS::P2020Pitch = Features::RCS::P2020Pitch;
			Config::RCS::P2020Yaw = Features::RCS::P2020Yaw;
			Config::RCS::P2020PitchReduction = Features::RCS::P2020PitchReduction;
			Config::RCS::P2020YawReduction = Features::RCS::P2020YawReduction;
			Config::RCS::RE45Pitch = Features::RCS::RE45Pitch;
			Config::RCS::RE45Yaw = Features::RCS::RE45Yaw;
			Config::RCS::RE45PitchReduction = Features::RCS::RE45PitchReduction;
			Config::RCS::RE45YawReduction = Features::RCS::RE45YawReduction;
			Config::RCS::AlternatorPitch = Features::RCS::AlternatorPitch;
			Config::RCS::AlternatorYaw = Features::RCS::AlternatorYaw;
			Config::RCS::AlternatorPitchReduction = Features::RCS::AlternatorPitchReduction;
			Config::RCS::AlternatorYawReduction = Features::RCS::AlternatorYawReduction;
			Config::RCS::R99Pitch = Features::RCS::R99Pitch;
			Config::RCS::R99Yaw = Features::RCS::R99Yaw;
			Config::RCS::R99PitchReduction = Features::RCS::R99PitchReduction;
			Config::RCS::R99YawReduction = Features::RCS::R99YawReduction;
			Config::RCS::R301Pitch = Features::RCS::R301Pitch;
			Config::RCS::R301Yaw = Features::RCS::R301Yaw;
			Config::RCS::R301PitchReduction = Features::RCS::R301PitchReduction;
			Config::RCS::R301YawReduction = Features::RCS::R301YawReduction;
			Config::RCS::SpitfirePitch = Features::RCS::SpitfirePitch;
			Config::RCS::SpitfireYaw = Features::RCS::SpitfireYaw;
			Config::RCS::SpitfirePitchReduction = Features::RCS::SpitfirePitchReduction;
			Config::RCS::SpitfireYawReduction = Features::RCS::SpitfireYawReduction;
			Config::RCS::G7Pitch = Features::RCS::G7Pitch;
			Config::RCS::G7Yaw = Features::RCS::G7Yaw;
			Config::RCS::G7PitchReduction = Features::RCS::G7PitchReduction;
			Config::RCS::G7YawReduction = Features::RCS::G7YawReduction;
			Config::RCS::FlatlinePitch = Features::RCS::FlatlinePitch;
			Config::RCS::FlatlineYaw = Features::RCS::FlatlineYaw;
			Config::RCS::FlatlinePitchReduction = Features::RCS::FlatlinePitchReduction;
			Config::RCS::FlatlineYawReduction = Features::RCS::FlatlineYawReduction;
			Config::RCS::HemlockPitch = Features::RCS::HemlockPitch;
			Config::RCS::HemlockYaw = Features::RCS::HemlockYaw;
			Config::RCS::HemlockPitchReduction = Features::RCS::HemlockPitchReduction;
			Config::RCS::HemlockYawReduction = Features::RCS::HemlockYawReduction;
			Config::RCS::ProwlerPitch = Features::RCS::ProwlerPitch;
			Config::RCS::ProwlerYaw = Features::RCS::ProwlerYaw;
			Config::RCS::ProwlerPitchReduction = Features::RCS::ProwlerPitchReduction;
			Config::RCS::ProwlerYawReduction = Features::RCS::ProwlerYawReduction;
			Config::RCS::RepeaterPitch = Features::RCS::RepeaterPitch;
			Config::RCS::RepeaterYaw = Features::RCS::RepeaterYaw;
			Config::RCS::RepeaterPitchReduction = Features::RCS::RepeaterPitchReduction;
			Config::RCS::RepeaterYawReduction = Features::RCS::RepeaterYawReduction;
			Config::RCS::RampagePitch = Features::RCS::RampagePitch;
			Config::RCS::RampageYaw = Features::RCS::RampageYaw;
			Config::RCS::RampagePitchReduction = Features::RCS::RampagePitchReduction;
			Config::RCS::RampageYawReduction = Features::RCS::RampageYawReduction;
			Config::RCS::CARSMGPitch = Features::RCS::CARSMGPitch;
			Config::RCS::CARSMGYaw = Features::RCS::CARSMGYaw;
			Config::RCS::CARSMGPitchReduction = Features::RCS::CARSMGPitchReduction;
			Config::RCS::CARSMGYawReduction = Features::RCS::CARSMGYawReduction;
			Config::RCS::HavocPitch = Features::RCS::HavocPitch;
			Config::RCS::HavocYaw = Features::RCS::HavocYaw;
			Config::RCS::HavocPitchReduction = Features::RCS::HavocPitchReduction;
			Config::RCS::HavocYawReduction = Features::RCS::HavocYawReduction;
			Config::RCS::DevotionPitch = Features::RCS::DevotionPitch;
			Config::RCS::DevotionYaw = Features::RCS::DevotionYaw;
			Config::RCS::DevotionPitchReduction = Features::RCS::DevotionPitchReduction;
			Config::RCS::DevotionYawReduction = Features::RCS::DevotionYawReduction;
			Config::RCS::LSTARPitch = Features::RCS::LSTARPitch;
			Config::RCS::LSTARYaw = Features::RCS::LSTARYaw;
			Config::RCS::LSTARPitchReduction = Features::RCS::LSTARPitchReduction;
			Config::RCS::LSTARYawReduction = Features::RCS::LSTARYawReduction;
			Config::RCS::TripleTakePitch = Features::RCS::TripleTakePitch;
			Config::RCS::TripleTakeYaw = Features::RCS::TripleTakeYaw;
			Config::RCS::TripleTakePitchReduction = Features::RCS::TripleTakePitchReduction;
			Config::RCS::TripleTakeYawReduction = Features::RCS::TripleTakeYawReduction;
			Config::RCS::VoltPitch = Features::RCS::VoltPitch;
			Config::RCS::VoltYaw = Features::RCS::VoltYaw;
			Config::RCS::VoltPitchReduction = Features::RCS::VoltPitchReduction;
			Config::RCS::VoltYawReduction = Features::RCS::VoltYawReduction;
			Config::RCS::NemesisPitch = Features::RCS::NemesisPitch;
			Config::RCS::NemesisYaw = Features::RCS::NemesisYaw;
			Config::RCS::NemesisPitchReduction = Features::RCS::NemesisPitchReduction;
			Config::RCS::NemesisYawReduction = Features::RCS::NemesisYawReduction;
			Config::RCS::MozambiquePitch = Features::RCS::MozambiquePitch;
			Config::RCS::MozambiqueYaw = Features::RCS::MozambiqueYaw;
			Config::RCS::MozambiquePitchReduction = Features::RCS::MozambiquePitchReduction;
			Config::RCS::MozambiqueYawReduction = Features::RCS::MozambiqueYawReduction;
			Config::RCS::PeacekeeperPitch = Features::RCS::PeacekeeperPitch;
			Config::RCS::PeacekeeperYaw = Features::RCS::PeacekeeperYaw;
			Config::RCS::PeacekeeperPitchReduction = Features::RCS::PeacekeeperPitchReduction;
			Config::RCS::PeacekeeperYawReduction = Features::RCS::PeacekeeperYawReduction;
			Config::RCS::MastiffPitch = Features::RCS::MastiffPitch;
			Config::RCS::MastiffYaw = Features::RCS::MastiffYaw;
			Config::RCS::MastiffPitchReduction = Features::RCS::MastiffPitchReduction;
			Config::RCS::MastiffYawReduction = Features::RCS::MastiffYawReduction;
			Config::RCS::LongbowPitch = Features::RCS::LongbowPitch;
			Config::RCS::LongbowYaw = Features::RCS::LongbowYaw;
			Config::RCS::LongbowPitchReduction = Features::RCS::LongbowPitchReduction;
			Config::RCS::LongbowYawReduction = Features::RCS::LongbowYawReduction;
			Config::RCS::ChargeRiflePitch = Features::RCS::ChargeRiflePitch;
			Config::RCS::ChargeRifleYaw = Features::RCS::ChargeRifleYaw;
			Config::RCS::ChargeRiflePitchReduction = Features::RCS::ChargeRiflePitchReduction;
			Config::RCS::ChargeRifleYawReduction = Features::RCS::ChargeRifleYawReduction;
			Config::RCS::SentinelPitch = Features::RCS::SentinelPitch;
			Config::RCS::SentinelYaw = Features::RCS::SentinelYaw;
			Config::RCS::SentinelPitchReduction = Features::RCS::SentinelPitchReduction;
			Config::RCS::SentinelYawReduction = Features::RCS::SentinelYawReduction;
			Config::RCS::WingmanPitch = Features::RCS::WingmanPitch;
			Config::RCS::WingmanYaw = Features::RCS::WingmanYaw;
			Config::RCS::WingmanPitchReduction = Features::RCS::WingmanPitchReduction;
			Config::RCS::WingmanYawReduction = Features::RCS::WingmanYawReduction;
			Config::RCS::EVA8Pitch = Features::RCS::EVA8Pitch;
			Config::RCS::EVA8Yaw = Features::RCS::EVA8Yaw;
			Config::RCS::EVA8PitchReduction = Features::RCS::EVA8PitchReduction;
			Config::RCS::EVA8YawReduction = Features::RCS::EVA8YawReduction;
			Config::RCS::KraberPitch = Features::RCS::KraberPitch;
			Config::RCS::KraberYaw = Features::RCS::KraberYaw;
			Config::RCS::KraberPitchReduction = Features::RCS::KraberPitchReduction;
			Config::RCS::KraberYawReduction = Features::RCS::KraberYawReduction;

			return true;
		} catch (...) {
			return false;
		}
	}

	void UpdateAimList() {
		Features::Aimbot::AimList.clear();
		// Define a lambda function to reduce repetition
		auto InsertIfEnabled = [&](const bool feature, const int weaponID) {
			if (feature)
				Features::Aimbot::AimList.insert(weaponID);
		};
		// Light
		InsertIfEnabled(Features::Aimbot::P2020, WeaponIDs::P2020);
		InsertIfEnabled(Features::Aimbot::RE45, WeaponIDs::RE45);
		InsertIfEnabled(Features::Aimbot::Alternator, WeaponIDs::ALTERNATOR);
		InsertIfEnabled(Features::Aimbot::R99, WeaponIDs::R99);
		InsertIfEnabled(Features::Aimbot::R301, WeaponIDs::R301);
		InsertIfEnabled(Features::Aimbot::Spitfire, WeaponIDs::SPITFIRE);
		InsertIfEnabled(Features::Aimbot::G7, WeaponIDs::G7);

		// Heavy
		InsertIfEnabled(Features::Aimbot::Flatline, WeaponIDs::FLATLINE);
		InsertIfEnabled(Features::Aimbot::Prowler, WeaponIDs::PROWLER);
		InsertIfEnabled(Features::Aimbot::Hemlock, WeaponIDs::HEMLOCK);
		InsertIfEnabled(Features::Aimbot::Repeater, WeaponIDs::REPEATER);
		InsertIfEnabled(Features::Aimbot::Rampage, WeaponIDs::RAMPAGE);
		InsertIfEnabled(Features::Aimbot::CARSMG, WeaponIDs::CAR);

		// Energy
		InsertIfEnabled(Features::Aimbot::Havoc, WeaponIDs::HAVOC);
		InsertIfEnabled(Features::Aimbot::Devotion, WeaponIDs::DEVOTION);
		InsertIfEnabled(Features::Aimbot::LSTAR, WeaponIDs::LSTAR);
		InsertIfEnabled(Features::Aimbot::TripleTake, WeaponIDs::TRIPLETAKE);
		InsertIfEnabled(Features::Aimbot::Volt, WeaponIDs::VOLT);
		InsertIfEnabled(Features::Aimbot::Nemesis, WeaponIDs::NEMESIS);

		// Shotguns
		InsertIfEnabled(Features::Aimbot::Mozambique, WeaponIDs::MOZAMBIQUE);
		InsertIfEnabled(Features::Aimbot::Peacekeeper, WeaponIDs::PEACEKEEPER);
		InsertIfEnabled(Features::Aimbot::Mastiff, WeaponIDs::MASTIFF);

		// Snipers
		InsertIfEnabled(Features::Aimbot::Longbow, WeaponIDs::LONGBOW);
		InsertIfEnabled(Features::Aimbot::ChargeRifle, WeaponIDs::CHARGE_RIFLE);
		InsertIfEnabled(Features::Aimbot::Sentinel, WeaponIDs::SENTINEL);

		// Legendary
		InsertIfEnabled(Features::Aimbot::Wingman, WeaponIDs::WINGMAN);
		InsertIfEnabled(Features::Aimbot::EVA8, WeaponIDs::EVA8);
		InsertIfEnabled(Features::Aimbot::Bocek, WeaponIDs::BOCEK);
		InsertIfEnabled(Features::Aimbot::Kraber, WeaponIDs::KRABER);
		InsertIfEnabled(Features::Aimbot::Knife, WeaponIDs::KNIFE);
	}

	void UpdateRCSList() {
		Features::RCS::RCSList.clear();
		// Define a lambda function to reduce repetition
		auto InsertIfEnabled = [&](const bool feature, const int weaponID) {
			if (feature)
				Features::RCS::RCSList.insert(weaponID);
		};
		// Light
		InsertIfEnabled(Features::RCS::P2020, WeaponIDs::P2020);
		InsertIfEnabled(Features::RCS::RE45, WeaponIDs::RE45);
		InsertIfEnabled(Features::RCS::Alternator, WeaponIDs::ALTERNATOR);
		InsertIfEnabled(Features::RCS::R99, WeaponIDs::R99);
		InsertIfEnabled(Features::RCS::R301, WeaponIDs::R301);
		InsertIfEnabled(Features::RCS::Spitfire, WeaponIDs::SPITFIRE);
		InsertIfEnabled(Features::RCS::G7, WeaponIDs::G7);

		// Heavy
		InsertIfEnabled(Features::RCS::Flatline, WeaponIDs::FLATLINE);
		InsertIfEnabled(Features::RCS::Prowler, WeaponIDs::PROWLER);
		InsertIfEnabled(Features::RCS::Hemlock, WeaponIDs::HEMLOCK);
		InsertIfEnabled(Features::RCS::Repeater, WeaponIDs::REPEATER);
		InsertIfEnabled(Features::RCS::Rampage, WeaponIDs::RAMPAGE);
		InsertIfEnabled(Features::RCS::CARSMG, WeaponIDs::CAR);

		// Energy
		InsertIfEnabled(Features::RCS::Havoc, WeaponIDs::HAVOC);
		InsertIfEnabled(Features::RCS::Devotion, WeaponIDs::DEVOTION);
		InsertIfEnabled(Features::RCS::LSTAR, WeaponIDs::LSTAR);
		InsertIfEnabled(Features::RCS::TripleTake, WeaponIDs::TRIPLETAKE);
		InsertIfEnabled(Features::RCS::Volt, WeaponIDs::VOLT);
		InsertIfEnabled(Features::RCS::Nemesis, WeaponIDs::NEMESIS);

		// Shotguns
		InsertIfEnabled(Features::RCS::Mozambique, WeaponIDs::MOZAMBIQUE);
		InsertIfEnabled(Features::RCS::Peacekeeper, WeaponIDs::PEACEKEEPER);
		InsertIfEnabled(Features::RCS::Mastiff, WeaponIDs::MASTIFF);

		// Snipers
		InsertIfEnabled(Features::RCS::Longbow, WeaponIDs::LONGBOW);
		InsertIfEnabled(Features::RCS::ChargeRifle, WeaponIDs::CHARGE_RIFLE);
		InsertIfEnabled(Features::RCS::Sentinel, WeaponIDs::SENTINEL);

		// Legendary
		InsertIfEnabled(Features::RCS::Wingman, WeaponIDs::WINGMAN);
		InsertIfEnabled(Features::RCS::EVA8, WeaponIDs::EVA8);
		InsertIfEnabled(Features::RCS::Kraber, WeaponIDs::KRABER);
	}

	void UpdateAimbot() {

		if (!Map->IsPlayable) {
			ReleaseTarget();
			return;
		}

		if (!Features::Aimbot::AimbotEnabled) {
			ReleaseTarget();
			return;
		}

		if (Features::Aimbot::AimbotEnabled) {
			if (Features::Home::IsMenuOpened)
				return; // Dont aimbot whilst menu is open

			if (Features::Aimbot::SpectatorCheck && Features::TotalSpectators >= 1)
				return; // Disables Aimbot If Being Spectated

			UpdateAimList();
			if (Features::Aimbot::AdvancedAim) {
				UpdateAimbotSettings();
			}

			if (Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 2) // Cubic Beizer (xap-client) & [New] Cubic Bezier (Testing)
			{

				if (!Myself->IsCombatReady()) {
					CurrentTarget = nullptr;
					return;
				}

				if (Features::Aimbot::AimList.find(Myself->WeaponIndex) == Features::Aimbot::AimList.end()) {
					ReleaseTarget();
					return;
				}

				if (Myself->IsHoldingGrenade) {
					ReleaseTarget();
					return;
				}

				if (Features::Aimbot::BindMethod == 0) { // OnFire and OnADS
					{
						if (Features::Aimbot::OnFire && Features::Aimbot::OnADS) {
							if (!Myself->IsInAttack) {
								if (!Myself->IsZooming) {
									ReleaseTarget();
									return;
								}
							}
							if (!Myself->IsZooming) {
								if (!Myself->IsInAttack) {
									ReleaseTarget();
									return;
								}
							}
						}
					}

					if (Features::Aimbot::OnFire && !Features::Aimbot::OnADS) {
						if (!Myself->IsInAttack) {
							ReleaseTarget();
							return;
						}
					}

					if (Features::Aimbot::OnFire && !Features::Aimbot::OnFire) {
						if (!Myself->IsZooming) {
							ReleaseTarget();
							return;
						}
					}
				}

				else if (Features::Aimbot::BindMethod == 1) { // Keybinds
					if (!isKeybindDown()) {
						ReleaseTarget();
						return;
					}
				}

				Player* Target = BestTarget;
				if (!Features::Aimbot::TargetSwitching) {
					if (!IsValidTarget(Target)) {
						if (TargetSelected) {
							return;
						}

						Target = FindBestTarget();
						if (!IsValidTarget(Target)) {
							ReleaseTarget();
							return;
						}

						BestTarget = Target;
						return;
					}
				} else {
					Target = FindBestTarget();
					if (!IsValidTarget(Target)) {
						ReleaseTarget();
						return;
					}

					CurrentTarget = Target;
					CurrentTarget->IsLockedOn = true;
					TargetSelected = true;
				}

				if (TargetSelected && CurrentTarget) {
					std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
					if (Now >= LastAimTime + std::chrono::milliseconds(Features::Aimbot::Delay)) {
						StartAiming();
						LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
					}
					return;
				}
			}

			// Grinder (Linear) Aimbot Mode
			if (Features::Aimbot::AimbotMode == 1) {
				if (Features::Aimbot::InputMethod == 1) // Memory / Controller - Does not work
				return;

				if (!active()) {
					releaseTarget();
					return;
				}
				if (Features::Aimbot::AimList.find(Myself->WeaponIndex) == Features::Aimbot::AimList.end())
					return;
				if (Myself->IsHoldingGrenade)
					return;
				if (CurrentTarget == nullptr)
					assignTarget();
				if (CurrentTarget == nullptr)
					return;
				if (!CurrentTarget->IsVisible)
					return;
				if (CurrentTarget->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Aimbot::AdvancedMinDistance1))
					return;
				if (CurrentTarget->Distance2DToLocalPlayer > Conversion::ToGameUnits(Features::Aimbot::AdvancedMaxDistance1))
					return;
				moveMouse();
			}
		}
	}

	void UpdateRCS() {
		if (!Map->IsPlayable)
			return;

		if (!Features::RCS::RCSEnabled)
			return;

		if (Features::RCS::RCSEnabled) {
			if (Features::RCS::RCSMode == 1) // Combined
				return; // Combined Is In StartAiming() && MoveMouse()
			
			UpdateRCSSettings();

			if (Features::RCS::OnADS) {

				if (!Myself->IsCombatReady())
					return;
				if (!Myself->IsZooming)
					return;
				if (!Myself->IsInAttack)
					return;

				int PitchPower;
				int YawPower;
				if (Features::RCS::AdvancedRCS) {
					PitchPower = Features::RCS::AdvancedPitchPower;
					YawPower = Features::RCS::AdvancedYawPower;
				}

				else if (!Features::RCS::AdvancedRCS) {
					PitchPower = Features::RCS::PitchPower;
					YawPower = Features::RCS::YawPower;
				}

				FloatVector2D punchAnglesDiff = Myself->punchAnglesDiff;
				if (punchAnglesDiff.isZeroVector())
					return;
				int pitch = (punchAnglesDiff.x > 0)
					? RoundHalfEven(punchAnglesDiff.x * PitchPower)
					: 0;
				int yaw = RoundHalfEven(-punchAnglesDiff.y * YawPower);
				DHID->MoveMouse(pitch, yaw);
			}

			if (!Features::RCS::OnADS) {
				if (!Myself->IsCombatReady())
					return;
				if (!Myself->IsInAttack)
					return;
				FloatVector2D punchAnglesDiff = Myself->punchAnglesDiff;
				if (punchAnglesDiff.isZeroVector())
					return;

				int PitchPower;
				int YawPower;
				if (Features::RCS::AdvancedRCS) {
					PitchPower = Features::RCS::AdvancedPitchPower;
					YawPower = Features::RCS::AdvancedYawPower;
				}

				else if (!Features::RCS::AdvancedRCS) {
					PitchPower = Features::RCS::PitchPower;
					YawPower = Features::RCS::YawPower;
				}

				int pitch = (punchAnglesDiff.x > 0)
					? RoundHalfEven(punchAnglesDiff.x * PitchPower)
					: 0;
				int yaw = RoundHalfEven(-punchAnglesDiff.y * YawPower);
				DHID->MoveMouse(pitch, yaw);
			}
		}
	}

	//------------------------------ Legitbot - Aimbot ------------------------------

	// Cubic Beizer (xap-client)

	static bool isKeybindDown() {
		return InputManager::isKeyDownOrPress(Features::AimbotBinds::AimBind) || InputManager::isKeyDownOrPress(Features::AimbotBinds::ExtraBind);
	}

	void StartAiming() {
		if (Features::Aimbot::InputMethod == 0) { // MoveMouse
			if (Features::Aimbot::AimbotMode == 0) { // Cubic Beizer
				// Get Target Angle
				if (!GetAngle(CurrentTarget, DesiredAngles))
					return;

				if (Features::RCS::RCSEnabled && Features::RCS::RCSMode == 1) {
					QAngle PunchAngles = Memory::Read<QAngle>(Myself->BasePointer + OFF_PUNCH_ANGLES);
					if (Features::RCS::AdvancedRCS) {
						PunchAngles.x *= (Features::RCS::AdvancedPitchReduction / 100.f);
						PunchAngles.y *= (Features::RCS::AdvancedYawReduction / 100.f);
					}

					else if (!Features::RCS::AdvancedRCS) {
						PunchAngles.x *= (Features::RCS::PitchReduction / 100.f);
						PunchAngles.y *= (Features::RCS::YawReduction / 100.f);
					}

					DesiredAngles -= PunchAngles;
				}

				if (DesiredAngles == QAngle(0, 0))
					return;
				DesiredAngles.NormalizeAngles();

				// Smoothing
				SmoothAngle(CurrentTarget, DesiredAngles);

				Vector2D aimbotDelta;
				aimbotDelta = Vector2D(CalculatePitchIncrement(DesiredAngles), CalculateYawIncrement(DesiredAngles)).Multiply(Features::Aimbot::AdvancedAim ? Features::Aimbot::AdvancedSpeed : Features::Aimbot::Speed);

				int totalYawIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.x));
				int totalPitchIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.y * -1));

				//Deadzone - Are We Close Enough Yet?
				if (fabs(CurrentTarget->aimbotDesiredAnglesIncrement.x) < Features::Aimbot::Deadzone) totalPitchIncrementInt = 0;
				if (fabs(CurrentTarget->aimbotDesiredAnglesIncrement.y) < Features::Aimbot::Deadzone) totalYawIncrementInt = 0;

				// Move Mouse
				if (totalPitchIncrementInt == 0 && totalYawIncrementInt == 0)
					return;
				DHID->MoveMouse(totalYawIncrementInt, totalPitchIncrementInt);
			}

			if (Features::Aimbot::AimbotMode == 2) // [New] Cubic Beizer (Testing)
			{
				// Get Target Angle
				if (!GetAngle(CurrentTarget, DesiredAngles))
					return;

				// Calculate Increment
				Vector2D DesiredAnglesIncrement = Vector2D(CalculatePitchIncrement(DesiredAngles), CalculateYawIncrement(DesiredAngles));

				// Calculate Smooth
				float Extra = Features::Aimbot::MouseExtraSmoothing / CurrentTarget->DistanceToLocalPlayer;
				float Smooth;
				if (Features::Aimbot::AdvancedAim) {
					return; // Will setup advanced aim in the future
				}
				if (!Features::Aimbot::AdvancedAim) {
					if (Features::Aimbot::SmoothingMethod == 0) // Static
					{
						if (Myself->IsZooming) {
							Smooth = Features::Aimbot::MouseADSSmoothing;
						} else {
							Smooth = Features::Aimbot::MouseHipfireSmoothing;
						}
					}
					if (Features::Aimbot::SmoothingMethod == 1) // Random
					{
						if (Myself->IsZooming) {
							Smooth = RandomSmoothing(Features::Aimbot::MinMouseADSSmoothing, Features::Aimbot::MaxMouseADSSmoothing);
						} else {
							Smooth = RandomSmoothing(Features::Aimbot::MinMouseHipfireSmoothing, Features::Aimbot::MaxMouseHipfireSmoothing);
						}
					}
				}


				float TotalSmooth = Smooth + Extra;

				// Aimbot calcs
				Vector2D aimbotDelta = DesiredAnglesIncrement.Divide(TotalSmooth).Multiply(Features::Aimbot::Speed);
				double aimYawIncrement = aimbotDelta.y * -1;
				double aimPitchIncrement = aimbotDelta.x;

				// Combine
				double totalPitchIncrement = aimPitchIncrement;
				double totalYawIncrement = aimYawIncrement;

				// Turn into integers
				int totalPitchIncrementInt = RoundHalfEven(AL1AF0(totalPitchIncrement));
				int totalYawIncrementInt = RoundHalfEven(AL1AF0(totalYawIncrement));

				//Deadzone - Are We Close Enough Yet?
				if (fabs(CurrentTarget->aimbotDesiredAnglesIncrement.x) < Features::Aimbot::Deadzone) totalPitchIncrementInt = 0;
				if (fabs(CurrentTarget->aimbotDesiredAnglesIncrement.y) < Features::Aimbot::Deadzone) totalYawIncrementInt = 0;

				// Move Mouse
				if (totalPitchIncrementInt == 0 && totalYawIncrementInt == 0) return;
				DHID->MoveMouse(totalPitchIncrementInt, totalYawIncrementInt);
			}
		}

		else if (Features::Aimbot::InputMethod == 1) // Write ViewAngles / Controller
		{
			// Get Target Angle
			if (!GetAngle(CurrentTarget, DesiredAngles)) // Get Angle to target + prediction
				return;

			// Recoil Control
			if (Features::RCS::RCSEnabled) {
				QAngle PunchAngles = Memory::Read<QAngle>(Myself->BasePointer + OFF_PUNCH_ANGLES); // Get punch angles
				PunchAngles.x *= (Features::RCS::PitchReduction / 100.f);
				PunchAngles.y *= (Features::RCS::YawReduction / 100.f);

				DesiredAngles -= PunchAngles;
			}

			if (DesiredAngles == QAngle(0, 0))
				return;
			DesiredAngles.NormalizeAngles();

			SmoothAngle(CurrentTarget, DesiredAngles); // Apply Smoothing

			// Memory Aimbot
			Vector2D VectorDesiredAngles = Vector2D(DesiredAngles.x, DesiredAngles.y);
			Myself->SetViewAngle(VectorDesiredAngles);
		}

	}

	void SmoothAngle(Player* Target, QAngle& Angle) {
		QAngle ViewAngles = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
		QAngle Delta = Angle - ViewAngles;
		Delta.NormalizeAngles();

		// Calculate Smoothing
		float SmoothValue;
		if (Features::Aimbot::AdvancedAim) {
			if (Myself->IsZooming) {
				SmoothValue = powf(Features::Aimbot::AdvancedADSSmooth, 0.4f);
			} else { // Hipfire
				SmoothValue = powf(Features::Aimbot::AdvancedHipfireSmooth, 0.4f);
			}
			SmoothValue = (std::min)(0.99f, SmoothValue);
		}

		else if (!Features::Aimbot::AdvancedAim) {
			if (Myself->IsZooming) {
				if (Features::Aimbot::SmoothingMethod == 0) // Static Smoothing
				{
					SmoothValue = powf(Features::Aimbot::ADSSmooth, 0.4f);
				} else if (Features::Aimbot::SmoothingMethod == 1) // Random Smoothing
				{
					SmoothValue = RandomSmoothing(Features::Aimbot::MinADSSmooth, Features::Aimbot::MaxADSSmooth);
				}
			} else { // Hipfire
				if (Features::Aimbot::SmoothingMethod == 0) // Static Smoothing
				{
					SmoothValue = powf(Features::Aimbot::HipfireSmooth, 0.4f);
				} else if (Features::Aimbot::SmoothingMethod == 1) // Random Smoothing
				{
					SmoothValue = RandomSmoothing(Features::Aimbot::MinHipfireSmooth, Features::Aimbot::MaxHipfireSmooth);
				}
			}
			SmoothValue = (std::min)(0.999f, SmoothValue);
		}

		QAngle ToChange = QAngle();
		ToChange = Delta - Delta * SmoothValue;

		Angle = ViewAngles + ToChange;
	}

	bool GetAngle(Player* Target, QAngle& Angle) {
		const QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
		if (!CurrentAngle.isValid())
			return false;

		if (!GetAngleToTarget(Target, Angle))
			return false;

		return true;
	}

	bool GetAngleToTarget(Player* Target, QAngle& Angle) {
		if (!Features::Aimbot::ClosestHitbox) {
			TargetPosition = Target->GetBonePosition(Features::AimbotHitboxes::Hitbox);
		} else if (Features::Aimbot::ClosestHitbox) {
			TargetPosition = Target->GetBonePosition(static_cast<HitboxType>(GetBestBone(Target)));
		}

		Vector3D TargetVelocity = Target->AbsoluteVelocity;
		Vector3D CameraPosition = Myself->CameraPosition;
		QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();

		if (Myself->WeaponProjectileSpeed > 1.0f) {
			if (Features::Aimbot::PredictBulletDrop && Features::Aimbot::PredictMovement) {
				return Resolver::CalculateAimRotationNew(CameraPosition, TargetPosition, TargetVelocity, Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, 255, Angle);
			} else if (Features::Aimbot::PredictBulletDrop) {
				return Resolver::CalculateAimRotationNew(CameraPosition, TargetPosition, Vector3D(0, 0, 0), Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, 255, Angle);
			} else if (Features::Aimbot::PredictMovement) {
				return Resolver::CalculateAimRotation(CameraPosition, TargetPosition, TargetVelocity, Myself->WeaponProjectileSpeed, Angle);
			}
		}

		Angle = Resolver::CalculateAngle(CameraPosition, TargetPosition);
		return true;
	}

	bool IsValidTarget(Player* target) {
		if (Features::Aimbot::TeamCheck) {
			if (Features::Aimbot::VisCheck) {
				if (target == nullptr ||
					!target->IsCombatReady() ||
					!target->IsVisible ||
					!target->IsHostile ||
					target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Aimbot::AdvancedMinDistance1) ||
					target->Distance2DToLocalPlayer > Conversion::ToGameUnits(Features::Aimbot::AdvancedMaxDistance1)) // Ignore the advanced part, works for advanced + simple aimbot
					return false;
				return true;
			}
			if (!Features::Aimbot::VisCheck) {
				if (target == nullptr ||
					!target->IsCombatReady() ||
					!target->IsHostile ||
					target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Aimbot::AdvancedMinDistance1) ||
					target->Distance2DToLocalPlayer > Conversion::ToGameUnits(Features::Aimbot::AdvancedMaxDistance1)) // Ignore the advanced part, works for advanced + simple aimbot
					return false;
				return true;
			}
		}
		if (!Features::Aimbot::TeamCheck) {
			if (Features::Aimbot::VisCheck) {
				if (target == nullptr ||
					!target->IsCombatReady() ||
					!target->IsVisible ||
					target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Aimbot::AdvancedMinDistance1) ||
					target->Distance2DToLocalPlayer > Conversion::ToGameUnits(Features::Aimbot::AdvancedMaxDistance1)) // Ignore the advanced part, works for advanced + simple aimbot
					return false;
				return true;
			}
			if (!Features::Aimbot::VisCheck) {
				if (target == nullptr ||
					!target->IsCombatReady() ||
					target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Aimbot::AdvancedMinDistance1) ||
					target->Distance2DToLocalPlayer > Conversion::ToGameUnits(Features::Aimbot::AdvancedMaxDistance1)) // Ignore the advanced part, works for advanced + simple aimbot
					return false;
				return true;
			}
		}
	}

	double CalculateDistanceFromCrosshair(Vector3D TargetPosition) {
		Vector3D CameraPosition = Myself->CameraPosition;
		QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();

		if (CameraPosition.Distance(TargetPosition) <= 0.0001f)
			return -1;

		QAngle TargetAngle = Resolver::CalculateAngle(CameraPosition, TargetPosition);
		if (!TargetAngle.isValid())
			return -1;

		return CurrentAngle.distanceTo(TargetAngle);
	}

	void ReleaseTarget() {
		if (CurrentTarget != nullptr && CurrentTarget->IsValid())
			CurrentTarget->IsLockedOn = false;

		TargetSelected = false;
		CurrentTarget = nullptr;
	}

	float GetFOVScale() {
		if (Myself->IsValid()) {
			if (Myself->IsZooming) {
				if (Myself->TargetZoomFOV > 1.0 && Myself->TargetZoomFOV < 90.0) {
					return tanf(DEG2RAD(Myself->TargetZoomFOV) * (0.64285714285));
				}
			}
		}
		return 1.0;
	}

	int GetBestBone(Player* Target) {
		float NearestDistance = 999;
		int NearestBone = 2;
		for (int i = 0; i < 6; i++) {
			HitboxType Bone = static_cast<HitboxType>(i);
			double DistanceFromCrosshair = CalculateDistanceFromCrosshair(Target->GetBonePosition(Bone));
			if (DistanceFromCrosshair < NearestDistance) {
				NearestBone = i;
				NearestDistance = DistanceFromCrosshair;
			}
		}
		return NearestBone;
	}

	Player* FindBestTarget() {
		Player* NearestTarget = nullptr;
		float BestDistance = 9999;
		float BestFOV = (std::min)(Features::Aimbot::FOV, Features::Aimbot::FOV * (GetFOVScale() * Features::Aimbot::ZoomScale));
		float LastPov = 9999;
		Vector3D CameraPosition = Myself->CameraPosition;
		for (int i = 0; i < Players->size(); i++) {
			Player* p = Players->at(i);
			if (!IsValidTarget(p))
				continue;
			if (p->DistanceToLocalPlayer > Conversion::ToGameUnits(Features::Aimbot::AdvancedMinDistance1) && p->DistanceToLocalPlayer < Conversion::ToGameUnits(Features::Aimbot::AdvancedMaxDistance1)) {
				HitboxType BestBone = static_cast<HitboxType>(GetBestBone(p));
				Vector3D TargetPosition = p->GetBonePosition(BestBone);

				float Distance = CameraPosition.Distance(TargetPosition);
				float FOV = CalculateDistanceFromCrosshair(TargetPosition);

				if (FOV > BestFOV)
					continue;

				if (Features::Aimbot::Priority == 0 && FOV > LastPov)
					continue;

				if (Features::Aimbot::Priority == 1 && Distance > BestDistance)
					continue;

				if (Features::Aimbot::Priority == 2 && FOV > LastPov && Distance > BestDistance)
					continue;

				NearestTarget = p;
				BestDistance = Distance;
				LastPov = FOV;
			}
		}
		return NearestTarget;
	}

	// Grinder Aimbot

	void moveMouse() {
		// calculate smoothing
		float EXTRA_SMOOTH;
		if (Features::Aimbot::AdvancedAim) {
			EXTRA_SMOOTH = Features::Aimbot::AdvancedExtraSmooth1 / CurrentTarget->DistanceToLocalPlayer;
		}

		else {
			EXTRA_SMOOTH = Features::Aimbot::ExtraSmoothing / CurrentTarget->DistanceToLocalPlayer;
		}

		float TOTAL_SMOOTH;
		if (Features::Aimbot::AdvancedAim) {
			if (Myself->IsZooming) {
				TOTAL_SMOOTH = Features::Aimbot::AdvancedADSSmooth1 + EXTRA_SMOOTH;
			}

			else {
				TOTAL_SMOOTH = Features::Aimbot::AdvancedHipfireSmooth1 + EXTRA_SMOOTH;
			}
		} else if (!Features::Aimbot::AdvancedAim) {
			if (Myself->IsZooming) // ADS
			{
				if (Features::Aimbot::SmoothingMethod == 0) // Static
				{
					TOTAL_SMOOTH = Features::Aimbot::ADSSmooth1 + EXTRA_SMOOTH;
				} else if (Features::Aimbot::SmoothingMethod == 1) // Random
				{
					TOTAL_SMOOTH = (RandomSmoothing(Features::Aimbot::MinADSSmooth1, Features::Aimbot::MaxHipfireSmooth1)) + EXTRA_SMOOTH;
				}
			}

			else // Hipfire
			{
				if (Features::Aimbot::SmoothingMethod == 0) // Static
				{
					TOTAL_SMOOTH = Features::Aimbot::HipfireSmooth1 + EXTRA_SMOOTH;
				} else if (Features::Aimbot::SmoothingMethod == 1) // Random
				{
					TOTAL_SMOOTH = (RandomSmoothing(Features::Aimbot::MinHipfireSmooth1, Features::Aimbot::MaxHipfireSmooth1)) + EXTRA_SMOOTH;
				}
			}
		}

		// Aimbot calcs
		const FloatVector2D aimbotDelta = CurrentTarget->aimbotDesiredAnglesIncrement
			.multiply(100)
			.divide(TOTAL_SMOOTH);

		const double aimYawIncrement = aimbotDelta.y * -1;
		const double aimPitchIncrement = aimbotDelta.x;
		// combine
		const double totalPitchIncrement = aimPitchIncrement;
		const double totalYawIncrement = aimYawIncrement;
		// turn into integers
		int totalPitchIncrementInt = RoundHalfEven(AL1AF0(totalPitchIncrement));
		int totalYawIncrementInt = RoundHalfEven(AL1AF0(totalYawIncrement));
		// deadzone - are we close enough yet?
		if (Features::Aimbot::AdvancedAim) {
			if (fabs(CurrentTarget->aimbotDesiredAnglesIncrement.x) < Features::Aimbot::AdvancedDeadzone)
				totalPitchIncrementInt = 0;
			if (fabs(CurrentTarget->aimbotDesiredAnglesIncrement.y) < Features::Aimbot::AdvancedDeadzone)
				totalYawIncrementInt = 0;
		}

		else if (!Features::Aimbot::AdvancedAim) {
			if (fabs(CurrentTarget->aimbotDesiredAnglesIncrement.x) < Features::Aimbot::Deadzone)
				totalPitchIncrementInt = 0;
			if (fabs(CurrentTarget->aimbotDesiredAnglesIncrement.y) < Features::Aimbot::Deadzone)
				totalYawIncrementInt = 0;
		}

		if (totalPitchIncrementInt == 0 && totalYawIncrementInt == 0)
			return;
		// move mouse
		DHID->MoveMouse(totalPitchIncrementInt, totalYawIncrementInt);
	}

	bool active() {
		bool aimbotIsOn = Features::Aimbot::AimbotEnabled;
		bool combatReady = Myself->IsCombatReady();
		int weaponId = Myself->WeaponIndex;
		bool weaponDiscarded = Myself->weaponDiscarded;

		bool activatedByAimBind = InputManager::isKeyDownOrPress(Features::AimbotBinds::AimBind);
		bool activatedByExtraBind = InputManager::isKeyDownOrPress(Features::AimbotBinds::ExtraBind);
		bool activatedByAttackingAndIsAttacking = Features::Aimbot::OnFire && Myself->IsInAttack;
		bool activatedByADSAndIsADSing = Features::Aimbot::OnADS && Myself->IsZooming;
		if (Features::Aimbot::BindMethod == 0) { // OnFire and OnADS
			bool active = aimbotIsOn && combatReady && !weaponDiscarded && (activatedByAttackingAndIsAttacking || activatedByADSAndIsADSing);
			return active;
		} else if (Features::Aimbot::BindMethod == 1) { // Keybinds
			bool active = aimbotIsOn && combatReady && !weaponDiscarded && (activatedByAimBind || activatedByExtraBind);
			return active;
		}
	}

	void assignTarget() {
		for (int i = 0; i < Players->size(); i++) {
			Player* p = Players->at(i);
			if (Features::Aimbot::TeamCheck) {
				if (!p->IsCombatReady())
					continue;
				if (!p->IsHostile)
					continue;
				if (!p->IsVisible)
					continue;
				if (p->IsAimedAt)
					continue;
				if (fabs(p->aimbotDesiredAnglesIncrement.x) > Features::Aimbot::FOV1)
					continue;
				if (fabs(p->aimbotDesiredAnglesIncrement.y) > Features::Aimbot::FOV1)
					continue;
				if (CurrentTarget == nullptr || p->aimbotScore > CurrentTarget->aimbotScore) {
					CurrentTarget = p;
					CurrentTarget->IsLockedOn = true;
				}
			}
			if (!Features::Aimbot::TeamCheck) {
				if (!p->IsCombatReady())
					continue;
				if (!p->IsVisible)
					continue;
				if (p->IsAimedAt)
					continue;
				if (fabs(p->aimbotDesiredAnglesIncrement.x) > Features::Aimbot::FOV1)
					continue;
				if (fabs(p->aimbotDesiredAnglesIncrement.y) > Features::Aimbot::FOV1)
					continue;
				if (CurrentTarget == nullptr || p->aimbotScore > CurrentTarget->aimbotScore) {
					CurrentTarget = p;
					CurrentTarget->IsLockedOn = true;
				}
			}
		}
	}

	void releaseTarget() {
		if (CurrentTarget != nullptr && CurrentTarget->IsValid())
			CurrentTarget->IsLockedOn = false;
		TargetSelected = false;
		CurrentTarget = nullptr;
	}

	void resetLockFlag() {
		for (int i = 0; i < Players->size(); i++) {
			Player* p = Players->at(i);
			if (!p->IsCombatReady())
				continue;
			p->IsLockedOn = false;
		}
		if (CurrentTarget != nullptr)
			CurrentTarget->IsLockedOn = true;
	}

	// Math

	float RandomSmoothing(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	float CalculatePitchIncrement(QAngle AimbotDesiredAngles) {
		float wayA = AimbotDesiredAngles.x - Myself->ViewAngles.x;
		float wayB = 180 - abs(wayA);
		if (wayA > 0 && wayB > 0)
			wayB *= -1;
		if (fabs(wayA) < fabs(wayB))
			return wayA;
		return wayB;
	}

	float CalculateYawIncrement(QAngle AimbotDesiredAngles) {
		float wayA = AimbotDesiredAngles.y - Myself->ViewAngles.y;
		float wayB = 360 - abs(wayA);
		if (wayA > 0 && wayB > 0)
			wayB *= -1;
		if (fabs(wayA) < fabs(wayB))
			return wayA;
		return wayB;
	}

	static int RoundHalfEven(float x) {
		return (x >= 0.0)
			? static_cast<int>(std::round(x))
			: static_cast<int>(std::round(-x)) * -1;
	}

	static float AL1AF0(float num) {
		if (num > 0)
			return (std::max)(num, 1.0f);
		return (std::min)(num, -1.0f);
	}

	// Updating Settings For Advanced Options
	void UpdateAimbotSettings() {
		if (!Features::Aimbot::AdvancedAim) {
			return;
		}
		int weaponHeld = Myself->WeaponIndex;
		// Keybinds && Deadzone
		if (Features::Aimbot::AdvancedAim) {
			if (weaponHeld == WeaponIDs::P2020) { // P2020
				Features::AimbotBinds::AimBind = Features::AimbotBinds::P2020AimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::P2020ExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::P2020Fire;
				Features::Aimbot::OnADS = Features::Aimbot::P2020ADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::P2020Deadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::P2020ClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::P2020Hitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::P2020Speed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::P2020HipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::P2020ADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::P2020SmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::P2020MinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::P2020MaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::P2020MinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::P2020MaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::P2020HipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::P2020ADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::P2020MinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::P2020MaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::P2020MinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::P2020MaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::P2020ExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::P2020FOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::P2020MinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::P2020MaxDistance1;
			}
			if (weaponHeld == WeaponIDs::RE45) { // RE45
				Features::AimbotBinds::AimBind = Features::AimbotBinds::RE45AimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::RE45ExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::RE45Fire;
				Features::Aimbot::OnADS = Features::Aimbot::RE45ADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::RE45Deadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::RE45ClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::RE45Hitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::RE45Speed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::RE45HipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::RE45ADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::RE45SmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::RE45MinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::RE45MaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::RE45MinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::RE45MaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::RE45HipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::RE45ADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::RE45MinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::RE45MaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::RE45MinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::RE45MaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::RE45ExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::RE45FOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::RE45MinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::RE45MaxDistance1;
			}
			if (weaponHeld == WeaponIDs::ALTERNATOR) { // Alternator
				Features::AimbotBinds::AimBind = Features::AimbotBinds::AlternatorAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::AlternatorExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::AlternatorFire;
				Features::Aimbot::OnADS = Features::Aimbot::AlternatorADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::AlternatorDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::AlternatorClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::AlternatorHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::AlternatorSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::AlternatorHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::AlternatorADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::AlternatorSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::AlternatorMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::AlternatorMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::AlternatorMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::AlternatorMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::AlternatorHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::AlternatorADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::AlternatorMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::AlternatorMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::AlternatorMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::AlternatorMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::AlternatorExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::AlternatorFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::AlternatorMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::AlternatorMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::R99) { // R99
				Features::AimbotBinds::AimBind = Features::AimbotBinds::R99AimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::R99ExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::R99Fire;
				Features::Aimbot::OnADS = Features::Aimbot::R99ADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::R99Deadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::R99ClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::R99Hitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::R99Speed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::R99HipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::R99ADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::R99SmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::R99MinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::R99MaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::R99MinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::R99MaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::R99HipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::R99ADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::R99MinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::R99MaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::R99MinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::R99MaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::R99ExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::R99FOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::R99MinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::R99MaxDistance1;
			}
			if (weaponHeld == WeaponIDs::R301) { // R301
				Features::AimbotBinds::AimBind = Features::AimbotBinds::R301AimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::R301ExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::R301Fire;
				Features::Aimbot::OnADS = Features::Aimbot::R301ADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::R301Deadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::R301ClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::R301Hitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::R301Speed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::R301HipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::R301ADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::R301SmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::R301MinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::R301MaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::R301MinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::R301MaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::R301HipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::R301ADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::R301MinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::R301MaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::R301MinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::R301MaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::R301ExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::R301FOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::R301MinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::R301MaxDistance1;
			}
			if (weaponHeld == WeaponIDs::SPITFIRE) { // Spitfire
				Features::AimbotBinds::AimBind = Features::AimbotBinds::SpitfireAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::SpitfireExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::SpitfireFire;
				Features::Aimbot::OnADS = Features::Aimbot::SpitfireADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::SpitfireDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::SpitfireClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::SpitfireHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::SpitfireSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::SpitfireHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::SpitfireADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::SpitfireSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::SpitfireMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::SpitfireMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::SpitfireMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::SpitfireMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::SpitfireHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::SpitfireADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::SpitfireMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::SpitfireMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::SpitfireMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::SpitfireMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::SpitfireExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::SpitfireFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::SpitfireMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::SpitfireMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::G7) { // G7
				Features::AimbotBinds::AimBind = Features::AimbotBinds::G7AimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::G7ExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::G7Fire;
				Features::Aimbot::OnADS = Features::Aimbot::G7ADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::G7Deadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::G7ClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::G7Hitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::G7Speed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::G7HipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::G7ADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::G7SmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::G7MinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::G7MaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::G7MinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::G7MaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::G7HipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::G7ADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::G7MinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::G7MaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::G7MinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::G7MaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::G7ExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::G7FOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::G7MinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::G7MaxDistance1;
			}
			// Heavy Weapons
			if (weaponHeld == WeaponIDs::CAR) { // CARSMG
				Features::AimbotBinds::AimBind = Features::AimbotBinds::CARSMGAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::CARSMGExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::CARSMGFire;
				Features::Aimbot::OnADS = Features::Aimbot::CARSMGADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::CARSMGDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::CARSMGClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::CARSMGHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::CARSMGSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::CARSMGHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::CARSMGADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::CARSMGSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::CARSMGMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::CARSMGMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::CARSMGMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::CARSMGMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::CARSMGHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::CARSMGADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::CARSMGMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::CARSMGMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::CARSMGMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::CARSMGMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::CARSMGExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::CARSMGFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::CARSMGMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::CARSMGMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::RAMPAGE) { // Rampage
				Features::AimbotBinds::AimBind = Features::AimbotBinds::RampageAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::RampageExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::RampageFire;
				Features::Aimbot::OnADS = Features::Aimbot::RampageADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::RampageDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::RampageClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::RampageHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::RampageSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::RampageHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::RampageADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::RampageSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::RampageMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::RampageMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::RampageMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::RampageMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::RampageHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::RampageADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::RampageMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::RampageMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::RampageMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::RampageMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::RampageExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::RampageFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::RampageMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::RampageMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::REPEATER) { // Repeater
				Features::AimbotBinds::AimBind = Features::AimbotBinds::RepeaterAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::RepeaterExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::RepeaterFire;
				Features::Aimbot::OnADS = Features::Aimbot::RepeaterADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::RepeaterDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::RepeaterClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::RepeaterHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::RepeaterSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::RepeaterHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::RepeaterADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::RepeaterSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::RepeaterMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::RepeaterMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::RepeaterMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::RepeaterMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::RepeaterHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::RepeaterADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::RepeaterMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::RepeaterMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::RepeaterMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::RepeaterMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::RepeaterExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::RepeaterFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::RepeaterMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::RepeaterMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::PROWLER) { // Prowler
				Features::AimbotBinds::AimBind = Features::AimbotBinds::ProwlerAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::ProwlerExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::ProwlerFire;
				Features::Aimbot::OnADS = Features::Aimbot::ProwlerADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::ProwlerDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::ProwlerClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::ProwlerHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::ProwlerSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::ProwlerHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::ProwlerADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::ProwlerSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::ProwlerMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::ProwlerMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::ProwlerMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::ProwlerMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::ProwlerHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::ProwlerADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::ProwlerMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::ProwlerMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::ProwlerMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::ProwlerMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::ProwlerExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::ProwlerFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::ProwlerMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::ProwlerMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::HEMLOCK) { // Hemlock
				Features::AimbotBinds::AimBind = Features::AimbotBinds::HemlockAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::HemlockExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::HemlockFire;
				Features::Aimbot::OnADS = Features::Aimbot::HemlockADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::HemlockDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::HemlockClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::HemlockHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::HemlockSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::HemlockHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::HemlockADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::HemlockSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::HemlockMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::HemlockMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::HemlockMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::HemlockMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::HemlockHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::HemlockADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::HemlockMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::HemlockMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::HemlockMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::HemlockMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::HemlockExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::HemlockFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::HemlockMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::HemlockMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::FLATLINE) { // Flatline
				Features::AimbotBinds::AimBind = Features::AimbotBinds::FlatlineAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::FlatlineExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::FlatlineFire;
				Features::Aimbot::OnADS = Features::Aimbot::FlatlineADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::FlatlineDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::FlatlineClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::FlatlineHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::FlatlineSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::FlatlineHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::FlatlineADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::FlatlineSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::FlatlineMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::FlatlineMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::FlatlineMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::FlatlineMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::FlatlineHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::FlatlineADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::FlatlineMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::FlatlineMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::FlatlineMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::FlatlineMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::FlatlineExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::FlatlineFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::FlatlineMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::FlatlineMaxDistance1;
			}
			// Energy Weapons
			if (weaponHeld == WeaponIDs::NEMESIS) { // Nemesis
				Features::AimbotBinds::AimBind = Features::AimbotBinds::NemesisAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::NemesisExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::NemesisFire;
				Features::Aimbot::OnADS = Features::Aimbot::NemesisADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::NemesisDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::NemesisClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::NemesisHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::NemesisSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::NemesisHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::NemesisADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::NemesisSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::NemesisMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::NemesisMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::NemesisMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::NemesisMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::NemesisHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::NemesisADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::NemesisMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::NemesisMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::NemesisMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::NemesisMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::NemesisExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::NemesisFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::NemesisMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::NemesisMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::VOLT) { // Volt
				Features::AimbotBinds::AimBind = Features::AimbotBinds::VoltAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::VoltExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::VoltFire;
				Features::Aimbot::OnADS = Features::Aimbot::VoltADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::VoltDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::VoltClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::VoltHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::VoltSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::VoltHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::VoltADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::VoltSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::VoltMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::VoltMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::VoltMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::VoltMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::VoltHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::VoltADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::VoltMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::VoltMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::VoltMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::VoltMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::VoltExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::VoltFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::VoltMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::VoltMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::TRIPLETAKE) { // TripleTake
				Features::AimbotBinds::AimBind = Features::AimbotBinds::TripleTakeAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::TripleTakeExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::TripleTakeFire;
				Features::Aimbot::OnADS = Features::Aimbot::TripleTakeADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::TripleTakeDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::TripleTakeClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::TripleTakeHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::TripleTakeSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::TripleTakeHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::TripleTakeADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::TripleTakeSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::TripleTakeMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::TripleTakeMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::TripleTakeMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::TripleTakeMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::TripleTakeHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::TripleTakeADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::TripleTakeMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::TripleTakeMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::TripleTakeMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::TripleTakeMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::TripleTakeExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::TripleTakeFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::TripleTakeMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::TripleTakeMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::LSTAR) { // LSTAR
				Features::AimbotBinds::AimBind = Features::AimbotBinds::LSTARAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::LSTARExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::LSTARFire;
				Features::Aimbot::OnADS = Features::Aimbot::LSTARADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::LSTARDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::LSTARClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::LSTARHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::LSTARSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::LSTARHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::LSTARADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::LSTARSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::LSTARMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::LSTARMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::LSTARMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::LSTARMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::LSTARHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::LSTARADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::LSTARMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::LSTARMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::LSTARMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::LSTARMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::LSTARExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::LSTARFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::LSTARMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::LSTARMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::DEVOTION) { // Devotion
				Features::AimbotBinds::AimBind = Features::AimbotBinds::DevotionAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::DevotionExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::DevotionFire;
				Features::Aimbot::OnADS = Features::Aimbot::DevotionADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::DevotionDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::DevotionClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::DevotionHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::DevotionSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::DevotionHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::DevotionADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::DevotionSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::DevotionMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::DevotionMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::DevotionMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::DevotionMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::DevotionHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::DevotionADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::DevotionMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::DevotionMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::DevotionMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::DevotionMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::DevotionExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::DevotionFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::DevotionMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::DevotionMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::HAVOC) { // Havoc
				Features::AimbotBinds::AimBind = Features::AimbotBinds::HavocAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::HavocExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::HavocFire;
				Features::Aimbot::OnADS = Features::Aimbot::HavocADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::HavocDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::HavocClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::HavocHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::HavocSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::HavocHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::HavocADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::HavocSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::HavocMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::HavocMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::HavocMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::HavocMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::HavocHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::HavocADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::HavocMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::HavocMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::HavocMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::HavocMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::HavocExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::HavocFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::HavocMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::HavocMaxDistance1;
			}
			// Shotguns
			if (weaponHeld == WeaponIDs::MOZAMBIQUE) { // Mozambique
				Features::AimbotBinds::AimBind = Features::AimbotBinds::MozambiqueAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::MozambiqueExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::MozambiqueFire;
				Features::Aimbot::OnADS = Features::Aimbot::MozambiqueADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::MozambiqueDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::MozambiqueClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::MozambiqueHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::MozambiqueSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::MozambiqueHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::MozambiqueADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::MozambiqueSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::MozambiqueMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::MozambiqueMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::MozambiqueMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::MozambiqueMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::MozambiqueHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::MozambiqueADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::MozambiqueMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::MozambiqueMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::MozambiqueMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::MozambiqueMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::MozambiqueExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::MozambiqueFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::MozambiqueMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::MozambiqueMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::PEACEKEEPER) { // Peacekeeper
				Features::AimbotBinds::AimBind = Features::AimbotBinds::PeacekeeperAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::PeacekeeperExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::PeacekeeperFire;
				Features::Aimbot::OnADS = Features::Aimbot::PeacekeeperADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::PeacekeeperDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::PeacekeeperClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::PeacekeeperHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::PeacekeeperSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::PeacekeeperHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::PeacekeeperADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::PeacekeeperSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::PeacekeeperMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::PeacekeeperMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::PeacekeeperMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::PeacekeeperMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::PeacekeeperHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::PeacekeeperADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::PeacekeeperMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::PeacekeeperMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::PeacekeeperMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::PeacekeeperMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::PeacekeeperExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::PeacekeeperFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::PeacekeeperMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::PeacekeeperMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::MASTIFF) { // Mastiff
				Features::AimbotBinds::AimBind = Features::AimbotBinds::MastiffAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::MastiffExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::MastiffFire;
				Features::Aimbot::OnADS = Features::Aimbot::MastiffADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::MastiffDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::MastiffClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::MastiffHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::MastiffSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::MastiffHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::MastiffADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::MastiffSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::MastiffMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::MastiffMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::MastiffMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::MastiffMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::MastiffHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::MastiffADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::MastiffMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::MastiffMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::MastiffMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::MastiffMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::MastiffExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::MastiffFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::MastiffMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::MastiffMaxDistance1;
			}
			// Snipers
			if (weaponHeld == WeaponIDs::SENTINEL) { // Sentinel
				Features::AimbotBinds::AimBind = Features::AimbotBinds::SentinelAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::SentinelExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::SentinelFire;
				Features::Aimbot::OnADS = Features::Aimbot::SentinelADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::SentinelDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::SentinelClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::SentinelHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::SentinelSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::SentinelHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::SentinelADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::SentinelSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::SentinelMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::SentinelMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::SentinelMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::SentinelMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::SentinelHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::SentinelADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::SentinelMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::SentinelMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::SentinelMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::SentinelMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::SentinelExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::SentinelFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::SentinelMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::SentinelMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::CHARGE_RIFLE) { // ChargeRifle
				Features::AimbotBinds::AimBind = Features::AimbotBinds::ChargeRifleAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::ChargeRifleExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::ChargeRifleFire;
				Features::Aimbot::OnADS = Features::Aimbot::ChargeRifleADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::ChargeRifleDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::ChargeRifleClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::ChargeRifleHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::ChargeRifleSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::ChargeRifleHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::ChargeRifleADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::ChargeRifleSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::ChargeRifleMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::ChargeRifleMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::ChargeRifleMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::ChargeRifleMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::ChargeRifleHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::ChargeRifleADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::ChargeRifleMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::ChargeRifleMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::ChargeRifleMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::ChargeRifleMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::ChargeRifleExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::ChargeRifleFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::ChargeRifleMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::ChargeRifleMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::LONGBOW) { // Longbow
				Features::AimbotBinds::AimBind = Features::AimbotBinds::LongbowAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::LongbowExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::LongbowFire;
				Features::Aimbot::OnADS = Features::Aimbot::LongbowADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::LongbowDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::LongbowClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::LongbowHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::LongbowSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::LongbowHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::LongbowADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::LongbowSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::LongbowMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::LongbowMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::LongbowMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::LongbowMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::LongbowHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::LongbowADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::LongbowMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::LongbowMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::LongbowMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::LongbowMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::LongbowExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::LongbowFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::LongbowMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::LongbowMaxDistance1;
			}
			// Legendary Weapons
			if (weaponHeld == WeaponIDs::WINGMAN) { // Wingman
				Features::AimbotBinds::AimBind = Features::AimbotBinds::WingmanAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::WingmanExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::WingmanFire;
				Features::Aimbot::OnADS = Features::Aimbot::WingmanADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::WingmanDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::WingmanClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::WingmanHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::WingmanSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::WingmanHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::WingmanADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::WingmanSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::WingmanMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::WingmanMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::WingmanMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::WingmanMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::WingmanHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::WingmanADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::WingmanMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::WingmanMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::WingmanMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::WingmanMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::WingmanExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::WingmanFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::WingmanMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::WingmanMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::EVA8) { // EVA8
				Features::AimbotBinds::AimBind = Features::AimbotBinds::EVA8AimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::EVA8ExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::EVA8Fire;
				Features::Aimbot::OnADS = Features::Aimbot::EVA8ADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::EVA8Deadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::EVA8ClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::EVA8Hitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::EVA8Speed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::EVA8HipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::EVA8ADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::EVA8SmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::EVA8MinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::EVA8MaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::EVA8MinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::EVA8MaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::EVA8HipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::EVA8ADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::EVA8MinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::EVA8MaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::EVA8MinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::EVA8MaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::EVA8ExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::EVA8FOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::EVA8MinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::EVA8MaxDistance1;
			}
			if (weaponHeld == WeaponIDs::BOCEK) { // Bocek
				Features::AimbotBinds::AimBind = Features::AimbotBinds::BocekAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::BocekExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::BocekFire;
				Features::Aimbot::OnADS = Features::Aimbot::BocekADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::BocekDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::BocekClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::BocekHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::BocekSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::BocekHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::BocekADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::BocekSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::BocekMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::BocekMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::BocekMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::BocekMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::BocekHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::BocekADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::BocekMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::BocekMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::BocekMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::BocekMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::BocekExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::BocekFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::BocekMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::BocekMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::KRABER) { // Kraber
				Features::AimbotBinds::AimBind = Features::AimbotBinds::KraberAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::KraberExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::KraberFire;
				Features::Aimbot::OnADS = Features::Aimbot::KraberADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::KraberDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::KraberClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::KraberHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::KraberSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::KraberHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::KraberADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::KraberSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::KraberMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::KraberMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::KraberMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::KraberMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::KraberHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::KraberADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::KraberMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::KraberMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::KraberMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::KraberMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::KraberExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::KraberFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::KraberMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::KraberMaxDistance1;
			}
			if (weaponHeld == WeaponIDs::KNIFE) { // ThrowingKnife
				Features::AimbotBinds::AimBind = Features::AimbotBinds::ThrowingKnifeAimBind;
				Features::AimbotBinds::ExtraBind = Features::AimbotBinds::ThrowingKnifeExtraBind;
				Features::Aimbot::OnFire = Features::Aimbot::ThrowingKnifeFire;
				Features::Aimbot::OnADS = Features::Aimbot::ThrowingKnifeADS;
				Features::Aimbot::AdvancedDeadzone = Features::Aimbot::ThrowingKnifeDeadzone;

				Features::Aimbot::ClosestHitbox = Features::Aimbot::ThrowingKnifeClosestHitbox;
				Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Features::AimbotHitboxes::ThrowingKnifeHitbox);
				Features::Aimbot::AdvancedSpeed = Features::Aimbot::ThrowingKnifeSpeed;
				Features::Aimbot::AdvancedHipfireSmooth = Features::Aimbot::ThrowingKnifeHipfireSmooth;
				Features::Aimbot::AdvancedADSSmooth = Features::Aimbot::ThrowingKnifeADSSmooth;
				Features::Aimbot::AdvancedSmoothingMethod = Features::Aimbot::ThrowingKnifeSmoothingMethod;
				Features::Aimbot::AdvancedMinHipfireSmooth = Features::Aimbot::ThrowingKnifeMinHipfireSmooth;
				Features::Aimbot::AdvancedMaxHipfireSmooth = Features::Aimbot::ThrowingKnifeMaxHipfireSmooth;
				Features::Aimbot::AdvancedMinADSSmooth = Features::Aimbot::ThrowingKnifeMinADSSmooth;
				Features::Aimbot::AdvancedMaxADSSmooth = Features::Aimbot::ThrowingKnifeMaxADSSmooth;

				Features::Aimbot::AdvancedHipfireSmooth1 = Features::Aimbot::ThrowingKnifeHipfireSmooth1;
				Features::Aimbot::AdvancedADSSmooth1 = Features::Aimbot::ThrowingKnifeADSSmooth1;
				Features::Aimbot::AdvancedMinHipfireSmooth1 = Features::Aimbot::ThrowingKnifeMinHipfireSmooth1;
				Features::Aimbot::AdvancedMaxHipfireSmooth1 = Features::Aimbot::ThrowingKnifeMaxHipfireSmooth1;
				Features::Aimbot::AdvancedMinADSSmooth1 = Features::Aimbot::ThrowingKnifeMinADSSmooth1;
				Features::Aimbot::AdvancedMaxADSSmooth1 = Features::Aimbot::ThrowingKnifeMaxADSSmooth1;
				Features::Aimbot::AdvancedExtraSmooth1 = Features::Aimbot::ThrowingKnifeExtraSmooth1;
				Features::Aimbot::AdvancedFOV1 = Features::Aimbot::ThrowingKnifeFOV1;
				Features::Aimbot::AdvancedMinDistance1 = Features::Aimbot::ThrowingKnifeMinDistance1;
				Features::Aimbot::AdvancedMaxDistance1 = Features::Aimbot::ThrowingKnifeMaxDistance1;
			}
		}
	}

	void UpdateRCSSettings() {
		if (!Features::RCS::AdvancedRCS) {
			return;
		}

		int weaponHeld = Myself->WeaponIndex;

		if (Features::RCS::AdvancedRCS) {
			if (weaponHeld == WeaponIDs::P2020) { // P2020
				Features::RCS::AdvancedPitchPower = Features::RCS::P2020Pitch;
				Features::RCS::AdvancedYawPower = Features::RCS::P2020Yaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::P2020PitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::P2020YawReduction;
			}
			if (weaponHeld == WeaponIDs::RE45) { // RE-45
				Features::RCS::AdvancedPitchPower = Features::RCS::RE45Pitch;
				Features::RCS::AdvancedYawPower = Features::RCS::RE45Yaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::RE45PitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::RE45YawReduction;
			}
			if (weaponHeld == WeaponIDs::ALTERNATOR) { // Alternator
				Features::RCS::AdvancedPitchPower = Features::RCS::AlternatorPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::AlternatorYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::AlternatorPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::AlternatorYawReduction;
			}
			if (weaponHeld == WeaponIDs::R99) { // R-99
				Features::RCS::AdvancedPitchPower = Features::RCS::R99Pitch;
				Features::RCS::AdvancedYawPower = Features::RCS::R99Yaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::R99PitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::R99YawReduction;
			}
			if (weaponHeld == WeaponIDs::R301) { // R-301
				Features::RCS::AdvancedPitchPower = Features::RCS::R301Pitch;
				Features::RCS::AdvancedYawPower = Features::RCS::R301Yaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::R301PitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::R301YawReduction;
			}
			if (weaponHeld == WeaponIDs::SPITFIRE) { // Spitfire
				Features::RCS::AdvancedPitchPower = Features::RCS::SpitfirePitch;
				Features::RCS::AdvancedYawPower = Features::RCS::SpitfireYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::SpitfirePitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::SpitfireYawReduction;
			}
			if (weaponHeld == WeaponIDs::G7) { // G7
				Features::RCS::AdvancedPitchPower = Features::RCS::G7Pitch;
				Features::RCS::AdvancedYawPower = Features::RCS::G7Yaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::G7PitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::G7YawReduction;
			}
			// Heavy Weapons
			if (weaponHeld == WeaponIDs::CAR) { // CARSMG
				Features::RCS::AdvancedPitchPower = Features::RCS::CARSMGPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::CARSMGYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::CARSMGPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::CARSMGYawReduction;
			}
			if (weaponHeld == WeaponIDs::RAMPAGE) { // Rampage
				Features::RCS::AdvancedPitchPower = Features::RCS::RampagePitch;
				Features::RCS::AdvancedYawPower = Features::RCS::RampageYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::RampagePitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::RampageYawReduction;
			}
			if (weaponHeld == WeaponIDs::REPEATER) { // Repeater
				Features::RCS::AdvancedPitchPower = Features::RCS::RepeaterPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::RepeaterYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::RepeaterPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::RepeaterYawReduction;
			}
			if (weaponHeld == WeaponIDs::HEMLOCK) { // Hemlock
				Features::RCS::AdvancedPitchPower = Features::RCS::HemlockPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::HemlockYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::HemlockPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::HemlockYawReduction;
			}
			if (weaponHeld == WeaponIDs::FLATLINE) { // Flatline
				Features::RCS::AdvancedPitchPower = Features::RCS::FlatlinePitch;
				Features::RCS::AdvancedYawPower = Features::RCS::FlatlineYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::FlatlinePitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::FlatlineYawReduction;
			}
			// Energy Weapons
			if (weaponHeld == WeaponIDs::NEMESIS) { // Nemesis
				Features::RCS::AdvancedPitchPower = Features::RCS::NemesisPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::NemesisYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::NemesisPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::NemesisYawReduction;
			}
			if (weaponHeld == WeaponIDs::VOLT) { // Volt
				Features::RCS::AdvancedPitchPower = Features::RCS::VoltPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::VoltYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::VoltPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::VoltYawReduction;
			}
			if (weaponHeld == WeaponIDs::TRIPLETAKE) { // TripleTake
				Features::RCS::AdvancedPitchPower = Features::RCS::TripleTakePitch;
				Features::RCS::AdvancedYawPower = Features::RCS::TripleTakeYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::TripleTakePitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::TripleTakeYawReduction;
			}
			if (weaponHeld == WeaponIDs::LSTAR) { // LSTAR
				Features::RCS::AdvancedPitchPower = Features::RCS::LSTARPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::LSTARYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::LSTARPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::LSTARYawReduction;
			}
			if (weaponHeld == WeaponIDs::DEVOTION) { // Devotion
				Features::RCS::AdvancedPitchPower = Features::RCS::DevotionPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::DevotionYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::DevotionPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::DevotionYawReduction;
			}
			if (weaponHeld == WeaponIDs::HAVOC) { // Havoc
				Features::RCS::AdvancedPitchPower = Features::RCS::HavocPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::HavocYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::HavocPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::HavocYawReduction;
			}
			// Shotguns
			if (weaponHeld == WeaponIDs::MOZAMBIQUE) { // Mozambique
				Features::RCS::AdvancedPitchPower = Features::RCS::MozambiquePitch;
				Features::RCS::AdvancedYawPower = Features::RCS::MozambiqueYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::MozambiquePitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::MozambiqueYawReduction;
			}
			if (weaponHeld == WeaponIDs::EVA8) { // EVA8
				Features::RCS::AdvancedPitchPower = Features::RCS::EVA8Pitch;
				Features::RCS::AdvancedYawPower = Features::RCS::EVA8Yaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::EVA8PitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::EVA8YawReduction;
			}
			if (weaponHeld == WeaponIDs::PEACEKEEPER) { // Peacekeeper
				Features::RCS::AdvancedPitchPower = Features::RCS::PeacekeeperPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::PeacekeeperYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::PeacekeeperPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::PeacekeeperYawReduction;
			}
			if (weaponHeld == WeaponIDs::MASTIFF) { // Mastiff
				Features::RCS::AdvancedPitchPower = Features::RCS::MastiffPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::MastiffYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::MastiffPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::MastiffYawReduction;
			}
			// Snipers
			if (weaponHeld == WeaponIDs::SENTINEL) { // Sentinel
				Features::RCS::AdvancedPitchPower = Features::RCS::SentinelPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::SentinelYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::SentinelPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::SentinelYawReduction;
			}
			if (weaponHeld == WeaponIDs::CHARGE_RIFLE) { // ChargeRifle
				Features::RCS::AdvancedPitchPower = Features::RCS::ChargeRiflePitch;
				Features::RCS::AdvancedYawPower = Features::RCS::ChargeRifleYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::ChargeRiflePitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::ChargeRifleYawReduction;
			}
			if (weaponHeld == WeaponIDs::LONGBOW) { // Longbow
				Features::RCS::AdvancedPitchPower = Features::RCS::LongbowPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::LongbowYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::LongbowPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::LongbowYawReduction;
			}
			// Legendary Weapons
			if (weaponHeld == WeaponIDs::WINGMAN) { // Wingman
				Features::RCS::AdvancedPitchPower = Features::RCS::WingmanPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::WingmanYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::WingmanPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::WingmanYawReduction;
			}
			if (weaponHeld == WeaponIDs::PROWLER) { // Prowler
				Features::RCS::AdvancedPitchPower = Features::RCS::ProwlerPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::ProwlerYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::ProwlerPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::ProwlerYawReduction;
			}
			if (weaponHeld == WeaponIDs::KRABER) { // Kraber
				Features::RCS::AdvancedPitchPower = Features::RCS::KraberPitch;
				Features::RCS::AdvancedYawPower = Features::RCS::KraberYaw;
				Features::RCS::AdvancedPitchReduction = Features::RCS::KraberPitchReduction;
				Features::RCS::AdvancedYawReduction = Features::RCS::KraberYawReduction;
			}
		}
	}

	bool IsBestTarget() // For Target Visuals
	{
		if (!Map->IsPlayable) {
			ReleaseBestTarget();
			return false;
		}

		if (!Features::Aimbot::AimbotEnabled) {
			ReleaseBestTarget();
			return false;
		}

		if (Features::Aimbot::AimbotEnabled) {
			if (Features::Home::IsMenuOpened)
				return false; // Dont aimbot whilst menu is open

			if (!Myself->IsCombatReady()) {
				BestTarget = nullptr;
				return false;
			}

			if (Features::Aimbot::AimList.find(Myself->WeaponIndex) == Features::Aimbot::AimList.end()) {
				ReleaseBestTarget();
				return false;
			}

			Player* Target = BestTarget;
			if (!Features::Aimbot::TargetSwitching) {
				if (!IsValidTarget(Target)) {
					if (TargetSelected) {
						return false;
					}

					Target = FindBestTarget();
					if (!IsValidTarget(Target)) {
						ReleaseBestTarget();
						return false;
					}

					BestTarget = Target;
					return true;
				}
			} else {
				Target = FindBestTarget();
				if (!IsValidTarget(Target)) {
					ReleaseBestTarget();
					return false;
				}

				BestTarget = Target;
				return true;
			}
		}
	}

	void ReleaseBestTarget() {
		BestTarget = nullptr;
	}

};
