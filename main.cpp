#include <iostream>
#include <vector>
#include <bitset>
#include "leviers.h"

using namespace std;

int main()
{
    cout << "Test Leviers\n";

    std::bitset<32> objectif = {65535};
    std::bitset<32> a = {64};
    std::bitset<32> b = {127};
    std::bitset<32> c = {2127};
    std::bitset<32> d = {1527};

    vector<bitset<32>> v = {};
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);

    Leviers leviers(objectif, v);

    cin.get();
    return 0;
}
