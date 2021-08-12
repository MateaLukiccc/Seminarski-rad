/*
** PROJEKAT : Seminarski rad iz predmeta P1
** DATOTEKA : jsloperacije2.c
** OPIS     : Napisati program u programskom jeziku C koji
**            prikazuje upotrebu osnovnih operacije nad jednostruko spregnutom listom(2/8)
** DATUM    : 11.07.2021
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

 

void DodajNaPocetak(PCVOR* glava, int broj) {
	PCVOR novi = malloc(sizeof(CVOR));
	novi->podatak = broj;
	novi->sledeci = NULL;


	if (*glava == NULL) {
		*glava = novi;
	}
	else {
		novi->sledeci = *glava;
		*glava = novi;
	}

}

void PrintujListu(PCVOR glava) {
	PCVOR tekuci = glava;
	while (tekuci != NULL) {
		printf("%d->", tekuci->podatak);
		tekuci = tekuci->sledeci;
	}
	printf("NULL\n");


}

//sortira listu rastuce,za rastuce sortiranje u 60.redu se < menja u >
PCVOR SortirajListu(PCVOR glava) {
	PCVOR i, j;
	int pom;

	for (i = glava; i != NULL; i = i->sledeci) {
		for (j = glava; j != NULL; j = j->sledeci) {
			if (i->podatak < j->podatak) {
				pom = i->podatak;
				i->podatak = j->podatak;
				j->podatak = pom;
			}
		}
	}

	return glava;
}

void DodajNaKraj(PCVOR *glava,int broj) {
	struct cvor* novielement = malloc(sizeof(CVOR));
	novielement->podatak = broj;
	novielement->sledeci = NULL;

	if (*glava == NULL) {
		*glava = novielement;
	}
	else {
		struct cvor* tekuci = *glava;
		while (tekuci->sledeci != NULL) {
			tekuci = tekuci->sledeci;
		}
		tekuci->sledeci = novielement;
	}
}

//nakon sortiranja liste nalazi odgovarajucu poziciju za ubacivanje elmenta
void SortiranoUbacivanje(PCVOR* glava,int broj) {
	PCVOR novi;
	PCVOR brzi;
	PCVOR spori;
	int signal;
	brzi = *glava;
	signal = 0;
	spori = NULL;
	while (brzi != NULL && signal == 0) {
		if (brzi->podatak > broj) signal = 1;
		else {
			spori = brzi;
			brzi = brzi->sledeci;
		}
	}
	if (signal == 0) { // Nije nadjena pozicija
		DodajNaKraj(glava, broj);
	}
	else { // Pozicija je nadjena
		novi = malloc(sizeof(CVOR));
		novi->podatak = broj;
		novi->sledeci = NULL;
		if (spori == NULL) {
			novi->sledeci = *glava;
			*glava = novi;
		}
		else {
			novi->sledeci = brzi;
			spori->sledeci = novi;
		}
	}
}

//prolazi kroz listu i trazi element i njegovu poziciju
void DaLiPostoji(PCVOR glava, int broj) {
	PCVOR tekuci = glava;
	int signal = 0;
	int pozicija = 1;
	while (tekuci != NULL&&signal==0) {
		if (tekuci->podatak == broj) {
			printf("\nPostoji broj %d u listi na %d. mestu\n", broj, pozicija);
			signal = 1;
		}
		pozicija++;
		tekuci = tekuci->sledeci;
	}

	if (signal == 0) {
		printf("\nBroj %d ne postoji u datoj listi\n", broj);
	}



}

//racuna aritmeticku sredinu liste
void AritmetickaSredina(PCVOR glava) {
	PCVOR tekuci = glava;
	int zbir = 0;
	int brelemenata = 0;

	while (tekuci != NULL) {
		zbir += tekuci->podatak;
		brelemenata++;
		tekuci = tekuci->sledeci;
	}


	printf("\nAritmeticka vrednost liste je %.2lf\n", (float)zbir/brelemenata);

}

//ispisuje listu u datoteku
void IspisUDatoteku(PCVOR glava) {

	FILE* datoteka = fopen("lista.txt","w");
	PCVOR tekuci = glava;
	while (tekuci != NULL) {
		fprintf(datoteka, "%d->", tekuci->podatak);
		tekuci = tekuci->sledeci;
	}

	fprintf(datoteka, "NULL");

	fclose(datoteka);
}


int meni() {
	int izbor;
	printf("\n\
================================\n\
          MENI                  \n\
================================\n\
1)Dodaj na pocetak liste\n\
2)Dodaj na kraj liste\n\
3)Sortiraj listu\n\
4)Ubaci sortirano(prethodno sortirati\n\
5)Da li postoji broj u listi\n\
6)Prikazi aritmeticku sredinu liste\n\
7)Prikazi listu\n\
8)Ispisi u datoteku\n\
0)Izadji iz menija\n\
Vas izbor: ");
	scanf("%d", &izbor);

	return izbor;

}




int main() {
	PCVOR glava = NULL;
	int izbor,broj;

	do {
		izbor = meni();

		switch (izbor) {
		case 1:
			printf("\nUnesite broj\n");
			scanf("%d", &broj);
			DodajNaPocetak(&glava,broj);
			break;
		case 2:
			printf("\nUnesite broj\n");
			scanf("%d", &broj);
			DodajNaKraj(&glava, broj);
			break;
		case 3:
			glava=SortirajListu(glava);
			break;
		case 4:
			printf("\nUnesite broj\n");
			scanf("%d", &broj);
			SortiranoUbacivanje(&glava, broj);
			break;
		case 5:
			printf("\nUnesite broj\n");
			scanf("%d", &broj);
			DaLiPostoji(glava, broj);
			break;
		case 6:
			AritmetickaSredina(glava);
			break;
		case 7:
			PrintujListu(glava);
			break;
		case 8:
			IspisUDatoteku(glava);
			break;
		case 0:
			break;
		default:
			printf("\nUnesite broj 0-8");
			break;
		}
	} while (izbor != 0);

		return 0;
}