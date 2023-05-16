

#include "VendingMachine.h"

VendingMachine::VendingMachine(){
    string text;
    string name;
    double price;
    int quantity;
    int flag;

    file.open("uno.txt", ios::in);
    if (file.good()) {

        products = new Product[N];

        for(int i=0; i < N;i++) {

            file >> name >> price >> quantity >> flag;

            if (flag == 1) {
                quantity = 10;
                flag = 0;
            }

            products[i] = Product(name,price,quantity,flag);
        }
    }
    else{
        cout << "file is wrong" << endl;

    }

    file.close();
}
VendingMachine::~VendingMachine() {
    delete[] products;
}

void VendingMachine::save_to_file() {

    string text;
    file.open("uno.txt", ios::out);

    for (int i = 0; i < N; i++) {
        if (products[i].GetQty() == 0) {
            products[i].SetFlag();
        }
    }
    for (int i = 0; i < N; i++) {
        stringstream ss(text);
        file << products[i].GetProduct() << ' ' << products[i].GetPrice() << ' ' << products[i].GetQty() <<' ' << products[i].GetFlag() << endl;
    }
    file.close();
}

void VendingMachine::dispProduct() {
    for (int i = 0; i < N; i++)
        cout << "id:" << i + 1 << "\t" << "Product:\t" << products[i].GetProduct() << "\tavaible quantity:\t" << products[i].GetQty() << "\t" << "price:\t" << products[i].GetPrice() << " zl" << endl;
}

void VendingMachine::checkQty(int id,int qty) {

    if (products[id - 1].GetQty() < qty && qty < 0) {
        do {
            cout << "there is no such amont of product" << endl;
            cout << "-------------------------------" << endl;
            cout << "please select the proper amont" << endl;
            cin >> qty;
        } while (products[id - 1].GetQty() < qty);
    }
}
void VendingMachine::Check_id(int id_in) {

    while (id_in > N && id_in < N) {
        cout << "there is no such id of product" << endl;
        cout << "-------------------------------" << endl;
        cout << "please select the proper id" << endl;
        cin >> id_in;

    }
}
void VendingMachine::check_if_enough(int id,int qty,double *total) {

    if (*total < products[id-1].GetPrice()* qty) {
        do {
            cout << "you have not enough money" << endl;
            cout << "-------------------------------" << endl;
            cout << "please select the proper amount" << endl;
            cin >> qty;
            checkQty(id,qty);

        } while (*total < products[id-1].GetPrice()* qty);
        (*total) -= products[id-1].GetPrice()* qty;
        Bought_product[id-1] += qty;
        products[id-1].setQTY(products[id-1].GetQty() - qty);
    }
    else {
        (*total) -= products[id-1].GetPrice() * qty;
        Bought_product[id-1] += qty;
        products[id-1].setQTY(products[id-1].GetQty() - qty);
    }
}

void VendingMachine::CashInfo(){

    int inserted_qty;

    cout << "enter the amount of 5zl" << endl;
    cin >> inserted_qty;
    coins->setCoinQty(0,inserted_qty);
    cout << "enter the amount of 2zl" << endl;
    cin >> inserted_qty;
    coins->setCoinQty(1,inserted_qty);
    cout << "enter the amount of 1zl" << endl;
    cin >> inserted_qty;
    coins->setCoinQty(2,inserted_qty);
    cout << "enter the amount of 0.5zl" << endl;
    cin >> inserted_qty;
    coins->setCoinQty(3,inserted_qty);
    cout << "enter the amount of 0.2zl" << endl;
    cin >> inserted_qty;
    coins->setCoinQty(4,inserted_qty);
    cout << "enter the amount of 0.1zl" << endl;
    cin >> inserted_qty;
    coins->setCoinQty(5,inserted_qty);

}
double VendingMachine::calculateTotalInput(){
    double total_input_cash = 0;
    for (int i=0; i < 6; i++) {
        total_input_cash += coins->GetQty(i) * coins->coins_val[i];
    }
    return total_input_cash;
}

int* VendingMachine::Give_rest(double input_cash) {

    static int rest[6] = {0, 0, 0, 0, 0, 0};
    int priority = 0;
    int prior_qty = 0;
    // adding coins to general pool
    for (int i = 0; i < 6; i++) {
        coins->Cash_pool[i] += coins->GetQty(i);
    }
    input_cash = round(input_cash*100);
    // setting the priority to the coin that occurs the most
    while (input_cash > 0) {
        for (int i = 0; i < 6; i++) {
            if (input_cash >= coins->coins_val[i]*100) {
                if (coins->Cash_pool[i] > prior_qty) {
                    priority = i;
                    prior_qty = coins->Cash_pool[i];
                }
            }
        }

        for (int i = 0; i < 6; i++) {
            if (input_cash >= coins->coins_val[i]*100 && i == priority && coins->Cash_pool[i] > 0) {
                input_cash -= coins->coins_val[i]*100;
                rest[i] += 1;
                coins->Cash_pool[i] -= 1;
                goto endd;
            }
        }
        for (int i = 0; i < 6; i++) {
            if (input_cash >= coins->coins_val[i]*100 && coins->Cash_pool[i] > 0) {
                input_cash -= coins->coins_val[i]*100;
                rest[i] += 1;
                coins->Cash_pool[i] -= 1;
                goto endd;
            }
        }
        cout << "unable to give rest" << endl;
        cout << "please enter the payment deducted in cash" << endl;
        exit(0);

        endd:
        coins->save();
        cout << "";

    }

    return rest;
}
void VendingMachine::Display_bought(){
    for(int i =0; i < Bought_product.size();i++){
        if (Bought_product[i] > 0)
            cout << "you successfully bought: " << products[i].GetProduct() << " in quantity of: " << Bought_product[i]<<endl;
    }
}