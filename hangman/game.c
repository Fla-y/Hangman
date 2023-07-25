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

//The file has a list of words, this makes it easy to add new words to the game

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
		printf("ERROR while trying to open the file: %s", fileName);
		return error;
	}

	n = fscanf(fp, "%s %d", &temp.word, &temp.dim);
	while (n == 2) {
		nLines++;
		n = fscanf(fp, "%s %d", &temp.word, &temp.dim);
	}

	rewind(fp);
	//now i know the number of words in the file, so i can choose one randomly
	srand(time(NULL));
	wordSel = rand() % (nLines + 1);
	wordSel++;
	//printf("%d\n", wordSel);

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

//magari in futuro metterò un check che controlli che tutte e lettere siano minuscole, per ora lo do per scontato

//____________________________________________________________________________________________________________________________

/*inizia il gioco 
6 vite
numero di lettere fornito ma non la prima lettera*/


word checkInWord(char guess, word answer) {
	int len;
	len = answer.dim+1;
	char* sol;
	int status = 0,counter=0;
	word checkStatus;
	
	sol = (char*)malloc(len * sizeof(char));
	if (sol == NULL) {
		printf("Error in memory allocation\n");
		exit(0);
	}

	for (int i = 0; i < (len-1); i++) {
		if (guess == answer.word[i]) {
			sol[i] = guess;
			printf("letter found in spot n: %d\n", i);
			status = 1;
			counter++;
		}
		else {
			sol[i] = '1';
		}

	}

	strcpy(checkStatus.word, sol);

	free(sol);
	checkStatus.dim = counter; //the dim parameter is used to tell how many times the letter was found in the word
	return checkStatus;

}

int game(word answer) {
	int len = answer.dim+1,win=0, tries=0,k=0; //win=1 means you won, otherwise it's 0
	char guess, usedLetters[27],alphabet[27]="abcdefghijklmnopqrstuvwxyz",trash;
	char* wordGuess;
	word check;
	int used = 0, isValid=0; //isValid=1 if the letter guessed is a valid one
	int lives = 6,point; //magari più avanti creando un menù di partenza posso creare varie difficoltà con più o meno vite e parole diverse

	wordGuess = (char*)malloc(len * sizeof(char));
	if (wordGuess == NULL) {
		printf("Error in memory allocation\n");
		exit(0);
	}

	for (int i = 0; i < (len-1); i++) {
		wordGuess[i] = '-'; //shows how long the word actually is
	}

	wordGuess[len - 1] = '\0';

	printf("%s\n", wordGuess);

	do {
		printf("lives: %d\n", lives);
		if (tries != 0) {
			printf("used letters: ");
		}
		for (int j = 0; j < tries; j++) {
			printf("%c, ", usedLetters[j]);
		}
		

		for (; isValid != 1;k++) {
			if (k != 0) {
				printf("the letter you just typed is not valid, please use a letter from the english alphabet");
			}
			printf("\nGuess a letter?\n");
			guess = getchar(); //ora come ora do per scontato che il carattere inserito sia minuscolo e che sia valido, poi lo migliorerò...
			trash = getchar();

			for (; trash != '\n';) {
				printf("You wrote more than a letter, I'll use the first one\n");
				trash = getchar();
			}
			guess = tolower(guess);
			for (int i = 0; alphabet[i] != '\0'; i++) {
				if (guess == alphabet[i]) {
					isValid = 1;
				}
			}
		}


		if (tries != 0) {
			for (int k = 0;k<27 ; k++) {
				if (used == 1) {
					k = 0;
				}
				used = 0;
				if (guess == usedLetters[k]) {
					printf("Error, you have already tried this letter, try another one!\n");
					guess = getchar;
					trash=getchar();
					for (; trash != '\n';) {
						printf("You typed more than one letter, i'll take the first one\n");
						trash = getchar();
					}
					used = 1;
				}
			}
		}
		usedLetters[tries] = guess;

		check = checkInWord(guess, answer);
		if (check.dim != 0) {  //in questo caso la lettera è stata trovata
			for (int i = 0; i < (len-1); i++) {
				if (check.word[i] != '1') {
					wordGuess[i] = check.word[i];
				}
			}
			printf("%s\n", wordGuess);

			point=strcmp(wordGuess, answer.word);
			if (point == 0) {
				win = 1;
			}
		}
		else {
			lives--;
		}
		tries++;
		isValid = 0;
		k = 0;
	} while (lives > 0 && win == 0);
	free(wordGuess);
	
	if (win == 1) {
		printf("Congratulation, you won!\n");
	}
	else {
		printf("You lost!\nThe word was:\n%s", answer.word);
	}

	return win;
}
