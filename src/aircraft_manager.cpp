#include "aircraft_manager.hpp"

#include "aircraft.hpp"

void AircraftManager::add_aircraft(Aircraft* aircraft)
{
    this->aircraftPool.emplace(aircraft);
}

void AircraftManager::move()
{
    std::unordered_set<Aircraft*> aircraftToRemove;

    for (auto& aircraft : aircraftPool)
    {
        if (!aircraft->move())
            aircraftToRemove.emplace(aircraft);
    }

    for (auto& aircraft : aircraftToRemove)
    {
        aircraftPool.erase(aircraft);
        delete aircraft;
    }
}