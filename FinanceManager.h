#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Transaction.h"
#include "Account.h"

using namespace std;

class FinanceManager
{
public:
    FinanceManager();

    void addTransaction(const Transaction &transaction);

    void addAccount(const Account &account);
    Account &getAccount(const string &name);

    void transfer(const string &fromAccountName, const string &toAccountName, double amount);

private:
    vector<Account> accounts;
    vector<Transaction> transactions;
};
