#include "aircraft.hpp"

class AircraftManager
{
public:
    AircraftManager() {}
    void add_aircraft(Aircraft* aircraft);

private:
    using AircraftPool        = std::unordered_set<Aircraft*>;
    AircraftPool aircraftPool = {};
};