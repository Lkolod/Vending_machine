#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

int product_len = 5;
const int n = 5;

vector<string> Product; // ={ "twix", "bounty", "mars", "chips" ,"water" };
vector<double> Prices; // = { 3.2,3,4.2,5,2 };
vector<int> Qty;// = { 5,5,5,5,5 };
vector<int> Flag;
vector<int> Coin_qty;
vector<double> Coins;
vector<int> Bought_product = {0,0,0,0,0};


void products_init() {

    string text, name, price2, quantity2, flag2;
    fstream file;

    double price;
    int quantity;
    int flag;

    file.open("uno.txt", ios::in);
    if (file.good()) {

        while (getline(file, text)) {

            stringstream ss(text);
            getline(ss, name, ',');
            getline(ss, price2, ',');
            price = stod(price2);

            getline(ss, quantity2, ',');
            quantity = stoi(quantity2);

            getline(ss, flag2, ',');
            flag = stoi(flag2);

            if (flag == 1) {
                quantity = 10;
                flag = 0;
            }


            Product.push_back(name);
            Prices.push_back(price);
            Qty.push_back(quantity);
            Flag.push_back(flag);
        }
    }
    else{
        cout << "file is wrong" << endl;

    }

    file.close();
}

void cash_init() {

    string text,quantity,coin;
    fstream file;

    double coin2;
    int quantity2;

    if (file.good()) {
        file.open("cash.txt", ios::in);

        while (getline(file, text)) {

            stringstream ss(text);
            getline(ss, quantity, ',');
            getline(ss, coin, ',');

            quantity2 = stoi(quantity);
            coin2 = stod(coin);

            Coin_qty.push_back(quantity2);
            Coins.push_back(coin2);
        }
    }
    else{
        cout << "file is wrong" << endl;
    }
    file.close();

}
void save_cash_to_file() {

    string text;
    fstream file;
    file.open("cash.txt", ios::out);

    for (int i = 0; i < 6; i++) {
        stringstream ss(text);
        file << Coin_qty[i] << ',' << Coins[i] << endl;
    }
    file.close();

}
void save_to_file() {

    string text;
    fstream file;
    file.open("uno.txt", ios::out);

    for (int i = 0; i < n; i++) {
        stringstream ss(text);
        file << Product[i] << ',' << Prices[i] << ',' << Qty[i] <<',' << Flag[i] << endl;
    }
    file.close();
}

void dispProduct() {
    for (int i = 0; i < n; i++)
        cout << "id:" << i + 1 << "\t" << "Product:\t" << Product[i] << "\tavaible quantity:\t" << Qty[i] << "\t" << "price:\t" << Prices[i] << " zl" << endl;
}

void secret_code(int inp) {

    if (inp == 1223) {
        save_to_file();
        exit(0);
    }
}

void checkQty(int id,int qty) {

    if (Qty[id - 1] < qty && qty < 0) {
        do {
            cout << "there is no such amont of product" << endl;
            cout << "-------------------------------" << endl;
            cout << "please select the proper amont" << endl;
            cin >> qty;
            secret_code(qty);
        } while (Qty[id - 1] < qty);
    }
}
void check_if_enough(int id,int qty,double *total) {

    if (*total < Prices[id-1]* qty) {
        do {
            cout << "you have not enough money" << endl;
            cout << "-------------------------------" << endl;
            cout << "please select the proper amount" << endl;
            cin >> qty;
            checkQty(id,qty);
            secret_code(qty);
        } while (*total < Prices[id-1]* qty);
        (*total) -= Prices[id-1]* qty;
        Bought_product[id-1] += qty;
        Qty[id-1] = Qty[id-1] - qty;
    }
    else {
        (*total) -= Prices[id-1]* qty;
        Bought_product[id-1] += qty;
        Qty[id-1] = Qty[id-1] - qty;
    }
}

void Check_id(int *id_in) {

    while (*id_in > product_len) {
        cout << "there is no such id of product" << endl;
        cout << "-------------------------------" << endl;
        cout << "please select the proper id" << endl;
        cin >> *id_in;
        secret_code(*id_in);
    }
}

void product_flag() {

    for (int i = 0; i < n; i++) {
        if (Qty[i] == 0) {
            Flag[i] = 1;
        }
    }
}

void cash_info(int *sth){

    cout << "enter the amount of 5zl" << endl;
    cin >> sth[0];
    cout << "enter the amount of 2zl" << endl;
    cin >> sth[1];
    cout << "enter the amount of 1zl" << endl;
    cin >> sth[2];
    cout << "enter the amount of 0.5zl" << endl;
    cin >> sth[3];
    cout << "enter the amount of 0.2zl" << endl;
    cin >> sth[4];
    cout << "enter the amount of 0.1zl" << endl;
    cin >> sth[5];
}

int* Give_rest(double input_cash,int *coins) {

    static int rest[6] = {0, 0, 0, 0, 0, 0};
    int priority = 0;
    int prior_qty = 0;
    // adding coins to general pool
    for (int i = 0; i < 6; i++) {
        Coin_qty[i] += coins[i];
    }
    input_cash = round(input_cash*100);
    // setting the priority to the coin that occurs the most
    while (input_cash > 0) {
        for (int i = 0; i < 6; i++) {
            if (input_cash >= Coins[i]*100) {
                if (Coin_qty[i] > prior_qty) {
                    priority = i;
                    prior_qty = Coin_qty[i];
                }
            }
        }

        for (int i = 0; i < 6; i++) {
            if (input_cash >= Coins[i]*100 && i == priority && Coin_qty[i] > 0) {
                input_cash -= Coins[i]*100;
                rest[i] += 1;
                Coin_qty[i] -= 1;
                goto endd;
            }
        }
        for (int i = 0; i < 6; i++) {
            if (input_cash >= Coins[i]*100 && Coin_qty[i] > 0) {
                input_cash -= Coins[i]*100;
                rest[i] += 1;
                Coin_qty[i] -= 1;
                goto endd;
            }
        }
        cout << "unable to give rest" << endl;
        cout << "please enter the payment deducted in cash" << endl;
        exit(0);

        endd:
        cout << "";

    }

    return rest;
}

void Display_bought(){
    for(int i =0; i < Bought_product.size();i++){
        if (Bought_product[i] > 0)
            cout << "you successfully bought: " << Product[i] << " in quantity of: " << Bought_product[i]<<endl;
    }
}

void modify_coins() {
    for (int i = 0; i < 6; i++) {
        cout << "Set no of " << Coins[i] << " PLN coins: ";
        cin >> Coin_qty[i];
    }
    cout << "Changing the cash pool completed" << endl;

}

//change secret code into while statement

int main()
{
    int salacted_id;
    int salacted_qty;
    char choice;

    int CASH_QTY[6];
    double COINS[6] = {5,2,1,0.5,0.2,0.1};
    double total_input_cash = 0;

    products_init();
    cash_init();
    cash_info(CASH_QTY);

    for (int i=0; i < 6; i++) {
        total_input_cash += CASH_QTY[i] * COINS[i];
    }


    do
    {
        dispProduct();
        cout << "Select id" << endl;
        cin >> salacted_id;
        secret_code(salacted_id);
        Check_id(&salacted_id);
        cout << "You selected id:\t" << salacted_id << endl;

        cout << "Select quantity" << endl;
        cin >> salacted_qty;
        secret_code(salacted_qty);
        cout << "You selected quantity:\t" << salacted_qty << endl;


        checkQty(salacted_id, salacted_qty);
        if (salacted_qty > 0) {
            check_if_enough(salacted_id, salacted_qty, &total_input_cash);
        }

        dispProduct();
        cout << "you have: " << total_input_cash << "zl" <<endl;

        cout << "\n\n-->Do you want to continue (y/n)? ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    Display_bought();

    int *rest_sum = Give_rest(total_input_cash, CASH_QTY);

    cout << "your rest here:" << endl;
    for(int i =0;i<6;i++){
        cout << rest_sum[i] <<"\t" <<COINS[i] <<"zl"<< endl;
    }

    product_flag();
    save_cash_to_file();
    save_to_file();

    return 0;
}



