#include "aircraft_factory.hpp"

#include "aircraft.hpp"
#include "airport.hpp"

Aircraft* AircraftFactory::create_aircraft(Airport& airport, const AircraftType& type) const
{
    const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    Aircraft* aircraft = new Aircraft { type, flight_number, start, direction, airport.get_tower() };
    return aircraft;
}

Aircraft* AircraftFactory::create_random_aircraft(Airport& airport) const
{
    return create_aircraft(airport, *(aircraft_types[rand() % 3]));
}