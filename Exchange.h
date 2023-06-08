#include "Wallet.h"
#include "Zonix.h"
#include "Transaction.h"

#ifndef EXCHANGE_H
#define EXCHANGE_H

class Exchange {
    private:
        string address;
        float tokens, currency;
        vector<string> pay;

        // Private constructor to prevent instantiation from outside the class
        Exchange() {
            ifstream inFile("exchange_data.txt");
            if (inFile) {
                if (!is_file_empty(inFile)) {
                    inFile >> this->address;
                    inFile >> this->currency;
                    inFile >> this->tokens;

                    inFile.close();
                }
                else {
                    Block block;
                    this->address = block.calculateAddress("Exchange");
                    this->currency = 0;
                    this->tokens = 0;

                    inFile.close();
                }
            }
        }

        // Private copy constructor and assignment operator to prevent copies of the class
        Exchange(const Exchange&) = delete;
        Exchange& operator=(const Exchange&) = delete;

    public:
        // Static function to get a reference to the shared instance of the Exchange class
        static Exchange& getInstance() {
            static Exchange instance;
            return instance;
        }

        void overview() {
            int i;

            system("cls");

            cout << "\t\t\tMilky Way Exchange\n\n" << endl;

            cout << "1) Deposit\n2) Witdraw\n3) Market\n4) Wallet\n5) Exit\n\nPress: ";
            cin >> i;

            switch (i) {
                case 1:
                    deposit();
                    overview();
                    break;
                case 2:
                    withdraw();
                    overview();
                    break;
                case 3:
                    markets();
                    overview();
                    break;
                case 4:
                    wallet();
                    overview();
                    break;
                case 5:
                    return;
                default:
                    overview();
            }
        }

        void deposit() {
            Wallet& wallet = Wallet::getInstance();

            int n, amount;

            system("cls");

            cout << "Available tokens\n" << endl;
            cout << "Choose a token to deposit:\n\n1) USDT\n2) ZNX\n\nPress: ";
            cin >> n;

            switch (n) {
                case 1:
                    amount = wallet.withdraw(address, 1);
                    currency += amount;
                    break;
                case 2:
                    amount = wallet.withdraw(address, 2);
                    tokens += amount;
                    break;
                default:
                    deposit();
            }
        }

        void withdraw() {
            int amount, n, k;

            system("cls");

            cout << "Available tokens\n" << endl;
            cout << "Choose a token to withdraw:\n\n1) USDT - " << currency << "\n2) ZNX - " << tokens << "\n\nPress: ";
            cin >> n;

            cout << "\n\nEnter amount to witdraw: ";
            cin >> amount;

            switch (n) {
                case 1:
                    if (amount > currency) {
                        cout << "\n\nWithdraw amount exceeded\n" << endl;

                        int i = 0;

                        cout << "1) Another take\n2) Cancel\n\nPress: ";
                        cin >> i;

                        if (i == 1) {
                            withdraw();
                        }
                        else {
                            return;
                        }
                    }
                    else {
                        Wallet& wallet = Wallet::getInstance();

                        wallet.recieve(amount, address, n);
                        currency -= amount;

                        cout << "\n\nContinue: ";
                        cin >> k;
                    }
                case 2:
                    if (amount > tokens) {
                        cout << "Withdraw amount exceeded." << endl;

                        int i = 0;

                        cout << "1) Another take\n2) Cancel\n\nPress: ";
                        cin >> i;

                        if (i == 1) {
                            withdraw();
                        }
                        else {
                            return;
                        }
                    }
                    else {
                        Wallet& wallet = Wallet::getInstance();

                        wallet.recieve(amount, address, n);
                        tokens -= amount;

                        cout << "\n\nContinue: ";
                        cin >> k;
                    }
                default:
                    break;
            }
        }

        void buy_coin() {
            float amount;
            int k;

            Zonix& zonix = Zonix::getInstance();

            system("cls");

            cout << "Zonix - " << zonix.getCurrentPrice() << endl;
            cout << "\nUSDT$ - " << currency << endl;

            cout << "\n\nEnter amount (USDT): ";
            cin >> amount;

            if (amount > currency) {
                cout << "\n\nAmount exceeded." << endl;

                int i = 0;

                cout << "1) Another take\n2) Cancel\n\nPress: ";
                cin >> i;

                if (i == 1) {
                    buy_coin();
                }
                else {
                    return;
                }
            }
            else {
                tokens += amount / zonix.getCurrentPrice();
                currency -= amount;
                zonix.buy(amount);

                cout << "\n\nContinue: ";
                cin >> k;
            }
        }

        void sell_coin() {
            float tk;
            int k;

            Zonix& zonix = Zonix::getInstance();

            system("cls");

            cout << "Zonix - " << zonix.getCurrentPrice() << endl;
            cout << "\nZonix token - " << tokens << endl;

            cout << "\n\nEnter tokens (ZNX): ";
            cin >> tk;

            if (tk > tokens) {
                cout << "\n\nTokens exceeded." << endl;

                int i = 0;

                cout << "1) Another take\n2) Cancel\n\nPress: ";
                cin >> i;

                if (i == 1) {
                    sell_coin();
                }
                else {
                    return;
                }
            }
            else {
                float y = tk * zonix.getCurrentPrice();
                currency += y;
                tokens -= tk;
                zonix.sell(y);

                cout << "\n\nContinue: ";
                cin >> k;
            }
        }

        void trade() {
            int i;

            system("cls");

            cout << "Trade\n" << endl;

            cout << "1) Buy\n2) Sell\n\nPress: ";
            cin >> i;

            if (i == 1) {
                buy_coin();
            }
            else if (i == 2) {
                sell_coin();
            }
        }

        void markets() {
            Zonix& zonix = Zonix::getInstance();

            int i;

            system("cls");

            cout << "Market\n" << endl;

            cout << "Zonix - " << zonix.getCurrentPrice() << endl;

            cout << "\n\nTrade (0/1): ";
            cin >> i;

            if (i == 1) {
                trade();
            }
            else {
                overview();
            }
        }

        float getTokenPrice() {
            Zonix& zonix = Zonix::getInstance();
            return zonix.getCurrentPrice();
        }

        float getBalance() {
            Zonix& zonix = Zonix::getInstance();

            float y = currency + (tokens * zonix.getCurrentPrice());

            return y;
        }

        void wallet() {
            int k;

            system("cls");

            cout << "Wallet\n\n" << endl;

            cout << "Balance\t" << getBalance() << endl << endl;

            cout << "USD$\t" << currency << endl;
            cout << "Zonix Token\t" << tokens << endl;

            cout << "\n\nContinue: ";
            cin >> k;
        }

        void save_data() {
            ofstream outFile("exchange_data.txt", ofstream::out | ofstream::trunc);

            outFile << address << "\n";
            outFile << int(currency) << "\n";
            outFile << int(tokens) << "\n";

            outFile.close();
        }
};

#endif