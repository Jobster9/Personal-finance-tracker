#include <gtest/gtest.h>
#include "../../Transaction.h"
#include <chrono>

using namespace std::chrono;

class TransactionUnit : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Create a test date: January 1, 2024
        testDate = system_clock::from_time_t(std::mktime(&testTm));
    }

    system_clock::time_point testDate;

private:
    std::tm testTm = {0, 0, 0, 1, 0, 124}; // Jan 1, 2024
};

// Test one-time income transaction constructor
TEST_F(TransactionUnit, IncomeTransactionConstructor)
{
    Transaction income(1500.0, "Salary payment", testDate, IncomeCategory::SALARY);

    EXPECT_DOUBLE_EQ(income.getAmount(), 1500.0);
    EXPECT_EQ(income.getDescription(), "Salary payment");
    EXPECT_EQ(income.getDate(), testDate);
    EXPECT_EQ(income.getType(), TransactionType::INCOME);
    EXPECT_FALSE(income.isRecurring());
    EXPECT_EQ(income.getIncomeCategory(), IncomeCategory::SALARY);
}

// Test one-time expense transaction constructor
TEST_F(TransactionUnit, ExpenseTransactionConstructor)
{
    Transaction expense(50.0, "Food shopping", testDate, ExpenseCategory::FOOD);

    EXPECT_DOUBLE_EQ(expense.getAmount(), 50.0);
    EXPECT_EQ(expense.getDescription(), "Food shopping");
    EXPECT_EQ(expense.getDate(), testDate);
    EXPECT_EQ(expense.getType(), TransactionType::EXPENSE);
    EXPECT_FALSE(expense.isRecurring());
    EXPECT_EQ(expense.getExpenseCategory(), ExpenseCategory::FOOD);
}

// Test recurring income transaction constructor
TEST_F(TransactionUnit, RecurringIncomeTransactionConstructor)
{
    RecurrenceInfo recurrence(Frequency::MONTHLY, testDate);
    Transaction recurringIncome(3000.0, "Monthly salary", IncomeCategory::SALARY, recurrence);

    EXPECT_DOUBLE_EQ(recurringIncome.getAmount(), 3000.0);
    EXPECT_EQ(recurringIncome.getDescription(), "Monthly salary");
    EXPECT_EQ(recurringIncome.getDate(), testDate);
    EXPECT_EQ(recurringIncome.getType(), TransactionType::INCOME);
    EXPECT_TRUE(recurringIncome.isRecurring());
    EXPECT_EQ(recurringIncome.getIncomeCategory(), IncomeCategory::SALARY);

    auto recInfo = recurringIncome.getRecurrence();
    EXPECT_TRUE(recInfo.has_value());
    EXPECT_EQ(recInfo->frequency, Frequency::MONTHLY);
}

// Test recurring expense transaction constructor
TEST_F(TransactionUnit, RecurringExpenseTransactionConstructor)
{
    RecurrenceInfo recurrence(Frequency::MONTHLY, testDate);
    Transaction recurringExpense(120.0, "Internet bill", ExpenseCategory::UTILITIES, recurrence);

    EXPECT_DOUBLE_EQ(recurringExpense.getAmount(), 120.0);
    EXPECT_EQ(recurringExpense.getDescription(), "Internet bill");
    EXPECT_EQ(recurringExpense.getType(), TransactionType::EXPENSE);
    EXPECT_TRUE(recurringExpense.isRecurring());
    EXPECT_EQ(recurringExpense.getExpenseCategory(), ExpenseCategory::UTILITIES);
}

// Test getting wrong category type throws exception
TEST_F(TransactionUnit, GetWrongCategoryTypeThrows)
{
    Transaction income(1000.0, "Salary", testDate, IncomeCategory::SALARY);
    Transaction expense(100.0, "Food", testDate, ExpenseCategory::FOOD);

    // Income transaction should throw when getting expense category
    EXPECT_THROW(income.getExpenseCategory(), std::runtime_error);

    // Expense transaction should throw when getting income category
    EXPECT_THROW(expense.getIncomeCategory(), std::runtime_error);
}

// Test getNextOccurrence for non-recurring transaction
TEST_F(TransactionUnit, GetNextOccurrenceNonRecurring)
{
    Transaction oneTime(100.0, "One-time payment", testDate, IncomeCategory::BONUS);

    auto nextOccurrence = oneTime.getNextOccurrence();
    EXPECT_FALSE(nextOccurrence.has_value());
}

// Test getNextOccurrence for recurring transaction
TEST_F(TransactionUnit, GetNextOccurrenceRecurring)
{
    RecurrenceInfo monthlyRecurrence(Frequency::MONTHLY, testDate);
    Transaction monthly(500.0, "Monthly payment", IncomeCategory::SALARY, monthlyRecurrence);

    auto nextOccurrence = monthly.getNextOccurrence();
    EXPECT_TRUE(nextOccurrence.has_value());

    // Should be approximately 30 days later (720 hours)
    auto timeDiff = nextOccurrence.value() - testDate;
    auto hoursDiff = duration_cast<hours>(timeDiff).count();
    EXPECT_EQ(hoursDiff, 720); // 30 days * 24 hours
}

// Test getNextOccurrence with end date
TEST_F(TransactionUnit, GetNextOccurrenceWithEndDate)
{
    auto endDate = testDate + hours(24 * 15); // 15 days after start
    RecurrenceInfo recurrenceWithEnd(Frequency::MONTHLY, testDate, endDate);
    Transaction limited(200.0, "Limited recurring", IncomeCategory::OTHER, recurrenceWithEnd);

    auto nextOccurrence = limited.getNextOccurrence();
    // Next occurrence would be 30 days later, but end date is 15 days
    // So should return nullopt
    EXPECT_FALSE(nextOccurrence.has_value());
}

// Test different income categories
TEST_F(TransactionUnit, IncomeCategories)
{
    Transaction salary(1000.0, "Job", testDate, IncomeCategory::SALARY);
    Transaction freelance(500.0, "Project", testDate, IncomeCategory::FREELANCE);
    Transaction investment(200.0, "Dividends", testDate, IncomeCategory::INVESTMENT);
    Transaction gift(100.0, "Birthday", testDate, IncomeCategory::GIFT);
    Transaction bonus(300.0, "Performance", testDate, IncomeCategory::BONUS);
    Transaction other(150.0, "Misc", testDate, IncomeCategory::OTHER);

    EXPECT_EQ(salary.getIncomeCategory(), IncomeCategory::SALARY);
    EXPECT_EQ(freelance.getIncomeCategory(), IncomeCategory::FREELANCE);
    EXPECT_EQ(investment.getIncomeCategory(), IncomeCategory::INVESTMENT);
    EXPECT_EQ(gift.getIncomeCategory(), IncomeCategory::GIFT);
    EXPECT_EQ(bonus.getIncomeCategory(), IncomeCategory::BONUS);
    EXPECT_EQ(other.getIncomeCategory(), IncomeCategory::OTHER);
}

// Test different expense categories
TEST_F(TransactionUnit, ExpenseCategories)
{
    Transaction food(50.0, "Groceries", testDate, ExpenseCategory::FOOD);
    Transaction transport(30.0, "Bus fare", testDate, ExpenseCategory::TRANSPORT);
    Transaction entertainment(25.0, "Movies", testDate, ExpenseCategory::ENTERTAINMENT);
    Transaction utilities(100.0, "Electric", testDate, ExpenseCategory::UTILITIES);
    Transaction shopping(75.0, "Clothes", testDate, ExpenseCategory::SHOPPING);
    Transaction other(40.0, "Misc", testDate, ExpenseCategory::OTHER);

    EXPECT_EQ(food.getExpenseCategory(), ExpenseCategory::FOOD);
    EXPECT_EQ(transport.getExpenseCategory(), ExpenseCategory::TRANSPORT);
    EXPECT_EQ(entertainment.getExpenseCategory(), ExpenseCategory::ENTERTAINMENT);
    EXPECT_EQ(utilities.getExpenseCategory(), ExpenseCategory::UTILITIES);
    EXPECT_EQ(shopping.getExpenseCategory(), ExpenseCategory::SHOPPING);
    EXPECT_EQ(other.getExpenseCategory(), ExpenseCategory::OTHER);
}

// Test RecurrenceInfo functionality
TEST_F(TransactionUnit, RecurrenceInfo)
{
    RecurrenceInfo daily(Frequency::DAILY, testDate);
    RecurrenceInfo weekly(Frequency::WEEKLY, testDate);
    RecurrenceInfo monthly(Frequency::MONTHLY, testDate);
    RecurrenceInfo quarterly(Frequency::QUARTERLY, testDate);
    RecurrenceInfo yearly(Frequency::YEARLY, testDate);

    EXPECT_EQ(daily.frequencyToString(), "Daily");
    EXPECT_EQ(weekly.frequencyToString(), "Weekly");
    EXPECT_EQ(monthly.frequencyToString(), "Monthly");
    EXPECT_EQ(quarterly.frequencyToString(), "Quarterly");
    EXPECT_EQ(yearly.frequencyToString(), "Yearly");

    EXPECT_FALSE(daily.hasEndDate());
}

// Test RecurrenceInfo with end date
TEST_F(TransactionUnit, RecurrenceInfoWithEndDate)
{
    auto endDate = testDate + hours(24 * 30);
    RecurrenceInfo withEnd(Frequency::WEEKLY, testDate, endDate);

    EXPECT_TRUE(withEnd.hasEndDate());

    // Test isActiveOn
    auto beforeStart = testDate - hours(24);
    auto duringPeriod = testDate + hours(24 * 15);
    auto afterEnd = testDate + hours(24 * 35);

    EXPECT_FALSE(withEnd.isActiveOn(beforeStart));
    EXPECT_TRUE(withEnd.isActiveOn(duringPeriod));
    EXPECT_FALSE(withEnd.isActiveOn(afterEnd));
}

// Test edge cases
TEST_F(TransactionUnit, EdgeCases)
{
    // Test zero amount
    Transaction zeroAmount(0.0, "Zero payment", testDate, IncomeCategory::OTHER);
    EXPECT_DOUBLE_EQ(zeroAmount.getAmount(), 0.0);

    // Test empty description
    Transaction emptyDesc(100.0, "", testDate, IncomeCategory::OTHER);
    EXPECT_EQ(emptyDesc.getDescription(), "");

    // Test negative amount validation
    EXPECT_THROW(
        Transaction(-100.0, "Invalid transaction", testDate, IncomeCategory::OTHER),
        std::invalid_argument);

    EXPECT_THROW(
        Transaction(-50.0, "Invalid expense", testDate, ExpenseCategory::FOOD),
        std::invalid_argument);
}