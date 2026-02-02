// Implements RegularAccount with basic behavior inherited from Account
#include "RegularAccount.h"
#include <iostream>
using namespace std;

// Constructor just uses the base class constructor
RegularAccount::RegularAccount(string nam, double amnt, Date d) : Account(nam, amnt, d) {}

// Print function with account type prefix
void RegularAccount::print() const {
    cout << "Regular account, ";
    this->Account::print();
}
