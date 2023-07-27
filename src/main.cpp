#include <iostream>
#include <cmath>
// #include <random>
// #include <fstream>
#include <Eigen/Dense>

// #include "constants.hpp"
// #include "simulation/receiver.hpp"
// #include "simulation/satellite.hpp"
// #include "simulation/simulation.hpp"
#include "state_estimator/weights.hpp"
#include "state_estimator/state_estimator.hpp"

int main(){
    int n = 3;
    int m = 4;
    Eigen::VectorXd x0(3);
    x0 << 1, 2, 3;

    StateEstimator state_estimator(3, 4, x0);
    // std::cout << state_estimator.x_corr << std::endl;
    state_estimator.setSigmaPoints();


    return 0;
}
