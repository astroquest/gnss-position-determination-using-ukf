using namespace std;

class Receiver{
    public:
        Receiver(){
            stdev_clock_bias = c*1e-8;
            stdev_pos_rec = .1;
        }

        void initialize(double init_clock_bias, double init_x_pos, double init_y_pos){
            clock_bias = init_clock_bias; //c*1e-5

            pos_rec.push_back(init_x_pos);
            pos_rec.push_back(init_y_pos);

            random_walk_pos_rec.push_back(0);
            random_walk_pos_rec.push_back(0);
        }

        void propagateLocation(double sampling_time){
            normal_distribution<double> norm_dist_pos_rec(0,stdev_pos_rec);

            pos_rec[0] = pos_rec[0] + sampling_time*norm_dist_pos_rec(gen);
            pos_rec[1] = pos_rec[1] + sampling_time*norm_dist_pos_rec(gen);
        }

        void propagateClockBias(double sampling_time){
            normal_distribution<double> norm_dist_clock_bias(0,stdev_clock_bias);

            clock_bias = clock_bias + sampling_time*norm_dist_clock_bias(gen);
        }

        vector<double> pos_rec;
        double clock_bias;

    private:
        double stdev_clock_bias;
        double stdev_pos_rec;
        vector<double> random_walk_pos_rec;
        double random_walk_clock_bias;

        default_random_engine gen;
};