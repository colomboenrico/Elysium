//
//  SimulationEngine.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 30/05/2026.
//

#include "SimulationEngine.h"
#include <algorithm>
#include "SpaceStation.h"
#include "LifeSupportSystem.h"
#include"PopulationSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "SolarPlant.h"
#include "Greenhouse.h"

void SimulationEngine::init(){
    station =  new SpaceStation();
    lifeSupport = new LifeSupportSystem();
    population = new PopulationSystem();
    
    station->oxygen = 100;
    station->water = 100;
    station->energy = 100;
    station->food = 60;
    station->population = 10;
    station->credits = 50;
    station->solarPanels = 1;
    station->waterRecyclers = 1;
    station->oxygenGenerator = 1;
    station->farms = 1;
    station->parks = 0;
    station->luxuryApartments = 0;
    station->entertaimentCenters = 0;
    running = true;
    
    station->modules.push_back(new SolarPlant);
    station->modules.push_back(new Greenhouse);
    
    events= new EventSystem();
    solar = new SolarModule();
    solarPanel = new SolarPanelSystem();
    water = new WaterRecycler();
    oxygen = new OxygenGenerator();
    farm = new FarmSystem();
    economy = new EconomySystem();
    morale = new MoraleSystem();
    advisor = new AdvisorSystem();

    writeState();
}
void SimulationEngine::update(){
    tick++;

    std::string prevEvent = station->lastEvent;

    water->update(*station);
    solarPanel->update(*station);
    oxygen->update(*station);
    solar-> update(*station);
    farm->update(*station);
    economy->update(*station);
    morale->update(*station);
    advisor->update(*station);
    
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
    <<"SOLAR PANEl EFFICIENCY:" <<station->SolarEfficiency*100 <<"%"
    <<std::endl;
    
    if(station->population<=0){
        std::cout<<"STATION FAILED"<<std::endl;
        running=false;
    }
    for(Module* module :station -> modules){
        module ->update(*station);
    }

    // se EventSystem ha generato un evento nuovo, lo registriamo nel log storico
    if(station->lastEvent != prevEvent && !station->lastEvent.empty()){
        logEvent(station->lastEvent);
    }

    processCommands();

    writeState();
}
void SimulationEngine::shutdown(){
    for(Module* module : station->modules){
        delete module;
    }
    station->modules.clear();

    delete station;
    delete lifeSupport;
    delete population;
    delete events;
    delete solar;
    delete solarPanel;
    delete water;
    delete oxygen;
    delete farm;
    delete economy;
    delete morale;
    delete advisor;
}
bool SimulationEngine::isRunning()const{
    return running;
}

void SimulationEngine::logEvent(const std::string& msg){
    station->lastEvent = msg;

    std::ofstream out("/data/events.log", std::ios::app);
    if(!out.is_open()) return;
    out << "{\"tick\":" << tick << ",\"message\":\"" << msg << "\"}\n";
}

void SimulationEngine::processCommands(){
    std::ifstream in("/data/command.txt");
    if(!in.is_open()) return;
    std::string cmd;
    in >> cmd;
    in.close();
    std::remove("/data/command.txt");
    if(cmd.empty()) return;

    if(cmd=="solar"){
        if(station->credits>=30){ station->credits-=30; station->solarPanels++; logEvent("Costruito nuovo pannello solare."); }
        else logEvent("Crediti insufficienti per un pannello solare.");
    }
    else if(cmd=="farm"){
        if(station->credits>=25){ station->credits-=25; station->farms++; logEvent("Costruita nuova fattoria."); }
        else logEvent("Crediti insufficienti per una fattoria.");
    }
    else if(cmd=="water"){
        if(station->credits>=25){ station->credits-=25; station->waterRecyclers++; logEvent("Costruito nuovo riciclatore d'acqua."); }
        else logEvent("Crediti insufficienti per un riciclatore d'acqua.");
    }
    else if(cmd=="oxygen"){
        if(station->credits>=25){ station->credits-=25; station->oxygenGenerator++; logEvent("Costruito nuovo generatore di ossigeno."); }
        else logEvent("Crediti insufficienti per un generatore di ossigeno.");
    }
    else if(cmd=="park"){
        if(station->credits>=20){ station->credits-=20; station->parks++; logEvent("Costruito nuovo parco."); }
        else logEvent("Crediti insufficienti per un parco.");
    }
    else if(cmd=="luxury"){
        if(station->credits>=40){ station->credits-=40; station->luxuryApartments++; logEvent("Costruito nuovo appartamento di lusso."); }
        else logEvent("Crediti insufficienti per un appartamento di lusso.");
    }
    else if(cmd=="entertainment"){
        if(station->credits>=35){ station->credits-=35; station->entertaimentCenters++; logEvent("Costruito nuovo centro ricreativo."); }
        else logEvent("Crediti insufficienti per un centro ricreativo.");
    }
}

void SimulationEngine::writeState(){
    // scrive lo stato su un file temporaneo e poi lo rinomina, cosi'
    // chi legge (il server web) non trova mai un file a meta' scritto.
    const char* tmpPath = "/data/state.json.tmp";
    const char* finalPath = "/data/state.json";

    std::ofstream out(tmpPath);
    if(!out.is_open()){
        // non siamo dentro Docker (es. build locale in Xcode): nessun /data disponibile,
        // la simulazione continua a funzionare normalmente solo su console.
        return;
    }

    out << "{\n"
        << "  \"tick\": " << tick << ",\n"
        << "  \"running\": " << (running ? "true" : "false") << ",\n"
        << "  \"population\": " << station->population << ",\n"
        << "  \"oxygen\": " << station->oxygen << ",\n"
        << "  \"water\": " << station->water << ",\n"
        << "  \"energy\": " << station->energy << ",\n"
        << "  \"food\": " << station->food << ",\n"
        << "  \"credits\": " << station->credits << ",\n"
        << "  \"morale\": " << station->morale << ",\n"
        << "  \"solarEfficiency\": " << station->SolarEfficiency << ",\n"
        << "  \"solarProduction\": " << station->solarProduction << ",\n"
        << "  \"solarPanels\": " << station->solarPanels << ",\n"
        << "  \"waterRecyclers\": " << station->waterRecyclers << ",\n"
        << "  \"oxygenGenerator\": " << station->oxygenGenerator << ",\n"
        << "  \"farms\": " << station->farms << ",\n"
        << "  \"parks\": " << station->parks << ",\n"
        << "  \"luxuryApartments\": " << station->luxuryApartments << ",\n"
        << "  \"entertainmentCenters\": " << station->entertaimentCenters << ",\n"
        << "  \"modules\": " << station->modules.size() << ",\n"
        << "  \"lastEvent\": \"" << station->lastEvent << "\",\n"
        << "  \"advisorMessage\": \"" << station->advisorMessage << "\"\n"
        << "}\n";
    out.close();

    std::rename(tmpPath, finalPath);
}
