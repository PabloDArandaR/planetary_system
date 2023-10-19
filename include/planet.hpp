#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Eigen>

#ifndef PLANET_GUARD
#define PLANET_GUARD

class Planet {
    private:
        float radius, mass;
        Eigen::Vector3d position, speed, acceleration;
        std::string name;
    public:
        Planet(float radius, float mass, Eigen::Vector3d initial_position, Eigen::Vector3d initial_speed, Eigen::Vector3d initial_acceleration, std::string name);

        void update_acceleration(Eigen::Vector3d sum_F);
        void update_speed(double timestep);
        void update_position(double timestep);
        void update_kin(Eigen::Vector3d sum_F, float t, float t_0);

        Eigen::Vector3d get_position();
        Eigen::Vector3d get_speed();
        Eigen::Vector3d get_acceleration();
        float get_mass();
        float get_radius();
        std::string get_name();
};

#endif