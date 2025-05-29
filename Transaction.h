#pragma once
#include <string>
#include <iostream>


using namespace std;

enum class Category { 
    //Expense categories
    FOOD, TRANSPORT, ENTERTAINMENT, UTILITIES, SHOPPING,
    //Income categories  
    SALARY, FREELANCE, INVESTMENT, GIFT, BONUS,
    //Common
    OTHER 
};

class Transaction {
protected:
    double amount;
    string description;
    Category category;
    string date;
    
public:
    Transaction(double amount, const string& description, Category category, const string& date): 
    amount(amount), description(description), category(category), date(date) {}
    
    virtual ~Transaction() = default;
    virtual void display() const = 0;

    double getAmount() const { return amount; };
    const string& getDescription() const { return description; };
    Category getCategory() const { return category; };
    const string& getDate() const { return date; };
};