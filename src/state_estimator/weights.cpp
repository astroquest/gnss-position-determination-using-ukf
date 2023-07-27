#include <iostream>
#include <cmath>
#include <Eigen/Dense>

#include "weights.hpp"

Weights::Weights(int n, int m, double alph, double bet, Eigen::VectorXd p, Eigen::VectorXd q, Eigen::VectorXd r){
    n_states = n;
    n_measurements = m;
    n_sigma = 2*n + 1;

    alpha = alph;
    beta = bet;

    setLambda();
    setEta();
    setUncertaintyWeights(p, q, r);
    setSigmaPointWeights();
}

void Weights::setEta(){
    eta = sqrt(n_states + lambda);
}

void Weights::setLambda(){
    lambda = n_states*(pow(alpha,2) - 1);
}

void Weights::setUncertaintyWeights(Eigen::VectorXd p, Eigen::VectorXd q, Eigen::VectorXd r){
    P.resize(n_states, n_states);
    Q.resize(n_states, n_states);
    R.resize(n_measurements, n_measurements);

    P = p.asDiagonal();
    Q = q.asDiagonal();
    R = r.asDiagonal();
}

void Weights::setSigmaPointWeights(){
    Wm.resize(n_sigma);
    Wc.resize(n_sigma, n_sigma);
    Wc = Eigen::MatrixXd::Zero(n_sigma, n_sigma);

    Wm(0) = lambda/(n_states + lambda);
    Wc(0,0) = lambda/(n_states + lambda) + (1 - pow(alpha,2) + beta);

    for(int i = 1; i < n_sigma; i++){
        Wm(i) = 1/(2*(n_states + lambda));
        Wc(i,i) = 1/(2*(n_states + lambda));
    }
}
