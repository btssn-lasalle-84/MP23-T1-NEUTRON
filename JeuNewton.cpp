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
        if(this->plateau.pionEstCoince())
        {
            partieGagnee = 1;
            this->ihm.feliciter((joueurActif + 1) % 2);
        }
        this->jouerUnCoup(1);
        int campNeutron = this->plateau.neutronDansCamp();
        if(campNeutron == CASE_NEUTRE)
        {
            partieGagnee = 1;
            this->ihm.feliciter(campNeutron);
        }
        if(this->plateau.pionsSontCoinces(joueurActif))
        {
            partieGagnee = 1;
            this->ihm.feliciter((joueurActif + 1) % 2);
        }
        if(! premierCoup)
            this->jouerUnCoup(0);
        premierCoup = 0;
    }
    return 0;
}

void JeuNewton::jouerUnCoup(bool estNeutron /*=1*/)
{
    unsigned int direction;
    unsigned int erreur;
    bool directionInvalide = 1, pionNonSelectionne = 1;
    unsigned int pionValeur, caseSelectionne;
    unsigned int i, j;

    while(directionInvalide)
    {
        if(estNeutron)
        {
            caseSelectionne = this->plateau.getCoordonneesNeutron();
            i = caseSelectionne / 10;
            j = caseSelectionne % 10;
            pionValeur = NEUTRON;
        }
        else if(pionNonSelectionne)
        {
            pionValeur = (unsigned int)this->joueurActif;
            caseSelectionne = this->ihm.selectionneUnPion(joueurActif);
            while (this->plateau.pionEstCoince(i, j))
            {
                this->ihm.ecrireErreur(ERREUR_CASE_INVALIDE);
                caseSelectionne = this->ihm.selectionneUnPion(joueurActif);
            }
            pionNonSelectionne = 0;
            i = caseSelectionne / 10;
            j = caseSelectionne % 10;
        }
        direction = this->ihm.demandeUneDirection(this->joueurActif);
        erreur = this->plateau.deplaceUnPion(direction, i, j, pionValeur);
        if(! erreur)
            directionInvalide = 0;
        else
            this->ihm.ecrireErreur(erreur);
    }
    this->ihm.afficherPlateau(this->plateau);
}

