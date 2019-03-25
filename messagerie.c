#include "messagerie.h"

int isset_message(PMessagerie *PM, int identifiant, int taille_matrice)
// regarde si la boite au lettre de identifiant contient un message
	{
	LetterBox *LB;
	LB=PM->first;
	while (LettreBox->proprietaire != identifiant)
		{
		LB=LB->nextLetterBox;
		}
	if (LB->Message==NULL)
		return 0; // pas de lettre
	else
		return 1;
	}


