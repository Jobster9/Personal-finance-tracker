#pragma once
#include <string>
#include <iostream>

using std::string;

class Account
{
public:
    Account(const string &name, double balance, double interestRate) : name(name), balance(balance), interestRate(interestRate) {};

    string getName() const { return name; }
    double getBalance() const { return balance; }
    double getInterestRate() const { return interestRate; }

    void rename(const string &newName) { name = newName; }
    void deposit(double amount) { balance += amount; }
    void withdraw(double amount) { balance -= amount; }
    void adjustRate(double newRate) { interestRate = newRate; }

private:
    double interestRate;
    string name;
    double balance;
};