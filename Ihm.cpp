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

#include <iostream>
#include "Ihm.h"
#include "Plateau.h"

Ihm::Ihm()
{
}

Ihm::~Ihm()
{
}
{
}

void  Ihm::afficherPlateau(Plateau &plateau)
{
    for (i = 0, i < 5, ++i)
        for (loop = 0, loop < 21)
            std::cout << "_";
        std::cout << std::endl;
        for (loop = 0, loop < 5)
            std::cout << "|   ";
        std::cout << "|" << std::endl;
        for (j = 0, j < 5)
            std::cout << "| " << plateau[i,j] << " ";
        std::cout << "|" << std::endl;
    for (loop = 0, loop < 21)
            std::cout << "_";
        std::cout << std::endl;
}

std::string   *definirJoueurs()
{
    std::string joueurs[2];

    std::cout << "Saisir le nom du premier Joueur" << endl;
    cin >> joueurs[0];
    do
    {
        cout << "Saisir le nom du second Joueur"
        cin >> joueur[1];
    } while (joueurs[0] == joueurs[1]);
    return joueurs;
}
