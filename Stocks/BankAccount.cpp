//
//  BankAccount.cpp
//  Stocks
//
//  Created by MacUser on 4/22/18.
//  Copyright © 2018 Dev. All rights reserved.
//

#include "BankAccount.hpp"
#include <iostream>

BankAccount::BankAccount(double amount) {
    this->amount = amount;
}
BankAccount::~BankAccount() {
    this->amount = 0;
    this->shares = 0;
}
double BankAccount::getAmount(){
    return this->amount;
}
void BankAccount::buyStock(double price) {
    if(this->amount >= price) {
        this->amount = this->amount - price;
        this->shares++;
    }
    else {
        std::cout << "Error, not enough money to buy" <<std::endl;
    }
}
void BankAccount::sellStock(double price) {
    if(this->shares >0) {
        this->amount = this->amount + price;
        this->shares++;
    }
    else {
        std::cout <<"Error, you own no stocks" << std::endl;
    }
}
