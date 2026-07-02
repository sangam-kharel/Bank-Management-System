#ifndef DATABASE_H
#define DATABASE_H

#include "account.h"

/* Database Operations */

int saveAccount(const Account *account);

int accountExists(int accountNumber);

int generateAccountNumber(void);

int findAccount(int accountNumber, Account *account);

long findAccountPosition(int accountNumber);

int updateAccount(const Account *account);

#endif
