#ifndef PERSONNE_H
#define PERSONNE_H

#define CONTAMINATION_RATE 0.8
#define IMMUNISATION_RATE 0.30
#define DEAD_RATE 0.5

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

void create_graph(Graph* G, const char* grapheFileName);
int randomize_state(float proba);
void print_graph(Graph* G);
void printGrid(Graph *G, int size);
void generateGrid(Graph *G, int size);

#endif
