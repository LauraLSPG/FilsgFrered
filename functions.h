#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 30

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

/* Fonctions d'ajout d'un mot et d'ajout de mots depuis un fichier */

void ajouteMotsDepuisFichier (Arbre *a, char *nomFichier);

void ajouteMot(Arbre *a, char *mot);

void creeArbreDepuisFichier (Arbre *a, FILE *in);

/* Fonction de Recherche d'un mot dans un lexique */

int recherche(Arbre a, char *mot);

/* Fonctions d'affichage du Lexique depuis un fichier */

void afficheLexique(Arbre *a);

void afficheLexiqueRecursif(Arbre a, char *buffer, int idx);

/* Fonctions de sauvegarde du Lexique dans un fichier */

void sauvegardeLexiqueDansFichier(Arbre a, char *nomFichier);

void sauvegardeLexique(Arbre a, FILE *out, char *buffer, int idx);

/* Fonctions de sauvegarde de l'Arbre dans un fichier */

void sauvegardeArbreDansFichier(Arbre a, char *nomFichier);

void sauvegardeArbre(Arbre a, FILE *out);

void supprimeSuffixe(char *nomFichierSansSuffixe);

void ajouteSuffixe(char *nomFichier, char *suffixe);

#endif
