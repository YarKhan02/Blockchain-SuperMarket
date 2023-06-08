#include <vector>
#include <string>
#include <list>

#include "Block.h"
#include "Wallet.h"
#include "Exchange.h"
#include "StoreItems.h"

class Mart {
    public:

        list<pair<string, pair<int, int>>> beverages_stock;
        list<pair<string, pair<int, int>>> vegetables_stock;
        list<pair<string, pair<int, int>>> fruits_stock;
        static list<pair<string, pair<int, int>>> cart;
        static string address;
        static int total_price;

        Mart() {
            this -> total_price = 0;
        }

        virtual void add_products(string, int, int) = 0;

        virtual void remove_products(string) = 0;

        virtual void add_to_cart() = 0;

        virtual void display_stock() = 0;

        virtual void container() = 0;

        virtual void save_data() = 0;
};

list<pair<string, pair<int, int>>> Mart::cart = {};
string Mart::address = "0";
int Mart::total_price = 0;

class Fruits : public Mart {
    public:

        Fruits() {}

        void add_products(string product_name, int product_quantity, int product_price) {
            fruits_stock.push_back(make_pair(product_name, make_pair(product_quantity, product_price)));
        }

        void remove_products(string name) {
            int i = 0;
            for (const auto& x : fruits_stock) {
                if (x.first == name) {
                    break;
                }
                i++;
            }
            auto it = fruits_stock.begin();
            advance(it, i);
            fruits_stock.erase(it);
        }

        void add_to_cart() {
            string product;
            int quantity, price;

            cout << "\n\nEnter product name: ";
            cin >> product;

            cout << "Enter quantity: ";
            cin >> quantity;

            for (auto& x : fruits_stock) {
                if (x.first == product) {
                    if (quantity > x.second.first) {
                        cout << "Not enough items available" << endl;
                        add_to_cart();
                    }
                    else {
                        x.second.first -= quantity;
                        price = x.second.second * quantity;
                        cart.push_back(make_pair(product, make_pair(quantity, price)));
                    }
                }
            }
        }

        void display_stock() {
            int i = 0, k;

            system("cls");

            cout << "Fruits Cart\n\n" << endl;

            cout << "Product\t\tQuantity\t\tPrice\n" << endl;
            for (const auto& x : fruits_stock) {
                cout << x.first << "\t\t" << x.second.first << "\t\t\t" << x.second.second << endl;
            }
            cout << "\n\nDo you want to buy? ";
            cin >> i;

            if (i == 1) {
                add_to_cart();
                cout << "\n\nAnother take? ";
                cin >> i;
                if (i == 1) {
                    display_stock();
                }
                else {
                    cout << "\n\nContinue: ";
                    cin >> k;
                }
            }
            else {
                cout << "\nDon't mind me just watching" << endl;

                cout << "\n\nContinue: ";
                cin >> k;
            }
        }

        void container() {
            ifstream inFile("fruits.txt");

            string name, line;
            int quantity, price;

            if (inFile) {
                while (getline(inFile, line)) {
                    istringstream iss(line);
                    iss >> name >> quantity >> price;
                    add_products(name, quantity, price);
                }
            }
            else {
                cout << "File does not exist" << endl;
            }

            inFile.close();
        }

        void save_data() {
            ofstream outFile("fruits.txt", ofstream::out | ofstream::trunc);

            if (outFile) {
                for (const auto& x : fruits_stock) {
                    outFile << x.first << " " << x.second.first << " " << x.second.second << endl;
                }
            }
            else {
                cout << "File does not exist" << endl;
            }
        }
};

class Vegetables : public Mart {
    public:

        Vegetables() {}

        void add_products(string product_name, int product_quantity, int product_price) {
            vegetables_stock.push_back(make_pair(product_name, make_pair(product_quantity, product_price)));
        }

        void remove_products(string name) {
            int i = 0;
            for (const auto& x : vegetables_stock) {
                if (x.first == name) {
                    break;
                }
                i++;
            }
            auto it = vegetables_stock.begin();
            advance(it, i);
            vegetables_stock.erase(it);
        }

        void add_to_cart() {
            string product;
            int quantity, price;

            cout << "\n\nEnter product name: ";
            cin >> product;

            cout << "Enter quantity: ";
            cin >> quantity;

            for (auto& x : vegetables_stock) {
                if (x.first == product) {
                    if (quantity > x.second.first) {
                        cout << "Not enough items available" << endl;
                        add_to_cart();
                    }
                    else {
                        x.second.first -= quantity;
                        price = x.second.second * quantity;
                        cart.push_back(make_pair(product, make_pair(quantity, price)));
                    }
                }
            }
        }

        void display_stock() {
            int i = 0, k;

            system("cls");

            cout << "Vegetabls Cart\n\n" << endl;

            cout << "Product\t\tQuantity\n" << endl;
            for (const auto& x : vegetables_stock) {
                cout << x.first << "\t\t" << x.second.first << "\t\t\t" << x.second.second << endl;
            }
            cout << "\n\nDo you want to buy? ";
            cin >> i;

            if (i == 1) {
                add_to_cart();
                cout << "\n\nAnother take? ";
                cin >> i;
                if (i == 1) {
                    display_stock();
                }
                else {
                    cout << "\n\nContinue: ";
                    cin >> k;
                }
            }
            else {
                cout << "\nDon't mind me just watching" << endl;

                cout << "\n\nContinue: ";
                cin >> k;
            }
        }

        void container() {
            ifstream inFile("vegetables.txt");

            string name, line;
            int quantity, price;

            if (inFile) {
                while (getline(inFile, line)) {
                    istringstream iss(line);
                    iss >> name >> quantity >> price;
                    add_products(name, quantity, price);
                }
            }
            else {
                cout << "File does not exist" << endl;
            }

            inFile.close();
        }

        void save_data() {
            ofstream outFile("vegetables.txt", ofstream::out | ofstream::trunc);

            if (outFile) {
                for (const auto& x : vegetables_stock) {
                    outFile << x.first << " " << x.second.first << " " << x.second.second << endl;
                }
            }
            else {
                cout << "File does not exist" << endl;
            }
        }
};

class Beverages : public Mart {
    public:

        Beverages() {}

        void add_products(string product_name, int product_quantity, int product_price) {
            beverages_stock.push_back(make_pair(product_name, make_pair(product_quantity, product_price)));
        }

        void remove_products(string name) {
            int i = 0;
            for (const auto& x : beverages_stock) {
                if (x.first == name) {
                    break;
                }
                i++;
            }
            auto it = beverages_stock.begin();
            advance(it, i);
            beverages_stock.erase(it);
        }

        void add_to_cart() {
            string product;
            int quantity, price;

            cout << "\n\nEnter product name: ";
            cin >> product;

            cout << "Enter quantity: ";
            cin >> quantity;

            for (auto& x : beverages_stock) {
                if (x.first == product) {
                    if (quantity > x.second.first) {
                        cout << "Not enough items available" << endl;
                        add_to_cart();
                    }
                    else {
                        x.second.first -= quantity;
                        price = quantity * x.second.second;
                        cart.push_back(make_pair(product, make_pair(quantity, price)));
                    }
                }
            }
        }

        void display_stock() {
            int i = 0, k;

            system("cls");

            cout << "Beverages Cart\n\n" << endl;

            cout << "Product\t\tQuantity\t\tPrice\n" << endl;

            for (const auto& x : beverages_stock) {
                cout << x.first << "\t\t" << x.second.first << "\t\t\t" << x.second.second << endl;
            }

            cout << "\n\nDo you want to buy? ";
            cin >> i;

            if (i == 1) {
                add_to_cart();
                cout << "\n\nAnother take? ";
                cin >> i;
                if (i == 1) {
                    display_stock();
                }
                else {
                    cout << "\n\nContinue: ";
                    cin >> k;
                }
            }
            else {
                cout << "\nDon't mind me just watching" << endl;

                cout << "\n\nContinue: ";
                cin >> k;
            }
        }

        void container() {
            ifstream inFile("beverages.txt");

            string name, line;
            int quantity, price;

            if (inFile) {
                while (getline(inFile, line)) {
                    istringstream iss(line);
                    iss >> name >> quantity >> price;
                    add_products(name, quantity, price);
                }
            }
            else {
                cout << "File does not exist" << endl;
            }

            inFile.close();
        }

        void save_data() {
            ofstream outFile("beverages.txt", ofstream::out | ofstream::trunc);

            if (outFile) {
                for (const auto& x : beverages_stock) {
                    outFile << x.first << " " << x.second.first << " " << x.second.second << endl;
                }
            }
            else {
                cout << "File does not exist" << endl;
            }
        }
};

vector<StoreItems> buildMenu(const vector<string>& names, const vector<double>& cost, const vector<double>& weight) {
    vector<StoreItems> menu;

    for (size_t i = 0; i < cost.size(); i++) {
        menu.push_back(StoreItems(names[i], cost[i], weight[i]));
    }

    return menu;
}

list<pair<string, pair<int, int>>> greedy(const vector<StoreItems>& items, double maxWeight, function<double(const StoreItems&)> keyFunction) {
    srand(time(NULL));
    vector<StoreItems> itemsCopy = items;

    sort(itemsCopy.begin(), itemsCopy.end(), [&keyFunction](const StoreItems& a, const StoreItems& b) { return keyFunction(a) > keyFunction(b); });

    list<pair<string, pair<int, int>>> result;
    int totalCost = 0;
    int weight = 0;
    int temp = 0;

    if (maxWeight < 1000) {
        for (const auto& item : itemsCopy) {
            if (totalCost + item.getCost() <= maxWeight) {
                weight = 1 + rand() % (10 - 1 + 1);
                if ((weight * item.getCost() <= maxWeight)) {
                    totalCost += weight * int(item.getCost());
                    if (totalCost <= maxWeight) {
                        result.push_back(make_pair(item.getName(), make_pair(weight, weight * item.getCost())));
                    }
                }
                weight = 0;
                temp = 0;
            }
        }
    }
    else {
        for (const auto& item : itemsCopy) {
            if (totalCost + item.getCost() <= maxWeight) {
                temp = int(item.getWeight());
                weight = 1 + rand() % (temp - 1 + 1);
                if ((weight * item.getCost() <= maxWeight)) {
                    totalCost += weight * int(item.getCost());
                    if (totalCost <= maxWeight) {
                        result.push_back(make_pair(item.getName(), make_pair(weight, weight * item.getCost())));
                    }
                }
                weight = 0;
                temp = 0;
            }
        }
    }

    return result;
}

list<pair<string, pair<int, int>>> testGreedy(const vector<StoreItems>& items, double constraint, function<double(const StoreItems&)> keyFunction) {
    auto taken = greedy(items, constraint, keyFunction);
    int totalCost = 0;

    for (const auto& item : taken) {
        totalCost += item.second.second;
    }
    cout << "Total cost of items taken = " << totalCost << endl;

    for (const auto& item : taken) {
        cout << " " << item.first << " : <" << item.second.first << ", " << item.second.second << ">" << endl;
    }

    return taken;
}

list<pair<string, pair<int, int>>> testGreedys(vector<StoreItems>& items, double maxUnits) {
    cout << "\nMinimum quantity to allocate " << maxUnits << " tokens" << endl;
    auto taken = testGreedy(items, maxUnits, [](const StoreItems& item) {return 1 / item.getWeight(); });
    return taken;
}

class MartOverview : public Vegetables, public Fruits, public Beverages {
    public:

        void dashboard() {
            int n = 0;

            system("cls");

            cout << "Milky Way Super Mart\n\n" << endl;

            cout << "Available Items Category In Super Mart\n" << endl;

            cout << "1) Fruits\n2) Vegetables\n3) Beverages\n4) Recommendation\n5) Checkout\n6) Exit\n\nPress: ";
            cin >> n;

            if (n == 1) {
                Fruits::display_stock();
                dashboard();
            }
            else if (n == 2) {
                Vegetables::display_stock();
                dashboard();
            }
            else if (n == 3) {
                Beverages::display_stock();
                dashboard();
            }
            else if (n == 4) {
                recommendation();
            }
            else if (n == 5) {
                checkout();
            }
            else {
                Fruits::save_data();
                Vegetables::save_data();
                Beverages::save_data();
                return;
            }
        }

        void add() {
            system("cls");

            bool k = true;
            int y, i = 1, j = 1, m = 1, l = 0;

            string name;
            int quantity;

            cout << "Enter product name: ";
            cin >> name;

            cout << "Enter quantity to add: ";
            cin >> quantity;

            while (true) {
                for (auto& x : Fruits::fruits_stock) {
                    if (x.first == name) {
                        if (quantity > x.second.second) {
                            cout << "Insuffient quantity in stock" << endl;
                            cout << "Available in stock is " << x.second.second << endl;
                            cout << "\n\nRetake(0/1)";
                            cin >> y;
                            if (y == 1) {
                                add();
                            }
                        }
                        else {
                            for (auto& z : cart) {
                                if (z.first == name) {
                                    l = 1;
                                    z.second.first += quantity;
                                    z.second.second = x.second.second * z.second.first;
                                    cout << "Changes made" << endl;
                                    cout << "\n\nContinue: " << endl;
                                    cin >> y;
                                    return;
                                }
                                else {
                                    i = 0;
                                }
                            }
                            if (l != 1) {
                                y = 0;
                                cart.push_back(make_pair(name, make_pair(quantity, quantity * x.second.second)));
                            }    
                        }
                    }
                }

                if (y == 0) {
                    k = false;
                    break;
                }

                for (auto& x : Vegetables::vegetables_stock) {
                    if (x.first == name) {
                        if (quantity > x.second.second) {
                            cout << "Insuffient quantity in stock" << endl;
                            cout << "Available in stock is " << x.second.second << endl;
                            cout << "\n\nRetake(0/1)";
                            cin >> y;
                            if (y == 1) {
                                add();
                            }
                        }
                        else {
                            for (auto& z : cart) {
                                if (z.first == name) {
                                    l = 1;
                                    z.second.first += quantity;
                                    z.second.second = x.second.second * z.second.first;
                                    cout << "Changes made" << endl;
                                    cout << "\n\nContinue: " << endl;
                                    cin >> y;
                                    return;
                                }
                                else {
                                    j = 0;
                                }
                            }
                            if (l != 1) {
                                y = 0;
                                cart.push_back(make_pair(name, make_pair(quantity, quantity * x.second.second)));
                            }
                        }
                    }
                }

                if (y == 0) {
                    k = false;
                    break;
                }

                for (auto& x : Beverages::beverages_stock) {
                    if (x.first == name) {
                        if (quantity > x.second.second) {
                            cout << "Insuffient quantity in stock" << endl;
                            cout << "Available in stock is " << x.second.second << endl;
                            cout << "\n\nRetake(0/1)";
                            cin >> y;
                            if (y == 1) {
                                add();
                            }
                        }
                        else {
                            for (auto& z : cart) {
                                if (z.first == name) {
                                    l = 1;
                                    z.second.first += quantity;
                                    z.second.second = x.second.second * z.second.first;
                                    cout << "Changes made" << endl;
                                    cout << "\n\nContinue: " << endl;
                                    cin >> y;
                                    return;
                                }
                                else {
                                    m = 0;
                                }
                            }
                            if (l != 1) {
                                y = 0;
                                cart.push_back(make_pair(name, make_pair(quantity, quantity * x.second.second)));
                            }
                        }
                    }
                }

                if (y == 0) {
                    k = false;
                    break;
                }

                if ((i == 0) && (j == 0) && (m == 0)){
                    system("cls");
                    cout << "Enter product name: ";
                    cin >> name;
                    cout << "Enter product quantity: ";
                    cin >> quantity;
                }
            }
        }

        void checkout() {
            int i = 0, k;

            system("cls");

            cout << "Cart\n" << endl;

            cout << "Product\t\tQuantity\t\tPrice" << endl;

            for (const auto& x : cart) {
                cout << x.first << "\t\t" << x.second.first << "\t\t\t" << x.second.second << endl;
                total_price += x.second.second;
            }
            cout << "\nTotal Price:\t\t\t\t" << total_price << endl;

            cout << "\n*) Do you want to remove/add anything from cart?(0/1)\n*) Cart(2)\n*) Dashboard(3)\n*) Proceed to payment(4)\n\nPress: ";
            cin >> i;

            if (i == 1) {
                add();
                checkout();
            }
            else if (i == 0) {
                string product;
                int quantity;

                cout << "Enter product name: ";
                cin >> product;

                cout << "Enter quantity to remove: ";
                cin >> quantity;

                for (auto& x : cart) {
                    if (x.first == product) {
                        if (quantity > x.second.first) {
                            cout << "Not enough items in cart" << endl;
                            checkout();
                        }
                        else {
                            int product_price = x.second.second / x.second.first;
                            x.second.first -= quantity;
                            x.second.second = product_price * x.second.first;
                            if (x.second.first == 0) {
                                cart.erase(remove(cart.begin(), cart.end(), x), cart.end());
                            }
                            checkout();
                            break;
                        }
                    }
                }
            }
            else if (i == 2) {
                checkout();
            }
            else if (i == 3) {
                dashboard();
            }
            else {
                cout << "\n\nProceed to payment" << endl;

                cout << "\n\nContinue: ";
                cin >> k;

                payment();
            }
        }

        void payment() {
            Wallet& wallet = Wallet::getInstance();

            int k;

            wallet.payment(total_price, address);
            
            cart.clear();
            total_price = 0;

            cout << "\n\nContinue: ";
            cin >> k;

            dashboard();
        }

        void recommendation() {
            int i, k;
            vector<StoreItems> items;

            system("cls");
            
            for (const auto& x : Fruits::fruits_stock) {
                items.push_back(StoreItems(x.first, x.second.second, x.second.first));
            }

            for (const auto& x : Vegetables::vegetables_stock) {
                items.push_back(StoreItems(x.first, x.second.second, x.second.first));
            }

            for (const auto& x : Beverages::beverages_stock) {
                items.push_back(StoreItems(x.first, x.second.second, x.second.first));
            }

            cout << "Amount to shop: ";
            cin >> i;

            auto taken = testGreedys(items, i);

            cout << "\nAdd this to cart?(0/1) ";
            cin >> k;

            if (k == 1) {
                for (const auto& item : taken) {
                    cart.push_back(make_pair(item.first, make_pair(item.second.first, item.second.second)));

                    for (auto& x : Fruits::fruits_stock) {
                        if (item.first == x.first) {
                            x.second.first -= item.second.first;
                        }
                    }

                    for (auto& x : Vegetables::vegetables_stock) {
                        if (item.first == x.first) {
                            x.second.first -= item.second.first;
                        }
                    }

                    for (auto& x : Beverages::beverages_stock) {
                        if (item.first == x.first) {
                            x.second.first -= item.second.first;
                        }
                    }
                }
            }

            cout << "\n\nContinue: ";
            cin >> k;

            dashboard();
        }

        void container() {
            Block block;
            this -> address = block.calculateAddress("Mart");

            Vegetables::container();
            Beverages::container();
            Fruits::container();
        }
};