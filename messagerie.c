#include "messagerie.h"

int isset_message(PMessagerie *PM, int identifiant)
// Est-ce que ça inexiste
	{
	int existe;
	if (PM->first==NULL)
		existe = 0; 
	else
		existe = 1;
	return existe;
	}
