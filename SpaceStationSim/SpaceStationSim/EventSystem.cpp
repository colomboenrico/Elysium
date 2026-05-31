//
//  EventSystem.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 31/05/2026.
//

#include "EventSystem.h"
#include <iostream>
#include <cstdlib>
 
void EventSystem::update(SpaceStation &station)
{
    int event = rand()%100;
    //2% probabilità
    if(event<2)
    {
        std::cout <<"METEOR IMPACT !"<<std::endl;
        station.oxygen-=15;
        station.water-=10;
        station.energy-=20;
    }
    //3% probabilità
    else if(event <5){
        std::cout<<"LIFE SUPPORT FAILURE!"<<std::endl;
        station.oxygen-=10;
    }
    //3% probabilità
    else if(event<8){
        std::cout<<"WATER LEAK!"<<std::endl;
        station.water-=15;
    }
    //3%probabilità
    else if(event<11){
        std::cout<<"SOLAR STORM!"<<std::endl;
        station.energy-=25;
    }
    //2% probabilità
    else if(event <13){
        std::cout <<"NEW COLONISTS ARRIVED!"<<std::endl;
        station.population+=5;
    }
}
