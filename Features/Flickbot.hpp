#pragma once
#include <iostream>
#include <vector>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/Level.hpp"

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

#include <DriverHID.hpp>

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"


// Conversion
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))

struct Flickbot
{
	std::chrono::milliseconds LastClickTime;

	int FinalDistance = 0;

	//XDisplay* X11Display;
	DriverHID* DHID;
	LocalPlayer* Myself;
	std::vector<Player*>* Players;
	Level* Map;

	Player* CurrentTarget = nullptr;
	bool TargetSelected = true;
	std::chrono::milliseconds LastAimTime;
	std::chrono::milliseconds LastFlickTime;
	std::chrono::milliseconds LastFlickBackTime;

	Flickbot(DriverHID* DHID, Level* Map, LocalPlayer* Myself, std::vector<Player*>* GamePlayers) {
		this->DHID = DHID;
		this->Myself = Myself;
		this->Map = Map;
		this->Players = GamePlayers;
	}

	static bool Save() {
		try {

			Config::Flickbot::Flickbot = Features::Flickbot::Flickbot;
			Config::Flickbot::FlickbotMethod = Features::Flickbot::FlickbotMethod;
			Config::Flickbot::FlickBind = static_cast<int>(Features::Flickbot::FlickBind);
			Config::Flickbot::ClosestHitbox = Features::Flickbot::ClosestHitbox;
			Config::Flickbot::Hitbox = static_cast<int>(Features::Flickbot::Hitbox);
			Config::Flickbot::Priority = Features::Flickbot::Priority;
			Config::Flickbot::AutoShoot = Features::Flickbot::AutoShoot;
			Config::Flickbot::AutoShootDelay = Features::Flickbot::AutoShootDelay;
			Config::Flickbot::FlickBack = Features::Flickbot::FlickBack;
			Config::Flickbot::FlickBackDelay = Features::Flickbot::FlickBackDelay;
			Config::Flickbot::PredictMovement = Features::Flickbot::PredictMovement;
			Config::Flickbot::PredictBulletDrop = Features::Flickbot::PredictBulletDrop;
			Config::Flickbot::TeamCheck = Features::Flickbot::TeamCheck;
			Config::Flickbot::PreditcionAmount = Features::Flickbot::PreditcionAmount;
			Config::Flickbot::FinalDistance = Features::Flickbot::FinalDistance;
			Config::Flickbot::HipfireSmooth = Features::Flickbot::HipfireSmooth;
			Config::Flickbot::ADSSmooth = Features::Flickbot::ADSSmooth;
			Config::Flickbot::SmoothDistance = Features::Flickbot::SmoothDistance;
			Config::Flickbot::Delay = Features::Flickbot::Delay;
			Config::Flickbot::FOV = Features::Flickbot::FOV;
			Config::Flickbot::ZoomScale = Features::Flickbot::ZoomScale;
			Config::Flickbot::MinDistance = Features::Flickbot::MinDistance;
			Config::Flickbot::HipfireDistance = Features::Flickbot::HipfireDistance;
			Config::Flickbot::ZoomDistance = Features::Flickbot::ZoomDistance;
			//Weapon Toggles
			//Light
			Config::Flickbot::P2020 = Features::Flickbot::P2020;
			Config::Flickbot::RE45 = Features::Flickbot::RE45;
			Config::Flickbot::Alternator = Features::Flickbot::Alternator;
			Config::Flickbot::R99 = Features::Flickbot::R99;
			Config::Flickbot::R301 = Features::Flickbot::R301;
			Config::Flickbot::Spitfire = Features::Flickbot::Spitfire;
			Config::Flickbot::G7 = Features::Flickbot::G7;
			//Heavy
			Config::Flickbot::Flatline = Features::Flickbot::Flatline;
			Config::Flickbot::Hemlock = Features::Flickbot::Hemlock;
			Config::Flickbot::Repeater = Features::Flickbot::Repeater;
			Config::Flickbot::Rampage = Features::Flickbot::Rampage;
			Config::Flickbot::CARSMG = Features::Flickbot::CARSMG;
			//Energy
			Config::Flickbot::Havoc = Features::Flickbot::Havoc;
			Config::Flickbot::Devotion = Features::Flickbot::Devotion;
			Config::Flickbot::LSTAR = Features::Flickbot::LSTAR;
			Config::Flickbot::TripleTake = Features::Flickbot::TripleTake;
			Config::Flickbot::Volt = Features::Flickbot::Volt;
			Config::Flickbot::Nemesis = Features::Flickbot::Nemesis;
			//Shotgun
			Config::Flickbot::Mozambique = Features::Flickbot::Mozambique;
			Config::Flickbot::EVA8 = Features::Flickbot::EVA8;
			Config::Flickbot::Peacekeeper = Features::Flickbot::Peacekeeper;
			Config::Flickbot::Mastiff = Features::Flickbot::Mastiff;
			//Snipers
			Config::Flickbot::Longbow = Features::Flickbot::Longbow;
			Config::Flickbot::ChargeRifle = Features::Flickbot::ChargeRifle;
			Config::Flickbot::Sentinel = Features::Flickbot::Sentinel;
			//Legendary
			Config::Flickbot::Wingman = Features::Flickbot::Wingman;
			Config::Flickbot::Prowler = Features::Flickbot::Prowler;
			Config::Flickbot::Bocek = Features::Flickbot::Bocek;
			Config::Flickbot::Kraber = Features::Flickbot::Kraber;
			Config::Flickbot::Knife = Features::Flickbot::Knife;

			return true;
		} catch (...) {
			return false;
		}
	}

	void UpdateFlickList() {
		Features::Flickbot::FlickList.clear();
		// Define a lambda function to reduce repetition
		auto InsertIfEnabled = [&](const bool feature, const int weaponID) {
		if (feature)
			Features::Flickbot::FlickList.insert(weaponID);
		};
		// Light
		InsertIfEnabled(Features::Flickbot::P2020, WeaponIDs::P2020);
		InsertIfEnabled(Features::Flickbot::RE45, WeaponIDs::RE45);
		InsertIfEnabled(Features::Flickbot::Alternator, WeaponIDs::ALTERNATOR);
		InsertIfEnabled(Features::Flickbot::R99, WeaponIDs::R99);
		InsertIfEnabled(Features::Flickbot::R301, WeaponIDs::R301);
		InsertIfEnabled(Features::Flickbot::Spitfire, WeaponIDs::SPITFIRE);
		InsertIfEnabled(Features::Flickbot::G7, WeaponIDs::G7);

		// Heavy
		InsertIfEnabled(Features::Flickbot::Flatline, WeaponIDs::FLATLINE);
		InsertIfEnabled(Features::Flickbot::Prowler, WeaponIDs::PROWLER);
		InsertIfEnabled(Features::Flickbot::Hemlock, WeaponIDs::HEMLOCK);
		InsertIfEnabled(Features::Flickbot::Repeater, WeaponIDs::REPEATER);
		InsertIfEnabled(Features::Flickbot::Rampage, WeaponIDs::RAMPAGE);
		InsertIfEnabled(Features::Flickbot::CARSMG, WeaponIDs::CAR);

		// Energy
		InsertIfEnabled(Features::Flickbot::Havoc, WeaponIDs::HAVOC);
		InsertIfEnabled(Features::Flickbot::Devotion, WeaponIDs::DEVOTION);
		InsertIfEnabled(Features::Flickbot::LSTAR, WeaponIDs::LSTAR);
		InsertIfEnabled(Features::Flickbot::TripleTake, WeaponIDs::TRIPLETAKE);
		InsertIfEnabled(Features::Flickbot::Volt, WeaponIDs::VOLT);
		InsertIfEnabled(Features::Flickbot::Nemesis, WeaponIDs::NEMESIS);

		// Shotguns
		InsertIfEnabled(Features::Flickbot::Mozambique, WeaponIDs::MOZAMBIQUE);
		InsertIfEnabled(Features::Flickbot::Peacekeeper, WeaponIDs::PEACEKEEPER);
		InsertIfEnabled(Features::Flickbot::Mastiff, WeaponIDs::MASTIFF);

		// Snipers
		InsertIfEnabled(Features::Flickbot::Longbow, WeaponIDs::LONGBOW);
		InsertIfEnabled(Features::Flickbot::ChargeRifle, WeaponIDs::CHARGE_RIFLE);
		InsertIfEnabled(Features::Flickbot::Sentinel, WeaponIDs::SENTINEL);

		// Legendary
		InsertIfEnabled(Features::Flickbot::Wingman, WeaponIDs::WINGMAN);
		InsertIfEnabled(Features::Flickbot::EVA8, WeaponIDs::EVA8);
		InsertIfEnabled(Features::Flickbot::Bocek, WeaponIDs::BOCEK);
		InsertIfEnabled(Features::Flickbot::Kraber, WeaponIDs::KRABER);
		InsertIfEnabled(Features::Flickbot::Knife, WeaponIDs::KNIFE);
	}

	void Update() {
		if (!Features::Flickbot::Flickbot) {
			ReleaseTarget();
			return;
		}

		if (Features::Flickbot::Flickbot) {

			if (Myself->IsZooming)
				FinalDistance = Features::Flickbot::ZoomDistance;
			else
				FinalDistance = Features::Flickbot::HipfireDistance;

			if (!Myself->IsCombatReady()) {
				CurrentTarget = nullptr;
				return;
			}

			if (Features::Flickbot::FlickList.find(Myself->WeaponIndex) == Features::Flickbot::FlickList.end()) {
				ReleaseTarget();
				return;
			}

			if (Myself->IsHoldingGrenade) {
				ReleaseTarget();
				return;
			}

			if (!isKeybindDown()) {
				ReleaseTarget();
				return;
			}

			Player* Target = CurrentTarget;
			if (!IsValidTarget(Target)) {
				if (TargetSelected)
					return;

				Target = FindBestTarget();
				if (!IsValidTarget(Target)) {
					ReleaseTarget();
					return;
				}

				CurrentTarget = Target;
				// CurrentTarget->IsLockedOn = true;
				TargetSelected = true;
			}

			if (TargetSelected && CurrentTarget) {
				std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
				if (Now >= LastAimTime + std::chrono::milliseconds(Features::Flickbot::Delay)) {
					StartAiming();
					LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
				}
				return;
			}
		}
	}

	bool isKeybindDown() {
		bool ActivatedByAimBind = InputManager::isKeyDownOrPress(Features::Flickbot::FlickBind);
		bool active = (ActivatedByAimBind);
		return active;
	}

	void StartAiming() {
		// Get Target Angle
		QAngle DesiredAngles = QAngle(0, 0);
		if (!GetAngle(CurrentTarget, DesiredAngles))
			return;

		// Smoothing
		SmoothAngle(DesiredAngles);

		if (DesiredAngles == QAngle(0, 0))
			return;
		DesiredAngles.NormalizeAngles();

		if (Features::Flickbot::FlickbotMethod == 0) // Mouse
		{
			Vector2D FlickbotDelta = Vector2D(CalculatePitchIncrement(DesiredAngles), CalculateYawIncrement(DesiredAngles)).Multiply(25);
			/*int totalYawIncrementInt = RoundHalfEven(AL1AF0(FlickbotDelta.x));
			int totalPitchIncrementInt = RoundHalfEven(AL1AF0(FlickbotDelta.y * -1));*/
			if (FlickbotDelta.x == 0 && FlickbotDelta.y == 0) return;

			Vector2D CurrentAngles = Memory::Read<Vector2D>(Myself->BasePointer + OFF_VIEW_ANGLES);

			// Flick Angles
			if (InputManager::isKeyDownOrPress(Features::Flickbot::FlickBind)) {
				DHID->MoveMouse(FlickbotDelta.x, FlickbotDelta.y * -1);
				if (Features::Flickbot::AutoShoot) {
					std::this_thread::sleep_for(std::chrono::milliseconds(Features::Flickbot::AutoShootDelay));
					DHID->MouseClickLeft();
				}

				if (Features::Flickbot::FlickBack) {
					std::this_thread::sleep_for(std::chrono::milliseconds(Features::Flickbot::FlickBackDelay));
					Myself->SetViewAngle(CurrentAngles);
				}
			}
		}

		else if (Features::Flickbot::FlickbotMethod == 1) // Memory
		{
			Vector2D CurrentAngles = Memory::Read<Vector2D>(Myself->BasePointer + OFF_VIEW_ANGLES);

			// Flick Angles
			if (InputManager::isKeyDownOrPress(Features::Flickbot::FlickBind)) {
				//Change QAngle To Vector2D
				Vector2D VectorDesiredAngles = Vector2D(DesiredAngles.x, DesiredAngles.y);

				Myself->SetViewAngle(VectorDesiredAngles);
				if (Features::Flickbot::AutoShoot) {
					std::this_thread::sleep_for(std::chrono::milliseconds(Features::Flickbot::AutoShootDelay));
					DHID->MouseClickLeft();
				}

				if (Features::Flickbot::FlickBack) {
					std::this_thread::sleep_for(std::chrono::milliseconds(Features::Flickbot::FlickBackDelay));
					Myself->SetViewAngle(CurrentAngles);
				}
			}
		}
	}

	void SmoothAngle(QAngle& Angle) {
		QAngle ViewAngles = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
		QAngle Delta = Angle - ViewAngles;
		Delta.NormalizeAngles();

		if (Myself->IsZooming) {
			Features::Flickbot::Smooth = Features::Flickbot::ADSSmooth;
			float SmoothValue = powf(Features::Flickbot::Smooth, 0.4f);
			SmoothValue = (std::min)(0.99f, SmoothValue);
		} else if (!Myself->IsZooming) {
			Features::Flickbot::Smooth = Features::Flickbot::HipfireSmooth;
			float SmoothValue = powf(Features::Flickbot::Smooth, 0.4f);
			SmoothValue = (std::min)(0.99f, SmoothValue);
		}

		QAngle ToChange = QAngle();
		ToChange = Delta - Delta * Features::Flickbot::Smooth;

		Angle = ViewAngles + ToChange;
	}

	void SmoothBackAngle(QAngle& Angle) {
		QAngle ViewAngles = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
		QAngle Delta = Angle - ViewAngles;
		Delta.NormalizeAngles();

		Features::Flickbot::FlickBackSmooth = Features::Flickbot::FlickBackSmoothing;
		float SmoothValue = powf(Features::Flickbot::FlickBackSmooth, 0.4f);
		SmoothValue = (std::min)(0.99f, SmoothValue);

		QAngle ToChange = QAngle();
		ToChange = Delta - Delta * Features::Flickbot::FlickBackSmooth;

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
		Vector3D TargetPosition;
		if (!Features::Flickbot::ClosestHitbox) {
			TargetPosition = Target->GetBonePosition(Features::Flickbot::Hitbox);
		}
		if (Features::Flickbot::ClosestHitbox) {
			TargetPosition = Target->GetBonePosition(static_cast<HitboxType>(GetBestBone(Target)));
		}
		Vector3D TargetPos = Target->GetBonePosition(Features::Flickbot::Hitbox);
		Vector3D TargetVelocity = Target->AbsoluteVelocity;
		Vector3D CameraPosition = Myself->CameraPosition;

		if (Myself->WeaponProjectileSpeed > 1.0f) {
			if (Features::Flickbot::PredictBulletDrop && Features::Flickbot::PredictMovement) {
				return Resolver::CalculateAimRotationNew(CameraPosition, TargetPos, TargetVelocity, Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, Features::Flickbot::PreditcionAmount, Angle);
			} else if (Features::Flickbot::PredictBulletDrop) {
				return Resolver::CalculateAimRotationNew(CameraPosition, TargetPos, Vector3D(0, 0, 0), Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, Features::Flickbot::PreditcionAmount, Angle);
			} else if (Features::Flickbot::PredictMovement) {
				return Resolver::CalculateAimRotation(CameraPosition, TargetPos, TargetVelocity, Myself->WeaponProjectileSpeed, Angle);
			}
		}

		Angle = Resolver::CalculateAngle(CameraPosition, TargetPos);
		return true;
	}

	bool IsValidTarget(Player* target) {
		if (target == nullptr ||
			!target->IsValid() ||
			!target->IsCombatReady() ||
			!target->IsVisible ||
			!target->IsHostile ||
			target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Flickbot::MinDistance) ||
			target->Distance2DToLocalPlayer > Conversion::ToGameUnits(FinalDistance))
			return false;
		return true;
	}

	float CalculatePitchIncrement(QAngle FlickbotDesiredAngles) {
		float wayA = FlickbotDesiredAngles.x - Myself->ViewAngles.x;
		float wayB = 180 - abs(wayA);
		if (wayA > 0 && wayB > 0)
			wayB *= -1;
		if (fabs(wayA) < fabs(wayB))
			return wayA;
		return wayB;
	}

	float CalculateYawIncrement(QAngle FlickbotDesiredAngles) {
		float wayA = FlickbotDesiredAngles.y - Myself->ViewAngles.y;
		float wayB = 360 - abs(wayA);
		if (wayA > 0 && wayB > 0)
			wayB *= -1;
		if (fabs(wayA) < fabs(wayB))
			return wayA;
		return wayB;
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
		float BestFOV = (std::min)(Features::Flickbot::FOV, Features::Flickbot::FOV * (GetFOVScale() * Features::Flickbot::ZoomScale));
		float LastPov = 9999;
		Vector3D CameraPosition = Myself->CameraPosition;
		for (int i = 0; i < Players->size(); i++) {
			Player* p = Players->at(i);
			if (!IsValidTarget(p))
				continue;
			if (p->DistanceToLocalPlayer < Conversion::ToGameUnits(Features::Flickbot::ZoomDistance)) {
				HitboxType BestBone = static_cast<HitboxType>(GetBestBone(p));
				Vector3D TargetPosition = p->GetBonePosition(BestBone);

				float Distance = CameraPosition.Distance(TargetPosition);
				float FOV = CalculateDistanceFromCrosshair(TargetPosition);

				if (FOV > BestFOV)
					continue;

				if (FOV > LastPov)
					continue;

				NearestTarget = p;
				BestDistance = Distance;
				LastPov = FOV;
			}
		}
		return NearestTarget;
	}
};