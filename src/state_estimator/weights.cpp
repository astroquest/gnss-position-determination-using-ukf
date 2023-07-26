#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

#include "weights.hpp"

Weights::Weights(int n, int m, double alph, double bet, double* p, double* q, double* r){
    n_states = n;
    n_measurements = m;

    void setLambda();
    void setEta();

    setUncertaintyWeights(p, q, r);
    setSigmaPointWeights();
}

void Weights::setUncertaintyWeights(double* state_uncertainties, double* process_uncertainties, double* measurement_uncertainties){
    P = setDiagonalMatrix(state_uncertainties, n_states);
    Q = setDiagonalMatrix(process_uncertainties, n_states);
    R = setDiagonalMatrix(measurement_uncertainties, n_measurements);
}

void Weights::setSigmaPointWeights(){
    Wm.resize(2*n_states+1);
    Wc.resize(2*n_states+1);

    Wm[0] = lambda/(n_states + lambda);
    Wc[0] = lambda/(n_states + lambda) + (1 - pow(alpha,2) + beta);

    for(int i = 1; i < 2*n_states+1; i++){
        Wm[i] = 1/(2*(n_states + lambda));
        Wc[i] = 1/(2*(n_states + lambda));
    }
}

Eigen::MatrixXd Weights::setDiagonalMatrix(double* diagonal_terms, int diagonal_size){
    Eigen::MatrixXd diagonal_matrix(diagonal_size, diagonal_size);

    for(int i = 0; i < diagonal_size; i++){
        diagonal_matrix(i,i) = diagonal_terms[i];
    }

    return diagonal_matrix;
}