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

Simulation::Simulation(double t_sim, double t_sample){
    sim_time = t_sim;
    sampling_time = t_sample;

    initialize();
}

void Simulation::initialize(){
    num_samples = sim_time/sampling_time;

    // sim settings
    receiver.initialize(earth_radius/2, earth_radius/2, 1000, 1, 10);
    sat_1.initialize(-30*pi/180);
    sat_2.initialize(-15*pi/180);
    sat_3.initialize(15*pi/180);
    sat_4.initialize(30*pi/180);

    time.resize(num_samples);
    states_rec.resize(num_samples, 3);
    states_sat_1.resize(num_samples, 2);
    states_sat_2.resize(num_samples, 2);
    states_sat_3.resize(num_samples, 2);
    states_sat_4.resize(num_samples, 2);
    ranges.resize(num_samples, 4);

    time(0) = 0;
    states_rec.row(0) << receiver.position.transpose(), receiver.clock_bias;
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
        states_rec.row(i) << receiver.position.transpose(), receiver.clock_bias;
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