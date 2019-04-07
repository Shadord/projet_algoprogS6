#include "messagerie.h"
#include "math.h"
#include "time.h"

int menu(); // Affiche le menu et propose des initialisations


void simulation(Graph *G, LetterBox *LB, int size, float parametres[]); // Fonction principale de simulation


int graphSize(); // Demande la taille de la grille


void compteur(FILE* fp, Graph *G, int day); //Fonction qui compte et ecrit les resultats successifs dans un fichier texte

void parametreMenu(float parametres[]);

int updateParam(float p[]);
int reinitialiserParam(float p[]);
int loadParam(float p[]);
