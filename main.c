#include "main.h"


void main(int argc, char const *argv[]) {
  int reponse;
  Graph G;
  G.nb_personnes = -1;
  LetterBox LB;
  LB.first = NULL;
  LB.last = NULL;
  const char* filename = "graph_10_13.txt";
  int size;
  while(1){
    reponse = menu();
    if(reponse == 1) {
      create_graph(&G, filename);
      print_graph(&G);
    }else if(reponse == 2) {
      size = graphSize();
      generateGrid(&G, size);
      printGrid2(&G, size);
    }else if(reponse == 3){
      if(G.nb_personnes != -1){
        simulation(&G, &LB,size);
        system("python graph.py");
      }
    }
  }




}

void compteur(FILE* fp, Graph *G, int day) {
  int sain = 0, malade = 0, imm = 0, dead = 0;
  Personne* P;
  for(int i = 0; i<G->nb_personnes; i++) {
    P = G->liste_personnes[i];
    switch(P->etat) {
      case 0:
        sain++;
        break;
      case 1:
        malade++;
        break;
      case 2:
        imm++;
        break;
      case 3:
        dead++;
        break;
    }
  }
  fprintf(fp, "%d;%d;%d;%d;%d\n", day , sain, malade, imm, dead);
}




int graphSize(){
  int size;
  printf("Entrez la taille de la grille a générer : ");
	scanf("%d", &size);
  return size;
}

int menu() {
  int reponse;
  printf("===============================================================\n");
  printf("==>   MENU PRINCIPAL DE LA SIMULATION\n");
  printf("===============================================================\n\n");
  printf("1. INITIER LES DONNEES DEPUIS TEXTE\n");
  printf("2. INITIER LES DONNEES GRID\n");
  printf("3. LANCER LA SIMULATION\n");
  scanf("%d", &reponse);
  return reponse;
}

void simulation(Graph *G, LetterBox *LB, int size)
	{
	int temps;
  FILE* fp = fopen("save.txt", "w");
	printf("Entrez le nombre de jours de la simulation : \n");
	scanf("%d", &temps);

	printf("Jour 0 - Situation de départ : \n");
	printGrid2(G, size);
  compteur(fp, G, 0);
	for (int i=0; i<temps; i++)
		{
		printf("Jour %d : \n", i+1);
		set(G,LB);
		update(LB);
		printGrid2(G, size);
    compteur(fp, G, i+1);
		}
    fclose(fp);
	}
