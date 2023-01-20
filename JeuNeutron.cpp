/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        JeuNeutron.cpp */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/14 by C. Trichet                                        */
/*   Updated: 2023/01/19 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#include "JeuNeutron.h"

JeuNeutron::JeuNeutron() : joueurActif(0)
{
}

JeuNeutron::~JeuNeutron()
{
}

void JeuNeutron::setJoueurActif(bool joueurActif)
{
    this->joueurActif = joueurActif;
}

bool JeuNeutron::getJoueurActif() const
{
    return this->joueurActif;
}

int JeuNeutron::demarrer()
{
    return this->jouerPartieUnJoueur();
}

int JeuNeutron::jouerPartieUnJoueur()
{
    this->ihm.afficherVersion();
    bool premierCoup   = 1;
    bool partieEnCours = 1;

    this->ihm.definirJoueurs(0);
    this->ihm.definirJoueurs(1);
    this->ihm.afficherInformations();
    this->ihm.afficherPlateau(this->plateau);
    while(partieEnCours)
    {
        if(this->plateau.pionEstCoince())
        {
            this->ihm.feliciter((joueurActif + 1) % 2);
            partieEnCours = 0;
        }
        else if(!premierCoup)
        {
            this->jouerUnCoup(1);
        }
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
        if(partieEnCours)
        {
            this->jouerUnCoup(0);
            premierCoup = 0;
        }
        this->joueurActif = (this->joueurActif + 1) % 2;
    }
    return 0;
}

void JeuNeutron::jouerUnCoup(bool estNeutron /*=1*/)
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
            ligne            = caseSelectionnee / BASE;
            colonne          = caseSelectionnee % BASE;
#ifdef DEBUG
            std::cout << "Tout va bien les copains" << std::endl;
#endif
            while(this->plateau.pionEstCoince(ligne, colonne))
            {
#ifdef DEBUG
                std::cout << "Tant que pionCoincé" << std::endl;
#endif
                this->ihm.ecrireErreur(ERREUR_CASE_INVALIDE);
                caseSelectionnee = this->ihm.selectionneUnPion(joueurActif);
                ligne            = caseSelectionnee / BASE;
                colonne          = caseSelectionnee % BASE;
            }
#ifdef DEBUG
            std::cout << "Pion non Coincé" << std::endl;
#endif
            pionNonSelectionne = 0;
        }
#ifdef DEBUG
        std::cout << "Pion bien selectionne" << std::endl;
#endif
        if(this->plateau.getContenuCase(ligne, colonne) ==
           (unsigned int)joueurActif)
            direction = this->ihm.demandeUneDirection(this->joueurActif);
        else
            direction = 8;
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

int JeuNeutron::jouerPartieUnJoueur()
{
    bool premierCoup   = true;
    bool partieEnCours = true;
    this->joueurActif  = this->ihm.choisirPremierJoueur(true);

    this->ihm.definirJoueurs(0);
    this->ihm.afficherPlateau(this->plateau);
    while(partieEnCours)
    {
        if(this->plateau.pionEstCoince())
        {
            this->ihm.feliciter((joueurActif + 1) % 2);
            partieEnCours = 0;
        }
        else if(!premierCoup)
        {
            if(this->joueurActif)
                this->IAJoueUnCoup(1) else this->jouerUnCoup(1);
        }
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
        if((partieEnCours && joueurActif == 0) ||)
        {
            if(this->joueurActif)
                this->IAJoueUnCoup(0) else this->jouerUnCoup(0);
            premierCoup = 0;
        }
        this->joueurActif = (this->joueurActif + 1) % 2;
    }
    return 0;
}
