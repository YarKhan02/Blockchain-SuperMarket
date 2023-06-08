#include <iostream>

#include "Block.h"
#include "Blockchain.h"
#include "MilkyExplorer.h"

using namespace std;

class Functionality {
    private:
        // Private constructor to prevent instantiation from outside the class
        Functionality() {

        }

        // Private copy constructor and assignment operator to prevent copies of the class
        Functionality(const Functionality&) = delete;
        Functionality& operator=(const Functionality&) = delete;

    public:
        // Static function to get a reference to the shared instance of the Functionality class
        static Functionality& getInstance() {
            static Functionality instance;
            return instance;
        }

        void createBlock() {
            Blockchain& blockchain = Blockchain::getInstance();
            blockchain.addBlock("New Block");
            MilkyExplorer& milky_explorer = MilkyExplorer::getInstance();
            milky_explorer.addBlock("New Block");
        }

        void show() {
            int k;

            Blockchain& blockchain = Blockchain::getInstance();
            MilkyExplorer& milky_explorer = MilkyExplorer::getInstance();

            system("cls");

            cout << "Explorer\n" << endl;
            cout << "1) Blockchain Explorer\n2) MilkyWay Explorer\n\nPress: ";
            cin >> k;

            if (k == 1) {
                for (int i = 0; i < blockchain.blocks.size(); i++) {
                    Block block = blockchain.blocks[i];
                    cout << "Block " << i << ":" << endl;
                    cout << "  Data: " << block.data << endl;
                    cout << "  Timestamp: " << block.timestamp << endl;
                    cout << "  Hash: " << block.hash << endl;
                    cout << "  Previous hash: " << block.prevHash << endl << endl;
                    if (i > 0) {
                        for (int j = 0; j < block.transaction.size(); j++) {
                            cout << "\tSender: " << block.transaction[j][0] << endl;
                            cout << "\tReciever: " << block.transaction[j][1] << endl;
                            cout << "\tAmount: " << block.transaction[j][2] << endl << endl;
                        }
                    }
                }
            }
            else if (k == 2) {
                for (int i = 0; i < milky_explorer.milky_blocks.size(); i++) {
                    Block block = milky_explorer.milky_blocks[i];
                    cout << "Block " << i << ":" << endl;
                    cout << "  Data: " << block.data << endl;
                    cout << "  Timestamp: " << block.timestamp << endl;
                    cout << "  Hash: " << block.hash << endl;
                    cout << "  Previous hash: " << block.prevHash << endl << endl;
                    if (i > 0) {
                        for (int j = 0; j < block.transaction.size(); j++) {
                            cout << "\tSender: " << block.transaction[j][0] << endl;
                            cout << "\tReciever: " << block.transaction[j][1] << endl;
                            cout << "\tAmount: " << block.transaction[j][2] << endl << endl;
                        }
                    }
                }
            }
            else {
                show();
            }

            cout << "\n\nContinue: ";
            cin >> k;
        }
};