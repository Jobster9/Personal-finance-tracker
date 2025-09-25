#include "FinanceManager.h"
#include <stdexcept>
#include <chrono>

FinanceManager::FinanceManager() {}

void FinanceManager::addTransaction(const Transaction &transaction)
{
    transactions.push_back(transaction);
}

void FinanceManager::addAccount(const Account &account)
{
    accounts.push_back(account);
}

Account &FinanceManager::getAccount(const string &name)
{
    for (auto &account : accounts)
    {
        if (account.getName() == name)
        {
            return account;
        }
    }
    throw runtime_error("Account '" + name + "' not found");
}

void FinanceManager::transfer(const string &fromAccountName, const string &toAccountName, double amount)
{
    Account &fromAccount = getAccount(fromAccountName);
    Account &toAccount = getAccount(toAccountName);

    if (fromAccount.getBalance() < amount)
    {
        throw runtime_error("Insufficient funds");
    }

    fromAccount.withdraw(amount);
    toAccount.deposit(amount);

    auto now = std::chrono::system_clock::now();

    Transaction withdrawal(amount, "Transfer to " + toAccountName,
                           now, ExpenseCategory::OTHER);
    Transaction deposit(amount, "Transfer from " + fromAccountName,
                        now, IncomeCategory::OTHER);

    transactions.push_back(withdrawal);
    transactions.push_back(deposit);
}