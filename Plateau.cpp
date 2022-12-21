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

Plateau::Plateau() : coordonneesNeutron({ 3, 3 })
{
    for(unsigned int i = 0; i < 5; ++i)
    {
        for(unsigned int j = 0; i < 5; ++i)
        {
            if(i == 0)
                this->damier[i].push_back(0);
            else if(i == 4)
                this->damier[i].push_back(1);
            else if(i == 3 && j == 3)
                this->damier[i].push_back(2);
            else
                this->damier[i].push_back(-1);
        }
    }
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
    if((i + 1 < 5 && this->damier[i + 1][j] = -1) ||
       (i - 1 > -1 && this->damier[i - 1][j] = -1) ||
       (j + 1 < 5 && this->damier[i][j + 1] = -1) ||
       (j - 1 > -1 && this->damier[j - 1][j] = -1))
        return false;
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
    int ligne   = (1 - i / 4 - (i / 7) * (i / 4 % 2));
    int colonne = (((i + 1) % 3 % 2 - i % 3 % 2));

    if(this->damier[i][j] != pionValeur)
        return 1;
    unsigned int directionValide = 0;
    while(this->damier[ligne][colonne] == -1)
    {
        if(!directionValide)
        {
            directionValide == 1;
            this->damier[i][j] = -1;
        }
        i       = ligne;
        j       = colonne;
        ligne   = (1 - i / 4 - (i / 7) * (i / 4 % 2));
        colonne = (((j + 1) % 3 % 2 - j % 3 % 2));
    }
    if(directionValide)
    {
        this->damier[i][j] = pionValeur;
        if(pionValeur == 2)
            this->coordonneesNeutron[0] = i;
        this->coordonneesNeutron[1] = j;
        return 0;
    }
    return 2;
}