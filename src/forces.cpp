#include "forces.hpp"
#include "constants.hpp"

#ifndef FORCES_GUARD
#define FORCES_GUARD


Eigen::Vector3d forces::gravity(Planet& in1, Planet& in2){

    Eigen::Vector3d position = in2.get_position() - in1.get_position();

    Eigen::Vector3d force = G*in1.get_mass()*in2.get_mass()*position/pow(position.norm(),3);

    return force;
}

#endif