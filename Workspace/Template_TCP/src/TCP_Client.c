/*
 ============================================================================
 Name        : TCP_Server.c
 Author      : Onori Alessio
 Matricola	 : 0000695432
 Version     :
 Copyright   :
 Description : Template di soluzione Server TCP C
 ESEMPIO	 : Client per richiedere l'ordinamento remoto di un file
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define DIM_BUFF 256

int main(int argc, char *argv[])
{
	int sd, fd_sorg, fd_dest, nread;
	char buff[DIM_BUFF];
	// FILENAME_MAX: lunghezza massima nome file. Costante di sistema.
	char nome_sorg[FILENAME_MAX+1], nome_dest[FILENAME_MAX+1];
	struct hostent *host;
	struct sockaddr_in servaddr;


	/* CONTROLLO ARGOMENTI 	***************************************/
	if(argc!=3){
		printf("Error:%s serverAddress serverPort\n", argv[0]);
		exit(1);
	}

	/*
	 * NOTA: gethostbyname restituisce gli indirizzi gia' in formato di rete
	 */
	host = gethostbyname(argv[1]);
	if (host == NULL){
		printf("%s not found in /etc/hosts\n", argv[1]);
		exit(1);
	}

	/*VERIFICA INTERO*/
	nread=0;
	while( argv[2][nread]!= '\0' ){
		if( (argv[2][nread] < '0') || (argv[2][nread] > '9') ){
			printf("Secondo argomento non intero\n");
			exit(2);
		}
		nread++;
	}
	/********************************************************/


	/* INIZIALIZZAZIONE INDIRIZZO SERVER -------------------------- */
	memset((char *)&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=((struct in_addr*) (host->h_addr))->s_addr;
	servaddr.sin_port = htons(atoi(argv[2]));
	/********************************************************/



	/******* CORPO DEL CLIENT: ESEMPIO *****************
	ciclo di accettazione di richieste da utente ------- */
	printf("Ciclo di richieste di ordinamento fino a EOF\n");
	printf("Nome del file da ordinare, EOF per terminare: ");

	/* ATTENZIONE!!
	* Cosa accade se la riga e' piu' lunga di FILENAME_MAX-1?
	* Stesso dicasi per le altre gets...
	* Come si potrebbe risolvere il problema?
	*/
	while (fgets(nome_sorg,sizeof(nome_sorg),stdin)!=NULL){ //filtro, fino a EOF
		strtok(nome_dest, "\n"); //rimuovo il fine linea letto da fgets

		printf("File da aprire: __%s__\n", nome_sorg);

		/* Verifico l'esistenza del file */
		if((fd_sorg=open(nome_sorg, O_RDONLY))<0){
			perror("open file sorgente"); 
			printf("Qualsiasi tasto per procedere, EOF per fine: ");
			continue;
		}
		printf("Nome del file ordinato: ");
		if ( fgets(nome_dest,sizeof(nome_dest),stdin)==NULL ) break;
		strtok(nome_dest, "\n"); //rimuovo il fine linea letto da fgets
		/*	
		else{
			printf("File da aprire: __%s__\n", nome_dest);
		}
		*/

		/*Verifico creazione file*/
		if((fd_dest=open(nome_dest, O_WRONLY|O_CREAT, 0644))<0){
			perror("open file destinatario");
			printf("Nome del file da ordinare, EOF per terminare: ");
			continue;
		}

		/* CREAZIONE SOCKET ------------------------------------ */
		sd=socket(AF_INET, SOCK_STREAM, 0);
		if(sd<0) {perror("apertura socket"); exit(1);}
		printf("Client: creata la socket sd=%d\n", sd);
		/*********************************************/


		/*** Operazione di BIND implicita nella connect *****/
		if(connect(sd,(struct sockaddr *) &servaddr, sizeof(struct sockaddr))<0)
		{perror("connect"); exit(1);}
		printf("Client: connect ok\n");
		/*********************************************/


		/*********INVIO File**********/
		printf("Client: stampo e invio file da ordinare\n");
		while((nread=read(fd_sorg, buff, DIM_BUFF))>0){
			write(1,buff,nread);	//stampa
			write(sd,buff,nread);	//invio
		}
		printf("Client: file inviato\n");
		/* Chiusura socket in spedizione -> invio dell'EOF */
		shutdown(sd,1);
		/*********************************************/


		/******RICEZIONE File**************/
		printf("Client: ricevo e stampo file ordinato\n");
		while((nread=read(sd,buff,DIM_BUFF))>0){
			write(fd_dest,buff,nread);
			write(1,buff,nread);
		}
		printf("Traspefimento terminato\n");
		/* Chiusura socket in ricezione */
		shutdown(sd, 0);
		/*********************************************/

		/* Chiusura file */
		close(fd_sorg);
		close(fd_dest);

		printf("Nome del file da ordinare, EOF per terminare: ");
	}//while
	/********************************************************/

	printf("\nClient: termino...\n");
	exit(0);
}

