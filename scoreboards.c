//mini_group_project_Keenan_Holsapple_Scoreboards.c
/*BRIEF DESCRIPTION
 * Management of scoreboard for both single player and multiplayer. This includes reading in the developed user
 * structure, along with the function determining whoWin() returned value. These winning values will be sent to
 * a dedicated text file, and finally returned in a format in the user’s console.
 *
 * THIS FUNCTION WILL OCCUR AFTER THE ROUND HAS BEEN COMPLETED BY AN INDIVIDUAL
 */
/* FUNCTIONS
 * singlePlayerScoreboard() *player
 * multiPlayerScoreboard() *player
 * writeWinsConsoleSingle() void?
 * writeWinsConsoleMulti() void?
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 256
//define player structure
struct player{
    char first_name[20];
    char last_name[20];
    char country[20];
    char outcome[6];
    int score;
    int numWordsFound;
    int numWordsAdded;
};


void displayPlayer(struct player *pPlayer){
    printf("PLAYER DATA");
    printf("\nFirst: %s\n", pPlayer->first_name);
    printf("Last: %s\n", pPlayer->last_name);
    printf("Country: %s\n", pPlayer->country);
    printf("Score: %d\n", pPlayer->score);
    printf("Words Added: %d\n", pPlayer->numWordsAdded);
    printf("Words Found: %d\n", pPlayer->numWordsFound);
}

//sorting algorithm for highest to lowest score
int scoreOrder(int *arr){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(arr[j] < arr[i])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    //pointer issue?
    return *arr;
}

void testFill(){
    char line[6];
    FILE *fptr;
    fptr = fopen("singlePlayer.txt" , "w");


}

void singlePlayerScoreboard(struct player *playerArr, int score, int wordsFound, int wordsAdded){

   //creating singlePlayer.txt
    int num;
    int scoreArr[6];
    char line[100];
    FILE *fptr;

    //begins on read of file to check for score values
    // fptr = fopen("singlePlayer.txt", "r");
    // if(fptr == NULL){
    //     printf("Error locating file singlePlayer.txt");
    // }

    //checks existence of file
    if (fptr = fopen("singlePlayer.txt", "r"))
    {
        
        fclose(fptr);
    }
    //file does not exist; create file with template
    else{

        printf("Creating new file...\n");
        fptr = fopen("singlePlayer.txt", "w");
        fprintf(fptr, "%s", "\tFirst name\t|");
        fprintf(fptr, "%s", "\tLast name\t|");
        fprintf(fptr, "%s", "\tCountry    |");
        fprintf(fptr, "%s", " Score |");
        fprintf(fptr, "%s", " Number of Players |");
        fprintf(fptr, "%s\n", " Number of Rounds");
        fprintf(fptr, "----------------------------------------------------------------------------------------------------------------\n");
        printf("File has been created. Ready to add/change data.");
    }
    //SCORE COMPARISON
    //reading in lines for score array in comparison
    for(int i = 0; i < 5; i++){
        //fscanf(fptr, "whatever format for score", scoreArr[i]);
    }
    //adding in final score value to final index
    scoreArr[6] = score;
    scoreOrder(scoreArr);   
 


    // fscanf(fptr, "%s", line);
    // printf("%s", &line[0]);
}

//demo driver for testing sequence, not for later use
int main() {

    //driver player values for testing
    struct player *testPlayer = malloc(5000);
    strcpy(testPlayer->first_name, "Keenan");
    strcpy(testPlayer->last_name, "Holsapple");
    strcpy(testPlayer->country, "USA");
    strcpy(testPlayer->outcome, "Win");
    testPlayer->score = 12;
    testPlayer->numWordsAdded = 3;
    testPlayer->numWordsFound = 2;

    displayPlayer(testPlayer);
    singlePlayerScoreboard(testPlayer, 1, 2, 3);

//    singlePlayerScoreboard(testPlayer, 13, 3, 2);
    return 0;
}

