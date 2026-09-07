//
//  MoraleSystem.cpp
//  SpaceStationSim
//
#include "MoraleSystem.h"
#include <algorithm>

void MoraleSystem::update(SpaceStation& station)
{
    float base = 0.5f;
    float bonus = station.parks * 0.05f
                + station.luxuryApartments * 0.08f
                + station.entertaimentCenters * 0.06f;
    station.morale = std::clamp(base + bonus, 0.0f, 1.5f);
}
