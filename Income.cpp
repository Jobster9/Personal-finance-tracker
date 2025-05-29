#include "Income.h"
Income::Income(double amount, const string& description, Category category, const string& date)
: Transaction (amount,description,category,date){};

void Income::display() const 
{
    cout << "Description: " << getDescription() <<
    "Amount: £" << getAmount() <<
    "Category: " << categoryToString <<
    "Date: " << getDate() << endl;
}

string Income::categoryToString() const {
    switch (getCategory()) {
        case Category::SALARY: return "Salary";
        case Category::FREELANCE: return "Freelance";
        case Category::INVESTMENT: return "Investment";
        case Category::GIFT: return "Gift";
        case Category::BONUS: return "Bonus";
        case Category::OTHER: return "Other";
        default: return "Unknown";
    }
}