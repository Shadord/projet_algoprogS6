#include "messagerie.h"

void send_message(PMessagerie *PM, Personne *A, Personne *B) {
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

void update(LetterBox *LB)
	{
	while (LB->first!=NULL)
		{
		Message *M = depile(LB);
		Personne *P = M->destinataire;
		P->etat = M->etat ;
		}
	}
