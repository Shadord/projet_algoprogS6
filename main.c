#include "main.h"


void main(int argc, char const *argv[]) {

  /// Chargement des parametres
  float parametre[8];
  if(loadParam(parametres) != 1) {
    printf("Erreur lors du chargement des parametres\n");
  }

  /// Creation du graphe
  Graph G;
  G.nb_personnes = -1;

  /// Creation de la boite au lettre (file  : FIFO)
  LetterBox LB;
  LB.first = NULL;
  LB.last = NULL;

  const char* filename = "graph_10_13.txt"; // Nom du fichier contenant le graph
  int size; // Variable pour la taille d'un graph GRILLE
  int reponse; // Reponse du menu principal

  while(1){ // Bouche sans fin
    reponse = menu(); // On recupere la valeur entrée par l'utilisateur
    if(reponse == 1) {
      create_graph(&G, filename); // Creation d'un graph normal grace au fichier et affichage
      print_graph(&G);
    }else if(reponse == 2) { // Creation d'un graph grille avec demande de taille et affichage
      size = graphSize();
      generateGrid(&G, size);
      printGrid2(&G, size);
    }else if(reponse == 4){ // Simulation si le graph est crée
      if(G.nb_personnes != -1){
        simulation(&G, &LB, size);
        system("python graph.py");
      }else{
        printf("  Erreur, votre Graph est vide.\n");
      }
    }else if(reponse == 3) { // On rentre dans le menu des parametres
      parametreMenu();
    }else if(reponse == 5) { // On quitte le programme
      return;
    }
  }

}


void compteur(FILE* fp, Graph *G, int day) {
  int sain = 0, malade = 0, imm = 0, dead = 0, zombie = 0;
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
  printf("3. MODIFIER LES PARAMETRES DE SIMULATION\n");
  printf("4. LANCER LA SIMULATION\n");
  printf("5. QUITTER LE PROGRAMME\n");
  scanf("%d", &reponse);
  return reponse;
}

void simulation(Graph *G, LetterBox *LB, int size, float parametres[]) {
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
	for (int i=0; i<temps; i++) {
		printf("Jour %d : \n", i+1);
		set(G,LB, i, vaccination_day, parametres);
		update(LB);
		printGrid2(G, size);
    compteur(fp, G, i+1);
	}
  fclose(fp);
}

void parametreMenu(float parametres[]) {
  int reponse;
  int flag = 1;
  int etat_zombie = parametres[2] != 0 && parametres[4] != 0;
  int etat_vaccination = parametres[6] != 0;
  char etat[4] = {"DESACTIVER", "ACTIVER", "DESACTIVE", "ACTIVE"};
  while(flag) {
    printf("    ===============================================================\n");
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
        system("nano parametre.txt");
        break;
      case 2:
        parametres[2] = 0.30;
        parametres[4] = 0.23;
        if(updateParam(parametres)) {
          printf("    Le mode zombie a été %s avec les valeurs de probabilité suivantes : \n", etat[2 + etat_zombie]);
          printf("        - Probabilité qu'un zombie morde une personne : 0.30\n");
          printf("        - Probabilité qu'un malade devienne un zombie : 0.23\n");
          etat_zombie == 1 - etat_zombie;
        }else{
          printf("    Erreur lors de la sauvegarde des parametres.\n");
        }
        break;
      case 3:
        parametre[6] = 0.24;
        if(updateParam(parametres)) {
          printf("    Le mode vaccination a été %s avec la valeur de probabilité suivante : \n", etat[2 + etat_vaccination]);
          printf("        - Probabilité qu'un sain aille se faire vacciner : 0.24\n");
          etat_vaccination == 1 - etat_vaccination;
        }else{
          printf("    Erreur lors de la sauvegarde des parametres.\n");
        }
        break;
      case 4:
        if(reinitialiserParam(parametres)) {
          printf("    Les paramètres ont étés reinitialisés.\n");
        }else{
          printf("    Erreur lors de la sauvegarde des parametres.\n");
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
    fprintf("Parametres de la SIMULATION\n
    %.2f //Probabilite de contamination initiale
    %.2f // Proba qu'un malade transmette sa maladie
    %.2f // Proba qu'un zombie morde qqun
    %.2f // Proba d'etre immunisé en etant malade
    %.2f // Proba de devenir naturellement zombie en etant malade
    %.2f // Proba qu'un malade meurt
    %.2f // Proba qu'un individu sain se fasse immunisé : Immunisation marche + Qu'il ai l'argent etc...
    %.2f // Proba qu'un immunisé tue un zombie
    "; p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]});
    fclose(fp);
    return 1;
  }else{
    return 0;
  }
}

int loadParam(float p[]) {
  FILE *fp;
	fp = open(grapheFileName, "r");
  if(fp != NULL){
    float param;
    char autre[100];
    for(int i = 0; i == 7; i++) {
      fscanf("%f;%[^\n]s", param, autre);
      p[i] = param;
    }
    return 1;
  }else{
    return 0;
  }


}

int reinitialiserParam(float paramtres[]) {
  return updateParam({0.12, 0.32, 0.4, 0.22, 0.20, 0.33, 0.21, 0.22});
}
