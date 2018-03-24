/*
 ============================================================================
 Name        : Template_Z_C_IO.c
 Author      : Alessio
 Version     :
 Copyright   : Your copyright notice
 Description : Gestione file
 ============================================================================
 */

//ovviamente non sono necessari tutti questi include, da potare poi quando piu esperto
#include <stdio.h> //fondamentale di sicuro
#include <stdlib.h>
#include <unistd.h> //sys call, per esempio read e getpid
#include <fcntl.h> //gestione file, es O_WRONLY
#include <string.h> //metodi per le stringhe
#include <dirent.h> //directory operations

#define MAX_STRING_LENGTH 256
#define LINE_LENGTH 128


/********************************************************/
/* funzione che conta i file presenti in una directory
 *
 */
int conta_file (char *name){
	DIR *dir; //struttura directory astratta
	struct dirent * dd; //struttura directory letta
	int count = 0;

	dir = opendir (name);
	while ((dd = readdir(dir)) != NULL){
		printf("Trovato il file %s\n", dd-> d_name);
		count++;
	}

	printf("Numero totale di file %d\n", count);

	closedir (dir);
	return count;
}
/********************************************************/



/********************************************************/
/* funzione che conta i file presenti in una directory, FILTRANDOLI PER: dimensione e suffisso
 * esempio molto interessante che fa uso delle strutture
 *
 */
int conta_file_filtro(char *direttorio,char *suffisso, int soglia){
	int result = 0;
	DIR* dir;
	struct dirent * dd;
	int fd_file;
	off_t fileSize; //struttura size e offset
	char stringBuffer[strlen(suffisso)+1];

	result = -1;

	printf("Richiesto direttorio %s\n", direttorio);
	if ((dir = opendir(direttorio)) == NULL)
		return result;

	result = 0;
	while ((dd = readdir(dir)) != NULL){

		fd_file = open(dd->d_name, O_RDONLY);
		if (fd_file < 0){
			printf("File inesistente\n");
			return result;
		}

		fileSize=lseek(fd_file,0L,SEEK_END);
		memcpy(stringBuffer, &dd->d_name[0], strlen(suffisso));
		stringBuffer[strlen(suffisso)+1] = '\0';
		if(strstr(stringBuffer,suffisso) != NULL)
			if (fileSize>=soglia){
				printf("DEBUG: candidate file size %ld\n", fileSize);
				result++;
			}

		close(fd_file);
	}

	printf("Numero totale di file nel direttorio richiesto %d\n", result);

	return result;
}
/********************************************************/
