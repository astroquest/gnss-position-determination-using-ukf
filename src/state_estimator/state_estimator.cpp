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
    Y_pred.resize(n_x, n_sigma);
    P_y.resize(n_y, n_y);
    P_xy.resize(n_x, n_y);

    x_corr = x0;

    Eigen::VectorXd p(4);  // improve this
    p << pow(earth_radius,2), 10, 10, 100;
    Eigen::VectorXd q(4);
    q << 1e-9, 1e-9, 1e-9, 1e-9;
    Eigen::VectorXd r(4);
    r << 1e-10, 1e-10, 1e-10, 1e-10;

    Weights weights(n_x, n_y, p, q, r);
    P_corr = weights.P;
    Q = weights.Q;
    R = weights.R;
    Wm = weights.Wm;
    Wc = weights.Wc;
    eta = weights.eta;
}

void StateEstimator::getSigmaPoints(){
    S = P_corr.llt().matrixL(); // TODO account for P not being positive definite

    X.col(0) = x_corr;
    for(int i = 1; i <= n_x; i++){
        X.col(i) = x_corr + eta*S.col(i-1);
        X.col(i+n_x) = x_corr - eta*S.col(i-1);
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
    Eigen::MatrixXd x_pred_repl = x_pred.replicate(1,n_sigma); // TODO move declaration to .hpp
    Eigen::MatrixXd y_pred_repl = y_pred.replicate(1,n_sigma);

    P_pred = (X_pred - x_pred_repl)*Wc*(X_pred - x_pred_repl).transpose() + Q;
    P_y = (Y_pred - y_pred_repl)*Wc*(Y_pred - y_pred_repl).transpose() + R;
    P_xy = (X_pred - x_pred_repl)*Wc*(Y_pred - y_pred_repl).transpose();

    K = P_xy*P_y.inverse(); // TODO acount for inverse not existing
}

void StateEstimator::correct(Eigen::VectorXd y){
    x_corr = x_pred + K*(y - y_pred);
    P_corr = P_pred - K*P_y*K.transpose();
}

Eigen::VectorXd StateEstimator::getOutput(Eigen::VectorXd x, Eigen::VectorXd u){
    Eigen::Vector4d y; // TODO need to allocate size dynamically

    y(0) = sqrt(pow(x(0) - u(0), 2) + pow(x(1) - u(1), 2) + pow(x(2), 2)) + x(3);  // TODO needs improvement
    y(1) = sqrt(pow(x(0) - u(2), 2) + pow(x(1) - u(3), 2) + pow(x(2), 2)) + x(3);
    y(2) = sqrt(pow(x(0) - u(4), 2) + pow(x(1) - u(5), 2) + pow(x(2), 2)) + x(3);
    y(3) = sqrt(pow(x(0) - u(6), 2) + pow(x(1) - u(7), 2) + pow(x(2), 2)) + x(3);

    return y;
}