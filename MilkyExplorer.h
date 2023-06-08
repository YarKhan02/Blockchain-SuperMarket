#include "Block.h"
#include "Explorer.h"

#ifndef MILKYEXPLORER_H
#define MILKYEXPLORER_H

class MilkyExplorer : public Explorer {
    private:
        // Private constructor to prevent instantiation from outside the class
        MilkyExplorer() {
            // Add the genesis block
            Block genesis("Genesis block", "");
            milky_blocks.push_back(genesis);
        }

        // Private copy constructor and assignment operator to prevent copies of the class
        MilkyExplorer(const MilkyExplorer&) = delete;
        MilkyExplorer& operator=(const MilkyExplorer&) = delete;

    public:
        // Vector to hold the blocks in the blockchain
        static vector<Block> milky_blocks;

        // Static function to get a reference to the shared instance of the Blockchain class
        static MilkyExplorer& getInstance() {
            static MilkyExplorer instance;
            return instance;
        }

        // Add a block to the blockchain
        void addBlock(string data) {
            Block block(data, milky_blocks.back().hash);
            milky_blocks.push_back(block);
    }
};

vector<Block> MilkyExplorer::milky_blocks = {};

#endif