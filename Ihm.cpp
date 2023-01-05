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
    for(unsigned int i = 0; i < LARGEUR_DAMIER; ++i)
    {
        for(unsigned int indiceCase = 0; indiceCase < NB_TIRETS; ++indiceCase)
            std::cout << "_";
        std::cout << std::endl;
        for(unsigned int j = 0; j < LARGEUR_DAMIER; ++j)
            std::cout << "|   ";
        std::cout << "|" << std::endl;
        for(unsigned int j = 0; j < LARGEUR_DAMIER; ++j)
            std::cout << "| " << plateau.getContenuCase(i, j) << " ";
        std::cout << "|" << std::endl;
    }
    for(unsigned int colonne = 0; colonne < NB_TIRETS; ++colonne)
        std::cout << "_";
    std::cout << std::endl;
}

void Ihm::definirJoueurs(unsigned int numero)
{
    std::cout << "Saisir le nom du joueur numero " << numero << std::endl;
    std::cin >> this->joueurs[numero];
}

unsigned int Ihm::demandeUneDirection(bool joueurActif) const
{
    unsigned int choixDirection;

    std::cout << "Saisir la direction: ";
    do
    {
        std::cin >> choixDirection;
        if(choixDirection == 5 || choixDirection == 0 || choixDirection > 9)
        {
            std::cout << "Choix invalide, resélectionnez une direction: ";
        }
    } while (choixDirection == 5 || choixDirection == 0 || choixDirection > 9);
    return choixDirection;
}

void Ihm::ecrireErreur(unsigned int erreur)
{
    switch (erreur)
    {
    case 1:
        std::cout << "Il n'y a pas un de vos pion sur la case." << std::endl;
        break;

    case 2:
        std::cout << "Vous ne pouvez pas aller dans cette direction." << std::endl;
        break;

    case 3:
        std::cout << "Ce pion ne peut pas être déplacé." << std::endl;
        break;

    default:
        break;
    }
}

unsigned int Ihm::selectionneUnPion(bool joueurActif)
{
    unsigned int choixPion;

    std::cout << this->joueurs[joueurActif] << " doit choisir une direction: ";
    do
    {
        std::cin >> choixPion;
        if(choixPion >= LARGEUR_DAMIER && choixPion >= LARGEUR_DAMIER)
        {
            std::cout << "Entrée invalide, rentrer à nouveau votre direction: ";
        }
    } while (choixPion >= LARGEUR_DAMIER && choixPion >= LARGEUR_DAMIER);
    return choixPion;
}

void Ihm::feliciter(bool joueurActif)
{
    std::cout << "Bravo " << this->joueurs[joueurActif] << std::endl;
}