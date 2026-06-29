#include <stdio.h>
#include <stdlib.h>

#include "../include/utility.h"

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
    getchar();
}

void printHeader(void)
{
    printf("=============================================================\n");
    printf("                 BANK MANAGEMENT SYSTEM\n");
    printf("=============================================================\n");
    printf("Developer : Sangam Kharel\n");
    printf("Version   : v0.3.0\n");
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
