
#ifndef VENDING_OOP_PRODUCT_H
#define VENDING_OOP_PRODUCT_H

#include <vector>
#include <string>

using namespace std;

class Product {
    private:

        string product;
        double price;
        int Qty;
        int Flag;

    public:
        Product();
        Product(string,double,int,int);
        ~Product();
        string GetProduct();
        double GetPrice();
        int GetQty();
        void setProduct(string);
        void setPrice(double);
        void setQTY(int);
        int GetFlag();
        void SetFlag();
};



#endif //VENDING_OOP_PRODUCT_H
