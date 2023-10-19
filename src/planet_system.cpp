#include "planet_system.hpp"


PlanetSystem::PlanetSystem(): n_planets(0), planet_system(std::vector<Planet*>()){};

void PlanetSystem::addPlanet(Planet* new_planet){
    this->planet_system.push_back(new_planet);
    this -> n_planets = this -> n_planets + 1;
}

int PlanetSystem::get_number_of_planets() {
    return this -> n_planets;
}

std::vector<Planet*> PlanetSystem::get_planets() {
    return this -> planet_system;
}