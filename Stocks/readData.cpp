//
//  readData.cpp
//  Stocks
//
//  Created by Devan on 12/14/18.
//  Copyright © 2018 Dev. All rights reserved.
//

#include "readData.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

stockData readAllData() {
    stockData data;
    int row =0;
    int column = 0;
    
    ifstream dataStream;
    dataStream.open("/Users/dev/Desktop/c++/Lab1/Stocks/data/stockProject.csv");
    while(dataStream.good()) {
        string line;
        if(column != 29) {
            getline(dataStream,line,',');
        }
        else
            getline(dataStream,line,'\n');
        double num = stod(line);
        data.stockInfo[row][column] = num;
        if(column != 29) {
            column++;
        }
        else {
            column = 0;
            row++;
        }
        
    }
    dataStream.close();
    
    
    
    return data;
}
