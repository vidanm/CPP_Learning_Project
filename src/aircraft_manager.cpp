#include "aircraft_manager.hpp"

#include "aircraft.hpp"

#include <memory>

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

    // Sorting aircrafts by priority
    std::sort(aircraftPool.begin(), aircraftPool.end(),
              [](Aircraft* first, Aircraft* second)
              {
                  if (first->has_terminal() && second->has_terminal())
                      return first->remaining_fuel() < second->remaining_fuel();
                  else if (first->has_terminal())
                      return true;
                  else if (second->has_terminal())
                      return false;
                  else
                      return first->remaining_fuel() < second->remaining_fuel();
              });

    for (auto& aircraft : aircraftPool)
    {
        if (!aircraft->move())
            aircraftToRemove.emplace(aircraft);
    }

    auto newEnd = std::remove_if(aircraftPool.begin(), aircraftPool.end(),
                                 [](Aircraft* aircraft) { return !(aircraft->move()); });

    aircraftPool.erase(newEnd, aircraftPool.end());
}