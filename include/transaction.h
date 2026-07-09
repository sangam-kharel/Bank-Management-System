#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "account.h"

#define MAX_TRANSACTIONS 100

typedef enum {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER
} TransactionType;

typedef struct {
    int accountNumber;
    TransactionType type;
    double amount;
    double balanceAfter;
    char date[20];
    char time[10];
} Transaction;

/* Transaction functions */
int saveTransaction(const Transaction *transaction);
int getTransactions(int accountNumber, Transaction *transactions, int *count);
void depositMoney(int accountNumber, double amount);
int withdrawMoney(int accountNumber, double amount);

#endif
