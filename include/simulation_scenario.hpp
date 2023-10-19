#include <unordered_map>
#include <eigen3/Eigen/Eigen>

#include "forces.hpp"
#include "planet.hpp"
#include "planet_system.hpp"

class simulationScenario {
    private:
        PlanetSystem system;
        double time;
        std::unordered_map<int, Eigen::Vector3d> forces_in_each_planet;
        std::string log_filename;
        std::ofstream log_file;

        void updateForces();
        void updateKin(double&);

    public:
        simulationScenario();

        void set_system(PlanetSystem);
        void set_time(double);
        void set_config_filename(std::string);

        PlanetSystem& get_system();
        double get_time();
        
        void simulate_timesteps(double&);

        void initialize_log();
        void update_log();
};