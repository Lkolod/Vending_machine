#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
#include "Product.h"
#include "Money.h"

#ifndef VENDING_OOP_VENDINGMACHINE_H
#define VENDING_OOP_VENDINGMACHINE_H


class VendingMachine {
    private:
        int N = 5;
        Product* products;
        Money* coins = new Money;
        fstream file;
        vector<int> Bought_product = {0,0,0,0,0};

public:
    VendingMachine();
    ~VendingMachine();
    void save_to_file();
    void dispProduct();
    void checkQty(int, int);
    void Check_id(int);
    void CashInfo();
    void check_if_enough(int,int,double*);
    int* Give_rest(double);
    void Display_bought();
    double calculateTotalInput();
};


#endif //VENDING_OOP_VENDINGMACHINE_H
