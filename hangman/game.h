#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define DIM 25


typedef struct
{
	char word[DIM];
	int dim;  //nb dim non conta \0 per cui di base se lo uso per la dimensione devo incrementarlo di uno
	//IL MOTIVO PER CUI NON HA FUNZIONATO FINO AD ORA è ESATTAMENTE QUESTO, CONTROLLA E RIPROVA

}word;

word readFile(char* filename);

int game(word answer);

word checkInWord(char guess, word answer);

