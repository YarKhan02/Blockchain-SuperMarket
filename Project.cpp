#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <list>
#include <iomanip>
#include <utility>
#include <sstream>
#include <algorithm>
#include <openssl/sha.h>
#include "json.hpp"
#include <fstream>

#include "Control.h"

using namespace std;
using json = nlohmann::json;

int main(){
    Control c;
    c.controller();

    return 0;
}