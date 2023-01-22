/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        JeuNeutron.cpp                                                      */
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
    bool fin = false;

    this->ihm.effacerEcran();
    this->ihm.afficherVersion();

    do
    {
        unsigned int choix = this->ihm.afficherMenu();
        switch(choix)
        {
            case LANCER_PARTIE:
                this->jouerPartieUnJoueur();
                break;

            case HISTORIQUE:
                break;

            case AFFICHER_REGLES:
                this->ihm.afficherRegles();
                break;

            case QUITTER_JEU:
                fin = true;

            default:
                break;
        }
    } while(!fin);

    return 0;
}

int JeuNeutron::jouerPartieUnJoueur()
{
    bool premierCoup   = true;
    bool partieEnCours = true;
    bool unJoueur      = false;
    bool joueurDeuxCommence;

    this->ihm.definirJoueurs(0);
    this->ihm.definirJoueurs(1);
    joueurDeuxCommence = this->ihm.choisirPremierJoueur(unJoueur);
    if(joueurDeuxCommence)
    {
        this->ihm.changerOrdreJoueur();
    }

    this->ihm.afficherInformations();
    this->ihm.afficherPlateau(this->plateau);
    while(partieEnCours)
    {
        if(this->plateau.pionEstCoince())
        {
            this->ihm.feliciter((joueurActif + 1) % 2);
            partieEnCours = false;
        }
        else if(!premierCoup)
        {
            this->jouerUnCoup(1);
        }
        int campNeutron = this->plateau.neutronEstDansCamp();
        if(campNeutron != CASE_NEUTRE)
        {
            this->ihm.feliciter(campNeutron);
            partieEnCours = false;
        }
        if(this->plateau.pionsSontCoinces(joueurActif))
        {
#ifdef DEBUG
            std::cout << "Les pions du joueur " << joueurActif << "sont coincés"
                      << std::endl;
#endif
            this->ihm.feliciter((joueurActif + 1) % 2);
            partieEnCours = false;
        }
        if(partieEnCours)
        {
            this->jouerUnCoup(0);
            premierCoup = false;
        }
        this->joueurActif = (this->joueurActif + 1) % 2;
    }
    return 0;
}

void JeuNeutron::jouerUnCoup(bool estNeutron /*=true*/)
{
    unsigned int direction;
    unsigned int erreur;
    bool         directionInvalide = true, pionNonSelectionne = true;
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
            pionNonSelectionne = false;
        }
#ifdef DEBUG
        std::cout << "Pion bien selectionne" << std::endl;
#endif
        if(this->plateau.getContenuCase(ligne, colonne) ==
             (unsigned int)joueurActif ||
           (estNeutron &&
            this->plateau.getContenuCase(ligne, colonne) == NEUTRON))
            direction = this->ihm.demandeUneDirection(this->joueurActif);
        else
            direction = 8;
        erreur =
          this->plateau.deplaceUnPion(direction, ligne, colonne, pionValeur);
        if(!erreur)
            directionInvalide = false;
        else
        {
            this->ihm.ecrireErreur(erreur);
            if(!estNeutron)
                pionNonSelectionne = true;
        }
    }
    this->ihm.effacerEcran();
    this->ihm.afficherPlateau(this->plateau);
}
