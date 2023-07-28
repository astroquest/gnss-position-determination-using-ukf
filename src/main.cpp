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

// TODO optimize matrix declarations (i.e. <double, dynamic, 3>)

void simDump(std::string file_name, Eigen::VectorXd time, Eigen::MatrixXd input, Eigen::MatrixXd output){
    std::ofstream dump;
    dump.open(file_name);
    dump << "t (s)" << ","
            << "x_sat_1 (m)" << "," << "y_sat_1 (m)" << "," << "R_1 (m)" << ","
            << "x_sat_2 (m)" << "," << "y_sat_2 (m)" << "," << "R_2 (m)" << ","
            << "x_sat_3 (m)" << "," << "y_sat_3 (m)" << "," << "R_3 (m)" << ","
            << "x_sat_4 (m)" << "," << "y_sat_4 (m)" << "," << "R_4 (m)" << std::endl;

    for(int i = 0; i < time.rows(); i++){
        dump << std::setprecision(4) << time(i) << ","
                << input(i,0) << "," << input(i,1) << "," << output(i,0) << ","
                << input(i,2) << "," << input(i,3) << "," << output(i,1) << ","
                << input(i,4) << "," << input(i,5) << "," << output(i,2) << ","
                << input(i,6) << "," << input(i,7) << "," << output(i,3) << std::endl;
    }
    dump.close();
}

void stateEstimationDump(std::string file_name, Eigen::VectorXd time, Eigen::MatrixXd baseline, Eigen::MatrixXd estimates){
    std::ofstream dump;
    dump.open(file_name);
    dump << "t (s)" << ","
            << "x_rec_baseline (m)" << "," << "y_rec_baseline (m)" <<  ","
            << "clock_bias_baseline (m)" << ","
            << "x_rec (m)" << "," << "y_rec (m)"  << ","
            << "clock_bias (m)" << std::endl;

    for(int i = 0; i < time.rows(); i++){
        dump << std::setprecision(4) << time(i) << ","
                << baseline(i,0) << "," << baseline(i,1) << ","
                << baseline(i,2) << ","
                << estimates(i,0) << "," << estimates(i,1) << ","
                << estimates(i,2) << std::endl;               
    }
    dump.close();
}

int main(){
    //// SIMULATION
    Simulation simulation(120, 1);
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
    Eigen::Vector3d x0;
    x0 << 0, 0, 0;

    StateEstimator state_estimator(3, 4, x0);

    Eigen::MatrixXd state_estimates;
    state_estimates.resize(simulation.num_samples, 3);

    for(int i = 0; i < simulation.num_samples; i++){
        state_estimator.getSigmaPoints();
        state_estimator.predict(input.row(i).transpose());
        state_estimator.getKalmanGain();
        state_estimator.correct(output.row(i).transpose());

        state_estimates.row(i) = state_estimator.x_corr.transpose();
    }

    std::cout << baseline << std::endl;
    std::cout << std::endl;
    std::cout << state_estimates << std::endl;

    simDump("../data/sim_results.txt", simulation.time, input, output);
    stateEstimationDump("../data/estimation_results.txt", simulation.time, baseline, state_estimates);

    return 0;
}
