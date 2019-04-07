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
        simulation(&G, &LB, size);
        system("python graph.py");
      }
    }
  }




}

void compteur(FILE* fp, Graph *G, int day) {
  int sain = 0, malade = 0, imm = 0, dead = 0, zombie = 0;
  float average_ill;
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
      case 4:
        zombie++;
        break;

    }
  }
  for (int i=0; i<G->nb_personnes; i++)
	{
	if (G->liste_personnes[i]->etat==1)
		average_ill+=G->liste_personnes[i]->jour_malade;
	}
  average_ill=average_ill/malade;
  printf("Durée moyenne de la maladie : %f\n", average_ill);
  fprintf(fp, "%d;%d;%d;%d;%d;%d\n", day , sain, malade, imm, dead, zombie);
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
  int vaccination_day;
  FILE* fp = fopen("save.txt", "w");
	printf("Entrez le nombre de jours de la simulation : \n");
	scanf("%d", &temps);
  printf("Entrez le jour de debut vaccination (-1 => aucun vaccin) : \n");
	scanf("%d", &vaccination_day);

	printf("Jour 0 - Situation de départ : \n");
	printGrid2(G, size);
  compteur(fp, G, 0);
	for (int i=0; i<temps; i++)
		{
		printf("Jour %d : \n", i+1);
		set(G,LB, i, vaccination_day);
		update(LB);
		printGrid2(G, size);
    compteur(fp, G, i+1);
		}
    fclose(fp);
	}
