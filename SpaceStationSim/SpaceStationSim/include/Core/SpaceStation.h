//
//  SpaceStation.c++
//  SpaceStationSim
//
//  Created by Enrico Colombo on 30/05/2026.
//
#pragma once
#include <vector>
#include <string>
class Module;
class SpaceStation{
    public :
    //risorse
    float oxygen  ;
    float energy  ;
    float water ;
    float food;
  
    
    float SolarEfficiency;
    float solarProduction;
    //popolazione
    int population;
    float morale = 1.0f;
    //economia
    float credits;
    //moduli
    int solarPanels;
    //todo
    int waterRecyclers;
    int oxygenGenerator;
    int farms;
    
    //lusso
    int luxuryApartments;
    int parks;
    int entertaimentCenters;
    
    std::vector<Module*>modules;

    //ultimo evento generato da EventSystem, usato dall'interfaccia web
    std::string lastEvent = "";

    //consiglio del sistema esperto di bordo (AdvisorSystem), mostrato nella dashboard
    std::string advisorMessage = "Inizializzazione sistemi...";

};
