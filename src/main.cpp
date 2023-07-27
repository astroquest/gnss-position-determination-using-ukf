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
    //// SIMULATION
    Simulation simulation(100, 10);
    simulation.run();

    Eigen::MatrixXd baseline = simulation.states_rec;
    Eigen::MatrixXd input;
    input.resize(simulation.num_samples, 4*2);
    input << simulation.states_sat_1, 
                simulation.states_sat_2, 
                simulation.states_sat_3, 
                simulation.states_sat_4;
    Eigen::MatrixXd output = simulation.ranges;
    output.resize(simulation.num_samples, 4);

    //// STATE ESTIMATION
    Eigen::VectorXd x0(4);
    x0 << 0, 0, 0, c;

    StateEstimator state_estimator(3, 4, x0);

    for(int i = 0; i < 100; i++){
        state_estimator.getSigmaPoints();
        std::cout << state_estimator.x_corr << std::endl;
        state_estimator.predict(input.row(i).transpose());
        state_estimator.getKalmanGain();
        state_estimator.correct(output.row(i).transpose());
    }


    return 0;
}
