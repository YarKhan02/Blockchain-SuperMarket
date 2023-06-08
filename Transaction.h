#include <iostream>
#include <vector>

#include "Blockchain.h"
#include "Block.h"

#ifndef TRANSACTION_H
#define TRANSACTION_H

using namespace std;

class Transaction : private Block {
    private:
        // Private constructor to prevent instantiation from outside the class
        Transaction() {}

        // Private copy constructor and assignment operator to prevent copies of the class
        Transaction(const Transaction&) = delete;
        Transaction& operator=(const Transaction&) = delete;

    public:
        // Static function to get a reference to the shared instance of the Transaction class
        static Transaction& getInstance() {
            static Transaction instance;
            return instance;
        }

        void addTransaction(vector<string> transactions) {
            Blockchain& blockchain = Blockchain::getInstance();
            if (count > 1) {
                blockchain.addBlock("New Block");
                i++;
                count = 0;
            }
            blockchain.blocks[i].transaction.push_back(transactions);
            count++;
        }
};

#endif