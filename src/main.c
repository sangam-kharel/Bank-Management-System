#include "../include/account.h"
#include <stdio.h>
#include <stdlib.h>

#include "../include/utility.h"

int main(void)
{
    int choice;

    while (1)
    {
        clearScreen();

        printHeader();

        printMainMenu();

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                customerLogin();
                break;

            case 3:
                printf("\nFeature coming in Stage 16.\n");
                break;

            case 4:
                printf("\nThank you for using Bank Management System.\n");
                return 0;

            default:
                printf("\nInvalid choice.\n");
        }

        while (getchar() != '\n');

        pauseScreen();
    }

    return 0;
}
