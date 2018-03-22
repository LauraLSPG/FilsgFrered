#include "functions.h"

int main(int argc, char const *argv[]) {
	Arbre lexico = NULL;
	int stop = 0;
	char nomFichier[TAILLE_MAX];
	char choix;
	char mot[TAILLE_MAX];

	if(argc == 3) {
		strcpy(nomFichier, argv[2]);
		
		if (strcmp(argv[1], "-l") == 0) {
			afficheLexiqueDepuisFichier(&lexico, nomFichier);
			printf("\n\n");
		}
		else if (strcmp(argv[1], "-s") == 0) {
			strcat(nomFichier, ".L");
			sauvegardeLexiqueDansFichier(lexico, nomFichier);
			printf("Les mots du lexique ont bien été sauvegardés dans le ficher \"%s.L.\"\n\n", argv[2]);
		}
		else if (strcmp(argv[1], "-r") == 0) {
			printf("Quel mot souhaitez-vous chercher dans le lexique ?\n");
			scanf(" %s", mot);
			if(recherche(lexico, mot))
				printf("Le mot \"%s\" est présent dans le lexique.\n\n", mot);
			else {
				printf("Le mot \"%s\" est absent du lexique.\nSouhaitez-vous l'ajouter ?\nSi oui, appuyez sur 1, sinon, sur 0.\n", mot);
				scanf(" %c", &choix);
				if(choix == '1') {
					ajouteMot(&lexico, mot);
					printf("Le mot \"%s\" a bien été ajouté.\n\n", mot);
				}
			}
		}
		else if (strcmp(argv[1], "-S") == 0) {
			strcat(nomFichier, ".DICO");
			sauvegardeArbreDansFichier(lexico, nomFichier);
			printf("L'arbre a bien été sauvegardé dans le ficher \"%s\".DICO.\n\n", argv[2]);
		}
		else {
			printf("Oups, les caractères saisis ne correspondent à aucune option disponible.\n\n");
		}
	}

	if(argc == 2) {
		strcpy(nomFichier, argv[1]);
		while(stop == 0) {
			printf("Que souhaitez-vous faire ?\n- Appuyez sur 1 pour afficher les mots du lexique dans l\'ordre alphabétique.\n- Appuyez sur 2 pour sauvegarder les mots du lexique dans le ficher \"%s\".\n- Appuyez sur 3 pour rechercher un mot dans le lexique.\n- Appuyez sur 4 pour sauvegarder l\'arbre dans le ficher \"%s\".\n- Appuyez sur 5 pour quitter le programme.\n", argv[1], argv[1]);
			scanf(" %c", &choix);

			switch(choix) {
				case '1' :
					afficheLexiqueDepuisFichier(&lexico, nomFichier);
					printf("\n\n");
					break;

				case '2' :
					strcat(nomFichier, ".L");
					sauvegardeLexiqueDansFichier(lexico, nomFichier);
					printf("Les mots du lexique ont bien été sauvegardés dans le ficher \"%s.L.\"\n\n", argv[2]);
					break;

				case '3' :
					printf("Quel mot souhaitez-vous chercher dans le lexique ?\n");
					scanf(" %s", mot);
					if(recherche(lexico, mot))
						printf("Le mot \"%s\" est présent dans le lexique.\n\n", mot);
					else {
						printf("Le mot \"%s\" est absent du lexique.\nSouhaitez-vous l'ajouter ?\nSi oui, appuyez sur 1, sinon, sur 0.\n", mot);
						scanf(" %c", &choix);
						if(choix == '1') {
							ajouteMot(&lexico, mot);
							printf("Le mot \"%s\" a bien été ajouté.\n\n", mot);
						}
					}
					break;

				case '4' :
					strcat(nomFichier, ".DICO");
					sauvegardeArbreDansFichier(lexico, nomFichier);
					printf("L'arbre a bien été sauvegardé dans le ficher \"%s\".DICO.\n\n", argv[1]);
					break;

				case '5' :
					stop = 1;
					break;

				default :

					break;
			}
		}
	}

	return 0;
}

/*
Bright star would I were stedfast as thou art
Not in lone splendour hung aloft the night
And watching with eternal lids apart
Like nature's patient sleepless Eremite
The moving waters at their priestlike task
Of pure ablution round earth's human shores
Or gazing on the new soft-fallen mask
Of snow upon the mountains and the moors
No—yet still stedfast still unchangeable
Pillow'd upon my fair love's ripening breast
To feel for ever its soft fall and swell
Awake for ever in a sweet unrest
Still still to hear her tender-taken breath
And so live ever—or else swoon to death
*/