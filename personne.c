#include "personne.h"

/* Creer la matrice d'adjacance
retrouver une personne à partir des coordonnées
trouver les voisins à partir de coordonnées */

Personne*** creer_graphe(int* taille_matrice) {
	printf("Quelle est la taille de la matrice ? (nombre de colonne) : ");
	scanf("%d", taille_matrice);

 	Personne*** adjacency_matrix = (Personne***) malloc((*taille_matrice)*sizeof(Personne**)); 
	Personne *courant;
	courant = (Personne*)malloc(sizeof(Personne));
	
	for (int i = 0; i < *taille_matrice; i++) 
	{			
		adjacency_matrix[i] = (Personne**) malloc((*taille_matrice)*sizeof(Personne*)); 
		for (int j = 0; j < *taille_matrice; j++)
			{
			courant = adjacency_matrix[i][j]; 
			courant->etat = 0; // personne saine
			courant->id= i*(*taille_matrice)+j;
			}
	}

	return adjacency_matrix;
}

void print_adjacency_matrix(Personne*** adjacency_matrix, int* taille_matrice)
{
	for (int i = 0; i < *taille_matrice; i++) 
	{
		for (int j = 0; j < *taille_matrice; j++)
			{
			printf("%d ", adjacency_matrix[i][j]->etat); 
			}
		printf("\n" ); 
	}
}

int main(void)
	{
	int taille_matrice;
	Personne*** matrice_adjacence;
	matrice_adjacence = creer_graphe(&taille_matrice);
	print_adjacency_matrix(matrice_adjacence, &taille_matrice);
	}











