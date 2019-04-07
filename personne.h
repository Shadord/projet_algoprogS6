#ifndef PERSONNE_H
#define PERSONNE_H

#define BEGIN_CONTAMINATION_RATE 1 //Pourcentage de malade dans la grille/Graph de depart
#define ILL_CONTAMINATION_RATE 0.10 // Proba qu'un malade transmette sa maladie
#define ZOMBIE_CONTAMINATION_RATE 0.10 // Proba qu'un zombie morde qqun
#define IMMUNISATION_RATE 0.10 // Proba d'etre immunisé en etant malade
#define ZOMBIE_RATE 0.1 // Proba de devenir naturellement zombie en etant malade
#define DEAD_RATE 0.02 // Proba qu'un malade meurt
#define VACCINATION_RATE 0.1 // Proba qu'un individu sain se fasse immunisé : Immunisation marche + Qu'il ai l'argent etc...
#define KILL_ZOMBIE_RATE 0.1 // Proba qu'un immunisé tue un zombie

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "time.h"



typedef struct
{
	int		id;
	int		etat;
} Personne;

typedef struct _Successeur
{
	Personne *personne;
	struct _Successeur *successeur;
} Successeur;

typedef struct
{
	int	nb_personnes;
	Personne** liste_personnes;
	Successeur** liste_successeurs;
} Graph;

/* *********** Table des états : *****************
0 : sain
1 : malade
2 : immunisé
3 : mort
4: Zombie
*/

/* *********** But du jeu : *****************
On a X personnes malade posées sur l'AM (Adjency Matrix).
A chaque tour (process), l'ordinateur calcule les états futur en fonction des états présent.

    2
    |
1---0---3
    |
		4
Ici, si 0 est malade, alors il a une probabilité \lambda de transmettre sa maladie a 1, 2, 3, et 4 a conditions qu'ils
soient sain.
SI un d'entre eu est deja malade, il le reste. Si il est Mort ou immunisé, il ne tombe pas malade
Une personne malade, a la probabilité \beta de se soigner et d'être imminisé, et \gamma de mourrir.
*/


/// GENERATION DE MONDES
// Generation d'un graph via un fichier texte. Attention, les Malades sont disposés aléatoirement selon la proba BEGIN_CONTAMINATION_RATE
void create_graph(Graph* G, const char* grapheFileName);

// Génération d'une grille ou les malades sont disposés aleatoirement selon la proba BEGIN_CONTAMINATION_RATE
void generateGrid(Graph *G, int size);

// Envois 0 ou 1 si la proba est réalisée
int randomize_state(float proba);

// Affiche un graph quelquonque
void print_graph(Graph* G);

//Affiche un graph grille
void printGrid2(Graph *G, int size);

#endif
