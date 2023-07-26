#ifndef SIMULATION_HPP
#define SIMULATION_HPP

class Simulation{
    public:
        Simulation(double = 3600, double = 10);

        void initialize();
        void run();
        void dump(std::string);

    private:
        double getPseudorange(double, double, double, double, double);

        Receiver receiver;
        Satellite satellite_1;
        Satellite satellite_2;
        Satellite satellite_3;
        Satellite satellite_4;

        double sim_time;
        double sampling_time;
        int num_samples;

        std::vector<double> time;
        std::vector<double> x_rec;
        std::vector<double> y_rec;
        std::vector<double> clock_bias_rec;

        std::vector<double> x_sat_1;
        std::vector<double> y_sat_1;
        std::vector<double> range_1;

        std::vector<double> x_sat_2;
        std::vector<double> y_sat_2;
        std::vector<double> range_2;

        std::vector<double> x_sat_3;
        std::vector<double> y_sat_3;
        std::vector<double> range_3;
        
        std::vector<double> x_sat_4;
        std::vector<double> y_sat_4;
        std::vector<double> range_4;
};

#endif
