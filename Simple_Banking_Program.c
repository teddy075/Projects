//SIMPLE PROGRAM FOR THE TRANSACTION SYSTEM//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNT 100

// TO STORE THE DATA AND CREDENTIALS OF THE USER
struct Account {
    char fullName[100];
    char phoneNumber[11]; 
    int pin;
    float balance; 
};

// FUNCTIONS
void creatAccount(struct Account account[], int *accountCount);
int login(struct Account account[], int accountCount);
void menu(struct Account *acc);
void balanceCheck(struct Account *acc);
void sendmoney(struct Account *acc);
void loadmoney(struct Account *acc);
void accountInfo(struct Account *acc);
void savingAccdata(struct Account account[], int accountCount);
void retAccdata(struct Account account[], int *accountCount);
int pinVerify(int pin);

int main() {
    struct Account accounts[MAX_ACCOUNT];
    int accountCount = 0;
    int loggedinIndex;
    int option;

    printf("*********************************8888888888888**************\n");
    printf("        WELCOME TO THE SIMPLE BANKING PROGRAM \n");
    printf("*************************************************************\n");

    // FIRST MENU DISPLAYED TO THE USERS
    retAccdata(accounts, &accountCount); 

    while (1) {
        printf("\nMENU:\n");
        printf("1. Login\n");
        printf("2. Create a New Account\n");
        printf("3. Exit\n");
        printf("Enter the option which you want to access: ");
        scanf("%d", &option);

        if (option == 1) {
            loggedinIndex = login(accounts, accountCount);
            if (loggedinIndex != -1) {
                menu(&accounts[loggedinIndex]); 
            }

        } else if (option == 2) {
            creatAccount(accounts, &accountCount);
            savingAccdata(accounts, accountCount);
        } else if (option == 3) {
            printf("Thank you for using our service, Goodbye!!!"); 
            exit(0);
        } else {
            printf("Invalid Input! Please try again.\n");
        }
    }

    return 0;
}

// FUNCTION TO CREATE A NEW ACCOUNT
void creatAccount(struct Account account[], int *accountCount) {
    printf("\nFill up all the information to Create an account\n");

    printf("Enter your Full Name: ");
    getchar(); 
    fgets(account[*accountCount].fullName, sizeof(account[*accountCount].fullName), stdin);
    account[*accountCount].fullName[strcspn(account[*accountCount].fullName, "\n")] = 0; 

    printf("Enter your phone number: ");
    fgets(account[*accountCount].phoneNumber, sizeof(account[*accountCount].phoneNumber), stdin);
    account[*accountCount].phoneNumber[strcspn(account[*accountCount].phoneNumber, "\n")] = 0; 

    printf("Set a 4-digit PIN: ");
    scanf("%d", &(account[*accountCount].pin));

    account[*accountCount].balance = 0.0; //account is started with zero balace

    printf("Account created successfully!\n");
    (*accountCount)++;
}

// FUNCTION FOR LOGIN (USING BOTH PIN AND PHONE NUMBERS)
int login(struct Account account[], int accountCount) {
    char phoneNumber[11]; 
    int pin;
    int i;

    printf("\nEnter your phone number: ");
    getchar(); 
    fgets(phoneNumber, sizeof(phoneNumber), stdin);
    phoneNumber[strcspn(phoneNumber, "\n")] = 0; 

    printf("Enter your PIN: ");
    scanf("%d", &pin);

    for (i = 0; i < accountCount; i++) {
        if (strcmp(account[i].phoneNumber, phoneNumber) == 0 && account[i].pin == pin) {
            printf("\nLogin successful! Welcome, %s!\n", account[i].fullName);
            return i;
        }
    }

    printf("Invalid phone number or PIN. Please try again.\n");
    return -1;
}

// MAIN MENU FUNCTION
void menu(struct Account *acc) {
    int choice;
    do {
        printf("\n================== Main Menu ==================\n");
        printf("1. Check Balance\n");
        printf("2. Send Money\n");
        printf("3. Load Balance\n");
        printf("4. View Bank Information\n");
        printf("5. Log Out\n");
        printf("================================================\n");
        printf("Enter the option which you want to access:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                balanceCheck(acc); 
                break;
            case 2:
                sendmoney(acc); 
                break;
            case 3:
                loadmoney(acc); 
                break;
            case 4:
                accountInfo(acc); 
                break;
            case 5:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (1);
}

// LOAD BALANCE FUNCTION
void loadmoney(struct Account *acc) {
    float amount;

    printf("\nEnter the amount to load in your Account: Rs.");
    scanf("%f", &amount);

    acc->balance += amount;
    printf("Rs.%.2f amount is loaded successfully! Your new balance is Rs.%.2f\n", amount, acc->balance);
}

// FUNCTION TO CHECK ACCOUNT BALANCE
void balanceCheck(struct Account *acc) {
    printf("\nYour current Balance is: Rs.%.2f\n", acc->balance);
}

// FUNCTION TO VIEW ACCOUNT INFORMATION
void accountInfo(struct Account *acc) {
    printf("\n--------Account Information----------------------\n");
    printf("Full Name: %s\n", acc->fullName);
    printf("Phone Number: %s\n", acc->phoneNumber);
    printf("Balance: Rs.%.2f\n", acc->balance);
    printf("------------------------------------------------------\n");
}

// FUNCTION TO SEND MONEY
void sendmoney(struct Account *acc) {
    char recipientPhone[11];
    float amount;

    printf("\nEnter the phone number of the recipient: ");
    scanf("%s", recipientPhone);

    printf("Enter the amount to send: Rs.");
    scanf("%f", &amount);

    if (amount > acc->balance) {
        printf("Insufficient funds in your account! Your current balance is Rs.%.2f\n", acc->balance);
    } else {
        acc->balance -= amount;
        printf("Money sent successfully! Your new balance is Rs.%.2f\n", acc->balance);
    }
}

// FUNCTION TO SAVE USER ALL ACCOUNT DATA TO FILES
void savingAccdata(struct Account account[], int accountCount) {
    FILE *file = fopen("accounts.dat", "w");
    if (file != NULL) {
        fwrite(&accountCount, sizeof(int), 1, file);
        fwrite(account, sizeof(struct Account), accountCount, file); 
        fclose(file);
        printf("Account data saved successfully.\n");
    } else {
        printf("Error saving account data!\n");
    }
}

// FUNCTION TO LOAD ACCOUNT DATA FROM FILE
void retAccdata(struct Account account[], int *accountCount) {
    FILE *file = fopen("accounts.dat", "r");
    if (file != NULL) {
        fread(accountCount, sizeof(int), 1, file);
        fread(account, sizeof(struct Account), *accountCount, file); 
        fclose(file);
        printf("Loaded %d account(s) from file.\n", *accountCount);
    } else {
        printf("No existing accounts found. You can create a new account.\n");
    }
}
