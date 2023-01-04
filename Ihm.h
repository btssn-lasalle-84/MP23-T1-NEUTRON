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

#include <string>
#ifndef IHM_H
#define IHM_H
#define NB_TIRETS      21
#define LARGEUR_DAMIER 5

class Ihm
{
  private:
    std::string joueurs[2];

  public:
    Ihm();
    ~Ihm();

    void        afficherPlateau(const Plateau& plateau) const;
    std::string definirJoueurs(unsigned int numero);
};

#endif