#include <iostream>
#include "VendingMachine.h"

int main() {
    int salacted_id;
    int salacted_qty;
    char choice;
    double total_input_cash = 0;
    double COINS[6] = {5,2,1,0.5,0.2,0.1};

    VendingMachine machine;

    machine.CashInfo();
    total_input_cash = machine.calculateTotalInput();
    cout << "you have: " << total_input_cash << "zl" <<endl;

    do {
        machine.dispProduct();
        cout << "Select id" << endl;
        cin >> salacted_id;
        cout << "You selected id:\t" << salacted_id << endl;
        machine.Check_id(salacted_id);

        cout << "Select quantity" << endl;
        cin >> salacted_qty;
        cout << "You selected quantity:\t" << salacted_qty << endl;
        machine.checkQty(salacted_id,salacted_qty);

        if (salacted_qty > 0) {
            machine.check_if_enough(salacted_id, salacted_qty, &total_input_cash);
        }
        machine.dispProduct();
        cout << "\n\n-->Do you want to continue (y/n)? ";
        cin >> choice;

    } while((choice == 'y' || choice== 'Y') && (salacted_id != 1223 || salacted_qty != 1223));

    machine.Display_bought();

    int *rest = machine.Give_rest(total_input_cash);
    cout << "your rest here:" << endl;
    for(int i =0;i<6;i++){
        cout << rest[i] <<"\t" <<COINS[i] <<"zl"<< endl;
    }
    machine.save_to_file();
}
