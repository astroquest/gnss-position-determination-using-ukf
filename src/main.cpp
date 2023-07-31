#if __INTELLISENSE__  // needed to fix a vscode intellisense issue with the eigen library 
#undef __ARM_NEON     // -> https://github.com/microsoft/vscode-cpptools/issues/7413
#undef __ARM_NEON__
#endif

#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <Eigen/Dense>

#include "constants.hpp"
#include "sim_settings.hpp"
#include "state_estimator_settings.hpp"
#include "dump.hpp"
#include "simulation/receiver.hpp"
#include "simulation/satellite.hpp"
#include "simulation/simulation.hpp"
#include "state_estimator/weights.hpp"
#include "state_estimator/state_estimator.hpp"

int main(){
    //// SIMULATION
    Simulation simulation(sim_time, sampling_time, init_x_receiver, 
                            init_y_receiver, init_clock_bias_receiver,
                            stdev_position_receiver, stdev_clock_bias_receiver,
                            init_mean_anomaly_sat_1, init_mean_anomaly_sat_2,
                            init_mean_anomaly_sat_3, init_mean_anomaly_sat_4);
    simulation.run();

    Eigen::MatrixXd baseline = simulation.states_receiver;
    Eigen::MatrixXd input;
    input.resize(simulation.num_samples, 4*2);
    input << simulation.states_sat_1, 
                simulation.states_sat_2, 
                simulation.states_sat_3, 
                simulation.states_sat_4;
    Eigen::MatrixXd output = simulation.ranges;
    output.resize(simulation.num_samples, 4);

    //// STATE ESTIMATION
    StateEstimator state_estimator(n_states, n_measurements, alpha, beta, x0, p, q, r);

    Eigen::MatrixXd state_estimates;
    state_estimates.resize(simulation.num_samples, n_states);

    for(int i = 0; i < simulation.num_samples; i++){
        state_estimator.setSigmaPoints();
        state_estimator.predict(input.row(i).transpose());
        state_estimator.setKalmanGain();
        state_estimator.correct(output.row(i).transpose());

        state_estimates.row(i) = state_estimator.x_corr.transpose();
    }

    simDump("../data/sim_results.txt", simulation.time, input, output);
    stateEstimationDump("../data/estimation_results.txt", simulation.time, baseline, state_estimates);

    return 0;
}
