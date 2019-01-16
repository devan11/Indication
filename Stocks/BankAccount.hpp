//
//  BankAccount.hpp
//  Stocks
//
//  Created by MacUser on 4/22/18.
//  Copyright © 2018 Dev. All rights reserved.
//

#ifndef BankAccount_hpp
#define BankAccount_hpp

#include <stdio.h>

class BankAccount {
    
public:
    BankAccount(double amount);
    ~BankAccount();
    void buyStock(double price);
    void sellStock(double price);
    double getAmount();
private:
    double amount;
    int shares;
};

#endif /* BankAccount_hpp */
