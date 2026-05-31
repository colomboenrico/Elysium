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
#include "SolarPlant.h"
#include "Greenhouse.h"

void SimulationEngine::init(){
    station =  new SpaceStation();
    lifeSupport = new LifeSupportSystem();
    population = new PopulationSystem();
    
    station->oxygen = 100;
    station->water = 100;
    station->energy = 100;
    station->population = 10;
    running = true;
    
    station->modules.push_back(new SolarPlant);
    station->modules.push_back(new Greenhouse);
    
    events= new EventSystem();
}
void SimulationEngine::update(){
    lifeSupport->update(*station);
    population->update(*station);
    events->update(*station);
    
    station->oxygen= std::clamp(station->oxygen,0.0f,100.0f);
    station->water=std::clamp(station->water,0.0f,100.0f);
    station->energy=std::clamp(station->energy,0.0f,100.0f);
    
   
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
    for(Module* module :station -> modules){
        module ->update(*station);
    }
}
void SimulationEngine::shutdown(){
    delete station;
    delete lifeSupport;
    delete population;
    delete events;
    for(Module* module :station->modules){
        delete module;
    }
    station->modules.clear();
}
bool SimulationEngine::isRunning()const{
    return running;
}
