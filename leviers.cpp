#include "leviers.h"

/* 4 constructeurs */

Leviers::Leviers(const Bs32 obj, const std::vector<Bs32>& vec)
{
    //ctor
    m_objectif = obj;
    Init(vec);
}

Leviers::Leviers(const Bs32 obj, const std::vector<int>& vecInt)
{
    m_objectif = obj;

    std::vector<std::bitset<32>> bs = {};
    for (auto it : vecInt)
    {
        bs.push_back(Bs32(it));
    }
    Init(bs);
}

Leviers::Leviers(const int obj, const std::vector<Bs32>& vec)
{
    m_objectif = std::bitset<32>(obj);
    Init(vec);
}

Leviers::Leviers(const int obj, const std::vector<int>& vecInt)
{
    m_objectif = std::bitset<32>(obj);
    std::vector<std::bitset<32>> bs = {};
    for (auto it : vecInt)
    {
        bs.push_back(std::bitset<32>(it));
    }
    Init(bs);
}

Leviers::~Leviers()
{
    //dtor
}

/* Init, les calculs se font ici */

void Leviers::Init(const std::vector<Bs32>& vec)
{
    ConstruireLCalques(vec);
    EffacerTropGrands();

    if (SolutionExiste())
    {
        VerifierSiSolution();
        while (!(SolutionTrouvee))
            {
                ReduireCalques();
                Combiner();
                VerifierSiSolution();
            }  // end while
    }  // end if
}

/* Créer une liste de paires (calque) / (référence(s) dans le vecteur initial) */

void Leviers::ConstruireLCalques(const std::vector<std::bitset<32>>& vec)
{
    std::unordered_set<int> FirstSet = {};
    Calque element;

    for (int LineNumber = 0; LineNumber<(int)vec.size(); LineNumber++)
    {
        FirstSet.emplace(LineNumber);
        element = std::make_pair(vec.at(LineNumber), FirstSet);
        m_LCalques.push_back(element);
        FirstSet.clear();
    }
}

void Leviers::EffacerTropGrands()
{
    iteratorListCalques it = m_LCalques.begin();
    iteratorListCalques itToDelete;
    Bs32 bs = {};
    while (it != m_LCalques.end())
    {
        itToDelete = it;
        bs = (*itToDelete).first;
        it++;
        if (bs.to_ullong() > m_objectif.to_ullong())
        {
            m_LCalques.erase(itToDelete); // calque trop grand
        }
    }
}

/* D'abord vérifier si une solution existe, avant de la rechercher */

const bool Leviers::SolutionExiste() const //
{
    Bs32 BsCompare = {};

    for (const auto &it : m_LCalques)
    {
        BsCompare |= it.first;
        if ((m_objectif & BsCompare) == m_objectif)
                {
                    return true;
                }
    }  // end for
    return false; //
}

/* Certains calques peuvent-ils être absorbés par d'autres (réduction) : si oui, effacement */
/* Si le calque est incompatible avec l'objectif, effacement */

void  Leviers::ReduireCalques()
{
    iteratorListCalques it1 = m_LCalques.begin();
    iteratorListCalques itToDelete = {};
    Calque element = {};
    bool toDelete = false;

    while ( (it1 != m_LCalques.end()) )
    {
        itToDelete = it1;
        it1++;
        element = *itToDelete;

        if ((m_objectif | (*itToDelete).first) != m_objectif)
        {
            m_LCalques.erase(itToDelete);  // Le calque est incompatible
            toDelete = false;
        }
        else
        {
            toDelete = Fusionner2Calques(itToDelete);
            if (toDelete)
            {
                m_LCalques.erase(itToDelete); // Le calque peut être absorbé
                toDelete = false;
            }
        }
    } // end while
}

/*  Comparer deux calques : si le premier est inclus dans le deuxième, on renvoie true */

const bool Leviers::Fusionner2Calques(Leviers::iteratorListCalques it)
{
    Calque element = *it;
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
                {
                    toDelete = true;
                }
        }
        boucle++;
    }
    return toDelete;
}

/* Processus de fusion de calques */

void Leviers::Combiner()
{
    ListCalques NouveauLCalques = {};
    Calque NouvelElement = {};

    std::bitset<32> PremierSet;
    std::unordered_set<int> PremiereListe;

    std::bitset<32> SecondSet;
    std::unordered_set<int> SecondeListe;

    std::bitset<32> NouveauSet = {};
    std::unordered_set<int> NouvelleListe = {};

    iteratorListCalques it1 = {};
    iteratorListCalques it2 = {};

    for(it1=m_LCalques.begin(); it1!=m_LCalques.end(); it1++)
    {
        it2 = it1; it2++;

        while (it2!=m_LCalques.end())
        {
           PremierSet = (*it1).first;
           SecondSet = (*it2).first;
           PremiereListe = (*it1).second;
           SecondeListe = (*it2).second;

           NouveauSet = (PremierSet | SecondSet);

           NouvelleListe.insert(PremiereListe.begin(), PremiereListe.end());
           NouvelleListe.insert(SecondeListe.begin(), SecondeListe.end());
           NouvelElement = std::make_pair(NouveauSet, NouvelleListe);
           NouveauLCalques.emplace_back(NouvelElement);
           NouvelleListe.clear();
           it2++;
        } // end while
    }  // end for

    m_LCalques.clear();
    m_LCalques = NouveauLCalques;
}

void Leviers::VerifierSiSolution()
{
    iteratorListCalques it = m_LCalques.begin();
    while (it!=m_LCalques.end() && (!SolutionTrouvee))
    {
        if ( (*it).first==m_objectif )
        {
            SolutionTrouvee = true;
            Solution = (*it).second;
        }
        it++;
    }
    return;
}

const std::unordered_set<int> Leviers::LireSolution() const  // public
{
    return Solution;  // vide si pas de solution
}





