#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_set>
#include <random>
#include <ctime>
#include <string>
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

    for (int i = 0; i<1000; i++)
    {
        rd = rand()%8192;
        v1.push_back(rd);
    }


    v1.push_back(16384);
    v1.push_back(8192);

    std::unordered_set<int> Sol = {};


    Leviers leviers1(32767, v1);
    Sol = leviers1.LireSolution();

    std::cout << "Sol Size = " << Sol.size() << std::endl;
    std::cout << "Solution a la fin\n";
    std::bitset<32> bssol;

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
