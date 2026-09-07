//
//  PopulationSystem.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 30/05/2026.
//

#include "PopulationSystem.h"

void PopulationSystem::update(SpaceStation& station){
    float delta=0;
    //crescita base
    delta +=0.1f;
    //crescita base
    
    //stress ambientale
    if(station.oxygen<20)
        delta-=0.5f;
    if(station.water<20)
       delta-=0.5f;
    if(station.energy<10)
        delta-=0.3f;
    if(station.food<20)
        delta-=0.4f;
    
    //morte critica
    if(station.oxygen<=0)
        delta-=3.0f;
    if(station.water<=0)
        delta+=0.2f;
    if(station.food<=0)
        delta-=1.5f;
  
    //condizioni buone
    if(station.oxygen>70 || station.water>70){
        station.population+=0.2f;
    }

    //il morale amplifica o riduce la crescita (0 = colonia infelice, 1.5 = colonia felice)
    delta *= (0.6f + 0.4f * station.morale);
    
    //applicazione
    station.population+=delta;
    
    //clamp
    if(station.population<0)
        station.population=0;
}
