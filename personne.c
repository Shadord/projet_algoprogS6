#include "personne.h"

/* Creer la matrice d'adjacance
retrouver une personne à partir des coordonnées
trouver les voisins à partir de coordonnées */

Personne*** creer_graphe(int taille_matrice) {

 	Personne*** adjacency_matrix = (Personne***) malloc((taille_matrice)*sizeof(Personne**));

	for (int i = 0; i < taille_matrice; i++) // Ligne
	{
		adjacency_matrix[i] = (Personne**) malloc((taille_matrice)*sizeof(Personne*));
		for (int j = 0; j < taille_matrice; j++) // Colonne
			{
			Personne* N = malloc(sizeof(Personne));
			N->etat = randomize_state(0.22); // personne saine
			N->id= i*(taille_matrice)+j;
			adjacency_matrix[i][j] = N;
			}
	}

	return adjacency_matrix;
}

void print_adjacency_matrix(Personne*** adjacency_matrix, int taille_matrice)
{
	for (int i = 0; i < taille_matrice; i++)
	{
		for (int j = 0; j < taille_matrice; j++)
			{
			printf("%d ", adjacency_matrix[i][j]->etat);
			}
		printf("\n" );
	}
}

int randomize_state(float proba) { // Fonction de random, renvois 1 si la proba est réalisée et 0 sinon
  double nombre  = (rand()/(double)RAND_MAX);
  if(nombre < proba) {
    return 1;
  }else{
    return 0;
  }
}
