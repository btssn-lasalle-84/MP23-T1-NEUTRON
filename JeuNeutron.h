/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        JeuNeutron.h */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/14 by C. Trichet                                        */
/*   Updated: 2022/12/14 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef JEU_NEWTON_H
#define JEU_NEWTON_H

#ifdef DEBUG
#include <iostream>
#endif

#include <string>
#include <iostream>
#include "Ihm.h"
#include "Plateau.h"

#define CASE_NEUTRE          2
#define NEUTRON_XY           5
#define ERREUR_CASE_INVALIDE 1
#define BASE                 10
#define LANCER_PARTIE        1
#define HISTORIQUE           2
#define AFFICHER_REGLES      3
#define QUITTER_JEU          4

class IHM;
class Plateau;

class JeuNeutron
{
  private:
    Ihm     ihm;
    Plateau plateau;
    bool    joueurActif;

  public:
    JeuNeutron();
    ~JeuNeutron();

    void setJoueurActif(bool joueurActif);
    bool getJoueurActif() const;

    void jouerUnCoup(bool estNeutron = true);
    int  demarrer();
    int  jouerPartieUnJoueur();
};

#endif