#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*
	COMPILATION
	gcc -ansi -Wall Lexique.c -o Lexique
	./Lexique
*/

#ifndef FG_FrD
#define FG_FrD

typedef struct noeud {
    unsigned char lettre;
    struct noeud *filsg, *frered;
} Noeud, *Arbre;

Arbre alloueNoeud(unsigned char lettre);

void ajouteBranche(Arbre *a, char *mot);

void ajouteMot(Arbre *a, char *mot);;

int recherche(Arbre a, char *mot);

void afficheLexique(Arbre a, char *buffer, int idx);

void sauvegardeLexique(Arbre a, FILE *out);

void sauvegardeArbre(Arbre a, FILE *out);

#endif
