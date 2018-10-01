//
//  Modeling.cpp
//  MoodysPractice
//
//  Created by David Donnelly II on 9/29/18.
//  Copyright © 2018 DavidDonnellyII. All rights reserved.
//

#include "Modeling.hpp"
#include "DataHandle.hpp"
#include <vector>
#include<math.h>
#include<random>
using namespace std;

/*
      ****************************************************************************************************
                                        Constructor and Helper
      ****************************************************************************************************
 */
MonteCarlo::MonteCarlo(Simulation sim, vector<Firm> firms){
    //Set public class members
    Simu = sim;
    FirmsList = firms;
    SimSumm();
}

void MonteCarlo::SimSumm(){
    cout << "         Begining MonteCarlo Simulation" << "\n" << endl;
    cout << "Number of firms:      " << FirmsList.size() << "\n" << "Iterations:           " << Simu.iterations << endl;
    cout << "Years per iteration:  " << Simu.years << endl << endl;
}

/*
    ****************************************************************************************************
                                                Merton Model
    ****************************************************************************************************
 */
double MonteCarlo::phi(double x)
{
    // constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;
    
    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x)/sqrt(2.0);
    
    // A&S formula 7.1.26
    double t = 1.0/(1.0 + p*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);
    
    return 0.5*(1.0 + sign*y);
}

double MonteCarlo::d2Calc(Firm f, int T, int t){
    double hold = f.mean;
    //cout << hold << endl;
    return (log(f.CurrentValue / f.DefaultValue) + (T-t)*((f.mean * .01) - pow((f.std_deviation * .01),2)/2)) / f.std_deviation * sqrt(T-t);
}

double MonteCarlo::MertonCalc(Firm f, int T, int t){
    return phi(-d2Calc(f, T, t));
}

/*
      ****************************************************************************************************
                                                GDP Generators
      ****************************************************************************************************
 */
double* MonteCarlo::American_GDP_Generator(){
    double* GDPArr = new double[Simu.years];
    GDPArr[0] = Simu.startMean;
    double mean = Simu.startMean;
    double std = Simu.MeanVar;
    for(int ii = 1; ii < Simu.years; ii++){
        //Randomly from the American GDP distribution
        default_random_engine generator;
        normal_distribution<double> tempDist(mean,std);
        double sampleRate = tempDist(generator);
        //Copy the gdp rate into the array
        GDPArr[ii] = sampleRate;
        //Adjust to new mean
        mean = sampleRate;
    }
    return GDPArr;
}

double* MonteCarlo::Euro_GDP_Generator(double* AmericanArr){
    double* GDPArr = new double[Simu.years];
    default_random_engine generator;
    normal_distribution<double> tempDist(Simu.euro_diff_mean,Simu.euro_diff_var);
    for(int ii = 0; ii < Simu.years; ii++){
        //Sample for the scale
        double sampleRate = tempDist(generator);
        //Store the Euro gdp rate calculated from the american one
        GDPArr[ii] = AmericanArr[ii] - sampleRate;
    }
    return GDPArr;
}

/*
     ****************************************************************************************************
                                            Simulation Engine
      ****************************************************************************************************
 */
double* MonteCarlo::SingleIteration(){
    double* riskArray = new double[FirmsList.size()];
    //First generate the GDP reuslts
    double* American_GDPs = American_GDP_Generator();
    double* Euro_GDPs = Euro_GDP_Generator(American_GDPs);
    for(int tt = 0; tt < Simu.years; tt++){
        for(int ff = 0; ff < FirmsList.size(); ff++){
            //Update Firm's growth and volatility
            FirmsList[ff].meanCalc(American_GDPs[tt], Euro_GDPs[tt]);
            FirmsList[ff].DeviationCalc(American_GDPs[tt], Euro_GDPs[tt]);
            //Calculate risk for firm
            riskArray[ff] += MertonCalc(FirmsList[ff], Simu.years, tt);
        }
    }
    for(int ii = 0; ii < FirmsList.size(); ii++){
        riskArray[ii] /= Simu.years;
    }
    return riskArray;
}

double* MonteCarlo::Run(){
    //Array to hold total cumulative averages
    double* RiskAverages = new double[FirmsList.size()];
    //Run the MonteCarlo for each iteration
    for(int ii = 0; ii < Simu.iterations; ii++){
        //Use helper function for each iteration
        double* holdArr = SingleIteration();
        //Total the averages for each firm
        for(int jj = 0; jj < FirmsList.size(); jj ++){
            double hol = RiskAverages[jj];
            RiskAverages[jj] += holdArr[jj];
        }
    }
    //Calculate average at end
    for(int kk = 0; kk < FirmsList.size(); kk++){
        RiskAverages[kk] = RiskAverages[kk] / Simu.iterations;
    }
    return RiskAverages;
}
