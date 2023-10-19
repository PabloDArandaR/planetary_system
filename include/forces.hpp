#include <vector>
#include <math.h>
#include <iostream>
#include <eigen3/Eigen/Eigen>

#include "planet.hpp"

namespace forces {
    Eigen::Vector3d gravity(Planet* in1, Planet* in2);
}