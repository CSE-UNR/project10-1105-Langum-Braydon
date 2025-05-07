// Author: Braydon Langum
// Purpose: Project 10
// Date: 5/6/25

#include <stdio.h> 
#include <stdbool.h> 

void loadWord(char mysteryWord[]); 
bool isValidGuess(const char guess[]); 
void displayGuesses(char guesses[6][6], int guessCount, const char mysteryWord[]); 
void checkGuess(const char guess[], const char mysteryWord[], char result[]); 
bool isWordGuessed(const char guess[], const char mysteryWord[]); 
void toLowerCase(char word[]); 

int main() { 
	char mysteryWord[6]; 
	char guesses[6][6] = {0}; 
	int guessCount = 0; 
	bool guessedCorrectly = false; 

	loadWord(mysteryWord); 

	while (guessCount < 6 && !guessedCorrectly) { 
		char guess[6]; 
		printf("GUESS %d! Enter your guess: ", guessCount + 1); 
		scanf("%5s", guess);

		if (!isValidGuess(guess)) { 
			printf("Your guess must be 5 letters long.\n"); 
			printf("Please try again\n"); 
			continue; 
		} 

		toLowerCase(guess); 

		for (int i = 0; i < 6; i++) { 
			guesses[guessCount][i] = guess[i]; 
		} 

		guessedCorrectly = isWordGuessed(guess, mysteryWord); 

		printf("================================\n");
		displayGuesses(guesses, guessCount + 1, mysteryWord); 

		guessCount++; 
	} 

	if (guessedCorrectly) { 
		printf("		%s\n", mysteryWord); 
		printf("	You won in %d guesses!\n", guessCount);
		printf("		Amazing!\n");
	} else { 
		printf("You lost, better luck next time!\n"); 
	} 

	return 0; 

} 

void loadWord(char mysteryWord[]) { 
	FILE *file = fopen("word.txt", "r"); 
	if (file == NULL) { 
		printf("Error: Could not open word.txt\n"); 
	return; 
	} 
	fscanf(file, "%5s", mysteryWord); 
	fclose(file); 
} 

bool isValidGuess(const char guess[]) { 
	int length = 0; 
	while (guess[length] != '\0') { 
		if (guess[length] < 'a' || guess[length] > 'z') { 
			if (guess[length] < 'A' || guess[length] > 'Z') { 
				return false;
			} 
		} 
	length++; 
	} 
	return length == 5;
} 

void displayGuesses(char guesses[6][6], int guessCount, const char mysteryWord[]) { 
	for (int i = 0; i < guessCount; i++) { 
		char result[6] = {0}; 
		checkGuess(guesses[i], mysteryWord, result); 
		printf("%s\n", result); 

			for (int j = 0; j < 5; j++) { 
				if (result[j] == '^') { 
					printf("^"); 
				} else { 
					printf(" "); 
				} 
			} 
		printf("\n"); 
	} 
} 

void checkGuess(const char guess[], const char mysteryWord[], char result[]) { 
	bool used[5] = {false};

	for (int i = 0; i < 5; i++) { 
		if (guess[i] == mysteryWord[i]) { 
			result[i] = guess[i] - 32;
			used[i] = true; 
		} else { 
			result[i] = guess[i];
		} 
	} 

	for (int i = 0; i < 5; i++) { 
		if (result[i] >= 'A' && result[i] <= 'Z') { 
			continue; 
		} 
		for (int j = 0; j < 5; j++) { 
			if (!used[j] && guess[i] == mysteryWord[j]) { 
				result[i] = '^';
				used[j] = true; 
			break; 
			} 
		} 
	} 
} 

bool isWordGuessed(const char guess[], const char mysteryWord[]) { 
	for (int i = 0; i < 5; i++) { 
		if (guess[i] != mysteryWord[i]) { 
			return false; 
		} 
	} 
	return true; 
} 

void toLowerCase(char word[]) { 
	for (int i = 0; word[i] != '\0'; i++) { 
		if (word[i] >= 'A' && word[i] <= 'Z') { 
			word[i] += 32;
		} 
	} 
} 
