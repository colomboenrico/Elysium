//
//  OxygenGenerator.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 31/05/2026.
//
#include "OxygenGenerator.h"
#include <algorithm>

void OxygenGenerator::update(SpaceStation& station)
{
    station.oxygen += 4.0f + station.oxygenGenerator * 1.5f;
    station.energy -= 0.3f;

    station.oxygen = std::clamp(station.oxygen, 0.0f, 100.0f);
}
