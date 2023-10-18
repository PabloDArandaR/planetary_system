#include <gtest/gtest.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Eigen>
#include "forces.hpp"
#include "planet.hpp"

TEST(GravityCalculations, SimpleCase){
    Eigen::Vector3d pos1 {Eigen::Vector3d::Zero()}, vel1 {Eigen::Vector3d::Zero()}, acc1 {Eigen::Vector3d::Zero()};
    pos1 << 1, 2, 3;
    vel1 << 1, 2, 3;
    acc1 << 1, 2, 3;
    Planet pl1(0.5, 1.0, pos1, vel1, acc1, sf::Color::Red, "pl1");

    Eigen::Vector3d pos2 {Eigen::Vector3d::Zero()}, vel2 {Eigen::Vector3d::Zero()}, acc2 {Eigen::Vector3d::Zero()};
    pos2 << 2, 3, 4;
    vel2 << 2, 3, 4;
    acc2 << 2, 3, 4;
    Planet pl2(0.5, 1.0, pos2, vel2, acc2, sf::Color::Red, "pl2");

    Eigen::Vector3d f_Test1 {Eigen::Vector3d::Zero()};

    double abs_error {1e-9};

    ASSERT_NEAR(forces::gravity(pl1, pl2)[0], f_Test1[0], abs_error) << "Force should be (0.0, 0.0, 0.0) but isn't";
    ASSERT_NEAR(forces::gravity(pl1, pl2)[1], f_Test1[1], abs_error) << "Force should be (0.0, 0.0, 0.0) but isn't";
    ASSERT_NEAR(forces::gravity(pl1, pl2)[2], f_Test1[2], abs_error) << "Force should be (0.0, 0.0, 0.0) but isn't";
}

TEST(GravityCalculations, GravityCalculations_GravityForce_Test){
    Eigen::Vector3d pos1 {Eigen::Vector3d::Zero()}, vel1 {Eigen::Vector3d::Zero()}, acc1 {Eigen::Vector3d::Zero()};
    pos1 << 0, 0, 0;
    vel1 << 0, 0, 0;
    acc1 << 0, 0, 0;
    Planet pl1(0.5, 100, pos1, vel1, acc1, sf::Color::Red, "pl1");

    Eigen::Vector3d pos2 {Eigen::Vector3d::Zero()}, vel2 {Eigen::Vector3d::Zero()}, acc2 {Eigen::Vector3d::Zero()};
    pos2 << 1, 0.5, 0.33;
    vel2 << 0, 0, 0;
    acc2 << 0, 0, 0;
    Planet pl2(0.5, 100, pos2, vel2, acc2, sf::Color::Red, "pl2");

    Eigen::Vector3d f_Test1 {Eigen::Vector3d::Zero()};
    f_Test1 << 4.21332030e-07, 2.10666015e-07, 1.3903957e-07;

    double abs_error {1e-8};

    Eigen::Vector3d result = forces::gravity(pl1, pl2);

    ASSERT_NEAR(result[0], f_Test1[0], abs_error) << "Force should be 4.21332125e-07 but isn't";
    ASSERT_NEAR(result[1], f_Test1[1], abs_error) << "Force should be 2.10666062e-07 but isn't";
    ASSERT_NEAR(result[2], f_Test1[2], abs_error) << "Force should be 1.39039601e-07 but isn't";

}