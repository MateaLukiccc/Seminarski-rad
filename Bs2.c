/*
** PROJEKAT : Seminarski rad iz predmeta P1
** DATOTEKA : Bs2.c
** OPIS     : Napisati program u programskom jeziku C koji
**            prikazuje upotrebu osnovnih operacije nad binarnim stablom(7/8)
** DATUM    : 13.07.2021
** AUTOR    : M.L
** PROMENE  :
**  xx.xx.xxxx. - <opis promene> (<programer>)
*/
#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<stdlib.h>


typedef struct cvor* PCVOR;

typedef struct cvor
{
	int podatak;
	struct cvor* levi;
	struct cvor *desni;
}CVOR;



void inorder(PCVOR koren)
{
	if (koren == NULL)
		return;
	inorder(koren->levi);
	printf("%d ", koren->podatak);
	inorder(koren->desni);
}


//pretrazuje element rekurzivno i vraca !NULL ukoliko je element pronadjen
PCVOR pretrazi(PCVOR koren, int broj)
{
	if (koren == NULL || koren->podatak == broj) 
		return koren;
	else if (broj > koren->podatak) 
		return pretrazi(koren->desni, broj);
	else 
		return pretrazi(koren->levi, broj);
}


//nalazi najdesniji element stabla koji je ujedno i najveci
int findmax(PCVOR koren)
{
	
	while (koren->desni != NULL)
		koren = koren->desni;
	printf("\nMaximum=%d", koren->podatak);

	return koren->podatak;
}



int findmin(PCVOR koren)
{
	
	while (koren->levi != NULL)
		koren = koren->levi;
	printf("\nMinimum=%d", koren->podatak);

	return koren->podatak;
}


//trazimo element koji je najleviji
PCVOR najmanjaVrednost(PCVOR koren)
{
	PCVOR tekuci = koren;

	
	while (tekuci!=NULL && tekuci->levi != NULL)
		tekuci = tekuci->levi;

	return tekuci;
}


//razlikuje 3 slucaja od kojih zavisi postupak raspodele elemenata u stablu!!!
PCVOR obrisi(PCVOR koren, int broj)
{
	
	if (koren == NULL)
		return koren;

	
	if (broj < koren->podatak)
		koren->levi = obrisi(koren->levi, broj);


	else if (broj > koren->podatak)
		koren->desni = obrisi(koren->desni, broj);

	
	else {
		
		if (koren->levi == NULL) {
			PCVOR pomocni = koren->desni;
			free(koren);
			return pomocni;
		}
		else if (koren->desni == NULL) {
			PCVOR pomocni = koren->levi;
			free(koren);
			return pomocni;
		}

		
		PCVOR pomocni = najmanjaVrednost(koren->desni);

		koren->podatak = pomocni->podatak;

		
		koren->desni = obrisi(koren->desni, pomocni->podatak);
	}
	return koren;
}



PCVOR ubacikoren(int podatak)
{
	struct cvor* novi = malloc(sizeof(struct cvor));
	novi->podatak = podatak;
	novi->levi = NULL;
	novi->desni = NULL;

	return novi;
}



PCVOR ubaci(PCVOR koren, int podatak)
{

	if (koren == NULL)
		return ubacikoren(podatak);

	if (koren->podatak < podatak)
		koren->desni = ubaci(koren->desni, podatak);

	else if (koren->podatak > podatak)
		koren->levi = ubaci(koren->levi, podatak);

	return koren;
}



int main()
{
	int a,min,max;
	PCVOR pomocni;
	PCVOR koren = NULL;
	

	do
	{
		printf("\n 1.Ubaci element u stablo\n 2.Pretrazi element\n 3.Obrisi element\n 4.Prikazi stablo\n 5.Nadji najmanji element\n 6.Nadji najveci element\n 0.Izadji iz programa\nVas izbor: ");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			
			printf("\nUnesite element\n");
			scanf("%d", &a);
			koren=ubaci(koren, a);
			
			break;

		case 2:

			if (koren == NULL) {
				printf("\nStablo je prazno\n");
			}
			else {
				printf("\nUnesite element koji zelite da pronadjete\n");

				scanf("%d", &a);

				if (koren->podatak == a)
					printf("\nElement postoji u stablu\n");
				else
				{
					pomocni = pretrazi(koren, a);
					if (pomocni == NULL)
						printf("\nElement ne postoji u stablu\n");
					else
						printf("\nTrazeni element je u stablu\n");
				}
			}
			break;
		case 3:
			if (koren == NULL) {
				printf("\nStablo je prazno\n");
			}
			else {
				printf("\nUnesite element koji zelite da se obrise\n");
				scanf("%d", &a);
				if (koren->podatak == a && koren->levi == NULL && koren->desni == NULL)
				{
					printf("\nElement je obrisan\n");
					free(koren);
					koren = NULL;
				}
				else {


					pomocni = pretrazi(koren, a);
					if (pomocni == NULL)
						printf("\nElement ne postoji u stablu\n");
					else
						koren = obrisi(koren, a);
				}
			}
			break;
		case 4:
			if (koren == NULL)
				printf("\nStablo je prazno\n");
			else{
			
					inorder(koren);
					
			}
			break;
		case 5:
			if (koren == NULL) {
				printf("\nStablo je prazno");
				break;
			}
			min=findmin(koren);
			break;
		case 6:
			if (koren == NULL) {
				printf("\nStablo je prazno");
				break;
			}
			max=findmax(koren);

			break;

		case 0:
			break;


		default:
			printf("\nUnesite odgovarajuci broj\n");
		}
	} while (a != 0);
}



