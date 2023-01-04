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
#include "Ihm.h"
#include "Plateau.h"

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

    int demarrer();
};

#endif