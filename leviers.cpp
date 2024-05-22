#include "leviers.h"

Leviers::Leviers(const std::bitset<32>& obj, const std::vector<std::bitset<32>>& vec)
{
    //ctor
    objectif = obj;
    std::unordered_set<int> FirstSet = {};
    for (int i = 0; i<(int)vec.size(); i++)
    {
        Calque element;
        FirstSet.emplace(i);
        element = std::make_pair(vec.at(i), FirstSet);
        m_VCalques.push_back(element);
        FirstSet.clear();
    }
/*
    std::bitset<32> a = {1};
    std::bitset<32> b = {2};
    std::bitset<32> c = {4};
    std::bitset<32> d = {8};
    std::bitset<32> e = {16};
    std::unordered_set<int> set1 = {1};
    std::unordered_set<int> set2 = {2};
    std::unordered_set<int> set3 = {3};
    std::unordered_set<int> set4 = {4};
    std::unordered_set<int> set5 = {5};

    m_calque = std::make_pair(a, set1);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(b, set2);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(c, set3);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(d, set4);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(e, set5);
    m_VCalques.emplace_back(m_calque);
*/
/*
    srand(time(NULL));
    std::unordered_set<int> set1 = {};
    for (int i = 0; i<16; i++)
    {
        set1.insert(i);
        m_VCalques.emplace_back(std::make_pair(std::bitset<32>(rand()%256), set1));
        set1.clear();
    }
*/

    std::cout << "Lancer la reduction\n" ; pause();

    AfficherBitsets(m_VCalques);
    ReduireCalques();
    std::cout << "Reste = " << std::endl;
    AfficherBitsets(m_VCalques);
    std::cout << "Combinaison\n";
    Combiner();
    AfficherBitsets(m_VCalques);
}

void Leviers::Combiner()
{
    Leviers::VectorCalques m_NewVCalques = {};
    Leviers::Calque PremierElement = {};
    Leviers::Calque SecondElement = {};

    std::bitset<32> PremierSet;
    std::unordered_set<int> PremiereListe;
    std::bitset<32> SecondSet;
    std::unordered_set<int> SecondeListe;
    iteratorVectorCalques it = m_VCalques.begin();
    iteratorVectorCalques it2 = m_VCalques.begin();

    std::bitset<32> NouveauSet = {};
    std::unordered_set<int> NouvelleListe = {};
    Calque NouvelElement = {};
    int i = 0;
    int j = 0;

    for(it=m_VCalques.begin(); it!=m_VCalques.end(); it++)
    {
        it2 = it; it2++;
        i++; std::cout << "i = " << i << std::endl;
        j = i;
        while (it2!=m_VCalques.end())
        {
           PremierElement = *it;
           SecondElement = *it2;
           PremierSet = PremierElement.first;
           SecondSet = SecondElement.first;
           PremiereListe = PremierElement.second;
           SecondeListe = SecondElement.second;

           NouveauSet = (PremierSet | SecondSet);
           NouvelleListe.insert(PremiereListe.begin(), PremiereListe.end());
           NouvelleListe.insert(SecondeListe.begin(), SecondeListe.end());
           NouvelElement = std::make_pair(NouveauSet, NouvelleListe);
           m_NewVCalques.emplace_back(NouvelElement);
           NouvelleListe.clear();
           j++; std::cout << "j = " << j << std::endl;
           it2++;
        }
    }
    m_VCalques.clear();
    m_VCalques = m_NewVCalques;
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
    Calque element = {};
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
               element = *itToDelete;
               if ( (objectif | element.first) != objectif )
                {
                    std::cout << "objectif                      " << objectif.to_string() << std::endl;
                    std::cout << "incompatibilite avec objectif " << element.first.to_string() << std::endl;
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

void Leviers::AfficherBitsets(const Leviers::VectorCalques& v)
{
    for (auto r : v)
    {
        Leviers::Calque element = r;
        std::cout << "bitset = " << element.first.to_string() << std::endl;
        std::cout << "liste = ";
        for(auto it : element.second)
        {
            std::cout << it << "  ";
        }
        std::cout << std::endl;
    }
    pause();
}

void Leviers::pause()
{
    std::cin.ignore();
    std::cin.get();
}
