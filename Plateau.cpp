/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        Plateau.cpp                                                         */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/14 by C. Trichet                                        */
/*   Updated: 2022/12/14 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#include "Plateau.h"

#ifdef DEBUG
#include <iostream>
#endif

Plateau::Plateau() :
    coordonneesNeutron{ 2, 2 }, damier{
        { PION_JOUEUR_0,
          PION_JOUEUR_0,
          PION_JOUEUR_0,
          PION_JOUEUR_0,
          PION_JOUEUR_0 },
        { CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE },
        { CASE_VIDE, CASE_VIDE, NEUTRON, CASE_VIDE, CASE_VIDE },
        { CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE },
        { PION_JOUEUR_1,
          PION_JOUEUR_1,
          PION_JOUEUR_1,
          PION_JOUEUR_1,
          PION_JOUEUR_1 }
    }
{
}

Plateau::~Plateau()
{
}

void Plateau::setCoordonneesNeutron(unsigned int i, unsigned int j)
{
    this->coordonneesNeutron[0] = i;
    this->coordonneesNeutron[1] = j;
}

unsigned int Plateau::getCoordonneesNeutron() const
{

    return (this->coordonneesNeutron[0] * 10 + this->coordonneesNeutron[1]);
}

unsigned int Plateau::getContenuCase(unsigned int i, unsigned int j) const
{
    return this->damier[i][j];
}

bool Plateau::pionEstCoince(unsigned int i /*=NEUTRON_XY*/,
                            unsigned int j /*=NEUTRON_XY*/) const
{
    if(i == 5)
    {
        i = this->coordonneesNeutron[0];
        j = this->coordonneesNeutron[1];
    }
    if((i + 1 < 5 && this->damier[i + 1][j] == CASE_VIDE) ||
       (int(i) - 1 > -1 && this->damier[i - 1][j] == CASE_VIDE) ||
       (j + 1 < 5 && this->damier[i][j + 1] == CASE_VIDE) ||
       (int(j) - 1 > -1 && this->damier[j - 1][j] == CASE_VIDE))
        return false;
    return true;
}

bool Plateau::pionsSontCoinces(bool joueurActif) const
{
    for(unsigned int i = 0; i < NB_LIGNES; ++i)
    {
        for(unsigned int j = 0; j < NB_COLONNES; ++j)
        {
            if(damier[i][j] == (unsigned int)joueurActif)
            {
                if(!pionEstCoince(i, j))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

int Plateau::deplaceUnPion(unsigned int direction,
                           unsigned int i /*=NEUTRON_XY*/,
                           unsigned int j /*=NEUTRON_XY*/,
                           unsigned int pionValeur /*=NEUTRON*/)
{
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    if(i == 5)
    {
        i = this->coordonneesNeutron[0];
        j = this->coordonneesNeutron[1];
    }
#ifdef DEBUG
    std::cout << this->coordonneesNeutron[0] << this->coordonneesNeutron[1]
              << std::endl;
#endif
    if(this->damier[i][j] != pionValeur)
    {
#ifdef DEBUG
        std::cout << "pion pas à moi" << this->damier[i][j] << pionValeur
                  << std::endl;
#endif
        return ERREUR_CASE_INVALIDE;
    }
    if(this->pionEstCoince(i, j))
    {
#ifdef DEBUG
        std::cout << "pion est coincé" << std::endl;
#endif
        return ERREUR_PION_BLOQUE;
    }
    int ligne = i + (1 - direction / 4 - (direction / 7) * (direction / 4 % 2));
    int colonne = j + (((direction + 1) % 3 % 2 - direction % 3 % 2));
#ifdef DEBUG
    std::cout << ligne << " " << colonne << std::endl;
#endif
    unsigned int directionValide = 0;
    while(this->damier[ligne][colonne] == CASE_VIDE)
    {
        if(!directionValide)
        {
#ifdef DEBUG
            std::cout << "Si direction invalide" << std::endl;
#endif
            ++directionValide;
            this->damier[i][j] = CASE_VIDE;
        }
        i     = ligne;
        j     = colonne;
        ligne = i + (1 - direction / 4 - (direction / 7) * (direction / 4 % 2));
        colonne = j + (((direction + 1) % 3 % 2 - direction % 3 % 2));
    }
    if(directionValide)
    {
        this->damier[i][j] = pionValeur;
        if(pionValeur == NEUTRON)
        {
            this->coordonneesNeutron[0] = i;
            this->coordonneesNeutron[1] = j;
        }
        return 0;
    }
#ifdef DEBUG
    std::cout << "Erreur direction invalide" << std::endl;
#endif
    return ERREUR_DIRECTION_INVALIDE;
}