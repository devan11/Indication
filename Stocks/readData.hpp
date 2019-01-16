//
//  readData.hpp
//  Stocks
//
//  Created by Devan on 12/14/18.
//  Copyright © 2018 Dev. All rights reserved.
//

#ifndef readData_hpp
#define readData_hpp
#define numberOfStocks 30
#define numberOfDays 1260

#include <stdio.h>



#endif /* readData_hpp */

struct stockData{
    double stockInfo[numberOfDays][numberOfStocks];
};

stockData readAllData();





