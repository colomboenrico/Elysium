//
//  SimulationEngine.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 30/05/2026.
//

#include "SimulationEngine.h"
#include "SpaceStation.h"
#include "LifeSupportSystem.h"
#include"PopulationSystem.h"
#include <iostream>

void SimulationEngine::init(){
    station =  new SpaceStation();
    lifeSupport = new LifeSupportSystem();
    population = new PopulationSystem();
    
    station->oxygen = 100;
    station->water = 100;
    station->energy = 100;
    station->population = 10;
    running = true;
}
void SimulationEngine::update(){
    lifeSupport->update(*station);
    population->update(*station);
   
    std::cout
    <<"POP: "<<station->population
    <<"O2: "<<station->oxygen
    <<"WATER: "<<station->water
    <<"ENERGY: "<<station->energy
    <<std::endl;
    
    if(station->population<=0){
        std::cout<<"STATION FAILED"<<std::endl;
        running=false;
    }
}
void SimulationEngine::shutdown(){
    delete station;
    delete lifeSupport;
    delete population;
}
bool SimulationEngine::isRunning()const{
    return running;
}
