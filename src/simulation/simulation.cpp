#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <cmath>

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
    receiver.initialize(c, earth_radius, 0);
    satellite_1.initialize(0);
    satellite_2.initialize(10*pi/180);
    satellite_3.initialize(20*pi/180);
    satellite_4.initialize(30*pi/180);

    time.push_back(0);

    x_rec.push_back(receiver.position[0]);
    y_rec.push_back(receiver.position[1]);
    clock_bias_rec.push_back(receiver.clock_bias);

    x_sat_1.push_back(satellite_1.position[0]);
    y_sat_1.push_back(satellite_1.position[1]);
    range_1.push_back(getPseudorange(receiver.position[0], receiver.position[1], satellite_1.position[0], satellite_1.position[1], receiver.clock_bias));

    x_sat_2.push_back(satellite_2.position[0]);
    y_sat_2.push_back(satellite_2.position[1]);
    range_2.push_back(getPseudorange(receiver.position[0], receiver.position[1], satellite_2.position[0], satellite_2.position[1], receiver.clock_bias));

    x_sat_3.push_back(satellite_3.position[0]);
    y_sat_3.push_back(satellite_3.position[1]);
    range_3.push_back(getPseudorange(receiver.position[0], receiver.position[1], satellite_3.position[0], satellite_3.position[1], receiver.clock_bias));

    x_sat_4.push_back(satellite_4.position[0]);
    y_sat_4.push_back(satellite_4.position[1]);
    range_4.push_back(getPseudorange(receiver.position[0], receiver.position[1], satellite_4.position[0], satellite_4.position[1], receiver.clock_bias));
}

void Simulation::run(){
    num_samples = sim_time/sampling_time;

    for(int i = 0; i < num_samples; i++){
        double time_next = time[i] + sampling_time;
        
        receiver.propagateLocation(sampling_time);
        receiver.propagateClockBias(sampling_time);

        satellite_1.propagateOrbit(sampling_time);
        satellite_2.propagateOrbit(sampling_time);
        satellite_3.propagateOrbit(sampling_time);
        satellite_4.propagateOrbit(sampling_time);

        time.push_back(time_next);

        x_rec.push_back(receiver.position[0]);
        y_rec.push_back(receiver.position[1]);
        clock_bias_rec.push_back(receiver.clock_bias);

        x_sat_1.push_back(satellite_1.position[0]);
        y_sat_1.push_back(satellite_1.position[1]);
        range_1.push_back(getPseudorange(receiver.position[0], receiver.position[1], satellite_1.position[0], satellite_1.position[1], receiver.clock_bias));  // <- use pointer here?

        x_sat_2.push_back(satellite_2.position[0]);
        y_sat_2.push_back(satellite_2.position[1]);
        range_2.push_back(getPseudorange(receiver.position[0], receiver.position[1], satellite_2.position[0], satellite_2.position[1], receiver.clock_bias));

        x_sat_3.push_back(satellite_3.position[0]);
        y_sat_3.push_back(satellite_3.position[1]);
        range_3.push_back(getPseudorange(receiver.position[0], receiver.position[1], satellite_3.position[0], satellite_3.position[1], receiver.clock_bias));

        x_sat_4.push_back(satellite_4.position[0]);
        y_sat_4.push_back(satellite_4.position[1]);
        range_4.push_back(getPseudorange(receiver.position[0], receiver.position[1], satellite_4.position[0], satellite_4.position[1], receiver.clock_bias));
    }
}

void Simulation::dump(std::string file_name){
    std::ofstream dump;
    dump.open(file_name);
    dump << "t (s)" << "," << "x_rec (m)" << "," << "y_rec (m)" << "," << "ctr (m)" << "," 
            << "x_sat_1 (m)" << "," << "y_sat_1 (m)" << "," << "R_1 (m)" << ","
            << "x_sat_2 (m)" << "," << "y_sat_2 (m)" << "," << "R_2 (m)" << ","
            << "x_sat_3 (m)" << "," << "y_sat_3 (m)" << "," << "R_3 (m)" << ","
            << "x_sat_4 (m)" << "," << "y_sat_4 (m)" << "," << "R_4 (m)" << std::endl;

    for (int i = 0; i < time.size(); i++){
        dump << std::setprecision(4) << time[i] << "," << x_rec[i] << "," << y_rec[i] << "," << clock_bias_rec[i] << ","
            << x_sat_1[i] << "," << y_sat_1[i] << "," << range_1[i] << ","
            << x_sat_2[i] << "," << y_sat_2[i] << "," << range_2[i] << ","
            << x_sat_3[i] << "," << y_sat_3[i] << "," << range_3[i] << ","
            << x_sat_4[i] << "," << y_sat_4[i] << "," << range_4[i] << std::endl;
    }
    dump.close();
}

double Simulation::getPseudorange(double x_rec, double y_rec, double x_sat, double y_sat, double clock_bias){
    return sqrt(pow(x_rec - x_sat, 2) + pow(y_rec - y_sat, 2)) + clock_bias;
}