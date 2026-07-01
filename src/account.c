#include <stdio.h>
#include <string.h>
#include "../include/account.h"

static int nextAccountNumber=1001;

static void trim_newline(char*s){
 size_t n=strlen(s);
 if(n&&s[n-1]=='\n') s[n-1]='\0';
}

static void readLine(const char*prompt,char*buf,size_t sz){
 do{
   printf("%s",prompt);
   if(!fgets(buf,sz,stdin)) return;
   trim_newline(buf);
 }while(strlen(buf)==0);
}

void displayAccount(const Account *a){
 printf("\n===== ACCOUNT PREVIEW =====\n");
 printf("Account : %d\n",a->accountNumber);
 printf("Name    : %s\n",a->name);
 printf("Father  : %s\n",a->fatherName);
 printf("Address : %s\n",a->address);
 printf("Phone   : %s\n",a->phone);
 printf("Email   : %s\n",a->email);
 printf("Type    : %s\n",a->accountType);
 printf("Balance : %.2f\n",a->balance);
}

void createAccount(void){
 Account a;
 char line[64];

 a.accountNumber=nextAccountNumber++;

 readLine("Full Name: ",a.name,sizeof(a.name));
 readLine("Father Name: ",a.fatherName,sizeof(a.fatherName));
 readLine("Address: ",a.address,sizeof(a.address));
 readLine("Phone: ",a.phone,sizeof(a.phone));
 readLine("Email: ",a.email,sizeof(a.email));
 readLine("Account Type (Savings/Current): ",a.accountType,sizeof(a.accountType));

 do{
   printf("PIN (4 digits): ");
   if(!fgets(line,sizeof(line),stdin)) return;
   a.pin=atoi(line);
 }while(a.pin<1000||a.pin>9999);

 do{
   printf("Initial Deposit: ");
   if(!fgets(line,sizeof(line),stdin)) return;
   a.balance=atof(line);
 }while(a.balance<0);

 displayAccount(&a);
 printf("\n[v0.5.0] Account created in memory only. Database support comes in v0.6.0\n");
}
