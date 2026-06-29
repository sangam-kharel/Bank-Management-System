#include <stdio.h>

#include "../include/account.h"

void createAccount(void)
{
    printf("\n========================================\n");
    printf("        CREATE ACCOUNT MODULE\n");
    printf("========================================\n");

    printf("\nThis feature will be implemented in Stage 5.\n");
}

void displayAccount(const Account *account)
{
    (void)account;
}

int accountExists(int accountNumber)
{
    (void)accountNumber;

    return 0;
}

int generateAccountNumber(void)
{
    return 1001;
}