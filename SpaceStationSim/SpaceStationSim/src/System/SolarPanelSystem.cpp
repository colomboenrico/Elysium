//
//  SolarPanelSystem.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 01/06/2026.
//
#include "SolarPanelSystem.h"
#include <algorithm>

void SolarPanelSystem::update(SpaceStation& station)
{
    station.solarProduction = station.solarPanels * 2.0f;
    station.energy += station.solarProduction;

    station.energy = std::clamp(station.energy, 0.0f, 100.0f);
}
