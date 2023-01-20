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
#define NB_TIRETS                 21
#define LARGEUR_DAMIER            5
#define ERREUR_CASE_INVALIDE      1
#define ERREUR_PION_BLOQUE        2
#define ERREUR_DIRECTION_INVALIDE 3
#define NB_CHOIX_MENU             5
#define NB_CHOIX_MODE_DE_JEU      2

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
};

#endif