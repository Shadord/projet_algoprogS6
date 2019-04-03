#include "messagerie.h"


void send_message(LetterBox *LB, Personne *A, Personne *B) {
	int futur_etat;
	Message* M = malloc(sizeof(Message));
	if(A == B) { // Si A n'est pas B alors on check juste la transmission et on envois le message que si l'autre doit etre malade
		if(randomize_state(IMMUNISATION_RATE)) { // B ou A car c'est pareil est immunisé
			M->destinataire = B;
			M->emetteur = A;
			M->etat = 2;
			//
		}else{
			if(randomize_state(DEAD_RATE)) { // On check si il va mourrir ?
				M->destinataire = B;
				M->emetteur = A;
				M->etat = 3;
				//
			}
		}
	}else{ // Si A != B on regarde les proba transmettre la maladie a condition que B ne soit pas mort ou immunisé ou malade
		if(B->etat == 0) { // B Mort avec proba 0.10
			if(randomize_state(CONTAMINATION_RATE)) {
				M->destinataire = B;
				M->emetteur = A;
				M->etat = 1;
				//
			}
		}
	}

	if(M != NULL)
		empile(LB, M);
}


void empile(LetterBox* LB, Message* M){ // Emplile par la fin
	if(LB->first == NULL){ // Aucun elements dans la liste actuellement
		LB->first = M;
		LB->last = M;
	}else{
	 	LB->last->nextMessage = M->nextMessage;
	 	LB->last = M;
 }
}



Message* depile(LetterBox* LB){ // Depile par le debut
	Message* M = LB->first;
	LB->first = M->nextMessage;
	M->nextMessage = NULL;
	return M;
}

void update(LetterBox *LB)
	{
	while (LB->first!=NULL)
		{
		Message *M = depile(LB);
		Personne *P = M->destinataire;
		P->etat = M->etat ;
		}
	}

void set(Graph *G, LetterBox *LB) {

}
