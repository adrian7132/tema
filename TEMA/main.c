#include "bib.h"

int main() {
    FILE* fisier = fopen("d.in", "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        return 1;
    }

    int numarEchipe;
    fscanf(fisier, "%d", &numarEchipe);

    struct Team* listaEchipe = NULL;

    // Citirea datelor din fișier și crearea listei
    for (int i = 0; i < numarEchipe; i++) {
        int numarJucatori;
        char numeEchipa[100];
        fscanf(fisier, "%d %[^\n]s", &numarJucatori, numeEchipa);

        struct Player* listaJucatori = (struct Player*)malloc(numarJucatori * sizeof(struct Player));
        for (int j = 0; j < numarJucatori; j++) {
            char nume[100];
            char prenume[100];
            int puncte;
            fscanf(fisier, "%s %s %d", nume, prenume, &puncte);

            listaJucatori[j].nume = strdup(nume);
            listaJucatori[j].prenume = strdup(prenume);
            listaJucatori[j].puncte = puncte;
        }

        adaugaEchipa(&listaEchipe, numeEchipa, numarJucatori, listaJucatori, 0);
    }

    fclose(fisier);

    // Calcularea punctajelor și afișarea listei inițiale
    struct Team* echipaCurenta = listaEchipe;
    while (echipaCurenta != NULL) {
        calculeazaPunctajEchipa(echipaCurenta);
        echipaCurenta = echipaCurenta->next;
    }

    FILE* rezultat = fopen("r.out", "w");
    if (rezultat == NULL) {
        printf("Eroare la deschiderea fisierului de rezultate\n");
        return 1;
    }

    fprintf(rezultat, "Lista initiala:\n");
    struct Team* echipaCurenta2 = listaEchipe;
    while (echipaCurenta2 != NULL) {
        fprintf(rezultat, "%s\n", echipaCurenta2->nume);
        struct Player* jucator = echipaCurenta2->listaJucatori;
        for (int i = 0; i < echipaCurenta2->numarJucatori; i++) {
            fprintf(rezultat, "%s %s %d\n", jucator->nume, jucator->prenume, jucator->puncte);
            jucator++;
        }
        fprintf(rezultat, "Punctaj echipa: %d\n\n", echipaCurenta2->punctajEchipa);
        echipaCurenta2 = echipaCurenta2->next;
    }

    // Eliminarea echipelor descalificate
    eliminaEchipe(&listaEchipe, &numarEchipe);

    // Modificarea punctajelor jucătorilor și recalcularea punctajelor de echipă
    echipaCurenta = listaEchipe;
    while (echipaCurenta != NULL) {
        modificaPunctajeJucatori(echipaCurenta);
        calculeazaPunctajEchipa(echipaCurenta);
        echipaCurenta = echipaCurenta->next;
    }

    // Afișarea listei finale
    fprintf(rezultat, "Lista finala:\n");
    struct Team* echipaCurenta3 = listaEchipe;
    while (echipaCurenta3 != NULL) {
        fprintf(rezultat, "%s\n", echipaCurenta3->nume);
        struct Player* jucator = echipaCurenta3->listaJucatori;
        for (int i = 0; i < echipaCurenta3->numarJucatori; i++) {
            fprintf(rezultat, "%s %s %d\n", jucator->nume, jucator->prenume, jucator->puncte);
            jucator++;
        }
        fprintf(rezultat, "Punctaj echipa: %d\n\n", echipaCurenta3->punctajEchipa);
        echipaCurenta3 = echipaCurenta3->next;
    }

    fclose(rezultat);

    // Eliberarea memoriei alocate pentru lista și jucători
    elibereazaLista(listaEchipe);

    return 0;
}
