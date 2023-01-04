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