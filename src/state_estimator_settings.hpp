#ifndef STATE_ESTIMATOR_SETTINGS_HPP
#define STATE_ESTIMATOR_SETTINGS_HPP

#include <Eigen/Dense>

// system size
int n_states = 3;
int n_measurements = 4;

// sigma point spread settings
double alpha = 1e-3;
double beta = 2;

// initial states
Eigen::Vector3d x0(0, 0, 0);

// diagonals of covariance matrices
Eigen::Vector3d p(pow(earth_radius,2), pow(earth_radius,2), 1000);
Eigen::Vector3d q(10, 10, 100);
Eigen::Vector4d r(1, 1, 1, 1);

#endif