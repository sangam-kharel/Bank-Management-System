#include <stdio.h>

#include "../include/account.h"

/*
 * Create a new account.
 * (Real implementation will be added in the next stage.)
 */
void createAccount(void)
{
    Account account;

    inputAccountDetails(&account);

    displayAccount(&account);

    printf("\nAccount is ready to be saved.\n");
    printf("(Database support will be added in Stage 7.)\n");
}

/*
 * Collect account details from the user.
 * (Implemented in Stage 6.)
 */
void inputAccountDetails(Account *account)
{
    printf("\n========== CREATE ACCOUNT ==========\n");

    account->accountNumber = generateAccountNumber();

    printf("Full Name       : ");
    scanf(" %49[^\n]", account->name);

    printf("Father's Name   : ");
    scanf(" %49[^\n]", account->fatherName);

    printf("Address         : ");
    scanf(" %99[^\n]", account->address);

    printf("Phone Number    : ");
    scanf(" %19s", account->phone);

    printf("Email           : ");
    scanf(" %49s", account->email);

    printf("Account Type    : ");
    scanf(" %19s", account->accountType);

    printf("4-Digit PIN     : ");
    scanf("%d", &account->pin);

    printf("Initial Deposit : ");
    scanf("%lf", &account->balance);
}

/*
 * Display account information.
 * (Expanded later.)
 */
void displayAccount(const Account *account)
{
    printf("\n=========================================\n");
    printf("        ACCOUNT CREATED (PREVIEW)\n");
    printf("=========================================\n");

    printf("Account Number : %d\n", account->accountNumber);
    printf("Name           : %s\n", account->name);
    printf("Father Name    : %s\n", account->fatherName);
    printf("Address        : %s\n", account->address);
    printf("Phone          : %s\n", account->phone);
    printf("Email          : %s\n", account->email);
    printf("Account Type   : %s\n", account->accountType);
    printf("Balance        : %.2lf\n", account->balance);

    printf("=========================================\n");
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
    static int nextAccountNumber = 1001;

    return nextAccountNumber++;
}