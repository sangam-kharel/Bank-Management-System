#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "../include/utility.h"

static struct termios original_termios;

static void disableEcho(void)
{
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &original_termios);
    new_termios = original_termios;
    new_termios.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

static void restoreEcho(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen(void)
{
    printf("\nPress Enter to continue...");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

void printHeader(void)
{
    printf("=============================================================\n");
    printf("                 BANK MANAGEMENT SYSTEM\n");
    printf("=============================================================\n");
    printf("Developer : Sangam Kharel\n");
    printf("Version   : v0.7.1\n");
    printf("Language  : C\n");
    printf("=============================================================\n\n");
}

void printMainMenu(void)
{
    printf("1. Create New Account\n");
    printf("2. Customer Login\n");
    printf("3. Administrator Login\n");
    printf("4. Exit\n");
}

void printCustomerMenu(void)
{
    printf("\n=========================================\n");
    printf("         CUSTOMER DASHBOARD\n");
    printf("=========================================\n");
    printf("1. View Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Transaction History\n");
    printf("5. Update Profile\n");
    printf("6. Change PIN\n");
    printf("7. Logout\n");
    printf("=========================================\n");
}

int readPIN(const char *prompt)
{
    int pin = 0;
    int ch;
    int count = 0;

    printf("%s", prompt);
    fflush(stdout);

    disableEcho();

    while (1)
    {
        ch = getchar();

        if (ch == '\n' || ch == EOF)
        {
            if (count == 4)
            {
                printf("\n");
                restoreEcho();
                return pin;
            }
            else
            {
                printf("\nPIN must be exactly 4 digits.\n");
                printf("%s", prompt);
                fflush(stdout);
                pin = 0;
                count = 0;
                continue;
            }
        }

        if (ch >= '0' && ch <= '9')
        {
            if (count < 4)
            {
                pin = pin * 10 + (ch - '0');
                count++;
                printf("*");
                fflush(stdout);
            }
        }
        else if (ch == 127 || ch == 8)
        {
            if (count > 0)
            {
                pin /= 10;
                count--;
                printf("\b \b");
                fflush(stdout);
            }
        }
    }
}

char *readPassword(const char *prompt, char *buffer, int size)
{
    int ch;
    int count = 0;

    printf("%s", prompt);
    fflush(stdout);

    disableEcho();

    while (1)
    {
        ch = getchar();

        if (ch == '\n' || ch == EOF)
        {
            buffer[count] = '\0';
            printf("\n");
            restoreEcho();
            return buffer;
        }

        if (ch == 127 || ch == 8)
        {
            if (count > 0)
            {
                count--;
                printf("\b \b");
                fflush(stdout);
            }
        }
        else if (count < size - 1)
        {
            buffer[count++] = ch;
            printf("*");
            fflush(stdout);
        }
    }
}
