#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <ctime>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
const std::string CURRENCY_SYMBOL = "\xE2\x82\xB9";
const std::string BANK_NAME = "ICICI BANK";

void configureSystemSettings()
{
    std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
}

void clearTerminal()
{
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

void systemSleep(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void waitForUser()
{
    std::cout << "\n[Press Enter to continue...]";
    std::cin.get();
}

void printHeader(const std::string &title)
{
    std::string fullTitle = BANK_NAME + " - " + title;
    int width = 50;
    int padding = 0;

    if (fullTitle.length() < width)
    {
        padding = (width - fullTitle.length()) / 2;
    }

    std::cout << "\n==================================================\n";
    std::cout << std::string(padding, ' ') << fullTitle << "\n";
    std::cout << "==================================================\n";
}

template <typename T>
T getSafeInput(const std::string &prompt)
{
    T value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            if (std::cin.peek() != '\n' && std::cin.peek() != EOF)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << ">> Invalid input format. Please try again.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        if (std::cin.eof())
            exit(0);

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << ">> Invalid input. Please enter a valid value.\n";
    }
}

struct TransactionRecord
{
    std::string type;
    double amount;
    std::string dateStr;

    TransactionRecord(std::string transactionType, double transactionAmount)
        : type(transactionType), amount(transactionAmount)
    {
        std::time_t now = std::time(nullptr);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", std::localtime(&now));
        dateStr = std::string(buffer);
    }
};

class BankAccount
{
private:
    std::string userId;
    std::string fullName;
    std::string pinCode;
    double currentBalance;
    bool isLocked;
    int failedLoginAttempts;
    std::vector<TransactionRecord> transactionHistory;

public:
    BankAccount(std::string id, std::string name, std::string pin, double initialBalance)
        : userId(id), fullName(name), pinCode(pin), currentBalance(initialBalance),
          isLocked(false), failedLoginAttempts(0) {}

    bool validatePin(const std::string &inputPin)
    {
        if (isLocked)
            return false;

        std::cout << ">> Verifying credentials...\n";
        systemSleep(800);

        if (inputPin == pinCode)
        {
            failedLoginAttempts = 0;
            return true;
        }

        failedLoginAttempts++;
        if (failedLoginAttempts >= 3)
        {
            isLocked = true;
        }
        return false;
    }

    bool getAccountStatus() const { return isLocked; }
    std::string getOwnerName() const { return fullName; }
    double getBalance() const { return currentBalance; }

    void depositFunds(double amount)
    {
        if (amount <= 0)
        {
            std::cout << ">> Error: Amount must be positive.\n";
            waitForUser();
            return;
        }

        std::cout << ">> Reading currency details...\n";
        systemSleep(1000);

        currentBalance += amount;
        transactionHistory.emplace_back("Credit", amount);

        std::cout << "\n>> Deposit Successful.\n";
        std::cout << ">> Added:       " << CURRENCY_SYMBOL << std::fixed << std::setprecision(2) << amount << "\n";
        std::cout << ">> New Balance: " << CURRENCY_SYMBOL << currentBalance << "\n";
        waitForUser();
    }

    void withdrawFunds(double amount)
    {
        if (amount <= 0)
        {
            std::cout << ">> Error: Invalid amount.\n";
            waitForUser();
            return;
        }

        if (amount > currentBalance)
        {
            std::cout << ">> Transaction Declined: Insufficient Funds.\n";
            waitForUser();
            return;
        }

        std::cout << ">> Processing withdrawal...\n";
        systemSleep(1000);
        std::cout << ">> Dispensing cash...\n";
        systemSleep(1000);

        currentBalance -= amount;
        transactionHistory.emplace_back("Debit", amount);

        std::cout << "\n>> Please collect your cash.\n";
        std::cout << ">> Withdrawn: " << CURRENCY_SYMBOL << std::fixed << std::setprecision(2) << amount << "\n";
        std::cout << ">> Remaining: " << CURRENCY_SYMBOL << currentBalance << "\n";
        waitForUser();
    }

    void showMiniStatement()
    {
        clearTerminal();
        printHeader("MINI STATEMENT");

        std::cout << "Customer: " << fullName << "\n";
        std::cout << "Balance : " << CURRENCY_SYMBOL << std::fixed << std::setprecision(2) << currentBalance << "\n\n";

        if (transactionHistory.empty())
        {
            std::cout << "No recent transactions available.\n";
        }
        else
        {
            std::cout << std::left << std::setw(20) << "Date" << std::setw(10) << "Type" << "Amount\n";
            std::cout << "--------------------------------------------------\n";

            int count = 0;
            for (auto it = transactionHistory.rbegin(); it != transactionHistory.rend(); ++it)
            {
                if (++count > 5)
                    break;
                std::cout << std::left << std::setw(20) << it->dateStr
                          << std::setw(10) << it->type
                          << CURRENCY_SYMBOL << it->amount << "\n";
            }
        }
        waitForUser();
    }
};

class AtmMachine
{
private:
    std::unordered_map<std::string, BankAccount> database;

public:
    void registerUser(std::string id, std::string name, std::string pin, double balance)
    {
        database.emplace(id, BankAccount(id, name, pin, balance));
    }

    void startService()
    {
        configureSystemSettings();

        while (true)
        {
            clearTerminal();
            printHeader("WELCOME");
            std::cout << "Please insert your card details below.\n\n";

            std::string userId = getSafeInput<std::string>("Enter User ID (or 'exit'): ");

            if (userId == "exit")
                break;

            if (database.find(userId) == database.end())
            {
                std::cout << ">> User not found. Please try again.\n";
                systemSleep(1500);
                continue;
            }

            BankAccount &activeAccount = database.at(userId);

            if (activeAccount.getAccountStatus())
            {
                std::cout << ">> ACCOUNT LOCKED due to multiple failed attempts.\n";
                std::cout << ">> Please visit the nearest branch.\n";
                waitForUser();
                continue;
            }

            std::string userPin = getSafeInput<std::string>("Enter 4-Digit PIN: ");

            if (activeAccount.validatePin(userPin))
            {
                runUserSession(activeAccount);
            }
            else
            {
                std::cout << ">> Incorrect PIN.\n";
                systemSleep(1500);
            }
        }
    }

    void runUserSession(BankAccount &account)
    {
        while (true)
        {
            clearTerminal();
            printHeader("MAIN MENU");
            std::cout << "Welcome, " << account.getOwnerName() << "\n\n";
            std::cout << "1. Check Balance\n";
            std::cout << "2. Deposit Cash\n";
            std::cout << "3. Withdraw Cash\n";
            std::cout << "4. Mini Statement\n";
            std::cout << "5. Logout\n";
            std::cout << "--------------------------------------------------\n";

            int selection = getSafeInput<int>("Select Option: ");

            switch (selection)
            {
            case 1:
                std::cout << "\n>> Available Balance: " << CURRENCY_SYMBOL
                          << std::fixed << std::setprecision(2) << account.getBalance() << "\n";
                waitForUser();
                break;
            case 2:
                account.depositFunds(getSafeInput<double>("Enter Amount to Deposit: "));
                break;
            case 3:
                account.withdrawFunds(getSafeInput<double>("Enter Amount to Withdraw: "));
                break;
            case 4:
                account.showMiniStatement();
                break;
            case 5:
                std::cout << "\n>> Logging out safely...\n";
                systemSleep(1000);
                return;
            default:
                std::cout << ">> Invalid option selected.\n";
                systemSleep(1000);
            }
        }
    }
};

int main()
{
    AtmMachine iciciAtm;

    iciciAtm.registerUser("arjun", "Arjun Das", "3331", 47000.50);
    iciciAtm.registerUser("sneha", "Sneha Roy", "9876", 92000.00);
    iciciAtm.registerUser("admin", "Kishanu Mondal", "0000", 500000.00);

    iciciAtm.startService();
    return 0;
}