#include "bib.h"

// Functie pentru adaugarea unui element la inceputul listei
void adaugaEchipa(struct Team** lista, char* numeEchipa, int numarJucatori, struct Player* listaJucatori, int punctajEchipa) {
    struct Team* nouaEchipa = (struct Team*)malloc(sizeof(struct Team));
    nouaEchipa->nume = strdup(numeEchipa);
    nouaEchipa->numarJucatori = numarJucatori;
    nouaEchipa->listaJucatori = listaJucatori;
    nouaEchipa->punctajEchipa = punctajEchipa;
    nouaEchipa->next = *lista;
    *lista = nouaEchipa;
}

// Functie pentru eliberarea memoriei alocate pentru un jucator
void elibereazaJucator(struct Player* jucator) {
    free(jucator->nume);
    free(jucator->prenume);
}

// Functie pentru eliberarea memoriei alocate pentru o echipa
void elibereazaEchipa(struct Team* echipa) {
    struct Player* jucator = echipa->listaJucatori;
    for (int i = 0; i < echipa->numarJucatori; i++) {
        elibereazaJucator(&jucator[i]);
    }
    free(echipa->listaJucatori);
    free(echipa->nume);
    free(echipa);
}

// Functie pentru eliberarea memoriei pentru intreaga lista
void elibereazaLista(struct Team* lista) {
    while (lista != NULL) {
        struct Team* echipaCurenta = lista;
        lista = lista->next;
        elibereazaEchipa(echipaCurenta);
    }
}

// Functie pentru afisarea listei
void afiseazaLista(struct Team* lista) {
    struct Team* echipa = lista;
    while (echipa != NULL) {
        printf("%s\n", echipa->nume);
        struct Player* jucator = echipa->listaJucatori;
        for (int i = 0; i < echipa->numarJucatori; i++) {
            printf("%s %s %d\n", jucator->nume, jucator->prenume, jucator->puncte);
            jucator++;
        }
        printf("Punctaj echipa: %d\n\n", echipa->punctajEchipa);
        echipa = echipa->next;
    }
}

// Functie pentru calculul punctajului de echipa
void calculeazaPunctajEchipa(struct Team* echipa) {
    int sumaPuncte = 0;
    struct Player* jucator = echipa->listaJucatori;
    for (int i = 0; i < echipa->numarJucatori; i++) {
        sumaPuncte += jucator->puncte;
        jucator++;
    }
    echipa->punctajEchipa = sumaPuncte / echipa->numarJucatori;
}

// Functie pentru modificarea punctajelor jucatorilor dintr-o echipa
void modificaPunctajeJucatori(struct Team* echipa) {
    struct Player* jucator = echipa->listaJucatori;
    for (int i = 0; i < echipa->numarJucatori; i++) {
        jucator->puncte++;
        jucator++;
    }
}

int numarEchipe(int nr_team)
{
    int semn = 1,nr = 1;
    while(semn == 1)
    {
        nr = nr*2;
        if(nr>nr_team)
            semn = 0;
    }
    return nr/2;
}
// Functie pentru determinarea punctajului minim de echipa
int punctajMinimEchipa(struct Team* lista) {
    int punctajMinim = lista->punctajEchipa;
    struct Team* echipaCurenta = lista->next;

    while (echipaCurenta != NULL) {
        if (echipaCurenta->punctajEchipa < punctajMinim) {
            punctajMinim = echipaCurenta->punctajEchipa;
        }
        echipaCurenta = echipaCurenta->next;
    }

    return punctajMinim;
}
void stergereEchipa(struct Team** head, float v)
{
    if(*head == NULL)
        return;
    struct Team* headcopy = *head;
    if(headcopy->punctajEchipa == v)
    {
        *head = (*head)->next;
        free(headcopy);
        return;
    }
    struct Team *prev = *head;
    while(headcopy != NULL)
    {
        if(headcopy->punctajEchipa != v)
        {
            prev = headcopy;
            headcopy = headcopy->next;
        }
        else
        {
            prev->next = headcopy->next;
            elibereazaEchipa(headcopy);
            return;
        }
    }
}

// Functie pentru eliminarea echipelor
void eliminaEchipe(struct Team** head, int* nr_team) {
    int nr = numarEchipe(*nr_team);
    struct Team* prev = NULL;
    while (nr != (*nr_team)) {
        float p_min = punctajMinimEchipa(*head);
        stergereEchipa(head, p_min);
        (*nr_team)--;
    }
}

