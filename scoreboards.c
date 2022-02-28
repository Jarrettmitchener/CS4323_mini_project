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

void initializeTable(char* filename){
        
        FILE* file = fopen(filename,"w");

        file = fopen("singlePlayer.txt", "w");
        fprintf(file, "%s", "\tFirst name\t|");
        fprintf(file, "%s", "\tLast name\t|");
        fprintf(file, "%s", "\tCountry   |");
        fprintf(file, "%s", " Score |");
        fprintf(file, "%s", " Number of Words Found |");
        fprintf(file, "%s\n", " Number of Added to Dictionary");
        fprintf(file , "-----------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(file, "\t%s\t", "Zhao");
        fprintf(file, "\t%s\t", "Bao");
        fprintf(file, "\t%s\t", "China");
        fprintf(file, "\t%d\t", 34);
        fprintf(file, "\t%d\t", 7);
        fprintf(file, "\t%d\n", 2);
        fprintf(file, "\t%s\t", "Nakano");
        fprintf(file, "\t%s\t", "Tsutomu");
        fprintf(file, "\t%s\t", "Japan");
        fprintf(file, "\t%d\t", 32);
        fprintf(file, "\t%d\t", 8);
        fprintf(file, "\t%d\n", 9);
        fprintf(file, "\t%s\t", "Felicjan");
        fprintf(file, "\t%s\t", "Wos");
        fprintf(file, "\t%s\t", "Poland");
        fprintf(file, "\t%d\t", 31);
        fprintf(file, "\t%d\t", 9);
        fprintf(file, "\t%d\n", 1);
        fprintf(file, "\t%s\t", "Kapsar");
        fprintf(file, "\t%s\t", "Zimmermann");
        fprintf(file, "\t%s\t", "Germany");
        fprintf(file, "\t%d\t", 30);
        fprintf(file, "\t%d\t", 11);
        fprintf(file, "\t%d\n", 0);
        fprintf(file, "\t%s\t", "Karina");
        fprintf(file, "\t%s\t", "Maynard");
        fprintf(file, "\t%s\t", "USA");
        fprintf(file, "\t%d\t", 30);
        fprintf(file, "\t%d\t", 10);
        fprintf(file, "\t%d\n", 0);
        printf("File has been created. Ready to add/change data.");
        fclose(file);
}

void initializeMultiTable(char* filename){
        
        FILE* file = fopen(filename,"w");

        file = fopen("multiPlayer.txt", "w");
        fprintf(file, "%s", "\tFirst name\t|");
        fprintf(file, "%s", "\tLast name\t|");
        fprintf(file, "%s", "\tCountry   |");
        fprintf(file, "%s", " Score |");
        fprintf(file, "%s", "  Win/lose  |");
        fprintf(file, "%s", " Number of Words Found |");
        fprintf(file, "%s\n", " Number of Added to Dictionary");
        fprintf(file , "-----------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(file, "\t%s\t", "Zhao");
        fprintf(file, "\t%s\t", "Bao");
        fprintf(file, "\t%s\t", "China");
        fprintf(file, "\t%d\t", 34);
        fprintf(file, "\t%s\t", "Win");
        fprintf(file, "\t%d\t", 7);
        fprintf(file, "\t%d\n", 2);
        fprintf(file, "\t%s\t", "Nakano");
        fprintf(file, "\t%s\t", "Tsutomu");
        fprintf(file, "\t%s\t", "Japan");
        fprintf(file, "\t%d\t", 32);
        fprintf(file, "\t%s\t", "Win");
        fprintf(file, "\t%d\t", 8);
        fprintf(file, "\t%d\n", 9);
        fprintf(file, "\t%s\t", "Felicjan");
        fprintf(file, "\t%s\t", "Wos");
        fprintf(file, "\t%s\t", "Poland");
        fprintf(file, "\t%d\t", 31);
        fprintf(file, "\t%s\t", "Loss");
        fprintf(file, "\t%d\t", 9);
        fprintf(file, "\t%d\n", 1);
        fprintf(file, "\t%s\t", "Kapsar");
        fprintf(file, "\t%s\t", "Zimmermann");
        fprintf(file, "\t%s\t", "Germany");
        fprintf(file, "\t%d\t", 30);
        fprintf(file, "\t%s\t", "Win");
        fprintf(file, "\t%d\t", 11);
        fprintf(file, "\t%d\n", 0);
        fprintf(file, "\t%s\t", "Karina");
        fprintf(file, "\t%s\t", "Maynard");
        fprintf(file, "\t%s\t", "USA");
        fprintf(file, "\t%d\t", 30);
        fprintf(file, "\t%s\t", "Win");
        fprintf(file, "\t%d\t", 10);
        fprintf(file, "\t%d\n", 0);
        printf("File has been created. Ready to add/change data.");
        fclose(file);
}


//function to read scores to add to array
void readScoresSingle(char* filename,struct player* newPlayer){
    
    //reading in
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

    file = fopen("singlePlayer.txt", "w");
    fprintf(file, "%s", "\tFirst name\t|");
    fprintf(file, "%s", "\tLast name\t|");
    fprintf(file, "%s", "\tCountry   |");
    fprintf(file, "%s", " Score |");
    fprintf(file, "%s", " Number of Words Found |");
    fprintf(file, "%s\n", " Number of Added to Dictionary");
    fprintf(file , "-----------------------------------------------------------------------------------------------------------------------------\n");

    char flagname[20] = "";

    //placing in order depending on score array placement
    for(int i = 0; i < 5; i++){
 
        if(scoreArr[i] == p1->score && (strcmp(p1->first_name, flagname) < 0 || strcmp(p1->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p1->first_name);
            fprintf(file, "\t%s\t", p1->last_name);
            fprintf(file, "\t%s\t", p1->country);
            fprintf(file, "\t%d\t", p1->score);
            fprintf(file, "\t%d\t", p1->numWordsFound);
            fprintf(file, "\t%d\n", p1->numWordsAdded);
            strcpy(flagname, p1->first_name);
            printf("\n%s", flagname);

            continue;
        }
        if(scoreArr[i] == p2->score && (strcmp(p2->first_name, flagname) < 0 || strcmp(p2->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p2->first_name);
            fprintf(file, "\t%s\t", p2->last_name);
            fprintf(file, "\t%s\t", p2->country);
            fprintf(file, "\t%d\t", p2->score);
            fprintf(file, "\t%d\t", p2->numWordsFound);
            fprintf(file, "\t%d\n", p2->numWordsAdded);
            strcpy(flagname, p2->first_name);
            printf("\n%s", flagname);
            
            continue;
        }
        if(scoreArr[i] == p3->score && (strcmp(p3->first_name, flagname) < 0 || strcmp(p3->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p3->first_name);
            fprintf(file, "\t%s\t", p3->last_name);
            fprintf(file, "\t%s\t", p3->country);
            fprintf(file, "\t%d\t", p3->score);
            fprintf(file, "\t%d\t", p3->numWordsFound);
            fprintf(file, "\t%d\n", p3->numWordsAdded);
            strcpy(flagname, p3->first_name);
            printf("\n%s", flagname);

           continue;
        }
        if(scoreArr[i] == p4->score && (strcmp(p4->first_name, flagname) < 0 || strcmp(p4->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p4->first_name);
            fprintf(file, "\t%s\t", p4->last_name);
            fprintf(file, "\t%s\t", p4->country);
            fprintf(file, "\t%d\t", p4->score);
            fprintf(file, "\t%d\t", p4->numWordsFound);
            fprintf(file, "\t%d\n", p4->numWordsAdded);
            strcpy(flagname, p4->first_name);
            printf("\n%s", flagname);
 
            continue;
        }
        if(scoreArr[i] == p5->score && (strcmp(p5->first_name, flagname) < 0 || strcmp(p5->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p5->first_name);
            fprintf(file, "\t%s\t", p5->last_name);
            fprintf(file, "\t%s\t", p5->country);
            fprintf(file, "\t%d\t", p5->score);
            fprintf(file, "\t%d\t", p5->numWordsFound);
            fprintf(file, "\t%d\n", p5->numWordsAdded);
            strcpy(flagname, p5->first_name);
            printf("\n%s", flagname);

            continue;
        }
        if(scoreArr[i] == newPlayer->score && (strcmp(newPlayer->first_name, flagname) < 0 || strcmp(newPlayer->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", newPlayer->first_name);
            fprintf(file, "\t%s\t", newPlayer->last_name);
            fprintf(file, "\t%s\t", newPlayer->country);
            fprintf(file, "\t%d\t", newPlayer->score);
            fprintf(file, "\t%d\t", newPlayer->numWordsFound);
            fprintf(file, "\t%d\n", newPlayer->numWordsAdded);
            strcpy(flagname, newPlayer->first_name);
            printf("\n%s", flagname);

           continue;
        }
    }

    realloc(p1,1001);
    realloc(p2,1001);
    realloc(p3,1001);
    realloc(p4,1001);
    realloc(p5,1001);

    fclose(file);

}

//function to read scores to add to array for multi
void readScoresMulti(char* filename, struct player* newPlayer){
    
    //reading in
    FILE* file = fopen(filename,"r");
    int i = 0;

    char first_name[20];
    char last_name[20];
    char country[20];
    int numWordsFound;
    int numWordsAdded;
    char outcome[6];
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
        fscanf(file, "%s%s%s%d%s%d%d", first_name, last_name, country, &i, outcome, &numWordsFound, &numWordsAdded);
        scoreArr[arrIndex] = i;

        //storing all players data into player structures
        switch(arrIndex){
            case 0:
                strcpy(p1->first_name, first_name);
                strcpy(p1->last_name, last_name);
                strcpy(p1->country, country);
                p1->score = i;
                strcpy(p1->outcome, outcome);
                p1->numWordsAdded = numWordsFound;
                p1->numWordsFound = numWordsAdded;
                break;
            case 1:
                strcpy(p2->first_name, first_name);
                strcpy(p2->last_name, last_name);
                strcpy(p2->country, country);
                p2->score = i;
                strcpy(p2->outcome, outcome);
                p2->numWordsAdded = numWordsFound;
                p2->numWordsFound = numWordsAdded;
                break;   
            case 2:    
                strcpy(p3->first_name, first_name);
                strcpy(p3->last_name, last_name);
                strcpy(p3->country, country);
                p3->score = i;
                strcpy(p3->outcome, outcome);
                p3->numWordsAdded = numWordsFound;
                p3->numWordsFound = numWordsAdded;
                break;
            case 3:
                strcpy(p4->first_name, first_name);
                strcpy(p4->last_name, last_name);
                strcpy(p4->country, country);
                p4->score = i;
                strcpy(p4->outcome, outcome);
                p4->numWordsAdded = numWordsFound;
                p4->numWordsFound = numWordsAdded;
                break;
            case 4:
                strcpy(p5->first_name, first_name);
                strcpy(p5->last_name, last_name);
                strcpy(p5->country, country);
                p5->score = i;
                strcpy(p5->outcome, outcome);
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

    file = fopen("singlePlayer.txt", "w");
    fprintf(file, "%s", "\tFirst name\t|");
    fprintf(file, "%s", "\tLast name\t|");
    fprintf(file, "%s", "\tCountry   |");
    fprintf(file, "%s", " Score |");
    fprintf(file, "%s", " Number of Words Found |");
    fprintf(file, "%s\n", " Number of Added to Dictionary");
    fprintf(file , "-----------------------------------------------------------------------------------------------------------------------------\n");

    char flagname[20] = "";

    //placing in order depending on score array placement
    for(int i = 0; i < 5; i++){
 
        if(scoreArr[i] == p1->score && (strcmp(p1->first_name, flagname) < 0 || strcmp(p1->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p1->first_name);
            fprintf(file, "\t%s\t", p1->last_name);
            fprintf(file, "\t%s\t", p1->country);
            fprintf(file, "\t%d\t", p1->score);
            fprintf(file, "\t%s\t", p1->outcome);
            fprintf(file, "\t%d\t", p1->numWordsFound);
            fprintf(file, "\t%d\n", p1->numWordsAdded);
            strcpy(flagname, p1->first_name);
            printf("\n%s", flagname);

            continue;
        }
        if(scoreArr[i] == p2->score && (strcmp(p2->first_name, flagname) < 0 || strcmp(p2->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p2->first_name);
            fprintf(file, "\t%s\t", p2->last_name);
            fprintf(file, "\t%s\t", p2->country);
            fprintf(file, "\t%d\t", p2->score);
            fprintf(file, "\t%s\t", p2->outcome);
            fprintf(file, "\t%d\t", p2->numWordsFound);
            fprintf(file, "\t%d\n", p2->numWordsAdded);
            strcpy(flagname, p2->first_name);
            printf("\n%s", flagname);
            
            continue;
        }
        if(scoreArr[i] == p3->score && (strcmp(p3->first_name, flagname) < 0 || strcmp(p3->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p3->first_name);
            fprintf(file, "\t%s\t", p3->last_name);
            fprintf(file, "\t%s\t", p3->country);
            fprintf(file, "\t%d\t", p3->score);
            fprintf(file, "\t%s\t", p3->outcome);
            fprintf(file, "\t%d\t", p3->numWordsFound);
            fprintf(file, "\t%d\n", p3->numWordsAdded);
            strcpy(flagname, p3->first_name);
            printf("\n%s", flagname);

           continue;
        }
        if(scoreArr[i] == p4->score && (strcmp(p4->first_name, flagname) < 0 || strcmp(p4->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p4->first_name);
            fprintf(file, "\t%s\t", p4->last_name);
            fprintf(file, "\t%s\t", p4->country);
            fprintf(file, "\t%d\t", p4->score);
            fprintf(file, "\t%s\t", p4->outcome);
            fprintf(file, "\t%d\t", p4->numWordsFound);
            fprintf(file, "\t%d\n", p4->numWordsAdded);
            strcpy(flagname, p4->first_name);
            printf("\n%s", flagname);
 
            continue;
        }
        if(scoreArr[i] == p5->score && (strcmp(p5->first_name, flagname) < 0 || strcmp(p5->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", p5->first_name);
            fprintf(file, "\t%s\t", p5->last_name);
            fprintf(file, "\t%s\t", p5->country);
            fprintf(file, "\t%d\t", p5->score);
            fprintf(file, "\t%s\t", p5->outcome);
            fprintf(file, "\t%d\t", p5->numWordsFound);
            fprintf(file, "\t%d\n", p5->numWordsAdded);
            strcpy(flagname, p5->first_name);
            printf("\n%s", flagname);

            continue;
        }
        if(scoreArr[i] == newPlayer->score && (strcmp(newPlayer->first_name, flagname) < 0 || strcmp(newPlayer->first_name, flagname) > 0)){
            fprintf(file, "\t%s\t", newPlayer->first_name);
            fprintf(file, "\t%s\t", newPlayer->last_name);
            fprintf(file, "\t%s\t", newPlayer->country);
            fprintf(file, "\t%d\t", newPlayer->score);
            fprintf(file, "\t%s\t", newPlayer->outcome);
            fprintf(file, "\t%d\t", newPlayer->numWordsFound);
            fprintf(file, "\t%d\n", newPlayer->numWordsAdded);
            strcpy(flagname, newPlayer->first_name);
            printf("\n%s", flagname);

           continue;
        }
    }

    fclose(file);


}


/*singlePlayerScoreboard()
* 1. Checks for/creates scoreboard text file
* 2. Reads for score values and stores into array
* 3. Sorts array in descending order
* 4. Performs swap for locations in file
*/
void singlePlayerScoreboard(struct player *playerArr){

   //creating singlePlayer.txt

    //checks existence of file

    //file does not exist; create file with template


    initializeTable("singlePlayer.txt");

    //adding in final score value to final index
    readScoresSingle("singlePlayer.txt", playerArr);

}

/*multiPlayerScoreboard()
* same as singlePlayer, just different file with addition of structure attribute for win/loss
* 1. Checks for/creates scoreboard text file
* 2. Reads for score values and stores into array
* 3. Sorts array in descending order
* 4. Performs swap for locations in file
*/
void multiPlayerScoreboard(struct player *playerArr){

    initializeMultiTable("multiPlayer.txt");

    //adding in final score value to final index
    readScoresMulti("singlePlayer.txt", playerArr);

}

char* single_scoreboardLine(char* filename){
    char* stringLine

}
char* multi_scoreboardLine(){

}


//demo driver for testing sequence, not for later use
int main() {

    //driver player values for testing
    struct player *testPlayer = malloc(1000);
    strcpy(testPlayer->first_name, "Keenan");
    strcpy(testPlayer->last_name, "Holsapple");
    strcpy(testPlayer->country, "USA");
    strcpy(testPlayer->outcome, "Win");
    testPlayer->score = 42;
    testPlayer->numWordsAdded = 3;
    testPlayer->numWordsFound = 2;

    singlePlayerScoreboard(testPlayer);
    multiPlayerScoreboard(testPlayer);



    return 0;
}
