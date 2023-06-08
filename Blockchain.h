#include <string>

#include "Block.h"
#include "Explorer.h"

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

class Blockchain: public Explorer {
    private:
        // Private constructor to prevent instantiation from outside the class
        Blockchain() {
            // Add the genesis block
            Block genesis("Genesis block", "");
            blocks.push_back(genesis);
        }

        // Private copy constructor and assignment operator to prevent copies of the class
        Blockchain(const Blockchain&) = delete;
        Blockchain& operator=(const Blockchain&) = delete;

    public:
        // Vector to hold the blocks in the blockchain
        static vector<Block> blocks;

        // Static function to get a reference to the shared instance of the Blockchain class
        static Blockchain& getInstance() {
            static Blockchain instance;
            return instance;
        }

        // Add a block to the blockchain
        void addBlock(string data) {
            Block block(data, blocks.back().hash);
            blocks.push_back(block);
        }
};

vector<Block> Blockchain::blocks = {};

#endif // BLOCKCHAIN_H