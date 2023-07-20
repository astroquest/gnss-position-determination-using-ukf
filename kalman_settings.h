using namespace std;

class KalmanSettings{
    public:
        void set_constants(int n, double alpha){
            beta = 2;
            lambda = n*(pow(alpha,2) - 1);
            eta = sqrt(n + lambda);
        };

        void set_weights(int n, double alpha, double beta, double lambda){

        };

        double eta;
        double Wm[1];
        double Wc[1];

    private:
        double beta;
        double lambda;
};