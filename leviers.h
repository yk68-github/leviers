#ifndef LEVIERS_H
#define LEVIERS_H

#include <iostream>

#include <cstdint>
#include <utility>
#include <unordered_set>
#include <vector>
#include <bitset>
#include <list>

using std::string;

class Leviers
{
    public:
        typedef std::pair<std::bitset<32>, std::unordered_set<int>> Calque;
        typedef std::list< std::pair <std::bitset<32>, std::unordered_set<int>> > VectorCalques;
        typedef std::list< std::pair <std::bitset<32>, std::unordered_set<int>> >::iterator iteratorVectorCalques;

        /** Default constructor */
        Leviers();
        /** Default destructor */
        virtual ~Leviers();
        void FixerLongueur(int);
        const int LireLongueur() const;

    protected:

    private:

        static constexpr int LONGUEURMINIMALE = 0;
        static constexpr int LONGUEURMAXIMALE = 16;
        std::bitset<32> objectif = {7};
        int m_longueur = 0;
        Calque m_calque = {};
        VectorCalques m_VCalques = {};
        void ReduireCalques();
        bool ConjuguerCalques(Leviers::iteratorVectorCalques it);
        void AfficherBitsets();
        int ConvertFromBin(string);
        void pause();
};

#endif // LEVIERS_H
