#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Expense.h"
#include "Income.h"

using namespace std;

class FinanceManager 
{
public:
    FinanceManager();


private:
    vector<Expense> expenses;
    vector<Income> incomes;
};