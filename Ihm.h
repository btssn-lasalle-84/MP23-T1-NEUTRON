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
#include "Plateau.h"
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
    void definirJoueurs(unsigned int numero);
    unsigned int demandeUneDirection(bool joueurActif) const;
    void ecrireErreur(unsigned int erreur);
    unsigned int selectionneUnPion(bool joueurActif);
    void feliciter(bool joueurActif);
};

#endif