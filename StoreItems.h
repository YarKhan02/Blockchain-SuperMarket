#include <string>

using namespace std;

class StoreItems {
    private:
        string name;
        double cost;
        double weight;
    public:
        StoreItems(string n, double v, double w) : name(n), cost(v), weight(w) {}

        string getName() const {
            return name;
        }

        double getCost() const {
            return cost;
        }

        double getWeight() const {
            return weight;
        }

        double density() const {
            return getCost() / getWeight();
        }
};
