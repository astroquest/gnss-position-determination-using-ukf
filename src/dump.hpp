#ifndef DUMP_HPP
#define DUMP_HPP

void simDump(std::string file_name, Eigen::VectorXd time, Eigen::MatrixXd input, Eigen::MatrixXd output){
    std::ofstream dump;
    dump.open(file_name);
    dump << "t (s)" << ","
            << "x_sat_1 (m)" << "," << "y_sat_1 (m)" << "," << "R_1 (m)" << ","
            << "x_sat_2 (m)" << "," << "y_sat_2 (m)" << "," << "R_2 (m)" << ","
            << "x_sat_3 (m)" << "," << "y_sat_3 (m)" << "," << "R_3 (m)" << ","
            << "x_sat_4 (m)" << "," << "y_sat_4 (m)" << "," << "R_4 (m)" << std::endl;

    for(int i = 0; i < time.rows(); i++){
        dump << std::setprecision(15) <<  time(i) << ","
                << input(i,0) << "," << input(i,1) << "," << output(i,0) << ","
                << input(i,2) << "," << input(i,3) << "," << output(i,1) << ","
                << input(i,4) << "," << input(i,5) << "," << output(i,2) << ","
                << input(i,6) << "," << input(i,7) << "," << output(i,3) << std::endl;
    }
    dump.close();
}

void stateEstimationDump(std::string file_name, Eigen::VectorXd time, Eigen::MatrixXd baseline, Eigen::MatrixXd estimates){
    std::ofstream dump;
    dump.open(file_name);
    dump << "t (s)" << ","
            << "x_rec_baseline (m)" << "," << "y_rec_baseline (m)" <<  ","
            << "clock_bias_baseline (m)" << ","
            << "x_rec (m)" << "," << "y_rec (m)"  << ","
            << "clock_bias (m)" << std::endl;

    for(int i = 0; i < time.rows(); i++){
        dump << std::setprecision(15) << time(i) << ","
                << baseline(i,0) << "," << baseline(i,1) << ","
                << baseline(i,2) << ","
                << estimates(i,0) << "," << estimates(i,1) << ","
                << estimates(i,2) << std::endl;               
    }
    dump.close();
}

#endif
