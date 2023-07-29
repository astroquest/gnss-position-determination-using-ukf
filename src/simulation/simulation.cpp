#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>

#include "../constants.hpp"
#include "receiver.hpp"
#include "satellite.hpp"
#include "simulation.hpp"

Simulation::Simulation(double t_sim, double t_sample, double init_x_receiver,
                        double init_y_receiver, double init_clock_bias_receiver, 
                        double stdev_position_receiver, double stdev_clock_bias_receiver,
                        double init_mean_anomaly_sat_1, double init_mean_anomaly_sat_2, 
                        double init_mean_anomaly_sat_3, double init_mean_anomaly_sat_4){
    sim_time = t_sim;
    sampling_time = t_sample;

    initialize(init_x_receiver, init_y_receiver, init_clock_bias_receiver, 
                stdev_position_receiver, stdev_clock_bias_receiver,
                init_mean_anomaly_sat_1, init_mean_anomaly_sat_2,
                init_mean_anomaly_sat_3, init_mean_anomaly_sat_4);
}

void Simulation::initialize(double init_x_receiver, double init_y_receiver, double init_clock_bias_receiver, 
                            double stdev_position_receiver, double stdev_clock_bias_receiver,
                            double init_mean_anomaly_sat_1, double init_mean_anomaly_sat_2, 
                            double init_mean_anomaly_sat_3, double init_mean_anomaly_sat_4){
    num_samples = sim_time/sampling_time;

    receiver.initialize(init_x_receiver, init_y_receiver, init_clock_bias_receiver,
                        stdev_position_receiver, stdev_clock_bias_receiver);
    sat_1.initialize(init_mean_anomaly_sat_1*pi/180);
    sat_2.initialize(init_mean_anomaly_sat_2*pi/180);
    sat_3.initialize(init_mean_anomaly_sat_3*pi/180);
    sat_4.initialize(init_mean_anomaly_sat_4*pi/180);

    time.resize(num_samples);
    states_receiver.resize(num_samples, 3);
    states_sat_1.resize(num_samples, 2);
    states_sat_2.resize(num_samples, 2);
    states_sat_3.resize(num_samples, 2);
    states_sat_4.resize(num_samples, 2);
    ranges.resize(num_samples, 4);

    time(0) = 0;
    states_receiver.row(0) << receiver.position.transpose(), receiver.clock_bias;
    states_sat_1.row(0) << sat_1.position.transpose();
    states_sat_2.row(0) << sat_2.position.transpose();
    states_sat_3.row(0) << sat_3.position.transpose();
    states_sat_4.row(0) << sat_4.position.transpose();
    ranges.row(0) << getPseudorange(receiver.position, sat_1.position, receiver.clock_bias),
                        getPseudorange(receiver.position, sat_2.position, receiver.clock_bias),
                        getPseudorange(receiver.position, sat_3.position, receiver.clock_bias),
                        getPseudorange(receiver.position, sat_4.position, receiver.clock_bias);
}

void Simulation::run(){
    for(int i = 1; i < num_samples; i++){
        receiver.propagateLocation(sampling_time);
        receiver.propagateClockBias(sampling_time);

        sat_1.propagateOrbit(sampling_time);
        sat_2.propagateOrbit(sampling_time);
        sat_3.propagateOrbit(sampling_time);
        sat_4.propagateOrbit(sampling_time);

        time(i) = time(i-1) + sampling_time;
        states_receiver.row(i) << receiver.position.transpose(), receiver.clock_bias;
        states_sat_1.row(i) << sat_1.position.transpose();
        states_sat_2.row(i) << sat_2.position.transpose();
        states_sat_3.row(i) << sat_3.position.transpose();
        states_sat_4.row(i) << sat_4.position.transpose();
        ranges.row(i) << getPseudorange(receiver.position, sat_1.position, receiver.clock_bias),
                            getPseudorange(receiver.position, sat_2.position, receiver.clock_bias),
                            getPseudorange(receiver.position, sat_3.position, receiver.clock_bias),
                            getPseudorange(receiver.position, sat_4.position, receiver.clock_bias);
    }
}

double Simulation::getPseudorange(Eigen::Vector2d pos_rec, Eigen::Vector2d pos_sat, double clock_bias){
    return sqrt(pow(pos_rec(0) - pos_sat(0),2) + pow(pos_rec(1) - pos_sat(1),2)) + clock_bias;
}