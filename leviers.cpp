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
    std::cout << "objectif fixe sur " << m_objectif.to_string() << std::endl;
    std::vector<std::bitset<32>> bs = {};
    for (auto it : vecInt)
    {
        bs.push_back(std::bitset<32>(it));
    }
    Init(bs);
}

/* Init, les calculs se font ici */

void Leviers::Init(const std::vector<Bs32>& vec)
{
    ConstruireLCalques(vec);
    Solution.clear();

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

/* Créer une liste de paires (calque) / (référence(s) à l'indice dans le vecteur initial) */

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

/* D'abord vérifier si une solution existe, avant de la rechercher */

const bool Leviers::SolutionExiste() const //
{
    Bs32 BsCompare = {};
    int compteur = 0;

    for (const auto &it : m_LCalques)
    {
        BsCompare |= it.first;
        compteur++;
        if ((m_objectif & BsCompare) == m_objectif)
                {
                    std::cout << "La preuve qu'une solution existe a ete decouverte\n";
                    return true;
                }
    }  // end for
    std::cout << "Solution n'existe pas\n";
    std::cout << std::setw(32) << "Verification finale =    " << BsCompare.to_string() << std::endl;
    std::cout << std::setw(32) << "Sur objectif =           " << std::setw(32) << m_objectif.to_string() << std::endl;
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
    std::string str = "";
    std::string strObjectif = m_objectif.to_string();

    while ( (it1 != m_LCalques.end()) )
    {
        itToDelete = it1;
        it1++;
        element = *itToDelete;

        if ((m_objectif | (*itToDelete).first) != m_objectif)
        {
            str = (*itToDelete).first.to_string();
            m_LCalques.erase(itToDelete);  // Le calque est incompatible
            std::cout << "Calque incompatible " << str << "avec  " << strObjectif << std::endl;
            toDelete = false;
        }
        else
        {
            toDelete = Fusionner2Calques(itToDelete);
            if (toDelete)
            {
                str = (*itToDelete).first.to_string();
                m_LCalques.erase(itToDelete); // Le calque peut être absorbé
                std::cout << "Calque a supprimer " << str << std::endl;
                toDelete = false;
            }
        }
    } // end while
    std::cout << "Reste(nt) " << m_LCalques.size() << " calques.\n";
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
                    toDelete = true;
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

    iteratorListCalques it1 = m_LCalques.begin();
    iteratorListCalques it2 = m_LCalques.begin();

    std::cout << "Combinaison " << m_LCalques.size() << std::endl;

    std::cin.ignore();
    std::cin.get();

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
        }
    }
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

std::unordered_set<int> Leviers::LireSolution() const
{
    return Solution;
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
      m_longueur = x;
}

const int Leviers::LireLongueur() const
{
    return m_longueur;
}




