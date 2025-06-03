#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <optional>

using std::string, std::chrono::system_clock, std::cout, std::cin, std::endl, std::optional;

enum class TransactionType { INCOME, EXPENSE };
enum class  IncomeCategory { SALARY, FREELANCE, INVESTMENT, GIFT, BONUS,OTHER };
enum class ExpenseCategory { FOOD, TRANSPORT, ENTERTAINMENT, UTILITIES, SHOPPING,OTHER };
enum class Frequency { DAILY, WEEKLY, MONTHLY, QUARTERLY, YEARLY };

struct RecurrenceInfo 
{
    Frequency frequency;
    system_clock::time_point startDate;
    optional<system_clock::time_point> endDate;  // Optional end date
    
    RecurrenceInfo(Frequency freq, const system_clock::time_point& start, 
                   const optional<system_clock::time_point>& end = std::nullopt)
        : frequency(freq), startDate(start), endDate(end) {}
    
    bool hasEndDate() const { return endDate.has_value(); }
    
    bool isActiveOn(const system_clock::time_point& date) const 
    {
        if (date < startDate) return false;
        if (endDate.has_value() && date > endDate.value()) return false;
        return true;
    } 

    string frequencyToString() const 
    {
        switch (frequency) {
            case Frequency::DAILY: return "Daily";
            case Frequency::WEEKLY: return "Weekly";
            case Frequency::MONTHLY: return "Monthly";
            case Frequency::QUARTERLY: return "Quarterly";
            case Frequency::YEARLY: return "Yearly";
            default: return "Unknown";
        }
    }
};

class Transaction
{    
public:
    //One time transactions
    Transaction(double amount, const string& description, const system_clock::time_point& date, IncomeCategory cat)
        : amount(amount), description(description), transactionDate(date),
        type(TransactionType::INCOME), incomeCat(cat), recurrence(std::nullopt) {}

    Transaction(double amount, const string& description, const system_clock::time_point& date, ExpenseCategory cat)
        : amount(amount), description(description), transactionDate(date),
          type(TransactionType::EXPENSE), expenseCat(cat), recurrence(std::nullopt) {}

    //Recurring transactions
    Transaction(double amount, const string& description, IncomeCategory cat, const RecurrenceInfo& recurInfo)
        : amount(amount), description(description), transactionDate(recurInfo.startDate),
          type(TransactionType::INCOME), incomeCat(cat), recurrence(recurInfo) {}

    Transaction(double amount, const string& description, ExpenseCategory cat,const RecurrenceInfo& recurInfo)
        : amount(amount), description(description), transactionDate(recurInfo.startDate),
          type(TransactionType::EXPENSE), expenseCat(cat), recurrence(recurInfo) {}


    ~Transaction() = default;
    void displayCompact() const;
    void displayDetailed() const;

    double getAmount() const { return amount; };
    const string& getDescription() const { return description; };

    system_clock::time_point getDate() const { return transactionDate; }
    bool isRecurring() const { return recurrence.has_value(); }
    optional<RecurrenceInfo> getRecurrence() const { return recurrence; }
    optional<system_clock::time_point> getNextOccurrence() const;

    TransactionType getType() const { return type; }
    ExpenseCategory getExpenseCategory() const;
    IncomeCategory getIncomeCategory() const;


private:
    double amount;
    string description;

    system_clock::time_point transactionDate;
    optional<RecurrenceInfo> recurrence;

    TransactionType type;
    union
    {
        ExpenseCategory expenseCat;
        IncomeCategory incomeCat;
    };

    string categoryToString() const;
    string frequencyToString() const;
    system_clock::time_point calculateNextDate(const system_clock::time_point& lastDate, Frequency freq, 
                                               const system_clock::time_point& fromDate) const;

};