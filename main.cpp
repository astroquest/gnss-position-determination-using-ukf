#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>

#include "constants.h"
#include "receiver.h"
#include "satellite.h"
#include "simulation.h"
#include "kalman_settings.h"
#include "covariances.h"

using namespace std;

int main(){
    Simulation simulation;

    simulation.initialize();
    simulation.run();
    simulation.dumpToFile("simulation_results.txt");

    return 0;
}
