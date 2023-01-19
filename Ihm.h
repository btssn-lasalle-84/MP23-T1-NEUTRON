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

#ifndef IHM_H
#define IHM_H

#include <string>
#include "Plateau.h"

#define NB_TIRETS                 21
#define LARGEUR_DAMIER            5
#define ERREUR_CASE_INVALIDE      1
#define ERREUR_PION_BLOQUE        2
#define ERREUR_DIRECTION_INVALIDE 3
#define BASE                      10

class Ihm
{
  private:
    std::string joueurs[2];

  public:
    Ihm();
    ~Ihm();

    void         afficherPlateau(const Plateau& plateau) const;
    void         definirJoueurs(unsigned int numero);
    unsigned int demandeUneDirection(bool joueurActif) const;
    void         ecrireErreur(unsigned int erreur);
    unsigned int selectionneUnPion(bool joueurActif);
    void         feliciter(bool joueurActif);
    void         afficherVersion();
    void         afficherInformations();
};

#endif