#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_set>
#include <random>
#include <ctime>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>

#include "leviers.h"

using namespace std;

int main()
{
    cout << "Test Leviers\n";
    srand(time(NULL));

    vector<int> v1 = {};
    std::vector<int> v2 = {1, 2, 4, 8, 16, 32, 64, 128};
    int rd = 0;
    int val = 0;
    int obj = 32767;

    for (int i = 0; i<50; i++)
    {
        for (int j = 0;j<3;j++)
            {
                rd = rand()%16;
                val += std::pow(2, rd);
            }
        v1.push_back(val);
        val=0;
    }

    std::unordered_set<int> Sol = {};

    Leviers leviers1(obj, v1);
    Sol = leviers1.LireSolution();

    std::cout << "Sol Size = " << Sol.size() << std::endl;
    std::cout << "Solution a la fin\n";
    std::bitset<32> bssol;

    std::cout << std::setw(4) << "obj" << " = " << std::bitset<32>(obj).to_string() << std::endl;
    for (auto SolLev : Sol)
    {
        bssol=v1.at(SolLev);
        std::cout << std::setw(4) << SolLev << " = " << bssol.to_string() << std::endl;
    }

    Sol.clear();
/*
    std::cout << "--------------------------------------" << std::endl;

    Leviers leviers2 (255, v2);

    Sol = leviers2.LireSolution();
    std::cout << "Sol Size = " << Sol.size() << std::endl;
    std::cout << "Solution a la fin\n";
    for (auto SolLev : Sol)
    {
        std::cout << SolLev << std::endl;
    }
*/
    cin.ignore();
    cin.get();
    return 0;
}
