#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define DATA_FILE    "accounts.txt"
#define TEMP_FILE    "temp.txt"

#define MAX_NAME_LEN     50
#define MAX_SURNAME_LEN  50
#define MAX_ADDRESS_LEN 100
#define PESEL_LEN       11
#define BUFFER_SIZE     256

typedef struct {
    int    accountNumber;
    char   name[MAX_NAME_LEN];
    char   surname[MAX_SURNAME_LEN];
    char   address[MAX_ADDRESS_LEN];
    char   pesel[PESEL_LEN + 1];
    double balance;
    double loanBalance;
} Account;

void    clearInputBuffer(void);
void    readString(const char *prompt, char *buffer, int maxLen);
int     readInt(const char *prompt);
double  readDouble(const char *prompt);
char    readYesNo(const char *prompt);

bool    isValidPesel(const char *peselInput);

int     generateAccountNumber(void);
bool    parseAccountLine(const char *line, Account *accOut);
void    formatAccountLine(const Account *acc, char *outLine, int maxLen);

void    createAccount(void);
void    listAllAccounts(void);
void    searchAccount(void);
void    makeDeposit(void);
void    makeWithdrawal(void);
void    makeTransfer(void);
void    takeLoan(void);
void    payDebt(void);

void    printMainMenu(void);

int main(void) {
    int choice;
    do {
        printMainMenu();
        choice = readInt("Enter your choice: ");
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                listAllAccounts();
                break;
            case 3:
                searchAccount();
                break;
            case 4:
                makeDeposit();
                break;
            case 5:
                makeWithdrawal();
                break;
            case 6:
                makeTransfer();
                break;
            case 7:
                takeLoan();
                break;
            case 8:
                payDebt();
                break;
            case 9:
                printf("Exiting... Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 9.\n");
        }
        printf("\n");
    } while (choice != 9);
    return 0;
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        ;
    }
}

void readString(const char *prompt, char *buffer, int maxLen) {
    while (true) {
        printf("%s", prompt);
        if (fgets(buffer, maxLen, stdin) == NULL) {
            clearInputBuffer();
            continue;
        }
        size_t len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        } else {
            clearInputBuffer();
        }

        if (len == 0) {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }
        return;
    }
}

int readInt(const char *prompt) {
    char buffer[BUFFER_SIZE];
    char *endPtr;
    long value;
    while (true) {
        readString(prompt, buffer, BUFFER_SIZE);
        value = strtol(buffer, &endPtr, 10);
        if (endPtr == buffer || *endPtr != '\0') {
            printf("Invalid integer. Please enter a valid number.\n");
            continue;
        }
        return (int)value;
    }
}

double readDouble(const char *prompt) {
    char buffer[BUFFER_SIZE];
    char *endPtr;
    double value;
    while (true) {
        readString(prompt, buffer, BUFFER_SIZE);
        value = strtod(buffer, &endPtr);
        if (endPtr == buffer || *endPtr != '\0') {
            printf("Invalid number. Please enter a valid numeric value.\n");
            continue;
        }
        return value;
    }
}

char readYesNo(const char *prompt) {
    char buffer[BUFFER_SIZE];
    while (true) {
        readString(prompt, buffer, BUFFER_SIZE);
        if (strlen(buffer) == 1) {
            char c = toupper(buffer[0]);
            if (c == 'Y' || c == 'N') {
                return c;
            }
        }
        printf("Please enter 'Y' for yes or 'N' for no.\n");
    }
}

bool isValidPesel(const char *peselInput) {
    if (strlen(peselInput) != PESEL_LEN) {
        return false;
    }
    for (int i = 0; i < PESEL_LEN; i++) {
        if (!isdigit((unsigned char)peselInput[i])) {
            return false;
        }
    }
    return true;
}

int generateAccountNumber(void) {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        return 1000;
    }
    char line[BUFFER_SIZE];
    int maxNumber = 999;
    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        Account tempAcc;
        if (parseAccountLine(line, &tempAcc)) {
            if (tempAcc.accountNumber > maxNumber) {
                maxNumber = tempAcc.accountNumber;
            }
        }
    }
    fclose(file);
    return maxNumber + 1;
}

bool parseAccountLine(const char *line, Account *accOut) {
    if (line == NULL || accOut == NULL) {
        return false;
    }
    char buffer[BUFFER_SIZE];
    strncpy(buffer, line, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';
    char *token;
    int fieldIndex = 0;
    token = strtok(buffer, ";");
    while (token != NULL) {
        switch (fieldIndex) {
            case 0:
                accOut->accountNumber = atoi(token);
                break;
            case 1:
                strncpy(accOut->name, token, MAX_NAME_LEN - 1);
                accOut->name[MAX_NAME_LEN - 1] = '\0';
                break;
            case 2:
                strncpy(accOut->surname, token, MAX_SURNAME_LEN - 1);
                accOut->surname[MAX_SURNAME_LEN - 1] = '\0';
                break;
            case 3:
                strncpy(accOut->address, token, MAX_ADDRESS_LEN - 1);
                accOut->address[MAX_ADDRESS_LEN - 1] = '\0';
                break;
            case 4:
                strncpy(accOut->pesel, token, PESEL_LEN);
                accOut->pesel[PESEL_LEN] = '\0';
                break;
            case 5:
                accOut->balance = atof(token);
                break;
            case 6:
                accOut->loanBalance = atof(token);
                break;
            default:
                break;
        }
        fieldIndex++;
        token = strtok(NULL, ";");
    }
    return (fieldIndex >= 7);
}

void formatAccountLine(const Account *acc, char *outLine, int maxLen) {
    snprintf(outLine, maxLen, "%d;%s;%s;%s;%s;%.2f;%.2f\n",
             acc->accountNumber,
             acc->name,
             acc->surname,
             acc->address,
             acc->pesel,
             acc->balance,
             acc->loanBalance);
}

void createAccount(void) {
    printf("=== Create New Account ===\n");
    Account newAccount;
    char peselBuffer[PESEL_LEN + 1];

    newAccount.accountNumber = generateAccountNumber();
    printf("Assigned Account Number: %d\n", newAccount.accountNumber);

    readString("Enter customer's first name: ", newAccount.name, MAX_NAME_LEN);
    readString("Enter customer's surname: ", newAccount.surname, MAX_SURNAME_LEN);
    readString("Enter customer's address: ", newAccount.address, MAX_ADDRESS_LEN);

    while (true) {
        readString("Enter customer's PESEL (11 digits): ", peselBuffer, PESEL_LEN + 1);
        if (isValidPesel(peselBuffer)) {
            strncpy(newAccount.pesel, peselBuffer, PESEL_LEN);
            newAccount.pesel[PESEL_LEN] = '\0';
            break;
        } else {
            printf("Invalid PESEL. PESEL must be exactly 11 digits (numbers only). Please try again.\n");
        }
    }

    newAccount.balance = readDouble("Enter initial balance for this account: ");
    if (newAccount.balance < 0) {
        printf("Initial balance cannot be negative. Setting to 0.00\n");
        newAccount.balance = 0.00;
    }
    newAccount.loanBalance = 0.00;

    printf("\nPlease confirm the following details:\n");
    printf("Account Number : %d\n", newAccount.accountNumber);
    printf("Name           : %s %s\n", newAccount.name, newAccount.surname);
    printf("Address        : %s\n", newAccount.address);
    printf("PESEL          : %s\n", newAccount.pesel);
    printf("Initial Balance: %.2f\n", newAccount.balance);
    printf("Loan Balance   : %.2f\n", newAccount.loanBalance);

    char confirm = readYesNo("Confirm create account? (Y/N): ");
    if (confirm != 'Y') {
        printf("Account creation canceled.\n");
        return;
    }

    FILE *file = fopen(DATA_FILE, "a");
    if (file == NULL) {
        perror("Error opening data file for writing");
        return;
    }
    char lineOut[BUFFER_SIZE];
    formatAccountLine(&newAccount, lineOut, BUFFER_SIZE);
    fputs(lineOut, file);
    fclose(file);

    printf("Account successfully created with account number %d.\n", newAccount.accountNumber);
}

void listAllAccounts(void) {
    printf("=== List All Accounts ===\n");
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("No accounts found. (Data file does not exist or is empty.)\n");
        return;
    }
    printf("%-10s | %-15s | %-15s | %-20s | %-11s | %-12s | %-12s\n",
           "Acct Num", "Name", "Surname", "Address", "PESEL",
           "Balance", "Loan Bal");
    printf("-----------------------------------------------------------------------------------------------\n");
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        Account acc;
        if (parseAccountLine(line, &acc)) {
            printf("%-10d | %-15s | %-15s | %-20s | %-11s | %12.2f | %12.2f\n",
                   acc.accountNumber,
                   acc.name,
                   acc.surname,
                   acc.address,
                   acc.pesel,
                   acc.balance,
                   acc.loanBalance);
        }
    }
    fclose(file);
}

void searchAccount(void) {
    printf("=== Search for Account ===\n");
    printf("Search by:\n");
    printf("  1. Account Number\n");
    printf("  2. Name\n");
    printf("  3. Surname\n");
    printf("  4. Address\n");
    printf("  5. PESEL\n");
    int criterion = readInt("Enter the number corresponding to the search field: ");

    int   searchAccNum = 0;
    char  searchString[MAX_ADDRESS_LEN];
    char  searchPesel[PESEL_LEN + 1];

    switch (criterion) {
        case 1:
            searchAccNum = readInt("Enter the account number to search for: ");
            break;
        case 2:
            readString("Enter the first name to search for: ", searchString, MAX_NAME_LEN);
            break;
        case 3:
            readString("Enter the surname to search for: ", searchString, MAX_SURNAME_LEN);
            break;
        case 4:
            readString("Enter the address (or part of it) to search for: ", searchString, MAX_ADDRESS_LEN);
            break;
        case 5:
            while (true) {
                readString("Enter the PESEL (11 digits) to search for: ", searchPesel, PESEL_LEN + 1);
                if (isValidPesel(searchPesel)) {
                    break;
                }
                printf("Invalid PESEL format. Please try again.\n");
            }
            break;
        default:
            printf("Invalid choice. Returning to main menu.\n");
            return;
    }

    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("No accounts found. (Data file does not exist or is empty.)\n");
        return;
    }

    bool foundAny = false;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        Account acc;
        if (!parseAccountLine(line, &acc)) {
            continue;
        }
        bool match = false;
        switch (criterion) {
            case 1:
                if (acc.accountNumber == searchAccNum) {
                    match = true;
                }
                break;
            case 2:
                if (strcasecmp(acc.name, searchString) == 0) {
                    match = true;
                }
                break;
            case 3:
                if (strcasecmp(acc.surname, searchString) == 0) {
                    match = true;
                }
                break;
            case 4:
                if (strstr(acc.address, searchString) != NULL) {
                    match = true;
                }
                break;
            case 5:
                if (strcmp(acc.pesel, searchPesel) == 0) {
                    match = true;
                }
                break;
            default:
                break;
        }
        if (match) {
            if (!foundAny) {
                printf("\n%-10s | %-15s | %-15s | %-20s | %-11s | %-12s | %-12s\n",
                       "Acct Num", "Name", "Surname", "Address", "PESEL",
                       "Balance", "Loan Bal");
                printf("-----------------------------------------------------------------------------------------------\n");
            }
            foundAny = true;
            printf("%-10d | %-15s | %-15s | %-20s | %-11s | %12.2f | %12.2f\n",
                   acc.accountNumber,
                   acc.name,
                   acc.surname,
                   acc.address,
                   acc.pesel,
                   acc.balance,
                   acc.loanBalance);
        }
    }

    fclose(file);

    if (!foundAny) {
        printf("No matching accounts found.\n");
    }
}

void makeDeposit(void) {
    printf("=== Make a Deposit ===\n");
    int targetAccNum = readInt("Enter the account number to deposit into: ");
    double depositAmount = readDouble("Enter the deposit amount: ");

    if (depositAmount <= 0) {
        printf("Deposit amount must be positive. Operation cancelled.\n");
        return;
    }

    printf("You are depositing %.2f into account %d.\n", depositAmount, targetAccNum);
    char confirm = readYesNo("Proceed? (Y/N): ");
    if (confirm != 'Y') {
        printf("Deposit cancelled.\n");
        return;
    }

    FILE *inFile = fopen(DATA_FILE, "r");
    if (inFile == NULL) {
        printf("Data file not found. No accounts to update.\n");
        return;
    }
    FILE *outFile = fopen(TEMP_FILE, "w");
    if (outFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(inFile);
        return;
    }

    bool updated = false;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, inFile) != NULL) {
        Account acc;
        if (parseAccountLine(line, &acc)) {
            if (acc.accountNumber == targetAccNum) {
                acc.balance += depositAmount;
                updated = true;
            }
            char newLine[BUFFER_SIZE];
            formatAccountLine(&acc, newLine, BUFFER_SIZE);
            fputs(newLine, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

    if (!updated) {
        remove(TEMP_FILE);
        printf("Account number %d not found. Deposit not applied.\n", targetAccNum);
    } else {
        remove(DATA_FILE);
        rename(TEMP_FILE, DATA_FILE);
        printf("Deposit successful. Updated balance has been saved.\n");
    }
}

void makeWithdrawal(void) {
    printf("=== Make a Withdrawal ===\n");
    int targetAccNum = readInt("Enter the account number to withdraw from: ");
    double withdrawAmount = readDouble("Enter the withdrawal amount: ");

    if (withdrawAmount <= 0) {
        printf("Withdrawal amount must be positive. Operation cancelled.\n");
        return;
    }

    FILE *checkFile = fopen(DATA_FILE, "r");
    if (checkFile == NULL) {
        printf("Data file not found. No accounts to check.\n");
        return;
    }
    bool foundAccount = false;
    double currentBalance = 0.0;
    char lineCheck[BUFFER_SIZE];
    while (fgets(lineCheck, BUFFER_SIZE, checkFile) != NULL) {
        Account tempAcc;
        if (parseAccountLine(lineCheck, &tempAcc) && tempAcc.accountNumber == targetAccNum) {
            foundAccount = true;
            currentBalance = tempAcc.balance;
            break;
        }
    }
    fclose(checkFile);

    if (!foundAccount) {
        printf("Account number %d not found. Withdrawal cancelled.\n", targetAccNum);
        return;
    }
    if (withdrawAmount > currentBalance) {
        printf("Insufficient funds. Current balance: %.2f. Withdrawal cancelled.\n", currentBalance);
        return;
    }

    printf("You are withdrawing %.2f from account %d (current balance: %.2f).\n",
           withdrawAmount, targetAccNum, currentBalance);
    char confirm = readYesNo("Proceed? (Y/N): ");
    if (confirm != 'Y') {
        printf("Withdrawal cancelled.\n");
        return;
    }

    FILE *inFile = fopen(DATA_FILE, "r");
    if (inFile == NULL) {
        printf("Data file not found. No accounts to update.\n");
        return;
    }
    FILE *outFile = fopen(TEMP_FILE, "w");
    if (outFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(inFile);
        return;
    }

    bool updated = false;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, inFile) != NULL) {
        Account acc;
        if (parseAccountLine(line, &acc)) {
            if (acc.accountNumber == targetAccNum) {
                acc.balance -= withdrawAmount;
                updated = true;
            }
            char newLine[BUFFER_SIZE];
            formatAccountLine(&acc, newLine, BUFFER_SIZE);
            fputs(newLine, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

    if (!updated) {
        remove(TEMP_FILE);
        printf("Unexpected error: account was found earlier but not updated. No changes made.\n");
    } else {
        remove(DATA_FILE);
        rename(TEMP_FILE, DATA_FILE);
        printf("Withdrawal successful. Updated balance has been saved.\n");
    }
}

void makeTransfer(void) {
    printf("=== Transfer Money Between Accounts ===\n");
    int sourceAccNum = readInt("Enter the source account number: ");
    int destAccNum   = readInt("Enter the destination account number: ");
    if (sourceAccNum == destAccNum) {
        printf("Source and destination accounts must be different. Operation cancelled.\n");
        return;
    }
    double transferAmount = readDouble("Enter the transfer amount: ");

    if (transferAmount <= 0) {
        printf("Transfer amount must be positive. Operation cancelled.\n");
        return;
    }

    FILE *checkFile = fopen(DATA_FILE, "r");
    if (checkFile == NULL) {
        printf("Data file not found. No accounts to check.\n");
        return;
    }
    bool foundSource = false, foundDest = false;
    double sourceBalance = 0.0, destBalance = 0.0;
    char lineCheck[BUFFER_SIZE];
    while (fgets(lineCheck, BUFFER_SIZE, checkFile) != NULL) {
        Account tempAcc;
        if (!parseAccountLine(lineCheck, &tempAcc)) {
            continue;
        }
        if (tempAcc.accountNumber == sourceAccNum) {
            foundSource = true;
            sourceBalance = tempAcc.balance;
        }
        if (tempAcc.accountNumber == destAccNum) {
            foundDest = true;
            destBalance = tempAcc.balance;
        }
        if (foundSource && foundDest) { break; }
    }
    fclose(checkFile);

    if (!foundSource) {
        printf("Source account %d not found. Transfer cancelled.\n", sourceAccNum);
        return;
    }
    if (!foundDest) {
        printf("Destination account %d not found. Transfer cancelled.\n", destAccNum);
        return;
    }
    if (transferAmount > sourceBalance) {
        printf("Insufficient funds in source account (balance: %.2f). Transfer cancelled.\n", sourceBalance);
        return;
    }

    printf("You are transferring %.2f from account %d (current balance: %.2f) to account %d (current balance: %.2f).\n",
           transferAmount, sourceAccNum, sourceBalance, destAccNum, destBalance);
    char confirm = readYesNo("Proceed? (Y/N): ");
    if (confirm != 'Y') {
        printf("Transfer cancelled.\n");
        return;
    }

    FILE *inFile = fopen(DATA_FILE, "r");
    if (inFile == NULL) {
        printf("Data file not found. No accounts to update.\n");
        return;
    }
    FILE *outFile = fopen(TEMP_FILE, "w");
    if (outFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(inFile);
        return;
    }

    bool updatedSource = false, updatedDest = false;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, inFile) != NULL) {
        Account acc;
        if (parseAccountLine(line, &acc)) {
            if (acc.accountNumber == sourceAccNum) {
                acc.balance -= transferAmount;
                updatedSource = true;
            } else if (acc.accountNumber == destAccNum) {
                acc.balance += transferAmount;
                updatedDest = true;
            }
            char newLine[BUFFER_SIZE];
            formatAccountLine(&acc, newLine, BUFFER_SIZE);
            fputs(newLine, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

    if (!(updatedSource && updatedDest)) {
        remove(TEMP_FILE);
        printf("Unexpected error: accounts were found earlier but not updated. No changes made.\n");
    } else {
        remove(DATA_FILE);
        rename(TEMP_FILE, DATA_FILE);
        printf("Transfer successful. Updated balances have been saved.\n");
    }
}

void takeLoan(void) {
    printf("=== Take a Loan ===\n");
    int targetAccNum = readInt("Enter the account number to take a loan: ");
    double loanAmount   = readDouble("Enter the loan amount: ");
    if (loanAmount <= 0) {
        printf("Loan amount must be positive. Operation cancelled.\n");
        return;
    }
    double interestRate = readDouble("Enter the interest rate (as percentage, e.g., 5.5 for 5.5%%): ");
    if (interestRate < 0) {
        printf("Interest rate cannot be negative. Operation cancelled.\n");
        return;
    }

    printf("You are taking a loan of %.2f with %.2f%% interest for account %d.\n",
           loanAmount, interestRate, targetAccNum);
    char confirm = readYesNo("Proceed? (Y/N): ");
    if (confirm != 'Y') {
        printf("Loan operation canceled.\n");
        return;
    }

    FILE *inFile = fopen(DATA_FILE, "r");
    if (inFile == NULL) {
        printf("Data file not found. No accounts to update.\n");
        return;
    }
    FILE *outFile = fopen(TEMP_FILE, "w");
    if (outFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(inFile);
        return;
    }

    bool updated = false;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, inFile) != NULL) {
        Account acc;
        if (parseAccountLine(line, &acc)) {
            if (acc.accountNumber == targetAccNum) {
                double interestAmount = loanAmount * (interestRate / 100.0);
                double totalLoan = loanAmount + interestAmount;
                acc.balance += loanAmount;
                acc.loanBalance += totalLoan;
                updated = true;
            }
            char newLine[BUFFER_SIZE];
            formatAccountLine(&acc, newLine, BUFFER_SIZE);
            fputs(newLine, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

    if (!updated) {
        remove(TEMP_FILE);
        printf("Account number %d not found. Loan not applied.\n", targetAccNum);
    } else {
        remove(DATA_FILE);
        rename(TEMP_FILE, DATA_FILE);
        printf("Loan successful. Loan amount disbursed and balances updated.\n");
    }
}

void payDebt(void) {
    printf("=== Pay Off Debt ===\n");
    int targetAccNum = readInt("Enter the account number to pay debt: ");
    double paymentAmount = readDouble("Enter the payment amount: ");
    if (paymentAmount <= 0) {
        printf("Payment amount must be positive. Operation cancelled.\n");
        return;
    }

    FILE *checkFile = fopen(DATA_FILE, "r");
    if (checkFile == NULL) {
        printf("Data file not found. No accounts to check.\n");
        return;
    }
    bool foundAccount = false;
    double currentBalance = 0.0, currentLoanBalance = 0.0;
    char lineCheck[BUFFER_SIZE];
    while (fgets(lineCheck, BUFFER_SIZE, checkFile) != NULL) {
        Account tempAcc;
        if (parseAccountLine(lineCheck, &tempAcc) && tempAcc.accountNumber == targetAccNum) {
            foundAccount = true;
            currentBalance = tempAcc.balance;
            currentLoanBalance = tempAcc.loanBalance;
            break;
        }
    }
    fclose(checkFile);

    if (!foundAccount) {
        printf("Account number %d not found. Operation canceled.\n", targetAccNum);
        return;
    }
    if (paymentAmount > currentBalance) {
        printf("Insufficient regular account balance (%.2f) to make this payment. Operation canceled.\n", currentBalance);
        return;
    }
    if (paymentAmount > currentLoanBalance) {
        printf("Payment amount (%.2f) exceeds loan balance (%.2f). Operation canceled.\n", paymentAmount, currentLoanBalance);
        return;
    }

    printf("You are paying %.2f towards debt for account %d (Balance: %.2f, Loan: %.2f).\n",
           paymentAmount, targetAccNum, currentBalance, currentLoanBalance);
    char confirm = readYesNo("Proceed? (Y/N): ");
    if (confirm != 'Y') {
        printf("Debt payment canceled.\n");
        return;
    }

    FILE *inFile = fopen(DATA_FILE, "r");
    if (inFile == NULL) {
        printf("Data file not found. No accounts to update.\n");
        return;
    }
    FILE *outFile = fopen(TEMP_FILE, "w");
    if (outFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(inFile);
        return;
    }

    bool updated = false;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, inFile) != NULL) {
        Account acc;
        if (parseAccountLine(line, &acc)) {
            if (acc.accountNumber == targetAccNum) {
                acc.balance    -= paymentAmount;
                acc.loanBalance -= paymentAmount;
                updated = true;
            }
            char newLine[BUFFER_SIZE];
            formatAccountLine(&acc, newLine, BUFFER_SIZE);
            fputs(newLine, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

    if (!updated) {
        remove(TEMP_FILE);
        printf("Unexpected error: account was found earlier but not updated. No changes made.\n");
    } else {
        remove(DATA_FILE);
        rename(TEMP_FILE, DATA_FILE);
        printf("Debt payment successful. Updated balances have been saved.\n");
    }
}

void printMainMenu(void) {
    printf("===== Bank Account Management System =====\n");
    printf("1.  Create new account\n");
    printf("2.  List all accounts\n");
    printf("3.  Search for an account\n");
    printf("4.  Make a deposit\n");
    printf("5.  Make a withdrawal\n");
    printf("6.  Transfer money between accounts\n");
    printf("7.  Take a loan and transfer to account\n");
    printf("8.  Pay debt from account\n");
    printf("9.  Exit\n");
    printf("==========================================\n");
}
