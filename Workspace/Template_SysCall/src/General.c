/*
 ============================================================================
 Name        : Template_SysCall.c
 Author      : Alessio
 Version     :
 Copyright   : Your copyright notice
 Description : prima versione di template per System Call
 ============================================================================
 */

#include <stdio.h> //standard input output
#include <stdlib.h>
#include <time.h>//per gestire il random
#include <string.h> //libreria string
#include <unistd.h>
#include <signal.h> //consente gestione segnali anche in forma non numerica
#include <fcntl.h> //gestisce modalita apertura file
#include <sys/wait.h>



//funzioni standard
void forkError();
void argomentsError();
void print_usage(char*);
void waitChild();
void pipeError();


//varibili globali



int main(int argc, char *argv[]){
	argomentsError(argc,argv);

}//fine main







void forkError(){
	perror("Fork error:");
	exit(1);
}

void argomentsError(int argc,char **argv){
	if(argc!=5){
		fprintf(stderr,"Numero di argomenti non valido\n");
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
 	}
}

void print_usage(char *progName){
	fprintf(stderr, "Usage:\n\t%s fileIn FileOut c1 c2\n",progName);
}

void waitChild(){
    int status, pid;

    pid = wait(&status);
    if(pid < 0) {
        perror("Error while waiting for a child to terminate:");
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status))
        printf("Child %d terminated with exit status %d\n", pid,WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("Child %d was terminated by signal no. %d\n", pid,WTERMSIG(status));
}

void pipeError(){
	perror("Pipe error:");
	exit(1);
}



