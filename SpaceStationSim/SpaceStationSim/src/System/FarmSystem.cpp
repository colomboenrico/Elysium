//
//  FarmSystem.cpp
//  SpaceStationSim
//
#include "FarmSystem.h"
#include <algorithm>

void FarmSystem::update(SpaceStation& station)
{
    float produced = station.farms * 2.0f;
    float consumed = station.population * 0.12f;
    station.food += produced - consumed;
    station.food = std::clamp(station.food, 0.0f, 100.0f);
}
