#include "functions.h"
#include "dot.h"

int main(int argc, char const *argv[]) {

	Arbre lexico = NULL;
	int stop = 0;
	char nomFichierTxt[TAILLE_MAX];
	char nomFichierCourant[TAILLE_MAX];
	char choix;
	char mot[TAILLE_MAX];
	FILE *dico;

	if(argc == 3) {

		strcpy(nomFichierTxt, argv[2]);
		strcpy(nomFichierCourant, nomFichierTxt);

		if (strcmp(argv[1], "-l") == 0) {

			if (!lexico) {
                ajouteSuffixe(nomFichierCourant, ".DICO");
								if ((dico = fopen(nomFichierCourant, "r"))) {
									printf("chargé depuis dico\n");
									creeArbreDepuisFichier(&lexico, dico);
									fclose(dico);
								}
				else ajouteMotsDepuisFichier(&lexico, nomFichierTxt);

			}
			afficheLexique(lexico);
			printf("\n");
		}

		else if (strcmp(argv[1], "-s") == 0) {

        if (!lexico) {
                ajouteSuffixe(nomFichierCourant, ".DICO");
								if ((dico = fopen(nomFichierCourant, "r"))) {
									printf("chargé depuis dico\n");
									creeArbreDepuisFichier(&lexico, dico);
									fclose(dico);
								}
				else ajouteMotsDepuisFichier(&lexico, nomFichierTxt);

			}

			ajouteSuffixe(nomFichierCourant, ".L");
			sauvegardeLexiqueDansFichier(lexico, nomFichierCourant);
			printf("Les mots du lexique ont bien été sauvegardés dans le fichier \"%s.\"\n\n", nomFichierTxt);
		}

		else if (strcmp(argv[1], "-r") == 0) {

			printf("Quel mot souhaitez-vous chercher dans le lexique ?\n");
			scanf(" %s", mot);

			if (!lexico) {
                ajouteSuffixe(nomFichierCourant, ".DICO");
								if ((dico = fopen(nomFichierCourant, "r"))) {
									printf("chargé depuis dico\n");
									creeArbreDepuisFichier(&lexico, dico);
									fclose(dico);
								}
				else ajouteMotsDepuisFichier(&lexico, nomFichierTxt);

			}

			if(recherche(lexico, mot) == 1) printf("Le mot \"%s\" est présent dans le lexique.\n\n", mot);
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
			ajouteSuffixe(nomFichierCourant, ".DICO");
			lexico = NULL;
			ajouteMotsDepuisFichier(&lexico, nomFichierTxt);
			sauvegardeArbreDansFichier(lexico, nomFichierCourant);
			printf("L'arbre a bien été sauvegardé dans le fichier \"%s\".\n\n", nomFichierTxt);
		}

		else printf("Oups, les caractères saisis ne correspondent à aucune option disponible.\n\n");
	}

	if(argc == 2) {
		strcpy(nomFichierTxt, argv[1]);
		strcpy(nomFichierCourant, nomFichierTxt);


		while(stop == 0) {

			printf("Que souhaitez-vous faire ?\n");
            printf("- Appuyez sur 1 pour afficher les mots du lexique dans l\'ordre alphabétique.\n");
            ajouteSuffixe(nomFichierCourant, ".");
            printf("- Appuyez sur 2 pour sauvegarder les mots du lexique dans le fichier \"%s\".\n", nomFichierCourant);
            printf("- Appuyez sur 3 pour rechercher un mot dans le lexique.\n");
            ajouteSuffixe(nomFichierCourant, ".DICO");
            printf("- Appuyez sur 4 pour sauvegarder l\'arbre dans le fichier \"%s\".\n", nomFichierCourant);
            printf("- Appuyez sur 5 pour quitter le programme.\n");

			scanf(" %c", &choix);

			switch(choix) {
				case '1' :
					if (!lexico) {
                ajouteSuffixe(nomFichierCourant, ".DICO");
                if ((dico = fopen(nomFichierCourant, "r"))) {
										printf("chargé depuis dico\n");
                    creeArbreDepuisFichier(&lexico, dico);
                    fclose(dico);
                    }
                else ajouteMotsDepuisFichier(&lexico, nomFichierTxt);
          }
					afficheLexique(lexico);
					printf("\n");
					break;

				case '2' :
				    if (!lexico) {
                        ajouteSuffixe(nomFichierCourant, ".DICO");
												if ((dico = fopen(nomFichierCourant, "r"))) {
													printf("chargé depuis dico\n");
													creeArbreDepuisFichier(&lexico, dico);
													fclose(dico);
												}
                        else ajouteMotsDepuisFichier(&lexico, nomFichierTxt);

                    }
					ajouteSuffixe(nomFichierCourant, ".L");
					sauvegardeLexiqueDansFichier(lexico, nomFichierCourant);
					printf("Les mots du lexique ont bien été sauvegardés dans le fichier \"%s.\"\n\n", nomFichierCourant);
					break;

				case '3' :
					printf("Quel mot souhaitez-vous chercher dans le lexique ?\n");
					scanf(" %s", mot);

					if (!lexico) {
                        ajouteSuffixe(nomFichierCourant, ".DICO");
												if ((dico = fopen(nomFichierCourant, "r"))) {
													printf("chargé depuis dico\n");
													creeArbreDepuisFichier(&lexico, dico);
													fclose(dico);
												}
                        else ajouteMotsDepuisFichier(&lexico, nomFichierTxt);

                    }
					if(recherche(lexico, mot) == 1)
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
					ajouteSuffixe(nomFichierCourant, ".DICO");
					lexico = NULL;
          ajouteMotsDepuisFichier(&lexico, nomFichierTxt);
					sauvegardeArbreDansFichier(lexico, nomFichierCourant);
					printf("L'arbre a bien été sauvegardé dans le ficher \"%s\".\n\n", nomFichierCourant);
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
