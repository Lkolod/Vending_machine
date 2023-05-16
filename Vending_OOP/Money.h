#ifndef VENDING_OOP_MONEY_H
#define VENDING_OOP_MONEY_H

#include <iostream>
#include <cmath>
#include <vector>
#include<fstream>

using namespace std;

class Money {
    private:

        int *coins_qty;
        fstream file;

    public:

        vector<double> coins_val;
        vector<int> Cash_pool;
        Money();
        ~Money();
        void setCoinQty(int,int);
        int GetQty(int);
        void setCoins();
        void save();
};


#endif //VENDING_OOP_MONEY_H
