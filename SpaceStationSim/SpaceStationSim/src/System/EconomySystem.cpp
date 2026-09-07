//
//  EconomySystem.cpp
//  SpaceStationSim
//
#include "EconomySystem.h"

void EconomySystem::update(SpaceStation& station)
{
    // entrate passive dalla popolazione (tasse/commercio con la Terra)
    station.credits += station.population * 0.05f;
    if (station.credits < 0) station.credits = 0;
}
