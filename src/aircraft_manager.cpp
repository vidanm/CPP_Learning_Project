#include "aircraft_manager.hpp"

#include "aircraft.hpp"

#include <memory>

void AircraftManager::add_aircraft(std::unique_ptr<Aircraft>& aircraft)
{
    this->aircraftPool.emplace_back(std::move(aircraft));
}

void AircraftManager::move()
{
    // Sorting aircrafts by priority
    std::sort(aircraftPool.begin(), aircraftPool.end(),
              [](std::unique_ptr<Aircraft>& first, std::unique_ptr<Aircraft>& second)
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

    auto newEnd = std::remove_if(aircraftPool.begin(), aircraftPool.end(),
                                 [this](std::unique_ptr<Aircraft>& aircraft)
                                 {
                                     try
                                     {
                                         return !(aircraft->move());
                                     } catch (const AircraftCrash& crash)
                                     {
                                         std::cerr << crash.what() << std::endl;
                                         crashed_airplanes++;
                                         return true;
                                     }
                                 });

    aircraftPool.erase(newEnd, aircraftPool.end());
}
unsigned int AircraftManager::get_required_fuel()
{
    unsigned int sum = 0;
    for (auto& aircraft : aircraftPool)
    {
        if (aircraft->is_low_on_fuel())
        {
            sum += 3000 - aircraft->remaining_fuel();
        }
    }
    return sum;
}

unsigned int AircraftManager::get_crashed_numbers()
{
    return this->crashed_airplanes;
}