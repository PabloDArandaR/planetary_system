#include <vector>
#include <jsoncpp/json/json.h>
#include <fstream>
#include "planet.hpp"
#include "forces.hpp"

#ifndef PLANET_SYSTEM_HPP
#define PLANET_SYSTEM_HPP

class PlanetSystem {
    public:
        PlanetSystem();
        PlanetSystem(int n_planets);

        void addPlanet(Planet* new_planet);
        
        std::vector<Planet*> get_planets();
        int get_number_of_planets();

    private:
        std::vector<Planet*> planet_system;
        std::string log_filename;
        int n_planets;

};


#endif