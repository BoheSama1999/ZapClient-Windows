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

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Conversion
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))

struct Ragebot
{

	int FinalDistance = 0;
	Vector3D TargetBoneW2S;

	//XDisplay* X11Display; linux
	DriverHID* DHID;
	LocalPlayer* Myself;
	std::vector<Player*>* Players;
	Level* Map;

	Player* CurrentTarget = nullptr;
	bool TargetSelected = true;
	std::chrono::milliseconds LastAimTime;
	std::chrono::milliseconds LastClickTime;
	std::chrono::milliseconds LastFlickBackTime;
	Vector2D previous_weaponPunchAngles;
	Vector2D RCSLastPunch;

	Ragebot(DriverHID* DHID, Level* Map, LocalPlayer* Myself, std::vector<Player*>* GamePlayers) {
		this->DHID = DHID;
		this->Myself = Myself;
		this->Map = Map;
		this->Players = GamePlayers;
	}

	static bool Save() {
		try {

			Config::Ragebot::RagebotEnabled = Features::Ragebot::RagebotEnabled;
			Config::Ragebot::RageAimbot = Features::Ragebot::RageAimbot;
			Config::Ragebot::AimMethod = Features::Ragebot::AimMethod;
			Config::Ragebot::ClosestHitbox = Features::Ragebot::ClosestHitbox;
			Config::Ragebot::Hitbox = static_cast<int>(Features::Ragebot::Hitbox);
			Config::Ragebot::BindMethod = Features::Ragebot::BindMethod;
			Config::Ragebot::OnFire = Features::Ragebot::OnFire;
			Config::Ragebot::OnADS = Features::Ragebot::OnADS;
			Config::Ragebot::AimBind = static_cast<int>(Features::Ragebot::AimBind);
			Config::Ragebot::ExtraBind = static_cast<int>(Features::Ragebot::ExtraBind);
			Config::Ragebot::VisCheck = Features::Ragebot::VisCheck;
			Config::Ragebot::TeamCheck = Features::Ragebot::TeamCheck;
			Config::Ragebot::Priority = Features::Ragebot::Priority;
			Config::Ragebot::AutoShoot = Features::Ragebot::AutoShoot;
			Config::Ragebot::PredictMovement = Features::Ragebot::PredictMovement;
			Config::Ragebot::PredictBulletDrop = Features::Ragebot::PredictBulletDrop;
			Config::Ragebot::PreditcionAmount = Features::Ragebot::PreditcionAmount;
			Config::Ragebot::FinalDistance = Features::Ragebot::FinalDistance;
			Config::Ragebot::Speed = Features::Ragebot::Speed;
			Config::Ragebot::Smooth = Features::Ragebot::Smooth;
			Config::Ragebot::Speed = Features::Ragebot::Speed;
			Config::Ragebot::HipfireSmooth = Features::Ragebot::HipfireSmooth;
			Config::Ragebot::ADSSmooth = Features::Ragebot::ADSSmooth;
			Config::Ragebot::SmoothDistance = Features::Ragebot::SmoothDistance;
			Config::Ragebot::Delay = Features::Ragebot::Delay;
			Config::Ragebot::FOV = Features::Ragebot::FOV;
			Config::Ragebot::ZoomScale = Features::Ragebot::ZoomScale;
			Config::Ragebot::MinDistance = Features::Ragebot::MinDistance;
			Config::Ragebot::HipfireDistance = Features::Ragebot::HipfireDistance;
			Config::Ragebot::ZoomDistance = Features::Ragebot::ZoomDistance;
			Config::Ragebot::RageRCS = Features::Ragebot::RageRCS;
			Config::Ragebot::RecoilRate = Features::Ragebot::RecoilRate;
			//Weapon Toggles
			//Light
			Config::Ragebot::P2020 = Features::Ragebot::P2020;
			Config::Ragebot::RE45 = Features::Ragebot::RE45;
			Config::Ragebot::Alternator = Features::Ragebot::Alternator;
			Config::Ragebot::R99 = Features::Ragebot::R99;
			Config::Ragebot::R301 = Features::Ragebot::R301;
			Config::Ragebot::Spitfire = Features::Ragebot::Spitfire;
			Config::Ragebot::G7 = Features::Ragebot::G7;
			//Heavy
			Config::Ragebot::Flatline = Features::Ragebot::Flatline;
			Config::Ragebot::Hemlock = Features::Ragebot::Hemlock;
			Config::Ragebot::Repeater = Features::Ragebot::Repeater;
			Config::Ragebot::Rampage = Features::Ragebot::Rampage;
			Config::Ragebot::CARSMG = Features::Ragebot::CARSMG;
			//Energy
			Config::Ragebot::Havoc = Features::Ragebot::Havoc;
			Config::Ragebot::Devotion = Features::Ragebot::Devotion;
			Config::Ragebot::LSTAR = Features::Ragebot::LSTAR;
			Config::Ragebot::TripleTake = Features::Ragebot::TripleTake;
			Config::Ragebot::Volt = Features::Ragebot::Volt;
			Config::Ragebot::Nemesis = Features::Ragebot::Nemesis;
			//Shotgun
			Config::Ragebot::Mozambique = Features::Ragebot::Mozambique;
			Config::Ragebot::EVA8 = Features::Ragebot::EVA8;
			Config::Ragebot::Peacekeeper = Features::Ragebot::Peacekeeper;
			Config::Ragebot::Mastiff = Features::Ragebot::Mastiff;
			//Snipers
			Config::Ragebot::Longbow = Features::Ragebot::Longbow;
			Config::Ragebot::ChargeRifle = Features::Ragebot::ChargeRifle;
			Config::Ragebot::Sentinel = Features::Ragebot::Sentinel;
			//Legendary
			Config::Ragebot::Wingman = Features::Ragebot::Wingman;
			Config::Ragebot::Prowler = Features::Ragebot::Prowler;
			Config::Ragebot::Bocek = Features::Ragebot::Bocek;
			Config::Ragebot::Kraber = Features::Ragebot::Kraber;
			Config::Ragebot::Knife = Features::Ragebot::Knife;

			return true;
		} catch (...) {
			return false;
		}
	}

	void UpdateRageList() {
		Features::Ragebot::RageList.clear();
		// Define a lambda function to reduce repetition
		auto InsertIfEnabled = [&](const bool feature, const int weaponID) {
		if (feature)
			Features::Ragebot::RageList.insert(weaponID);
		};
		// Light
		InsertIfEnabled(Features::Ragebot::P2020, WeaponIDs::P2020);
		InsertIfEnabled(Features::Ragebot::RE45, WeaponIDs::RE45);
		InsertIfEnabled(Features::Ragebot::Alternator, WeaponIDs::ALTERNATOR);
		InsertIfEnabled(Features::Ragebot::R99, WeaponIDs::R99);
		InsertIfEnabled(Features::Ragebot::R301, WeaponIDs::R301);
		InsertIfEnabled(Features::Ragebot::Spitfire, WeaponIDs::SPITFIRE);
		InsertIfEnabled(Features::Ragebot::G7, WeaponIDs::G7);

		// Heavy
		InsertIfEnabled(Features::Ragebot::Flatline, WeaponIDs::FLATLINE);
		InsertIfEnabled(Features::Ragebot::Prowler, WeaponIDs::PROWLER);
		InsertIfEnabled(Features::Ragebot::Hemlock, WeaponIDs::HEMLOCK);
		InsertIfEnabled(Features::Ragebot::Repeater, WeaponIDs::REPEATER);
		InsertIfEnabled(Features::Ragebot::Rampage, WeaponIDs::RAMPAGE);
		InsertIfEnabled(Features::Ragebot::CARSMG, WeaponIDs::CAR);

		// Energy
		InsertIfEnabled(Features::Ragebot::Havoc, WeaponIDs::HAVOC);
		InsertIfEnabled(Features::Ragebot::Devotion, WeaponIDs::DEVOTION);
		InsertIfEnabled(Features::Ragebot::LSTAR, WeaponIDs::LSTAR);
		InsertIfEnabled(Features::Ragebot::TripleTake, WeaponIDs::TRIPLETAKE);
		InsertIfEnabled(Features::Ragebot::Volt, WeaponIDs::VOLT);
		InsertIfEnabled(Features::Ragebot::Nemesis, WeaponIDs::NEMESIS);

		// Shotguns
		InsertIfEnabled(Features::Ragebot::Mozambique, WeaponIDs::MOZAMBIQUE);
		InsertIfEnabled(Features::Ragebot::Peacekeeper, WeaponIDs::PEACEKEEPER);
		InsertIfEnabled(Features::Ragebot::Mastiff, WeaponIDs::MASTIFF);

		// Snipers
		InsertIfEnabled(Features::Ragebot::Longbow, WeaponIDs::LONGBOW);
		InsertIfEnabled(Features::Ragebot::ChargeRifle, WeaponIDs::CHARGE_RIFLE);
		InsertIfEnabled(Features::Ragebot::Sentinel, WeaponIDs::SENTINEL);

		// Legendary
		InsertIfEnabled(Features::Ragebot::Wingman, WeaponIDs::WINGMAN);
		InsertIfEnabled(Features::Ragebot::EVA8, WeaponIDs::EVA8);
		InsertIfEnabled(Features::Ragebot::Bocek, WeaponIDs::BOCEK);
		InsertIfEnabled(Features::Ragebot::Kraber, WeaponIDs::KRABER);
		InsertIfEnabled(Features::Ragebot::Knife, WeaponIDs::KNIFE);
	}

	void Update() {

		if (!Map->IsPlayable) {
			ReleaseTarget();
			return;
		}

		if (!Features::Ragebot::RageAimbot) {
			ReleaseTarget();
			return;
		}

		if (Features::Ragebot::RageAimbot) {

			if (Myself->IsZooming)
				FinalDistance = Features::Ragebot::ZoomDistance;
			else
				FinalDistance = Features::Ragebot::HipfireDistance;

			if (!Myself->IsCombatReady()) {
				CurrentTarget = nullptr;
				return;
			}

			if (Features::Ragebot::RageList.find(Myself->WeaponIndex) == Features::Ragebot::RageList.end()) {
				ReleaseTarget();
				return;
			}

			if (Myself->IsHoldingGrenade) {
				ReleaseTarget();
				return;
			}


			if (Features::Ragebot::BindMethod == 0) {
				if (Features::Ragebot::OnFire && Features::Ragebot::OnADS) {
					if (!Myself->IsInAttack) {
						if (!Myself->IsZooming) {
							ReleaseTarget();
							TargetSelected = false;
							CurrentTarget = nullptr;
							return;
						}
					}
					if (!Myself->IsZooming) {
						if (!Myself->IsInAttack) {
							ReleaseTarget();
							TargetSelected = false;
							CurrentTarget = nullptr;
							return;
						}
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
						CurrentTarget->IsLockedOn = true;
						TargetSelected = true;
					}

					if (TargetSelected && CurrentTarget) {
						std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
						if (Now >= LastAimTime + std::chrono::milliseconds(Features::Ragebot::Delay)) {
							StartAiming();
							LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
						}
						return;
					}
				}

				if (Features::Ragebot::OnFire) {
					if (!Myself->IsInAttack) {
						ReleaseTarget();
						TargetSelected = false;
						CurrentTarget = nullptr;
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
						CurrentTarget->IsLockedOn = true;
						TargetSelected = true;
					}

					if (TargetSelected && CurrentTarget) {
						std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
						if (Now >= LastAimTime + std::chrono::milliseconds(Features::Ragebot::Delay)) {
							StartAiming();
							LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
						}
						return;
					}
				}

				if (Features::Ragebot::OnADS) {
					if (!Myself->IsZooming) {
						ReleaseTarget();
						TargetSelected = false;
						CurrentTarget = nullptr;
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
						CurrentTarget->IsLockedOn = true;
						TargetSelected = true;
					}

					if (TargetSelected && CurrentTarget) {
						std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
						if (Now >= LastAimTime + std::chrono::milliseconds(Features::Ragebot::Delay)) {
							StartAiming();
							LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
						}
						return;
					}
				}
			}

			if (Features::Ragebot::BindMethod == 1) {
				if (!isKeybindDown()) {
					ReleaseTarget();
					TargetSelected = false;
					CurrentTarget = nullptr;
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
					CurrentTarget->IsLockedOn = true;
					TargetSelected = true;
				}

				if (TargetSelected && CurrentTarget) {
					std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
					if (Now >= LastAimTime + std::chrono::milliseconds(Features::Ragebot::Delay)) {
						StartAiming();
						LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
					}
					return;
				}
			}

			if (Features::Ragebot::BindMethod == 2) {
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
					CurrentTarget->IsLockedOn = true;
					TargetSelected = true;
				}

				if (TargetSelected && CurrentTarget) {
					std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
					if (Now >= LastAimTime + std::chrono::milliseconds(Features::Ragebot::Delay)) {
						StartAiming();
						LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
					}
					return;
				}
			}
		}
	}

	bool isKeybindDown() {
		bool ActivatedByAimBind = InputManager::isKeyDownOrPress(Features::Ragebot::AimBind);
		bool ActivatedByExtraBind = InputManager::isKeyDownOrPress(Features::Ragebot::ExtraBind);
		bool active = (ActivatedByAimBind || ActivatedByExtraBind);
		return active;
	}

	void StartAiming() {
		// Get Target Angle
		QAngle DesiredAngles = QAngle(0, 0);
		if (!GetAngle(CurrentTarget, DesiredAngles)) // Get Angle to target + prediction
			return;

		SmoothAngle(DesiredAngles); // Apply Smoothing

		// Recoil Control
		if (Features::Ragebot::RageRCS) {
			Vector2D PunchAngles = Memory::Read<Vector2D>(Myself->BasePointer + OFF_PUNCH_ANGLES); // Get punch angles
			PunchAngles.x *= (Features::Ragebot::RecoilRate / 100.f);
			PunchAngles.y *= (Features::Ragebot::RecoilRate / 100.f);

			DesiredAngles -= QAngle(PunchAngles.x, PunchAngles.y);
		}

		if (DesiredAngles == QAngle(0, 0))
			return;
		DesiredAngles.NormalizeAngles();

		// Memory Aimbot
		if (Features::Ragebot::AimMethod == 0) { // Memory
			Vector2D VectorDesiredAngles = Vector2D(DesiredAngles.x, DesiredAngles.y);
			if (!Features::Ragebot::AutoShoot) {
				Myself->SetViewAngle(VectorDesiredAngles);
			}
			if (Features::Ragebot::AutoShoot) {
				Myself->SetViewAngle(VectorDesiredAngles);
				DHID->MouseClickLeft();
			}
		}

		// Mouse Aimbot
		if (Features::Ragebot::AimMethod == 1) {																															// Mouse
			Vector2D aimbotD = Vector2D(CalculatePitchIncrement(DesiredAngles), CalculateYawIncrement(DesiredAngles)).Multiply(30); // 30 = Speed

			int totalYawIncrementInt = RoundHalfEven(AL1AF0(aimbotD.x));
			int totalPitchIncrementInt = RoundHalfEven(AL1AF0(aimbotD.y * -1));

			/*if (totalPitchIncrementInt == 0 && totalYawIncrementInt == 0)
				return;*/
			if (!Features::Ragebot::AutoShoot) {
				DHID->MoveMouse(totalYawIncrementInt, totalPitchIncrementInt);
			}
			if (Features::Ragebot::AutoShoot) {
				DHID->MoveMouse(totalYawIncrementInt, totalPitchIncrementInt);
				DHID->MouseClickLeft();
			}
		}
	}

	void SmoothAngle(QAngle& Angle) {
		QAngle ViewAngles = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
		QAngle Delta = Angle - ViewAngles;
		Delta.NormalizeAngles();

		if (Myself->IsZooming) {
			Features::Ragebot::Smooth = Features::Ragebot::ADSSmooth;
			float SmoothValue = powf(Features::Ragebot::Smooth, 0.4f);
			SmoothValue = (std::min)(0.99f, SmoothValue);
		} else if (!Myself->IsZooming) {
			Features::Ragebot::Smooth = Features::Ragebot::HipfireSmooth;
			float SmoothValue = powf(Features::Ragebot::Smooth, 0.4f);
			SmoothValue = (std::min)(0.99f, SmoothValue);
		}

		QAngle ToChange = QAngle();
		ToChange = Delta - Delta * Features::Ragebot::Smooth;

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
		if (!Features::Ragebot::ClosestHitbox) {
			TargetPosition = Target->GetBonePosition(Features::Ragebot::Hitbox);
		}
		if (Features::Ragebot::ClosestHitbox) {
			TargetPosition = Target->GetBonePosition(static_cast<HitboxType>(GetBestBone(Target)));
		}

		Vector3D TargetPos = Target->GetBonePosition(Features::Ragebot::Hitbox);
		Vector3D TargetVelocity = Target->AbsoluteVelocity;
		Vector3D CameraPosition = Myself->CameraPosition;

		if (Features::Ragebot::PredictBulletDrop && Features::Ragebot::PredictMovement) {
			return Resolver::CalculateAimRotationNew(CameraPosition, TargetPos, TargetVelocity, Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, Features::Ragebot::PreditcionAmount, Angle);
		} else if (Features::Ragebot::PredictMovement) {
			return Resolver::CalculateAimRotationNew(CameraPosition, TargetPos, Vector3D(0, 0, 0), Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, Features::Ragebot::PreditcionAmount, Angle);
		} else if (Features::Ragebot::PredictBulletDrop) {
			return Resolver::CalculateAimRotation(CameraPosition, TargetPos, TargetVelocity, Myself->WeaponProjectileSpeed, Angle);
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
			target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Ragebot::MinDistance) ||
			target->Distance2DToLocalPlayer > Conversion::ToGameUnits(FinalDistance))
			return false;
		return true;
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
		float BestFOV = (std::min)(Features::Ragebot::FOV, Features::Ragebot::FOV * (GetFOVScale() * Features::Ragebot::ZoomScale));
		float LastPov = 9999;
		Vector3D CameraPosition = Myself->CameraPosition;
		for (int i = 0; i < Players->size(); i++) {
			Player* p = Players->at(i);
			if (!IsValidTarget(p))
				continue;
			if (p->DistanceToLocalPlayer < Conversion::ToGameUnits(Features::Ragebot::ZoomDistance)) {
				HitboxType BestBone = static_cast<HitboxType>(GetBestBone(p));
				Vector3D TargetPosition = p->GetBonePosition(BestBone);

				float Distance = CameraPosition.Distance(TargetPosition);
				float FOV = CalculateDistanceFromCrosshair(TargetPosition);

				if (FOV > BestFOV)
					continue;

				if (Features::Ragebot::Priority == 0 && FOV > LastPov)
					continue;

				if (Features::Ragebot::Priority == 1 && Distance > BestDistance)
					continue;

				NearestTarget = p;
				BestDistance = Distance;
				LastPov = FOV;
			}
		}
		return NearestTarget;
	}
};