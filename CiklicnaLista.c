/*
** PROJEKAT : Seminarski rad iz predmeta P1
** DATOTEKA : CiklicnaLista.c
** OPIS     : Napisati program u programskom jeziku C koji
**            prikazuje upotrebu osnovnih operacije nad ciklicnom listom oblika 1UL(5/8)
** DATUM    : 13.07.2021
** AUTOR    : M.L
** PROMENE  :
**  xx.xx.xxxx. - <opis promene> (<programer>)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct cvor* PCVOR;

typedef struct cvor {
	int podatak;
	PCVOR sledeci;
}CVOR;


//ako lista nije prazna menja se pokazivac poslednjeg elementa dok pokazivac dodatog ostaje glava
void dodajelementnakraj(PCVOR*glava,int broj) {
	PCVOR novielement = malloc(sizeof(CVOR));
	novielement->sledeci = *glava;
	novielement->podatak = broj;

	if (*glava == NULL) {
		*glava = novielement;
		novielement->sledeci = *glava;
		return;
	}

	PCVOR tekuci = (*glava)->sledeci;
	while (tekuci->sledeci != *glava) {
		tekuci = tekuci->sledeci;
	}

	tekuci->sledeci = novielement;


}


//prolazi se kroz listu dok se ne dodje ponovo do pocetnog elementa
void printujlistu(PCVOR glava) {

	PCVOR tekuci = glava;
	
	if (tekuci != NULL) {

		do {
			printf("%d->", tekuci->podatak);
			tekuci = tekuci->sledeci;

		} while (tekuci != glava);
		printf("NULL");
	}

	else {
		printf("\nlista je prazna\n");
	}

}


//pronalazi se poslednji element ciji se pokazivac podesava dok se prvi element pomera na drugo mesto
void dodajnapocetak(PCVOR* glava, int broj) {
	PCVOR novielement = malloc(sizeof(CVOR));
	novielement->podatak = broj;
	novielement->sledeci = *glava;

	if (*glava == NULL) {
		*glava = novielement;
		novielement->sledeci = *glava;
		return;
	}

	PCVOR tekuci = (*glava)->sledeci;
	while (tekuci->sledeci != *glava) {
		tekuci = tekuci->sledeci;
	}
	*glava = novielement;
	tekuci->sledeci = novielement;
	
}


//pomeraju se pokazivaci i oslobadja se element naredbom free
int izbaciSaPocetka(PCVOR* glava) {
	PCVOR tekuci = *glava;
	
	int izbaceni = tekuci->podatak;
	if (*glava == NULL) {
		printf("\nLista je prazna\n");
		return;
	}
	if ((*glava)->sledeci == *glava) {
		*glava = NULL;
		free(tekuci);
		return izbaceni;
	}
	PCVOR poslednji = *glava;
	while (poslednji->sledeci != *glava) {
		poslednji = poslednji->sledeci;
	}
	poslednji->sledeci = tekuci->sledeci;

	*glava = tekuci->sledeci;
	free(tekuci);



	return izbaceni;
}


//podeljena je u 3 slucaja kada je prazna ima 1 element ili vise 
int izbaciSaKraja(PCVOR* glava) {

	if (*glava == NULL) {
		printf("\nLista je prazna\n");
		return;
	}
	else if ((*glava)->sledeci == *glava) {
		PCVOR tekuci = *glava;
		int izbaceni = tekuci->podatak;
		*glava = NULL;
		free(tekuci);
		return izbaceni;
	}
	PCVOR tekuci = *glava;
	int izbaceni = tekuci->podatak;
	PCVOR poslednji = *glava;

	while (poslednji->sledeci->sledeci != *glava) {
		poslednji = poslednji->sledeci;
	}
	tekuci = poslednji->sledeci;
	izbaceni = tekuci->podatak;
	poslednji->sledeci = *glava;
	free(tekuci);
	return izbaceni;
}


//isto 3 slucaja od kojih zavisi postupak
void unistiListu(PCVOR* glava) {


	if (*glava == NULL) {
		printf("lista je prazna");
		return;
	}
	else if(*glava==(*glava)->sledeci){
		PCVOR tekuci = *glava;
		*glava = NULL;
		free(tekuci);
		return;
	}


	PCVOR tekuci = (*glava)->sledeci;
	PCVOR spori = NULL;
	while (tekuci != *glava) {
		spori = tekuci;
		tekuci = tekuci->sledeci;
		free(spori);
		tekuci = *glava;
	}

	*glava = NULL;

}


int meni() {
	int izbor;

	printf("\n\
=========================\n\
           MENI\n\
=========================\n\
1.Ubaci element na pocetak liste\n\
2.Ubaci element na kraj liste\n\
3.Izbaci sa kraja liste\n\
4.Izbaci sa pocetka liste\n\
5.Unisti listu\n\
6.Prikazi listu\n\
0.Izadji\n\
Vas izbor: ");
	scanf("%d", &izbor);

	return izbor;
}


int main(){
	PCVOR glava = NULL;
	int izbor;
	int broj;
	do {
		izbor = meni();

		switch (izbor) {
		case 1:
			
			printf("\nUnesite broj koji zelite da ubacite u listu\n");
			scanf("%d", &broj);
			dodajnapocetak(&glava, broj);
			break;
		case 2:
			printf("\nUnesite broj koji zelite da ubacite u listu\n");
			scanf("%d", &broj);
			dodajelementnakraj(&glava, broj);
			break;
		case 3:
			izbaciSaKraja(&glava);
			break;
		case 4:
			izbaciSaPocetka(&glava);
			break;
		case 5:
			unistiListu(&glava);
			break;
		case 6:
			printujlistu(glava);
			break;
		case 0:
			break;
		default:
			printf("\nUnesite odgovarajuci broj\n");
		}


	} while (izbor != 0);

	

	return 0;
}