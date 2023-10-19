cmake_minimum_required(VERSION 3.10)
project(Planet VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
enable_testing()

find_package(Eigen3 REQUIRED NO_MODULE)
find_package(GTest REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(Boost 1.40 COMPONENTS program_options REQUIRED )
find_package(yaml-cpp REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

include_directories(src)
include_directories(include)
include_directories(${Boost_INCLUDE_DIR})
link_directories(src)
link_directories(include)

set(SOURCES src/main.cpp src/aux.cpp src/forces.cpp src/planet_system.cpp src/planet.cpp src/simulation_scenario.cpp)
set(HEADERS include/aux.hpp include/forces.cpp include/planet_system.cpp include/planet.cpp include/simulation_scenario.cpp)

add_executable(main ${SOURCES})
target_link_libraries (main Eigen3::Eigen sfml-graphics yaml-cpp jsoncpp ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)


## TESTS 

# message(STATUS "Building test cases")
# set(COMMON_TEST_SOURCES include/planet.hpp include/forces.hpp include/simulation_scenario.hpp src/planet.cpp src/forces.cpp src/simulation_scenario.cpp)
# add_executable(gravity_tests  tests/test_gravity.cc ${COMMON_TEST_SOURCES})
# target_link_libraries(gravity_tests GTest::gtest_main sfml-graphics Eigen3::Eigen jsoncpp)
# target_include_directories(gravity_tests PRIVATE include)
# include(GoogleTest)
# gtest_discover_tests(gravity_tests)