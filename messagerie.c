#include "messagerie.h"


void send_message(LetterBox *LB, Personne *A, Personne *B) {
	int futur_etat;
	Message* M = malloc(sizeof(Message));
	if(A == B) { // Si A n'est pas B alors on check juste la transmission et on envois le message que si l'autre doit etre malade
		if(randomize_state(IMMUNISATION_RATE)) { // B ou A car c'est pareil est immunisé
			M->destinataire = B;
			M->emetteur = A;
			M->etat = 2;
			empile(LB, M);
			return;
			//
		}else{
			if(randomize_state(DEAD_RATE)) { // On check si il va mourrir ?
				M->destinataire = B;
				M->emetteur = A;
				M->etat = 3;
				empile(LB, M);
				return;
				//
			}
		}
	}else{ // Si A != B on regarde les proba transmettre la maladie a condition que B ne soit pas mort ou immunisé ou malade
		if(B->etat == 0) { // B Mort avec proba 0.10
			if(randomize_state(CONTAMINATION_RATE)) {
				M->destinataire = B;
				M->emetteur = A;
				M->etat = 1;
				empile(LB, M);
				return;
				//
			}
		}
	}

}


void empile(LetterBox* LB, Message* M){ // Emplile par la fin
	if(LB->first == NULL){ // Aucun elements dans la liste actuellement
		LB->first = M;
		LB->last = M;
	}else{
		LB->last->nextMessage = M;
	 	LB->last = M;

 }
}



Message* depile(LetterBox* LB){ // Depile par le debut
	Message* M = LB->first;
	LB->first = M->nextMessage;
	M->nextMessage = NULL;
	return M;
}

void update(LetterBox *LB) // met à jour l'état des personnes en fonction des messages reçus
	{
	while (LB->first!=NULL)
		{
		Message *M = depile(LB);
		Personne *P = M->destinataire;
		P->etat = M->etat ;
		}
	}

void set(Graph *G, LetterBox *LB) { // verifie l'état des personnes et envoie un message si malade
	for (int i=0; i< G->nb_personnes; i++)
		{
		Personne *P = G->liste_personnes[i];
		if (P->etat == 1)
			{
			send_message(LB, P, P); // envoie un message à lui-même
			Successeur* S = G->liste_successeurs[i];
			while (S != NULL) // on envoie un message à tous les voisins
				{
				send_message(LB, P, S->personne);
				S = S->successeur;
				}
			}
		}
	}
