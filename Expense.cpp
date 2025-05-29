#include "Expense.h"
Expense::Expense(double amount, const string& description, Category category, const string& date)
: Transaction (amount,description,category,date){};

void Expense::display() const {
    cout << "Description: " << getDescription() << "\n"
         << "Amount: £" << getAmount() << "\n"  
         << "Category: " << categoryToString() << "\n"
         << "Date: " << getDate() << "\n\n";
}

string Expense::categoryToString() const {
    switch (getCategory()) {
        case Category::FOOD: return "Food";
        case Category::TRANSPORT: return "Transport";
        case Category::ENTERTAINMENT: return "Entertainment";
        case Category::UTILITIES: return "Utilities";
        case Category::SHOPPING: return "Shopping";
        case Category::OTHER: return "Other";
        default: return "Unknown";
    }
}