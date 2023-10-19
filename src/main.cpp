#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include "planet.hpp"
#include "forces.hpp"
#include "simulation_scenario.hpp"
#include "planet_system.hpp"

#define R_MARS 3389.5
#define M_MARS 6.39e23
#define R_ORBIT_MARS 2.273921e11
#define V_ORBIT_MARS 24000
#define R_EARTH 6371
#define M_EARTH 5.972e24
#define R_ORBIT_EARTH 1.49598261e11
#define V_ORBIT_EARTH 29780
#define R_SUN 696340
#define M_SUN 1.989e30
#define METADATA_FILENAME "metadata.yaml"
#define SECONDS_IN_A_YEAR 31536000

int main()
{

    // Define the Planets of the system
    Eigen::Vector3d pos {Eigen::Vector3d::Zero()}, vel {Eigen::Vector3d::Zero()}, acc {Eigen::Vector3d::Zero()};

    pos[0] = 0.0; pos[1] = R_ORBIT_MARS; pos[2] = 0.0;
    vel[0] = -V_ORBIT_MARS; vel[1] = 0.0; vel[2] = 0.0;
    Planet mars = Planet(R_MARS, M_MARS, pos, vel, acc, "Mars");

    pos[0] = 0.0; pos[1] = -R_ORBIT_EARTH; pos[2] = 0.0;
    vel[0] = V_ORBIT_EARTH; vel[1] = 30e3; vel[2] = 0.0;
    Planet earth = Planet(R_EARTH, M_EARTH, pos, vel, acc, "Earth");

    pos[0] = 0.0; pos[1] = 0.0; pos[2] = 0.0;
    vel[0] = 0.0; vel[1] = 0.0; vel[2] = 0.0;
    Planet sun = Planet(R_SUN, M_SUN, pos, vel, acc, "Sun");


    PlanetSystem system = PlanetSystem();
    system.addPlanet(&mars);
    system.addPlanet(&earth);
    system.addPlanet(&sun);

    simulationScenario scenario = simulationScenario();
    scenario.set_system(system);

    // Simulation parameters:
    float dt {1.0};
    double timestep {31536000/365};

    scenario.initialize_log();
    scenario.update_log();
    u_long limit {100000*long(SECONDS_IN_A_YEAR)};
    while (scenario.get_time() < limit){
        scenario.simulate_timesteps(timestep);
        scenario.update_log();
        scenario.set_time(scenario.get_time() + timestep);
    }

    return 0;
}