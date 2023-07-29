#ifndef WEIGHTS_HPP
#define WEIGHTS_HPP

#include <vector>
#include <Eigen/Dense>

class Weights{
    public:
        Weights(int, int, double, double);

        void setEta();
        void setLambda();
        void setSigmaPointWeights();

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
