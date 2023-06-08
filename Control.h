#include "Wallet.h""
#include "Exchange.h"
#include "MartOverview.h"
#include "Functionality.h"

class Control {
    private:
        MartOverview mart_overview;

    public:
        Control() {
            Functionality& functionality = Functionality::getInstance();
            functionality.createBlock();

            MartOverview mo;
            this -> mart_overview = mo;
            mart_overview.MartOverview::container();
        }

        void controller() {
            int n;

            system("cls");

            cout << "Blochchain Based Application Of Self Environment\n\n" << endl;

            cout << "1) Wallet\n2) Exchange\n3) Mart\n4) Blocks\n5) Exit\n\nPress: ";
            cin >> n;

            switch (n) {
                case 1:
                    control_wallet();
                    break;
                case 2:
                    control_exchange();
                    break;
                case 3:
                    control_mart();
                    break;
                case 4:
                    control_blocks();
                    break;
                default:
                    system("cls");
                    Wallet& wallet = Wallet::getInstance();
                    wallet.save_data();
                    Exchange& exchange = Exchange::getInstance();
                    exchange.save_data();
                    Zonix& zonix = Zonix::getInstance();
                    zonix.save_data();

                    cout << "\n\n\n\t\tThis project is created by WALI YAR in collaboration with SHABBIR and OSMAN" << endl << endl;
                    return;
            }
        }

        void control_wallet() {
            Wallet& wallet = Wallet::getInstance();
            wallet.dashboard();
            controller();
        }

        void control_exchange() {
            Exchange& exchange = Exchange::getInstance();
            exchange.overview();
            controller();
        }

        void control_mart() {
            mart_overview.dashboard();
            controller();
        }

        void control_blocks() {
            int k;

            system("cls");

            cout << "1) Explorer\n2) Zonix Details\n\nPress: ";
            cin >> k;
            
            if (k == 1) {
                Functionality& functionality = Functionality::getInstance();
                functionality.show();
                controller();
            }
            else if (k == 2) {
                Zonix& zonix = Zonix::getInstance();
                zonix.details();
                controller();
            }
        }
};