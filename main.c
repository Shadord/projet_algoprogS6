#include "main.h"


void main(int argc, char const *argv[]) {
  const char* filename = "graph_10_13.txt";
  Graph G;
  create_graph(&G, filename);
  print_graph(&G);

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
