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

class IHM;
class Plateau;

class JeuNewton {
private:
  IHM ihm;
  Plateau plateau;
  std::string joueurs[2];
  bool joueurActif;

public:
  JeuNewton();
  ~JeuNewton();

  void setJoueurActif(bool joueurActif);
  bool getJoueurActif() const;
  void setJoueurs(const std::string joueurs[2]);
  std::string getJoueur(unsigned int numero) const;

  void demarrer();
};

#endif