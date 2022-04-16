#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
public:
    AircraftManager() {}
    void add_aircraft(std::unique_ptr<Aircraft>& aircraft);
    void move() override;
    unsigned int get_required_fuel();
    unsigned int get_crashed_numbers();

private:
    using AircraftPool             = std::vector<std::unique_ptr<Aircraft>>;
    AircraftPool aircraftPool      = {};
    unsigned int crashed_airplanes = 0;
};