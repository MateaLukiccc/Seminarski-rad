/*
** PROJEKAT : Seminarski rad iz predmeta P1
** DATOTEKA : DUoperacije2.c
** OPIS     : Napisati program u programskom jeziku C koji
**            prikazuje upotrebu osnovnih operacije nad dvostruko spregnutom listom(4/8)
** DATUM    : 13.07.2021
** AUTOR    : M.L
** PROMENE  :
**  xx.xx.xxxx. - <opis promene> (<programer>)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>


typedef struct cvor* PCVOR;


typedef struct cvor
{
    struct cvor* prethodni;
    int podatak;
    struct cvor* sledeci;
}CVOR;

typedef int mat[3][3];



void ubacinapocetak(struct cvor** glava, int podatak) {

    struct cvor* novielement = malloc(sizeof(CVOR));

    novielement->podatak = podatak;
    novielement->sledeci = *glava;
    novielement->prethodni = NULL;

    if (*glava != NULL)
        (*glava)->prethodni = novielement;

    *glava = novielement;

}



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



void Printujlistu(PCVOR glava) {

    PCVOR tekuci = glava;

    while (tekuci != NULL) {

        printf("%d->", tekuci->podatak);
        tekuci = tekuci->sledeci;

    }
    printf("NULL\n");


}


//prolazimo kroz matricvu i svaki element jedan po jedan ubacujemo u listu
void izmatriceulistu(mat mat, PCVOR* glava,int dim) {

    for (int i = 0; i < dim; i++) {

        for (int j = 0; j < dim; j++) {
        
            ubacinapocetak(glava, mat[i][j]);
        
        }
    }


}


//ispis matrice
void printujmatricu(mat mat, int dim) {

    for (int i = 0; i < dim; i++) {
    
        for (int j = 0; j < dim; j++) {
        
            printf("%4d", mat[i][j]);
        
        }
        
        printf("\n");
    }


}


//unosimo dimenziju i elemente kvadratne matrice, ukoliko matrica nije kvadratna menjamo promenljivo dim, petlje i saljemo dodatnu promenljivu u funkcije
void unesimatricu(PCVOR*glava) {

    int dim;

    mat mat;
    printf("\nUnesi dimenziju kvadratne matrice\n");
    scanf("%d", &dim);

    printf("\nUnesite elemente\n");

    for (int i = 0; i < dim; i++) {

        for (int j = 0; j < dim; j++) {

            scanf("%d", &mat[i][j]);

        }
    }

    printf("\nUneta matrica je:\n");
    printujmatricu(mat, dim);
    izmatriceulistu(mat, glava, dim);

}



PCVOR sort(PCVOR glava) {

    PCVOR i,j ;
    int pom;

    for (i = glava; i != NULL; i = i->sledeci) {
        for (j = glava; j != NULL; j = j->sledeci) {
            if (i->podatak > j->podatak) {
                pom = i->podatak;
                i->podatak = j->podatak;
                j->podatak = pom;
            }
        }
    }

    return glava;
}



int meni() {
    int izbor;

    printf("\n\
====================\n\
       MENI\n\
====================\n\
1.Ubaci novi element na pocetak\n\
2.Ubaci novi element na kraj\n\
3.Unesi matricu i prebaci u listu njene elemente\n\
4.Prikazi listu\n\
5.sortiraj listu\n\
0.Izadji iz programa\n\
Vas izbor je: ");

    scanf("%d", &izbor);



    return izbor;
}

int main() {
    PCVOR glava = NULL;
   
    int izbor;
    int broj;

    do {

        izbor = meni();

        switch (izbor) {
        case 1:
            printf("\nUnesite element koji zelite da unesete u listu: \n");
            scanf("%d", &broj);
            printf("\n");
            ubacinapocetak(&glava, broj);
            break;
        case 2:
            printf("\nUnesite element koji zelite da unesete u listu: \n");
            scanf("%d", &broj);
            printf("\n");
            dodajNaKraj(&glava, broj);
            break;
        case 3:
            unesimatricu(&glava);
            break;
        case 4:
            Printujlistu(glava);
            break;
        case 5:
            sort(glava);
            break;
        case 0:
            break;
        default:
            printf("\nUnesite odgovarajuci broj: ");


        }



    } while (izbor != 0);




	return 0;
}


