/*
Group Number: C
Group Member: Cameron Stalcup
Email: cameron.stalcup@okstate.edu
Date: 2/27/2022
Description: This project is a game where 1 or 2 players take turns inputting words based on what letters are made available. The letters are randomly chosen
from an input file as well as a list of words that are known to be made from those letters. Each word hasa specific point value based on how long it is, if id
is a new word, or if it is invalid. The game goes on until both players pass twice consecutively. At the end, the game declares a winner based on who got the
most points.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


typedef struct {
    char firstname[20];
    char lastname[20];
    char country[20];
    int score;
    char outcome[6];
    int wordsFound;
    int wordsAdded;    
} player;


void wordProcessing();
char* randomFile();
int isValidWordAndScore(char* prev, char* new, char* letters, char** used);
int checkFile(char* word, char* filename);
void getFileWords(char* filename);
int isValidWordFirstAndScore(char* new, char* letters, char** used);
int hasBeenUsed(char* new, char** words);
int scoring(char* word);
char* getCPUWord(int numGuesses);


player P1, P2, CPU;
char names[10][13] = {"input_01.txt", "input_02.txt", "input_03.txt",
        "input_04.txt", "input_05.txt", "input_06.txt", "input_07.txt",
        "input_08.txt", "input_09.txt", "input_10.txt"};
char fileWords[30][10];
int fileWordsLength = 0;


int main(){
    wordProcessing(2);
}


// =============================================================================================================================================================================================================
// Starts the game. gamemode refers to single player of multi player. 1 for Single, 2 for Multi.
void wordProcessing(int gamemode){
    // Initializes players and creates all needed variables.
    P1.score = 0; P1.wordsAdded = 0; P1.wordsFound = 0;
    P2.score = 0; P2.wordsAdded = 0; P2.wordsFound = 0;
    CPU.score = 0; CPU.wordsAdded = 0; CPU.wordsFound = 0;
    int giveScore, passes = 0, playerTurn = 0, numWords = 0, failedGuesses = 0;
    char entry[20];
    char storage[50][20];

    // Makes array of strings for words used in the game. 
    char** usedWords;
    usedWords = (char**)calloc(50, sizeof(char*));
    for (int i = 0; i < 50; i++){
        *(usedWords + i) = NULL;
    }

    // Makes an array for the two players in the game.
    player* players = calloc(2, sizeof(player));
    *(players) = P1;
    if (gamemode == 1){
        *(players + 1) = CPU;
    }
    else{
        *(players + 1) = P2;
    }
    
    // Gets the letters from the first line of each input_XX.txt
    srand(time(NULL));
    FILE* fp;
    char* filename = randomFile();
    fp = fopen(filename, "r");
    char validLetters[20];
    fgets(validLetters, 20, fp);
    if (validLetters[strlen(validLetters) - 1] == '\n'){
        validLetters[strlen(validLetters) - 1] = '\0';
    }
    getFileWords(filename);
    fclose(fp);

    printf("Enter Player 1's first name: ");
    scanf("%s", players[0].firstname);
    printf("Enter Player 1's last name: ");
    scanf("%s", players[0].lastname);
    printf("Enter Player 1's country: ");
    scanf("%s", players[0].country);


    // Singleplayer
    if (gamemode == 1){
        int cpuGuesses = 0;
        printf("\nMulti Player Game %d\n", gamemode);
        strcpy(players[1].firstname, "Computer");
        strcpy(players[1].lastname, "Player");
        strcpy(players[1].country, "N/A");
        while (passes < 4){
            if (failedGuesses == 3){
                printf("\nToo many invalid guesses. Passing");
                passes++;
                if (playerTurn == 0) { playerTurn = 1; }
                else { playerTurn = 0; }
                failedGuesses = 0;
                continue;
            }

            printf("\nLetters: %s", validLetters);
            printf("\nPlayer 1 Score: %d", players[0].score);
            printf("\nPlayer 2 Score: %d\nUsed Words: ", players[1].score);
            for (int i = 0; *(usedWords + i) != NULL; i++){
                printf("%s ", *(usedWords + i));
            }
            printf("\nPlayer %d's Turn", playerTurn + 1);
            printf("\nEnter a Word. You have 4 minutes. '/' if you want to pass.\n");
            if (passes == 2) { printf("You don't have to start your word with any specific letter(s)\n"); }
            // Player Turn
            if (playerTurn == 0) { scanf("%s", entry); }
            // CPU Turn
            else{ 
                strcpy(entry, getCPUWord(cpuGuesses));
                printf("%s\n", entry);
                cpuGuesses++; 
            }

            // Pass
            if (strcmp(entry, "/") == 0){
                passes++;
            }

            // Word Entered
            else {
                if (numWords == 0 || passes == 2) { giveScore = isValidWordFirstAndScore(entry, validLetters, usedWords); }         
                else { giveScore = isValidWordAndScore(usedWords[numWords - 1], entry, validLetters, usedWords); }                  
                passes = 0;
                // If word was valid
                if (giveScore >= 0){
                    failedGuesses = 0;
                    if (checkFile(entry, filename) == 0){
                        giveScore += 5;
                        players[playerTurn].wordsAdded++; 
                    }
                    players[playerTurn].wordsFound++;
                    strcpy(storage[numWords], entry);
                    usedWords[numWords] = storage[numWords];
                    numWords++;
                }
                printf("\nScore for word: %d\n", giveScore);
                players[playerTurn].score += giveScore;
                if (giveScore < 0){
                    failedGuesses++;
                    continue; 
                }
            }
            
            // Swap Player Turn
            if (playerTurn == 0) { playerTurn = 1; }
            else { playerTurn = 0; }
        }
    }


    // Multiplayer
    else if (gamemode == 2){
        printf("\nMulti Player Game %d\n", gamemode);
        printf("Enter Player 2's first name: ");
        scanf("%s", players[1].firstname);
        printf("Enter Player 2's last name: ");
        scanf("%s", players[1].lastname);
        printf("Enter Player 2's country: ");
        scanf("%s", players[1].country);

        while (passes < 4){
            if (failedGuesses == 3){
                printf("Too many invalid guesses. Passing\n");
                passes++;
                if (playerTurn == 0) { playerTurn = 1; }
                else { playerTurn = 0; }
                failedGuesses = 0;
                continue;
            }

            printf("\nLetters: %s", validLetters);
            printf("\nPlayer 1 Score: %d", players[0].score);
            printf("\nPlayer 2 Score: %d\nUsed Words: ", players[1].score);
            for (int i = 0; *(usedWords + i) != NULL; i++){
                printf("%s ", *(usedWords + i));
            }
            printf("\nPlayer %d's Turn", playerTurn + 1);
            printf("\nEnter a Word. You have 4 minutes. '/' if you want to pass.\n");
            if (passes == 2) { printf("You don't have to start your word with any specific letter(s)\n"); }
            scanf("%s", entry);

            // Pass
            if (strcmp(entry, "/") == 0){
                passes++;
            }

            // Word Entered
            else {
                if (numWords == 0 || passes == 2) { giveScore = isValidWordFirstAndScore(entry, validLetters, usedWords); }         
                else { giveScore = isValidWordAndScore(usedWords[numWords - 1], entry, validLetters, usedWords); }                  
                passes = 0;
                // If word was valid
                if (giveScore >= 0){
                    if (checkFile(entry, filename) == 0){

                        giveScore += 5;
                        players[playerTurn].wordsAdded++; 
                    }
                    players[playerTurn].wordsFound++;
                    strcpy(storage[numWords], entry);
                    usedWords[numWords] = storage[numWords];
                    numWords++;
                }
                printf("\nScore for word: %d\n", giveScore);
                players[playerTurn].score += giveScore;
                if (giveScore < 0){
                    failedGuesses++;
                    continue; 
                }
            }
            
            // Swap Player Turn
            if (playerTurn == 0) { playerTurn = 1; }
            else { playerTurn = 0; }
        }
    }


    // Game End
    if (players[0].score > players[1].score){
        strcpy(players[0].outcome, "Win");
        strcpy(players[1].outcome, "Lose");
        printf("Player 1 Wins!\n%s\t%s\t%s\t%d\t%s\t%d\t%d", players[0].firstname, players[0].lastname, players[0].country, players[0].score,
            players[0].outcome, players[0].wordsFound, players[0].wordsAdded);
    }
    else{
        strcpy(players[1].outcome, "Win");
        strcpy(players[0].outcome, "Lose");
        printf("Player 2 Wins!\n%s\t%s\t%s\t%d\t%s\t%d\t%d", players[1].firstname, players[1].lastname, players[1].country, players[1].score,
        players[1].outcome, players[1].wordsFound, players[1].wordsAdded);
    }

    free(usedWords);
    free(players);
}
// =============================================================================================================================================================================================================



// Selects a random input_XX.txt to use for the input file of the game.
char* randomFile(){
    int r = rand() % 9;
    char* result = names[r];
    return result;
}



// Checks to see if the word given is in the file given. This works for both the input files and the dictionary. Returns 5 if true, 0 if false.
int checkFile(char* word, char* filename){
    FILE* dict;
    dict = fopen(filename, "r");
    char checkWord[20];
    int check = 0;
    // Skips the first line of an input_XX.txt file
    if (filename[0] == 'i'){
        fgets(checkWord, 20, dict);
    }
    while (fgets(checkWord, 20, dict) && check == 0){
        // Removes the \n at the ends of some words from fgets()
        if (checkWord[strlen(checkWord) - 1] == '\n'){
            checkWord[strlen(checkWord) - 1] = '\0';
        }
        if (strcasecmp(word, checkWord) == 0){
            check = 5;
        }
    }

    fclose(dict);
    return check;
}



// Writes all words from selected input_XX.txt to an array every pointer can access.
void getFileWords(char* filename){
    FILE* dict;
    dict = fopen(filename, "r");
    char hold[30];
    int i = 0;
    fgets(hold, 20, dict);
    fgets(hold, 20, dict);
    fgets(hold, 20, dict);
    while (fgets(hold, 20, dict)){
        if (hold[strlen(hold) - 1] == '\n'){
            hold[strlen(hold) - 1] = '\0';
        }
        strcpy(fileWords[i], hold);
        i++;
        fileWordsLength++;
    }

    fclose(dict);
}



// Checks if the new word inputted is valid. This includes checking if the new word contains the only the letters specified from the input file, the word starts with
// the last letters of the previous word, and that the word is in the dictionary. Returns -1 if not valid, and -2 if the word has been used before. 
int isValidWordAndScore(char* prev, char* new, char* letters, char** used){
    int multicheck = 0;
    // Checks if new word uses the last letter(s) of the previous word.
    int check = 0;
    for (int i = 0; i < strlen(prev) && i < strlen(new); i++){
        check = 0;
        for (int j = 0; j <= i; j++){
            if (tolower(prev[strlen(prev) - 1 - i + j]) == tolower(new[j])){
                check++;
            }
            if (check == i + 1){
                multicheck++;
            }
            
        }
    }
    if (multicheck == 0){
        printf("Word does not start with the last letter of the previous word '%s'. Invaid Word.", prev);
        return -1;
    }

    // Checks if new word is in dictionary.txt.
    check = checkFile(new, "dictionary.txt");
    if (check == 5) { 
        multicheck++; 
    }
    else {
        printf("Word is not present in dictionary.txt. Invalid Word.");     
        return -1; 
    }

    // Checks if new word only consists of the valid letters given by the input file.
    for (int i = 0; i < strlen(new); i++){
        check = 0;
        for (int j = 0; j < strlen(letters); j++){
            if (tolower(new[i]) == tolower(letters[j])){
                check = 1;
                j = strlen(letters);
            }
        }
        if (check == 0){
            printf("Word does not only consist of letters available. Invalid Word.");
            return -1;
        }
    }
    
    // Word has passed initial validty check. Now check if the word has been used already.
    check = hasBeenUsed(new, used);
    if (check == 1){
        printf("Word has already been used. -2 point penalization.");
        return -2;
    }

    // Word is validated. Return value of word.
    return scoring(new);
}



// Checks if the new word inputted is valid. This is same as the function above, except without the previous word check. This is for the first word in a game,
// or when each player passes once and the previous word check is not needed.
int isValidWordFirstAndScore(char* new, char* letters, char** used){
    int multicheck = 0, check;

    // Checks if new word is in dictionary.txt.
    check = checkFile(new, "dictionary.txt");
    if (check == 5) { 
        multicheck++; 
    }
    else {
        printf("Word is not present in dictionary.txt. Invalid Word.");     
        return -1; 
    }

    // Checks if new word only consists of the valid letters given by the input file.
    for (int i = 0; i < strlen(new); i++){
        check = 0;
        for (int j = 0; j < strlen(letters); j++){
            if (tolower(new[i]) == tolower(letters[j])){
                check = 1;
                j = strlen(letters);
            }
        }
        if (check == 0){
            printf("Word does not only consist of letters available. Invalid Word.");
            return -1;
        }
    }
    
    // Word has passed initial validty check. Now check if the word has been used already.
    check = hasBeenUsed(new, used);
    if (check == 1){
        printf("Word has already been used. -2 point penalization.");
        return -2;
    }

    // Word is validated. Return value of word.
    return scoring(new);
}



// Checks if the new word has been used before in the game. Returns 1 if true, 0 if false.
int hasBeenUsed(char* new, char** words){
    for (int i = 0; *(words + i) != NULL; i++){
        if (strcasecmp(new, *(words + i)) == 0){
            return 1;
        }
    }
    return 0;
}



// Returns the score value for a word that is valid.
int scoring(char* word){
    int j = strlen(word);
    if (j == 3 || j == 4){
        return 1;
    }
    else if (j == 5){
        return 2;
    }
    else if (j == 6){
        return 3;
    }
    else if (j == 7){
        return 5;
    }
    else if (j > 7){
        return 11;
    }
    else{
        return 0;
    }
}




// Returns a random word from the input_XX.file for the CPU to use as an input. Limits the CPUs number of guess to 8.
char* getCPUWord(int numGuesses){
    if (numGuesses > 8) { return "/"; }
    else {
        int r = rand() % (fileWordsLength - 1);
        char* result = fileWords[r];
        return result;
    }
}
