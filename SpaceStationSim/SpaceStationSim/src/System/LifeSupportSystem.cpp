//
//  LifeSupportSystem.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 30/05/2026.
//

#include "LifeSupportSystem.h"
#include "SpaceStation.h"
void LifeSupportSystem::update(SpaceStation& station){
    station.oxygen -= station.population *0.2f;
    station.water -= station.population *0.15f;
    station.energy -= station.population *0.1f;
    
    if(station.oxygen<0) station.oxygen=0;
    if(station.water<0)station.water=0;
    if(station.energy<0)station.energy=0;
}
