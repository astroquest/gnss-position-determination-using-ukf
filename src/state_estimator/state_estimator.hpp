#ifndef STATE_ESTIMATOR_HPP
#define STATE_ESTIMATOR_HPP

#include <vector>
#include <Eigen/Dense>

class StateEstimator{
    public:
        StateEstimator(int, Eigen::VectorXd, Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd, Eigen::VectorXd, Eigen::VectorXd);

        void initialize(double, Eigen::MatrixXd);
        void getSigmaPoints(double, Eigen::VectorXd, Eigen::MatrixXd);
        void predict();
        void getKalmanGain();
        void correct();

        Eigen::VectorXd x_corr;
        Eigen::MatrixXd P_corr;
    private:
        Eigen::VectorXd getOutput(Eigen::VectorXd, Eigen::VectorXd);

        int n_x;
        int n_sigma;
        Eigen::MatrixXd x_pred;
        Eigen::MatrixXd y_pred;
        Eigen::MatrixXd P_pred;
        Eigen::MatrixXd Q;
        Eigen::MatrixXd R;
        Eigen::MatrixXd S;
        Eigen::MatrixXd X;
        Eigen::MatrixXd X_next;
        Eigen::MatrixXd Y_next;
};

#endif