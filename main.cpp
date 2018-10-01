//
//  main.cpp
//  MoodysPractice
//
//  Created by David Donnelly II on 9/28/18.
//  Copyright © 2018 DavidDonnellyII. All rights reserved.
//

#include <iostream>
#include"DataHandle.hpp"
#include"Modeling.hpp"
#include<iomanip>

using namespace std;

int main(int argc, const char * argv[]) {
    //Create DataHandle and read file
    DataHandle data = DataHandle("Firms.txt");
    data.ReadData();
    //Create a new Simulation
    Simulation sim1{1000, 10, 1.2, 2, .01, .0005};
    
    //Run MonteCarlo
    MonteCarlo monte1 = MonteCarlo(sim1, data._portfolio);
    double* results = monte1.Run();
    //Print results
    for(int ii = 0; ii < data._portfolio.size(); ii++){
        cout << data._portfolio[ii].FirmName << "    " << setprecision(4) << results[ii]*100  << " %" << endl;
    }
    return 0;
    
}
