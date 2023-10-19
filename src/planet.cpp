#include "planet.hpp"

Planet::Planet(float radius, float mass, Eigen::Vector3d initial_position, Eigen::Vector3d initial_speed, Eigen::Vector3d initial_acceleration, std::string name):
    radius(radius), mass(mass), position(initial_position), speed(initial_speed), acceleration(initial_acceleration), name(name) 
    {}

void Planet::update_acceleration(Eigen::Vector3d sum_F){
    for (int i = 0; i < this->acceleration.size(); i++){
        this->acceleration[i] = sum_F[i]/this->mass;
    }
}

void Planet::update_speed(double timestep){
    for (int i = 0; i < this->speed.size(); i++){
        this->speed[i] = this->speed[i] + this->acceleration[i]*timestep;
    }
}

void Planet::update_position(double timestep){
    for (int i = 0; i < this->position.size(); i++){
        this->position[i] += this->speed[i]*timestep + (1/2)*this->acceleration[i]*pow(timestep, 2);
    }
}

void Planet::update_kin(Eigen::Vector3d sumF, float t, float t_0){
    this->update_acceleration(sumF);
    this->update_speed(t-t_0);
    this->update_position(t-t_0);
}


Eigen::Vector3d Planet::get_position(){
    return this->position;
};
Eigen::Vector3d Planet::get_speed(){
    return this->speed;
};
Eigen::Vector3d Planet::get_acceleration(){
    return this->acceleration;
};
float Planet::get_mass(){
    return this->mass;
};
float Planet::get_radius(){
    return this->radius;
};
std::string Planet::get_name(){
    return this->name;
};