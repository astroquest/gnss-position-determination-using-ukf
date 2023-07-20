#include <iostream>
#include <Eigen/Dense>

#include "constants.h"
#include "satellite.h"
#include "kalman_settings.h"
#include "covariances.h"

using namespace std;

int main(){
    double orbital_radius = 25e6;

    Satellite satellite_1(orbital_radius);
    satellite_1.setInitialConditions(0);
    satellite_1.propagateOrbit(3600);


    KalmanSettings kalman_settings;
    Covariances covariances;

    return 0;
}
