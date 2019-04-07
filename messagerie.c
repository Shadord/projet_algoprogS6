#include "messagerie.h"


void send_message(LetterBox *LB, Message* M) {
	if(M != NULL) {
		empile(LB, M);
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

void set(Graph *G, LetterBox *LB, int jour_courant, int jour_vacc) { // verifie l'état des personnes et envoie un message
	for (int i=0; i< G->nb_personnes; i++)
		{
		Personne *P = G->liste_personnes[i];

		if (P->etat==0 && jour_courant==jour_vacc) // si la personne est saine et que c'est le jour de campagne de vaccination
			{
			send_message(LB, send_Sain(P,P));
			}
		if (P->etat == 1) // si la personne est malade
			{
			send_message(LB, send_Malade(P,P)); // envoie un message à lui-même
			Successeur* S = G->liste_successeurs[i];
			while (S != NULL) // on envoie un message à tous les voisins
				{
				send_message(LB, send_Malade(P, S->personne));
				S = S->successeur;
				}
			}
		if (P->etat==2) // si la personnne est immunisée
			{
			Successeur *S = G->liste_successeurs[i];
			while (S!=NULL) // on envoie un message à tous les voisins
				{
				send_message(LB, send_Immunise(P, S));
				S=S->successeur;
				}
			}
		if (P->etat==4) // si la personne est zombie
			{
			Successeur *S = G->liste_successeurs[i];
			while (S!=NULL) // on envoie un message à tous les voisins
				{
				send_message(LB, send_Zombie(P, S));
				S=S->successeur;
				}
			}
		}
	}

Message* send_Malade(Personne* A, Personne *B) { // Si un malade envoit un message

	int futur_etat = -1;
	if(A == B) { // Si A  est B alors il s'envoit un msg a lui même. Il peut :
		if(randomize_state(IMMUNISATION_RATE)) { // En premier être immunisé (etat prioritaire)
			futur_etat = 2;
			//
		}else{
			if(randomize_state(DEAD_RATE)) { // En second mourrir
				futur_etat = 3;
				//
			}else{
				if(randomize_state(ZOMBIE_RATE)) { // En dernier devenir un Zombie
					futur_etat = 4;
					//
				}
			}
		}
	}else{ // Si A != B on regarde les proba transmettre la maladie a condition que B ne soit pas mort ou immunisé ou malade
		if(B->etat == 0) { // B Mort avec proba 0.10
			if(randomize_state(ILL_CONTAMINATION_RATE)) {
				futur_etat = 1;
				//
			}
		}
	}
	if(futur_etat != -1) {
		Message* M = malloc(sizeof(Message));
		M->destinataire = B;
		M->emetteur = A;
		M->etat = futur_etat;
		return M;
	}
}

Message* send_Zombie(Personne* A, Personne* B) {
	int futur_etat = -1;
	if(A == B) { // Si A  est B alors il s'envoit un msg a lui même. Il peut : rien faire... il reste zombie

	}else{ // Si A != B on regarde ce qu'il peut transmettre a B
		if(randomize_state(ZOMBIE_CONTAMINATION_RATE)) {
			if(B->etat == 0 || B->etat == 1) { // Si B est sain ou malade, il peut se faire mordre et devenir zombie
				futur_etat = 4;
				//
			}else if(B->etat == 2){ // Si B est immunisé et que un zombie le mord, il meurt (parce que les zombies savent qu'il est immunisé)
				futur_etat = 3;
				//
			}
		}
	}
	if(futur_etat != -1) {
		Message* M = malloc(sizeof(Message));
		M->destinataire = B;
		M->emetteur = A;
		M->etat = futur_etat;
		return M;
	}
}

Message* send_Sain(Personne *A, Personne *B) { // un individu sain peut se faire vacciner lors de la campagne le jour j
	int futur_etat = -1;
	if(A == B) { // Si A n'est pas B alors on check juste la transmission et on envoie le message que si l'autre doit etre malade
		if(randomize_state(VACCINATION_RATE)) { // B ou A car c'est pareil, probabilité que le vaccin fonctionne et que l'individu devienne immunisé
			futur_etat=2;
		}
	if (futur_etat!=-1)
		{
		Message* M = malloc(sizeof(Message));
			M->destinataire = B;
			M->emetteur = A;
			M->etat = futur_etat;
		}
	}
}

Message* send_Immunise(Personne *A, Personne *B) { // Un immunisé peut tuer un zombie ou devenir zombie
	int futur_etat = -1;
	if(A != B) { //
		if(randomize_state(KILL_ZOMBIE_RATE)) { // B ou A car c'est pareil, probabilité que le vaccin fonctionne et que l'individu devienne immunisé
			futur_etat=3;
		}
	if (futur_etat != -1)
		{
		Message* M = malloc(sizeof(Message));
			M->destinataire = B;
			M->emetteur = A;
			M->etat = futur_etat;
		}
	}
}
