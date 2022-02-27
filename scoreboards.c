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

void writeSingleTableHeader(char* filename){
        
        FILE* file = fopen(filename,"w");
        
        printf("Creating new file...\n");
        file = fopen("singlePlayer.txt", "w");
        fprintf(file, "%s", "\tFirst name\t|");
        fprintf(file, "%s", "\tLast name\t|");
        fprintf(file, "%s", "\tCountry   |");
        fprintf(file, "%s", " Score |");
        fprintf(file, "%s", " Number of Words Found |");
        fprintf(file, "%s\n", " Number of Added to Dictionary");
        fprintf(file , "-----------------------------------------------------------------------------------------------------------------------------\n");
        printf("File has been created. Ready to add/change data.\n");
        printf("Beginning revisions...");
        fclose(file);
}

void singlePlayerBuild(){

}
//function to read scores to add to array
void readScoresSingle(char* filename, int score, struct player* newPlayer){
    FILE* file = fopen(filename,"r");
    int i = 0;

    char first_name[20];
    char last_name[20];
    char country[20];
    int numWordsFound;
    int numWordsAdded;
    int scoreArr[5];
    int arrIndex = 0;

    struct player *p1 = malloc(1000);
    struct player *p2 = malloc(1000);
    struct player *p3 = malloc(1000);
    struct player *p4 = malloc(1000);
    struct player *p5 = malloc(1000);

    //skips first two lines
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%*[^\n]\n");

    //while loop to find values
    while (!feof (file)){
        //skips existing string values
        fscanf(file, "%s%s%s%d%d%d", first_name, last_name, country, &i, &numWordsFound, &numWordsAdded);
        printf("%d", i);
        scoreArr[arrIndex] = i;

        //storing all players data into player structures
        switch(arrIndex){
            case 0:
                strcpy(p1->first_name, first_name);
                strcpy(p1->last_name, last_name);
                strcpy(p1->country, country);
                p1->score = i;
                p1->numWordsAdded = numWordsFound;
                p1->numWordsFound = numWordsAdded;
                break;
            case 1:
                strcpy(p2->first_name, first_name);
                strcpy(p2->last_name, last_name);
                strcpy(p2->country, country);
                p2->score = i;
                p2->numWordsAdded = numWordsFound;
                p2->numWordsFound = numWordsAdded;
                break;   
            case 2:    
                strcpy(p3->first_name, first_name);
                strcpy(p3->last_name, last_name);
                strcpy(p3->country, country);
                p3->score = i;
                p3->numWordsAdded = numWordsFound;
                p3->numWordsFound = numWordsAdded;
                break;
            case 3:
                strcpy(p4->first_name, first_name);
                strcpy(p4->last_name, last_name);
                strcpy(p4->country, country);
                p4->score = i;
                p4->numWordsAdded = numWordsFound;
                p4->numWordsFound = numWordsAdded;
                break;
            case 4:
                strcpy(p5->first_name, first_name);
                strcpy(p5->last_name, last_name);
                strcpy(p5->country, country);
                p5->score = i;
                p5->numWordsAdded = numWordsFound;
                p5->numWordsFound = numWordsAdded;
                break;             
        }

        //increase count for array index
        arrIndex++;   
    }

    //initilizing final index
    scoreArr[5] = newPlayer->score;
    fclose(file);

    //sorting array in ascending order
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(scoreArr[j] < scoreArr[i])
            {   

                //score array has been sorted
                int temp = scoreArr[i];
                scoreArr[i] = scoreArr[j];
                scoreArr[j] = temp;
            }
        }
    }

    //arranging placements
    writeSingleTableHeader(filename);


    file = fopen("singlePlayer.txt","a");
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%*[^\n]\n");

    //placing in order depending on score array placement
    for(int i = 0; i < 6; i++){
        if(scoreArr[i] == p1->score){
            fprintf(file, "\t%s\t", p1->first_name);
            fprintf(file, "\t%s\t", p1->last_name);
            fprintf(file, "\t%s\t", p1->country);
            fprintf(file, "\t%d\t", p1->score);
            fprintf(file, "\t%d\t", p1->numWordsFound);
            fprintf(file, "\t%d\n", p1->numWordsAdded);
        }
        if(scoreArr[i] == p2->score){
            fprintf(file, "\t%s\t", p2->first_name);
            fprintf(file, "\t%s\t", p2->last_name);
            fprintf(file, "\t%s\t", p2->country);
            fprintf(file, "\t%d\t", p2->score);
            fprintf(file, "\t%d\t", p2->numWordsFound);
            fprintf(file, "\t%d\n", p2->numWordsAdded);
        }
        if(scoreArr[i] == p3->score){
            fprintf(file, "\t%s\t", p3->first_name);
            fprintf(file, "\t%s\t", p3->last_name);
            fprintf(file, "\t%s\t", p3->country);
            fprintf(file, "\t%d\t", p3->score);
            fprintf(file, "\t%d\t", p3->numWordsFound);
            fprintf(file, "\t%d\n", p3->numWordsAdded);
        }
        if(scoreArr[i] == p4->score){
            fprintf(file, "\t%s\t", p4->first_name);
            fprintf(file, "\t%s\t", p4->last_name);
            fprintf(file, "\t%s\t", p4->country);
            fprintf(file, "\t%d\t", p4->score);
            fprintf(file, "\t%d\t", p4->numWordsFound);
            fprintf(file, "\t%d\n", p4->numWordsAdded);
        }
        if(scoreArr[i] == p5->score){
            fprintf(file, "\t%s\t", p5->first_name);
            fprintf(file, "\t%s\t", p5->last_name);
            fprintf(file, "\t%s\t", p5->country);
            fprintf(file, "\t%d\t", p5->score);
            fprintf(file, "\t%d\t", p5->numWordsFound);
            fprintf(file, "\t%d\n", p5->numWordsAdded);
        }
        if(scoreArr[i] == newPlayer->score){
            fprintf(file, "\t%s\t", newPlayer->first_name);
            fprintf(file, "\t%s\t", newPlayer->last_name);
            fprintf(file, "\t%s\t", newPlayer->country);
            fprintf(file, "\t%d\t", newPlayer->score);
            fprintf(file, "\t%d\t", newPlayer->numWordsFound);
            fprintf(file, "\t%d\n", newPlayer->numWordsAdded);
        }
    }



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


//single player function for swapping values
// void singleScoreboardPlacements(int *arr,char* filename){
//     FILE* file = fopen(filename,"w");
//     char line[1000];
//     fscanf(file, "%*[^\n]\n");
//     fscanf(file, "%*[^\n]\n");
//     int i = 0;


//     while(fgets(line, sizeof(line), file) != NULL){
//         fputs()        
//     }
// }

/*singlePlayerScoreboard()
* 1. Checks for/creates scoreboard text file
* 2. Reads for score values and stores into array
* 3. Sorts array in descending order
* 4. Performs swap for locations in file
*/
void singlePlayerScoreboard(struct player *playerArr, int score, int wordsFound, int wordsAdded){

   //creating singlePlayer.txt
    FILE *singlefptr;

    //checks existence of file
    if (singlefptr = fopen("singlePlayer.txt", "r"))
    {
        printf("File already exists, beginning revisions...");        
        fclose(singlefptr);
    }
    //file does not exist; create file with template
    else{
        writeSingleTableHeader("singlePlayer.txt");

    }
    //SCORE COMPARISON
    //reading in lines for score array in comparison
    for(int i = 0; i < 5; i++){
        //fscanf(fptr, "whatever format for score", scoreArr[i]);
    }
    //adding in final score value to final index
    readScoresSingle("singlePlayer.txt", score, playerArr);

    
    //arranging the order of the array
    



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

    singlePlayerScoreboard(testPlayer, 1, 2, 3);

    return 0;
}
