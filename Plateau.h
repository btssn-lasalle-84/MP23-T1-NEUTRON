/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        Plateau.h                                                           */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/14 by C. Trichet                                        */
/*   Updated: 2022/12/14 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef PLATEAU_H
#define PLATEAU_H
#define NEUTRON_XY                5
#define NB_LIGNES                 5
#define NB_COLONNES               5
#define NEUTRON                   2
#define PION_JOUEUR_0             0
#define PION_JOUEUR_1             1
#define CASE_VIDE                 3
#define ERREUR_CASE_INVALIDE      1
#define ERREUR_PION_BLOQUE        2
#define ERREUR_DIRECTION_INVALIDE 3

#include <vector>

class Plateau
{
  private:
    unsigned int                            coordonneesNeutron[2];
    std::vector<std::vector<unsigned int> > damier;

  public:
    Plateau();
    ~Plateau();

    void setCoordonneesNeutron(unsigned int i, unsigned int j);
    unsigned int getCoordonneesNeutron() const;
    unsigned int getContenuCase(unsigned int i, unsigned int j) const;

    bool pionEstCoince(unsigned int i = NEUTRON_XY,
                       unsigned int j = NEUTRON_XY) const;
    bool pionsSontCoinces(bool joueurActif) const;
    int  deplaceUnPion(unsigned int direction,
                       unsigned int i           = NEUTRON_XY,
                       unsigned int j           = NEUTRON_XY,
                       unsigned int joueurActif = NEUTRON);
};

#endif