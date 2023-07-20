#include <vector>
#include <cmath>

using namespace std;

class Satellite{
    public:
        Satellite(double r){
            sampling_time = 10;
            orbital_radius = r;
            mean_anomaly_change = sqrt(mu/pow(orbital_radius, 3));
        };

        void setInitialConditions(double M0){
            time.push_back(0);
            mean_anomaly.push_back(M0);
            x_sat.push_back(orbital_radius*cos(M0));
            y_sat.push_back(orbital_radius*sin(M0));
        }

        void propagateOrbit(double sim_time){
            num_samples = sim_time/sampling_time;

            for(int i = 0; i < num_samples; i++){
                double time_next = time[i] + sampling_time;
                double mean_anomaly_next = mean_anomaly[i] + sampling_time*(mean_anomaly_change - earth_radial_velocity);
                double x_sat_next = orbital_radius*cos(mean_anomaly_next);
                double y_sat_next = orbital_radius*sin(mean_anomaly_next);
                double range = computeRange()

                time.push_back(time_next);
                mean_anomaly.push_back(mean_anomaly_next);
                x_sat.push_back(x_sat_next);
                y_sat.push_back(y_sat_next);
            }
        }

        double computeRange(double x_rec, double y_rec, double x_sat, double y_sat){
            return sqrt(pow(x_rec - x_sat, 2) + pow(y_rec - y_sat, 2)) + clock_bias_rec
        }

    private:
        int num_samples;
        double orbital_radius;
        double sampling_time;
        double mean_anomaly_change;

        vector<double> time;
        vector<double> mean_anomaly;
        vector<double> x_sat;
        vector<double> y_sat;
};