#include <string>

#ifndef BLOCKCHAIN_H
#define EXPLORER_H

class Explorer {
    public:
        virtual void addBlock(string) = 0;
};

#endif