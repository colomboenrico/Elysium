//
//  AdvisorSystem.h
//  SpaceStationSim
//
//  Motore a regole (sistema esperto) che analizza lo stato della stazione
//  e genera un consiglio, sullo stesso principio dei sistemi di IA simbolica
//  (regole if-then a priorita', come in Prolog/CLIPS).
//
#pragma once
#include "SpaceStation.h"
class AdvisorSystem{
public:
    void update(SpaceStation& station);
};
