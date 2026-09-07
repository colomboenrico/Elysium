//
//  main.cpp
//  SpaceStationSim
//
//  Created by Enrico Colombo on 30/05/2026.
//
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include "SimulationEngine.h"
int main(int argc, const char * argv[]) {
    
    srand(time(nullptr));
    std::cout<<"start"<<std::endl;
    
    SimulationEngine engine;
    
    engine.init();
    
    while(engine.isRunning()){
        engine.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
    engine.shutdown();
    return 0;
}
