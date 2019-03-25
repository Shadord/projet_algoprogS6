#ifndef PERSONNE_H
#define PERSONNE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int etat;
	int id;
	} Personne ;

/* *********** Table des états : *****************
0 : sain
1 : malade
2 : immunisé
3 : mort
*/

Personne*** creer_graphe(int* taille_matrice);
void print_adjacency_matrix(Personne*** adjacency_matrix, int* taille_matrice);

#endif 
