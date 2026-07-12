#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/database.h"
#include "../include/account.h"
#include "../include/utility.h"
#include "../include/transaction.h"

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

static void readString(const char *message, char *buffer, int size)
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

static int isValidPassword(const char *password)
{
    int len = strlen(password);
    return (len >= 4 && len < PASSWORD_LENGTH);
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
    int cancel = 0;

    /* Account Number */
    account->accountNumber = generateAccountNumber();

    printf("\n=========================================\n");
    printf("          CREATE NEW ACCOUNT\n");
    printf("=========================================\n\n");

    /* Name */
    while (1)
    {
        printf("Full Name (or 0 to cancel): ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            continue;
        }

        trimNewline(input);

        if (strlen(input) == 0)
        {
            printf("Input cannot be empty.\n\n");
            continue;
        }

        if (strcmp(input, "0") == 0)
        {
            cancel = 1;
            break;
        }

        strcpy(account->name, input);
        break;
    }

    if (cancel)
    {
        return;
    }

    /* Father's Name */
    readString("Father's Name        : ", account->fatherName, NAME_LENGTH);

    /* Address */
    readString("Address              : ", account->address, ADDRESS_LENGTH);

    /* Phone Number */
    while (1)
    {
        readString("Phone Number         : ", account->phone, PHONE_LENGTH);

        if (isValidPhone(account->phone))
            break;

        printf("Invalid phone number.\n");
        printf("Only digits are allowed (7 - 15 digits).\n\n");
    }

    /* Email */
    while (1)
    {
        readString("Email Address        : ", account->email, EMAIL_LENGTH);

        if (isValidEmail(account->email))
            break;

        printf("Invalid email address.\n");
        printf("Example: sangam@gmail.com\n\n");
    }

    /* Account Type */
    while (1)
    {
        readString("Account Type (Savings/Current): ", account->accountType, TYPE_LENGTH);

        if (isValidAccountType(account->accountType))
            break;

        printf("Invalid account type.\n");
        printf("Enter Savings or Current.\n\n");
    }

    /* PIN */
    while (1)
    {
        account->pin = readPIN("4-Digit PIN          : ");
        if (isValidPIN(account->pin))
            break;

        printf("PIN must be exactly 4 digits.\n\n");
    }

    /* Password (optional) */
    while (1)
    {
        printf("Password (optional, min 4 chars): ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            continue;

        trimNewline(input);

        if (strlen(input) == 0)
        {
            account->password[0] = '\0';
            break;
        }

        if (isValidPassword(input))
        {
            strcpy(account->password, input);
            break;
        }

        printf("Password must be at least 4 characters.\n\n");
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

    printf("Account Number : %d\n", account->accountNumber);

    printf("Name           : %s\n", account->name);

    printf("Father Name    : %s\n", account->fatherName);

    printf("Address        : %s\n", account->address);

    printf("Phone          : %s\n", account->phone);

    printf("Email          : %s\n", account->email);

    printf("Account Type   : %s\n", account->accountType);

    printf("Balance        : Rs. %.2f\n", account->balance);

    printf("=========================================\n");
}

//PUBLIC API
void createAccount(void)
{
    Account account;

    /* Initialize to detect cancellation */
    account.name[0] = '\0';

    /* Clear input buffer to avoid leftover newline */
    clearInputBuffer();

    /* Get all customer details */
    inputAccountDetails(&account);

    /* Check if user cancelled */
    if (account.name[0] == '\0')
    {
        return;
    }

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

/* Verify PIN for an account */
int verifyPIN(int accountNumber, int pin)
{
    Account account;

    if (!findAccount(accountNumber, &account))
    {
        return 0;
    }

    return (account.pin == pin);
}

int verifyPassword(int accountNumber, const char *password)
{
    Account account;

    if (!findAccount(accountNumber, &account))
    {
        return 0;
    }

    return (strcmp(account.password, password) == 0);
}

/* Customer login - v0.7.0: Account Number based authentication */
void customerLogin(void)
{
    int accountNumber;
    int pin;
    int choice;
    char input[100];
    Account account;

    /* Clear input buffer to avoid leftover newline */
    clearInputBuffer();

    clearScreen();
    printHeader();

    printf("\n=========================================\n");
    printf("         CUSTOMER LOGIN\n");
    printf("=========================================\n\n");

    /* Get Account Number */
    while (1)
    {
        printf("Account Number (or 0 to go back): ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            continue;
        }

        trimNewline(input);

        if (strlen(input) == 0)
        {
            printf("Account number cannot be empty.\n\n");
            continue;
        }

        accountNumber = atoi(input);

        if (accountNumber == 0)
        {
            return; /* Go back to main menu */
        }

        /* Check if account exists */
        if (findAccount(accountNumber, &account))
        {
            break;
        }

        printf("No account found with this account number.\n\n");
    }

    /* Choose login method */
    printf("\nLogin Method:\n");
    printf("1. PIN (4 digits)\n");
    printf("2. Password\n");
    printf("Enter choice (1 or 2): ");

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            continue;
        }

        choice = atoi(input);

        if (choice == 1 || choice == 2)
        {
            break;
        }

        printf("Invalid choice. Enter 1 for PIN or 2 for Password: ");
    }

    if (choice == 1)
    {
        /* Login with PIN */
        pin = readPIN("4-Digit PIN          : ");

        if (verifyPIN(accountNumber, pin))
        {
            printf("\nLogin successful! Welcome back, %s.\n", account.name);
            customerDashboard(accountNumber);
        }
        else
        {
            printf("\nInvalid PIN.\n");
        }
    }
    else
    {
        /* Login with Password */
        char password[PASSWORD_LENGTH];
        readPassword("Password             : ", password, PASSWORD_LENGTH);

        if (strlen(password) == 0)
        {
            printf("\nPassword cannot be empty.\n");
        }
        else if (verifyPassword(accountNumber, password))
        {
            printf("\nLogin successful! Welcome back, %s.\n", account.name);
            customerDashboard(accountNumber);
        }
        else
        {
            printf("\nInvalid password.\n");
        }
    }
}

/* Customer dashboard after successful login - v0.7.0 */
void customerDashboard(int accountNumber)
{
    int choice;
    Account account;
    char input[100];

    while (1)
    {
        clearScreen();
        printHeader();

        /* Refresh account data */
        if (!findAccount(accountNumber, &account))
        {
            printf("\nError: Account not found.\n");
            pauseScreen();
            return;
        }

        printf("Welcome, %s (Account: %d)\n", account.name, account.accountNumber);
        printCustomerMenu();

        printf("\nEnter your choice (or 0 to go back): ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            continue;
        }

        trimNewline(input);
        choice = atoi(input);

        if (choice == 0)
        {
            return; /* Go back to main menu */
        }

        switch (choice)
        {
            case 1:
                /* View Balance - v0.7.0 feature */
                clearScreen();
                printHeader();
                printf("\n=========================================\n");
                printf("         BALANCE INQUIRY\n");
                printf("=========================================\n");
                printf("Account Number : %d\n", account.accountNumber);
                printf("Name           : %s\n", account.name);
                printf("Current Balance: Rs. %.2f\n", account.balance);
                printf("=========================================\n");
                pauseScreen();
                break;

            case 2:
                /* Deposit Money - v0.8.0 feature */
                {
                    double amount;
                    
                    clearScreen();
                    printHeader();
                    printf("\n=========================================\n");
                    printf("         DEPOSIT MONEY\n");
                    printf("=========================================\n");
                    printf("Account Number : %d\n", account.accountNumber);
                    printf("Current Balance: Rs. %.2f\n", account.balance);
                    printf("=========================================\n\n");
                    
                    printf("Enter amount to deposit (or 0 to cancel): ");
                    
                    if (fgets(input, sizeof(input), stdin) == NULL)
                    {
                        continue;
                    }
                    
                    trimNewline(input);
                    amount = atof(input);
                    
                    if (amount == 0)
                    {
                        printf("\nDeposit cancelled.\n");
                        pauseScreen();
                        break;
                    }
                    
                    if (amount < 0)
                    {
                        printf("\nInvalid amount. Amount must be positive.\n");
                        pauseScreen();
                        break;
                    }
                    
                    if (amount < 1)
                    {
                        printf("\nMinimum deposit amount is Rs. 1.\n");
                        pauseScreen();
                        break;
                    }
                    
                    depositMoney(accountNumber, amount);
                    printf("\nDeposit successful!\n");
                    printf("New Balance: Rs. %.2f\n", account.balance + amount);
                    pauseScreen();
                }
                break;

            case 3:
                /* Withdraw Money - v0.9.0 feature */
                {
                    double amount;
                    
                    clearScreen();
                    printHeader();
                    printf("\n=========================================\n");
                    printf("         WITHDRAW MONEY\n");
                    printf("=========================================\n");
                    printf("Account Number : %d\n", account.accountNumber);
                    printf("Current Balance: Rs. %.2f\n", account.balance);
                    printf("=========================================\n\n");
                    
                    printf("Enter amount to withdraw (or 0 to cancel): ");
                    
                    if (fgets(input, sizeof(input), stdin) == NULL)
                    {
                        continue;
                    }
                    
                    trimNewline(input);
                    amount = atof(input);
                    
                    if (amount == 0)
                    {
                        printf("\nWithdrawal cancelled.\n");
                        pauseScreen();
                        break;
                    }
                    
                    if (amount < 0)
                    {
                        printf("\nInvalid amount. Amount must be positive.\n");
                        pauseScreen();
                        break;
                    }
                    
                    if (amount < 1)
                    {
                        printf("\nMinimum withdrawal amount is Rs. 1.\n");
                        pauseScreen();
                        break;
                    }
                    
                    if (amount > account.balance)
                    {
                        printf("\nInsufficient balance. Your current balance is Rs. %.2f\n", account.balance);
                        pauseScreen();
                        break;
                    }
                    
                    if (withdrawMoney(accountNumber, amount))
                    {
                        printf("\nWithdrawal successful!\n");
                        printf("New Balance: Rs. %.2f\n", account.balance - amount);
                    }
                    else
                    {
                        printf("\nWithdrawal failed. Please try again.\n");
                    }
                    pauseScreen();
                }
                break;

            case 4:
                /* Transaction History - v1.1.0 feature */
                {
                    Transaction transactions[MAX_TRANSACTIONS];
                    int count = 0;
                    int i;
                    
                    clearScreen();
                    printHeader();
                    printf("\n=========================================\n");
                    printf("       TRANSACTION HISTORY\n");
                    printf("=========================================\n");
                    printf("Account Number : %d\n", account.accountNumber);
                    printf("Name           : %s\n", account.name);
                    printf("=========================================\n\n");
                    
                    if (getTransactions(accountNumber, transactions, &count))
                    {
                        if (count == 0)
                        {
                            printf("No transactions found.\n");
                        }
                        else
                        {
                            printf("%-12s | %-10s | %10s | %12s\n", 
                                   "Date", "Time", "Type", "Amount");
                            printf("--------------------------------------------------------------\n");
                            
                            for (i = 0; i < count; i++)
                            {
                                const char *typeStr = (transactions[i].type == DEPOSIT) ? "DEPOSIT" : "WITHDRAWAL";
                                printf("%-12s | %-10s | %10s | Rs. %10.2f\n",
                                       transactions[i].date,
                                       transactions[i].time,
                                       typeStr,
                                       transactions[i].amount);
                            }
                        }
                    }
                    else
                    {
                        printf("Error reading transactions.\n");
                    }
                    pauseScreen();
                }
                break;

            case 5:
                /* Update Profile - v1.2.0 feature */
                {
                    clearScreen();
                    printHeader();
                    printf("\n=========================================\n");
                    printf("         UPDATE PROFILE\n");
                    printf("=========================================\n");
                    printf("Account Number : %d\n", account.accountNumber);
                    printf("Current Name   : %s\n", account.name);
                    printf("=========================================\n\n");
                    
                    printf("Enter new name (or 0 to cancel): ");
                    
                    if (fgets(input, sizeof(input), stdin) == NULL)
                    {
                        continue;
                    }
                    
                    trimNewline(input);
                    
                    if (strcmp(input, "0") == 0)
                    {
                        printf("\nUpdate cancelled.\n");
                        pauseScreen();
                        break;
                    }
                    
                    if (strlen(input) == 0)
                    {
                        printf("\nName cannot be empty.\n");
                        pauseScreen();
                        break;
                    }
                    
                    strcpy(account.name, input);
                    
                    if (updateAccount(&account))
                    {
                        printf("\nProfile updated successfully!\n");
                    }
                    else
                    {
                        printf("\nFailed to update profile.\n");
                    }
                    pauseScreen();
                }
                break;

            case 6:
                /* Change PIN - v1.2.0 feature */
                {
                    int newPin;
                    
                    clearScreen();
                    printHeader();
                    printf("\n=========================================\n");
                    printf("         CHANGE PIN\n");
                    printf("=========================================\n");
                    printf("Account Number : %d\n", account.accountNumber);
                    printf("Current PIN    : ****\n");
                    printf("=========================================\n\n");
                    
                    newPin = readPIN("Enter new 4-digit PIN: ");
                    
                    if (isValidPIN(newPin))
                    {
                        account.pin = newPin;
                        
                        if (updateAccount(&account))
                        {
                            printf("\nPIN changed successfully!\n");
                        }
                        else
                        {
                            printf("\nFailed to change PIN.\n");
                        }
                    }
                    else
                    {
                        printf("\nInvalid PIN. PIN must be exactly 4 digits.\n");
                    }
                    pauseScreen();
                }
                break;

            case 7:
                /* Logout */
                clearScreen();
                printHeader();
                printf("\nLogging out...\n");
                return;

            default:
                printf("\nInvalid choice. Please try again.\n");
                pauseScreen();
        }
    }
}