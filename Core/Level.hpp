#pragma once
#include "Offsets.hpp"
#include <unordered_map>
#include <string>
#include "../Utils/Memory.hpp"

namespace LvMap
{
    bool m_mixtape;
}

struct Level
{
    std::string Name;
    bool IsPlayable;
    bool IsFiringRange;
    bool m_mixtape;
    char gameMode[64] = { 0 };
    std::unordered_map<std::string, bool> mixtape = { {"control", true}, {"freedm", true}, {"arenas", true} };

    void Read() {
        uint64_t gameModePtr = Memory::Read<uint64_t>(OFF_REGION + OFF_GAMEMODE + 0x50);
        Name = Memory::ReadString(OFF_REGION + OFF_LEVEL);
        IsPlayable = !Name.empty() && Name != "mp_lobby";
        IsFiringRange = Name == "mp_rr_canyonlands_staging_mu1";
        if (gameModePtr) {
            Memory::Read(gameModePtr, &gameMode, sizeof(gameMode));
            //m_mixtape = (gameMode == "control" || gameMode == "freedm" || gameMode == "arenas");
            m_mixtape = mixtape[gameMode];
            LvMap::m_mixtape = m_mixtape;
            //std::cout << gameMode << (mixtape[gameMode]) << std::endl;
        }
    }
};
