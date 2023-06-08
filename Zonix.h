#ifndef ZONIX_H
#define ZONIX_H

bool is_file_empty(std::ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}

class Zonix {
    private:
        float market_cap, circulating_supply;

        // Private constructor to prevent instantiation from outside the class
        Zonix() {
            ifstream inFile("zonix_data.txt");
            if (inFile) {
                if (!is_file_empty(inFile)) {
                    inFile >> this->market_cap;
                    this->circulating_supply = 120000.00;

                    inFile.close();
                }
                else {
                    market_cap = 200000.00;
                    circulating_supply = 120000.00;

                    inFile.close();
                }
            }
        }

        // Private copy constructor and assignment operator to prevent copies of the class
        Zonix(const Zonix&) = delete;
        Zonix& operator=(const Zonix&) = delete;

    public:
        // Static function to get a reference to the shared instance of the Zonix class
        static Zonix& getInstance() {
            static Zonix instance;
            return instance;
        }

        void buy(int n) {
            market_cap += n;
        }

        void sell(int n) {
            market_cap -= n;
        }

        float getCurrentPrice() {
            return market_cap / circulating_supply;
        }

        void details() {
            cout << "Zonix Coin\n\n";
            cout << "Current Price\t" << getCurrentPrice() << endl << endl;
            cout << "Market Cap\t" << market_cap << endl;
            cout << "Circulating Supply\t" << circulating_supply << endl;

            int k;

            cout << "\nContinue: ";
            cin >> k;
        }

        void save_data() {
            ofstream outFile("zonix_data.txt", ofstream::out | ofstream::trunc);

            outFile << int(market_cap) << "\n";

            outFile.close();
        }
};

#endif