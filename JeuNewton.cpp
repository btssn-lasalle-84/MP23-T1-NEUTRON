/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        JeuNewton.cpp                                                       */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/14 by C. Trichet                                        */
/*   Updated: 2022/12/14 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#include "JeuNewton.h"

JeuNewton::JeuNewton() : joueurActif(0)
{
}

JeuNewton::~JeuNewton()
{
    delete &this->ihm;
    delete &this->plateau;
}

void JeuNewton::setJoueurActif(bool joueurActif)
{
    this->joueurActif = joueurActif;
}

bool JeuNewton::getJoueurActif() const
{
    return this->joueurActif;
}

int JeuNewton::demarrer()
{
    bool premierCoup  = 1;
    bool partieGagnee = 0;

    this->ihm.definirJoueurs(0);
    this->ihm.definirJoueurs(1);
    while(!partieGagnee)
    {
        unsigned int entreeInvalide = 1;
        while(!entreeInvalide)
        {
            entreeInvalide = this->plateau.deplaceUnPion(
              this->ihm.demandeUneDirection(this->joueurActif));
            if(!entreeInvalide)
                this->ihm.ecrireErreur(entreeInvalide);
        }
        this->ihm.afficherPlateau(this->plateau);
        partieGagnee = this->plateau.pionEstCoince();
        if(!premierCoup && !partieGagnee)
        {
            entreeInvalide = 1;
            while(!entreeInvalide)
            {
                entreeInvalide = this->plateau.deplaceUnPion(
                  this->ihm.selectionneUnPion(this->joueurActif),
                  this->ihm.demandeUneDirection(this->joueurActif),
                  joueurActif);
            }
            this->ihm.afficherPlateau(this->plateau);
            partieGagnee =
              this->plateau.pionsSontCoinces(unsigned int joueurActif);
        }
        else
            premierCoup = 0;
        this->ihm.felicitater(joueurActif);
        this->joueurActif = (this->joueurActif + 1) % 2;
    }
    return 0;
}