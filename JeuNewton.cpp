/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        JeuNewton.cpp                                                       */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/14 by C. Trichet                                        */
/*   Updated: 2022/12/14 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#include "JeuNewton.h"
#include "Ihm.h"
#include "string"

class Plateau;

JeuNewton::JeuNewton() : ihm(new IHM), plateau(new Plateau), joueurActif(0) {}

JeuNewton::~JeuNewton() {
  delete this->ihm;
  delete this->plateau;
}

void JeuNewton::setJoueurActif(bool joueurActif) {
  this->joueurActif = joueurActif;
}

bool JeuNewton::getJoueurActif() const { return this->joueurActif; }

void JeuNewton::setJoueurs(const std::string *joueurs) {
  this->joueurs[0] = joueurs[0];
  this->joueurs[1] = joueurs[1];
}

std::string JeuNewton::getJoueur(unsigned int numero) const {
  return this->joueurs[numero];
}

void JeuNewton::demarrer() { this->setJoueurs(this->ihm.definirJoueurs()); }