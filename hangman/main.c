#include "menu.h"

int main() {
	char* filename = "parole.txt";
	word gameWord;
	int result;
	gameWord = readFile(filename);
	//printf("%s\n", gameWord.word);

	result = game(gameWord);


	return result;

}
