#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Transaction class
class Transaction {
public:
    string type;
    float amount;
    string note;

    Transaction(string t, float a, string n) {
        type = t;
        amount = a;
        note = n;
    }
};

// Account class
class Account {
private:
    int accountNumber;
    float balance;
    vector<Transaction> history;

public:
    Account(int accNo) {
        accountNumber = accNo;
        balance = 0.0;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    float getBalance() const {
        return balance;
    }

    void deposit(float amount) {
        if (amount <= 0) {
            cout << "❌ Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        history.push_back(Transaction("Deposit", amount, "Money Deposited"));
        cout << "✅ ₹" << amount << " deposited successfully. New balance: ₹" << balance << endl;
    }

    void withdraw(float amount) {
        if (amount <= 0 || amount > balance) {
            cout << "❌ Invalid or insufficient balance.\n";
            return;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount, "Money Withdrawn"));
        cout << "✅ ₹" << amount << " withdrawn successfully. New balance: ₹" << balance << endl;
    }

    void transfer(Account &receiver, float amount) {
        if (amount <= 0 || amount > balance) {
            cout << "❌ Invalid or insufficient balance.\n";
            return;
        }
        balance -= amount;
        receiver.balance += amount;
        history.push_back(Transaction("Transfer Sent", amount, "To Account " + to_string(receiver.getAccountNumber())));
        receiver.history.push_back(Transaction("Transfer Received", amount, "From Account " + to_string(accountNumber)));
        cout << "✅ ₹" << amount << " transferred to Account " << receiver.getAccountNumber() << endl;
    }

    void showTransactions() const {
        cout << "\n📄 Transaction History:\n";
        if (history.empty()) {
            cout << "No transactions available.\n";
        } else {
            for (const auto &t : history) {
                cout << "- " << t.type << ": ₹" << t.amount << " (" << t.note << ")\n";
            }
        }
    }

    void showAccountDetails() const {
        cout << "\n🧾 Account Number: " << accountNumber << endl;
        cout << "💰 Current Balance: ₹" << fixed << setprecision(2) << balance << endl;
        showTransactions();
    }
};

// Customer class
class Customer {
private:
    string name;
    Account account;

public:
    Customer(string customerName, int accNo) : name(customerName), account(accNo) {}

    string getName() const {
        return name;
    }

    Account& getAccount() {
        return account;
    }

    void displayCustomerDetails() const {
        cout << "\n👤 Customer Name: " << name << endl;
        account.showAccountDetails();
    }
};

// Find customer by account number
Customer* findCustomer(vector<Customer> &customers, int accNo) {
    for (auto &cust : customers) {
        if (cust.getAccount().getAccountNumber() == accNo) {
            return &cust;
        }
    }
    return nullptr;
}

// Main
int main() {
    vector<Customer> customers;
    int choice;

    while (true) {
        cout << "\n====== 🏦 Banking System Menu ======\n";
        cout << "1. Create Customer Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Funds\n";
        cout << "5. Show Account Details\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int accNo;
            cout << "\nEnter customer name: ";
            cin >> name;
            cout << "Enter new account number: ";
            cin >> accNo;

            if (findCustomer(customers, accNo)) {
                cout << "❌ Account number already exists.\n";
            } else {
                customers.push_back(Customer(name, accNo));
                cout << "✅ Account created successfully for " << name << endl;
            }

        } else if (choice >= 2 && choice <= 5) {
            int accNo;
            cout << "Enter your account number: ";
            cin >> accNo;

            Customer* customer = findCustomer(customers, accNo);
            if (!customer) {
                cout << "❌ Account not found.\n";
                continue;
            }

            if (choice == 2) {
                float amt;
                cout << "Enter amount to deposit: ";
                cin >> amt;
                customer->getAccount().deposit(amt);

            } else if (choice == 3) {
                float amt;
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                customer->getAccount().withdraw(amt);

            } else if (choice == 4) {
                int receiverAccNo;
                float amt;
                cout << "Enter receiver's account number: ";
                cin >> receiverAccNo;
                Customer* receiver = findCustomer(customers, receiverAccNo);
                if (!receiver) {
                    cout << "❌ Receiver account not found.\n";
                } else {
                    cout << "Enter amount to transfer: ";
                    cin >> amt;
                    customer->getAccount().transfer(receiver->getAccount(), amt);
                }

            } else if (choice == 5) {
                customer->displayCustomerDetails();
            }

        } else if (choice == 6) {
            cout << "👋 Exiting Banking System. Goodbye!\n";
            break;
        } else {
            cout << "❌ Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
