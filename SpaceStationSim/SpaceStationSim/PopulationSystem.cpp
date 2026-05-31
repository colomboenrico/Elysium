//
//  PopulationSystem.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 30/05/2026.
//

#include "PopulationSystem.h"

void PopulationSystem::update(SpaceStation& station){
    if(station.oxygen <30){
        station.population-=1;
    }
    if(station.oxygen>70 && station.water>70){
        station.population+=1;
    }
    if(station.population<0)
        station.population =0;
}
