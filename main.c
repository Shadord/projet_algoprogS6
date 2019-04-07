#include "main.h"


void main(int argc, char const *argv[]) {

  /// Chargement des parametres
  float parametres[8];
  if(loadParam(parametres) != 1) {
    printf("\033[31mErreur lors du chargement des parametres\n");
  }else{
    printf("\033[32mSucces du chargement des parametres\n");
  }

  /// Creation du graphe
  Graph G;
  G.nb_personnes = -1;

  /// Creation de la boite au lettre (file  : FIFO)
  LetterBox LB;
  LB.first = NULL;
  LB.last = NULL;

  const char* filename = "donnees_graphe.txt"; // Nom du fichier contenant le graph
  int size; // Variable pour la taille d'un graph GRILLE
  int reponse; // Reponse du menu principal

  while(1){ // Bouche sans fin
    reponse = menu(); // On recupere la valeur entrée par l'utilisateur
    if(reponse == 1) {
      create_graph(&G, filename, parametres); // Creation d'un graph normal grace au fichier et affichage
      print_graph(&G);
      G.type = 1;
    }else if(reponse == 2) { // Creation d'un graph grille avec demande de taille et affichage
      size = graphSize();
      generateGrid(&G, size, parametres);
      printGrid2(&G, size);
      G.type = 0;
    }else if(reponse == 4){ // Simulation si le graph est crée
      if(G.nb_personnes != -1){
        simulation(&G, &LB, size, parametres);
        system("python graph.py");
      }else{
        printf("  \033[31mErreur, votre Graph est vide.\n");
      }
    }else if(reponse == 3) { // On rentre dans le menu des parametres
      parametreMenu(parametres);
    }else if(reponse == 5) { // On quitte le programme
      return;
    }
  }

}


void compteur(FILE* fp, Graph *G, int day) {
  int sain = 0, malade = 0, imm = 0, dead = 0, zombie = 0;
  //float average_ill;
  Personne* P;
  for(int i = 0; i<G->nb_personnes; i++) {
    P = G->liste_personnes[i];
    switch(P->etat) {
      case 0:
        sain++;
        break;
      case 1:
        malade++;
        //average_ill += G->liste_personnes[i]->jour_malade;
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
  //average_ill=average_ill/malade;
  //printf("Durée moyenne de la maladie : %f\n", average_ill);
  fprintf(fp, "%d;%d;%d;%d;%d;%d\n", day , sain, malade, imm, dead, zombie);
}




int graphSize(){
  int size;
  printf("  \033[0mEntrez la taille de la grille a générer : ");
	scanf("%d", &size);
  return size;
}

int menu() {
  int reponse;
  printf("\033[0m===============================================================\n");
  printf("==>   MENU PRINCIPAL DE LA SIMULATION\n");
  printf("===============================================================\n\n");
  printf("1. GENERERATION D'UN GRAPHE DEPUIS UN FICHIER TEXTE\n");
  printf("2. GENERATION D'UN GRAPHE GRILLE\n");
  printf("3. MODIFIER LES PARAMETRES DE SIMULATION\n");
  printf("4. LANCER LA SIMULATION\n");
  printf("5. QUITTER LE PROGRAMME\n");
  scanf("%d", &reponse);
  return reponse;
}

void simulation(Graph *G, LetterBox *LB, int size, float parametres[]) {
	int temps;
  int vaccination_day;
  FILE* fp = fopen("resulats_simulation.txt", "w");
	printf(" \033[0mEntrez le nombre de jours de la simulation : \n");
	scanf("%d", &temps);
  if(parametres[6] != 0) {
    printf("  \033[0mEntrez le jour de debut vaccination (-1 => aucun vaccin) : \n");
  	scanf("%d", &vaccination_day);
  }else{
    vaccination_day = -1;
  }

	printf("Jour 0 - Situation de départ : \n");
  if(G->type = 0) {
    printGrid2(G, size);
  }else{
    print_graph(G);
  }

  compteur(fp, G, 0);
	for (int i=0; i<temps; i++) {
		printf("Jour %d : \n", i+1);
		set(G,LB, i, vaccination_day, parametres);
		update(LB);
    if(G->type = 0) {
      printGrid2(G, size);
    }else{
      print_graph(G);
    }
    compteur(fp, G, i+1);
	}
  fclose(fp);
}

void parametreMenu(float parametres[]) {
  int reponse;
  int flag = 1;
  int etat_zombie = (parametres[2] != 0) && (parametres[4] != 0);
  printf("%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",parametres[0], parametres[1], parametres[2], parametres[3],parametres[4],parametres[5], parametres[6],parametres[7]);
  int etat_vaccination = parametres[6] != 0;
  char* etat[4] = {"ACTIVER", "DESACTIVER", "ACTIVE", "DESACTIVE"};
  while(flag) {
    printf("    \033[0m===============================================================\n");
    printf("    ==>   MENU PARAMETRES DE LA SIMULATION\n");
    printf("    ===============================================================\n\n");
    printf("    1. MODIFIER LES CONSTANTES DE PROBABILITES\n");
    printf("    2. %s LE MODE ZOMBIE\n", etat[etat_zombie]);
    printf("    3. %s LA VACCINATION\n", etat[etat_vaccination]);
    printf("    4. REINITIALISER LES PARAMETRES\n");
    printf("    5. RETOUR AU MENU PRINCIPAL\n");
    scanf("%d", &reponse);
    switch (reponse) {
      case 1:
        system("nano parametres.txt");
        loadParam(parametres);
        break;
      case 2:
        if(etat_zombie == 0) {
          parametres[2] = 0.30;
          parametres[4] = 0.23;
          if(updateParam(parametres)) {
            printf("    \033[32mLe mode zombie a été %s avec les valeurs de probabilité suivantes : \n", etat[2 + etat_zombie]);
            printf("        - Probabilité qu'un zombie morde une personne : 0.30\n");
            printf("        - Probabilité qu'un malade devienne un zombie : 0.23\n");
            etat_zombie = 1 - etat_zombie;
          }else{
            printf("    \033[31mErreur lors de la sauvegarde des parametres.\n");
          }
        }else{
          parametres[2] = 0.00;
          parametres[4] = 0.00;
          if(updateParam(parametres)) {
            printf("    \033[32mLe mode zombie a été %s\n", etat[2 + etat_zombie]);
            etat_zombie = 1 - etat_zombie;
          }else{
            printf("    \033[31mErreur lors de la sauvegarde des parametres.\n");
          }
        }
        break;
      case 3:
        if(etat_vaccination == 0) {
          parametres[6] = 0.24;
          if(updateParam(parametres)) {
            printf("    \033[32mLe mode vaccination a été %s avec la valeur de probabilité suivante : \n", etat[2 + etat_vaccination]);
            printf("        - Probabilité qu'un sain aille se faire vacciner : 0.24\n");
            etat_vaccination = 1 - etat_vaccination;
          }else{
            printf("    \033[31mErreur lors de la sauvegarde des parametres.\n");
          }
        }else{
          parametres[6] = 0.00;
          if(updateParam(parametres)) {
            printf("    \033[32mLe mode vaccination a été %s\n", etat[2 + etat_vaccination]);
            etat_vaccination = 1 - etat_vaccination;
          }else{
            printf("    \033[31mErreur lors de la sauvegarde des parametres.\n");
          }
        }
        break;
      case 4:
        if(reinitialiserParam(parametres)) {
          printf("    \033[32mLes paramètres ont étés reinitialisés.\n");
        }else{
          printf("    \033[31mErreur lors de la sauvegarde des parametres.\n");
        }
        break;
      case 5:
        flag = 0;
        break;
      default:
        break;
    }
  }

}

int updateParam(float p[]) {
  FILE* fp = fopen("parametres.txt", "w");
  if(fp != NULL) {
    fprintf(fp, "%.2f BEGIN_CONTAMINATION_RATE\n", p[0]);
    fprintf(fp, "%.2f ILL_CONTAMINATION_RATE\n",p[1]);
    fprintf(fp, "%.2f ZOMBIE_RATE\n", p[2]);
    fprintf(fp, "%.2f IMMUNISATION_RATE\n", p[3]);
    fprintf(fp, "%.2f ZOMBIE_CONTAMINATION_RATE\n", p[4]);
    fprintf(fp, "%.2f DEAD_RATE\n", p[5]);
    fprintf(fp, "%.2f VACCINATION_RATE\n", p[6]);
    fprintf(fp, "%.2f KILL_ZOMBIE_RATE\n", p[7]);
    fclose(fp);
    return 1;
  }else{
    return 0;
  }
}

int loadParam(float p[]) {
  FILE *fp;
	fp = fopen("parametres.txt", "r");
  if(fp != NULL){
    float param;
    char autre[100];
    int i = 0;
    while(fscanf(fp, "%f%s",&param, autre) == 2){
      p[i] = param;
      i++;
    }
    fclose(fp);
    return 1;
  }else{
    return 0;
  }


}

int reinitialiserParam(float parametres[]) {
  float param[] = {0.12, 0.32, 0.4, 0.22, 0.20, 0.33, 0.21, 0.22};
  for(int i = 0; i == 7; i++) {
    parametres[i] = param[i];
  }
  updateParam(param);
  return loadParam(parametres);
}
