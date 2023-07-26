#include <random>

#include "../constants.hpp"
#include "receiver.hpp"

Receiver::Receiver(double init_clock_bias, double init_x_pos, double init_y_pos, double stdev_clock_bias, double stdev_pos_rec){
    initialize(init_clock_bias, init_x_pos, init_y_pos);
}

void Receiver::initialize(double init_clock_bias, double init_x_pos, double init_y_pos){
    clock_bias = init_clock_bias; //c*1e-5

    position.push_back(init_x_pos);
    position.push_back(init_y_pos);

    random_walk_pos_rec.push_back(0);
    random_walk_pos_rec.push_back(0);
}

void Receiver::propagateLocation(double sampling_time){
    std::normal_distribution<double> norm_dist_pos_rec(0,stdev_pos_rec);

    position[0] = position[0] + sampling_time*norm_dist_pos_rec(gen);
    position[1] = position[1] + sampling_time*norm_dist_pos_rec(gen);  
}

void Receiver::propagateClockBias(double sampling_time){
    std::normal_distribution<double> norm_dist_clock_bias(0,stdev_clock_bias);

    clock_bias = clock_bias + sampling_time*norm_dist_clock_bias(gen);   
}
