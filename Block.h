#include <string>
#include <vector>
#include <ctime>
#include <openssl/sha.h>
#include <sstream>

#ifndef BLOCK_H
#define BLOCK_H

using namespace std;

class Block {
    public:
        string prevHash;
        string data;
        time_t timestamp;
        string hash;
        vector<vector<string>> transaction;
        static int count, count_m, i, j;

        Block() {}

        Block(string data, string prevHash) {
            this->prevHash = prevHash;
            this->data = data;
            this->timestamp = time(nullptr);
            this->hash = calculateHash();
        }

        // Calculate the SHA-256 hash of the block
        string calculateHash() {
            stringstream ss;
            ss << prevHash << data << timestamp;
            string input = ss.str();
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256((unsigned char*)input.c_str(), input.size(), hash);
            stringstream result;
            for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
                result << hex << (int)hash[i];
            }
            return result.str();
        }

        // Calculate the Address
        string calculateAddress(string data) {
            stringstream ss;
            ss << "Address" << data << time(nullptr);
            string input = ss.str();
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256((unsigned char*)input.c_str(), input.size(), hash);
            stringstream result;
            for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
                result << hex << (int)hash[i];
            }
            return result.str();
        }

        virtual void addTransaction(vector<string>) {}
};

int Block::count = 0;
int Block::i = 1;
int Block::count_m = 0;
int Block::j = 1;

#endif // BLOCK_H