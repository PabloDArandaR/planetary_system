#include "Planet.hpp"
#include <vector>
#include <math.h>
#include <iostream>
#include <eigen3/Eigen/Eigen>


Eigen::Vector3d gravity(Planet in1, Planet in2);

Eigen::Vector3d all_interactions(Planet target, std::vector<Planet> system);