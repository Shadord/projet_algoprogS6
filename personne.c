#include "personne.h"


void create_graph(Graph* G, const char* grapheFileName)
{
	FILE *fp;
	fp = fopen(grapheFileName, "r");
	printf("1\n");
	if (fp != NULL)
	{
		int nb_personnes, nb_arcs, id_personne, id_successeur, etat;
		fscanf(fp, "%d %d", &nb_personnes, &nb_arcs);
		G->nb_personnes 		= nb_personnes;
		printf("1\n");
		G->liste_successeurs	= (Successeur**) malloc(nb_personnes * sizeof(Successeur*));
		printf("2\n");
		G->liste_personnes	= (Personne**) malloc(nb_personnes * sizeof(Personne*));
		printf("3\n");
		for (int i = 0; i < nb_personnes; i++) {
			G->liste_successeurs[i]	= NULL;
		}
		printf("4\n");

		for (int i = 0; i < nb_personnes; i++) {
			G->liste_personnes[i]	= NULL;
		}
		printf("5\n");

		for (int i = 0; i < nb_arcs; i++)
		{
			fscanf(fp, "%d %d", &id_personne, &id_successeur);
			Personne* P = malloc(sizeof(Personne)); // C'est la personne primaire
			Personne* successeur = malloc(sizeof(Personne)); // C'est la personne successeur
			// On verifie si elles existent !

			if(G->liste_personnes[id_successeur] == NULL) { // Si le successeur existe pas (la personne en elle meme n'est pas crée)
				successeur->id = id_successeur; // On cree son id de successeur
				successeur->etat = 1; // On cree son état
				G->liste_personnes[id_successeur] = successeur; // On le met dans la liste des personnes référencés
			}else{
				successeur = G->liste_personnes[id_successeur]; // Sinon on le recupere			}
			}
			if(G->liste_personnes[id_personne] == NULL) { // On verifie si la personne existe
				P->id = id_personne;
				P->etat = 1;
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
