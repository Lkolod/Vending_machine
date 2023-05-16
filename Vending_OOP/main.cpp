#include <iostream>
#include "VendingMachine.h"

int main() {
    int SelectedID;
    int Selected_QTY;
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
        cin >> SelectedID;
        cout << "You selected id:\t" << SelectedID << endl;
        machine.Check_id(SelectedID);

        cout << "Select quantity" << endl;
        cin >> Selected_QTY;
        cout << "You selected quantity:\t" << Selected_QTY << endl;
        machine.checkQty(SelectedID, Selected_QTY);

        if (Selected_QTY > 0) {
            machine.check_if_enough(SelectedID, Selected_QTY, &total_input_cash);
        }
        machine.dispProduct();
        cout << "\n\n-->Do you want to continue (y/n)? ";
        cin >> choice;

    } while((choice == 'y' || choice== 'Y') && (SelectedID != 1223 || Selected_QTY != 1223));

    machine.Display_bought();

    int *rest = machine.Give_rest(total_input_cash);
    cout << "your rest here:" << endl;
    for(int i =0;i<6;i++){
        cout << rest[i] <<"\t" <<COINS[i] <<"zl"<< endl;
    }
    machine.save_to_file();
}
