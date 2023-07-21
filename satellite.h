using namespace std;

class Satellite{
    public:
        Satellite(){
            orbital_radius = 25e6;
            mean_anomaly_change = sqrt(mu/pow(orbital_radius, 3));
        };

        void initialize(double M0){
            mean_anomaly = M0;

            pos_sat.push_back(orbital_radius*cos(mean_anomaly));
            pos_sat.push_back(orbital_radius*sin(mean_anomaly));
        }

        void propagateOrbit(double sampling_time){
            mean_anomaly = mean_anomaly + sampling_time*(mean_anomaly_change - earth_radial_velocity);

            pos_sat[0] = orbital_radius*cos(mean_anomaly);
            pos_sat[1] = orbital_radius*sin(mean_anomaly);
        }

        vector<double> pos_sat;

    private:
        double orbital_radius;
        double mean_anomaly;
        double mean_anomaly_change;
};
