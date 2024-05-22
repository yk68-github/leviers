#include "leviers.h"

Leviers::Leviers()
{
    //ctor
    std::bitset<32> a = {1};
    std::bitset<32> b = {4};
    std::bitset<32> c = {11};
    std::bitset<32> d = {9};
    std::unordered_set<int> set1 = {4, 5};
    std::unordered_set<int> set2 = {7, 9};
    std::unordered_set<int> set3 = {3};
    std::unordered_set<int> set4 = {7, 9, 14, 15};

    m_calque = std::make_pair(a, set1);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(b, set2);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(c, set3);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(d, set4);
    m_VCalques.emplace_back(m_calque);

    std::cout << "Lancer la reduction\n" ; pause();

    AfficherBitsets();
    ReduireCalques();
    AfficherBitsets();

}

int Leviers::ConvertFromBin(string s)
{
    int total = 0;
    int base = 1;
    char c;

    for (int n = (s.size()-1); n>=0; n--)
    {
        c = s[n];
        if (c=='1') { total+=base; }
        base*=2;

    }
        return total;
}


Leviers::~Leviers()
{
    //dtor
}


void Leviers::FixerLongueur(int x)
{
    if ( (x<LONGUEURMINIMALE) || (x>LONGUEURMAXIMALE) )
        {
            throw std::invalid_argument("Length Error");
        }
}

const int Leviers::LireLongueur() const
{
    return m_longueur;
}

void  Leviers::ReduireCalques()
{
    iteratorVectorCalques it1 = m_VCalques.begin();

    bool toDelete = false;

    while (it1!=m_VCalques.end())
    {
            auto itToDelete = it1;
            toDelete = ConjuguerCalques(it1);
            std::cout << "to delete = " << toDelete << std::endl;
            it1++;
            if (toDelete)
            {
                m_VCalques.erase(itToDelete);
                toDelete = false;
            } else
            {
               auto element = *itToDelete;
               if ( (objectif | element.first) != objectif )
                {
                    m_VCalques.erase(itToDelete);
                    toDelete = false;
                }
            }
    }
}


bool Leviers::ConjuguerCalques(Leviers::iteratorVectorCalques it)
{
    auto element = *it;
    auto PremierSet = element.first;
    bool toDelete = false;

    iteratorVectorCalques boucle = m_VCalques.begin();

    while (boucle != m_VCalques.end() && (!(toDelete)))
    {
        element = *boucle;
        auto SecondSet = element.first;
        if (boucle!=it)
        {
                if ((SecondSet | PremierSet) == SecondSet)
                    toDelete = true;
        }
        boucle++;
    }

    return toDelete;
}

void Leviers::AfficherBitsets()
{
    for (auto r : m_VCalques)
    {
        Leviers::Calque element = r;
        std::cout << "bitset = " << element.first.to_string() << std::endl;
    }
    pause();
}

void Leviers::pause()
{
    std::cin.ignore();
    std::cin.get();
}
