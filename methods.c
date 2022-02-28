#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

void setConnectedFlag(int num)
{
    FILE *f;
    f = fopen("numConnected.txt", "w");
    if(f == NULL)
    {
        printf("error opening numConnected file\n");
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

void setOccupiedFlag(int num)
{
    FILE *f;
    f = fopen("occupied.txt", "w");
    if(f == NULL)
    {
        printf("error opening occupied file\n");
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

void setSearchPlayerFlag(int num)
{
    FILE *f;
    f = fopen("search.txt", "w");
    if(f == NULL)
    {
        printf("error opening searcg file\n");
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
        printf("error opening search file\n");
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
        printf("error opening multi flag file\n");
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
        printf("error opening multi flag file\n");
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
        printf("error opening turn flag file\n");
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
        printf("error opening turn flag file\n");
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
        printf("error opening game flag file\n");
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
        printf("error opening game flag file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	
    return temp;
}

void setScoreP1(int num)
{
    FILE *f;
    f = fopen("score1.txt", "w");
    if(f == NULL)
    {
        printf("error opening p1 score file\n");
        exit(1);
    }
    fprintf(f, "%i", num);
    fclose(f);

}
int getScoreP1()
{
	FILE *file;
    file = fopen("score1.txt", "r");
	//if file doesnt open, exit
    if(file == NULL)
    {
        printf("error opening p1 score file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	
    return temp;
}

void setScoreP2(int num)
{
    FILE *f;
    f = fopen("score2.txt", "w");
    if(f == NULL)
    {
        printf("error opening p2 score file\n");
        exit(1);
    }
    fprintf(f, "%i", num);
    fclose(f);

}
int getScoreP2()
{
	FILE *file;
    file = fopen("score2.txt", "r");
	//if file doesnt open, exit
    if(file == NULL)
    {
        printf("error opening p2 score file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	
    return temp;
}

/*void setName(char* s)
{
    FILE *f;
    f = fopen("name.txt", "w");
    if(f == NULL)
    {
        printf("error opening name file\n");
        exit(1);
    }
    fprintf(f, "%s", s);
    fclose(f);

}
char* getName()
{
	FILE *file;
    file = fopen("name.txt", "r");
	//if file doesnt open, exit
    if(file == NULL)
    {
        printf("error opening name file\n");
        exit(1);
    }

    char* temp;
    fscanf(file, "%s", temp);
    fclose(file);
	
    return temp;
}*/