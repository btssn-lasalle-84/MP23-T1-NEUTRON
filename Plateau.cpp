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

Plateau::Plateau() :
    coordonneesNeutron{ 3, 3 }, damier{ { 0, 0, 0, 0, 0 },
                                        { -1, -1, -1, -1, -1 },
                                        { -1, -1, 2, -1, -1 },
                                        { -1, -1, -1, -1, -1 },
                                        { 1, 1, 1, 1, 1 } }
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

std::vector<unsigned int> Plateau::getCoordonneesNeutron() const
{
    std::vector<unsigned int> coordonnees = { this->coordonneesNeutron[0],
                                              this->coordonneesNeutron[1] };
    return (coordonnees);
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
    if((i + 1 < 5 && this->damier[i + 1][j] == -1) ||
       (int(i) - 1 > -1 && this->damier[i - 1][j] == -1) ||
       (j + 1 < 5 && this->damier[i][j + 1] == -1) ||
       (int(j) - 1 > -1 && this->damier[j - 1][j] == -1))
        return false;
    return true;
}

bool Plateau::pionsSontCoinces(bool joueurActif) const
{
    for(unsigned int i = 0; i < NB_LIGNES; ++i)
    {
        for(unsigned int j = 0; j < NB_COLONNES; ++j)
        {
            if(damier[i][j] == int(joueurActif))
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
                           unsigned int pionValeur /*=2*/)
{
    if(i == 5)
    {
        i = this->coordonneesNeutron[0];
        j = this->coordonneesNeutron[1];
    }

    if(this->damier[i][j] != int(pionValeur))
        return 1;
    if(this->pionEstCoince(i, j))
        return 2;
    int ligne = i + (1 - direction / 4 - (direction / 7) * (direction / 4 % 2));
    int colonne = j + (((direction + 1) % 3 % 2 - direction % 3 % 2));
    unsigned int directionValide = 0;
    while(this->damier[ligne][colonne] == -1)
    {
        if(!directionValide)
        {
            directionValide    = 1;
            this->damier[i][j] = -1;
        }
        i     = ligne;
        j     = colonne;
        ligne = i + (1 - direction / 4 - (direction / 7) * (direction / 4 % 2));
        colonne = j + (((direction + 1) % 3 % 2 - direction % 3 % 2));
    }
    if(directionValide)
    {
        this->damier[i][j] = int(pionValeur);
        if(pionValeur == 2)
        {
            this->coordonneesNeutron[0] = i;
            this->coordonneesNeutron[1] = j;
        }
        return 0;
    }
    return 3;
}