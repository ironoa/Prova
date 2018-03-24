/*
 ============================================================================
 Name        : Strassen.c
 Author      : Alessio Onori
 Version     :
 Copyright   : Your copyright notice
 Description : Voglio provare ad implementare una semplice moltiplicazione tra 2
 matrici prefissate, e contare il numero di operazioni necessarie distinguendo tra
 addizioni e moltiplicazioni.
 La moltiplicazione è definita come Moltiplicazione tra matrici, quella semplice
 in cui si scorre la riga sulla prima matrice, si scorre la colonna sulla seconda.
 Non verranno fatti controlli in quanto è tutto prefissato da me. E' solo un esempio.
 Qui matrici quadrate nxn

 NOTA: per agire sulla dimensione n delle matrici quadrate bisogna agire
 sulla variabile DIM_MATRIX
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
//#include "Struttura_Matrix_Malloc2Livelli.c"
#define DIM_MATRIX 4

typedef struct{
	//larghezza e altezza
	int w;
	int h;
	//puntatore a puntatori agli elementi, in una struttura a doppia malloc
	//per ora lavoriamo con soli INTERI
	int **data;
	//questa struttura va allocata e gestita con metodi ad hoc

} matrix;

int main(void) {

	//definisco la prima matrice di interi e la alloco
	matrix *M1=allocSquareMatrix(DIM_MATRIX);
	//riempio banalmente
	int numero=0;
	int i=0;
	int j=0;
	for(i=0;i<DIM_MATRIX;i++)
		for(j=0;j<DIM_MATRIX;j++){
			(M1->data)[i][j]=numero;
			numero++;
		}


	//definisco la seconda matrice di interi e la riempio banalmente
	matrix *M2=allocSquareMatrix(DIM_MATRIX);
	for(i=0;i<DIM_MATRIX;i++)
		for(j=0;j<DIM_MATRIX;j++){
			(M2->data)[i][j]=numero;
			numero++;
		}



	//stampo
	printf("prima matrice:\n");
	printMatrix(M1);
	printf("\n");


	printf("seconda matrice:\n");
	printMatrix(M2);
	printf("\n");



	//eseguo il prodotto tra matrici fra le 2 matrici M1 * M2
	//alloco matrice risultato
	matrix *O=allocSquareMatrix(DIM_MATRIX);
	int nsum=0;
	int nmul=0;
	multiplyMatrix_naive(O,M1,M2,&nsum,&nmul);



	//stampo
	printf("prodotto tra matrici:\n");
	printMatrix(O);
	printf("\n");

	printf("numero somme: %d\n", nsum);
	printf("numero moltiplicazioni: %d", nmul);



	//dealloco tutto: M1,M2,O
	freeMatrix(M1);freeMatrix(M2);
	freeMatrix(O);


	return EXIT_SUCCESS;
}




