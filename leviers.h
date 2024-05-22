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
        enum class Conjugaison{ GARDERLESDEUX, GARDERPREMIER, GARDERSECOND };

        int m_longueur = 0;
        std::bitset<32> objectif;
        Calque m_calque = {};
        VectorCalques m_VCalques = {};
        void ReduireCalques(VectorCalques& m_VCalques);
        Conjugaison ConjuguerCalques(std::bitset<32>, std::bitset<32>);
        int ConvertFromBin(string);
        void pause();
};

#endif // LEVIERS_H
