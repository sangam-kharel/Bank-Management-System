#ifndef ACCOUNT_H
#define ACCOUNT_H

/* ---------- Constants ---------- */

#define NAME_LENGTH 50
#define ADDRESS_LENGTH 100
#define PHONE_LENGTH 20
#define EMAIL_LENGTH 50
#define TYPE_LENGTH 20

/* ---------- Account Structure ---------- */

typedef struct
{
    int accountNumber;

    char name[NAME_LENGTH];

    char fatherName[NAME_LENGTH];

    char address[ADDRESS_LENGTH];

    char phone[PHONE_LENGTH];

    char email[EMAIL_LENGTH];

    char accountType[TYPE_LENGTH];

    int pin;

    double balance;

} Account;

/* ---------- Function Declarations ---------- */

void createAccount(void);

void inputAccountDetails(Account *account);

void displayAccount(const Account *account);

int saveAccount(const Account *account);

int accountExists(int accountNumber);

int generateAccountNumber(void);

#endif