#include "aircraft_manager.hpp"

#include "aircraft.hpp"

void AircraftManager::add_aircraft(Aircraft* aircraft)
{
    this->aircraftPool.emplace_back(aircraft);
}

bool toDelete(Aircraft aircraft)
{
    return !aircraft.move();
}

void AircraftManager::move()
{
    std::unordered_set<Aircraft*> aircraftToRemove;

    for (auto& aircraft : aircraftPool)
    {
        if (!aircraft->move())
            aircraftToRemove.emplace(aircraft);
    }

    auto newEnd = std::remove_if(aircraftPool.begin(), aircraftPool.end(),
                                 [](Aircraft* aircraft) { return !(aircraft->move()); });

    aircraftPool.erase(newEnd, aircraftPool.end());
}