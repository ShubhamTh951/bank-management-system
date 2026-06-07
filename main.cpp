#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// Base Class (Abstract)
class Account {
protected:
    std::string accountNumber;
    std::string ownerName;
    double balance;
    double interestRate;

public:
    Account(std::string accNum, std::string owner, double bal, double rate)
        : accountNumber(accNum), ownerName(owner), balance(bal), interestRate(rate) {}

    virtual ~Account() = default;

    // Pure virtual function 
    virtual void displayInfo() const = 0;
    virtual std::string getAccountType() const = 0;
    virtual bool withdraw(double amount) = 0;

    // Common functions for all accounts
    virtual void deposit(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid deposit amount!" << std::endl;
        return;
    }

    balance += amount;
    std::cout << "Deposited $" << amount
              << ". New balance: $" << balance << std::endl;
    }

    virtual void calculateInterest() {
        double interest = balance * (interestRate / 100);
        balance += interest;
         std::cout << "Interest added: $" << interest << std::endl;
    }

    // Getters
    std::string getAccountNumber() const { return accountNumber; }
    std::string getOwnerName() const { return ownerName; }
    double getBalance() const { return balance; }
    double getInterestRate() const { return interestRate; }
};

// Derived Classes
class SavingsAccount : public Account {
private:
    double minimumBalance;
    int withdrawalLimit;
    int withdrawalsThisMonth;

public:
    SavingsAccount(std::string accNum, std::string owner, double bal, double minBal = 500.0)
        : Account(accNum, owner, bal, 4.5), minimumBalance(minBal), withdrawalLimit(6), withdrawalsThisMonth(0) {}

    void displayInfo() const override {
        std::cout << "\n💰 SAVINGS ACCOUNT" << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Owner: " << ownerName << std::endl;
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "Interest Rate: " << interestRate << "%" << std::endl;
        std::cout << "Minimum Balance: $" << minimumBalance << std::endl;
        std::cout << "Withdrawals this month: " << withdrawalsThisMonth << "/" << withdrawalLimit << std::endl;
    }

    std::string getAccountType() const override {
        return "Saving";
    }

    bool withdraw(double amount) override {
        if (withdrawalsThisMonth >= withdrawalLimit) {
            std::cout << "Withdrawal limit exceeded for this month!" << std::endl;
            return false;
        }

        if (amount <= 0) {
            std::cout << "Invalid amount!" << std::endl;
            return false;
        }

        if ((balance - amount) < minimumBalance) {
            std::cout << "Insufficient funds! Minimum balance required: $" << minimumBalance << std::endl;
            return false;
        }

        balance -= amount;
        withdrawalsThisMonth++;
        std::cout << "Withdrew $" << amount << ". Remaining balance: $" << balance << std::endl;
        return true;
    }

    void resetMonthWithdrawals() {
        withdrawalsThisMonth = 0;
        std::cout << "Monthly withdrawal limit reset." << std::endl;
    }
};

class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(std::string accNum, std::string owner, double bal, double overdraft = 1000.0)
        : Account(accNum, owner, bal, 1.5), overdraftLimit(overdraft) {}

    void displayInfo() const override {
        std::cout << "\nCHECKING ACCOUNT" << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Owner: " << ownerName << std::endl;
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "Interest Rate: " << interestRate << "%" << std::endl;
        std::cout << "Overdraft Limit: $" << overdraftLimit << std::endl;
        if (balance < 0) {
            std::cout << "OVERDRAWN: $" << -balance << std::endl;
        }
    }

    std::string getAccountType() const override {
        return "Checking";
    }

    bool withdraw(double amount) override {
        if (amount <= 0) {
            std::cout << "Invalid amount!" << std::endl;
            return false;
        }

        double finalBalance = balance - amount;

        // Apply overdraft fee if account becomes negative
        if (finalBalance < 0) {
            finalBalance -= 25;
        }

        if (finalBalance < -overdraftLimit) {
            std::cout << "Overdraft limit exceeded! Max overdraft: $"
                      << overdraftLimit << std::endl;
            return false;
        }

        balance -= amount;

        if (balance < 0) {
            std::cout << "Withdrew $" << amount
                      << ". Account overdrawn by: $" << -balance << std::endl;

            std::cout << "Overdraft fee: $25 applied." << std::endl;
            balance -= 25;
        }

        else {
            std::cout << "Withdrew $" << amount
                      << ". Remaining balance: $" << balance << std::endl;
        }

        return true;
    }
};

class BusinessAccount : public Account {
private:
    double monthlyTransactionFee;
    int freeTransactions;
    int transactionCount;
    
public:
    BusinessAccount(std::string accNum, std::string owner, double bal)
        : Account(accNum, owner, bal, 2.0), monthlyTransactionFee(2.0), freeTransactions(50), transactionCount(0) {}

    void displayInfo() const override {
        std::cout << "\nBUSINESS ACCOUNT" << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Owner: " << ownerName << std::endl;
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "Interest Rate: " << interestRate << "%" << std::endl;
        std::cout << "Transactions this month: " << transactionCount << std::endl;
        std::cout << "Free transactions remaining: " << (freeTransactions - transactionCount) << std::endl;
    }

    std::string getAccountType() const override {
        return "Business";
    }

    bool withdraw(double amount) override {
        if (amount <= 0) {
            std::cout << "Invalid amount!" << std::endl;
            return false;
        }
        
        if (amount > balance) {
            std::cout << "Insufficient funds!" << std::endl;
            return false;
        }
        
        // Apply transaction fee if exceeded free limit
        if (transactionCount >= freeTransactions) {
            balance -= monthlyTransactionFee;
            std::cout << "Transaction fee applied: $" << monthlyTransactionFee << std::endl;
        }
        
        balance -= amount;
        transactionCount++;
        std::cout << "Withdrew $" << amount << ". Remaining balance: $" << balance << std::endl;
        return true;
    }

    void deposit(double amount) override {
    if (amount <= 0) {
        std::cout << "Invalid deposit amount!" << std::endl;
        return;
    }

    if (transactionCount >= freeTransactions) {
        balance -= monthlyTransactionFee;
        std::cout << "Transaction fee applied: $"
                  << monthlyTransactionFee << std::endl;
    }

    balance += amount;
    transactionCount++;
    std::cout << "Deposited $" << amount
              << ". New balance: $" << balance << std::endl;
}
    
    void resetMonthlyTransactions() {
        transactionCount = 0;
        std::cout << "Monthly transaction count reset." << std::endl;
    }
};

// Bank Management System
class BankSystem {
private:
    std::vector<Account*> accounts;

    Account* findAccount(const std::string& accountNumber) {
        for (auto* account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account;
            }
        }
        return nullptr;
    }

public:
    ~BankSystem() {
        for (auto* account : accounts) {
            delete account;
        }
    }

    // Function to check if account number exists
    bool accountExists(const std::string& accountNumber) {
        return findAccount(accountNumber) != nullptr;
    }

    void createSavingsAccount(std::string accNum, std::string owner, double initialBalance) {
        if(accountExists(accNum)) {
            std::cout << "Error: Account number " << accNum << " already exists!" << std::endl;
            std::cout << "Please choose a different account number." << std::endl;
            return;
        }

        if(initialBalance < 0) {
            std::cout << "Initial balance cannot be negative!"
                    << std::endl;
            return;
        }
        
        accounts.push_back(new SavingsAccount(accNum, owner, initialBalance));
        std::cout << "Savings account " << accNum << " created for " << owner << std::endl;
    }

    void createCheckingAccount(std::string accNum, std::string owner, double initialBalance) {
        if (accountExists(accNum)) {
            std::cout << "Error: Account number " << accNum << " already exists!" << std::endl;
            std::cout << "Please choose a different account number." << std::endl;
            return;
        }

        if(initialBalance < 0) {
            std::cout << "Initial balance cannot be negative!"
                    << std::endl;
            return;
        }

        accounts.push_back(new CheckingAccount(accNum, owner, initialBalance));
        std::cout << "Checking account " << accNum << " created for " << owner << std::endl;
    }
    
    void createBusinessAccount(std::string accNum, std::string owner, double initialBalance) {
        if (accountExists(accNum)) {
            std::cout << "Error: Account number " << accNum << " already exists!" << std::endl;
            std::cout << "Please choose a different account number." << std::endl;
            return;
        }

        if(initialBalance < 0) {
            std::cout << "Initial balance cannot be negative!"
                    << std::endl;
            return;
        }
        
        accounts.push_back(new BusinessAccount(accNum, owner, initialBalance));
        std::cout << "Business account " << accNum << " created for " << owner << std::endl;
    }

    void deposit(std::string accNum, double amount) {
        Account* account = findAccount(accNum);
        if (account) {
            account->deposit(amount);
        }
        else {
            std::cout << "Account not found!" << std::endl;
        }
    }

    void withdraw(std::string accNum, double amount) {
        Account* account = findAccount(accNum);
        if (account) {
            account->withdraw(amount);  // Polymorphic call - different behavior for each type
        } else {
            std::cout << "Account not found!" << std::endl;
        }
    }

    void transfer(std::string fromAcc, std::string toAcc, double amount) {
        Account* from = findAccount(fromAcc);
        Account* to = findAccount(toAcc);
        if (!from || !to) {
            std::cout << "One or both accounts not found!" << std::endl;
            return;
        }

        if (from->withdraw(amount)) {
            to->deposit(amount);
            std::cout << "Transfer completed from " << fromAcc << " to " << toAcc << std::endl;
        }
    }

    void displayAccount(std::string accNum) {
        Account* account = findAccount(accNum);
        if (account) {
            account->displayInfo();
        }
        else {
            std::cout << "Account not found!" << std::endl;
        }
    }

    void displayAllAccounts() {
        std::cout << "\n========== ALL ACCOUNTS ==========" << std::endl;
        for (const auto* account : accounts) {
            account->displayInfo();
            std::cout << "--------------------------------" << std::endl;
        }
    }

    void calculateInterestForAll() {
        std::cout << "\n========== CALCULATING INTEREST ==========" << std::endl;
        for (auto* account : accounts) {
            std::cout << "Account: " << account->getAccountNumber() << " - ";
            account->calculateInterest();
        }
    }

    void getBankStatistics() {
        double totalMoney = 0;
        int savingCount = 0, checkingCount = 0, businessCount = 0;

        for (const auto* account : accounts) {
            totalMoney += account->getBalance();

            std::string type = account->getAccountType();
            if (type == "Saving") savingCount++;
            else if (type == "Checking") checkingCount++;
            else if (type == "Business") businessCount++;
        }

        std::cout << "\n========== BANK STATISTICS ==========" << std::endl;
        std::cout << "Total Accounts: " << accounts.size() << std::endl;
        std::cout << "Savings Accounts: " << savingCount << std::endl;
        std::cout << "Checking Accounts: " << checkingCount << std::endl;
        std::cout << "Business Accounts: " << businessCount << std::endl;
        std::cout << "Total Money in Bank: $" << std::fixed << std::setprecision(2) << totalMoney << std::endl;
    }
};

// MENU SYSTEM
void showMenu() {
    std::cout << "\n========== BANK MANAGEMENT SYSTEM ==========";
    std::cout << "\n1. Create Savings Account";
    std::cout << "\n2. Create Checking Account";
    std::cout << "\n3. Create Business Account";
    std::cout << "\n4. Deposit Money";
    std::cout << "\n5. Withdraw Money";
    std::cout << "\n6. Transfer Money";
    std::cout << "\n7. Display Account";
    std::cout << "\n8. Display All Accounts";
    std::cout << "\n9. Calculate Interest (All Accounts)";
    std::cout << "\n10. Bank Statistics";
    std::cout << "\n0. Exit";
    std::cout << "\nChoose option: ";
}

int main() {
    BankSystem bank;
    int choice;

    std::cout << "Welcome to Bank Management System!" << std::endl;
    std::cout << "Setting up sample accounts with duplicate ID protection..." << std::endl;
    
    // Sample accounts for testing
    bank.createSavingsAccount("SAV001", "Alice Johnson", 5000.0);
    bank.createCheckingAccount("CHK001", "Bob Smith", 2000.0);
    bank.createBusinessAccount("BUS001", "TechCorp Ltd", 50000.0);
    
    // Test duplicate prevention
    std::cout << "\n--- Testing Duplicate Account Prevention ---" << std::endl;
    bank.createSavingsAccount("SAV001", "John Doe", 1000.0);   // Should fail!
    bank.createCheckingAccount("CHK001", "Jane Doe", 500.0);   // Should fail!
    std::cout << "--- End of duplicate test ---\n" << std::endl;

    do {
        showMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                std::string accNum, owner;
                double balance;
                std::cout << "Enter account number: "; std::cin >> accNum;
                std::cout << "Enter owner name: "; std::cin.ignore(); std::getline(std::cin, owner);
                std::cout << "Enter initial balance: "; std::cin >> balance;
                bank.createSavingsAccount(accNum, owner, balance);
                break;
            }
            case 2: {
                std::string accNum, owner;
                double balance;
                std::cout << "Enter account number: "; std::cin >> accNum;
                std::cout << "Enter owner name: "; std::cin.ignore(); std::getline(std::cin, owner);
                std::cout << "Enter initial balance: "; std::cin >> balance;
                bank.createCheckingAccount(accNum, owner, balance);
                break;
            }
            case 3: {
                std::string accNum, owner;
                double balance;
                std::cout << "Enter account number: "; std::cin >> accNum;
                std::cout << "Enter owner name: "; std::cin.ignore(); std::getline(std::cin, owner);
                std::cout << "Enter initial balance: "; std::cin >> balance;
                bank.createBusinessAccount(accNum, owner, balance);
                break;
            }
            case 4: {
                std::string accNum;
                double amount;
                std::cout << "Enter account number: "; std::cin >> accNum;
                std::cout << "Enter amount to deposit: "; std::cin >> amount;
                bank.deposit(accNum, amount);
                break;
            }
            case 5: {
                std::string accNum;
                double amount;
                std::cout << "Enter account number: "; std::cin >> accNum;
                std::cout << "Enter amount to withdraw: "; std::cin >> amount;
                bank.withdraw(accNum, amount);
                break;
            }
            case 6: {
                std::string fromAcc, toAcc;
                double amount;
                std::cout << "Enter source account: "; std::cin >> fromAcc;
                std::cout << "Enter destination account: "; std::cin >> toAcc;
                std::cout << "Enter amount to transfer: "; std::cin >> amount;
                bank.transfer(fromAcc, toAcc, amount);
                break;
            }
            case 7: {
                std::string accNum;
                std::cout << "Enter account number: "; std::cin >> accNum;
                bank.displayAccount(accNum);
                break;
            }
            case 8:
                bank.displayAllAccounts();
                break;
            case 9:
                bank.calculateInterestForAll();
                break;
            case 10:
                bank.getBankStatistics();
                break;
            case 0:
                std::cout << "Thank you for using our banking system!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;    
        }

        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(); std::cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}