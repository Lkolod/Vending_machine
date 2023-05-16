#include "Product.h"

Product::Product() {
    product = 'no_item';
    price = 0;
    Qty = 0;
    Flag = 0;
}

Product::Product(string NAME, double PRICE, int QUANTITY,int FLAG) {
    product = NAME;
    price = PRICE;
    Qty = QUANTITY;
    Flag = FLAG;
}

Product::~Product() {};

string Product::GetProduct() {
    return product;
}
double Product::GetPrice() {
    return price;
}
int Product::GetQty() {
    return Qty;
}
int Product::GetFlag() {
    return Flag;
}

void Product::SetFlag(){
    Flag = 1;
}
void Product::setProduct(string new_product) {
    product = new_product;
}

void Product::setPrice(double new_price) {
    price = new_price;
}

void Product::setQTY(int new_qty) {
    Qty = new_qty;
}
