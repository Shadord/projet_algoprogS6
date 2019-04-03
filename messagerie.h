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

typedef struct {
	Message* first;
	Message* last;
} LetterBox;

void send_message(LetterBox *LB, Personne *A, Personne *B);
void empile(LetterBox* LB, Message* M);
Message* depile(LetterBox* LB);

#endif
