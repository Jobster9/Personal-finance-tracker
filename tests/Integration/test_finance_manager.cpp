#include <gtest/gtest.h>
#include "../../FinanceManager.h"

TEST(FinanceManagerIntegration, TransferBetweenAccounts)
{
    FinanceManager manager;
    Account checking("Checking", 1000.0, 0.01);
    Account savings("Savings", 500.0, 0.05);

    manager.addAccount(checking);
    manager.addAccount(savings);

    manager.transfer("Checking", "Savings", 200.0);

    EXPECT_DOUBLE_EQ(manager.getAccount("Checking").getBalance(), 800.0);
    EXPECT_DOUBLE_EQ(manager.getAccount("Savings").getBalance(), 700.0);
}