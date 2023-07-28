#include <random>
#include <Eigen/Dense>
#include <iostream>

#include "../constants.hpp"
#include "receiver.hpp"

Receiver::Receiver(){}

void Receiver::initialize(double init_x_pos, double init_y_pos, double init_clock_bias,
                            double init_stdev_position, double init_stdev_clock_bias){
    stdev_position = init_stdev_position;
    stdev_clock_bias = init_stdev_clock_bias;

    clock_bias = init_clock_bias;
    position << init_x_pos, init_y_pos;
}

void Receiver::propagateLocation(double sampling_time){
    std::normal_distribution<double> distribution_position(0,stdev_position);

    random_walk_position << distribution_position(gen),
                            distribution_position(gen);

    position += sampling_time*random_walk_position;
}

void Receiver::propagateClockBias(double sampling_time){
    std::normal_distribution<double> distribution_clock_bias(0,stdev_clock_bias);

    clock_bias += sampling_time*distribution_clock_bias(gen);   
}
