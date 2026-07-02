#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "../include/database.h"
#include "../include/account.h"

//PRIVATE HELPERS

static void trimNewline(char *text)
{
    size_t len = strlen(text);

    if (len > 0 && text[len - 1] == '\n')
    {
        text[len - 1] = '\0';
    }
}

static void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

static void readString(const char *message,
char *buffer, int size)
{
    while (1)
    {
        printf("%s", message);

        if (fgets(buffer, size, stdin) == NULL)
        {
            continue;
        }

        trimNewline(buffer);

        if (strlen(buffer) == 0)
        {
            printf("Input cannot be empty.\n\n");
            continue;
        }

        return;
    }
}

//VALIDATION FUNCTIONS

static int isValidPIN(int pin)
{
    return (pin >= 1000 && pin <= 9999);
}

static int isValidBalance(double balance)
{
    return (balance >= 0);
}

static int isDigitsOnly(const char *text)
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)text[i]))
        {
            return 0;
        }
    }

    return 1;
}

static int isValidPhone(const char *phone)
{
    int len = strlen(phone);

    if (len < 7 || len > 15)
    {
        return 0;
    }

    return isDigitsOnly(phone);
}

static int isValidEmail(const char *email)
{
    return strchr(email, '@') != NULL;
}

static int isValidAccountType(const char *type)
{
    if (strcmp(type, "Savings") == 0)
    {
        return 1;
    }

    if (strcmp(type, "Current") == 0)
    {
        return 1;
    }

    return 0;
}


//INPUT FUNCTIONS

static void inputAccountDetails(Account *account)
{
    char input[100];

    /* Account Number */
    account->accountNumber = generateAccountNumber();

    printf("\n=========================================\n");
    printf("          CREATE NEW ACCOUNT\n");
    printf("=========================================\n\n");

    /* Name */
    readString("Full Name            : ",
               account->name,
               NAME_LENGTH);

    /* Father's Name */
    readString("Father's Name        : ",
               account->fatherName,
               NAME_LENGTH);

    /* Address */
    readString("Address              : ",
               account->address,
               ADDRESS_LENGTH);

    /* Phone Number */
    while (1)
    {
        readString("Phone Number         : ",
                   account->phone,
                   PHONE_LENGTH);

        if (isValidPhone(account->phone))
            break;

        printf("Invalid phone number.\n");
        printf("Only digits are allowed (7 - 15 digits).\n\n");
    }

    /* Email */
    while (1)
    {
        readString("Email Address        : ",
                   account->email,
                   EMAIL_LENGTH);

        if (isValidEmail(account->email))
            break;

        printf("Invalid email address.\n");
        printf("Example: sangam@gmail.com\n\n");
    }

    /* Account Type */
    while (1)
    {
        readString("Account Type "
                   "(Savings/Current): ",
                   account->accountType,
                   TYPE_LENGTH);

        if (isValidAccountType(account->accountType))
            break;

        printf("Invalid account type.\n");
        printf("Enter Savings or Current.\n\n");
    }

//PIN
    while (1)
    {
        printf("4-Digit PIN          : ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            continue;

        account->pin = atoi(input);

        if (isValidPIN(account->pin))
            break;

        printf("PIN must be exactly 4 digits.\n\n");
    }

    /* Initial Deposit */
    while (1)
    {
        printf("Initial Deposit      : ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            continue;

        account->balance = atof(input);

        if (isValidBalance(account->balance))
            break;

        printf("Balance cannot be negative.\n\n");
    }
}

//DISPLAY FUNCTIONS

void displayAccount(const Account *account)
{
    printf("\n");
    printf("=========================================\n");
    printf("         ACCOUNT INFORMATION\n");
    printf("=========================================\n");

    printf("Account Number : %d\n",
           account->accountNumber);

    printf("Name           : %s\n",
           account->name);

    printf("Father Name    : %s\n",
           account->fatherName);

    printf("Address        : %s\n",
           account->address);

    printf("Phone          : %s\n",
           account->phone);

    printf("Email          : %s\n",
           account->email);

    printf("Account Type   : %s\n",
           account->accountType);

    printf("Balance        : Rs. %.2f\n",
           account->balance);

    printf("=========================================\n");
}
//PUBLIC API
void createAccount(void)
  {
    Account account;
    clearInputBuffer(); 
    /* Get all customer details */
    inputAccountDetails(&account);

    /* Show account preview */
    displayAccount(&account);
    if (saveAccount(&account))
    {
      printf("\nAccount successfully saved.\n");
      
    }
    else
    {
       printf("\nAccount could not be saved.\n");
    }
  }