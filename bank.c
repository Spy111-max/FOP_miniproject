#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_TRANS 100

struct Transaction {
    char type[20];
    float amount;
};

struct Account {
    int accNumber;
    char name[50];
    float balance;
    struct Transaction transactions[MAX_TRANS];
    int transactionCount;
};

struct Account accounts[MAX];
int totalAccounts = 0;

void createAccount();
void deposit();
void withdraw();
void checkBalance();
void calculateInterest();
void showTransactions();
int findAccount(int accNo);

int main() {
    int choice;

    while (1) {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Show Transaction History\n");
        printf("6. Calculate Interest\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: showTransactions(); break;
            case 6: calculateInterest(); break;
            case 7: printf("Thank you for using our Bank!\n"); return 0;
            default: printf("Invalid Choice!\n");
        }
    }
    return 0;
}

int findAccount(int accNo) {
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accNumber == accNo)
            return i;
    }
    return -1;
}

void createAccount() {
    int accNo;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    if (findAccount(accNo) != -1) {
        printf("Account Number Already Exists!\n");
        return;
    }

    accounts[totalAccounts].accNumber = accNo;

    printf("Enter Name: ");
    scanf(" %[^\n]", accounts[totalAccounts].name);

    printf("Enter Initial Deposit: ");
    scanf("%f", &accounts[totalAccounts].balance);

    accounts[totalAccounts].transactionCount = 0;

    totalAccounts++;

    printf("Account Created Successfully!\n");
}

void deposit() {
    int accNo;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = findAccount(accNo);

    if (index == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    accounts[index].balance += amount;

    int t = accounts[index].transactionCount;

    strcpy(accounts[index].transactions[t].type, "Deposit");
    accounts[index].transactions[t].amount = amount;

    accounts[index].transactionCount++;

    printf("Amount Deposited Successfully!\n");
}

void withdraw() {
    int accNo;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = findAccount(accNo);

    if (index == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    if (accounts[index].balance < amount) {
        printf("Insufficient Balance!\n");
        return;
    }

    accounts[index].balance -= amount;

    int t = accounts[index].transactionCount;

    strcpy(accounts[index].transactions[t].type, "Withdraw");
    accounts[index].transactions[t].amount = amount;

    accounts[index].transactionCount++;

    printf("Amount Withdrawn Successfully!\n");
}

void checkBalance() {
    int accNo;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = findAccount(accNo);

    if (index == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Account Holder: %s\n", accounts[index].name);
    printf("Current Balance: %.2f\n", accounts[index].balance);
}

void showTransactions() {
    int accNo;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = findAccount(accNo);

    if (index == -1) {
        printf("Account Not Found!\n");
        return;
    }

    if (accounts[index].transactionCount == 0) {
        printf("No Transactions Yet.\n");
        return;
    }

    printf("\nTransaction History:\n");

    for (int i = 0; i < accounts[index].transactionCount; i++) {
        printf("%d. %s - %.2f\n",
               i + 1,
               accounts[index].transactions[i].type,
               accounts[index].transactions[i].amount);
    }
}

void calculateInterest() {
    int accNo;
    float rate, time, interest;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = findAccount(accNo);

    if (index == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter Interest Rate (%%): ");
    scanf("%f", &rate);

    printf("Enter Time (years): ");
    scanf("%f", &time);

    interest = (accounts[index].balance * rate * time) / 100;

    printf("Interest: %.2f\n", interest);
    printf("Total Amount After Interest: %.2f\n",
           accounts[index].balance + interest);
}

