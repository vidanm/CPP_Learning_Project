#include "aircraft_factory.hpp"

#include "aircraft.hpp"
#include "airport.hpp"

#include <vector>

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(Airport& airport, const AircraftType& type)
{

    std::string flight_number = "";
    do
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    while (!used_number.empty() && used_number.find(flight_number) != used_number.end());

    used_number.emplace(flight_number);
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    return std::make_unique<Aircraft>(type, flight_number, start, direction, airport.get_tower());
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Airport& airport)
{
    return create_aircraft(airport, *(aircraft_types[rand() % 3]));
}

void AircraftFactory::aircraft_number_by_airlines(const unsigned int airline) const
{
    if (airline >= airlines.size())
    {
        return;
    }

    std::cout << airlines.at(airline) << " : "
              << std::count_if(used_number.begin(), used_number.end(),
                               [this, airline](std::string flight)
                               { return airlines.at(airline).compare(0, 2, flight, 0, 2) == 0; })
              << std::endl;
}

unsigned int AircraftFactory::airlines_number()
{
    return airlines.size();
}
