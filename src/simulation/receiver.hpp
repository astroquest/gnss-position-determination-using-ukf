#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <random>

class Receiver{
    public:
        Receiver(double = c*1e-5, double = earth_radius, double = 0, double = c*1e-8, double = 0.1);

        void initialize(double, double, double);
        void propagateLocation(double);
        void propagateClockBias(double);

        std::vector<double> position;
        double clock_bias;

    private:
        double stdev_clock_bias;
        double stdev_pos_rec;
        std::vector<double> random_walk_pos_rec;
        double random_walk_clock_bias;

        std::default_random_engine gen;
};

#endif
