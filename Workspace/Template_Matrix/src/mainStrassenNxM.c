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
 sulla variabile DIM_MATRIX nell'header file matrix.h
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


int main(void) {

	//definisco la prima matrice di interi e la alloco
	matrix *M1=allocMatrix(32,31);

	//riempio banalmente
	int numero=0;
	int i=0;
	int j=0;
	for(i=0;i<M1->h;i++)
		for(j=0;j<M1->w;j++){
			(M1->data)[i][j]=numero;
			numero++;
		}


	//definisco la seconda matrice di interi e la riempio banalmente
	matrix *M2=allocMatrix(31,32);
	for(i=0;i<M2->h;i++)
		for(j=0;j<M2->w;j++){
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
	int nsum=0;
	int nmul=0;
	matrix *O = multiplyMatrix_naive(M1,M2,&nsum,&nmul);





	//stampo
	printf("prodotto tra matrici:\n");
	printMatrix(O);
	printf("\n");

	printf("numero somme: %d\n", nsum);
	printf("numero moltiplicazioni: %d", nmul);

	//conservo per dopo confronto
	int ns=nsum;
	int nm=nmul;





	printf("\n\n*********** STRASSEN ******************** \n\n");
	nsum=0;
	nmul=0;
	matrix *OUT=multiplyMatrix_strassen(M1,M2,&nsum,&nmul);

	//stampo
	printf("prodotto tra matrici con strassen:\n");
	printMatrix(OUT);
	printf("\n");

	printf("numero somme: %d\n", nsum);
	printf("numero moltiplicazioni: %d\n", nmul);

	printf("IN CONFRONTO A:\n");
	printf("numero somme: %d\n", ns);
	printf("numero moltiplicazioni: %d\n", nm);

	//dealloco tutto: M1,M2,O,OUT
	freeMatrix(M1);freeMatrix(M2);
	freeMatrix(O);freeMatrix(OUT);


	return EXIT_SUCCESS;
}




