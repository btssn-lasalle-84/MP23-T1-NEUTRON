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

void Plateau::setCoordonneesNeutron(unsigned int ligne, unsigned int colonne)
{
    this->coordonneesNeutron[0] = ligne;
    this->coordonneesNeutron[1] = colonne;
}

unsigned int Plateau::getCoordonneesNeutron() const
{
    return (this->coordonneesNeutron[0] * BASE + this->coordonneesNeutron[1]);
}

unsigned int Plateau::getContenuCase(unsigned int ligne,
                                     unsigned int colonne) const
{
    return this->damier[ligne][colonne];
}

bool Plateau::pionEstCoince(unsigned int ligne /*=NEUTRON_XY*/,
                            unsigned int colonne /*=NEUTRON_XY*/) const
{
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    if(ligne == 5)
    {
        ligne   = this->coordonneesNeutron[0];
        colonne = this->coordonneesNeutron[1];
    }
    if((ligne + 1 < 5 &&
        (this->damier[ligne + 1][colonne] == CASE_VIDE ||
         (colonne + 1 < 5 && this->damier[ligne + 1][colonne + 1]) ||
         (int(colonne) - 1 > -1 && this->damier[ligne + 1][colonne - 1]))) ||
       (int(ligne) - 1 > -1 &&
        (this->damier[ligne - 1][colonne] == CASE_VIDE ||
         (colonne + 1 < 5 && this->damier[ligne - 1][colonne + 1]) ||
         (int(colonne) - 1 > -1 && this->damier[ligne - 1][colonne - 1]))) ||
       (colonne + 1 < 5 && this->damier[ligne][colonne + 1] == CASE_VIDE) ||
       (int(colonne) - 1 > -1 && this->damier[ligne - 1][colonne] == CASE_VIDE))
        return false;
    return true;
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << "sortie" << std::endl;
#endif
}

bool Plateau::pionsSontCoinces(bool joueurActif) const
{
    for(unsigned int ligne = 0; ligne < NB_LIGNES; ++ligne)
    {
        for(unsigned int colonne = 0; colonne < NB_COLONNES; ++colonne)
        {
            if(damier[ligne][colonne] == (unsigned int)joueurActif)
            {
                if(!pionEstCoince(ligne, colonne))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

int Plateau::deplaceUnPion(unsigned int direction,
                           unsigned int ligne /*=NEUTRON_XY*/,
                           unsigned int colonne /*=NEUTRON_XY*/,
                           unsigned int pionValeur /*=NEUTRON*/)
{
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    if(ligne == 5)
    {
        ligne   = this->coordonneesNeutron[0];
        colonne = this->coordonneesNeutron[1];
    }
#ifdef DEBUG
    std::cout << this->coordonneesNeutron[0] << this->coordonneesNeutron[1]
              << std::endl;
#endif
    if(this->damier[ligne][colonne] != pionValeur)
    {
#ifdef DEBUG
        std::cout << "pion pas à moi" << this->damier[ligne][colonne]
                  << pionValeur << std::endl;
#endif
        return ERREUR_CASE_INVALIDE;
    }
    if(this->pionEstCoince(ligne, colonne))
    {
#ifdef DEBUG
        std::cout << "pion est coincé" << std::endl;
#endif
        return ERREUR_PION_BLOQUE;
    }
    int nouvelleLigne =
      ligne +
      (1 - direction / 4 -
       (direction / 7) *
         (direction / 4 % 2)); // incrémente ou décrémente le numéro de la ligne
                               // en fonction de la direction choisie
    int nouvelleColonne =
      colonne +
      (((direction + 1) % 3 % 2 -
        direction % 3 % 2)); // incrémente ou décrémente le numéro de la colonne
                             // en fonction de la direction choisie
#ifdef DEBUG
    std::cout << nouvelleLigne << " " << nouvelleColonne << std::endl;
#endif
    unsigned int directionValide = 0;
    while(((nouvelleLigne < 5 && nouvelleLigne >= 0) &&
           (nouvelleColonne < 5 && nouvelleColonne >= 0)) &&
          this->damier[nouvelleLigne][nouvelleColonne] == CASE_VIDE)
    {
        if(!directionValide)
        {
#ifdef DEBUG
            std::cout << "Si direction invalide" << std::endl;
#endif
            directionValide              = 1;
            this->damier[ligne][colonne] = CASE_VIDE;
#ifdef DEBUG
            std::cout << "00 Pas le problème" << std::endl;
#endif
        }
        ligne   = nouvelleLigne;
        colonne = nouvelleColonne;
        nouvelleLigne =
          ligne + (1 - direction / 4 - (direction / 7) * (direction / 4 % 2));
        nouvelleColonne =
          colonne + (((direction + 1) % 3 % 2 - direction % 3 % 2));
    }
#ifdef DEBUG
    std::cout << "directionValide " << directionValide << std::endl;
#endif
    if(directionValide)
    {
        this->damier[ligne][colonne] = pionValeur;
        if(pionValeur == NEUTRON)
        {
            this->coordonneesNeutron[0] = ligne;
            this->coordonneesNeutron[1] = colonne;
        }
        return 0;
    }
#ifdef DEBUG
    std::cout << "Erreur direction invalide" << std::endl;
#endif
    return ERREUR_DIRECTION_INVALIDE;
}

unsigned int Plateau::neutronEstDansCamp() const
{
    switch(this->coordonneesNeutron[0])
    {
        case PREMIERE_LIGNE:
            return NEUTRON_CAMP_JOUEUR_0;
            break;
        case DERNIERE_LIGNE:
            return NEUTRON_CAMP_JOUEUR_1;
            break;
        default:
            return AUCUN_CAMP;
            break;
    }
}

unsigned int Plateau::calculerScore(bool joueurActif) const
{
    unsigned int score = 0;
    for(unsigned int ligne = 0; ligne < NB_LIGNES; ++ligne)
    {
        for(unsigned int colonne = 0; colonne < NB_COLONNES; ++colonne)
        {
            score += ((this->damier[ligne][colonne] + 3) / 3) % 2 *
                     (pow(-1, this->damier[ligne][colonne]) *
                        pow(ligne, (this->damier[ligne][colonne] + 1) % 2) *
                        pow(4 - ligne, this->damier[ligne][colonne]) +
                      this->calculeNbDeplacements(ligne, colonne));
        }
        score += this->calculeNbEmplacements(this->coordonneesNeutron[0],
                                             this->coordonneesNeutron[1]) *
                 pow(-1, joueurActif);
    }
}