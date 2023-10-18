#include "planet_system.hpp"


PlanetSystem::PlanetSystem(): n_planets(0), planet_system(std::vector<Planet>()){};

void PlanetSystem::addPlanet(Planet new_planet){
    this->planet_system.push_back(new_planet);
    this -> n_planets = this -> n_planets + 1;
}

void PlanetSystem::generateJsonMetadata(std::string filename){
    Json::Value json_data;
    Json::Value vec(Json::arrayValue);
    for (Planet pl: this->planet_system){
        vec.append(Json::Value(pl.get_name()));
    }
    json_data["planets"] = vec;

    std::ofstream f(filename);
    f << json_data << std::endl;
}

void PlanetSystem::writeLog(double timestamp){
    std::fstream f(this->log_filename, std::ios::app);
    f << std::to_string(timestamp);
    for (Planet pl: this->planet_system){
        f << pl.get_position()[0] << ", " << pl.get_position()[1] << ", " << pl.get_position()[2] << ", ";
        f << pl.get_speed()[0] << ", " << pl.get_speed()[1] << ", " << pl.get_speed()[2] << ", ";
        f << pl.get_acceleration()[0] << ", " << pl.get_acceleration()[1] << ", " << pl.get_acceleration()[2] << std::endl;
    }
}

int PlanetSystem::get_number_of_planets() {
    return this -> n_planets;
}

std::vector<Planet> PlanetSystem::get_planets() {
    return this -> planet_system;
}