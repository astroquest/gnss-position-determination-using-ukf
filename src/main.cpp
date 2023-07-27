#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <Eigen/Dense>

#include "constants.hpp"
#include "simulation/receiver.hpp"
#include "simulation/satellite.hpp"
#include "simulation/simulation.hpp"
#include "state_estimator/weights.hpp"
#include "state_estimator/state_estimator.hpp"

int main(){
    Simulation simulation(3600, 10);
    simulation.run();

    Eigen::VectorXd x0(3);
    x0 << 1, 2, 3;

    // StateEstimator state_estimator(3, 4, x0);

    // for(int i = 0; i < 100; i++){
    //     state_estimator.getSigmaPoints();
    //     state_estimator.predict(input(Eigen::all,i));
    //     state_estimator.getKalmanGain();
    //     state_estimator.correct(output(Eigen::all,i));
    // }


    return 0;
}
