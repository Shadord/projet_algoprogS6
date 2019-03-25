#include "main.h"


void main(int argc, char const *argv[]) {










}

int menu() {
  int reponse;
  printf("===============================================================\n");
  printf("==>   MENU PRINCIPAL DE LA SIMULATION\n");
  printf("===============================================================\n\n");
  printf("1. PREMIERES DONNEES\n");
  printf("2. LANCER LA SIMULATION\n");
  printf("3. AFFICHER LES GRAPHES\n");
  fscanf("%d", &reponse);
  return reponse;
}

int randomize_state(int proba) { // Fonction de random, renvois 1 si la proba est réalisée et 0 sinon
  srand(time(null));
  double nombre  = (rand()/(double)RAND_MAX);
  if(nombre < proba) {
    return 1;
  }else{
    return 0;
  }
}
