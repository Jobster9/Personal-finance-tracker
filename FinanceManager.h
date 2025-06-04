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
    vector<Transaction> expenses;
    vector<Transaction> incomes;
};