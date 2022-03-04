#include "aircraft_manager.hpp"

#include "aircraft.hpp"

void AircraftManager::add_aircraft(Aircraft* aircraft)
{
    this->aircraftPool.emplace(aircraft);
}