#include <iostream>
#include <cmath>
#include <Eigen/Dense>

#include "../constants.hpp"
#include "state_estimator.hpp"
#include "weights.hpp"

StateEstimator::StateEstimator(int n_states, int n_measurements, Eigen::VectorXd x0){
    n_x = n_states;
    n_y = n_measurements;
    n_sigma = 2*n_x + 1;

    initialize(x0);
}

void StateEstimator::initialize(Eigen::VectorXd x0){
    X.resize(n_x, n_sigma);
    X_pred.resize(n_x, n_sigma);
    Y_pred.resize(n_y, n_sigma);
    P_y.resize(n_y, n_y);
    P_xy.resize(n_x, n_y);

    x_corr = x0;

    Eigen::Vector3d p;  // TODO improve this and change location
    Eigen::Vector3d q;
    Eigen::Vector4d r;
    p << pow(earth_radius,2), pow(earth_radius,2), 10000;
    q << 0.1, 0.1, 0.1;
    r << 1, 1, 1, 1;

    Weights weights(n_x, n_y, p, q, r);
    P_corr = weights.P;
    Q = weights.Q;
    R = weights.R;
    Wm = weights.Wm;
    Wc = weights.Wc;
    eta = weights.eta;
}

void StateEstimator::getSigmaPoints(){
    S = P_corr.llt().matrixL();

    X.col(0) = x_corr;
    for(int i = 0; i < n_x; i++){
        X.col(i+1) = x_corr + eta*S.col(i);
        X.col(i+n_x+1) = x_corr - eta*S.col(i);
    }
}

void StateEstimator::predict(Eigen::VectorXd u){
    for(int i = 0; i < n_sigma; i++){
        X_pred.col(i) = X.col(i);
        Y_pred.col(i) = getOutput(X_pred.col(i), u);
    }

    x_pred = X_pred*Wm;
    y_pred = Y_pred*Wm;
}

void StateEstimator::getKalmanGain(){
    x_pred_repl = x_pred.replicate(1,n_sigma);
    y_pred_repl = y_pred.replicate(1,n_sigma);

    P_pred = (X_pred - x_pred_repl)*Wc*(X_pred - x_pred_repl).transpose() + Q;
    P_y = (Y_pred - y_pred_repl)*Wc*(Y_pred - y_pred_repl).transpose() + R;
    P_xy = (X_pred - x_pred_repl)*Wc*(Y_pred - y_pred_repl).transpose();

    K = P_xy*P_y.inverse();
}

void StateEstimator::correct(Eigen::VectorXd y){
    x_corr = x_pred + K*(y - y_pred);
    P_corr = P_pred - K*P_y*K.transpose();
}

Eigen::VectorXd StateEstimator::getOutput(Eigen::VectorXd x, Eigen::VectorXd u){
    y_est << sqrt(pow(x(0) - u(0), 2) + pow(x(1) - u(1), 2)) + x(2),
            sqrt(pow(x(0) - u(2), 2) + pow(x(1) - u(3), 2)) + x(2),
            sqrt(pow(x(0) - u(4), 2) + pow(x(1) - u(5), 2)) + x(2),
            sqrt(pow(x(0) - u(6), 2) + pow(x(1) - u(7), 2)) + x(2);

    return y_est;
}
