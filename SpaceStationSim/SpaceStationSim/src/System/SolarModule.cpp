//
//  SolarModule.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 31/05/2026.
//

#include "SolarModule.h"
void SolarModule::update(SpaceStation& station){
    float prodution = 5.0f*station.SolarEfficiency;

    //produzione energia dei pannelli
    station.energy+=prodution;
    if(station.energy>100)
        station.energy =100;
    if(station.SolarEfficiency<1.0f)
    {
        station.SolarEfficiency+=0.01f;
    }
}
