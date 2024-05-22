#ifndef LEVIERS_H
#define LEVIERS_H

#include <iostream>

#include <cstdint>
#include <utility>
#include <unordered_set>
#include <vector>
#include <bitset>
#include <list>
#include <forward_list>
#include <iterator>
#include <algorithm>
#include <random>
#include <ctime>

using std::string;

class Leviers
{
    public:
        typedef std::pair<std::bitset<32>, std::unordered_set<int>> Calque;
        typedef std::list< std::pair <std::bitset<32>, std::unordered_set<int>> > VectorCalques;
        typedef std::list< std::pair <std::bitset<32>, std::unordered_set<int>> >::iterator iteratorVectorCalques;

        /** Default constructor */
        Leviers() = delete;
        Leviers(const std::bitset<32>&, const std::vector<std::bitset<32>>&);
        /** Default destructor */
        virtual ~Leviers();
        void FixerLongueur(int);
        const int LireLongueur() const;

    protected:

    private:

        static constexpr int LONGUEURMINIMALE = 0;
        static constexpr int LONGUEURMAXIMALE = 16;
        std::bitset<32> objectif = {255};
        int m_longueur = 0;
        Calque m_calque = {};
        VectorCalques m_VCalques = {};
        void ReduireCalques();
            bool ConjuguerCalques(Leviers::iteratorVectorCalques it);
        void Combiner();
        void AfficherBitsets(const VectorCalques&);
        int ConvertFromBin(string);
        void pause();
};

#endif // LEVIERS_H
