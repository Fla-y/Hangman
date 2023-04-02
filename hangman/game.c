#include "game.h"

//la parola viene scelta casualmente da una lista di parole  -->lista o array?
//il gioco indica il numero di lettere
//magari in base alla difficoltà posso inserire o meno la prima lettera
//indica il numero di vite
//indica le lettere già tentate
//la lista viene creata a partire da un file di testo

/*leggo il file 1 volta e conto le righe
genero un numero casuale tra 1 e il numero di righe
leggo nuovamente il file fino alla riga che corrisponde al numero generato
salvo la parola in un array inserito a sua volta in una struttura solo perchè più comodo
----per ora l'array è statico, dopo proverò una versione a memoria dinamica
*/

//leggo il file

word readFile(char* fileName) {

	word temp;
	word error;
	error.dim = 1;
	error.word[0] = "a";
	int n,nLines=0, wordSel,i=1;

	FILE* fp;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("ERRORE nell'apertura del file: %s", fileName);
		return error;
	}

	n = fscanf(fp, "%s %d", &temp.word, &temp.dim);
	while (n == 2) {
		nLines++;
		n = fscanf(fp, "%s %d", &temp.word, &temp.dim);
	}

	rewind(fp);

	//ho contato il numero di righe del file, quindi ora posso scegliere a caso una parola all'interno del file
	srand(time(NULL));
	wordSel = rand() % (nLines + 1);
	wordSel++;
	printf("%d\n", wordSel);

	while (i<=wordSel && i!= -1) {
		n = fscanf(fp, "%s %d", &temp.word, &temp.dim);
		if (i == wordSel) {
			i = -2;
		}
		i++;
	}
	fclose(fp);
	return temp;
}

//magari in futuro metterò un check che controlli che tutte e lettere sino minuscole, per ora lo do per scontato

//____________________________________________________________________________________________________________________________

/*inizia il gioco 
6 vite
numero di lettere fornito ma non la prima lettera*/

word checkword(char c, word answer) {
	int i, result;
	word temp;
	temp.dim = 0;
	for (i = 0; i < answer.dim; i++) {
		if (c == answer.word[i]) {
			temp.dim = 1;
			temp.word[i] = c;
		}
		else {
			temp.word[i] = '0';
		}
	}
	return temp;
}

int game(word answer) {
	int lives = 6,len,test,safe,win=0,guessCount=0,i=0;
	char guess;
	len = answer.dim;
	char alphabet[27];
	char* sol;

	sol = (char*)malloc(len * sizeof(char));
	if (sol == NULL) {
		printf("Errore nell' allocazione della memoria...\n");
		exit(0);
	}

	word esito;

	for (int i = 0; i < len; i++) {
		printf("_ ");
	}
	printf("\n");
	
	do {
		if (i != 0) {
			printf("lettere già provate: ");
			for (int k = 0; k < i; k++) {
				printf("%c ", alphabet[k]);
			}
			printf("\n");
		}

		printf("prova una lettera;\n");
		guess = getchar();
		if (i == 0) {
			alphabet[i] = guess;
			//controllo se è nella parola, altrimenti tolgo una vita
			esito = checkword(guess, answer);
			if (esito.dim != 1) {
				lives--;
			}
			else {
				for (int counter = 0; counter < len; counter++) {
					if (esito.word[counter] != '0' && counter<len) {
						printf("trovata la lettera %c in posizione: %d\n", guess, counter);
						
					}
				}
			}

		}
		else {
			for (int j = 0; j < i && i < 27; j++) {
				if (guess == alphabet[j]) {
					j = i;
					printf("lettera già usata, prova con un' altra\n");
				}
				else {
					if (j == i) {
						i++;
						alphabet[i] = guess;
						lives--;
					}
				}
			}
		}
		i++;
	} while (lives>0 && win!=1);
	

	if (win == 1) {
		printf("congratulazioni hai vinto!");
		return 1;
	}
	else {
		printf("peccato, hai perso");
		return 2;
	}

	free(sol);

}
