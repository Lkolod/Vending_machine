
#include "Money.h"


Money::Money() {
    string text;

    double coin;
    int quantity;

    if (file.good()) {
        file.open("cash.txt", ios::in);

        while (!file.eof()) {
            file >> quantity >> coin;
            Cash_pool.push_back(quantity);
            coins_val.push_back(coin);
        }
    }
    else{
        cout << "file is wrong" << endl;
    }
    file.close();
    coins_qty = new int[6];
}

void Money::setCoinQty(int id,int new_qty) {
    coins_qty[id] = new_qty;
}

Money::~Money() {
    delete [] coins_qty;
}

int Money::GetQty(int id) {
    return coins_qty[id];
}

void Money::setCoins(){
    for(int i=0; i < Cash_pool.size(); i++) {
        cout<<"Set no of "<<coins_val[i]<<" PLN coins: ";
        cin>>Cash_pool[i];
    }
    save();
    cout<<"Changing the cash pool completed"<< endl;
}

void Money::save(){
    string text;
    file.open("cash.txt", ios::out);

    for (int i = 0; i < 6; i++) {
        file << Cash_pool[i] << ' ' << coins_val[i] << endl;
    }
    file.close();

}
