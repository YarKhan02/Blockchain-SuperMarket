#include <iostream>
#include <vector>

#include "MilkyExplorer.h"
#include "Block.h"

#ifndef MILKYTRANSACTION_H
#define MILKYTRANSACTION_H

class MilkyTransaction : private Block {
    private:
        // Private constructor to prevent instantiation from outside the class
        MilkyTransaction() {}

        // Private copy constructor and assignment operator to prevent copies of the class
        MilkyTransaction(const MilkyTransaction&) = delete;
        MilkyTransaction& operator=(const MilkyTransaction&) = delete;

    public:
        // Static function to get a reference to the shared instance of the Transaction class
        static MilkyTransaction& getInstance() {
            static MilkyTransaction instance;
            return instance;
        }

        void addTransaction(vector<string> transactions) {
            MilkyExplorer& milky_explorer = MilkyExplorer::getInstance();
            if (count_m > 1) {
                milky_explorer.addBlock("New Block");
                j++;
                count_m = 0;
            }
            milky_explorer.milky_blocks[j].transaction.push_back(transactions);
            count_m++;
        }
};

#endif