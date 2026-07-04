#ifndef UTILITY_H
#define UTILITY_H

void clearScreen(void);
void pauseScreen(void);
void printHeader(void);
void printMainMenu(void);
void printCustomerMenu(void);
int readPIN(const char *prompt);
char *readPassword(const char *prompt, char *buffer, int size);

#endif
