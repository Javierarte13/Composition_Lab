// Javier Arteaga
//9/30/25
//MCSCI-272


#include <iostream>
#include <vector>
#include <ctime>

class Transaction;
using namespace std;

class Transaction {
private:
    std::string type;
    double amount;
    std::string currentTimestamp;

public:

    Transaction(string type, string currentTimestamp, double amount)
    : type(type), amount(amount), currentTimestamp(currentTimestamp) {} // constructor

    std::string getType() const;

    std::string getCurrentTimestamp() const;

    double getAmount() const;

    void setType(std::string type);
    void setCurrentTimestamp(std::string currentTimestamp);
    void setAmount(double amount);
};
void Transaction::setType(std::string type) {
    this->type = type;
}
void Transaction::setAmount(double amount) {
    this->amount = amount;
}
void Transaction::setCurrentTimestamp(std::string currentTimestamp) {
    this->currentTimestamp = currentTimestamp;
}

std::string Transaction::getType() const {
    return type;
}
double Transaction::getAmount() const {
    return amount;
}
std::string Transaction::getCurrentTimestamp() const {
    return currentTimestamp;
}



class BankAccount{
public:
    BankAccount(); // Constructor
    BankAccount(std::string accNum, std::string holder, double bal);  // Constructor
    BankAccount(const BankAccount& other);
    BankAccount& operator=(const BankAccount& other);
    virtual ~BankAccount(); // Destructor
    void addTransaction(const Transaction t);


    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);

    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;

    void setAccountHolderName(std::string holder);
    void setBalance(double bal);


    bool deposit(double amount) {
        if (amount <= 0) {
            return false;
        }
        balance += amount;
        addTransaction(Transaction("Deposit", currentTimestamp(), amount));
        return true;
    }

    virtual bool withdraw(double amount) {
            if (amount > 0 && amount <= balance) {
                balance -= amount;
                addTransaction(Transaction("Deposit", currentTimestamp(), amount));

                return true;
            }
            return false;
        }

    bool operator==(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;

    void printHistory() const;

    static void printAccount(const BankAccount& account);
    static BankAccount createAccountFromInput();


protected:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;
    std::vector<Transaction> transactionHistory;

    std::string currentTimestamp() const {
        time_t currentTime;
        time(&currentTime);
        return ctime(&currentTime);
    }
};

BankAccount::BankAccount() : accountNumber(""), accountHolderName(""), balance(0.0) {} //

BankAccount::BankAccount(string accNum, string holder, double bal)
    : accountNumber(accNum), accountHolderName(holder), balance(bal) {}

BankAccount::BankAccount(const BankAccount& other) {
    accountNumber = other.accountNumber;
    accountHolderName = other.accountHolderName;
    balance = other.balance;
}
BankAccount& BankAccount::operator=(const BankAccount& other) {
    accountNumber = other.accountNumber;
    accountHolderName = other.accountHolderName;
    balance = other.balance;
    return *this;
}
BankAccount::~BankAccount() = default;

void BankAccount::addTransaction(Transaction t) {
    transactionHistory.push_back(t);
}
BankAccount& BankAccount::operator+=(double amount) {
    balance += amount;
    return *this;
}
BankAccount& BankAccount::operator-=(double amount) {
    balance -= amount;
    return *this;
}

std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

std::string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}
double BankAccount::getBalance() const {
    return balance;
}

void BankAccount::setAccountHolderName(std::string holder) {
    accountHolderName = holder;
}
void BankAccount::setBalance(double bal) {
    balance = bal;
}

bool BankAccount::operator==(const BankAccount& other) const {
    return accountNumber == other.accountNumber;
}
bool BankAccount::operator<(const BankAccount& other) const {
    return balance < other.balance;
}
bool BankAccount::operator>(const BankAccount& other) const {
    return balance > other.balance;
}
void BankAccount::printHistory() const {
    cout << "Transaction History:" << accountNumber << endl;
    for (const Transaction& t : transactionHistory) {
        cout << t.getType() << " - " << t.getAmount() << " - " << t.getCurrentTimestamp() << endl;
    }
}
static void printAccount(const BankAccount& account){
    cout << account.getAccountNumber() << endl;
    cout << account.getAccountHolderName() << endl;
    cout << account.getBalance() << endl;
}
static BankAccount createAccountFromInput() {
    string inputAccountNum, inputAccountHolderName;
    double inputBalance;

    cout << "Enter account number: ";
    cin >> inputAccountNum;
    cout << "Enter account holder name: ";
    cin >> inputAccountHolderName;
    cout << "Enter balance: ";
    cin >> inputBalance;
    BankAccount newAccount(inputAccountNum, inputAccountHolderName, inputBalance);
    return newAccount;
}

class CheckingAccount:public BankAccount {
private:
    double transactionFee;
public:
    CheckingAccount(std::string accNum, std::string holder, double bal, double transactionFee) : BankAccount(accNum, holder, bal), transactionFee(transactionFee) {
    }

    bool withdraw(double amount) override {
        if (amount > 0 && amount <= balance) {
            balance -= amount + transactionFee;
            addTransaction(Transaction("Deposit", currentTimestamp(), amount));
            return true;
        }
        return false;
    }
};

class SavingsAccount:public BankAccount {
    private:
    double interestRate;
    public:
    SavingsAccount(std::string accNum, std::string holder, double bal, double interestrate) : BankAccount(accNum, holder, bal), interestRate(interestrate) {
    }
    void calculateInterest() {
        double interest = interestRate * balance;
        balance += interestRate;
        addTransaction(Transaction("Deposit", currentTimestamp(), interestRate * balance));
    }
};

int main() {
    std::vector<BankAccount*> accounts;

    int num;
        do {
            cout << "Select an option: " << endl;
            cout << "1. Create Account: " << endl;
            cout << "2. CheckingAccount:" << endl;
            cout << "3. SavingsAccount:" << endl;
            cout << "4. Deposit: " << endl;
            cout << "5. Withdraw: " << endl;
            cout << "6. Check Balance: " << endl;
            cout << "7. Transaction History:" << endl;
            cout << "8. Exit" << endl;


            cin >> num;

            if (std::cin.fail()) {
                cin.clear();
                continue;
            }
            switch (num) {
                case 1: {
                    string inputAccountNum, inputAccountHolderName;
                    double inputBalance;
                    cout << "Enter account number: ";
                    cin >> inputAccountNum;
                    cout << "Enter account holder name: ";
                    cin >> inputAccountHolderName;
                    cout << "Enter balance: ";
                    cin >> inputBalance;

                    accounts.push_back(new BankAccount(inputAccountNum, inputAccountHolderName, inputBalance));
                    cout << "Account Created" << endl;
                    break;
                }
                case 2: {
                    string inputAccountNum, inputAccountHolderName;
                    double inputBalance, transactionFee;
                    cout << "Enter account number: ";
                    cin >> inputAccountNum;
                    cout << "Enter account holder name: ";
                    cin >> inputAccountHolderName;
                    cout << "Enter balance: ";
                    cin >> inputBalance;
                    cout << "Enter transaction fee: ";
                    cin >> transactionFee;

                    accounts.push_back(new CheckingAccount(inputAccountNum, inputAccountHolderName, inputBalance, transactionFee));
                    cout << "Checking Account Created" << endl;
                    break;
                }
                case 3: {
                    string inputAccountNum, inputAccountHolderName;
                    double inputBalance, interestRate;
                    cout << "Enter account number: ";
                    cin >> inputAccountNum;
                    cout << "Enter account holder name: ";
                    cin >> inputAccountHolderName;
                    cout << "Enter balance: ";
                    cin >> inputBalance;
                    cout << "Enter interestRate: ";
                    cin >> interestRate;

                    accounts.push_back(new SavingsAccount(inputAccountNum, inputAccountHolderName, inputBalance, interestRate));
                    cout << "Savings Account Created" << endl;
                    break;
                }
                case 4: {
                    string inputAccountNum;
                    double amount;
                    cout << "Enter account number: ";
                    cin >> inputAccountNum;
                    cout << "Enter Deposit amount: ";
                    cin >> amount;

                    for (BankAccount* acc : accounts) {
                        delete acc;
                        if (acc->getAccountNumber() == inputAccountNum) {
                            if (acc->deposit(amount))
                                cout << "Balance issued" << endl;
                            else
                                cout << "Balance not issued" << endl;
                            break;
                        }
                        accounts.clear();
                    }
                }break;

                case 5: {
                    string inputAccountNum;
                    double amount;
                    cout << "Enter account number: ";
                    cin >> inputAccountNum;
                    cout << "Enter Withdraw amount: ";
                    cin >> amount;

                    for (BankAccount* acc : accounts) {
                        if (acc->getAccountNumber() == inputAccountNum) {
                            if (acc->withdraw(amount))
                                cout << "WithDraw Complete" << endl;
                            else
                                cout << "Withdraw Failed" << endl;
                            break;
                        }
                    }
                }break;

                    case 6: {
                        string inputAccountNum;
                        cout << "Enter account number: ";
                        cin >> inputAccountNum;

                        bool found = false;

                        for (const BankAccount* acc : accounts) {
                            if (acc->getAccountNumber() == inputAccountNum) {
                                found = true;
                                cout << "Account Name: " << acc->getAccountHolderName() << endl;
                                cout << "Balance: " << acc->getBalance() << endl;
                                break;
                            }
                        }
                        if (!found) cout << "Account not found" << endl;
                        break;
                    }
                    case 7: {
                        string inputAccountNum;
                        cout << "Enter account number: ";
                        cin >> inputAccountNum;
                        bool found = false;
                        for (const BankAccount* acc : accounts) {
                            if (acc->getAccountNumber() == inputAccountNum) {
                                found = true;
                                acc->printHistory();
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            cout << "Account not found" << endl;
                        }
                        break;
                    }
                    case 8: {
                        cout << "Exit" << endl;
                    }
                    break;

                }


            }while (num != 8);
    return 0;
}