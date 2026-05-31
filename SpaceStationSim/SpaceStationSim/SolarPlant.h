//
//  SolarPlant.h
//  SpaceStationSim
//
//  Created by Enrico Colombo on 31/05/2026.
//

#pragma once
#include "Module.h"

class SolarPlant : public Module{
public:
    void update(SpaceStation& station) override;
};
