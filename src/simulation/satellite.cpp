#include <random>

#include "../constants.hpp"
#include "satellite.hpp"

Satellite::Satellite(double r, double M0){
    orbital_radius = r;

    initialize(M0);
}

void Satellite::initialize(double init_mean_anomaly){
    mean_anomaly = init_mean_anomaly;
    mean_anomaly_change = sqrt(mu/pow(orbital_radius, 3));

    position.push_back(orbital_radius*cos(mean_anomaly));
    position.push_back(orbital_radius*sin(mean_anomaly));
}

void Satellite::propagateOrbit(double sampling_time){
    mean_anomaly = mean_anomaly + sampling_time*(mean_anomaly_change - earth_radial_velocity);

    position[0] = orbital_radius*cos(mean_anomaly);
    position[1] = orbital_radius*sin(mean_anomaly);    
}
