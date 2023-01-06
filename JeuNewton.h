/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        JeuNewton.h                                                         */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/14 by C. Trichet                                        */
/*   Updated: 2022/12/14 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef JEU_NEWTON_H
#define JEU_NEWTON_H

#include <string>
#include <iostream>
#include "Ihm.h"
#include "Plateau.h"
#define CASE_NEUTRE 2
#define NEUTRON_XY  5
#define ERREUR_CASE_INVALIDE 1

class IHM;
class Plateau;

class JeuNewton
{
  private:
    Ihm     ihm;
    Plateau plateau;
    bool    joueurActif;

  public:
    JeuNewton();
    ~JeuNewton();

    void setJoueurActif(bool joueurActif);
    bool getJoueurActif() const;
    void jouerUnCoup(bool estNeutron = 1);

    int demarrer();
};

#endif