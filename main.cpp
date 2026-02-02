/*
Pseudocode:

Date.cpp:
- Stores and manages a date (month, day, year, hour)
- Can set and get each value
- Can print the date in readable format

Account.cpp:
- Base class for bank accounts
- Handles deposits, withdrawals, and transaction history
- Tracks a unique account number and total number of accounts
- Stores owner name, balance, and transactions
- Records transactions with dynamic memory
- Can print account info and full transaction history

RegularAccount.cpp:
- Inherits from Account
- Adds a label when printing to identify it as a regular account

PremiumAccount.cpp:
- Inherits from Account
- Enforces a minimum balance requirement for withdrawals
- Adds a label when printing to identify it as a premium account

main.cpp:
- Lets the user create up to 5 accounts (regular or premium)
- Supports deposits, withdrawals, and printing info for all accounts
- Uses a menu loop to interact with the user
- Cleans up dynamic memory at the end
*/
#include <iostream>
#include <iomanip>
#include "Account.h"
#include "RegularAccount.h"
#include "PremiumAccount.h"
#include "Date.h"
using namespace std;

const int MAX_NUM_ACCOUNTS = 5;

// Helper function to find account by account number
int findAccount(Account* accounts[], int accNum) {
    for (int i = 0; i < MAX_NUM_ACCOUNTS; ++i) {
        if (accounts[i] != nullptr && accounts[i]->getAccountNumber() == accNum)
            return i;
    }
    return -1;
}

int main() {
    Account* accountArray[MAX_NUM_ACCOUNTS] = {nullptr}; // Holds up to 5 accounts
    int choice;

    do {
        // Display menu options
        cout << "\n1->Create regular accnt, 2->Create premium accnt, 3->Deposit to accnt\n"
             << "4->Withdraw from accnt, 5->Print info accnts, 6->Quit\n";
        cin >> choice;

        // Handle account creation
        if (choice == 1 || choice == 2) {
            int index = -1;
            // Find an empty slot
            for (int i = 0; i < MAX_NUM_ACCOUNTS; ++i) {
                if (accountArray[i] == nullptr) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                cout << "Max number of accounts reached, cannot add a new account\n";
                continue;
            }

            string name;
            int mm, dd, yyyy, hh;
            double amount;

            // Collect account creation data
            cout << "Enter owner's name: ";
            cin >> name;
            cout << "Enter date, in the mm/dd/yyyy/hh format: ";
            scanf("%d/%d/%d/%d", &mm, &dd, &yyyy, &hh);
            cout << "Enter amount: ";
            cin >> amount;

            Date date;
            date.set(mm, dd, yyyy, hh);

            // Create appropriate account type
            if (choice == 1) {
                if (amount <= 0) {
                    cout << "Amount cannot be negative, account creation not executed\n";
                    continue;
                }
                accountArray[index] = new RegularAccount(name, amount, date);
                cout << "Account created: \n";
                accountArray[index]->print();
            } else {
                if(amount < 0) {
                   cout << "Amount cannot be negative, account creation not executed\n";
                   continue;
                }
                else if (amount < PremiumAccount::getMinBalance()) {
                    cout << "Insufficient amount, you need at least 1000.00 Galactic units to open a premium account\n";
                    continue;
                }
                accountArray[index] = new PremiumAccount(name, amount, date);
                cout << "Account created: \n";
                accountArray[index]->print();
            }

        // Handle deposit or withdrawal
        } else if (choice == 3 || choice == 4) {
            int accNum;
            cout << "Enter account number: ";
            cin >> accNum;

            int idx = findAccount(accountArray, accNum);
            if (idx == -1) {
                cout << "No such account\n";
                continue;
            }

            int mm, dd, yyyy, hh;
            double amount;

            cout << "Enter date, in the mm/dd/yyyy/hh format: ";
            scanf("%d/%d/%d/%d", &mm, &dd, &yyyy, &hh);
            cout << "Enter amount: ";
            cin >> amount;

            Date date;
            date.set(mm, dd, yyyy, hh);

            if (amount <= 0) {
                cout << "Amount cannot be negative, " << (choice == 3 ? "deposit" : "withdraw") << " not executed\n";
                continue;
            }

            bool success = false;
            if (choice == 3) {
                success = accountArray[idx]->deposit(amount, date);
                if (success) {
                    cout << "Deposit executed: \n";
                }
            } else {
                success = accountArray[idx]->withdraw(amount, date);
                if (success) {
                    cout << "Withdraw executed: \n";
                } else {
                    cout << "Insufficient balance, withdrawal not executed\n";
                    continue;
                }
            }
            accountArray[idx]->print();

        // Handle printing all accounts and their transactions
        } else if (choice == 5) {
            cout << "Accounts\n========\n";
            for (int i = 0; i < MAX_NUM_ACCOUNTS; ++i) {
                if (accountArray[i] != nullptr) {
                    accountArray[i]->print();
                    accountArray[i]->printTransactions();
                }
            }
        }
    } while (choice != 6); // Exit on choice 6

    // Free memory
    for (int i = 0; i < MAX_NUM_ACCOUNTS; ++i) {
        delete accountArray[i];
    }

    return 0;
}