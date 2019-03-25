#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int destinataire;
	int emetteur;
	int etat;
	} Message ;

typedef struct {
	int id;
	Message *message;
	} Messagerie ;




#endif 
