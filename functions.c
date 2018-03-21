#include "functions.h"

Arbre alloueNoeud(unsigned char lettre) {
	Arbre a = (Arbre)malloc(sizeof(Noeud));
	if (a != NULL) {
		a->lettre = lettre;
		a->filsg = NULL;
		a->frered = NULL;
	}
	return a;
}

void ajouteBranche(Arbre *a, char *mot) {
	if((*a = alloueNoeud(*mot)) != NULL)
		if(*mot != '\0')
			ajouteBranche(&((*a)->filsg), mot+1);
}

/* Pas de gestion d'erreur */
void ajouteMot(Arbre *a, char *mot) {
	Arbre tmp = NULL;
	if(*a == NULL)
		ajouteBranche(a, mot);
	else {
		if(*mot > (*a)->lettre)
			ajouteMot(&((*a)->frered), mot);
		else {	
			if((*mot == (*a)->lettre) && (*mot != '\0'))
				ajouteMot(&((*a)->filsg), mot+1);
			else {
				if(*mot != '\0') {
					ajouteBranche(&tmp, mot);
					tmp->frered = (*a);
					*a = tmp;
				}
			}	
		}
	}
}

int recherche(Arbre a, char *mot) {
	if(a == NULL)
		return 0;
	if(*mot < a->lettre)
		return 0;
	if(*mot == a->lettre) {
		if(*mot == '\0')
			return 1;
		return recherche(a->filsg, mot+1);
	}
	return recherche(a->frered, mot);
}

void afficheLexique(Arbre a, char *buffer, int idx) {
	if(a != NULL) {
		/* Affichage lexicographique de la branche courante */
		buffer[idx] = a->lettre;
		if(a->lettre == '\0')
			printf("%s\n", buffer);
		else
			afficheLexique(a->filsg, buffer, idx+1);

		/* Affichage lexicographique des chaines de caractères supérieures */
		afficheLexique(a->frered, buffer, idx);
	}
}
