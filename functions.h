#ifndef FG_FrD
#define FG_FrD

typedef strut noeud {
    unsigned char lettre;
    strut noeud *filsg, *frered;
} Noeud, *Arbre;

#endif FG_FrD

Arbre alloueNoeud(char lettre);

void ajouteMot (Arbre *a, char *mot);

void afficheLexique (Arbre a);

void sauvegardeMots (Arbre a, FILE *out);

int recherche (Arbre a, char *mot);

void sauvegardeArbre (Arbre a , FILE *out);
