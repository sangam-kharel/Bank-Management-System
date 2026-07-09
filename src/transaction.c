#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/transaction.h"
#include "../include/database.h"

/* Helper function to record a transaction */
static void recordTransaction(int accountNumber, TransactionType type, double amount, double balanceAfter)
{
    Transaction transaction;
    time_t now;
    struct tm *t;

    transaction.accountNumber = accountNumber;
    transaction.type = type;
    transaction.amount = amount;
    transaction.balanceAfter = balanceAfter;

    time(&now);
    t = localtime(&now);
    strftime(transaction.date, sizeof(transaction.date), "%Y-%m-%d", t);
    strftime(transaction.time, sizeof(transaction.time), "%H:%M:%S", t);

    saveTransaction(&transaction);
}

int saveTransaction(const Transaction *transaction)
{
    FILE *fp;

    fp = fopen("database/transactions.dat", "ab");

    if (fp == NULL)
    {
        printf("\nERROR: Unable to open transaction database.\n");
        return 0;
    }

    fwrite(transaction, sizeof(Transaction), 1, fp);
    fclose(fp);

    return 1;
}

int getTransactions(int accountNumber, Transaction *transactions, int *count)
{
    FILE *fp;
    Transaction temp;

    *count = 0;

    fp = fopen("database/transactions.dat", "rb");

    if (fp == NULL)
    {
        return 1; /* No transactions file yet, but not an error */
    }

    while (fread(&temp, sizeof(Transaction), 1, fp) == 1 && *count < MAX_TRANSACTIONS)
    {
        if (temp.accountNumber == accountNumber)
        {
            transactions[*count] = temp;
            (*count)++;
        }
    }

    fclose(fp);

    return 1;
}

void depositMoney(int accountNumber, double amount)
{
    Account account;

    if (!findAccount(accountNumber, &account))
    {
        printf("\nError: Account not found.\n");
        return;
    }

    account.balance += amount;
    updateAccount(&account);
    recordTransaction(accountNumber, DEPOSIT, amount, account.balance);
}

int withdrawMoney(int accountNumber, double amount)
{
    Account account;

    if (!findAccount(accountNumber, &account))
    {
        return 0;
    }

    if (account.balance < amount)
    {
        return 0;
    }

    account.balance -= amount;
    updateAccount(&account);
    recordTransaction(accountNumber, WITHDRAWAL, amount, account.balance);

    return 1;
}