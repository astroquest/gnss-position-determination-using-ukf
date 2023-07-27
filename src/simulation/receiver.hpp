#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <random>

class Receiver{
    public:
        Receiver();

        void initialize(double, double, double, double, double, double);
        void propagateLocation(double);
        void propagateClockBias(double);

        Eigen::Vector3d position;
        double clock_bias;

    private:
        double stdev_position;
        double stdev_clock_bias;
        Eigen::Vector3d random_walk_position;
        double random_walk_clock_bias;

        std::default_random_engine gen;
};

#endif
