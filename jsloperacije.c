/*
** PROJEKAT : Seminarski rad iz predmeta P1
** DATOTEKA : jsloperacije.c
** OPIS     : Napisati program u programskom jeziku C koji
**            prikazuje upotrebu osnovnih operacije nad jednostruko spregnutom listom(1/8)
** DATUM    : 11.07.2021
** AUTOR    : M.L
** PROMENE  :
**  xx.xx.xxxx. - <opis promene> (<programer>)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct cvor* PCVOR;

typedef struct cvor {
	int podatak;
	PCVOR sledeci;
}CVOR;

//dodaje novi element na pocetak liste
void dodajNaPocetak(PCVOR* glava,int broj) {
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
//prikazuje listu
void PrintujListu(PCVOR glava) {
	PCVOR tekuci = glava;
	while (tekuci != NULL) {
		printf("%d->", tekuci->podatak);
		tekuci = tekuci->sledeci;
	}
	printf("NULL");


}

//sa dodatnom funkcijom
void ReverseList(PCVOR* glava) {                                  
	PCVOR novaglava = NULL;
	if (*glava == NULL||(*glava)->sledeci==NULL) {
		return;
	}
	else {
		PCVOR tekuci = *glava;
		while (tekuci != NULL) {
			dodajNaPocetak(&novaglava, tekuci->podatak);
			tekuci = tekuci->sledeci;
		}
		*glava = novaglava;
	}
}
//bez dodatne funkcije
void reverse(PCVOR* glava){
	PCVOR prethodni = NULL;
	PCVOR tekuci = *glava;
	PCVOR sledeci = NULL;
	while (tekuci != NULL) {
		sledeci = tekuci->sledeci;
		tekuci->sledeci = prethodni;
		prethodni = tekuci;
		tekuci = sledeci;
	}
	*glava = prethodni;
}

//dodaje novi element na kraj liste
void dodajNaKraj(PCVOR* glava,int broj) {
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

//vraca izbaceni element
int izbaciSaPocetka(struct cvor** glava) {

	struct cvor* obrisani = *glava;
	int obrisanbroj;
	if (*glava == NULL) {
		return 1;
	}
	obrisanbroj = obrisani->podatak;
	*glava = (*glava)->sledeci;
	free(obrisani);
	return obrisanbroj;
}

//vraca izbaceni element
int izbaciSaKraja(PCVOR* glava) {
	int broj; //broj koji ce se obrisati
	PCVOR brzi, spori;
	brzi = *glava;
	spori = NULL;
	while (brzi->sledeci != NULL) {
		spori = brzi;
		brzi = brzi->sledeci;
	}
	if (spori == NULL) {
		broj = brzi->podatak;
		free(brzi);
		*glava = NULL;
	}
	else {
		broj = brzi->podatak;
		free(brzi);
		spori->sledeci = NULL;
	}
	return broj;
}

//brise listu
void obrisiListu(PCVOR*glava)
{
	struct cvor* brzi = *glava;
	struct cvor* spori;
	while (brzi != NULL) {
		spori = brzi;
		brzi = brzi->sledeci;
		free(spori);
	}
	*glava = NULL;
}


int meni() {
	int izbor;

	printf("\n\
=================================================\n\
                MENI                             \n\
=================================================\n\
1.Ubaci u listu\n\
2.Izbaci iz liste\n\
3.Unisti listu\n\
4.Invertuj listu\n\
5.Prikazi listu\n\
0.Izadji iz programa\n\
Vas izbor:");
	scanf("%d", &izbor);

	return izbor;
}


int main() {
	PCVOR glava = NULL;
	int izbor;
	int izbor2;
	int broj;
	do {
		izbor = meni();
		switch (izbor) {
		case 1:
			printf("\n\
1.Ubaci na pocetak\n\
2.Ubaci na kraj\n\
vas izbor:");
			scanf("%d", &izbor2);
			if (izbor2 == 1) {
				printf("\nKoji broj zelite da ubacite na pocetak liste\n");
				scanf("%d", &broj);
				dodajNaPocetak(&glava, broj);
			}
			else if (izbor2 == 2) {
				printf("\nKoji broj zelite da ubacite na kraj liste\n");
				scanf("%d", &broj);
				dodajNaKraj(&glava, broj);
			}
			else {
				printf("\nUneli ste pogresnu vrednost\n");
			}

			
			break;
		case 2:
			printf("\n\
1.Izbaci sa pocetka\n\
2.Izbaci sa kraja\n\
vas izbor:");
			scanf("%d", &izbor2);
			if (izbor2 == 1) {
				izbaciSaPocetka(&glava);
			}
			else if (izbor2 == 2) {
				
				izbaciSaKraja(&glava);
			}
			else {
				printf("\nUneli ste pogresnu vrednost\n");
			}


			break;
		case 3:
			obrisiListu(&glava);
			break;
		case 4:
			reverse(&glava);
			break;
		case 5:
			PrintujListu(glava);
			break;
		case 0:
			break;
		default:
			printf("\nUnesite odgovarajucu vrednost\n\n");
			break;
		}
	} while (izbor != 0);

	return 0;
}
