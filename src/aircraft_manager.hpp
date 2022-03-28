#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
public:
    AircraftManager() {}
    void add_aircraft(Aircraft* aircraft);
    void move() override;

private:
    using AircraftPool        = std::vector<Aircraft*>;
    AircraftPool aircraftPool = {};
    bool toDelete;
};