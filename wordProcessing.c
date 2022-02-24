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
int isValidWord(char* prev, char* new, char* letters);
int checkFile(char* word, char* filename);
int isValidWordFirst(char* new, char* letters);

char names[10][13] = {"input_01.txt", "input_02.txt", "input_03.txt",
        "input_04.txt", "input_05.txt", "input_06.txt", "input_07.txt",
        "input_08.txt", "input_09.txt", "input_10.txt"};


int main(){

    player P1, P2, CPU;
    // strcpy(P1.firstname, "Michael");
    // strcpy(P1.lastname, "Bay");
    // strcpy(P1.country, "USA");
    // strcpy(P2.firstname, "Frank");
    // strcpy(P2.lastname, "Sinatra");
    // strcpy(P2.country, "Brazil");
    strcpy(CPU.firstname, "Computer");
    strcpy(CPU.lastname, "Player");
    strcpy(CPU.country, "N/A");
    
    char word1[10] = "errand";
    char word2[10] = "random";

    // printf("Length: %d", )

    wordProcessing();
    
}


// Where everything is going to happen.
void wordProcessing(){
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
    

    char usedWords[25][30];
    printf("\nThis function works %d", usedWords);
}


// Selects a random .txt to use for the input file of the game.
char* randomFile(){
    int r = rand() % 9;
    char* result = names[r];
    return result;
}


// Checks to see if the word given is in the file given. This works for both the input files and the dictionary. Returns 1 if true, 0 if false.
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
            check = 1;
        }
    }

    fclose(dict);
    return check;
}


// Checks if the new word inputted is valid. This includes checking if the new word contains the only the letters specified from the input file, the word starts with
// the last letters of the previous word, and that the word is in the dictionary. Returns 1 if true, 0 if false. 
int isValidWord(char* prev, char* new, char* letters){
    int multicheck = 0;

    // Checks if new word uses the last letter(s) of the previous word.
    int check = 0;
    for (int i = 0; i < strlen(prev) && i < strlen(new); i++){
        check = 0;
        for (int j = 0; j <= i; j++){
            if (prev[strlen(prev) - 1 - i + j] == new[j]){
                check++;
            }
            if (check == i + 1){
                multicheck++;
            }
            
        }
    }
    if (multicheck == 0){
        printf("\nWord does not start with the last letter of the previous word. Invaid Word.");
        return 0;
    }

    // Checks if new word is in dictionary.txt.
    check = checkFile(new, "dictionary.txt");
    if (check == 1) { 
        multicheck++; 
    }
    else {
        printf("\nWord is not present in dictionary.txt. Invalid Word.");     
        return 0; 
    }

    // Checks if new word only consists of the valid letters given by the input file.
    for (int i = 0; i < strlen(new); i++){
        check = 0;
        for (int j = 0; j < strlen(letters); j++){
            if (new[i] == letters[j]){
                check = 1;
                j = strlen(letters);
            }
        }
        if (check == 0){
            printf("\nWord does not only consist of letters available. Invalid Word.");
            return 0;
        }
    }
    multicheck++;
    return multicheck - 2;
}


// Checks if the new word inputted is valid. This is same as the function above, except without the previous word check. This is for the first word in a game,
// or when each player passes once and the previous word check is not needed.
int isValidWordFirst(char* new, char* letters){
    int multicheck = 0, check;

    // Checks if new word is in dictionary.txt.
    check = checkFile(new, "dictionary.txt");
    if (check == 1) { 
        multicheck++; 
    }
    else {
        printf("\nWord is not present in dictionary.txt. Invalid Word.");     
        return 0; 
    }

    // Checks if new word only consists of the valid letters given by the input file.
    for (int i = 0; i < strlen(new); i++){
        check = 0;
        for (int j = 0; j < strlen(letters); j++){
            if (new[i] == letters[j]){
                check = 1;
                j = strlen(letters);
            }
        }
        if (check == 0){
            printf("\nWord does not only consist of letters available. Invalid Word.");
            return 0;
        }
    }
    multicheck++;
    return multicheck - 1;
}
