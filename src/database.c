#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/database.h"

//DATABASE FUNCTIONS

int saveAccount(const Account *account)
{
    FILE *fp;

    fp = fopen("database/accounts.dat", "ab");

    if (fp == NULL)
    {
        printf("\nERROR: Unable to open database.\n");
        return 0;
    }

    fwrite(account,
           sizeof(Account),
           1,
           fp);

    fclose(fp);

    return 1;
}


int accountExists(int accountNumber)
{
    FILE *fp;

    Account account;

    fp = fopen("database/accounts.dat", "rb");

    if (fp == NULL)
    {
        return 0;
    }

    while (fread(&account,
                 sizeof(Account),
                 1,
                 fp) == 1)
    {
        if (account.accountNumber == accountNumber)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}

int generateAccountNumber(void)
{
    FILE *fp;

    Account account;

    int lastNumber = 1000;

    fp = fopen("database/accounts.dat", "rb");

    if (fp == NULL)
    {
        return 1001;
    }

    while (fread(&account,
                 sizeof(Account),
                 1,
                 fp) == 1)
    {
        if (account.accountNumber > lastNumber)
        {
            lastNumber = account.accountNumber;
        }
    }

    fclose(fp);

    return lastNumber + 1;
}
//SEARCH FUNCTIONS

int findAccount(int accountNumber, Account *account)
{
    FILE *fp;

    fp = fopen("database/accounts.dat", "rb");

    if (fp == NULL)
    {
        return 0;
    }

    while (fread(account,
                 sizeof(Account),
                 1,
                 fp) == 1)
    {
        if (account->accountNumber == accountNumber)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}

//--------------------------------------------------

long findAccountPosition(int accountNumber)
{
    FILE *fp;

    Account account;

    long position;

    fp = fopen("database/accounts.dat", "rb");

    if (fp == NULL)
    {
        return -1;
    }

    while (fread(&account,
                 sizeof(Account),
                 1,
                 fp) == 1)
    {
        if (account.accountNumber == accountNumber)
        {
            position = ftell(fp) - sizeof(Account);

            fclose(fp);

            return position;
        }
    }

    fclose(fp);

    return -1;
}
//UPDATE FUNCTIONS
int updateAccount(const Account *account)
{
    FILE *fp;

    long position;

    position = findAccountPosition(account->accountNumber);

    if (position == -1)
    {
        return 0;
    }

    fp = fopen("database/accounts.dat", "rb+");

    if (fp == NULL)
    {
        return 0;
    }

    fseek(fp, position, SEEK_SET);

    fwrite(account, sizeof(Account), 1, fp);

    fclose(fp);

    return 1;
}

/* Search by phone functions */
int findAccountByPhone(const char *phone, Account *account)
{
    FILE *fp;

    fp = fopen("database/accounts.dat", "rb");

    if (fp == NULL)
    {
        return 0;
    }

    while (fread(account,
                 sizeof(Account),
                 1,
                 fp) == 1)
    {
        if (strcmp(account->phone, phone) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}

int findAccountByPhoneAndPin(const char *phone, int pin, Account *account)
{
    FILE *fp;

    fp = fopen("database/accounts.dat", "rb");

    if (fp == NULL)
    {
        return 0;
    }

    while (fread(account,
                 sizeof(Account),
                 1,
                 fp) == 1)
    {
        if (strcmp(account->phone, phone) == 0 && account->pin == pin)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}

int findAccountByPhoneAndPassword(const char *phone, const char *password, Account *account)
{
    FILE *fp;

    fp = fopen("database/accounts.dat", "rb");

    if (fp == NULL)
    {
        return 0;
    }

    while (fread(account,
                 sizeof(Account),
                 1,
                 fp) == 1)
    {
        if (strcmp(account->phone, phone) == 0 && strcmp(account->password, password) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}
