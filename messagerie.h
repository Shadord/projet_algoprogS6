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
	} Message;

typedef struct {
	Message* first;
	Message* last;
} LetterBox;

// Cette fonction verifie que les messages ne soient pas nuls (on sait jamais) et les envois dans la boite
void send_message(LetterBox *LB, Message* M);

// Cette fonction remplie la LetterBox
void empile(LetterBox* LB, Message* M);

// Cette fonction vide la LetterBox
Message* depile(LetterBox* LB);

// Cette fonction traite les messages
void update(LetterBox *LB);

// Cette fonction parcours le graph et établie tous les messages
void set(Graph *G, LetterBox *LB);

/*
Fonctions d'intéractions :
La personne A de la fonction est l'emetteur du changement d'etat sur son voisin.
send_Malade a comme personne A un malade (dans tous les cas).
Elle retourne un objet Message* qui contient le futur etat de la personne B en fonction des probabilités
Chaque etat a sa fonction d'envois de messsage car les Zombie peuvent interragie avec les immunisés et inversement

Pour resumer le déroulement de la simulation complete:
# designe une interraction personnelle
. designe une interraction avec une autre personne

Un sain peut se #vacciner (depend du nombre de jours de la simulation)
Un Malade peut .infecter un sain, #devenir zombie, #mourrir, ou se #guerrir
Un zombie peut mordre un malade ou un sain pour qu'il devienne .zombie et peut que tuer un .immunisé si il le mord
Un immunisé peut .tuer un zombie


Attention !!! si un zombie est a coté d'un immunisé. Il est tout a fait probable,
que l'immunisé tue le zombie et que le zombie tu l'immunsé dans la même journée.
*/

Message* send_Zombie(Personne* A, Personne* B);
Message* send_Immunise(Personne* A, Personne* B);
Message* send_Malade(Personne* A, Personne* B);
Message* send_Sain(Personne* A, Personne* B);

#endif
