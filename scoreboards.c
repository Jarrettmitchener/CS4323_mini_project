//mini_group_project_Keenan_Holsapple_Scoreboards.c
/*BRIEF DESCRIPTION
 * Management of scoreboard for both single player and multiplayer. This includes reading in the developed user
 * structure, along with the function determining whoWin() returned value. These winning values will be sent to
 * a dedicated text file, and finally returned in a format in the user’s console.
 *
 * THIS FUNCTION WILL OCCUR AFTER THE ROUND HAS BEEN COMPLETED BY AN INDIVIDUAL
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



//initialize the table to handle later data
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
        fprintf(file, "%s ", "Zhao");
        fprintf(file, "%s ", "Bao");
        fprintf(file, "%s ", "China");
        fprintf(file, "%d ", 34);
        fprintf(file, "%d ", 7);
        fprintf(file, "%d ", 2);
        fprintf(file, "\t%3s\t", "Nakano");
        fprintf(file, "\t%9s\t", "Tsutomu");
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

        fclose(file);
}

//initializing table with multiplayer data from form
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
        fprintf(file, "\t%3s\t", "Zhao");
        fprintf(file, " \t%9s\t", "Bao");
        fprintf(file, "\t      %s\t", "China");
        fprintf(file, "\t      %d\t", 34);
        fprintf(file, "\t%s\t", "Win");
        fprintf(file, "\t%d\t", 7);
        fprintf(file, "\t%d\n", 2);
        fprintf(file, "\t%3s\t", "Nakano");
        fprintf(file, "\t%s\t", "Tsutomu");
        fprintf(file, "\t%s\t", "Japan");
        fprintf(file, "\t%d\t", 32);
        fprintf(file, "\t%s\t", "Win");
        fprintf(file, "\t%d\t", 8);
        fprintf(file, "\t%d\n", 9);
        fprintf(file, "\t%3s\t", "Felicjan");
        fprintf(file, "\t%s\t", "Wos");
        fprintf(file, "\t%s\t", "Poland");
        fprintf(file, "\t%d\t", 31);
        fprintf(file, "\t%s\t", "Loss");
        fprintf(file, "\t%d\t", 9);
        fprintf(file, "\t%d\n", 1);
        fprintf(file, "\t%3s\t", "Kapsar");
        fprintf(file, "\t%s\t", "Zimmermann");
        fprintf(file, "\t%s\t", "Germany");
        fprintf(file, "\t%d\t", 30);
        fprintf(file, "\t%s\t", "Win");
        fprintf(file, "\t%d\t", 11);
        fprintf(file, "\t%d\n", 0);
        fprintf(file, "\t%3s\t", "Karina");
        fprintf(file, "\t%s\t", "Maynard");
        fprintf(file, "\t%s\t", "USA");
        fprintf(file, "\t%d\t", 30);
        fprintf(file, "\t%s\t", "Win");
        fprintf(file, "\t%d\t", 10);
        fprintf(file, "\t%d\n", 0);

        fclose(file);
}

//returns file values line by line to pass as variables for client
void returnString(char* filetitle){

    char string_of_line[1000];

    FILE* file;
    file = fopen(filetitle, "r");
    while (fscanf(file, "%[^\n] ", string_of_line) != EOF) {
    printf("%s\n", string_of_line);
    }

    fclose(file);
}

//server uses for loop to determine which line will be taken
//kept seperate from actual screen readout to help with stability of program
char* lineToServer(int line, char* filename){

    
    FILE* file;
    file = fopen(filename, "r");
    char *string_of_line = malloc(1000);

    //skips first two lines of header
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%*[^\n]\n");

    //for loop to determine how many lines to skip to find certain line data
    switch(line){
        case 1:
            break;
        case 2:
            fscanf(file, "%*[^\n]\n");
            break;
        case 3:
            fscanf(file, "%*[^\n]\n");
            fscanf(file, "%*[^\n]\n");
            break;
        case 4:
            fscanf(file, "%*[^\n]\n");
            fscanf(file, "%*[^\n]\n");
            fscanf(file, "%*[^\n]\n");
            break;
        case 5:
            fscanf(file, "%*[^\n]\n");
            fscanf(file, "%*[^\n]\n");
            fscanf(file, "%*[^\n]\n");
            fscanf(file, "%*[^\n]\n");
            break;
    }


    fscanf(file, "%[^\n] ", string_of_line);

    fclose(file);

    return string_of_line;
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

    //defining separate player structures
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

    char flagname[1000] = "";

    //placing in order depending on score array placement
    for(int i = 0; i < 5; i++){
 
        //if statements that determine placement of scores on form
        if(scoreArr[i] == p1->score && (strcmp(p1->first_name, flagname) < 0 || strcmp(p1->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p1->first_name);
            fprintf(file, "%30s", p1->last_name);
            fprintf(file, "%22s", p1->country);
            fprintf(file, "%11d", p1->score);
            fprintf(file, "%15d", p1->numWordsFound);
            fprintf(file, "%20d\n", p1->numWordsAdded);
            strcpy(flagname, p1->first_name);

            continue;
        }
        if(scoreArr[i] == p2->score && (strcmp(p2->first_name, flagname) < 0 || strcmp(p2->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p2->first_name);
            fprintf(file, "%30s", p2->last_name);
            fprintf(file, "%22s", p2->country);
            fprintf(file, "%11d", p2->score);
            fprintf(file, "%15d", p2->numWordsFound);
            fprintf(file, "%20d\n", p2->numWordsAdded);
            strcpy(flagname, p2->first_name);
            
            continue;
        }
        if(scoreArr[i] == p3->score && (strcmp(p3->first_name, flagname) < 0 || strcmp(p3->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p3->first_name);
            fprintf(file, "%30s", p3->last_name);
            fprintf(file, "%22s", p3->country);
            fprintf(file, "%11d", p3->score);
            fprintf(file, "%15d", p3->numWordsFound);
            fprintf(file, "%20d\n", p3->numWordsAdded);
            strcpy(flagname, p3->first_name);

           continue;
        }
        if(scoreArr[i] == p4->score && (strcmp(p4->first_name, flagname) < 0 || strcmp(p4->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p4->first_name);
            fprintf(file, "%30s", p4->last_name);
            fprintf(file, "%22s", p4->country);
            fprintf(file, "%11d", p4->score);
            fprintf(file, "%15d", p4->numWordsFound);
            fprintf(file, "%20d\n", p4->numWordsAdded);
            strcpy(flagname, p4->first_name);
 
            continue;
        }
        if(scoreArr[i] == p5->score && (strcmp(p5->first_name, flagname) < 0 || strcmp(p5->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p5->first_name);
            fprintf(file, "%30s", p5->last_name);
            fprintf(file, "%22s", p5->country);
            fprintf(file, "%11d", p5->score);
            fprintf(file, "%15d", p5->numWordsFound);
            fprintf(file, "%20d\n", p5->numWordsAdded);
            strcpy(flagname, p5->first_name);

            continue;
        }
        if(scoreArr[i] == newPlayer->score && (strcmp(newPlayer->first_name, flagname) < 0 || strcmp(newPlayer->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", newPlayer->first_name);
            fprintf(file, "%30s", newPlayer->last_name);
            fprintf(file, "%22s", newPlayer->country);
            fprintf(file, "%11d", newPlayer->score);
            fprintf(file, "%15d", newPlayer->numWordsFound);
            fprintf(file, "%20d\n", newPlayer->numWordsAdded);
            strcpy(flagname, newPlayer->first_name);

           continue;
        }
    }

    //closes file for string read
    fclose(file);

    //reading file data to console
    returnString(filename);


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

    //creating player structure
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
    file = fopen("multiPlayer.txt", "w");
    fprintf(file, "%s", "\tFirst name\t|");
    fprintf(file, "%s", "\tLast name\t|");
    fprintf(file, "%s", "\tCountry   |");
    fprintf(file, "%s", " Score |");
    fprintf(file, "%s", "  Win/lose  |");
    fprintf(file, "%s", " Number of Words Found |");
    fprintf(file, "%s\n", " Number of Added to Dictionary");
    fprintf(file , "--------------------------------------------------------------------------------------------------------------------------------------------\n");

    //flagname utilized to compare scores
    char flagname[20] = "";

    //placing in order depending on score array placement
    for(int i = 0; i < 5; i++){
 
        //lines for reading out data to textfile
        if(scoreArr[i] == p1->score && (strcmp(p1->first_name, flagname) < 0 || strcmp(p1->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p1->first_name);
            fprintf(file, "%31s", p1->last_name);
            fprintf(file, "%22s", p1->country);
            fprintf(file, "%11d", p1->score);
            fprintf(file, "%11s", p1->outcome);
            fprintf(file, "%20d", p1->numWordsFound);
            fprintf(file, "%20d\n", p1->numWordsAdded);
            strcpy(flagname, p1->first_name);

            continue;
        }
        if(scoreArr[i] == p2->score && (strcmp(p2->first_name, flagname) < 0 || strcmp(p2->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p2->first_name);
            fprintf(file, "%31s", p2->last_name);
            fprintf(file, "%22s", p2->country);
            fprintf(file, "%11d", p2->score);
            fprintf(file, "%11s", p2->outcome);
            fprintf(file, "%20d", p2->numWordsFound);
            fprintf(file, "%20d\n", p2->numWordsAdded);
            strcpy(flagname, p2->first_name);
            
            continue;
        }
        if(scoreArr[i] == p3->score && (strcmp(p3->first_name, flagname) < 0 || strcmp(p3->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p3->first_name);
            fprintf(file, "%31s", p3->last_name);
            fprintf(file, "%22s", p3->country);
            fprintf(file, "%11d", p3->score);
            fprintf(file, "%11s", p3->outcome);
            fprintf(file, "%20d", p3->numWordsFound);
            fprintf(file, "%20d\n", p3->numWordsAdded);
            strcpy(flagname, p3->first_name);

           continue;
        }
        if(scoreArr[i] == p4->score && (strcmp(p4->first_name, flagname) < 0 || strcmp(p4->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p4->first_name);
            fprintf(file, "%31s", p4->last_name);
            fprintf(file, "%22s", p4->country);
            fprintf(file, "%11d", p4->score);
            fprintf(file, "%11s", p4->outcome);
            fprintf(file, "%20d", p4->numWordsFound);
            fprintf(file, "%20d\n", p4->numWordsAdded);
            strcpy(flagname, p4->first_name);
 
            continue;
        }
        if(scoreArr[i] == p5->score && (strcmp(p5->first_name, flagname) < 0 || strcmp(p5->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", p5->first_name);
            fprintf(file, "%31s", p5->last_name);
            fprintf(file, "%22s", p5->country);
            fprintf(file, "%11d", p5->score);
            fprintf(file, "%11s", p5->outcome);
            fprintf(file, "%20d", p5->numWordsFound);
            fprintf(file, "%20d\n", p5->numWordsAdded);
            strcpy(flagname, p5->first_name);

            continue;
        }
        if(scoreArr[i] == newPlayer->score && (strcmp(newPlayer->first_name, flagname) < 0 || strcmp(newPlayer->first_name, flagname) > 0)){
            fprintf(file, "\t%3s\t", newPlayer->first_name);
            fprintf(file, "%31s", newPlayer->last_name);
            fprintf(file, "%22s", newPlayer->country);
            fprintf(file, "%11d", newPlayer->score);
            fprintf(file, "%11s", newPlayer->outcome);
            fprintf(file, "%20d", newPlayer->numWordsFound);
            fprintf(file, "%20d\n", newPlayer->numWordsAdded);
            strcpy(flagname, newPlayer->first_name);

           continue;
        }

    }

    fclose(file);
    
    //reading file datas to console
    returnString("multiPlayer.txt");


}

/*singlePlayerScoreboard()
* 1. Checks for/creates scoreboard text file
* 2. Reads for score values and stores into array
* 3. Sorts array in descending order
* 4. Performs swap for locations in file
*/
void singlePlayerScoreboard(struct player *playerArr){

    //initiating check to see if file already exists
    FILE* file = fopen("singlePlayer.txt", "r");

    //if exist, reads in previous player data that exists
    if(file){
        fclose(file);
    }
    else{
        initializeTable("singlePlayer.txt");        
    }
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

    FILE* file = fopen("multiPlayer.txt", "r");
    //creating the initial table
    if(file){
        fclose(file);
    }
    else{
        initializeTable("multiPlayer.txt");        
    }

    //adding in final score value to final index
    readScoresMulti("multiPlayer.txt", playerArr);

}
