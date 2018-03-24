/*
 ============================================================================
 Name        : Template_DataStructure.c
 Author      : Alessio
 Version     :
 Copyright   : Your copyright notice
 Description : STRUTTURA DATI generica STATICA. Esempio di TABELLA
 ============================================================================
 */

#include <stdio.h>//fondamentale di sicuro
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>//gestione file, es O_WRONLY
#include <string.h> //metodi per le stringhe

#define NUMRIGHE 12
#define NUMCOL 4
#define STRINGSIZE 100
#define LENGTH_NAME 20

/*
 * definizione della struttura Riga senza bisogno di malloc
 * ==> sarà più facile la gestione in quanto non sarà necessario
 * deallocare manualmente
 */
typedef struct{
	char col1[LENGTH_NAME];
	char col2[LENGTH_NAME];
	char col3[LENGTH_NAME];
	char col4[LENGTH_NAME];
}Riga;

/* STATO SERVER per esempio
 * definizione con static significa scope globale,
 * variabili non "automatiche"
 * variabili statiche = persistenti, ma anche UNICHE... appunto STATO
 * ATTENZIONE!!
 * Una variabile se non è statica è deallocata automaticamente: ciò significa che alla fine del suo scope o blocco,
 * viene deallocata sia la viariabile sia il suo contenuto.
 * Tutto ciò vale anche per le STRUTTURE, e quindi anche in questo caso
 */
static Riga tabella[NUMRIGHE];
static int inizializzato=0; //0=false
/****************************************/




/********************************************************/
void inizializza(){
	if (inizializzato==1) return;

	int i=0;
	for(i=0;i<NUMRIGHE;i++){
		//una possibile inizializzazione
		strcpy(tabella[i].col1,"L");
		strcpy(tabella[i].col2,"L");
		strcpy(tabella[i].col3,"L");
		strcpy(tabella[i].col4,"L");
	}
	inizializzato = 1;

	printf("Terminata inizializzazione struttura dati!\n");
}
/********************************************************/

/********************************************************/
void visualizza(){
	if(inizializzato==0)
		inizializza();

	int i;
	printf("\nCOL1 \t|| COL2 \t|| COL3\t|| COL4\n");
	for(i=0; i<NUMRIGHE; i++){
		printf("%s \t||", tabella[i].col1);
		printf("%s \t||", tabella[i].col2);
		printf("%s \t||", tabella[i].col3);
		printf("%s", tabella[i].col4);
		printf("\n");
	}
}
/********************************************************/


//int main(int argc, char **argv){
//	//struttura statica: Non devo neanche dichiararla nel main
//}
