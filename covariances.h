#include <Eigen/Dense>

using Eigen::MatrixXd;

class Covariances{
    public:
        Covariances(){
            n = 3;
            m = 4;

            P.resize(n,n);
            P(0,0) = 10;
            P(1,1) = 10;
            P(2,2) = 10;

            Q.resize(n,n);
            Q(0,0) = 10;
            Q(1,1) = 10;
            Q(2,2) = 10;

            R.resize(m,m);
            R(0,0) = 10;
            R(1,1) = 10;
            R(2,2) = 10;
            R(3,3) = 10;
        }

    MatrixXd P;
    MatrixXd Q;
    MatrixXd R;

    private:
        int n;
        int m;
};