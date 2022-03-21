
#include "aircraft.hpp"
#include "aircraft_types.hpp"

#include <unordered_set>
struct AircraftType;
struct Airtport;

class AircraftFactory
{
public:
    AircraftFactory() {}
    Aircraft* create_aircraft(Airport& airport, const AircraftType& type);
    Aircraft* create_random_aircraft(Airport& airport);

private:
    AircraftType* aircraft_types[3] {
        new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } },
        new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } },
        new AircraftType { .02f, .1f, .05f, MediaPath { "concorde_af.png" } },
    };

    std::unordered_set<std::string> used_number = {};
    std::string airlines[8]                     = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
};