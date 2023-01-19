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
    std::cin >> choixDirection;

    while(choixDirection == DIRECTION_IMPOSSIBLE_1 ||
          choixDirection == DIRECTION_IMPOSSIBLE_2 || choixDirection >= BASE)
    {
        std::cout << "Choix invalide, resélectionnez une direction : ";
        std::cin >> choixDirection;
    }
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
            std::cerr << "Il n'y a pas un de vos pions sur la case."
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
    std::cin >> choixPion;

    while(choixPion / BASE >= LARGEUR_DAMIER ||
          choixPion % BASE >= LARGEUR_DAMIER)
    {
        std::cout << "Entrée invalide, rentrer à nouveau un pion : ";
        std::cin >> choixPion;
    }
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << "sortie" << this << std::endl;
#endif
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
    std::cout << "Jeu Neutron 1.3" << std::endl;
}

void Ihm::afficherInformations()
{
    std::cout << this->joueurs[0] << " jouera avec les pions 0 et "
              << this->joueurs[1]
              << " jouera avec les pions 1. Le pion 2 est le neutron."
              << std::endl;
}