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

void ajouteMot(Arbre *a, char *mot);

int recherche(Arbre a, char *mot);

<<<<<<< HEAD
void afficheLexique(Arbre a, char *buffer, int idx);
=======
Arbre alloueNoeud(char lettre);

void ajouteMot (Arbre *a, char *mot);

void afficheLexique (Arbre a);
>>>>>>> 2a4a91dc7af4dd36ecd2221bc12c1400d2f5afd2

void sauvegardeMots(Arbre a, FILE *out);

void sauvegardeArbre(Arbre a ,FILE *out);

<<<<<<< HEAD
#endif
=======
void sauvegardeArbre (Arbre a , FILE *out);
>>>>>>> 2a4a91dc7af4dd36ecd2221bc12c1400d2f5afd2
