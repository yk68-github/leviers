#include "leviers.h"

Leviers::Leviers()
{
    //ctor
    std::bitset<32> a = {1};
    std::bitset<32> b = {4};
    std::bitset<32> c = {11};
    std::bitset<32> d = {129};
    std::unordered_set<int> set1 = {4, 5};
    std::unordered_set<int> set2 = {7, 9};
    std::unordered_set<int> set3 = {3};
    std::unordered_set<int> set4 = {7, 9, 14, 15};
/* Tests */


    Conjugaison resultat;
    resultat = ConjuguerCalques(a, b);

    if (resultat==Conjugaison::GARDERLESDEUX)
    {
        std::cout << "Garder les deux\n";
    } else if (resultat==Conjugaison::GARDERPREMIER)
            {
                std::cout << "Garder premier\n";
            } else // GARDERSECOND
            {
                std::cout << "Garder second\n";
            }


    string s = {"00001000"};
    std::cout << ConvertFromBin(s) << std::endl;

    m_calque = std::make_pair(a, set1);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(b, set2);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(c, set3);
    m_VCalques.emplace_back(m_calque);
    m_calque = std::make_pair(d, set4);
    m_VCalques.emplace_back(m_calque);

    Leviers::VectorCalques res = {};
    std::cout << "Avant appel" << std::endl;
    std::cin.ignore();
    std::cin.get();
    ReduireCalques(m_VCalques);
    std::cout << "Après appel" << std::endl;
    pause();

    for (auto r : res)
    {
        Leviers::Calque element = r;
        std::cout << "bitset = " << element.first.to_string() << std::endl;
    }

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

void Leviers::ReduireCalques(Leviers::VectorCalques& m_VCalques)
{
    int size = m_VCalques.size(); // Vérifier la taille !
    Conjugaison resultat;
    std::bitset<32> PremierSet = {};
    std::unordered_set<int> PremiereListe = {};
    std::bitset<32> SecondSet  = {};
    std::unordered_set<int> SecondeListe  = {};
    auto it1 = m_VCalques.begin();
    bool removed = false;

    while (it1!=m_VCalques.end())
    {
        Calque PremierElement = *it1;
        PremierSet = PremierElement.first;
        PremiereListe = PremierElement.second;

        std::cout << "Avant deuxieme boucle" << std::endl;
        pause();

        auto it2 = it1;
        it2++;

        while (it2!=m_VCalques.end() || (!(removed)))
        {
            Calque SecondElement = *it2;
            auto SecondSet = SecondElement.first;
            auto SecondListe = SecondElement.second;
            resultat = ConjuguerCalques(PremierSet, SecondSet);
            if ( (resultat==Conjugaison::GARDERPREMIER) || (resultat==Conjugaison::GARDERLESDEUX) )
                {
                      m_VCalques.erase(it2);
                      removed = true;
                } else it2++;

            if ( (resultat==Conjugaison::GARDERSECOND) || (resultat==Conjugaison::GARDERLESDEUX) )
                {
                        m_VCalques.erase(it1);
                        removed = true;
                }
        } // end while it2
        if ((it2 == m_VCalques.end())) it1++;
    } // end while it1
    return;
}



/*
        for (auto it2=(it+1);it2!=(m_VCalques.end()-1);++it2)
        {

        std::cout << "Pendant deuxieme boucle" << std::endl;
        pause();

            Calque SecondElement = *it2;
            SecondSet = SecondElement.first;
            SecondeListe = SecondElement.second;
            resultat = ConjuguerCalques(PremierSet, SecondSet);
            if ( (resultat==Conjugaison::GARDERPREMIER) || (resultat==Conjugaison::GARDERLESDEUX) )
                {
                        Retour.emplace_back(PremierElement);
                }

            if ( (resultat==Conjugaison::GARDERSECOND) || (resultat==Conjugaison::GARDERLESDEUX) )
                {
                        Retour.emplace_back(SecondElement);
                }
        } // end for it2
    } // end for it


*/


Leviers::Conjugaison Leviers::ConjuguerCalques(std::bitset<32> premier, std::bitset<32> second)
{
    Leviers::Conjugaison resultat;
    std::bitset<32> initial;
    bool ok = false;
/*
    std::cout << (string)premier.to_string() << std::endl;
    std::cout << (string)second.to_string() << std::endl;
*/
    if ( (premier.count()) >= (second.count()) )
        {
            initial=premier;
            premier|=second;
            if (premier==initial)
                {
                    resultat = Leviers::Conjugaison::GARDERPREMIER;
                    ok = true;
                }
        }
        else
        {
            initial = second;
            second|=premier;
            if (second==initial)
                {
                    resultat = Leviers::Conjugaison::GARDERSECOND;
                    ok = true;
                }
        }

        if (!(ok)) resultat = Leviers::Conjugaison::GARDERLESDEUX;

    return resultat;
}

void Leviers::pause()
{
    std::cin.ignore();
    std::cin.get();
}
