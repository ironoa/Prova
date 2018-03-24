/*
 ============================================================================
 Name        : Prove.c
 Author      : Alessio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {

	int *a = malloc( sizeof(int)*4);
	a[1]=18;
	a[2]=18;
	free(a);

}
