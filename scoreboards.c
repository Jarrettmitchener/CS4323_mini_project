//mini_group_project_Keenan_Holsapple_Scoreboards.c
/*BRIEF DESCRIPTION
 * Management of scoreboard for both single player and multiplayer. This includes reading in the developed user
 * structure, along with the function determining whoWin() returned value. These winning values will be sent to
 * a dedicated text file, and finally returned in a format in the user’s console.
 *
 * THIS FUNCTION WILL OCCUR AFTER THE ROUND HAS BEEN COMPLETED BY AN INDIVIDUAL
 */
/* FUNCTIONS
 * singlePlayerScoreboard() void
 * multiPlayerScoreboard() void
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

//player structure test view function
void displayPlayer(struct player *pPlayer){
    printf("PLAYER DATA");
    printf("\nFirst: %s\n", pPlayer->first_name);
    printf("Last: %s\n", pPlayer->last_name);
    printf("Country: %s\n", pPlayer->country);
    printf("Score: %d\n", pPlayer->score);
    printf("Words Added: %d\n", pPlayer->numWordsAdded);
    printf("Words Found: %d\n", pPlayer->numWordsFound);
}

//function to read scores to add to array
//POINTER ISSUE
int *readScoresSingle(char* filename){
    FILE* file = fopen(filename,"r");
    int i = 0;

    char first_name[20];
    char last_name[20];
    char country[20];
    int *scoreArr[5];
    int arrIndex = 0;

    //skips first two lines
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%*[^\n]\n");

    //while loop to find values
    while (!feof (file)){
        //skips existing string values
        fscanf(file, "%s%s%s%d", first_name, last_name, country, &i);
        printf("%d", i);
        scoreArr[arrIndex] = &i;

        arrIndex++;   
    }

    //initilizing final index
    scoreArr[5] = 0;
    fclose(file);

    //return array to singlePlayer function
    return *scoreArr;
}

//function to read scores to add to array for multi
//POINTER ISSUE
int *readScoresMulti(char* filename){
    FILE* file = fopen(filename,"r");
    int i = 0;

    char first_name[20];
    char last_name[20];
    char country[20];
    char outcome[6];
    int *scoreArr[5];
    int arrIndex = 0;

    //skips first two lines
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%*[^\n]\n");

    //while loop to find values
    while (!feof (file)){
        //skips existing string values
        fscanf(file, "%s%s%s%d", first_name, last_name, country, &i);
        printf("%d", i);
        scoreArr[arrIndex] = &i;

        arrIndex++;   
    }

    //initilizing final index
    scoreArr[5] = 0;
    fclose(file);

    //return array to singlePlayer function
    return *scoreArr;
}
//sorting algorithm for highest to lowest score in score array
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

/*singlePlayerScoreboard()
* 1. Checks for/creates scoreboard text file
* 2. Reads for score values and stores into array
* 3. Sorts array in descending order
* 4. Performs swap for locations in file
*/
void singlePlayerScoreboard(struct player *playerArr, int score, int wordsFound, int wordsAdded){

   //creating singlePlayer.txt
    int num;
    int scoreArr[5];
    char line[10];
    FILE *singlefptr;

    //checks existence of file
    if (singlefptr = fopen("singlePlayer.txt", "r"))
    {
        printf("File already exists, beginning revisions...");        
        fclose(singlefptr);
    }
    //file does not exist; create file with template
    else{

        printf("Creating new file...\n");
        singlefptr = fopen("singlePlayer.txt", "w");
        fprintf(singlefptr, "%s", "\tFirst name\t|");
        fprintf(singlefptr, "%s", "\tLast name\t|");
        fprintf(singlefptr, "%s", "\tCountry    |");
        fprintf(singlefptr, "%s", " Score |");
        fprintf(singlefptr, "%s", " Number of Players |");
        fprintf(singlefptr, "%s\n", " Number of Rounds");
        fprintf(singlefptr, "----------------------------------------------------------------------------------------------------------------\n");
        printf("File has been created. Ready to add/change data.\n");
        printf("Beginning revisions...");
    }
    //SCORE COMPARISON
    //reading in lines for score array in comparison
    for(int i = 0; i < 5; i++){
        //fscanf(fptr, "whatever format for score", scoreArr[i]);
    }
    //adding in final score value to final index
    //POINTER ISSUE
    scoreArr = readScoresSingle("singlePlayer.txt");
    scoreArr[6] = score;
    scoreOrder(scoreArr);   
    
    //getw and putw for get and put of int
    //fgets and fputs for get and put of strings


    // fscanf(fptr, "%s", line);
    // printf("%s", &line[0]);
}

/*multiPlayerScoreboard()
* same as singlePlayer, just different file with addition of structure attribute for win/loss
* 1. Checks for/creates scoreboard text file
* 2. Reads for score values and stores into array
* 3. Sorts array in descending order
* 4. Performs swap for locations in file
*/
void multiPlayerScoreboard(struct player *playerArr, int score, int wordsFound, int wordsAdded){

    FILE *multifptr;
      //creating singlePlayer.txt
    int num;
    int scoreArr[5];
    char line[10];

    //checks existence of file
    if (multifptr = fopen("multiPlayer.txt", "r"))
    {
        printf("File already exists, beginning revisions...");        
        fclose(multifptr);
    }
    //file does not exist; create file with template
    else{

        printf("Creating new file...\n");
        multifptr = fopen("singlePlayer.txt", "w");
        fprintf(multifptr, "%s", "\tFirst name\t|");
        fprintf(multifptr, "%s", "\tLast name\t|");
        fprintf(multifptr, "%s", "\tCountry    |");
        fprintf(multifptr, "%s", " Score |");
        fprintf(multifptr, "%s", "\tWin/lose\t|");
        fprintf(multifptr, "%s", " Number of Players |");
        fprintf(multifptr, "%s\n", " Number of Rounds");
        fprintf(multifptr, "---------------------------------------------------------------------------------------------------------------------------\n");
        printf("File has been created. Ready to add/change data.\n");
        printf("Beginning revisions...");
    }
    //SCORE COMPARISON
    //reading in lines for score array in comparison
    for(int i = 0; i < 5; i++){
        //fscanf(fptr, "whatever format for score", scoreArr[i]);
    }
    //adding in final score value to final index
    //POINTER ISSUE
    scoreArr = readScoresSingle("singlePlayer.txt");
    scoreArr[6] = score;
    scoreOrder(scoreArr);   
    
    //getw and putw for get and put of int
    //fgets and fputs for get and put of strings


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
