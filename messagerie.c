#include "messagerie.h"

void send_message(LetterBox *LB, Personne *A, Personne *B) {
	int futur_etat_B;
	if(A->etat == 1) {// Si A est malade (sinon il envois pas de message)
		if(A != B) { // Si A n'est pas B alors on check juste la transmission et on envois le message que si l'autre doit etre malade
			if(futur_etat_B = randomize_state(0.22) && B->etat == 0) { // B Malade avec proba 0.22
				Message* M = malloc(sizeof(Message));
				M->destinataire = B;
				M->emetteur = A;
				M->etat = futur_etat_B;
				//
			}
		}else{ // Si A == B on regarde les proba pour mort et immunisé
			if(futur_etat_B = randomize_state(0.10) && B->etat == 0) { // B Mort avec proba 0.10
				Message* M = malloc(sizeof(Message));
				M->destinataire = B;
				M->emetteur = A;
				M->etat = futur_etat_B;
				//
			}else if(futur_etat_B = randomize_state(0.40) && B->etat == 0) { // B Immunisé avec proba 0.40
				Message* M = malloc(sizeof(Message));
				M->destinataire = B;
				M->emetteur = A;
				M->etat = futur_etat_B;
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
	 	LB->Last->nextMessage = M->nextMessage;
	 	LB->Last = M;
 }
}



Message* depile(LetterBox* LB){ // Depile par le debut
	Message* M = LB->first;
	LB->first = M->nextMessage;
	M->nextMessage = NULL;
	return M;
}
