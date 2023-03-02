[![C/C++ make](https://github.com/btssn-lasalle84/MP23-T1/actions/workflows/c-cpp.yml/badge.svg?branch=develop)](https://github.com/btssn-lasalle84/MP23-T1/actions/workflows/c-cpp.yml) [![C/C++ format](https://github.com/btssn-lasalle84/MP23-T1/actions/workflows/cppformat.yml/badge.svg?branch=develop)](https://github.com/btssn-lasalle84/MP23-T1/actions/workflows/cppformat.yml)

# Mini-projet : Neutron

- [Mini-projet : Neutron](#mini-projet--neutron)
  - [Présentation](#présentation)
  - [Jira](#jira)
    - [Les versions](#les-versions)
    - [Feuille de route](#feuille-de-route)
    - [Tickets](#tickets)
      - [Version 1.0](#version-10)
      - [Version 1.1](#version-11)
      - [Version 2.0 (non publiée)](#version-20-non-publiée)
  - [Recette](#recette)
  - [Auteurs](#auteurs)
  - [Problèmes identifiés](#problèmes-identifiés)

---

> Ceci est un mini-projet de 2 étudiants de BTS SN option Informatique & Réseaux développé en C++. L'objectif était la mise en oeuvre d'une méthode agile [Kanban](https://fr.wikipedia.org/wiki/Kanban_(d%C3%A9veloppement)) avec les outils **Jira / Github** et en appliquant le _workflow_ [Gitflow](https://btssn-lasalle84.github.io/guides-developpement-logiciel/jira.html#ancre-gitflow). L'application devait être limitée à une interface en ligne de commande (console).

---

## Présentation

Les joueurs se font face devant un damier 5x5. Au départ, chaque joueur à 5 pions (5 pions 0 et 5 pions 1) qui sont initialement placé sur la première et la dernière ligne. Le pion neutre est 2, appelé neutron, est placé dans la case centrale. Le but du jeu est d’amener le neutron dans son propre camp.

Tous les pions se déplacent dans l’une des huit directions diagonales ou orthogonales (à l'aide du pavé numérique, 8 correspond par exemple à en haut), aussi loin que possible jusqu’à ce qu’ils rencontrent un obstacle : le bord du tablier ou un autre pion, pour séléctionner son pions, il faut mettre en premier le numéro de la ligne (la première ligne correspond a 0), et à la suite celui de la colonne (la première colonne correspond à 0).

Le joueur qui commence la partie ne déplace pas le neutron au premier tour. Il déplace simplement une de ses pièces.

Puis, à tour de rôle, les joueurs doivent d’abord, déplacer le neutron, puis déplacer un de leurs pions.

Le joueur qui a amené le neutron dans son propre camp à gagné. Si un joueur ne peut pas déplacer le neutron ou un de ses pions il a perdu, de même s’il est obligé d’amener le neutron dans le camp adverse.

Il existe donc quatre façons de gagner :

- amener le neutron dans son propre camp, c’est-à-dire sur sa propre ligne de départ ;
- forcer l’adversaire à amener lui-même le neutron sur la ligne de départ adverse ;
- placer l’adversaire dans une situation où il ne peut pas déplacer le neutron ou un de ses pions (gagner à "l’étouffée") ;
- que toutes les cases de l’adversaire soient occupées par cinq de ses pions ou par quatre de ses pions et le neutron.

## Jira

Intégration avec Github :

![](images/mp23-t1-jira-code.png)

### Les versions

![](images/mp23-t1-jira-versions.png)

### Feuille de route

![](images/mp23-t1-jira-roadmap.png)

### Tickets

#### Version 1.0

![](images/mp23-t1-jira-version-1.0.png)

#### Version 1.1

![](images/mp23-t1-jira-version-1.2.png)

#### Version 2.0 (non publiée)

![](images/mp23-t1-jira-version-2.0.png)


## Recette

|Fonctionnalité                      |Oui|Non|
|------------------------------------|:-:|:-:|
|Saisir le nom du joueur             | X |   |
|Jouer une partie                    | X |   |
|Afficher le déroulement d'une partie| X |   |

## Auteurs

  - Clement Trichet <<clement.trichet.pro@gmail.com>>
  - Mercklen Jérémy <<mercklenjeremy@gmail.com>>

## Problèmes identifiés

- Bug si un caractère est entré lors de la séléction d'un pion ou d'une direction.
- Impossible de mettre des espaces dans les noms de joueurs.
- Certaines directions invalides n'affichent pas de message d'erreur.
