using namespace std;

class KalmanSettings{
    public:
        KalmanSettings(){
            n = 3;
            alpha = 1e-3;
            beta = 2;
            lambda = n*(pow(alpha,2) - 1);
            eta = sqrt(n + lambda);

            Wm.resize(2*n+1);
            Wc.resize(2*n+1);
        };

        void set_weights(){
            Wm[0] = lambda/(n + lambda);
            Wc[0] = lambda/(n + lambda) + (1 - pow(alpha,2) + beta);

            for(int i = 1; i < 2*n+1; i++){
                Wm[i] = 1/(2*(n + lambda));
                Wc[i] = 1/(2*(n + lambda));
            }
        };

        double eta;
        vector<double> Wm;
        vector<double> Wc;

    private:
        int n;
        double alpha;
        double beta;
        double lambda;
};