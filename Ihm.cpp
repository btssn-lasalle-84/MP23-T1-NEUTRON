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

#include "Ihm.h"
#include <iostream>

Ihm::Ihm()
{
}

Ihm::~Ihm()
{
}

void Ihm::afficherPlateau(const Plateau& plateau) const
{
    for(unsigned int i = 0; i < LARGEUR_DAMIER; ++i)
    {
        for(unsigned int indiceCase = 0; indiceCase < NB_TIRETS; ++indiceCase)
            std::cout << "_";
        std::cout << std::endl;
        for(unsigned int j = 0; j < LARGEUR_DAMIER; ++j)
            std::cout << "|   ";
        std::cout << "|" << std::endl;
        for(unsigned int j = 0; j < LARGEUR_DAMIER; ++j)
        {
            if(plateau.getContenuCase(i, j) == CASE_VIDE)
                std::cout << "|   ";
            else
                std::cout << "| " << plateau.getContenuCase(i, j) << " ";
        }
        std::cout << "|" << std::endl;
    }
    for(unsigned int colonne = 0; colonne < NB_TIRETS; ++colonne)
        std::cout << "_";
    std::cout << std::endl;
}

void Ihm::definirJoueurs(unsigned int numero)
{
    std::string nom;
    std::cout << "Saisir le nom du joueur numero " << numero << std::endl;
    std::getline(std::cin, nom);
    this->joueurs[numero] = nom;
}

unsigned int Ihm::demandeUneDirection(bool joueurActif) const
{
    unsigned int choixDirection;
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << this << std::endl;
#endif
    std::cout << this->joueurs[joueurActif] << " doit saisir la direction: ";
    do
    {
        std::cin >> choixDirection;
        if(choixDirection == 5 || choixDirection == 0 || choixDirection > 9)
        {
            std::cout << "Choix invalide, resélectionnez une direction: ";
        }
    } while(choixDirection == 5 || choixDirection == 0 || choixDirection > 9);
    return choixDirection;
}

void Ihm::ecrireErreur(unsigned int erreur)
{
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << this << std::endl;
#endif
    switch(erreur)
    {
        case ERREUR_CASE_INVALIDE:
            std::cerr << "Il n'y a pas un de vos pion sur la case."
                      << std::endl;
            break;

        case ERREUR_PION_BLOQUE:
            std::cerr << "Ce pion ne peut pas être déplacé." << std::endl;
            break;

        case ERREUR_DIRECTION_INVALIDE:
            std::cerr << "Vous ne pouvez pas aller dans cette direction."
                      << std::endl;
            break;

        default:
            break;
    }
}

unsigned int Ihm::selectionneUnPion(bool joueurActif)
{
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << this << std::endl;
#endif
    unsigned int choixPion;

    std::cout << this->joueurs[joueurActif] << " doit choisir un pion: ";
    do
    {
        std::cin >> choixPion;
        if(choixPion / 10 >= LARGEUR_DAMIER && choixPion % 10 >= LARGEUR_DAMIER)
        {
            std::cout << "Entrée invalide, rentrer à nouveau un pion: ";
        }
    } while(choixPion / 10 >= LARGEUR_DAMIER ||
            choixPion % 10 >= LARGEUR_DAMIER);
    return choixPion;
}

unsigned int Ihm::afficherMenu() const
{
    unsigned int choix = 0;

    std::cout << "1 : Lancer une partie\n"
              << "2 : Afficher l'historique\n"
              << "3 : Afficher les règles du jeu\n"
              << "5 : Fermer le jeu\n";
    while(choix == 0 || choix < NB_CHOIX_MENU)
    {
        std::cout << "Entrez votre choix : ";
        std::cin >> choix;
    }
    return choix;
}

void Ihm::afficherRegles() const
{
    std::cout
      << "Les joueurs se font face devant un damier 5x5. Au départ, chaque "
         "joueur à 5 pions (5 pions 0 et 5 pions 1) qui sont initialement "
         "placé sur la première et la dernière ligne. Le pion neutre est 2, "
         "appelé neutron, est placé dans la case centrale. Le but du jeu est "
         "d’amener le neutron dans son propre camp."
      << std::endl;
    std::cout
      << "Tous les pions se déplacent dans l’une des huit directions "
         "diagonales ou orthogonales (à l'aide du pavé numérique, 8 correspond "
         "par exemple à en haut), aussi loin que possible jusqu’à ce qu’ils "
         "rencontrent un obstacle : le bord du tablier ou un autre pion, pour "
         "séléctionner son pions, il faut mettre en premier le numéro de la "
         "ligne (la première ligne correspond a 0), et à la suite celui de la "
         "colonne (la première colonne correspond à 0), donc, par exemple, "
         "pour un pion qui est sur la première ligne et la 3ème colonne, il "
         "faudrait mettre 02."
      << std::endl;
    std::cout << "Le joueur qui commence la partie ne déplace pas le neutron "
                 "au premier tour. Il déplace simplement une de ses pièces."
              << std::endl;
    std::cout
      << "Puis, à tour de rôle, les joueurs doivent d’abord, déplacer le "
         "neutron, puis déplacer un de leurs pions. Le joueur qui a amené le "
         "neutron dans son propre camp à gagné. Si un joueur ne peut pas "
         "déplacer le neutron ou un de ses pions il a perdu, de même s’il est "
         "obligé d’amener le neutron dans le camp adverse."
      << std::endl;
    std::cout << "Il existe donc quatre façons de gagner :" << std::endl;
    std::cout << "    - amener le neutron dans son propre camp, c’est-à-dire "
                 "sur sa propre ligne de départ ;"
              << std::endl;
    std::cout << "    - forcer l’adversaire à amener lui-même le neutron sur "
                 "la ligne de départ adverse ;"
              << std::endl;
    std::cout
      << "    - placer l’adversaire dans une situation où il ne peut pas "
         "déplacer le neutron ou un de ses pions (gagner à l’étouffée) ;"
      << std::endl;
    std::cout
      << "    - que toutes les cases de l’adversaire soient occupées par cinq "
         "de ses pions ou par quatre de ses pions et le neutron.)"
      << std::endl;
}

unsigned int Ihm::afficherChoixModeDeJeu() const
{
    unsigned int choix = 0;

    std::cout << "1 : un joueur\n"
              << "2 : deux joueurs\n";

    while(choix == 0 || choix < NB_CHOIX_MODE_DE_JEU)
    {
        std::cout << "Entrez votre choix : ";
        std::cin >> choix;
    }
    return choix;
}

unsigned int Ihm::choisirPremierJoueur() const
{
    unsigned int choix = 0;

    while(choix != 1 && choix != 2)
    {
        std::cout << "Veuillez choisir le joueur qui commence : ";
        std::cin >> choix;
    }
    return choix;
}

void Ihm::effacerEcran() const
{
    std::cout << "\033[H\033[2J";
}

void Ihm::feliciter(bool joueurActif)
{
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << this << std::endl;
#endif
    std::cout << "Bravo " << this->joueurs[joueurActif] << std::endl;
}