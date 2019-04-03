#include "personne.h"


void create_graph(Graph* G, const char* grapheFileName)
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

		for (int i = 0; i < nb_personnes; i++)
			G->liste_successeurs[i]	= NULL;

		for (int i = 0; i < nb_personnes; i++)
			G->liste_personnes[i]	= NULL;

		for (int i = 0; i < nb_arcs; i++)
		{
			fscanf(fp, "%d %d %d", &id_personne, &id_successeur, &etat);
			if(G->liste_personnes[id_successeur] == NULL) {
				Personne* P = malloc(sizeof(Personne));
				P->id = id_personne;
				P->etat = etat;
			}else{
				Personne* P = G->liste_personnes[id_successeur];
			}

			Successeur* S = malloc(sizeof(Successeur));
			S->Personne = P;
			S->successeur	= G->liste_successeurs[id_personne];
			G->liste_successeurs[id_personne]	= S;
		}
	}
	else printf("File not found.");
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
