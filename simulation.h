using namespace std;

class Simulation{
    public:
        Simulation(){
            sim_time = 60*10000;
            sampling_time = 10;
            num_samples = sim_time/sampling_time;
        }

        void initialize(){
            receiver.initialize(c, earth_radius, 0);
            satellite_1.initialize(0);
            satellite_2.initialize(10*pi/180);
            satellite_3.initialize(20*pi/180);
            satellite_4.initialize(30*pi/180);

            time.push_back(0);

            x_rec.push_back(receiver.pos_rec[0]);
            y_rec.push_back(receiver.pos_rec[1]);
            clock_bias_rec.push_back(receiver.clock_bias);

            x_sat_1.push_back(satellite_1.pos_sat[0]);
            y_sat_1.push_back(satellite_1.pos_sat[1]);
            range_1.push_back(computeRange(receiver.pos_rec[0], receiver.pos_rec[1], satellite_1.pos_sat[0], satellite_1.pos_sat[1], receiver.clock_bias));  // <- use pointer here?
        
            x_sat_2.push_back(satellite_2.pos_sat[0]);
            y_sat_2.push_back(satellite_2.pos_sat[1]);
            range_2.push_back(computeRange(receiver.pos_rec[0], receiver.pos_rec[1], satellite_2.pos_sat[0], satellite_2.pos_sat[1], receiver.clock_bias));

            x_sat_3.push_back(satellite_3.pos_sat[0]);
            y_sat_3.push_back(satellite_3.pos_sat[1]);
            range_3.push_back(computeRange(receiver.pos_rec[0], receiver.pos_rec[1], satellite_3.pos_sat[0], satellite_3.pos_sat[1], receiver.clock_bias));

            x_sat_4.push_back(satellite_4.pos_sat[0]);
            y_sat_4.push_back(satellite_4.pos_sat[1]);
            range_4.push_back(computeRange(receiver.pos_rec[0], receiver.pos_rec[1], satellite_4.pos_sat[0], satellite_4.pos_sat[1], receiver.clock_bias));
        }

        void run(){
            num_samples = sim_time/sampling_time;

            for(int i = 0; i < num_samples; i++){
                double time_next = time[i] + sampling_time;
                
                receiver.propagateLocation(sampling_time);
                receiver.propagateClockBias(sampling_time);

                satellite_1.propagateOrbit(sampling_time);
                satellite_2.propagateOrbit(sampling_time);
                satellite_3.propagateOrbit(sampling_time);
                satellite_4.propagateOrbit(sampling_time);

                time.push_back(time_next);
                x_rec.push_back(receiver.pos_rec[0]);
                y_rec.push_back(receiver.pos_rec[1]);
                clock_bias_rec.push_back(receiver.clock_bias);

                x_sat_1.push_back(satellite_1.pos_sat[0]);
                y_sat_1.push_back(satellite_1.pos_sat[1]);
                range_1.push_back(computeRange(receiver.pos_rec[0], receiver.pos_rec[1], satellite_1.pos_sat[0], satellite_1.pos_sat[1], receiver.clock_bias));  // <- use pointer here?

                x_sat_2.push_back(satellite_2.pos_sat[0]);
                y_sat_2.push_back(satellite_2.pos_sat[1]);
                range_2.push_back(computeRange(receiver.pos_rec[0], receiver.pos_rec[1], satellite_2.pos_sat[0], satellite_2.pos_sat[1], receiver.clock_bias));

                x_sat_3.push_back(satellite_3.pos_sat[0]);
                y_sat_3.push_back(satellite_3.pos_sat[1]);
                range_3.push_back(computeRange(receiver.pos_rec[0], receiver.pos_rec[1], satellite_3.pos_sat[0], satellite_3.pos_sat[1], receiver.clock_bias));

                x_sat_4.push_back(satellite_4.pos_sat[0]);
                y_sat_4.push_back(satellite_4.pos_sat[1]);
                range_4.push_back(computeRange(receiver.pos_rec[0], receiver.pos_rec[1], satellite_4.pos_sat[0], satellite_4.pos_sat[1], receiver.clock_bias));
            }
        }

        void dumpToFile(string file_name){
            ofstream dump;
            dump.open(file_name);
            dump << "t (s)" << "," << "x_rec (m)" << "," << "y_rec (m)" << "," << "ctr (m)" << "," 
                    << "x_sat_1 (m)" << "," << "y_sat_1 (m)" << "," << "R_1 (m)" << ","
                    << "x_sat_2 (m)" << "," << "y_sat_2 (m)" << "," <<  "R_2 (m)" << ","
                    << "x_sat_3 (m)" << "," << "y_sat_3 (m)" << "," <<  "R_3 (m)" << ","
                    << "x_sat_4 (m)" << "," << "y_sat_4 (m)" << "," <<  "R_4 (m)" << endl;

            for (int i = 0; i < time.size(); i++){
                dump << setprecision(4) << time[i] << "," << x_rec[i] << "," << y_rec[i] << "," << clock_bias_rec[i] << ","
                    << x_sat_1[i] << "," << y_sat_1[i] << "," << range_1[i] << ","
                    << x_sat_2[i] << "," << y_sat_2[i] << "," << range_2[i] << ","
                    << x_sat_3[i] << "," << y_sat_3[i] << "," << range_3[i] << ","
                    << x_sat_4[i] << "," << y_sat_4[i] << "," << range_4[i] << endl;
            }
            dump.close();
        }

    private:
        double computeRange(double x_rec, double y_rec, double x_sat, double y_sat, double clock_bias){
            return sqrt(pow(x_rec - x_sat, 2) + pow(y_rec - y_sat, 2)) + clock_bias;
        }

        Receiver receiver;
        Satellite satellite_1;
        Satellite satellite_2;
        Satellite satellite_3;
        Satellite satellite_4;

        double sim_time;
        double sampling_time;
        int num_samples;

        vector<double> time;
        vector<double> x_rec;
        vector<double> y_rec;
        vector<double> clock_bias_rec;

        vector<double> x_sat_1;
        vector<double> y_sat_1;
        vector<double> range_1;

        vector<double> x_sat_2;
        vector<double> y_sat_2;
        vector<double> range_2;

        vector<double> x_sat_3;
        vector<double> y_sat_3;
        vector<double> range_3;
        
        vector<double> x_sat_4;
        vector<double> y_sat_4;
        vector<double> range_4;
};