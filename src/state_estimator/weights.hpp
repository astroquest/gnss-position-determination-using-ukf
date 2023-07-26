#ifndef WEIGHTS_HPP
#define WEIGHTS_HPP

#include <vector>
#include <Eigen/Dense>

class Weights{
    public:
        Weights(int, int, double, double, double*, double*, double*);

        void setUncertaintyWeights(double*, double*, double*);
        void setSigmaPointWeights();

        Eigen::MatrixXd P;
        Eigen::MatrixXd Q;
        Eigen::MatrixXd R;

        std::vector<double> Wm;
        std::vector<double> Wc;

        double eta;

    private:
        Eigen::MatrixXd setDiagonalMatrix(double*, int);

        int n_states;
        int n_measurements;
        double alpha;
        double beta;
        double lambda;
};

#endif
