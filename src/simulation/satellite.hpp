#ifndef SATELLITE_HPP
#define SATELLITE_HPP

class Satellite{
    public:
        Satellite(double = 25e6, double = 0);

        void initialize(double);
        void propagateOrbit(double);

        Eigen::Vector2d position;

        double orbital_radius;
    private:
        double mean_anomaly;
        double mean_anomaly_change;
};

#endif
