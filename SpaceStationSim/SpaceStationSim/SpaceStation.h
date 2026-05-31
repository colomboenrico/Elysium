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
    float oxygen  =100;
    float energy  =100;
    float water =100;
    float SolarEfficiency= 1.0f;
    int population=15;
    int solarPanels=10;
    //todo
    int waterRecyclers=1;
    int oxygenGenerator=1;
    std::vector<Module*>modules;
    

};
