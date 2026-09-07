//
//  WaterRecycle.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 01/06/2026.
//
#include "WaterRecycler.h"
#include <algorithm>
#include <iostream>

void WaterRecycler::update(SpaceStation& station)
{
    float recovered = station.population * 0.8f + station.waterRecyclers * 1.5f;
    station.water += recovered;
    station.water -= station.population * 0.3f;

    station.water = std::clamp(station.water, 0.0f, 100.0f);

    if (station.water <= 0.0f) {
        std::cout << "Warning: water depleted\n";
    }
}
