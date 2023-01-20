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
#define NB_CHOIX_MENU             4
#define NB_CHOIX_MODE_DE_JEU      2
#define BASE                      10
#define DIRECTION_IMPOSSIBLE_1    0
#define DIRECTION_IMPOSSIBLE_2    5
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
    unsigned int afficherMenu() const;
    void         afficherRegles() const;
    unsigned int afficherChoixModeDeJeu() const;
    bool         choisirPremierJoueur(bool unJoueur) const;
    void         effacerEcran() const;
    void         feliciter(bool joueurActif);
    void         afficherVersion();
    void         afficherInformations();
};

#endif