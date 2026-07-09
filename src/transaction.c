#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/transaction.h"
#include "../include/database.h"

int saveTransaction(const Transaction *transaction)
{
    FILE *fp;

    fp = fopen("database/transactions.dat", "ab");

    if (fp == NULL)
    {
        printf("\nERROR: Unable to open transaction database.\n");
        return 0;
    }

    fwrite(transaction,
           sizeof(Transaction),
           1,
           fp);

    fclose(fp);

    return 1;
}

int getTransactions(int accountNumber, Transaction *transactions, int *count)
{
    FILE *fp;
    Transaction temp;
    int i = 0;

    *count = 0;

    fp = fopen("database/transactions.dat", "rb");

    if (fp == NULL)
    {
        return 1; /* No transactions file yet, but not an error */
    }

    while (fread(&temp, sizeof(Transaction), 1, fp) == 1 && i < MAX_TRANSACTIONS)
    {
        if (temp.accountNumber == accountNumber)
        {
            transactions[*count] = temp;
            (*count)++;
            i++;
        }
    }

    fclose(fp);

    return 1;
}

void depositMoney(int accountNumber, double amount)
{
    Account account;
    Transaction transaction;
    time_t now;
    struct tm *t;

    if (!findAccount(accountNumber, &account))
    {
        printf("\nError: Account not found.\n");
        return;
    }

    /* Update balance */
    account.balance += amount;

    /* Save updated account */
    updateAccount(&account);

    /* Record transaction */
    transaction.accountNumber = accountNumber;
    transaction.type = DEPOSIT;
    transaction.amount = amount;
    transaction.balanceAfter = account.balance;

    /* Get current date and time */
    time(&now);
    t = localtime(&now);
    strftime(transaction.date, sizeof(transaction.date), "%Y-%m-%d", t);
    strftime(transaction.time, sizeof(transaction.time), "%H:%M:%S", t);

    saveTransaction(&transaction);
}

int withdrawMoney(int accountNumber, double amount)
{
    Account account;
    Transaction transaction;
    time_t now;
    struct tm *t;

    if (!findAccount(accountNumber, &account))
    {
        return 0;
    }

    /* Check for sufficient balance */
    if (account.balance < amount)
    {
        return 0;
    }

    /* Update balance */
    account.balance -= amount;

    /* Save updated account */
    updateAccount(&account);

    /* Record transaction */
    transaction.accountNumber = accountNumber;
    transaction.type = WITHDRAWAL;
    transaction.amount = amount;
    transaction.balanceAfter = account.balance;

    /* Get current date and time */
    time(&now);
    t = localtime(&now);
    strftime(transaction.date, sizeof(transaction.date), "%Y-%m-%d", t);
    strftime(transaction.time, sizeof(transaction.time), "%H:%M:%S", t);

    saveTransaction(&transaction);

    return 1;
}
