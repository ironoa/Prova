/*
 ============================================================================
 Name        : Template_DataStructure.c
 Author      : Alessio
 Version     :
 Copyright   : Your copyright notice
 Description : STRUTTURA DATI allocata con MALLOC a 2 livelli, DINAMICA. Esempio di MATRICE

 NOTA: la struttura è composta da 2 campi più un terzo gestito a malloc... la gestione deve essere tutta a malloc
 dunque, per una uniformità di gestione: potrebbe venire voglia di gestire a malloc solo il campo data, funzionerebbe,
 ma sarebbe concettualmente scorretto
 ============================================================================
 */

#include <stdlib.h> //malloc e co
#include <stdio.h>//fondamentale di sicuro
#include <limits.h>//contiene per esempio INT_MAX e INT_MIN

typedef struct{
	//larghezza e altezza
	int w;
	int h;
	//puntatore a puntatori agli elementi, in una struttura a doppia malloc
	//per ora lavoriamo con soli INTERI
	int **data;
	//questa struttura va allocata e gestita con metodi ad hoc

} matrix;


matrix * allocMatrix(int h, int w){
	matrix *m = malloc ( sizeof(matrix) );
	m->h=h;
	m->w=w;

	m->data=(int**) malloc( (m->h)*sizeof(int*) );
	int i;
	for(i=0;i<(m->h);i++){
		(m->data)[i]=(int*) malloc( (m->w)*sizeof(int) );
	}

	return m;
}

matrix* allocSquareMatrix(int dim){
	return allocMatrix(dim,dim);
}


/*
 * ricordiamo che ogni allocazione richiederà prima o poi un de allocazione
 *
 */
//giustamente metodo per deallocare
void freeMatrix(matrix *m){
	//dealloco prima il livello piu profondo
	int i;
	for(i=0;i<(m->h);i++){
		free( (m->data)[i] );
	}
	//poi il primo livello
	free(m->data);
	//poi la struttura intera
	free(m);
}



void reallocMatrix(matrix *m){
	int h = m->h;
	int w = m->w;

	if(m){
		freeMatrix(m);
	}

	allocMatrix(h,w);
}


void initMatrix(matrix *m){
	//dealloco solo il livello piu profondo
	int i;
	for(i=0;i<(m->h);i++){
		free( (m->data)[i] );
	}

	//agisco sui soli elementi puntati di secondo livello
	for(i=0;i<(m->h);i++){//per ogni riga
		(m->data)[i]=(int*) calloc( (m->w),sizeof(int) );
	}
}




/*
 * con questo tipo di struttura la gestione diventa semplicissima,
 * a puntatori come se fossero array
 */
void printMatrix(matrix *m){
	int r,c;
	for(r=0;r<(m->h);r++){//scorro righe
		for(c=0;c<(m->w);c++){//scorro colonne
			printf("%d | ", (m->data)[r][c] );
		}
		printf("\n");
	}
	printf("\n");
}


matrix* multiplyMatrix_naive(matrix *m1, matrix *m2,int *nsum, int *nmul){

	matrix *result = allocMatrix(m1->h,m2->w);

	//scorro le colonne di M2, il ciclo più esterno
	int k;
	for(k=0;k<m2->w;k++){
		//scorro le righe di M1
		int i;
		for(i=0;i<m1->h;i++){
			int sum=0;
			//scorro le colonne di M1
			int j;
			for(j=0;j< m1->w ;j++){
				//eseguo prodotto
				//nota come sia il puntatore j l'unico a scorrere
				sum+= (m1->data)[i][j] * (m2->data)[j][k] ;

				//conto
				(*nmul)++;
				if(j!=0) //la prima è una somma con lo zero, non si conta
					(*nsum)++;
			}//j
			//finite le colonne su M1 aggiorno la matrice risultato
			(result->data)[i][k]=sum;
		}//i
	}//k

	return result;
}



void sumMatrix(matrix *result,matrix *m1, matrix *m2, int *nsum, int *nmul){

	//scorro le righe di M1
	int i;
	for(i=0;i< m1->h;i++){
		//scorro le colonne di M1
		int j;
		for(j=0;j< m1->w;j++){
			//eseguo somma
			(result->data)[i][j]=(m1->data)[i][j]+(m2->data)[i][j];

			//conto
			(*nsum)++;
		}//j
	}//i
}

//sottrazione
void subMatrix(matrix *result,matrix *m1, matrix *m2, int *nsum, int *nmul){

	int i;
	//scorro le righe di M1
	for(i=0;i< m1->h;i++){
		//scorro le colonne di M1
		int j;
		for(j=0;j< m1->w;j++){
			//eseguo somma
			(result->data)[i][j]=(m1->data)[i][j]-(m2->data)[i][j];

			//conto
			(*nsum)++;
		}//j
	}//i
}


matrix* sumMatrix2(matrix *m1, matrix *m2, int *nsum, int *nmul){

	//controllo sulle dimensioni avvenuto all'esterno, m1 e m2 compatibili = stesse dimensioni
	matrix *result = allocMatrix(m1->h,m1->w);

	//scorro le righe di M1
	int i;
	for(i=0;i< m1->h;i++){
		//scorro le colonne di M1
		int j;
		for(j=0;j< m1->w;j++){
			//eseguo somma
			(result->data)[i][j]=(m1->data)[i][j]+(m2->data)[i][j];

			//conto
			(*nsum)++;
		}//j
	}//i

	return result;
}

//sottrazione
matrix* subMatrix2(matrix *m1, matrix *m2, int *nsum, int *nmul){

	//controllo sulle dimensioni avvenuto all'esterno, m1 e m2 compatibili = stesse dimensioni
	matrix *result = allocMatrix(m1->h,m1->w);

	int i;
	//scorro le righe di M1
	for(i=0;i< m1->h;i++){
		//scorro le colonne di M1
		int j;
		for(j=0;j< m1->w;j++){
			//eseguo somma
			(result->data)[i][j]=(m1->data)[i][j]-(m2->data)[i][j];

			//conto
			(*nsum)++;
		}//j
	}//i

	return result;
}


/*
 * SOURCE >> DEST
 * popolo per copia una matrice dest con un sottoinsieme degli elementi di una matrice source
 * PRE: dimensioni di dest entrambe minori delle dimensioni di source
 * Copia che procede in maniera ordinata ovviamente
 * previsti parametri di offset da cui considerare gli elementi di source: i controlli di
 * overflow devono essere fatti esternamente
 */
void copySubMatrix(matrix *source, matrix *dest, int offsetH, int offsetW){
	int i,j,h,k;
	/*
	 * per entrambi i for: la prima condizione è fondamentale per non sforare la destinazione,
	 * la seconda è un controllo aggiuntivo che mi basta per inglobare tutti i worst case.
	 */
	for( i=offsetH,h=0;h<dest->h && i<source->h;i++,h++){//righe
		for( j=offsetW,k=0;k<dest->w && j<source->w;j++,k++){//colonne
			(dest->data)[h][k]=(source->data)[i][j];
		}
	}
}


/*
 * DEST >> SOURCE
 * Simile a subCopy. Qui la differenza è che è dest ad essere più grande della sorgente, gli offset sono quindi
 * riferiti alla destinazione in questo caso
 */
void copySubMatrix2(matrix *source, matrix *dest, int offsetH, int offsetW){
	int i,j,h,k;
	/*
	 * per entrambi i for: la prima condizione è fondamentale per non sforare la destinazione,
	 * la seconda è un controllo aggiuntivo che mi basta per inglobare tutti i worst case.
	 */
	for( i=0,h=offsetH;h<dest->h && i<source->h;i++,h++){//righe
		for( j=0,k=offsetW;k<dest->w && j<source->w;j++,k++){//colonne
			(dest->data)[h][k]=(source->data)[i][j];
		}
	}
}

//ritorna la massima tra le dimensioni di 2 matrici
int getMaxMatrixDimension(matrix *a, matrix *b){
	int max = INT_MIN;
	if(a->h > max)
		max = a->h;
	if(a->w > max)
		max = a->w;
	if(b->h > max)
		max = b->h;
	if(b->w > max)
		max = b->w;
	return max;
}
