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
#include <sstream>
#include <iomanip>

class Leviers
{
    public:
        typedef std::bitset<32> Bs32;
        typedef std::pair<std::bitset<32>, std::unordered_set<int>> Calque;
        typedef std::list< std::pair <std::bitset<32>, std::unordered_set<int>> > ListCalques;
        typedef std::list< std::pair <std::bitset<32>, std::unordered_set<int>> >::iterator iteratorListCalques;

        /** Default constructor deleted */
        Leviers() = delete;
        /** Constructors  */
        Leviers(const Bs32, const std::vector<std::bitset<32>>&);
        Leviers(const Bs32, const std::vector<int>&);
        Leviers(const int, const std::vector<std::bitset<32>>&);
        Leviers(const int, const std::vector<int>&);
        /** Default destructor */
        virtual ~Leviers();

        const std::unordered_set<int> LireSolution() const;

    protected:

    private:
        Bs32 m_objectif = Bs32(255);
        Calque m_calque = {};
        ListCalques m_LCalques = {};
        bool SolutionTrouvee = false;
        std::unordered_set<int> Solution = {};

        void Init(const std::vector<Bs32>&);
        void ConstruireLCalques(const std::vector<Bs32>&);

        void EffacerTropGrands();

        const bool SolutionExiste() const;

        void ReduireCalques();

        void Combiner();
        const bool Fusionner2Calques(Leviers::iteratorListCalques it);

        void VerifierSiSolution();
};

#endif // LEVIERS_H
