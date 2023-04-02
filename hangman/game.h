#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define DIM 25


typedef struct
{
	char word[DIM];
	int dim;

}word;

word readFile(char* filename);

int game(word answer);

word checkword(char c, word answer);

