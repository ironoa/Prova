/*
 ============================================================================
 Name        : Template_Math.c
 Author      : Alessio
 Version     :
 Copyright   : Your copyright notice
 Description : Utils di funzioni della libreria math
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>//ovvio
/*
 * NOTA BENISSIMO: PER FAR FUNZIONARE MATH.H BISOGNA FARE UNA MODIFICA AL SISTEMA DI LINKING,
 * APRIRE PROPERTIES E VEDERE CHE HO AGGIUNTO LA M
 */
#include <limits.h>//contiene per esempio INT_MAX e INT_MIN


/* Round X to nearest integral value, rounding halfway cases away from
   zero.  */
int myRound(double x){
	/*
	 * il cast a int è importantissimo
	 */
	int i = round(x);
	return i;
}


/*
 * logaritmo in base 2
 */
double myLog2(int x){
	double res = log2(x);
	return res;
}


/*
 * ritorna il massimo tra 2 valori
 */
double myMax(double x, double y){
	return fmax(x,y);
}

/*
 * ritorna il massimo tra una serie di valori passati come array
 */
int myMax2(int *values, int nValues){
	int max = INT_MIN;
	int i;
	for(i=0;i<nValues;i++){
		if(values[i]>max)
			max=values[i];
	}
	return max;
}

//si spiega da sola
double myPow(double base,double power){
	return pow(base,power);
}
