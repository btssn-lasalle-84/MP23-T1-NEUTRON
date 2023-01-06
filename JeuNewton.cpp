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
    unsigned int direction = DIRECTION_IMPOSSIBLE;

    this->ihm.definirJoueurs(0);
    this->ihm.definirJoueurs(1);
    while(!partieGagnee)
    {
        unsigned int entreeInvalide = 0;
        this->ihm.afficherPlateau(this->plateau);
        while(!entreeInvalide)
        {
            direction = this->ihm.demandeUneDirection(this->joueurActif);
            entreeInvalide = this->plateau.deplaceUnPion(direction);
            this->ihm.ecrireErreur(entreeInvalide);
        }
        this->plateau.deplaceUnPion(direction);
        this->ihm.afficherPlateau(this->plateau);
        partieGagnee = this->plateau.pionEstCoince();
#ifdef DEBUG
    std::cout << partieGagnee << std::endl;
#endif
        if(!premierCoup && !partieGagnee)
        {
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << this << std::endl;
#endif
            entreeInvalide = 0;
            while(!entreeInvalide)
            {
                entreeInvalide = this->plateau.deplaceUnPion(
                  this->ihm.selectionneUnPion(this->joueurActif),
                  this->ihm.demandeUneDirection(this->joueurActif),
                  joueurActif);
            }
            this->ihm.afficherPlateau(this->plateau);
            partieGagnee =
              this->plateau.pionsSontCoinces(joueurActif);
        }
        else
            premierCoup = 0;
        this->joueurActif = (this->joueurActif + 1) % 2;
    }
    this->ihm.feliciter(joueurActif);
    return 0;
}