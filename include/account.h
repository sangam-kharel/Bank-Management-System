#ifndef ACCOUNT_H
#define ACCOUNT_H

#define NAME_LENGTH 50
#define ADDRESS_LENGTH 100
#define PHONE_LENGTH 20
#define EMAIL_LENGTH 50
#define TYPE_LENGTH 20
#define PASSWORD_LENGTH 50

typedef struct{
    int accountNumber;
    char name[NAME_LENGTH];
    char fatherName[NAME_LENGTH];
    char address[ADDRESS_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
    char accountType[TYPE_LENGTH];
    char password[PASSWORD_LENGTH];
    int pin;
    double balance;
} Account;

void createAccount(void);
void displayAccount(const Account *account);

/* Customer Login Functions */
void customerLogin(void);
void customerDashboard(int accountNumber);
int verifyPIN(int accountNumber, int pin);
int verifyPassword(int accountNumber, const char *password);
int findAccountByPhone(const char *phone, Account *account);
int findAccountByPhoneAndPin(const char *phone, int pin, Account *account);
int findAccountByPhoneAndPassword(const char *phone, const char *password, Account *account);
#endif
