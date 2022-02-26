/*
Group Number: C
Group Member: Cameron Stalcup
Email: cameron.stalcup@okstate.edu
Date: 2/24/2022
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
int isValidWordFirstAndScore(char* new, char* letters, char** used);
int hasBeenUsed(char* new, char** words);
int scoring(char* word);


char names[10][13] = {"input_01.txt", "input_02.txt", "input_03.txt",
        "input_04.txt", "input_05.txt", "input_06.txt", "input_07.txt",
        "input_08.txt", "input_09.txt", "input_10.txt"};
player P1, P2, CPU;


int main(){
    strcpy(CPU.firstname, "Computer");
    strcpy(CPU.lastname, "Player");
    strcpy(CPU.country, "N/A");
    
    char word1[10] = "errand";
    char word2[10] = "random";

    wordProcessing(1);
}


// =============================================================================================================================================================================================================
// Starts the game. gamemode refers to single player of multi player. 1 for Single, 2 for Multi.
void wordProcessing(int gamemode){
    int giveScore, passes = 0;
    char entry[20];
    // Gets the letters from the first line of each input_XX.txt
    srand(time(NULL));
    FILE* fp;
    // char* filename = randomFile();
    char* filename = "input_02.txt";
    fp = fopen(filename, "r");
    char validLetters[20];
    fgets(validLetters, 20, fp);
    if (validLetters[strlen(validLetters) - 1] == '\n'){
        validLetters[strlen(validLetters) - 1] = '\0';
    }
    fclose(fp);

    // Makes array of strings for words used in the game. 
    char** usedWords;
    usedWords = (char**)calloc(30, sizeof(char*));
    for (int i = 0; i < 30; i++){
        *(usedWords + i) = NULL;
    }
    usedWords[0] = "neon";
    usedWords[1] = "conten";

    // Multiplayer
    printf("Letters: %s \nEnter a word: ", validLetters);
    scanf("%s", entry);
    giveScore = isValidWordAndScore("once", entry, validLetters, usedWords);
    if (giveScore >= 0){
        if (checkFile("yellow", filename) == 0){
            giveScore += 5; 
        }
    }
    printf("\nScore for word: %d", giveScore);

    free(usedWords);
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
        printf("\nWord does not start with the last letter of the previous word '%s'. Invaid Word.", prev);
        return -1;
    }

    // Checks if new word is in dictionary.txt.
    check = checkFile(new, "dictionary.txt");
    if (check == 5) { 
        multicheck++; 
    }
    else {
        printf("\nWord is not present in dictionary.txt. Invalid Word.");     
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
            printf("\nWord does not only consist of letters available. Invalid Word.");
            return -1;
        }
    }
    
    // Word has passed initial validty check. Now check if the word has been used already.
    check = hasBeenUsed(new, used);
    if (check == 1){
        printf("\nWord has already been used. -2 point penalization.");
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
        printf("\nWord is not present in dictionary.txt. Invalid Word.");     
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
            printf("\nWord does not only consist of letters available. Invalid Word.");
            return -1;
        }
    }
    
    // Word has passed initial validty check. Now check if the word has been used already.
    check = hasBeenUsed(new, used);
    if (check == 1){
        printf("\nWord has already been used. -2 point penalization.");
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

