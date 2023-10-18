#include "simulation_scenario.hpp"
#include "planet_system.hpp"

void simulationScenario::addSystem(PlanetSystem new_system){
    this -> system = new_system;
    for (int i {0}; i < new_system.get_planets().size(); ++i){
        this -> forces_in_each_planet[i] = std::vector<Eigen::Vector3d>(
            new_system.get_number_of_planets(), Eigen::Vector3d::Zero());
    }
};

PlanetSystem& simulationScenario::get_system(){
    return this -> system;
}

double simulationScenario::get_time(){
    return this -> time;
}

void simulationScenario::updateForces(){
    for (int i {0}; i <= this->system.get_number_of_planets(); ++i){
        for (int j {i}; j <= this->system.get_number_of_planets(); ++j){
            if (i != j){
                Eigen::Vector3d new_force = forces::gravity(this->system.get_planets()[i], this->system.get_planets()[j]);
                this->forces_in_each_planet[i][j] = new_force;
                this->forces_in_each_planet[j][i] = -new_force;
            }
        }
    }
}

void simulationScenario::simulate_timesteps(double& delta_t){
    this -> updateForces();
    this -> updateKin();'
}

simulationScenario::simulationScenario(){
    this -> time = 0.0;
};