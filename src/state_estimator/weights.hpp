#ifndef WEIGHTS_HPP
#define WEIGHTS_HPP

#include <vector>
#include <Eigen/Dense>

class Weights{
    public:
        Weights(int, int, Eigen::VectorXd, Eigen::VectorXd, Eigen::VectorXd);

        void setEta();
        void setLambda();
        void setUncertaintyWeights(Eigen::VectorXd, Eigen::VectorXd, Eigen::VectorXd);
        void setSigmaPointWeights();

        Eigen::MatrixXd P;
        Eigen::MatrixXd Q;
        Eigen::MatrixXd R;

        Eigen::VectorXd Wm;
        Eigen::MatrixXd Wc;

        double eta;

    private:
        int n_x;
        int n_y;
        int n_sigma;
        double alpha;
        double beta;
        double lambda;
};

#endif
