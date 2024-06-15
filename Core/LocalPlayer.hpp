#pragma once
#include "Offsets.hpp"
#include <string>
#include <unordered_map>
#include "../Utils/Memory.hpp"
#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/FloatVector2D.hpp"
#include "../Math/FloatVector3D.hpp"
#include "../Math/QAngle.hpp"
#include "../Utils/Features.hpp"

#define M_PI       3.14159265358979323846

struct LocalPlayer {
    long BasePointer;

    bool IsDead;
    bool IsInAttack;
    bool IsKnocked;
    bool IsZooming;
    bool InJump;

    int Team;
    int Squad;
    Vector3D LocalOrigin;
    Vector3D CameraPosition;

    Vector2D ViewAngles;
    Vector2D PunchAngles;
    Vector2D PunchAnglesPrevious;
    Vector2D PunchAnglesDifferent;

    int WeaponIndex;
    float WeaponProjectileSpeed;
    float WeaponProjectileScale;
    bool IsHoldingGrenade;
    long WeaponEntity;
    bool weaponDiscarded;

    float ZoomFOV;
    float TargetZoomFOV;

    float ViewYaw;

    FloatVector3D localOrigin;
    FloatVector3D cameraPosition;
    FloatVector2D viewAngles;
    FloatVector2D punchAngles;
    FloatVector2D punchAnglesPrev;
    FloatVector2D punchAnglesDiff;

    void Read() {
        BasePointer = Memory::Read<long>(OFF_REGION + OFF_LOCAL_PLAYER);
        if (BasePointer == 0)
            return;

        IsDead = Memory::Read<short>(BasePointer + OFF_LIFE_STATE) > 0;
        IsKnocked = Memory::Read<short>(BasePointer + OFF_BLEEDOUT_STATE) > 0;
        IsZooming = Memory::Read<short>(BasePointer + OFF_ZOOMING) > 0;
        IsInAttack = Memory::Read<short>(OFF_REGION + OFF_INATTACK) > 0;
        InJump = Memory::Read<bool>(OFF_REGION + OFF_IN_JUMP) > 0;

        Team = Memory::Read<int>(BasePointer + OFF_TEAM_NUMBER);
        Squad = Memory::Read<int>(BasePointer + OFF_SQUAD_ID);

        localOrigin = Memory::Read<FloatVector3D>(BasePointer + OFF_LOCAL_ORIGIN);
        LocalOrigin = Memory::Read<Vector3D>(BasePointer + OFF_LOCAL_ORIGIN);

        CameraPosition = Memory::Read<Vector3D>(BasePointer + OFF_CAMERAORIGIN);
        ViewAngles = Memory::Read<Vector2D>(BasePointer + OFF_VIEW_ANGLES);
        PunchAngles = Memory::Read<Vector2D>(BasePointer + OFF_PUNCH_ANGLES);
        PunchAnglesDifferent = PunchAnglesPrevious.Subtract(PunchAngles);
        PunchAnglesPrevious = PunchAngles;
        ViewYaw = Memory::Read<float>(BasePointer + OFF_YAW);

        // FloatVector2D Versions, For Standalone RCS and Linear Aimbot
        cameraPosition = Memory::Read<FloatVector3D>(BasePointer + OFF_CAMERAORIGIN);
        viewAngles = Memory::Read<FloatVector2D>(BasePointer + OFF_VIEW_ANGLES);
        punchAngles = Memory::Read<FloatVector2D>(BasePointer + OFF_PUNCH_ANGLES);
        punchAnglesDiff = punchAnglesPrev.subtract(punchAngles);
        punchAnglesPrev = punchAngles;

        if (!IsDead && !IsKnocked) {
            long WeaponHandle = Memory::Read<long>(BasePointer + OFF_WEAPON_HANDLE);
            long WeaponHandleMasked = WeaponHandle & 0xffff;
            WeaponEntity = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (WeaponHandleMasked << 5));

            int OffHandWeaponID = Memory::Read<int>(BasePointer + OFF_OFFHAND_WEAPON);
            IsHoldingGrenade = OffHandWeaponID == -251 ? true : false;

            ZoomFOV = Memory::Read<float>(WeaponEntity + OFF_CURRENTZOOMFOV);
            TargetZoomFOV = Memory::Read<float>(WeaponEntity + OFF_TARGETZOOMFOV);

            WeaponIndex = Memory::Read<int>(WeaponEntity + OFF_WEAPON_INDEX);
            weaponDiscarded = Memory::Read<int>(WeaponEntity + OFF_WEAPON_DISCARDED) == 1;
            WeaponProjectileSpeed = Memory::Read<float>(WeaponEntity + OFF_PROJECTILESPEED);
            WeaponProjectileScale = Memory::Read<float>(WeaponEntity + OFF_PROJECTILESCALE);
        }
    }

    std::string GetPlayerModelName() {
        uintptr_t ModelOffset = Memory::Read<uintptr_t>(BasePointer + OFF_MODELNAME);
        std::string ModelName = Memory::ReadStringSize(ModelOffset, 1024);

        static std::unordered_map<std::string, std::string> ModelNameMap = { {"dummie", "Dummie"}, {"ash", "Ash"}, {"ballistic", "Ballistic"}, {"bangalore", "Bangalore"}, {"bloodhound", "Bloodhound"}, {"catalyst", "Catalyst"}, {"caustic", "Caustic"}, {"conduit", "Conduit"}, {"crypto", "Crypto"}, {"fuse", "Fuse"}, {"gibraltar", "Gibraltar"}, {"horizon", "Horizon"}, {"nova", "Horizon"}, {"holo", "Mirage"}, {"mirage", "Mirage"}, {"lifeline", "Lifeline"}, {"loba", "Loba"}, {"madmaggie", "Mad Maggie"}, {"newcastle", "Newcastle"}, {"octane", "Octane"}, {"pathfinder", "Pathfinder"}, {"rampart", "Rampart"}, {"revenant", "Revenant"}, {"seer", "Seer"}, {"stim", "Octane"}, {"valkyrie", "Valkyrie"}, {"vantage", "Vantage"}, {"wattson", "Wattson"}, {"wraith", "Wraith"}, {"alter", "Alter"}, };

        std::string replacedName = ModelName;
        for (auto& entry : ModelNameMap) {
            if (ModelName.find(entry.first) != std::string::npos) {
                replacedName = entry.second;
                break;
            }
        }

        return replacedName;
    }

    bool IsValid() {
        return BasePointer != 0;
    }

    bool IsCombatReady() {
        if (BasePointer == 0)
            return false;
        if (IsDead)
            return false;
        if (IsKnocked)
            return false;
        return true;
    }

    void setYaw(float angle) {
        long ptrLong = BasePointer + OFF_VIEW_ANGLES + sizeof(float);
        Memory::Write<float>(ptrLong, angle);
    }

    void SetQAngle(QAngle ViewAngle) {
        Memory::Write<QAngle>(BasePointer + OFF_VIEW_ANGLES, NormalizeQAngle(ViewAngle));
    }

    inline QAngle NormalizeQAngle(QAngle angle) {
        while (angle.x > 89.0f)
            angle.x -= 180.f;

        while (angle.x < -89.0f)
            angle.x += 180.f;

        while (angle.y > 180.f)
            angle.y -= 360.f;

        while (angle.y < -180.f) {
            angle.y += 360.f;
        }

        return angle;
    }

    void SetViewAngle(Vector2D ViewAngle) {
        Memory::Write<Vector2D>(BasePointer + OFF_VIEW_ANGLES, NormalizeVectorAngles(ViewAngle));
    }

    inline Vector2D NormalizeVectorAngles(Vector2D angle) {
        while (angle.x > 89.0f)
            angle.x -= 180.f;

        while (angle.x < -89.0f)
            angle.x += 180.f;

        while (angle.y > 180.f)
            angle.y -= 360.f;

        while (angle.y < -180.f) {
            angle.y += 360.f;
        }

        return angle;
    }
};
