#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Message {
	int destinataire;
	int emetteur;
	int etat;
	struct _Message nextMessage;
	} Message ;

typedef struct _LetterBox {
	int proprietaire;
	Message *message;
	struct _LetterBox *nextLetterBox;
} LetterBox;

typedef struct {
	LetterBox* first;
} PMessagerie;

void send_message(Messagerie *M, int destinataire);
int isset_message(Messagerie *M, int identifiant);


#endif
