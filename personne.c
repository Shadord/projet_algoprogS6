#include "personne.h"


void create_graph(Graph* G, const char* grapheFileName, float parametres[])
{
	FILE *fp;
	fp = fopen(grapheFileName, "r");
	if (fp != NULL)
	{
		int nb_personnes, nb_arcs, id_personne, id_successeur, etat;
		fscanf(fp, "%d %d", &nb_personnes, &nb_arcs);
		G->nb_personnes 		= nb_personnes;
		G->liste_successeurs	= (Successeur**) malloc(nb_personnes * sizeof(Successeur*));
		G->liste_personnes	= (Personne**) malloc(nb_personnes * sizeof(Personne*));

		for (int i = 0; i < nb_personnes; i++) {
			G->liste_successeurs[i]	= NULL;
		}
		for (int i = 0; i < nb_personnes; i++) {
			G->liste_personnes[i]	= NULL;
		}

		for (int i = 0; i < nb_arcs; i++)
		{
			fscanf(fp, "%d %d", &id_personne, &id_successeur);
			Personne* P = malloc(sizeof(Personne)); // C'est la personne primaire
			Personne* successeur = malloc(sizeof(Personne)); // C'est la personne successeur
			// On verifie si elles existent !

			if(G->liste_personnes[id_successeur] == NULL) { // Si le successeur existe pas (la personne en elle meme n'est pas crée)
				successeur->id = id_successeur; // On cree son id de successeur
				successeur->etat = randomize_state(parametres[0]); // On cree son état
				successeur->jour_malade=0;
				G->liste_personnes[id_successeur] = successeur; // On le met dans la liste des personnes référencés
			}else{
				successeur = G->liste_personnes[id_successeur]; // Sinon on le recupere			}
			}
			if(G->liste_personnes[id_personne] == NULL) { // On verifie si la personne existe
				P->id = id_personne;
				P->etat = randomize_state(parametres[0]);
				P->jour_malade=0;
				G->liste_personnes[id_personne] = P;
			}else{
				P = G->liste_personnes[id_personne];
			}

			Successeur* S = malloc(sizeof(Successeur)); // On cree l'entité de chaine successeur
			S->personne = successeur; // Elle contient le successeur (son adresse)
			S->successeur	= G->liste_successeurs[id_personne]; // Et on le chaine a successeur
			G->liste_successeurs[id_personne]	= S;
		}
	}
	else printf("File not found.\n");
	fclose(fp);
}

int randomize_state(float proba) { // Fonction de random, renvois 1 si la proba est réalisée et 0 sinon
  double nombre  = (rand()/(double)RAND_MAX);
  if(nombre <= proba) {
    return 1;
  }else{
    return 0;
  }
}

void print_graph(Graph* G) {
	for(int i = 0; i<G->nb_personnes;i++) {
		printf("%d[%d] : " , G->liste_personnes[i]->id, G->liste_personnes[i]->etat);
		Successeur* S = G->liste_successeurs[i];
		while (S != NULL) {
			printf("%d[%d], " , S->personne->id, S->personne->etat);
			S = S->successeur;
		}
		printf(";\n");
	}
}

void generateGrid(Graph *G, int size, float parametres[]) {
	G->nb_personnes = size*size;
	G->liste_successeurs	= (Successeur**) malloc(G->nb_personnes * sizeof(Successeur*));
	G->liste_personnes	= (Personne**) malloc(G->nb_personnes * sizeof(Personne*));
	for (int i = 0; i < G->nb_personnes; i++) {
		Personne* P = malloc(sizeof(Personne));
		P->id = i;
		P->etat = randomize_state(parametres[0]);
		G->liste_personnes[i]	= P;
	}
	for (int i = 0; i < G->nb_personnes; i++) {
		Successeur* S1;
		Successeur* S2;
		Successeur* S3;
		Successeur* S4;
		Personne* P = G->liste_personnes[i];
		if(i%size == 0) { // Bord Gauche
			if(i<size) {// Haut
				S1 = malloc(sizeof(Successeur));
				S1->personne = G->liste_personnes[i+1];
				S1->successeur = NULL;
				S2 = malloc(sizeof(Successeur));
				S2->personne = G->liste_personnes[i+size];
				S2->successeur = S1;
				G->liste_successeurs[i] = S2;
			}else if(i == G->nb_personnes - size) { // Si il est en bas
				S1 = malloc(sizeof(Successeur));
				S1->personne = G->liste_personnes[i+1];
				S1->successeur = NULL;
				S2 = malloc(sizeof(Successeur));
				S2->personne = G->liste_personnes[i-size];
				S2->successeur = S1;
				G->liste_successeurs[i] = S2;
			}else{ // Autre bord gauche
				S1 = malloc(sizeof(Successeur));
				S1->personne = G->liste_personnes[i-size];
				S1->successeur = NULL;
				S2 = malloc(sizeof(Successeur));
				S2->personne = G->liste_personnes[i+size];
				S2->successeur = S1;
				S3 = malloc(sizeof(Successeur));
				S3->personne = G->liste_personnes[i+1];
				S3->successeur = S2;
				G->liste_successeurs[i] = S3;
			}
		}else if(i%size == size-1){ // Bord droit
			if(i<size) {// Haut HAUT DROIT
				S1 = malloc(sizeof(Successeur));
				S1->personne = G->liste_personnes[i-1];
				S1->successeur = NULL;
				S2 = malloc(sizeof(Successeur));
				S2->personne = G->liste_personnes[i+size];
				S2->successeur = S1;
				G->liste_successeurs[i] = S2;
			}else if(i == G->nb_personnes-1) { // Si il est en bas BAS DROIT
				S1 = malloc(sizeof(Successeur));
				S1->personne = G->liste_personnes[i-1];
				S1->successeur = NULL;
				S2 = malloc(sizeof(Successeur));
				S2->personne = G->liste_personnes[i-size];
				S2->successeur = S1;
				G->liste_successeurs[i] = S2;
			}else{ // autre Bord droit
				S1 = malloc(sizeof(Successeur));
				S1->personne = G->liste_personnes[i-size];
				S1->successeur = NULL;
				S2 = malloc(sizeof(Successeur));
				S2->personne = G->liste_personnes[i+size];
				S2->successeur = S1;
				S3 = malloc(sizeof(Successeur));
				S3->personne = G->liste_personnes[i-1];
				S3->successeur = S2;
				G->liste_successeurs[i] = S3;
			}

		}else{ // Il est ailleurs
			if(i<size) {// Haut
				S1 = malloc(sizeof(Successeur));
				S1->personne = G->liste_personnes[i+size];
				S1->successeur = NULL;
				S2 = malloc(sizeof(Successeur));
				S2->personne = G->liste_personnes[i-1];
				S2->successeur = S1;
				S3 = malloc(sizeof(Successeur));
				S3->personne = G->liste_personnes[i+1];
				S3->successeur = S2;
				G->liste_successeurs[i] = S3;
			}else if(i > G->nb_personnes - size) { // Si il est en bas
				S1 = malloc(sizeof(Successeur));
				S1->personne = G->liste_personnes[i-size];
				S1->successeur = NULL;
				S2 = malloc(sizeof(Successeur));
				S2->personne = G->liste_personnes[i-1];
				S2->successeur = S1;
				S3 = malloc(sizeof(Successeur));
				S3->personne = G->liste_personnes[i+1];
				S3->successeur = S2;
				G->liste_successeurs[i] = S3;
			}else{ // SInon...
				S1 = malloc(sizeof(Successeur));
				S1->personne = G->liste_personnes[i-size];
				S1->successeur = NULL;
				S2 = malloc(sizeof(Successeur));
				S2->personne = G->liste_personnes[i+size];
				S2->successeur = S1;
				S3 = malloc(sizeof(Successeur));
				S3->personne = G->liste_personnes[i-1];
				S3->successeur = S2;
				S4 = malloc(sizeof(Successeur));
				S4->personne = G->liste_personnes[i+1];
				S4->successeur = S3;
				G->liste_successeurs[i] = S4;
			}
		}
	}
}

void printGrid2(Graph *G, int size) {
		for(int j = 0; j<G->nb_personnes; j++) {
			if(j%size == 0){
				printf("\n");
			}
			if(G->liste_personnes[j]->etat == 0) {
				printf("\033[32mS ");
			}else if(G->liste_personnes[j]->etat == 1){
				printf("\033[31mM ");
			}else if(G->liste_personnes[j]->etat == 2){
				printf("\033[36mI ");
			}else if(G->liste_personnes[j]->etat == 3){
				printf("\033[33mX ");
			}else if(G->liste_personnes[j]->etat == 4){
				printf("\033[35mZ ");
			}



		}
		printf("\033[0m\n");
}
