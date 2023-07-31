#include <iostream>
#include <cmath>
#include <Eigen/Dense>

#include "weights.hpp"

Weights::Weights(int n_x, int n_y, double alpha, double beta){
    this->n_x = n_x;
    this->n_y = n_y;
    n_sigma = 2*n_x + 1;

    this->alpha = alpha;
    this->beta = beta;

    setLambda();
    setEta();
    setSigmaPointWeights();
}

void Weights::setLambda(){
    lambda = n_x*(pow(alpha,2) - 1);
}

void Weights::setEta(){
    eta = sqrt(n_x + lambda);
}

void Weights::setSigmaPointWeights(){
    Wm.resize(n_sigma);
    Wc.resize(n_sigma, n_sigma);
    Wc = Eigen::MatrixXd::Zero(n_sigma, n_sigma);

    Wm(0) = lambda/(n_x + lambda);
    Wc(0,0) = lambda/(n_x + lambda) + (1 - pow(alpha,2) + beta);

    for(int i = 1; i < n_sigma; i++){
        Wm(i) = 1/(2*(n_x + lambda));
        Wc(i,i) = 1/(2*(n_x + lambda));
    }
}
