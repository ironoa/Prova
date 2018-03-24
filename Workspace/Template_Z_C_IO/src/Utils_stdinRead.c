/*
 ============================================================================
 Name        : Template_Z_C_IO.c
 Author      : Alessio
 Version     :
 Copyright   : Your copyright notice
 Description : Gestione file e stringhe
 ============================================================================
 */

//ovviamente non sono necessari tutti questi include, da potare poi quando piu esperto
#include <stdio.h> //fondamentale di sicuro
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>//gestione file, es O_WRONLY
#include <string.h> //metodi per le stringhe

#define MAX_STRING_LENGTH 256
//#define FILENAME_MAX 20 //definizione gia in stdio.h



/********* LETTURA A CARATTERE DA STDIN ************/
char readc(){
	char c;
	char ok[100]; //di supporto per il flush del buffer dello stdin

	puts("Inserisci carattere dal leggere:");
	c=getchar(); //in un inserimento da std in getchar non consuma il \n dal buffer di in
	//while (getchar() != '\n');//Consuma il resto della linea, tecnica 1
	fgets(ok,sizeof(ok),stdin); //Consuma il resto della linea, tecnica 2

	return c;
}
/***************************************************************/


/*
 * Lettura a carattere di una linea da stdin.
 * Non lo posso chiamare filtro perchè non consuma tutto fino a EOF
 */
void readln_car(){
	char c;

	puts("Inserisci una linea:");
	do {
		c=getchar();

		//gestione del contenuto letto
		printf("%c ", c);//debug
	}
	while(c!= '\n');
	//il buffer in ne esce pulito, funziona anche come un flush un po scomodo

}


/*
 * trim degli spazi bianchi e \n INIZIALI
 * ha piu senso se si parla di letture da file
 */
void myTrim_getchar(){
	char car;
	int nread;

	do{	//leggo a carattere (spazi e \n iniziali)
		nread = getchar();
		car = (char)nread;
	} while (((car == ' ') || (car == '\n')) && (nread > 0));

	//car contine il primo valore "buono"
}


/*
 * lettura da stdin di una riga
 */
char* readln(){
	static char stringa[MAX_STRING_LENGTH]; //attenzione static
	/*
	 * apro una parentesi: senza static stringa sarebbe una semplice variabile locale (PUNTATORE),
	 * deallocata quindi alla fine di questa funzione ==> non avrebbe senso ritornarla essendo un puntatore.
	 * ==> con static oltre a cambiarne la visibilità, che diventa globale, ne modifico
	 * anche il tempo di vita, che persiste alla chiusura di questa funzione
	 */
	printf("Inserisci una linea: \n");
	//gets(stringa);//DEPRECATO MEGLIO fgets, inoltre non conserva il FINE LINEA
	/*
	 * gets puo essere utilizzato anche per fare flush del buffer di stdin dopo una lettura
	 * a singolo carattere con getchar
	 */
	fgets(stringa,sizeof(stringa),stdin); //fgets conserva eventuali fine linea
	/*
	 * se non voglio il fine linea letto da fgets
	 * strtok(riga, "\n"); //rimuovo il fine linea letto da fgets
	 */
	return stringa;
}


/************FILTRO a LINEA,LETTURA DA STDIN**************************/
void filterLine(){
	char stringa[FILENAME_MAX+1];

	printf("Inserisci un nome: \n");
	while( fgets(stringa,sizeof(stringa),stdin) != NULL ){ //fino a EOF
		strtok(stringa, "\n"); //rimuovo il fine linea letto da fgets

		//elaboro

		printf("Inserisci un nome: \n");
	}
}
/*************************************************************/

/************** FILTRO A CARATTERE DA STDIN L**************************/
void filterCar(){
	char c;

	while( (c=getchar()) != EOF ) /* Fino ad EOF*/{

		//elaboro
	}
}
/**************************************************************/

/*
 * concatenazione di stringhe lette da stdin
 */
void readln_concat(){
	char riga [MAX_STRING_LENGTH];//alla fine concatenata
	char buf[MAX_STRING_LENGTH];//risultato parziale

	fgets(riga,sizeof(riga),stdin); //stringa ben formata = c'è il fine stringa
	strtok(riga, "\n"); //rimuovo il fine linea letto da fgets

	sprintf(buf,"%s",riga);	//formatted string, copio il risultato parziale

	strcat(riga, "parole a caso"); //la nuova stringa ricopre a partire dal fine stringa, riga continua ad essere stringa ben formata
}




/*********lettura RIGA DA STDIN e successiva scrittura su file*********/
void readln_writeFile(){
	char riga [MAX_STRING_LENGTH];

	fgets(riga,sizeof(riga),stdin); //stringa ben formata = c'è il fine stringa
	strtok(riga, "\n"); //rimuovo il fine linea letto da fgets

	//apertura file
	int fd = open("filename.txt", O_WRONLY);
	if (fd < 0){
		perror("P0: Impossibile creare/aprire il file");
		exit(EXIT_FAILURE);
	}
	//scrittura su file
	int bytes_to_write = strlen(riga);//strlen è una size of a runtime cucita sulla effettiva lunghezza della stringa
	int written = write(fd, riga, bytes_to_write);
	if (written < 0){
		perror("P0: errore nella scrittura sul file");
		close(fd);
		exit(EXIT_FAILURE);
	}
	//chiusura file
	close(fd);

}
/*****************************************************************/





/**************LETTURA FORMATTATA INTERO**********/
void myScanf_Int(){
	int in;
	char ok[100];

	puts("Inserire un numero intero:");

	//lettura formatta con controllo
	/*
	 * scanf non consuma in automatico i new line, e non svuota il buffer nemmeno in caso di match.
	 * INOLTRE
	 * Problema nell'implementazione della scanf. Se l'input contiene PRIMA
	 * dell'intero altri caratteri la testina di lettura si blocca sul primo carattere
	 * (non intero) letto. Ad esempio: ab1292\n
	 *								   ^     La testina si blocca qui
	 * Bisogna quindi consumare tutto il buffer in modo da sbloccare la testina.
	 */
	while(scanf("%d", &in)!=1){
		/*
		 * inserimento non corretto
		 * flush
		 * ci riprovo
		 */
		fgets(ok,sizeof(ok),stdin); //Consuma il resto della linea, tecnica 2
		printf("buffer liberato: %s\n", ok);//debug

		puts("Inserire un numero intero:");
	}
	fgets(ok,sizeof(ok),stdin); //Consuma il resto della linea, tecnica 2
	printf("buffer liberato: %s\n", ok);//debug

}
/*****************************************************************/

/**************FILTRO, LETTURA FORMATTATA INTERO**********/
void filter_myScanf_Int(){
	int ok=0,num;
	char okstr[256];

	puts("Inserire un numero intero, EOF per terminare: ");
	while ((ok=scanf("%i", &num)) != EOF ){

		//lettura formatta con controllo
		/*
		 * scanf non consuma in automatico i new line, e non svuota il buffer nemmeno in caso di match.
		 * INOLTRE
		 * Problema nell'implementazione della scanf. Se l'input contiene PRIMA
		 * dell'intero altri caratteri la testina di lettura si blocca sul primo carattere
		 * (non intero) letto. Ad esempio: ab1292\n
		 *								   ^     La testina si blocca qui
		 * Bisogna quindi consumare tutto il buffer in modo da sbloccare la testina.
		 */
		if(ok != 1){
			/*
			 * inserimento non corretto
			 * flush
			 * ci riprovo
			 */
			fgets(okstr,sizeof(okstr),stdin); //Consuma il resto della linea, tecnica 2
			printf("buffer liberato: %s\n", okstr);//debug

			puts("Inserire un numero intero, EOF per terminare: ");
			continue;
		}
		fgets(okstr,sizeof(okstr),stdin); //Consuma il resto della linea, tecnica 2
		printf("buffer liberato: %s\n", okstr);//debug
		// quando arrivo qui l'input e' stato letto correttamente

		//gestisco ed elaboro

		puts("Inserire un numero intero, EOF per terminare: ");
	}//while EOF
}
/*****************************************************************/



