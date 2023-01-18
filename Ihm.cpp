/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        Ihm.h                                                               */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/14 by C. Trichet                                        */
/*   Updated: 2022/12/14 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#include "Ihm.h"
#include <iostream>

Ihm::Ihm()
{
}

Ihm::~Ihm()
{
}

void Ihm::afficherPlateau(const Plateau& plateau) const
{
    for(unsigned int ligne = 0; ligne < LARGEUR_DAMIER; ++ligne)
    {
        for(unsigned int indiceCase = 0; indiceCase < NB_TIRETS; ++indiceCase)
            std::cout << "_";
        std::cout << std::endl;
        for(unsigned int colonne = 0; colonne < LARGEUR_DAMIER; ++colonne)
            std::cout << "|   ";
        std::cout << "|" << std::endl;
        for(unsigned int colonne = 0; colonne < LARGEUR_DAMIER; ++colonne)
        {
            if(plateau.getContenuCase(ligne, colonne) == CASE_VIDE)
                std::cout << "|   ";
            else
                std::cout << "| " << plateau.getContenuCase(ligne, colonne)
                          << " ";
        }
        std::cout << "|" << std::endl;
    }
    for(unsigned int colonne = 0; colonne < NB_TIRETS; ++colonne)
        std::cout << "_";
    std::cout << std::endl;
}

void Ihm::definirJoueurs(unsigned int numero)
{
    std::cout << "Saisir le nom du ";
    if(numero == 1)
        std::cout << "second";
    else if(numero == 0)
        std::cout << "premier";
    std::cout << " joueur : ";
    std::cin >> this->joueurs[numero];
}

unsigned int Ihm::demandeUneDirection(bool joueurActif) const
{
    unsigned int choixDirection;
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << this << std::endl;
#endif
    std::cout << this->joueurs[joueurActif] << " doit saisir la direction : ";
    do
    {
        std::cin >> choixDirection;
        if(choixDirection == 5 || choixDirection == 0 || choixDirection > 9)
        {
            std::cout << "Choix invalide, resélectionnez une direction : ";
        }
    } while(choixDirection == 5 || choixDirection == 0 || choixDirection > 9);
    return choixDirection;
}

void Ihm::ecrireErreur(unsigned int erreur)
{
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << this << std::endl;
#endif
    switch(erreur)
    {
        case ERREUR_CASE_INVALIDE:
            std::cerr << "Il n'y a pas un de vos pion sur la case."
                      << std::endl;
            break;

        case ERREUR_PION_BLOQUE:
            std::cerr << "Ce pion ne peut pas être déplacé." << std::endl;
            break;

        case ERREUR_DIRECTION_INVALIDE:
            std::cerr << "Vous ne pouvez pas aller dans cette direction."
                      << std::endl;
            break;

        default:
            break;
    }
}

unsigned int Ihm::selectionneUnPion(bool joueurActif)
{
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << this << std::endl;
#endif
    unsigned int choixPion;

    std::cout << this->joueurs[joueurActif] << " doit choisir un pion : ";
    do
    {
        std::cin >> choixPion;
        if(choixPion / BASE >= LARGEUR_DAMIER &&
           choixPion % BASE >= LARGEUR_DAMIER)
        {
            std::cout << "Entrée invalide, rentrer à nouveau un pion : ";
        }
    } while(choixPion / BASE >= LARGEUR_DAMIER ||
            choixPion % BASE >= LARGEUR_DAMIER);
    return choixPion;
}

void Ihm::feliciter(bool joueurActif)
{
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << this << std::endl;
#endif
    std::cout << "Bravo " << this->joueurs[joueurActif] << std::endl;
}

void Ihm::afficherVersion()
{
    std::cout << "Jeu Neutron 1.1" << std::endl;
}