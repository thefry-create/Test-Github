// Implements shared functionality for both Regular and Premium accounts
#include "Account.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Static variable to track number of created accounts
int Account::numberAccounts = 0;

// Constructor initializes account data and logs the creation transaction
Account::Account(string nam, double bal, Date d) {
    ownerName = nam;
    balance = bal;
    accountNumber = numberAccounts + 1000;
    numberAccounts++;
    
    transactionHistory = nullptr;
    numberTransactions = 0;
    
    Transaction t;
    t.date = d;
    t.transactionType = 0; // Creation
    t.amount = bal;
    recordTransaction(t);
}

// Withdraws money from account if sufficient balance exists
bool Account::withdraw(double amnt, Date d) {
    if (amnt <= balance) {
        balance -= amnt;
        Transaction t;
        t.date = d;
        t.transactionType = 2; // Withdrawal
        t.amount = amnt;
        recordTransaction(t);
        return true;
    }
    return false;
}

// Deposits money into account if amount is valid
bool Account::deposit(double amnt, Date d) {
    if (amnt > 0) {
        balance += amnt;
        Transaction t;
        t.date = d;
        t.transactionType = 1; // Deposit
        t.amount = amnt;
        recordTransaction(t);
        return true;
    }
    return false;
}

// Simple getter functions
int Account::getAccountNumber() const { return accountNumber; }
double Account::getBalance() const { return balance; }
int Account::getNumberAccounts() { return numberAccounts; }

// Prints account summary
void Account::print() const {
    cout << fixed << setprecision(2);
    cout << "#: " << accountNumber << ", Name: " << ownerName
         << ", Balance: " << balance << " Galactic units" << endl;
}

// Handles dynamic memory for adding a new transaction
void Account::recordTransaction(Transaction t) {
    Transaction* newHistory = new Transaction[numberTransactions + 1];
    for (int i = 0; i < numberTransactions; i++) {
        newHistory[i] = transactionHistory[i];
    }
    newHistory[numberTransactions] = t;
    delete[] transactionHistory;
    transactionHistory = newHistory;
    numberTransactions++;
}

// Prints the transaction history and running balance
void Account::printTransactions() const {
    cout << "Transaction history:\n-------------------\n";
    double runningBalance = 0;
    for (int i = 0; i < numberTransactions; ++i) {
        const Transaction& t = transactionHistory[i];
        cout << "Date: ";
        t.date.print();
        cout << ", Amount: " << fixed << setprecision(2) << t.amount;

        string typeStr;
        switch (t.transactionType) {
            case 0: typeStr = "Creation"; runningBalance = t.amount; break;
            case 1: typeStr = "Deposit"; runningBalance += t.amount; break;
            case 2: typeStr = "Withdrawal"; runningBalance -= t.amount; break;
        }

        cout << ", type: " << typeStr << ", New balance: " << fixed << setprecision(2) << runningBalance << endl;
    }
}
