//
//  Stock.cpp
//  Stocks
//
//  Created by MacUser on 5/4/18.
//  Copyright © 2018 Dev. All rights reserved.
//

#include "Stock.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <limits>
#include <string>


using namespace std;

Stock::Stock(){
}

Stock::Stock(string FileName,int numOfDays) {
    int column = 0;
    ifstream data;
    data.open(FileName);
    while(data.good()) {
        string line;
        if(column != 29) {
            getline(data,line,',');
        }
        else
            getline(data,line,'\n');
        double num = stod(line);
        stockData[row][column] = num;
        if(column != 29) {
            column++;
        }
        else {
            column = 0;
            row++;
        }
        
    }
    data.close();
    initialize(FileName,numOfDays);
}
Stock::~Stock(){

}
bool Stock::initialize(string FileName,int numOfDays) {
    
}

