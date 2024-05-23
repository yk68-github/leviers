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

class Leviers
{
    public:
        typedef std::pair<std::bitset<32>, std::unordered_set<int>> Calque;
        typedef std::list< std::pair <std::bitset<32>, std::unordered_set<int>> > ListCalques;
        typedef std::list< std::pair <std::bitset<32>, std::unordered_set<int>> >::iterator iteratorListCalques;

        /** Default constructor deleted */
        Leviers() = delete;
        /** Constructor  */
        Leviers(const std::bitset<32>&, const std::vector<std::bitset<32>>&);
        /** Default destructor */
        virtual ~Leviers();

        void FixerLongueur(int);
        const int LireLongueur() const;

    protected:

    private:
        static constexpr int LONGUEURMINIMALE = 0;
        static constexpr int LONGUEURMAXIMALE = 16;

        std::bitset<32> m_objectif = {255};
        int m_longueur = 0;
        Calque m_calque = {};
        ListCalques m_LCalques = {};

        void ReduireCalques();
        bool ConjuguerCalques(Leviers::iteratorListCalques it);
        void Combiner();

        int ConvertFromBin(std::string);
        void AfficherBitsets(const ListCalques&);
        void pause();
};

#endif // LEVIERS_H
