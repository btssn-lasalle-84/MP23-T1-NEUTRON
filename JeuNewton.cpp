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
    return this->jouerPartieUnJoueur();
}

int JeuNewton::jouerPartieUnJoueur()
{
    this->ihm.afficherVersion();
    bool premierCoup   = 1;
    bool partieEnCours = 1;

    this->ihm.definirJoueurs(0);
    this->ihm.definirJoueurs(1);
    this->ihm.afficherPlateau(this->plateau);
    while(partieEnCours)
    {
        if(this->plateau.pionEstCoince())
        {
            this->ihm.feliciter((joueurActif + 1) % 2);
            partieEnCours = 0;
        }
        else
            this->jouerUnCoup(1);
        int campNeutron = this->plateau.neutronEstDansCamp();
        if(campNeutron != CASE_NEUTRE)
        {
            this->ihm.feliciter(campNeutron);
            partieEnCours = 0;
        }
        if(this->plateau.pionsSontCoinces(joueurActif))
        {
#ifdef DEBUG
            std::cout << "Les pions du joueur " << joueurActif << "sont coincés"
                      << std::endl;
#endif
            this->ihm.feliciter((joueurActif + 1) % 2);
            partieEnCours = 0;
        }
        if(partieEnCours && !premierCoup)
            this->jouerUnCoup(0);
        this->joueurActif = (this->joueurActif + 1) % 2;
        premierCoup       = 0;
    }
    return 0;
}

void JeuNewton::jouerUnCoup(bool estNeutron /*=1*/)
{
    unsigned int direction;
    unsigned int erreur;
    bool         directionInvalide = 1, pionNonSelectionne = 1;
    unsigned int pionValeur, caseSelectionnee;
    unsigned int ligne, colonne;
#ifdef DEBUG
    std::cout << "estNeutron" << estNeutron << std::endl;
#endif
    while(directionInvalide)
    {
        if(estNeutron)
        {
            caseSelectionnee = this->plateau.getCoordonneesNeutron();
            ligne            = caseSelectionnee / BASE;
            colonne          = caseSelectionnee % BASE;
            pionValeur       = NEUTRON;
        }
        else if(pionNonSelectionne)
        {
            pionValeur       = (unsigned int)this->joueurActif;
            caseSelectionnee = this->ihm.selectionneUnPion(joueurActif);
            while(this->plateau.pionEstCoince(ligne, colonne))
            {
                this->ihm.ecrireErreur(ERREUR_CASE_INVALIDE);
                caseSelectionnee = this->ihm.selectionneUnPion(joueurActif);
            }
            pionNonSelectionne = 0;
            ligne              = caseSelectionnee / BASE;
            colonne            = caseSelectionnee % BASE;
        }
        direction = this->ihm.demandeUneDirection(this->joueurActif);
        erreur =
          this->plateau.deplaceUnPion(direction, ligne, colonne, pionValeur);
        if(!erreur)
            directionInvalide = 0;
        else
        {
            this->ihm.ecrireErreur(erreur);
            if(!estNeutron)
                pionNonSelectionne = 1;
        }
    }
    this->ihm.afficherPlateau(this->plateau);
}
