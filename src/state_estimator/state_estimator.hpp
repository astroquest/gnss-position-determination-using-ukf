#ifndef STATE_ESTIMATOR_HPP
#define STATE_ESTIMATOR_HPP

#include <Eigen/Dense>

class StateEstimator{
    public:
        StateEstimator(int, Eigen::VectorXd, Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd, Eigen::VectorXd, Eigen::VectorXd);

        void initialize(double, Eigen::MatrixXd);
        void getSigmaPoints(double, Eigen::VectorXd, Eigen::MatrixXd);
        void predict(Eigen::VectorXd u);
        void getKalmanGain();
        void correct(double);

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
        Eigen::VectorXd Wm;
        Eigen::MatrixXd Wc;
        Eigen::MatrixXd X;
        Eigen::MatrixXd X_next;
        Eigen::MatrixXd Y_next;
        Eigen::MatrixXd P_y;
        Eigen::MatrixXd P_xy;
        Eigen::MatrixXd K;
};

#endif
