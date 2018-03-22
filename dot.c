#include "dot.h"

void makedot (Arbre a, char nomFichier[]) {

    FILE *out;
    out=fopen(nomFichier,"w"); /* suppose OK*/
    ecrireDebut(out);
    ecrireTarbre(out, a);
    ecrireFin(out);
    fclose(out);

}

void ecrireDebut(FILE* stream) {
    fprintf(stream, "digraph arbre {\n  node [shape=record, height=.1];\n");
    fprintf(stream, "edge [tailclip=false, arrowtail=dot, dir=both];\n\n");
}

void ecrireFin(FILE* stream) {
    fprintf(stream, "\n}\n");
}

void ecrireTarbre(FILE* stream, Arbre a){

    if (a != NULL){

        if (a->lettre == '\0') fprintf(stream, "n%p [label=\"<gauche> | /0 | <droit>\"];\n", a);
        else fprintf(stream, "n%p [label=\"<gauche> | %c | <droit>\"];\n", a, a->lettre);

        if (a->frered){
            fprintf(stream, "n%p:droit:c -> n%p[color=blue];\n", a, a->frered);
            ecrireTarbre(stream, a->frered);
        }
        if (a->filsg){
            fprintf(stream, "n%p:s -> n%p [color=blue];\n", a, a->filsg);
            ecrireTarbre(stream, a->filsg);
        }
    }
}
