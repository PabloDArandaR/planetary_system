#include <fstream>
#include <boost/program_options.hpp>

#include "aux.hpp"
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

int main(int argc, char *argv[])
{
    double timestep {60};
    double duration {SECONDS_IN_A_YEAR};
    PlanetSystem simulation_system = PlanetSystem();

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("config_file", boost::program_options::value<std::string>(), "path to config file")
        ("timestep", boost::program_options::value<double>(), "Timestep [s]. Default 60 [s]")
        ("duration", boost::program_options::value<double>(), "Simulation time [s]. Default 31536000 [s] (one year).")
        //("log_file", boost::program_options::value<std::string>(), "Logfile name. Default log/YEAR_MONTH_DAY_HOUR_MINUTE_SECOND.csv.")
        ;
    
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }
    if (vm.count("config_file")){
        simulation_system = aux::parse_config_file(vm["config_file"].as<std::string>());
    }
    else{
        std::cout << "No config file added, exiting..." << std::endl;
        return 1;
    }
    if (vm.count("timestep")){
        timestep = vm["timestep"].as<double>();
    }
    if (vm.count("duration")){
        duration = vm["duration"].as<double>();
    }
    if (vm.count("log_file")){
        //
    }

    simulationScenario scenario = simulationScenario();
    scenario.set_system(simulation_system);

    scenario.initialize_log();
    scenario.update_log();
    while (scenario.get_time() < duration){
        scenario.simulate_timesteps(timestep);
        scenario.update_log();
        scenario.set_time(scenario.get_time() + timestep);
    }

    return 0;
}