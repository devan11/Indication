//
//  Stock.hpp
//  Stocks
//
//  Created by MacUser on 5/4/18.
//  Copyright © 2018 Dev. All rights reserved.
//

#ifndef Stock_hpp
#define Stock_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Stock {
    
public:
    Stock();
    Stock(string FileName, int numOfDays);
    ~Stock();
    bool initialize(string FileName,int numOfDays);
    
private:
    string startDate;
    double open[5033];
    double high[5033];
    double low[5033];
    double close[5033];
};
#endif /* Stock_hpp */
