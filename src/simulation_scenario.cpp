#include <chrono>
#include <filesystem>
#include <fstream>

#include "simulation_scenario.hpp"
#include "planet_system.hpp"

simulationScenario::simulationScenario(){
    this -> time = 0.0;

    const auto now = std::chrono::system_clock::now();
    std::time_t starting_time = std::chrono::system_clock::to_time_t(now);
    std::tm timeinfo = *std::localtime(&starting_time);
    this->log_filename = "log/" + std::to_string(timeinfo.tm_year + 1900) + "_" + 
        std::to_string(timeinfo.tm_mon + 1) + "_" + 
        std::to_string(timeinfo.tm_mday) + "_" + 
        std::to_string(timeinfo.tm_hour) + "_" + 
        std::to_string(timeinfo.tm_min) + "_" + 
        std::to_string(timeinfo.tm_sec) + ".csv";
    
    if (!std::filesystem::exists("log")){
        if (std::filesystem::create_directory("log")) {
            std::cout << "Folder created successfully." << std::endl;
        } else {
            std::cerr << "Failed to create the folder." << std::endl;
        }
    }

    this->log_file = std::ofstream(this->log_filename);
    if (this->log_file.is_open()){
        this->log_file.close();
    }
};

void simulationScenario::set_time(double new_time){
    this->time = new_time;
}

void simulationScenario::set_system(PlanetSystem new_system){
    this -> system = new_system;
    for (int i {0}; i < new_system.get_planets().size(); ++i){
        this -> forces_in_each_planet[i] = Eigen::Vector3d::Zero();
    }
};

PlanetSystem& simulationScenario::get_system(){
    return this -> system;
}

double simulationScenario::get_time(){
    return this -> time;
}

void simulationScenario::updateForces(){
    for (int i {0}; i < this->system.get_number_of_planets(); ++i){
        this->forces_in_each_planet[i] << 0.0, 0.0, 0.0;
    }
    for (int i {0}; i < this->system.get_number_of_planets(); ++i){
        for (int j {i}; j < this->system.get_number_of_planets(); ++j){
            if (i != j){
                Planet* pl1{this->system.get_planets()[i]};
                Planet* pl2{this->system.get_planets()[j]};
                Eigen::Vector3d new_force = forces::gravity(pl1, pl2);
                this->forces_in_each_planet[i] = this->forces_in_each_planet[i] + new_force;
                this->forces_in_each_planet[j] = this->forces_in_each_planet[j] - new_force;
            }
        }
    }
}

void simulationScenario::updateKin(double& delta_t){
    int i {0};
    for (int i {0}; i < this->system.get_number_of_planets(); ++i){
        this->system.get_planets()[i]->update_acceleration(this->forces_in_each_planet[i]);
        this->system.get_planets()[i]->update_speed(delta_t);
        this->system.get_planets()[i]->update_position(delta_t);
    }
}

void simulationScenario::simulate_timesteps(double& delta_t){
    this -> updateForces();
    this -> updateKin(delta_t);
}

void simulationScenario::initialize_log(){
    this->log_file.open(this->log_filename, std::ios_base::app);
    this->log_file << "time";
    for (Planet* pl: this->system.get_planets()){
        this->log_file << " ," + pl->get_name() + "_position_x" + " ," + pl->get_name() + "_position_y" + " ," + pl->get_name() + "_position_z";
        this->log_file << " ," + pl->get_name() + "_speed_x" + " ," + pl->get_name() + "_speed_y" + " ," + pl->get_name() + "_speed_z";
        this->log_file << " ," + pl->get_name() + "_acceleration_x" + " ," + pl->get_name() + "_acceleration_y" + " ," + pl->get_name() + "_acceleration_z";
    }
    this->log_file << "\n";
    this->log_file.close();
}

void simulationScenario::update_log(){
    this->log_file.open(this->log_filename, std::ios_base::app);
    this->log_file << std::to_string(this->time);
    for (Planet* pl: this->system.get_planets()){
        this->log_file << " ," + std::to_string(pl->get_position()[0]) +  " ," + std::to_string(pl->get_position()[1]) + " ," + std::to_string(pl->get_position()[2]);
        this->log_file << " ," + std::to_string(pl->get_speed()[0]) +  " ," + std::to_string(pl->get_speed()[1]) + " ," + std::to_string(pl->get_speed()[2]);
        this->log_file << " ," + std::to_string(pl->get_acceleration()[0]) +  " ," + std::to_string(pl->get_acceleration()[1]) + " ," + std::to_string(pl->get_acceleration()[2]);
    }
    this->log_file << "\n";
    this->log_file.close();
}

void simulationScenario::set_config_filename(std::string new_config_filename){
    this->log_filename = new_config_filename;
}