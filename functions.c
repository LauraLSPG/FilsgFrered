#include "functions.h"
#include "dot.h"

Arbre alloueNoeud(unsigned char lettre) {

	Arbre a =(Arbre)malloc(sizeof(Noeud));

	if(a != NULL) {
		a->lettre = lettre;
		a->filsg = NULL;
		a->frered = NULL;
	}

	return a;
}

void ajouteBranche(Arbre *a, char *mot) {

	if((*a = alloueNoeud(*mot)) != NULL) {
		if(*mot != '\0') {
			ajouteBranche(&((*a)->filsg), mot+1);
		}
	}
}

void ajouteMot(Arbre *a, char *mot) {

	Arbre tmp = NULL;

	if(*a == NULL) ajouteBranche(a, mot);
	else {
		if(*mot > (*a)->lettre) ajouteMot(&((*a)->frered), mot);
		else {
			if((*mot == (*a)->lettre) && (*mot != '\0')) ajouteMot(&((*a)->filsg), mot+1);
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

void ajouteMotsDepuisFichier(Arbre *a, char *nomFichier) {

    int i;
	char caractereActuel;
    char bufferAjout[TAILLE_MAX];
    FILE *in = fopen(nomFichier, "r");

    if(in != NULL) {

        while((caractereActuel = fgetc(in)) != EOF) {
            i = 0;
            while(caractereActuel != 32 && caractereActuel != EOF) {
                bufferAjout[i] = caractereActuel;
                i++;
                caractereActuel = fgetc(in);
            }
            bufferAjout[i] = '\0';
            ajouteMot(a, bufferAjout);
        }
    }
    fclose(in);
}

void creeArbreDepuisFichier(Arbre *a, char *nomFichier) {

    FILE *in = fopen(nomFichier, "r");

    fclose(in);
}

void creeArbre(Arbre *a, FILE *in) {

	char caractereActuel;
    if(in != NULL) {

        while((caractereActuel = fgetc(in)) != EOF) {

            switch(caractereActuel) {

            case 32 :
               (*a)->lettre = '\0';
                creeArbre(&((*a)->frered), in);
                break;

            case '\n' :
                return;
                break;

            default :
               (*a)->lettre = caractereActuel;
                creeArbre(&((*a)->filsg), in);
                creeArbre(&((*a)->frered), in);
                break;
            }
        }
    }
}

int recherche(Arbre a, char *mot) {

	if(a == NULL) return 0;
	if(*mot < a->lettre) return 0;
	if(*mot == a->lettre) {
		if(*mot == '\0') return 1;
		return recherche(a->filsg, mot+1);
	}
	return recherche(a->frered, mot);
}

void afficheLexiqueDepuisFichier(Arbre *a, char *nomFichier) {

    char buffer[TAILLE_MAX];
    ajouteMotsDepuisFichier(a, nomFichier);
    afficheLexique(*a, buffer, 0);
    makedot(*a, "Lexique.dot");
    system("dot -Tpdf Lexique.dot -o Lexique.pdf");

}

void afficheLexique(Arbre a, char *buffer, int idx) {

    if(a != NULL) {
        buffer[idx] = a->lettre;
        if(a->lettre == '\0') printf("%s\n", buffer);
        else {
            afficheLexique(a->filsg, buffer, idx+1);
            afficheLexique(a->frered, buffer, idx);
        }
    }
}

void sauvegardeLexiqueDansFichier(Arbre a, char *nomFichier) {

    FILE *out = fopen(nomFichier, "w");
    char buffer[TAILLE_MAX];
    sauvegardeLexique(a, out, buffer, 0);
    fclose(out);

}

void sauvegardeLexique(Arbre a, FILE *out, char *buffer, int idx) {

    if(out != NULL && a != NULL) {

        buffer[idx] = a->lettre;

        if(a->lettre == '\0') {
            buffer[idx] = ' ';
            fprintf(out, "%s\n", buffer);
        }

        else {
            sauvegardeLexique(a->filsg, out, buffer, idx+1);
            sauvegardeLexique(a->frered, out, buffer, idx);
        }
    }

}

void sauvegardeArbreDansFichier(Arbre a, char *nomFichier) {

    FILE *out = fopen(nomFichier, "w");
    sauvegardeArbre(a, out);
}

void sauvegardeArbre(Arbre a, FILE *out) {

    if(a != NULL) {
        if(a != '\0')  {
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