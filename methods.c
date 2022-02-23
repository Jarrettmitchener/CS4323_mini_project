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
        printf("error opening file\n");
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
        printf("error opening file\n");
        exit(1);
    }

    int temp;
    fscanf(file, "%i", &temp);
    fclose(file);
	//printf("in get function, temp = %i\n", temp);
    return temp;
}