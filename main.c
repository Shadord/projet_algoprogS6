#include "main.h"


void main(int argc, char const *argv[]) {
  const char* filename = "graph_10_13.txt";
  Graph G;
  LetterBox LB;
  LB.first = NULL;
  LB.last = NULL;
  create_graph(&G, filename);
  print_graph(&G);
  Graph R;
  generateGrid(&R, 10);
  printGrid(&R, 10);

  simulation(&R, &LB,10);
  system("atom");
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

void simulation(Graph *G, LetterBox *LB, int size)
	{
	int temps;
	printf("Entrez le nombre de jours de la simulation : ");
	scanf("%d", &temps);

	printf("Jour 0 - Situation de départ : \n");
	printGrid(G, size);
	for (int i=0; i<temps; i++)
		{
		printf("Jour %d : \n", i+1);
		set(G,LB);
		update(LB);
		printGrid(G, size);
		}
	}
