#ifndef SIMULATION_HPP
#define SIMULATION_HPP

class Simulation{
    public:
        Simulation(double, double);

        void initialize();
        void run();

        Eigen::VectorXd time;
        Eigen::MatrixXd states_rec;
        Eigen::MatrixXd states_sat_1;
        Eigen::MatrixXd states_sat_2;
        Eigen::MatrixXd states_sat_3;
        Eigen::MatrixXd states_sat_4;
        Eigen::MatrixXd ranges;

        int num_samples;
        
    private:
        double getPseudorange(Eigen::Vector2d, Eigen::Vector2d, double);

        Receiver receiver;
        Satellite sat_1;
        Satellite sat_2;
        Satellite sat_3;
        Satellite sat_4;

        double sim_time;
        double sampling_time;
};

#endif
