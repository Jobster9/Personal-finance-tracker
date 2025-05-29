#pragma once
#include <string>
#include <iostream>

using namespace std;

class Expense 
{
public:
    Expense(double amount,const string& description, Category catergory,const string& date);

    void display() const;
    double getAmount() const;
    const string& getDescription() const;
    Category getCategory() const;

private:
    string description;
    Category category; 
    double amount;
    string date;
};

enum class Category { 
        FOOD, 
        TRANSPORT, 
        ENTERTAINMENT, 
        UTILITIES, 
        OTHER 
    };
