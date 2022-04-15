#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "aircraft_factory.hpp"
#include "aircraft_manager.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    init_aircraftManager();
    init_airport();
    init_aircraftFactory();
    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

/*void TowerSimulation::create_aircraft(const AircraftType& type) const
{
    assert(airport); // make sure the airport is initialized before creating aircraft

    const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    Aircraft* aircraft = new Aircraft { type, flight_number, start, direction, airport->get_tower() };
    aircraftManager->add_aircraft(aircraft);
}
void TowerSimulation::create_random_aircraft() const
    {
        create_aircraft(*(aircraft_types[rand() % 3]));
    }*/

void TowerSimulation::create_keystrokes() const
{
    auto airlines_count = aircraftFactory->airlines_number();

    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace(
        'c', [this]() { aircraftManager->add_aircraft(aircraftFactory->create_random_aircraft(*airport)); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('p', []() { GL::ticks_per_sec++; });
    GL::keystrokes.emplace('o', []() { GL::ticks_per_sec--; });
    for (unsigned int i = 0; i < airlines_count; i++)
    {
        GL::keystrokes.emplace(i + '0', [this, i]() { aircraftFactory->aircraft_number_by_airlines(i); });
    }
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [a, b] : GL::keystrokes)
    {
        std::cout << a << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    // GL::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
    airport->set_aircraft_manager(aircraftManager);
}

void TowerSimulation::init_aircraftManager()
{
    aircraftManager = new AircraftManager();
    GL::move_queue.emplace(aircraftManager);
}

void TowerSimulation::init_aircraftFactory()
{
    aircraftFactory = new AircraftFactory();
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    GL::loop();
}
