#include "forces.hpp"

#define G 6.67430e-4

Eigen::Vector3d gravity(Planet in1, Planet in2){
    Eigen::Vector3d gravity = Eigen::Vector3d::Zero();

    Eigen::Vector3d position = in1.get_position() - in2.get_position();
    double distance = position.norm();
    double force_scalar = G*in1.get_mass()*in2.get_mass()/pow(distance,3);
    gravity = force_scalar * position;

    for (int i = 0; i < gravity.size(); i++){
        std::cout << "/t " << gravity[i] << std::endl;
    }

    return gravity;
}

std::vector<Eigen::Vector3d> gravity_system(std::vector<Planet> system){

    std::vector<Eigen::Vector3d> output(0, Eigen::Vector3d::Zero());
    for (int i = 0; i < system.size(); i++){
        Eigen::Vector3d sum_F  = Eigen::Vector3d::Zero();
        for (int j = 0; j < system.size(); j++){
            if (i != j){
                sum_F = sum_F + gravity(system[i], system[j]);
            }
        }
        output.push_back(sum_F);
    }

    return output;
}