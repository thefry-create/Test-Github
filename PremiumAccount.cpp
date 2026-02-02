// Implements PremiumAccount with an enforced minimum balance for withdrawals
#include "PremiumAccount.h"
#include <iostream>
using namespace std;

// Constant minimum balance for premium accounts
const double PremiumAccount::MIN_BALANCE = 1000.0;

// Constructor uses base class constructor
PremiumAccount::PremiumAccount(string nam, double amnt, Date d) : Account(nam, amnt, d) {}

// Only allows withdrawal if resulting balance doesn't drop below the minimum
bool PremiumAccount::withdraw(double amnt, Date d) {
    if (balance - amnt >= MIN_BALANCE) {
        balance -= amnt;
        Transaction t;
        t.date = d;
        t.transactionType = 2;
        t.amount = amnt;
        recordTransaction(t);
        return true;
    }
    return false;
}

// Getter for the minimum balance
double PremiumAccount::getMinBalance() {
    return MIN_BALANCE;
}

// Print function with account type prefix
void PremiumAccount::print() const {
    cout << "Premium account, ";
    this->Account::print();
}
