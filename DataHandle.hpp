//
//  DataHandle.hpp
//  MoodysPractice
//
//  Created by David Donnelly II on 9/28/18.
//  Copyright © 2018 DavidDonnellyII. All rights reserved.
//

#ifndef DataHandle_hpp
#define DataHandle_hpp
#include <string>
#include <cstring>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Firm{
public:
    //Constructor
    Firm(string, double, double, double, double, double, double);
    //Inputed Data
    string FirmName;
    double Euro_weight;
    double Euro_coefficient;
    double American_weight;
    double American_coefficient;
    double CurrentValue;
    double DefaultValue;
    //Calculated Metrics
    double mean;
    double std_deviation;
    void meanCalc(double, double);
    void DeviationCalc(double, double);
    
};

class DataHandle{
public:
    DataHandle(string, string);
    string in_file;
    string out_file;
    vector<Firm> _portfolio;
    void ReadData();
    void WriteData(double*, int, int);
};
#endif /* DataHandle_hpp */
