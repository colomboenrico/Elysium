//
//  AdvisorSystem.cpp
//  SpaceStationSim
//
#include "AdvisorSystem.h"

void AdvisorSystem::update(SpaceStation& station)
{
    // regole in ordine di priorita': la prima che scatta vince
    if (station.oxygen < 20) {
        station.advisorMessage = "ALLERTA: ossigeno critico. Costruisci subito un generatore di ossigeno.";
    }
    else if (station.water < 20) {
        station.advisorMessage = "ALLERTA: riserve d'acqua critiche. Costruisci un riciclatore d'acqua.";
    }
    else if (station.food < 20) {
        station.advisorMessage = "ALLERTA: riserve di cibo critiche. Costruisci una fattoria.";
    }
    else if (station.energy < 20) {
        station.advisorMessage = "Energia scarsa: i pannelli solari attuali non bastano, valuta di espanderli.";
    }
    else if (station.morale < 0.6f) {
        station.advisorMessage = "Morale basso: parchi e centri ricreativi migliorerebbero la situazione.";
    }
    else if (station.population <= 3) {
        station.advisorMessage = "Popolazione molto ridotta: stabilizza le risorse prima di espandere.";
    }
    else if (station.credits >= 80) {
        station.advisorMessage = "Crediti in eccesso: la colonia puo' permettersi nuove infrastrutture.";
    }
    else {
        station.advisorMessage = "Tutti i sistemi nominali. Nessuna azione richiesta.";
    }
}
