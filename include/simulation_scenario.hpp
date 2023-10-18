#include <unordered_map>
#include <eigen3/Eigen/Eigen>

#include "forces.hpp"
#include "planet.hpp"
#include "planet_system.hpp"

class simulationScenario {
    private:
        PlanetSystem system;
        double time;
        std::unordered_map<int, std::vector<Eigen::Vector3d>> forces_in_each_planet;
        void updateForces();

    public:
        simulationScenario();

        void addSystem(PlanetSystem);

        PlanetSystem& get_system();
        
        void simulate_timesteps(double&);
        double get_time();
};