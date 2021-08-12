/*
** PROJEKAT : Seminarski rad iz predmeta P1
** DATOTEKA : Bs1.c
** OPIS     : Napisati program u programskom jeziku C koji
**            prikazuje upotrebu osnovnih operacije nad binarnim stablom pretrage(6/8)
** DATUM    : 13.07.2021
** AUTOR    : M.L
** PROMENE  :
**  xx.xx.xxxx. - <opis promene> (<programer>)
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef struct cvor* PCVOR;

struct cvor
{
    int podatak;
    struct cvor* levi;
    struct cvor* desni;
};


//ubacuje koren celog stabla ili podstabla
PCVOR ubacikoren(int podatak)
{
    struct cvor* novi = malloc(sizeof(struct cvor));
    novi->podatak = podatak;
    novi->levi = NULL;
    novi->desni = NULL;

    return novi;
}


//ubacuje novi element u stablo na odgovarajuce mesto
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


//prikazuje elemente sa leva na desno
void inorder(PCVOR koren)
{
    if (koren == NULL)
        return;
    inorder(koren->levi);
    printf("%d ", koren->podatak);
    inorder(koren->desni);
}


//cita brojeve iz datoteke i ubacuje ih u stablo
void ProcitajizDatoteke(PCVOR *koren) {

    FILE* datoteka = fopen("brojevi.txt", "r");
    
    char znak;
    int broj;


    if (datoteka == NULL) {
        printf("\ngreska pri otvaranju datoteke\n");
        return;
    }

    while (fscanf(datoteka,"%d",&broj)==1) {

        *koren=ubaci(*koren, broj);

    }




    fclose(datoteka);
}


//ispisuje brojeve u datoteku
void NapraviDatoteku() {

    FILE* datoteka = fopen("brojevi.txt", "w");

    char slovo = 'n';
    int broj;


    do {
        printf("\nUnesite brojeve u datoteku\n");
        scanf("%d", &broj);

        fprintf(datoteka, "%d ", broj);

        fprintf(stdout, "\nDa li zelite da unesete jos brojeva(y-da,n-ne)\n");

        scanf(" %c", &slovo);

    } while (slovo != 'n');


    fclose(datoteka);

}


//broji elemente u stablu
int BrojElemenata(PCVOR koren) {
    static int elementi=0;
    {
        if (koren == NULL)
            return;
        BrojElemenata(koren->levi);
        elementi++;
        BrojElemenata(koren->desni);
    }



    return elementi;
}



int meni() {

    int izbor;

    printf("\n\
====================\n\
      MENI\n\
====================\n\
1.Ubaci element u stablo\n\
2.Ispisi brojeve u datoteku\n\
3.Ubaci brojeve iz datoteke u listu\n\
4.Izbroj elemente u listi\n\
5.Prikazi stablo\n\
0.Izadji iz programa\n\
Vas izbor:");


    scanf("%d", &izbor);


    return izbor;

}



int main(){
    
    PCVOR koren = NULL;
    int ele;
    int izbor;
    int broj;


    do {

        izbor = meni();

        switch (izbor) {

        case 1:
            
            printf("\nKoji broj zelite da ubacite u stablo\n");
            scanf("%d", &broj);
            koren=ubaci(koren, broj);

            break;

        case 2:

            NapraviDatoteku();

            break;

        case 3:

            ProcitajizDatoteke(&koren);

            break;
        
        case 4:
            
            ele = BrojElemenata(koren);
            printf("\nU binarnom stablu postoji %d elemenata\n", ele);
            
           break;
        
        case 5:
            
            inorder(koren);
            break;

        case 0:
            break;

        default:
            printf("\nUnesite odgovarajuci broj\n");


        }



    } while (izbor != 0);


    return 0;
}