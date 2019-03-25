#include "main.h"


void main(int argc, char const *argv[]) {
  srand(time(NULL));
  int taille_matrice = 10;
	Personne*** matrice_adjacence;
	matrice_adjacence = creer_graphe(taille_matrice);
	print_adjacency_matrix(matrice_adjacence, taille_matrice);


}

int menu() {
  int reponse;
  printf("===============================================================\n");
  printf("==>   MENU PRINCIPAL DE LA SIMULATION\n");
  printf("===============================================================\n\n");
  printf("1. PREMIERES DONNEES\n");
  printf("2. LANCER LA SIMULATION\n");
  printf("3. AFFICHER LES GRAPHES\n");
  scanf("%d", &reponse);
  return reponse;
}
