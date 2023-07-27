#ifndef STATE_ESTIMATOR_HPP
#define STATE_ESTIMATOR_HPP

#include <Eigen/Dense>

class StateEstimator{
    public:
        StateEstimator(int, int, Eigen::VectorXd);

        void initialize(Eigen::VectorXd);
        void getSigmaPoints();
        void predict(Eigen::VectorXd);
        void getKalmanGain();
        void correct(Eigen::VectorXd);

        Eigen::VectorXd x_corr;
        Eigen::MatrixXd P_corr;
    private:
        Eigen::VectorXd getOutput(Eigen::VectorXd, Eigen::VectorXd);

        int n_x;
        int n_y;
        int n_sigma;
        double eta;
        Eigen::MatrixXd x_pred;
        Eigen::MatrixXd y_pred;
        Eigen::MatrixXd P_pred;
        Eigen::MatrixXd Q;
        Eigen::MatrixXd R;
        Eigen::MatrixXd S;
        Eigen::VectorXd Wm;
        Eigen::MatrixXd Wc;
        Eigen::MatrixXd X;
        Eigen::MatrixXd X_pred;
        Eigen::MatrixXd Y_pred;
        Eigen::MatrixXd P_y;
        Eigen::MatrixXd P_xy;
        Eigen::MatrixXd K;
};

#endif
