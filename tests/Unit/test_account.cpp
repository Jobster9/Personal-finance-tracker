#include <gtest/gtest.h>
#include "../../Account.h"

TEST(AccountUnit, ConstructorSetsCorrectValues)
{
    Account account("Test Account", 1000.0, 0.05);

    EXPECT_EQ(account.getName(), "Test Account");
    EXPECT_DOUBLE_EQ(account.getBalance(), 1000.0);
    EXPECT_DOUBLE_EQ(account.getInterestRate(), 0.05);
}

TEST(AccountUnit, DepositIncreasesBalance)
{
    Account account("Test", 500.0, 0.02);

    account.deposit(250.0);

    EXPECT_DOUBLE_EQ(account.getBalance(), 750.0);
}

TEST(AccountUnit, WithdrawDecreasesBalance)
{
    Account account("Test", 1000.0, 0.02);

    account.withdraw(300.0);

    EXPECT_DOUBLE_EQ(account.getBalance(), 700.0);
}

TEST(AccountUnit, RenameChangesName)
{
    Account account("Original", 1000.0, 0.02);

    account.rename("New Name");

    EXPECT_EQ(account.getName(), "New Name");
}