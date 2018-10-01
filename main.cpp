//
//  main.cpp
//  MoodysPractice
//
//  Created by David Donnelly II on 10/1/18.
//  Copyright © 2018 DavidDonnellyII. All rights reserved.
//

#include "main.hpp"
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
    DataHandle data = DataHandle("Firms.txt", "Risks.txt");
    data.ReadData();
    //Create a new Simulation
    Simulation sim1{10000, 5, 1.2, 2, .01, .0005};
    Simulation sim2{10000, 10, 1.2, 2, .01, .0005};
    Simulation sim3{10000, 15, 1.2, 2, .01, .0005};
    Simulation sim4{10000, 30, 1.2, 2, .01, .0005};

    //Run MonteCarlo
    MonteCarlo monte1 = MonteCarlo(sim1, data._portfolio);
    double* results1 = monte1.Run();
    MonteCarlo monte2 = MonteCarlo(sim2, data._portfolio);
    double* results2 = monte2.Run();
    MonteCarlo monte3 = MonteCarlo(sim3, data._portfolio);
    double* results3 = monte3.Run();
    MonteCarlo monte4 = MonteCarlo(sim4, data._portfolio);
    double* results4 = monte4.Run();
    //Print results
    data.WriteData(results1, sim1.iterations, sim1.years);
    data.WriteData(results2, sim2.iterations, sim2.years);
    data.WriteData(results3, sim3.iterations, sim3.years);
    data.WriteData(results4, sim4.iterations, sim4.years);

    
    return 0;
    
}
