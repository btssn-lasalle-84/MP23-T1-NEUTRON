/*////////////////////////////////////////////////////////////////////////////*/
/*                                                                            */
/*        Arbre.cpp                                                           */
/*                                                                            */
/*   By: Clément Trichet                                                      */
/*                                                                            */
/*   Created: 2022/12/22 by C. Trichet                                        */
/*   Updated: 2022/12/31 by C. Trichet                                        */
/*                                                                            */
/*////////////////////////////////////////////////////////////////////////////*/

#include "Arbre.h"

Arbre::Arbre() :
    noeud(nullptr), branche(nullptr), plateau(new Plateau()),
    sousPlateau(new Plateau()), score(SCORE_DEFAUT), profondeur(0),
    nbPionsDeplaces(0), compteurs({ 0, 0 }), coordonneesPionCible({ 0, 0 })
{
}

Arbre::Arbre(Arbre* noeud) :
    noeud(noeud), branche(nullptr), plateau(new Plateau(noeud->plateau)),
    sousPlateau(new Plateau(noeud->plateau)), profondeur(noeud->profondeur + 1),
    score(SCORE_DEFAUT), nbPionsDeplaces(0), compteurs({ 0, 0 }),
    coordonneesPionCible({ 0, 0 })
{
}

Arbre::~Arbre()
{
    if(this->branche != nullptr)
        delete this->branche;
}

void Arbre::setProfondeurMax(unsigned int profondeur)
{
    Arbre::profondeurMax = profondeur;
}

int Arbre::simulerCoupsNeutron()
{
    if(this->compteurs[0] == NB_DIRECTIONS)
    {
        if(profondeur)
        {
            if(this->score == SCORE_DEFAUT)
            {
                this->score = SCORE_MAX * pow(-1, profondeur);
            }
            return this->elaguer(true);
        }
        else
            return 0;
    }
    this->sousPlateau   = this->plateau;
    unsigned int erreur = this->sousPlateau->deplaceUnPion(this->compteurs[0]);
    if(erreur == ERREUR_PION_BLOQUE)
    {
        this->compteurs[0] = NB_DIRECTIONS;
        return this->simulerCoupsNeutron();
    }
    else
    {
        ++this->compteurs[0];
        return this->simulerCoupsProton();
    }
}

int Arbre::simulerCoupsProton()
{
    if(this->nbPionsDeplaces == NB_PION_JOUEUR ||
       this->coordonneesPionCible[0] == LARGEUR_DAMIER)
    {
        this->coordonneesPionCible = { 0, 0 };
        this->compteurs[1]         = 0;
        return this->simulerCoupsNeutron();
    }
    else if(this->coordonneesPionCible[1] == LARGEUR_DAMIER)
    {
        ++coordonneesPionCible[0];
        coordonneesPionCible[1] = 0;
        return this->simulerCoupsProton();
    }
    else if(this->compteurs[1] == NB_DIRECTIONS)
    {
        this->compteurs[1] = 0;
        ++this->nbPionsDeplaces;
        ++this->coordonneesPionCible[0];
        return this->simulerCoupsProton();
    }
    else if(this->sousPlateau->getContenuCase(coordonneesPionCible[0],
                                              coordonneesPionCible[1]) !=
            profondeur % 2)
    {
        ++this->coordonneesPionCible[0];
        return this->simulerCoupsProton();
    }
    else
    {
        if(this->branche)
            delete this->branche;
        this->branche = new Arbre(this);
        unsigned int erreur =
          this->branche->plateau->deplaceUnPion(compteurs[1],
                                                this->coordonneesPionCible[0],
                                                this->coordonneesPionCible[1],
                                                this->profondeur % 2);
        ++this->compteurs[1];
        if(erreur == ERREUR_DIRECTION_INVALIDE)
            return this->simulerCoupsProton();
        else if(this->profondeur != profondeurMax)
            return this->branche->simulerCoupsNeutron();
        else
        {
            this->score = this->branche->plateau->calculerScore();
            this->branche->rapporterScore();
            return this->elaguer();
        }
    }
}

bool Arbre::comparerScores()
{
    if((this->score > this->noeud->score && this->profondeur % 2) ||
       (this->score < this->noeud->score && (this->profondeur + 1) % 2) ||
       this->noeud->score == SCORE_DEFAUT)
    {
        return true;
    }
    return false;
}

bool Arbre::rapporterScore()
{
    if(this->comparerScores())
    {
        this->noeud->score = this->score;
        return true;
    }
    return false;
}

int Arbre::elaguer(bool derniereBranche /*=false*/)
{
    if(derniereBranche)
    {
        if(this->rapporterScore())
            return this->noeud->elaguer(false);
    }
    else
    {
        if(this->comparerScores())
            return this->simulerCoupsProton();
        else
        {
            this->noeud->simulerCoupsProton();
        }
    }
}
