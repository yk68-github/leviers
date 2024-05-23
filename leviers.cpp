#include "leviers.h"

Leviers::Leviers(const std::bitset<32>& obj, const std::vector<std::bitset<32>>& vec)
{
    //ctor
    m_objectif = obj;
    std::unordered_set<int> FirstSet = {};

    for (int LineNumber = 0; LineNumber<(int)vec.size(); LineNumber++)
    {
        Calque element;
        FirstSet.emplace(LineNumber);
        element = std::make_pair(vec.at(LineNumber), FirstSet);
        m_LCalques.push_back(element);
        FirstSet.clear();
    }

    AfficherBitsets(m_LCalques);
    ReduireCalques();
    AfficherBitsets(m_LCalques);
    Combiner();
    AfficherBitsets(m_LCalques);
}

void Leviers::Combiner()
{
    Leviers::ListCalques NewLCalques = {};
    Leviers::Calque PremierElement = {};
    Leviers::Calque SecondElement = {};

    std::bitset<32> PremierSet;
    std::unordered_set<int> PremiereListe;
    std::bitset<32> SecondSet;
    std::unordered_set<int> SecondeListe;
    iteratorListCalques it = m_LCalques.begin();
    iteratorListCalques it2 = m_LCalques.begin();

    std::bitset<32> NouveauSet = {};
    std::unordered_set<int> NouvelleListe = {};
    Calque NouvelElement = {};

    for(it=m_LCalques.begin(); it!=m_LCalques.end(); it++)
    {
        it2 = it; it2++;
        while (it2!=m_LCalques.end())
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
           NewLCalques.emplace_back(NouvelElement);
           NouvelleListe.clear();
           it2++;
        }
    }
    m_LCalques.clear();
    m_LCalques = NewLCalques;
}


int Leviers::ConvertFromBin(std::string s)
{
    int total = 0;
    int base = 1;
    char c;

    for (int i = (s.size()-1); i>=0; i--)
    {
        c = s[i];
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
    iteratorListCalques it1 = m_LCalques.begin();
    Calque element = {};
    bool toDelete = false;

    while (it1!=m_LCalques.end())
    {
            auto itToDelete = it1;
            toDelete = Fusionner2Calques(it1);
            it1++;
            if (toDelete)
            {
                m_LCalques.erase(itToDelete);
                toDelete = false;
            }
            else
            {
               element = *itToDelete;
               if ( (m_objectif | element.first) != m_objectif )
                {
                    std::cout << "m_objectif                      " << m_objectif.to_string() << std::endl;
                    std::cout << "incompatibilite avec m_objectif " << element.first.to_string() << std::endl;
                    m_LCalques.erase(itToDelete);
                    toDelete = false;
                }
            }
    }
}

bool Leviers::Fusionner2Calques(Leviers::iteratorListCalques it)
{
    auto element = *it;
    auto PremierSet = element.first;
    bool toDelete = false;

    iteratorListCalques boucle = m_LCalques.begin();

    while (boucle != m_LCalques.end() && (!(toDelete)))
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

void Leviers::AfficherBitsets(const Leviers::ListCalques& lc)
{
    for (auto it1 : lc)
    {
        Leviers::Calque element = it1;
        std::cout << "bitset = " << element.first.to_string() << std::endl;
        std::cout << "liste = ";
        for(auto it2 : element.second) // loop unordered_set
        {
            std::cout << it2 << "  ";
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
