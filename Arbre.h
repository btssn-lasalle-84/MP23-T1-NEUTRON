/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        Arbre.h                                                             */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/22 by C. Trichet                                        */
/*   Updated: 2023/01/05 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef ARBRE_H
#define ARBRE_H

#include "Plateau.h"
#include <cmath>

#define NB_DIRECTIONS             8
#define NB_PION_JOUEUR            5
#define LARGEUR_DAMIER            5
#define SCORE_DEFAUT              10000
#define SCORE_MAX                 1000
#define ERREUR_PION_BLOQUE        2
#define ERREUR_DIRECTION_INVALIDE 3

class Arbre
{
  private:
    static unsigned int       profondeurMax;
    Arbre*                    noeud;
    Arbre*                    branche;
    Plateau*                  plateau;
    Plateau*                  sousPlateau;
    int                       score;
    unsigned int              profondeur;
    unsigned int              nbPionsDeplaces;
    std::vector<unsigned int> compteurs;
    std::vector<unsigned int> coordonneesPionCible;

  public:
    Arbre();
    Arbre(Arbre* noeud);
    ~Arbre();

    static void setProfondeurMax(unsigned int profondeur);

    int  simulerCoupsNeutron();
    int  simulerCoupsProton();
    int  elaguer(bool derniereBranche = false);
    bool comparerScores();
    bool rapporterScore();
};

#endif