//
//  main.cpp
//  Stocks
//
//  Created by MacUser on 4/21/18.
//  Copyright © 2018 Dev. All rights reserved.
//


#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <limits>
#include "BankAccount.hpp"
#include "readData.hpp"


using namespace std;
typedef std::numeric_limits< double > dbl;



int main(int argc, const char * argv[]) {

    

    stockData allData;
    allData = readAllData();
    
   /* ifstream data;
    data.open("/Users/dev/Desktop/c++/Lab1/Stocks/data/stockProject.csv");
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
    */
    
    
    double sumFor26 = 0.0;
    double sumFor12 = 0.0;
    double sumFor9 = 0.0;
    double TwelveEMAprevday = 0.0;
    double TwelveEMAarray[1260];
    double TwentySixDayEMAprevday = 0.0;
    double TwentySixDayEMAarray[1260];
    
    double NineEMAprevday = 0.0;
    double NineEMAarray[1260];
    
    
    double TwelveDayMultiplier = 2.0/13.0;
    double TwentySixDayMultiplier = 2.0/27.0;
    
    double NineDayMultiplier = 2.0/10.0;
    
    
    double EMAinfo[1260][30]; //12day ema -26day ema;
    double Signal[1260][30];
    int day = 0;
    int stock = 0;
    while(day < 1234) {
        sumFor26 = 0;
        sumFor12 = 0;
        
        for(int i = day + 14; i < day+26; i++) {
            sumFor12 = sumFor12 +  allData.stockInfo[i][stock];
        }
    
        double TwelveDaySMA = sumFor12/12.0;
    
        for(int i = day; i<day+26; i++) {
            sumFor26 = sumFor26 + allData.stockInfo[i][stock];
        }
        
        double TwentySixDaySMA = sumFor26/26.0;
        
        if(day == 0){
            TwelveEMAprevday = TwelveDaySMA;
            TwentySixDayEMAprevday = TwentySixDaySMA;
        }
        
        
        double TwelveEMA = ((allData.stockInfo[day+25][stock] - TwelveEMAprevday)*TwelveDayMultiplier) + TwelveEMAprevday;
        double TwentySixEMA = ((allData.stockInfo[day+25][stock] - TwentySixDayEMAprevday)*TwentySixDayMultiplier) + TwentySixDayEMAprevday;
        
        
        
        TwelveEMAarray[day] = TwelveEMA;
        TwentySixDayEMAarray[day] = TwentySixEMA;
        
        
        
        TwelveEMAprevday = TwelveEMA;
        TwelveEMA = 0;
        
        TwentySixDayEMAprevday = TwentySixEMA;
        TwentySixEMA= 0;
       
        if(day!=1233) {
            day++; }
        else if(day == 1233 && stock!=30) {
            day = 0;
            for(int i =0; i < 1234; i++) {
                EMAinfo[i][stock] = (TwelveEMAarray[i] - TwentySixDayEMAarray[i]);
            }
            stock++;
        }
        else
            day++;
    }
    
    day = 0;
    stock = 0;
    double profitSum = 0.0;
    double investmentSum = 0.0;
    while(day < 1234) {
        sumFor9 = 0;
        for(int i = day +17; i < day + 26;i++) {
            sumFor9 = sumFor9 + EMAinfo[i][stock];
        }
        
        double NineDaySMA = sumFor9/9.0;
        
        if(day == 0) {
            NineEMAprevday = NineDaySMA;
        }
        
        double NineEMA = ((EMAinfo[day+25][stock] - NineEMAprevday)*NineDayMultiplier) + NineEMAprevday;
        
        NineEMAarray[day] = NineEMA;
        
        
        
        
        NineEMAprevday = NineEMA;
        NineEMA = 0;
        if(day!=1233) {
            day++; }
        else if(day == 1233 && stock!=30) {
            day = 0;
            for(int i =0; i < 1234; i++) {
                Signal[i][stock] = NineEMAarray[i];
            }
            stock++;
        }
        else
            day++;
    }
    
    
    ofstream outputData;
    outputData.open("EMSDifference.csv");
    int i = 0;
    int stockNum = 0;
    while( !(stockNum == 29 && i == 1233) ) {
        outputData<< Signal[i][stockNum];
        if(stockNum!=29) {
            outputData<< ',';
            stockNum++;
        }
        else {
           
            outputData<< '\n';
            stockNum =0;
            i++;
        }
    }
    
    if(i == 1233 && stockNum == 29) {
        outputData<< Signal[i][stockNum];
        outputData<< '\n';
    }
    outputData.close();
    
    cout<<"done" <<endl;

    day =0;
    stock = 0;
    
    while(stock < 30) {
        bool MadeInitialInvestment = false;
        double initialInvestment = 0;
        BankAccount bank(100000);
        bool ownsStock = false;
        int numberOfStocksToBuy = 0;
        if(EMAinfo[day][stock] > 0) {
             numberOfStocksToBuy = 10000/allData.stockInfo[day+26][stock];
            for(int i = 0; i < numberOfStocksToBuy; i++ ) {
                bank.buyStock(allData.stockInfo[day+26][stock]);
            }
            initialInvestment =allData.stockInfo[day+26][stock] * numberOfStocksToBuy;
            ownsStock = true;
            MadeInitialInvestment = true;
        }
        day++;
        
        while (day < 1234) {
            if(ownsStock) {
                if(EMAinfo[day][stock] < 0) {
            for(int i = 0; i < numberOfStocksToBuy; i++ ) {
                bank.sellStock(allData.stockInfo[day+26][stock]);
            }
                ownsStock = false;
            }
        }
        else {
            if(EMAinfo[day][stock] > 0) {
                for(int i = 0; i < numberOfStocksToBuy; i++ ) {
                bank.buyStock(allData.stockInfo[day+26][stock]);
                }
                ownsStock = true;
                if(!MadeInitialInvestment) {
                    initialInvestment = allData.stockInfo[day+26][stock] * numberOfStocksToBuy;
                    MadeInitialInvestment = true;
                }
            }
        }
        if(day ==1233 && ownsStock) {
            for(int i = 0; i < numberOfStocksToBuy; i++ ) {
            bank.sellStock(allData.stockInfo[day+26][stock]);
            }
        }
        day++;
    }

        
    double profit = bank.getAmount() - 100000;
        profitSum = profitSum + profit;
        investmentSum = initialInvestment + investmentSum;
    double percentReturn = 100 * (profit/initialInvestment);
        
        cout<< "This stock has given a " << percentReturn << "% return in 5 years, with a initial investment of $" <<initialInvestment << " and a profit of $" <<profit << endl;
        stock++;
        day = 0;
    }
    cout<< "in total, we invested $" << investmentSum << "and made $" << profitSum <<" which is a " << (profitSum/investmentSum) *100 <<"% return in 5 years"<<endl;
 
    
 return 0;
    
}

