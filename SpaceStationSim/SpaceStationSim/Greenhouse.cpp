//
//  Greenhouse.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 31/05/2026.
//

#include "Greenhouse.h"
#include "SpaceStation.h"
void Greenhouse::update(SpaceStation& station){
    station.oxygen +=3;
    station.water +=1;
}
