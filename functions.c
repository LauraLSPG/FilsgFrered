#include "functions.h"
#include "dot.h"

/*
	Fonction d'allocation dynamiquement de la mémoire pour un caractère, c'est-à-dire un noeud
	Retourne l'arbre
*/
Arbre alloueNoeud(unsigned char lettre) {

	Arbre a =(Arbre)malloc(sizeof(Noeud));

	if(a != NULL) {
		a->lettre = lettre;
		a->filsg = NULL;
		a->frered = NULL;
	}

	return a;
}

/*
	Bla
*/
void ajouteBranche(Arbre *a, char *mot) {

	if((*a = alloueNoeud(*mot)) != NULL) {
		if(*mot != '\0') {
			ajouteBranche(&((*a)->filsg), mot+1);
		}
	}
}

/*
	Bla
*/
void ajouteMot(Arbre *a, char *mot) {

	Arbre tmp = NULL;

	if(*a == NULL) ajouteBranche(a, mot);
	else {
		if(*mot > (*a)->lettre) ajouteMot(&((*a)->frered), mot);
		else {
			if((*mot == (*a)->lettre) && (*mot != '\0')) ajouteMot(&((*a)->filsg), mot+1);
			else {
				if((*a)->lettre != '\0') {
          ajouteBranche(&tmp, mot);
					tmp->frered = (*a);
					*a = tmp;
				}
			}
		}
	}
}

/*
	Bla
*/
void ajouteMotsDepuisFichier(Arbre *a, char *nomFichier) {

  	int i;
		char caractereActuel;
    char bufferAjout[TAILLE_MAX];
    FILE *in = fopen(nomFichier, "r");

    if(in != NULL) {

        while((caractereActuel = fgetc(in)) != EOF) {
            i = 0;
            while(caractereActuel != 32 && caractereActuel != EOF) {
            	if(caractereActuel != 10 && caractereActuel != 13) {
	                bufferAjout[i] = caractereActuel;
	                i++;
            	}
	                caractereActuel = fgetc(in);
            }
            bufferAjout[i] = '\0';
            ajouteMot(a, bufferAjout);
        }
    }
    fclose(in);
}

/*
	Bla
*/
void creeArbreDepuisFichier(Arbre *a, FILE *in, char *buffer, int index) {

	char caractereActuel;

    if(in != NULL && (caractereActuel = fgetc(in)) != EOF) {

					if (caractereActuel != '\n') {

						if (caractereActuel == ' ') {
							buffer[index] = '\0';
							ajouteMot(a, buffer);
							creeArbreDepuisFichier(a, in, buffer, index);
						}
						else {
							buffer[index] = caractereActuel;
							creeArbreDepuisFichier(a, in, buffer, index+1);
						}
					}
					if (index == 0) creeArbreDepuisFichier(a, in, buffer, index);
					return;
    }
}

/*
	Recherche le mot passé en paramètre dans l'arbre également passé en paramètre
	Retourne :
		0	si le mot est absent de l'arbre ou si si l'arbre est vide,
		1	si le mot est présent dans l'arbre
*/
int recherche(Arbre a, char *mot) {

	if(a == NULL) return 0;
	if(*mot < a->lettre) return 0;
	if(*mot == a->lettre) {
		if(*mot == '\0') return 1;
		return recherche(a->filsg, mot+1);
	}
	return recherche(a->frered, mot);
}

void afficheLexique(Arbre a) {

    char buffer[TAILLE_MAX];
    afficheLexiqueRecursif(a, buffer, 0);
    makedot(a, "Lexique.dot");
    system("dot -Tpdf Lexique.dot -o Lexique.pdf");

}

/*
	Affiche chaque lettre en parcourant l'arbre fils gauche jusqu'à la fin du mot ('\0') puis passe au frère droit
*/
void afficheLexiqueRecursif(Arbre a, char *buffer, int idx) {

    if(a != NULL) {
        buffer[idx] = a->lettre;
        if(a->lettre == '\0') {
                printf("%s\n", buffer);
        }
        else {
            afficheLexiqueRecursif(a->filsg, buffer, idx+1);
        }
        afficheLexiqueRecursif(a->frered, buffer, idx);
    }
}

/*
	Ouvre le fichier passé en paramètre, appelle la fonction de sauvegarde récursive et ferme le fichier
*/
void sauvegardeLexiqueDansFichier(Arbre a, char *nomFichier) {

    FILE *out = fopen(nomFichier, "w+");
    char buffer[TAILLE_MAX];
    sauvegardeLexique(a, out, buffer, 0);
    fclose(out);

}

/*
	Bla
	Ecrit chaque lettre dans le fichier en parcourant l'arbre fils gauche jusqu'à la fin du mot ('\0') puis passe au frère droit
*/
void sauvegardeLexique(Arbre a, FILE *out, char *buffer, int idx) {

    if(out != NULL && a != NULL) {

        buffer[idx] = a->lettre;

        if(a->lettre == '\0') {
            buffer[idx] = ' ';
            buffer[idx+1] = '\0';
            fprintf(out, "%s", buffer);
            sauvegardeLexique(a->frered, out, buffer, idx);
        }

        else {
            sauvegardeLexique(a->filsg, out, buffer, idx+1);
            sauvegardeLexique(a->frered, out, buffer, idx);
        }
    }
}

/*
	Ouvre le fichier passé en paramètre, appelle la fonction de sauvegarde récursive et ferme le fichier
*/
void sauvegardeArbreDansFichier(Arbre a, char *nomFichier) {

    FILE *out = fopen(nomFichier, "w+");
    sauvegardeArbre(a, out);
    fclose(out);
}

/*
	Bla
	Ecrit chaque lettre dans le fichier en parcourant l'arbre fils gauche jusqu'à la fin du mot ('\0') puis passe au frère droit
		'\n' indique un sous arbre vide
		' ' indique la fin d'un mot
*/
void sauvegardeArbre(Arbre a, FILE *out) {

    if(a != NULL) {
        if(a->lettre != '\0')  {
            fprintf(out, "%c", a->lettre);
            sauvegardeArbre(a->filsg, out);
            sauvegardeArbre(a->frered, out);
        }
        else {
            fprintf(out, " ");
            sauvegardeArbre(a->frered, out);
        }
			}
    else fprintf(out, "\n");
}

/*
	Supprime l'extension du nom de fichier passé en paramètre en parcourant la chaîne de caractère jusqu'à trouver un point et en le remplaçant par la caractère de fin de mot ('\0')
*/
void supprimeSuffixe(char *nomFichier) {

	int idx = 0;

	while(nomFichier[idx] != '.' && nomFichier[idx] != '\0') {
		idx++;
	}
	nomFichier[idx] = '\0';
}

/*
	Concatène le nom de fichier passé en paramètre sans extension avec la nouvelle extension passée en paramètre
*/
void ajouteSuffixe(char *nomFichier, char *suffixe) {

	supprimeSuffixe(nomFichier);
	strcat(nomFichier, suffixe);
}
