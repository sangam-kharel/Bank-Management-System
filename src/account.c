#include <stdio.h>

#include "../include/account.h"

/*
 * Create a new account.
 * (Real implementation will be added in the next stage.)
 */
void createAccount(void)
{
    printf("\n========================================\n");
    printf("        CREATE ACCOUNT MODULE\n");
    printf("========================================\n");

    printf("This feature is under development.\n");
}

/*
 * Collect account details from the user.
 * (Implemented in Stage 6.)
 */
void inputAccountDetails(Account *account)
{
    (void)account;
}

/*
 * Display account information.
 * (Expanded later.)
 */
void displayAccount(const Account *account)
{
    (void)account;
}

/*
 * Save account to the database.
 * (Implemented in Stage 7.)
 */
int saveAccount(const Account *account)
{
    (void)account;
    return 1;
}

/*
 * Check whether an account exists.
 */
int accountExists(int accountNumber)
{
    (void)accountNumber;
    return 0;
}

/*
 * Generate a unique account number.
 */
int generateAccountNumber(void)
{
    return 1001;
}