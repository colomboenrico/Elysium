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
#include "SolarModule.h"
#include "SolarPanelSystem.h"
#include "WaterRecycler.h"
#include "OxygenGenerator.h"
#include "FarmSystem.h"
#include "EconomySystem.h"
#include "MoraleSystem.h"
#include "AdvisorSystem.h"
#pragma once
class SimulationEngine{
public:
    void init();
    void update();
    void shutdown();
    
    bool isRunning() const;
    
private:
    
    bool running = true;
    int tick = 0;
    
    SpaceStation* station;
    LifeSupportSystem* lifeSupport;
    PopulationSystem* population;
    EventSystem* events;
    SolarModule* solar;
    SolarPanelSystem* solarPanel;
    WaterRecycler* water;
    OxygenGenerator* oxygen;
    FarmSystem* farm;
    EconomySystem* economy;
    MoraleSystem* morale;
    AdvisorSystem* advisor;

    // scrive lo stato corrente in formato JSON (usato dall'interfaccia web)
    void writeState();
    // legge un eventuale comando "costruisci X" scritto dal sito web
    void processCommands();
    // registra un evento sia come "ultimo evento" sia nel log storico
    void logEvent(const std::string& msg);
    
};
