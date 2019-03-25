#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "personne.h"

typedef struct _Message {
	Personne* destinataire;
	Personne* emetteur;
	int etat;
	struct _Message* nextMessage;
	} Message ;

typedef struct _LetterBox {
	int proprietaire;
	Message *message;
	struct _LetterBox* nextLetterBox;
} LetterBox;

typedef struct {
	LetterBox* first;
} PMessagerie;

void send_message(PMessagerie *PM, Personne *A, Personne *B);
int isset_message(PMessagerie *PM, int identifiant);


#endif
