//
//  SpaceStation.c++
//  SpaceStationSim
//
//  Created by Enrico Colombo on 30/05/2026.
//
#pragma once
#include<vector>
class Module;
class SpaceStation{
    public :
    float oxygen  ;
    float energy  ;
    float water ;
    
    int population;
    std::vector<Module*>modules;
};
