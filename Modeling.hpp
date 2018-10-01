//
//  Modeling.hpp
//  MoodysPractice
//
//  Created by David Donnelly II on 9/29/18.
//  Copyright © 2018 DavidDonnellyII. All rights reserved.
//

#ifndef Modeling_hpp
#define Modeling_hpp
#include <vector>
#include <stdio.h>
#include "DataHandle.hpp"
#include <random>
#include <sstream>

struct Simulation{
    int iterations;
    int years;
    double startMean;
    double MeanVar;
    double euro_diff_mean;
    double euro_diff_var;
};

class MonteCarlo{
public:
    MonteCarlo(Simulation, vector<Firm>);
    Simulation Simu;
    double* Run();
    vector<Firm> FirmsList;
    double MertonCalc(Firm, int, int);
private:
    default_random_engine Generator;
    double* American_GDP_Generator();
    double* Euro_GDP_Generator(double*);
    double* SingleIteration();
    double d2Calc(Firm, int, int);
    void SimSumm();
    double phi(double);
};

#endif /* Modeling_hpp */
