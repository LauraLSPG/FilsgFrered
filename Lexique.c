#include "functions.h"

int main(int argc, char const *argv[]) {
	Arbre lexico = NULL;
	int stop = 0;
	char buffer[30]; 
	char choix;
	char mot[30];

	ajouteMot(&lexico, "ce");
	ajouteMot(&lexico, "lettre");
	ajouteMot(&lexico, "des");
	ajouteMot(&lexico, "ces");
	ajouteMot(&lexico, "mettre");

	if(argc == 2) {
		while(stop == 0) {
			printf("Que souhaitez-vous faire ?\n- Appuyez sur 1 pour afficher les mots du lexique dans l\'ordre alphabétique.\n- Appuyez sur 2 pour sauvegarder les mots du lexique dans le ficher \"%s\".\n- Appuyez sur 3 pour rechercher un mot dans le lexique.\n- Appuyez sur 4 pour sauvegarder l\'arbre dans le ficher \"%s\".\n- Appuyez sur 5 pour quitter le programme.\n", argv[1], argv[1]);
			scanf(" %c", &choix);

			switch(choix) {
				case '1' :
					afficheLexique(lexico, buffer, 0);
					break;

				case '2' :
					printf("Oups, cette fonction n'est pas encore disponible. Réessayez plus tard !\n");
					break;

				case '3' :
					printf("Quel mot souhaitez-vous chercher dans le lexique ?\n");
					scanf(" %s", mot);
					if(recherche(lexico, mot))
						printf("Le mot \"%s\" est présent dans le lexique.\n", mot);
					else {
						printf("Le mot \"%s\" est absent du lexique.\nSouhaitez-vous l'ajouter ?\nSi oui, appuyez sur 1, sinon, sur 0.\n", mot);
						scanf(" %c", &choix);
						if(choix == '1') {
							ajouteMot(&lexico, mot);
							printf("Le mot \"%s\" a bien été ajouté.\n", mot);
						}
					}
					break;

				case '4' :
					printf("Oups, cette fonction n'est pas encore disponible. Réessayez plus tard !\n");
					break;

				case '5' :
					stop = 1;
					break;

				default :
					printf("Oups, les caractères saisis ne correspondent à aucune option disponible.\n");
					break;
			}
		}
	}

	return 0;
}