#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "FinanceManager.h"
#include "Transaction.h"

using namespace std;
using namespace std::chrono;

int main()
{

#ifdef _WIN32
    system("chcp 65001 > nul"); // Set UTF-8 encoding on Windows
#endif

    cout << "=== Personal Finance Manager Demo ===" << endl
         << endl;

    // Create some dummy transactions
    vector<Transaction> demoTransactions;

    // Get current time for transactions
    auto now = system_clock::now();
    auto yesterday = now - hours(24);
    auto lastWeek = now - hours(24 * 7);
    auto lastMonth = now - hours(24 * 30);

    // Create some one-time income transactions
    demoTransactions.emplace_back(2500.00, "Monthly Salary", now, IncomeCategory::SALARY);
    demoTransactions.emplace_back(300.00, "Freelance Web Design", lastWeek, IncomeCategory::FREELANCE);
    demoTransactions.emplace_back(50.00, "Birthday Gift", yesterday, IncomeCategory::GIFT);

    // Create some one-time expense transactions
    demoTransactions.emplace_back(85.50, "Weekly Groceries", yesterday, ExpenseCategory::FOOD);
    demoTransactions.emplace_back(45.00, "Bus Pass", lastWeek, ExpenseCategory::TRANSPORT);
    demoTransactions.emplace_back(12.99, "Netflix Subscription", lastMonth, ExpenseCategory::ENTERTAINMENT);
    demoTransactions.emplace_back(120.00, "Electricity Bill", lastMonth, ExpenseCategory::UTILITIES);
    demoTransactions.emplace_back(89.99, "New Headphones", lastWeek, ExpenseCategory::SHOPPING);

    // Create some recurring transactions
    RecurrenceInfo monthlyRent(Frequency::MONTHLY, now);
    demoTransactions.emplace_back(800.00, "Monthly Rent", ExpenseCategory::UTILITIES, monthlyRent);

    RecurrenceInfo weeklySalary(Frequency::WEEKLY, now);
    demoTransactions.emplace_back(625.00, "Weekly Salary", IncomeCategory::SALARY, weeklySalary);

    RecurrenceInfo dailyCoffee(Frequency::DAILY, now);
    demoTransactions.emplace_back(4.50, "Morning Coffee", ExpenseCategory::FOOD, dailyCoffee);

    // Display all transactions in compact format
    cout << "=== COMPACT VIEW ===" << endl;
    cout << "Format: [+/-]Amount|Description|Category|Date[R=Recurring, O=One-off]" << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (const auto &transaction : demoTransactions)
    {
        transaction.displayCompact();
    }

    cout << endl
         << "=== DETAILED VIEW ===" << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (const auto &transaction : demoTransactions)
    {
        transaction.displayDetailed();
    }

    // Calculate and display totals
    double totalIncome = 0.0;
    double totalExpenses = 0.0;

    for (const auto &transaction : demoTransactions)
    {
        if (transaction.getType() == TransactionType::INCOME)
        {
            totalIncome += transaction.getAmount();
        }
        else
        {
            totalExpenses += transaction.getAmount();
        }
    }

    cout << endl
         << "=== SUMMARY ===" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "Total Income:  £" << fixed << setprecision(2) << totalIncome << endl;
    cout << "Total Expenses: £" << fixed << setprecision(2) << totalExpenses << endl;
    cout << "Net Balance:   £" << fixed << setprecision(2) << (totalIncome - totalExpenses) << endl;

    // Demonstrate recurring transaction functionality
    cout << endl
         << "=== NEXT OCCURRENCES ===" << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (const auto &transaction : demoTransactions)
    {
        if (transaction.isRecurring())
        {
            auto nextOccurrence = transaction.getNextOccurrence();
            if (nextOccurrence.has_value())
            {
                auto time_t = system_clock::to_time_t(nextOccurrence.value());
                tm tm_buf;
#ifdef _WIN32
                localtime_s(&tm_buf, &time_t);
#else
                localtime_r(&time_t, &tm_buf);
#endif

                char buffer[20];
                strftime(buffer, sizeof(buffer), "%d-%m-%Y", &tm_buf);

                cout << transaction.getDescription() << " - Next: " << buffer << endl;
            }
        }
    }

    return 0;
}