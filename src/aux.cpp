#include <fstream>
#include <nlohmann/json.hpp>

#include "aux.hpp"
#include "planet.hpp"

using json = nlohmann::json;

PlanetSystem aux::parse_config_file(std::string config_filename){
    PlanetSystem output;

    std::ifstream f(config_filename);
    json data = json::parse(f);

    auto result = data.find("bodies");

    for (auto &array: data["bodies"]){
        Eigen::Vector3d position;
        Eigen::Vector3d velocity;
        Eigen::Vector3d acceleration = Eigen::Vector3d::Zero();
        position << array["initial_position"][0], array["initial_position"][1], array["initial_position"][2]; 
        velocity << array["initial_velocity"][0], array["initial_velocity"][1], array["initial_velocity"][2]; 
        Planet* pl = new Planet(array["radius"], array["mass"], position, velocity, acceleration, array["name"]);

        output.addPlanet(pl);   
    }

    return output;
}