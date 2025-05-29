#pragma once
#include <string>
#include <iostream>
#include "Transaction.h"


using namespace std;

class Income : public Transaction 
{
public:
    Income(double amount, const string& description, Category category, const string& date);
    void display() const override;

private:
    string categoryToString() const;
};
