#pragma once

class Airport;
class AircraftManager;
struct AircraftType;
struct AircraftFactory;

class TowerSimulation
{
private:
    bool help                        = false;
    Airport* airport                 = nullptr;
    AircraftManager* aircraftManager = nullptr;
    AircraftFactory* aircraftFactory = nullptr;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_keystrokes() const;
    void display_help() const;

    void init_airport();
    void init_aircraftManager();
    void init_aircraftFactory();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
