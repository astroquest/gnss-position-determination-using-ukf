#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <Eigen/Dense>

#include "constants.hpp"
#include "simulation/receiver.hpp"
#include "simulation/satellite.hpp"
#include "simulation/simulation.hpp"

int main(){
    Simulation simulation;

    simulation.run();
    simulation.dump("../data/simulation_results.txt");

    return 0;
}
