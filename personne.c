#include "personne.h"



int randomize_state(float proba) { // Fonction de random, renvois 1 si la proba est réalisée et 0 sinon
  double nombre  = (rand()/(double)RAND_MAX);
  if(nombre < proba) {
    return 1;
  }else{
    return 0;
  }
}
