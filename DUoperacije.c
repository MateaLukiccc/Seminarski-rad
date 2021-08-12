/*
** PROJEKAT : Seminarski rad iz predmeta P1
** DATOTEKA : DUoperacije.c
** OPIS     : Napisati program u programskom jeziku C koji
**            prikazuje upotrebu osnovnih operacije nad dvostruko spregnutom listom(3/8)
** DATUM    : 13.07.2021
** AUTOR    : M.L
** PROMENE  :
**  xx.xx.xxxx. - <opis promene> (<programer>)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct cvor* PCVOR;


typedef struct cvor
{
    struct cvor* prethodni;
    int podatak;
    struct cvor* sledeci;
}CVOR;


//ubacuje novi element na pocetak menjanjem pokazivaca prvog elementa i novododatog
void ubacinapocetak(struct cvor** glava, int podatak) {

    struct cvor* novielement = malloc(sizeof(CVOR));

    novielement->podatak = podatak;
    novielement->sledeci = *glava;
    novielement->prethodni = NULL;

    if (*glava != NULL)
        (*glava)->prethodni = novielement;

    *glava = novielement;
}


//isti metod kao kod 1UL
void Printujlistu(PCVOR glava) {
    PCVOR tekuci = glava;

    while (tekuci != NULL) {
        printf("%d->", tekuci->podatak);
        tekuci = tekuci->sledeci;
    }
    printf("NULL\n");


}


//koriscenjem pokazivaca na prethodni element
void printujunazad(PCVOR glava) {
    PCVOR tekuci = glava;

    printf("NULL");
    while (tekuci->sledeci != NULL) {
        tekuci = tekuci->sledeci;
    }

    while (tekuci != NULL) {

        printf("<-%d", tekuci->podatak);
        tekuci = tekuci->prethodni;

    }
    printf("\n");



}


//slican metod kao print unazad, prolazi se do kraja liste gde se menjaju pokazivaci
void dodajNaKraj(struct cvor** glava, int podatak) {

    struct cvor* novi = malloc(sizeof(CVOR));

    struct cvor* tekuci = *glava;

    novi->podatak = podatak;

    novi->sledeci = NULL;


    if (*glava == NULL) {
        novi->prethodni = NULL;
        *glava = novi;
        return;
    }

    while (tekuci->sledeci != NULL)
        tekuci = tekuci->sledeci;

    tekuci->sledeci = novi;
    novi->prethodni = tekuci;

}


//razlikujemo 3 slucaja i vracamo izbaceni broj(ili element ako tip nije int)
int uklonisapocetka(PCVOR* glava) {
    PCVOR tekuci = *glava;
   
    if (*glava == NULL) {
        return;
    }
    int izbaceni = tekuci->podatak;
    if ((*glava)->sledeci == NULL) {
        *glava = NULL;
        free(tekuci);
        return izbaceni;
    }

    *glava = (*glava)->sledeci;
    (*glava)->prethodni = NULL;

    free(tekuci);
    return izbaceni;
}


//slicno kao sa pocetka opet imamo 3 slucaja
int uklonisakraja(PCVOR*glava) {
    int uklonjen;
    PCVOR tekuci = *glava;

    if (*glava == NULL) {
        return;
    }
    else if ((*glava)->sledeci == NULL) {
        *glava = NULL;
        uklonjen = tekuci->podatak;
        free(tekuci);
        return uklonjen;
    }

    while (tekuci->sledeci != NULL) {
        tekuci = tekuci->sledeci;
    }
    uklonjen = tekuci->podatak;
    tekuci->prethodni->sledeci = NULL;
    free(tekuci);

    return uklonjen;
}


int meni() {
    int izbor;

    printf("\n\
================================\n\
             MENI\n\
================================\n\
1)Ubaci element na pocetak liste\n\
2)Ubaci element na kraj liste\n\
3)Ispisi listu\n\
4)Ispisi listu unazad\n\
5)Ukloni element sa pocetka\n\
6)Ukloni element sa kraja\n\
Vas izbor:");
    scanf("%d", &izbor);




    return izbor;
}




int main() {

    PCVOR glava = NULL;
    int izbor,element;


    do {
        izbor = meni();

        switch (izbor) {
        case 1:
            printf("\nUnesite element\n");
            scanf("%d", &element);
            ubacinapocetak(&glava, element);
            break;
        case 2:
            printf("\nUnesite element\n");
            scanf("%d", &element);
            dodajNaKraj(&glava, element);
            break;
        case 3:
            Printujlistu(glava);
            break;
        case 4:
            printujunazad(glava);
            break;
        case 5:
            uklonisapocetka(&glava);
            break;
        case 6:
            uklonisakraja(&glava);
            break;
        case 0:
            break;
        default:
            printf("Unesite odgovarajuci broj");
        }



    } while (izbor != 0);



    return 0;
}