# Compila il simulatore C++ (stesso codice del progetto Xcode)
FROM gcc:13 AS build
WORKDIR /src
COPY SpaceStationSim/SpaceStationSim /src

RUN g++ -std=c++17 -O2 -Wall \
    -static-libgcc -static-libstdc++ \
    -Iinclude/Core -Iinclude/System \
    main.cpp \
    src/Core/SimulationEngine.cpp \
    src/System/EventSystem.cpp \
    src/System/Greenhouse.cpp \
    src/System/LifeSupportSystem.cpp \
    src/System/OxygenGenerator.cpp \
    src/System/PopulationSystem.cpp \
    src/System/SolarModule.cpp \
    src/System/SolarPanelSystem.cpp \
    src/System/SolarPlant.cpp \
    src/System/WaterRecycle.cpp \
    src/System/FarmSystem.cpp \
    src/System/EconomySystem.cpp \
    src/System/MoraleSystem.cpp \
    src/System/AdvisorSystem.cpp \
    -o /sim

# Immagine finale, leggera: contiene solo l'eseguibile
FROM debian:bookworm-slim
COPY --from=build /sim /sim
VOLUME /data
CMD ["/sim"]
