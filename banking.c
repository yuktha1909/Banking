#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    char name[100];
    int accountNumber;
    float balance;
};

// Function Prototypes
void createAccount(struct Account *acc);
void deposit(struct Account *acc, float amount);
void withdraw(struct Account *acc, float amount);
void displayAccount(struct Account *acc);
void saveAccount(struct Account *acc);
void loadAccount(struct Account *acc, int accountNumber);
void recordTransaction(struct Account *acc, char *type, float amount);

// Main function
int main() {
    struct Account account;
    int choice;
    float amount;
    int accountNumber;

    while (1) {
        printf("\n1. Create Account\n2. Log In\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(&account);
                saveAccount(&account);
                break;
            case 2:
                printf("Enter account number to log in: ");
                scanf("%d", &accountNumber);
                loadAccount(&account, accountNumber);
                if (account.accountNumber != 0) {
                    while (1) {
                        printf("\n1. Deposit\n2. Withdraw\n3. Display Account\n4. Log Out\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                printf("Enter amount to deposit: ");
                                scanf("%f", &amount);
                                deposit(&account, amount);
                                recordTransaction(&account, "Deposit", amount);
                                saveAccount(&account);
                                break;
                            case 2:
                                printf("Enter amount to withdraw: ");
                                scanf("%f", &amount);
                                withdraw(&account, amount);
                                recordTransaction(&account, "Withdraw", amount);
                                saveAccount(&account);
                                break;
                            case 3:
                                displayAccount(&account);
                                break;
                            case 4:
                                printf("Logging out...\n");
                                goto END_SESSION;
                            default:
                                printf("Invalid choice.\n");
                        }
                    }
                }
            END_SESSION:
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

// Function to create a new account
void createAccount(struct Account *acc) {
    printf("Enter name: ");
    scanf("%s", acc->name);
    printf("Enter account number: ");
    scanf("%d", &acc->accountNumber);
    acc->balance = 0.0;
    printf("Account created successfully.\n");
}

// Function to deposit money
void deposit(struct Account *acc, float amount) {
    acc->balance += amount;
    printf("Deposited: $%.2f\n", amount);
}

// Function to withdraw money
void withdraw(struct Account *acc, float amount) {
    if (amount > acc->balance) {
        printf("Insufficient balance.\n");
    } else {
        acc->balance -= amount;
        printf("Withdrawn: $%.2f\n", amount);
    }
}

// Function to display account details
void displayAccount(struct Account *acc) {
    printf("\n--- Account Details ---\n");
    printf("Name: %s\n", acc->name);
    printf("Account Number: %d\n", acc->accountNumber);
    printf("Balance: $%.2f\n", acc->balance);
}

// Function to save account data to a file
void saveAccount(struct Account *acc) {
    FILE *file;
    char filename[20];

    sprintf(filename, "%d.txt", acc->accountNumber);
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error saving account.\n");
        return;
    }

    fwrite(acc, sizeof(struct Account), 1, file);
    fclose(file);
    printf("Account saved successfully.\n");
}

// Function to load account data from a file
void loadAccount(struct Account *acc, int accountNumber) {
    FILE *file;
    char filename[20];

    sprintf(filename, "%d.txt", accountNumber);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Account not found.\n");
        acc->accountNumber = 0; // Mark as invalid account
        return;
    }

    fread(acc, sizeof(struct Account), 1, file);
    fclose(file);
    printf("Account loaded successfully.\n");
}

// Function to record transaction history
void recordTransaction(struct Account *acc, char *type, float amount) {
    FILE *file;
    char filename[20];

    sprintf(filename, "%d_transactions.txt", acc->accountNumber);
    file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error recording transaction.\n");
        return;
    }

    fprintf(file, "%s: $%.2f\n", type, amount);
    fclose(file);
}   