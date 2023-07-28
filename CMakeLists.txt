cmake_minimum_required(VERSION 3.27.0)
project(StateEstimator)

set(SOURCES
    src/simulation/receiver.cpp
    src/simulation/receiver.hpp
    src/simulation/satellite.cpp
    src/simulation/satellite.hpp
    src/simulation/simulation.cpp
    src/simulation/simulation.hpp
    src/state_estimator/state_estimator.cpp
    src/state_estimator/state_estimator.hpp
    src/state_estimator/weights.cpp
    src/state_estimator/weights.hpp
    src/main.cpp)

find_package (Eigen3 3.4 REQUIRED NO_MODULE)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)
