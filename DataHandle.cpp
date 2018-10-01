//
//  DataHandle.cpp
//  MoodysPractice
//
//  Created by David Donnelly II on 9/28/18.
//  Copyright © 2018 DavidDonnellyII. All rights reserved.
//

#include "DataHandle.hpp"
using namespace std;
#include <string>
#include <cstring>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "math.h"
/*
      ****************************************************************************************************
                                                DataHandle
      ****************************************************************************************************
 */

DataHandle::DataHandle(string file){
    filename = file;
}
void DataHandle::ReadData(){
    ifstream stream {filename};
    if(stream.fail()){
        throw runtime_error("File failed to connect");
    }
    string name;
    double ameriWeight, ameriCoeff, euroWeight, euroCoeff, prince, defa;
    while(stream >> name >>ameriWeight >> ameriCoeff >> euroWeight >> euroCoeff >> prince >> defa){
        _portfolio.push_back(Firm(name, ameriWeight, ameriCoeff, euroWeight, euroCoeff, prince, defa));
    }

    
};
/*
      ****************************************************************************************************
                                                    Firm
      ****************************************************************************************************
 */
Firm::Firm(string name, double Aw, double Ac, double Ew, double Ec, double prince, double defa){
    FirmName = name;
    Euro_coefficient = Ec;
    Euro_weight = Ew;
    American_coefficient = Ac;
    American_weight = Aw;
    CurrentValue = prince;
    DefaultValue = defa;
    //Set other values to 0
    mean = 0;
    std_deviation = 0;
    
}
void Firm::meanCalc(double American_gdp, double Euro_gdp){
    if(American_gdp > 0){
        mean = American_coefficient*American_weight * (sqrt(American_gdp) - .1875/sqrt(pow(American_gdp,3)));
        mean += Euro_weight*Euro_coefficient * (sqrt(Euro_gdp) - (.1875/sqrt(pow(American_gdp,3))) - .1);
    }
    else{
        mean = -American_coefficient*American_weight * (sqrt(abs(American_gdp)) - .1875/sqrt(pow(abs(American_gdp),3)));
        mean -= Euro_weight*Euro_coefficient * (sqrt(abs(American_gdp)) - (.1875/sqrt(pow(abs(American_gdp),3))) - .1);
    }
}

void Firm::DeviationCalc(double American_gdp, double Euro_gdp){
    std_deviation = pow(American_coefficient*American_weight,2) * abs(American_gdp);
    std_deviation += pow(Euro_weight*Euro_coefficient, 2) * abs(American_gdp);
    std_deviation -= .04;
    double hold = pow(mean,2);
    std_deviation += pow(mean, 2);
    if(std_deviation < 0){
        cout << "Problem" << endl;
    }
    std_deviation = sqrt(std_deviation);
}
