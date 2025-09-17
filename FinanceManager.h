#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Transaction.h"

using namespace std;

class FinanceManager
{
public:
    FinanceManager();

private:
    vector<Transaction> transactions;
};

// Is separate transaction vectors needed? no, condition check by trans type + easy saving & loading.
// Saving & Loading functionality as part of financeManager?
// what else should financeManager actually be responsible for besides storing a single transactions vector?
// higher level display methods i.e. display expenses(){ if(type=ex){dotypedisplay}}, displaybydaterange,
// calculate net balance, do this by week, month, year dependant on income?
// store savings / current account balance section (separate accounts class? interest rate storage)
// calculate savings projection based on recurring contributions + interest rate + current value (advanced + inflation??)

// Transfers between accounts should be classed as their own form of transaction,
// not income / expense + current account location & target account. Dependancy issues? transaction needs access to account class, FM needs access to both.
