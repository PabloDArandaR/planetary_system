#include "planet.hpp"

Planet::Planet(float radius, float mass, Eigen::Vector3d initial_position, Eigen::Vector3d initial_speed, Eigen::Vector3d initial_acceleration, sf::Color color, std::string name):
    radius(radius), mass(mass), position(initial_position), speed(initial_speed), acceleration(initial_acceleration), color(color), name(name) 
    {}

void Planet::update_acceleration(Eigen::Vector3d sum_F){
    for (int i = 0; i < this->acceleration.size(); i++){
        this->acceleration[i] = sum_F[i]/this->mass;
    }
}

void Planet::update_speed(float t, float t_0){
    for (int i = 0; i < this->speed.size(); i++){
        this->speed[i] = this->speed[i] + this->acceleration[i]*(t - t_0);
    }
}

void Planet::update_pos(float t, float t_0){
    for (int i = 0; i < this->position.size(); i++){
        float speed_term = this->speed[i]*(t - t_0);
        float acc_term = (1/2)*this->acceleration[i]*pow(t - t_0, 2);
        float new_pos = speed_term + acc_term;
        this->position[i] += new_pos;
    }
}

void Planet::update_kin(Eigen::Vector3d sumF, float t, float t_0){
    this->update_acceleration(sumF);
    this->update_speed(t,t_0);
    this->update_pos(t,t_0);
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
sf::Color Planet::get_color(){
    return this->color;
};
std::string Planet::get_name(){
    return this->name;
};