#include "Transaction.h"

void Transaction::displayCompact() const
{
    string typeStr = (type == TransactionType::EXPENSE) ? "-" : "+";
    string recChar = isRecurring() ? "R" : "O";

    cout << typeStr << "£" << std::fixed << std::setprecision(2) << amount
         << "|" << description
         << "|" << categoryToString()
         << "|" << dateToString()
         << "[" << recChar << "]" << endl;
}

void Transaction::displayDetailed() const
{
    string typeStr = (type == TransactionType::EXPENSE) ? "EXPENSE" : "INCOME";
    string recChar = isRecurring() ? "RECURRING" : "ONE-OFF";

    cout << typeStr << "£" << std::fixed << std::setprecision(2) << amount
         << "|" << description
         << "|" << categoryToString()
         << "|" << dateToString()
         << "[" << recChar << "]" << endl;
}

optional<system_clock::time_point> Transaction::getNextOccurrence() const
{
    if (!recurrence.has_value())
        return std::nullopt;

    auto now = system_clock::now();
    auto next = calculateNextDate(transactionDate, recurrence->frequency, now);

    // Check if we've passed the end date
    if (recurrence->endDate.has_value() && next > recurrence->endDate.value())
    {
        return std::nullopt;
    }

    return next;
}

ExpenseCategory Transaction::getExpenseCategory() const
{
    if (type != TransactionType::EXPENSE)
    {
        throw std::runtime_error("This transaction is not an expense");
    }
    return expenseCat;
}

IncomeCategory Transaction::getIncomeCategory() const
{
    if (type != TransactionType::INCOME)
    {
        throw std::runtime_error("This transaction is not an income");
    }
    return incomeCat;
}

string Transaction::dateToString() const
{
    auto time_t = system_clock::to_time_t(transactionDate);
    tm tm_buf;
#ifdef _WIN32
    localtime_s(&tm_buf, &time_t);
#else
    localtime_r(&tm_buf, &time_t);
#endif
    static constexpr size_t DATE_BUFFER_SIZE = 12;
    char buffer[DATE_BUFFER_SIZE];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &tm_buf);
    return string(buffer);
}

string Transaction::categoryToString() const
{
    if (type == TransactionType::INCOME)
    {
        switch (incomeCat)
        {
        case IncomeCategory::SALARY:
            return "Salary";
        case IncomeCategory::FREELANCE:
            return "Freelance";
        case IncomeCategory::INVESTMENT:
            return "Investment";
        case IncomeCategory::GIFT:
            return "Gift";
        case IncomeCategory::BONUS:
            return "Bonus";
        case IncomeCategory::OTHER:
            return "Other";
        default:
            return "Unknown";
        }
    }
    else
    {
        switch (expenseCat)
        {
        case ExpenseCategory::FOOD:
            return "Food";
        case ExpenseCategory::TRANSPORT:
            return "Transport";
        case ExpenseCategory::ENTERTAINMENT:
            return "Entertainment";
        case ExpenseCategory::UTILITIES:
            return "Utilities";
        case ExpenseCategory::SHOPPING:
            return "Shopping";
        case ExpenseCategory::OTHER:
            return "Other";
        default:
            return "Unknown";
        }
    }
};

system_clock::time_point Transaction::calculateNextDate(const system_clock::time_point &lastDate, Frequency freq,
                                                        const system_clock::time_point &fromDate) const
{
    using namespace std::chrono;

    switch (freq)
    {
    case Frequency::DAILY:
        return lastDate + hours(24);
    case Frequency::WEEKLY:
        return lastDate + hours(24 * 7);
    case Frequency::MONTHLY:
        return lastDate + hours(24 * 30); // Approximation
    case Frequency::QUARTERLY:
        return lastDate + hours(24 * 90); // Approximation
    case Frequency::YEARLY:
        return lastDate + hours(24 * 365); // Approximation
    default:
        return lastDate;
    }
};
