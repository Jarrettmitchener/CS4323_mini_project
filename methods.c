#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

void updateConnectedFile(int num)
{
    FILE *f;
    f = fopen("numConnected.txt", "w");
    if(f == NULL)
    {
        printf("error opening numConnected file in update\n");
        exit(1);
    }
    fprintf(f, "%i", num);
    fclose(f);

}

int getNumConnected()
{
	FILE *file;
    file = fopen("numConnected.txt", "r");
	//if file doesnt open, exit
    if(file == NULL)
    {
        printf("error opening numConnected file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	//printf("in get function, temp = %i\n", temp);
    return temp;
}

void updateOccupiedFile(int num)
{
    FILE *f;
    f = fopen("occupied.txt", "w");
    if(f == NULL)
    {
        printf("error opening occupied file in update\n");
        exit(1);
    }
    fprintf(f, "%i", num);
    fclose(f);

}
int getOccupied()
{
	FILE *file;
    file = fopen("occupied.txt", "r");
	//if file doesnt open, exit
    if(file == NULL)
    {
        printf("error opening occupied file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	//printf("in get function, temp = %i\n", temp);
    return temp;
}

void updateSearchPlayerFile(int num)
{
    FILE *f;
    f = fopen("search.txt", "w");
    if(f == NULL)
    {
        printf("error opening occupied file in update\n");
        exit(1);
    }
    fprintf(f, "%i", num);
    fclose(f);

}
int getSearchPlayerStatus()
{
	FILE *file;
    file = fopen("search.txt", "r");
	//if file doesnt open, exit
    if(file == NULL)
    {
        printf("error opening occupied file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	//printf("in get function, temp = %i\n", temp);
    return temp;
}

void updateMultiFlag(int num)
{
    FILE *f;
    f = fopen("multi.txt", "w");
    if(f == NULL)
    {
        printf("error opening occupied file in update\n");
        exit(1);
    }
    fprintf(f, "%i", num);
    fclose(f);

}
int getMultiFlag()
{
	FILE *file;
    file = fopen("multi.txt", "r");
	//if file doesnt open, exit
    if(file == NULL)
    {
        printf("error opening occupied file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	
    return temp;
}

void updateTurnFlag(int num)
{
    FILE *f;
    f = fopen("turn.txt", "w");
    if(f == NULL)
    {
        printf("error opening occupied file in update\n");
        exit(1);
    }
    fprintf(f, "%i", num);
    fclose(f);

}
int getTurnFlag()
{
	FILE *file;
    file = fopen("turn.txt", "r");
	//if file doesnt open, exit
    if(file == NULL)
    {
        printf("error opening occupied file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	
    return temp;
}
void updateGameFlag(int num)
{
    FILE *f;
    f = fopen("game.txt", "w");
    if(f == NULL)
    {
        printf("error opening occupied file in update\n");
        exit(1);
    }
    fprintf(f, "%i", num);
    fclose(f);

}
int getGameFlag()
{
	FILE *file;
    file = fopen("game.txt", "r");
	//if file doesnt open, exit
    if(file == NULL)
    {
        printf("error opening occupied file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	
    return temp;
}