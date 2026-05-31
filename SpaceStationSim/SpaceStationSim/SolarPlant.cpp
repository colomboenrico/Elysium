//
//  SolarPlant.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 31/05/2026.
//

#include "SolarPlant.h"
#include "SpaceStation.h"
void SolarPlant::update(SpaceStation& station){
    station.energy+=5;
}
