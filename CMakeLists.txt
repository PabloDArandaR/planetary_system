cmake_minimum_required(VERSION 3.10)
project(tutorial VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

find_package(SFML 2.5
  COMPONENTS
    system window graphics network audio REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
        
set(SOURCES src/main.cpp include/Planet.hpp include/forces.hpp include/math.hpp)
add_executable(main src/main.cpp)

target_link_libraries (main Eigen3::Eigen)
target_include_directories(main PRIVATE include)
    
target_link_libraries(main sfml-graphics)
#install(TARGETS main DESTINATION bin)