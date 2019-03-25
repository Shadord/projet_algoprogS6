#include "personne.h"

/* Creer la matrice d'adjacance
retrouver une personne à partir des coordonnées
trouver les voisins à partir de coordonnées */

void create_graph(Graph* G, const char* grapheFileName)
{
	FILE *fp;
	fp = fopen(grapheFileName, "r");

	if (fp != NULL)
	{
		int nb_personnes, nb_arcs, u, v, w;
		fscanf(fp, "%d %d", &nb_personnes, &nb_arcs);
		G->nb_personnes 		= nb_personnes;
		G->liste_successeurs	= (Personne**) malloc(nb_personnes * sizeof(Personne*));

		for (int i = 0; i < nb_personnes; i++)
			G->liste_successeurs[i]	= NULL;

		for (int i = 0; i < nb_arcs; i++)
		{
			fscanf(fp, "%d %d", &u, &v);
			Personne* s					= malloc(sizeof(Personne));
			s->id					= v;
			s->etat			= 0;
			s->successeur			= G->liste_successeurs[u];
			G->liste_successeurs[u]	= s;
		}
	}
	else printf("File not found.");
	fclose(fp);
}

int randomize_state(float proba) { // Fonction de random, renvois 1 si la proba est réalisée et 0 sinon
  double nombre  = (rand()/(double)RAND_MAX);
  if(nombre < proba) {
    return 1;
  }else{
    return 0;
  }
}
