//
//  SimulationEngine.c++
//  SpaceStationSim
//
//  Created by Enrico Colombo on 30/05/2026.
//
#include "SpaceStation.h"
#include "LifeSupportSystem.h"
#include "PopulationSystem.h"
#include "EventSystem.h"
#pragma once
class SimulationEngine{
public:
    void init();
    void update();
    void shutdown();
    
    bool isRunning() const;
    
private:
    
    bool running = true;
    
    SpaceStation* station;
    LifeSupportSystem* lifeSupport;
    PopulationSystem* population;
    EventSystem *events;
    
};
