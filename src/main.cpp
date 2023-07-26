#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <Eigen/Dense>

#include "constants.hpp"
#include "simulation/receiver.hpp"
#include "simulation/satellite.hpp"
#include "simulation/simulation.hpp"
#include "state_estimator/weights.hpp"

int main(){
    // int n = 3;
    // int m = 4;
    // double alpha = 1e-3;
    // double beta = 2;
    // double* p = (double [3]){10,10,10};
    // double* q = (double [3]){10,10,10};
    // double* r = (double [4]){10,10,10,10};

    // Weights weights(n, m, alpha, beta, p, q, r);

    // std::cout << weights.P << std::endl;

    // Eigen::MatrixXd P(3,3);
    // P << 10, 0, 0, 0, 10, 0, 0, 0, 10;

    // Eigen::MatrixXd S = P.llt().matrixL();

    // std::cout << P << std::endl;
    // std::cout << S.col(0) << std::endl;

    // Eigen::MatrixXd M(3,3);
    // Eigen::VectorXd V(3);
    // M << 0, 0, 0, 0, 0, 0, 0, 0, 0;
    // V << 1,1,1;
    // std::cout << M << std::endl;
    // // M(Eigen::all, 0) = V;
    // M.col(0) = V;
    // std::cout << M << std::endl;

    return 0;
}
