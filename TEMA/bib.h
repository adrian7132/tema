#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
    char* nume;
    char* prenume;
    int puncte;
};

struct Team {
    char* nume;
    int numarJucatori;
    struct Player* listaJucatori;
    int punctajEchipa;
    struct Team* next;
};

// Functie pentru adaugarea unui element la inceputul listei
void adaugaEchipa(struct Team** lista, char* numeEchipa, int numarJucatori, struct Player* listaJucatori, int punctajEchipa);

// Functie pentru eliberarea memoriei alocate pentru un jucator
void elibereazaJucator(struct Player* jucator);

// Functie pentru eliberarea memoriei alocate pentru o echipa
void elibereazaEchipa(struct Team* echipa);

// Functie pentru eliberarea memoriei pentru intreaga lista
void elibereazaLista(struct Team* lista);

// Functie pentru afisarea listei
void afiseazaLista(struct Team* lista);

// Functie pentru calculul punctajului de echipa
void calculeazaPunctajEchipa(struct Team* echipa);

// Functie pentru modificarea punctajelor jucatorilor dintr-o echipa
void modificaPunctajeJucatori(struct Team* echipa);

int numarEchipe(int nr_team);

// Functie pentru determinarea punctajului minim de echipa
int punctajMinimEchipa(struct Team* lista);

void stergereEchipa(struct Team** head, float v);

// Functie pentru eliminarea echipelor
void eliminaEchipe(struct Team** head, int* nr_team);
