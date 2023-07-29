#include <random>
#include <Eigen/Dense>

#include "../constants.hpp"
#include "satellite.hpp"

Satellite::Satellite(double r){
    orbital_radius = r;
}

void Satellite::initialize(double init_mean_anomaly){
    mean_anomaly = init_mean_anomaly;
    mean_anomaly_change = sqrt(mu/pow(orbital_radius, 3));

    position << orbital_radius*cos(mean_anomaly),
                orbital_radius*sin(mean_anomaly);
}

void Satellite::propagateOrbit(double sampling_time){
    mean_anomaly += sampling_time*(mean_anomaly_change - earth_radial_velocity);

    position << orbital_radius*cos(mean_anomaly),
                orbital_radius*sin(mean_anomaly);  
}
