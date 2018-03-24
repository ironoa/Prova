/*
 ============================================================================
 Name        : Template_Z_C_IO.c
 Author      : Alessio
 Version     :
 Copyright   : Your copyright notice
 Description : Gestione file con system call
 ============================================================================
 */

//ovviamente non sono necessari tutti questi include, da potare poi quando piu esperto
#include <stdio.h> //fondamentale di sicuro
#include <stdlib.h>
#include <unistd.h> //sys call, per esempio read e getpid
#include <fcntl.h> //gestione file, es O_WRONLY
#include <string.h> //metodi per le stringhe

#define MAX_STRING_LENGTH 256
#define LINE_LENGTH 128




/*******************************APERTURA FILE*******************************/
void openFile(){

	//posso utilizzare una cambinazine di vari flags
	int fd = open("fileName.txt", O_RDONLY | O_WRONLY|O_CREAT|O_TRUNC,00640);
	/*oppure un flag specifico
	 *
	 * fd = open("filename", O_RDONLY);
	 */

	if (fd < 0){
		perror("P0: Impossibile creare/aprire il file");
		exit(EXIT_FAILURE);
	}

	//utilizzo

	close(fd);
}
/*********************************************************************/




/********* Verifico l'esistenza del file ************/
void verifyFile(){

	int fd_sorg;
	if((fd_sorg=open("filename.txt", O_RDONLY))<0){
		perror("open file sorgente");
		exit(EXIT_FAILURE);
	}

	//utilizzo

	close(fd_sorg);

}
/*********************************************************************/

/*
 * trim degli spazi bianchi e \n INIZIALI
 */
void myTrim(){
	int nread;
	char car;

	int fd_sorg;
	if((fd_sorg=open("filename.txt", O_RDONLY))<0){
		perror("open file sorgente");
		exit(EXIT_FAILURE);
	}

	do{	//leggo a carattere (spazi e \n iniziali)
		nread = read(fd_sorg, &car, sizeof(char));
		if (nread < 0){// errore o fine file
			perror("c'e un problema");
			close(fd_sorg);
			exit(EXIT_FAILURE);
		}
	} while (((car == ' ') || (car == '\n')) && (nread > 0));


	//utilizzo

	close(fd_sorg);
}






/**********FILTRO a CARATTERE,lettura da FILE*********************************/
void filterCar_file(){
	char fileName[] = "filename.txt";
	char err[MAX_STRING_LENGTH];

	//apertura file
	int fd = open(fileName, O_RDONLY);
	if (fd < 0){
		perror("P0: Impossibile creare/aprire il file");
		exit(EXIT_FAILURE);
	}

	int nread=0;
	char read_char;
	while( ( nread = read(fd, &read_char, sizeof(char)) ) != 0  ) /* Fino ad EOF*/{
		if (nread < 0){
			sprintf(err,"(PID %d) impossibile leggere dal file %s", getpid(), fileName);
			perror(err);
			close(fd);
			exit(EXIT_FAILURE);
		}

		//utilizzo del carattere letto salvato in read_char
	}

	close(fd);
}
/**************************************************/


/************** FILTRO A CARATTERE DA STDIN con SYSTEM CALL**************************/
void filterCar_stdIn(){
	char err[MAX_STRING_LENGTH];
	char c;

	int nread=0;
	while( ( nread = read(0, &c, sizeof(char)) ) != 0 ) /* Fino ad EOF*/{
		if (nread < 0){
			sprintf(err,"(PID %d) impossibile leggere dal file ", getpid());
			perror(err);
			exit(EXIT_FAILURE);
		}

		//elaboro
	}
}
/**************************************************************/



/****************FILTRO A CARATTERE da stdin****************************
 *
 * ESEMPIO: FILTRO PREFIX, gestione a CARATTERE
 *
 */
void filterCar_filePrefix(){
	char err[MAX_STRING_LENGTH];
	char fileName[] = "filename.txt";
	char prefix[MAX_STRING_LENGTH]="Nel mezzo del";//stringa base di confronto
	int lPrefix=strlen(prefix);//lunghezza della striga base di confronto
	char cmp[MAX_STRING_LENGTH];// banco da lavoro temporaneo, conterrà ciò che va comparato con il prefix
	char read_char; //carattere che verra letto mano a mano

	//apertura file
	int fd = open(fileName, O_RDONLY);
	if (fd < 0){
		perror("P0: Impossibile aprire il file");
		exit(EXIT_FAILURE);
	}

	int nread=0;
	while( ( nread = read(fd, &read_char, sizeof(char)) ) != 0 ) /* Fino ad EOF*/{
		if (nread < 0){
			sprintf(err,"(PID %d) impossibile leggere dal file %s", getpid(), fileName);
			perror(err);
			close(fd);
			exit(EXIT_FAILURE);
		}

		int i=0;//testina scorrevole
		int daStampare=0; //boolean
		while(read_char!='\n'){//gestione linea

			if(i<lPrefix){
				//ok la considero
				cmp[i]=read_char;
				i++;
			}

			if(i==lPrefix){
				//caso che va gestito
				cmp[i]='\0';
				i++;
				if(!strcmp(cmp,prefix)){
					//stringhe uguali
					daStampare=1;
					printf("Trovato un buon match: %s",cmp);
				}
			}
			else if(daStampare){
				//stamperà fino alla fine della linea...
				printf("%c",read_char);
			}

			nread = read(fd,&read_char,sizeof(char));
			//ho fatto una lettura... un controllo ci vuole dai
			if(nread == 0 ){ //EOF
				break;
			}
			else if (nread < 0){
				sprintf(err,"(PID %d) impossibile leggere dal file %s", getpid(), fileName);
				perror(err);
				close(fd);
				exit(EXIT_FAILURE);
			}
		}//while linea

		if(daStampare) //se è stato stampato qualcosa....
			printf("\n");
	}//while EOF

	close(fd);
}
/***********************************************************************/





/******************FILTRO CHE CONTA **************************************/
/*void conta(int fd, int * caratteri, int * parole, int * linee)
 *							^------------^-------------^----- puntatori a risultati
 *				^---- descrittore, già controllato, del file
 * Per controllare l'esatta esecuzione della funzione, è possibile utilizzare l'utile comando Linux 'wc'.
 * 	'man wc' sul terminale per info.
 */
void filter_conta(int fd, int * caratteri, int * parole, int * linee)
{
	*caratteri = 0;
	*parole = 0;
	*linee = 0;

	/* tipoChar = intero che discrimina tra carattere e separatore:
	 *	0 = separatore;
	 *	1 = carattere.*/
	int tipoChar = 0;
	int nread;
	char read_char, err[LINE_LENGTH];

	while((nread = read(fd, &read_char, sizeof(char))) != 0 ){//fino a EOF
		if (nread < 0){
			sprintf(err,"(PID %d) impossibile leggere dal file", getpid());
			perror(err);
			exit(0);
		}

		else{
			*caratteri=*caratteri+1;

			//carattere letto è un separatore
			if(read_char == ' ' || read_char == '\r')
				tipoChar = 0;

			else if(read_char == '\n'){ //separatore (fine linea)
				*linee=*linee+1;
				tipoChar = 0;
			}

			else{ //carattere non separatore
				/* Il carattere di prima può essere
				 * 	Separatore = separatore e carattere --> inizia una nuova parola;
				 *	Carattere = carattere e carattere --> non faccio niente.*/
				if (tipoChar == 0){
					*parole=*parole+1;
				}
				tipoChar = 1;
			}
		}
	}//while oef
}
/**********************************************************************/



/******************FILTRO CHE TRASFERISCE LE LINEE CON ALMENO 1 OCCORRENZA PRESENTE***********************
 *
 * PRE: riceve dei file descriptor gia aperti, non è dunque qui che si gestira la chiusura
 *
 * DA TESTARE E MIGLIORARE
 *
 * ***************/
void filter_trasferisciLinee(int fdIn, int fdOut, char*parola){

	int DIM=100;
	int nread;
	char car;
	char buffer; //forse inutile
	char stringBuffer [DIM];//da confrontare con parola
	char linea[DIM]; //da trasferire in scrittura a fdOut
	int daInviare=1;//0 significa invia

	while (1){//demone? No, struttura in cui prevedo un meccanismo di uscita all interno
		int iBuffer=0;
		int iLinea=0;

		//trim Iniziale
		do{	//leggo a carattere (spazi e \n iniziali)
			nread = read(fdIn, &car, 1);
			if (nread <= 0){// errore o fine file
				if(nread<0)
					perror("c'e un problema");
				return;
			}
		} while (((car == ' ') || (car == '\n')) && (nread > 0));

		//si parte
		buffer = car;
		linea[iLinea]=car;
		stringBuffer[iBuffer]=car;
		iBuffer++;
		iLinea++;

		while (1){ //leggo a caratteri le linee
			nread = read(fdIn, &car, 1);
			if (nread <= 0){// errore o fine file
				if(nread<0)
					perror("c'e un problema");
				return;
			}

			buffer = car;
			linea[iLinea]=car;
			stringBuffer[iBuffer]=car;
			iBuffer++;
			iLinea++;

			//printf("DEBUG 1, %s, %c\n",stringBuffer,car);
			if ((buffer == ' ') || (buffer == '\n')){//fine parola o fine linea
				stringBuffer[iBuffer-1]='\0';

				if (strcmp(stringBuffer,parola)==0){
					//parola trovata
					printf("DEBUG: print occurrence %s \n", stringBuffer);
					daInviare=0;//l'intera linea sara da inviare
				}
				memset(stringBuffer, 0, sizeof(stringBuffer));
				iBuffer=0;

				if (buffer == '\n'){//linea finita

					if(daInviare==0){
						//invio la linea
						int j=0;
						for(j=0;j<iLinea;j++){
							if (write(fdOut, &linea[j], 1)<0){
								perror("errore in write");
								return;
							}
						}
						printf("LINEA INVIATA CON SUCCESSO!");
					}

					//ricomincio
					iLinea=0;
					memset(linea, 0, sizeof(linea));
					daInviare=1;//false
				}//caso fine linea
			}//fine parola o fine linea
		}//lettura linea
	}//while main
}
/***************************************************************************/




/***********CONTA LE OCCORRENZE IN UN FILE**************************************
 *
 * meno elegante... da sistemare e testare
 *
 * *******/
void filter_contaOccorrenze(int fd, int * caratteri, int * parole, int * linee, char *parola, int * occorrenze){
	*caratteri = 0;
	*parole = 0;
	*linee = 0;
	*occorrenze = 0;

	int DIM=100;
	int nread, index;
	char car;
	char buffer;
	char stringBuffer [DIM];

	while (1){
		index=0;
		do{	//leggo a caratteri (spazi e \n iniziali)
			nread = read(fd, &car, 1);
			*caratteri = *caratteri + 1;
			if (car == '\n') //new line
				*linee = *linee + 1;
			stringBuffer[index]=car;
			index=index+1;
		} while (((car == ' ') || (car == '\n')) && (nread > 0));

		if (nread <= 0){
			*caratteri = *caratteri - 1;
			return;
		}
		else buffer = car;

		while (1){ //leggo a caratteri tutto il resto
			nread = read(fd, &car, 1);
			if (nread > 0){
				*caratteri = *caratteri + 1;
				buffer = car;

				stringBuffer[index]=car;
				index=index+1;

			}
			else return;
			if ((buffer == ' ') || (buffer == '\n')){
				if (buffer == '\n')
					*linee = *linee + 1;
				*parole = *parole + 1;
				if (strstr(stringBuffer,parola)!=NULL){
					printf("DEBUG: print occurrence %s \n", stringBuffer);
					*occorrenze = *occorrenze +1;
				}
				memset(stringBuffer, 0, sizeof(stringBuffer));
				index=0;
				break;
			}
		}
	}
}
/********************************************************/


/**********CONTA (SOLO) LE OCCORRENZE IN UN FILE***************
 *
 * idem, manca di eleganza da sistemare e testare
 *
 *
 * ******************************/
void filter_contaOccorrenze2(int fd, int * occorrenze, char *parola){
	*occorrenze = 0;

	int DIM=100;
	int nread, index;
	char car;
	char buffer;
	char stringBuffer [DIM];

	while (1){

		do{	//leggo a caratteri (spazi e \n iniziali)
			index=0;
			nread = read(fd, &car, 1);
			stringBuffer[index]=car;
			index=index+1;
		} while (((car == ' ') || (car == '\n')) && (nread > 0));

		if (nread <= 0){
			return;
		}
		else buffer = car;//si parte!

		while (1){ //leggo a caratteri tutto il resto
			nread = read(fd, &car, 1);
			if (nread > 0){
				buffer = car;
				stringBuffer[index]=car;
				index=index+1;

			}
			else return; //errore o fine FILE

			if ((buffer == ' ') || (buffer == '\n')){
				stringBuffer[index-1]='\0';
				if (strcmp(stringBuffer,parola)==0){
					//parola trovata
					printf("DEBUG: print occurrence %s \n", stringBuffer);
					*occorrenze = *occorrenze +1;
					return;//mi basta 1 occorrenza per uscire
				}
				memset(stringBuffer, 0, sizeof(stringBuffer));
				index=0;
			}
		}
	}
}
/********************************************************/





