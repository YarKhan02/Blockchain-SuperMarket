#include <vector>

#include "Block.h"
#include "Zonix.h"
//#include "Exchange.h"
#include "Transaction.h"
#include "MilkyTransaction.h"

#ifndef WALLET_H
#define WALLET_H

using namespace std;

class Wallet {
    private:
        string address;
        vector<string> transactions;
        vector<int> tokens;

        // Private constructor to prevent instantiation from outside the class
        Wallet() {
            ifstream inFile("wallet_data.txt");
            if (inFile) {
                if (!is_file_empty(inFile)) {
                    inFile >> this->address;
                    int token;
                    while (inFile >> token) {
                        this->tokens.push_back(token);
                    }
                    inFile.close();
                }
                else {
                    Block block;
                    this->address = block.calculateAddress("Wallet");
                    this->tokens.push_back(0);
                    this->tokens.push_back(0);
                    inFile.close();
                }
            }
        }

        // Private copy constructor and assignment operator to prevent copies of the class
        Wallet(const Wallet&) = delete;
        Wallet& operator=(const Wallet&) = delete;

    public:
        // Static function to get a reference to the shared instance of the User class
        static Wallet& getInstance() {
            static Wallet instance;
            return instance;
        }

        string getAddress() {
            return address;
        }

        float getBalance() {
            Zonix& zonix = Zonix::getInstance();

            float y = tokens[0] + (tokens[1] * zonix.getCurrentPrice());

            return y;
        }

        void dashboard() {
            int n = 0;

            system("cls");

            cout << "\t\t\t   Milky Way Chain\n" << endl;
            cout << "\t\t\t\t$" << getBalance() << endl;
            cout << "\t" << getAddress() << "\n\n\n" << endl;

            cout << "1) Recieve\t2) Send\t\t3) Exit\n\n" << endl;

            cout << "Tokens" << endl;

            cout << "USDT - " << tokens[0] << "\nZNX - " << tokens[1] << endl;

            cout << "\n\nPress: ";
            cin >> n;

            switch (n) {
                case 1:
                    recieve();
                    break;
                case 2:
                    //withdraw();
                    break;
                case 3:
                    return;
                default:
                    dashboard();
            }
        }

        void recieve() {
            int amount, k;

            system("cls");

            cout << "Enter amount to deposit: ";
            cin >> amount;

            tokens[0] += amount;

            transactions.push_back("Bank Account");
            transactions.push_back(address);
            transactions.push_back(to_string(amount) + " USDT");
            Transaction& transaction = Transaction::getInstance();
            transaction.addTransaction(transactions);
            transactions.clear();

            cout << "\n\nDeposit Successful" << endl;

            cout << "\n\nContinue: ";
            cin >> k;

            dashboard();
        }
        
        void recieve(int amount, string sender, int x) {
            Transaction& transaction = Transaction::getInstance();
            switch (x) {
                case 1:
                    tokens[0] += amount;

                    transactions.push_back(sender);
                    transactions.push_back(address);
                    transactions.push_back(to_string(amount) + " USDT");
                    transaction.addTransaction(transactions);
                    transactions.clear();

                    break;

                case 2:
                    tokens[1] += amount;

                    transactions.push_back(sender);
                    transactions.push_back(address);
                    transactions.push_back(to_string(amount) + " ZNX");
                    transaction.addTransaction(transactions);
                    transactions.clear();

                    break;

                default:
                    return;
            }

            cout << "\nTransaction Successful" << endl;
        }

        /*int withdraw() {
            Exchange& exchange = Exchange::getInstance();
            exchange.deposit();

            dashboard();
        }*/

        int withdraw(string reciever, int x) {
            int amount, k;

            system("cls");

            cout << "Available tokens\n" << endl;
            cout << "USDT - " << tokens[0] << "\nZNX - " << tokens[1] << endl;

            cout << "\nEnter amount to deposit: ";
            cin >> amount;

            switch (x) {
                case 1:
                    if (amount <= tokens[0]) {
                        tokens[0] -= amount;

                        transactions.push_back(address);
                        transactions.push_back(reciever);
                        transactions.push_back(to_string(amount) + " USDT");
                        Transaction& transaction = Transaction::getInstance();
                        transaction.addTransaction(transactions);
                        transactions.clear();

                        cout << "\n\nDeposit Successful" << endl;

                        cout << "\n\nContinue: ";
                        cin >> k;

                        return amount;
                    }
                    else {
                        cout << "\n\nInsufficient amount" << endl;

                        cout << "\n\nContinue(0/1): ";
                        cin >> k;

                        if (k == 0) {
                            return 0;
                        }
                        else {
                            withdraw(reciever, x);
                        }
                    }

                case 2:
                    if (amount <= tokens[1]) {
                        tokens[1] -= amount;

                        transactions.push_back(address);
                        transactions.push_back(reciever);
                        transactions.push_back(to_string(amount) + " ZNX");
                        Transaction& transaction = Transaction::getInstance();
                        transaction.addTransaction(transactions);
                        transactions.clear();

                        cout << "Deposit Successful" << endl;

                        cout << "\n\nContinue: ";
                        cin >> k;

                        return amount;
                    }
                    else {
                        cout << "Insufficient amount" << endl;

                        cout << "\n\nContinue(0/1): ";
                        cin >> k;

                        if (k == 0) {
                            return 0;
                        }
                        else {
                            withdraw(reciever, x);
                        }
                    }

                default:
                    return 0;
            }
        }

        void payment(int amount, string reciever) {
            int tk = static_cast<float>(amount) / getTokenPrice();

            if (tk <= tokens[1]) {
                tokens[1] -= tk;
                transactions.push_back(address);
                transactions.push_back(reciever);
                transactions.push_back(to_string(tk) + " ZNX");
                Transaction& transaction = Transaction::getInstance();
                transaction.addTransaction(transactions);
                MilkyTransaction& milky_transaction = MilkyTransaction::getInstance();
                milky_transaction.addTransaction(transactions);
                transactions.clear();
                cout << "\n\nPayment Successful" << endl;
            }
            else {
                cout << "\n\nInsufficient amount in wallet" << endl;
                return;
            }
        }

        float getTokenPrice() {
            Zonix& zonix = Zonix::getInstance();
            return zonix.getCurrentPrice();
        }

        void save_data() {
            ofstream outFile("wallet_data.txt", ofstream::out | ofstream::trunc);

            outFile << address << "\n";
            for (const auto& tk : tokens) {
                outFile << tk << "\n";
            }

            outFile.close();
        }
};

#endif