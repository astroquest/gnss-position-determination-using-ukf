#ifndef SIM_SETTINGS_HPP
#define SIM_SETTINGS_HPP

#include "constants.hpp"

double sim_time = 60;  // in seconds
double sampling_time = 1;

double init_x_receiver = earth_radius;  // all in meters
double init_y_receiver = 0;
double init_clock_bias_receiver = 1000;
double stdev_position_receiver = 1;
double stdev_clock_bias_receiver = 10;

double init_mean_anomaly_sat_1 = -30;  // give in degrees (converted to radians later)
double init_mean_anomaly_sat_2 = -15;
double init_mean_anomaly_sat_3 = 15;
double init_mean_anomaly_sat_4 = 30;

#endif