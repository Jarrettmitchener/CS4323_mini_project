#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <sys/types.h>
#include "methods.c"


//port definition, needs to be the same for client and server
#define PORT 4444

int main()
{
	//flags
	bool shutdown = false;

	int sockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	//updateNumConnected(0);
	updateConnectedFile(0);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//if server can't make connection
	if(sockfd < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	//serts server address properties
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//binds socket
	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	//if socket doesn't create correctly, close
	if(ret < 0)
	{
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0)
	{
		printf("[+]Listening....\n");
	}
	else
	{
		printf("[-]Error in binding.\n");
	}

	//--------------------------------beginning of main server while loop-----------------------//
	while(shutdown == false)
	{
		//printf("amount of clients connected: %i\n", getNumConnected());
		
		//creates a new socket for a new connection
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		//if new socket isn't closed 
		if(newSocket < 0)
		{
			close(newSocket);
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		
		int d = getNumConnected();
		updateConnectedFile(d + 1);


		//--------------------------------------beginning of forked process---------------------------------------//
		if((childpid = fork()) == 0)
		{
			//amountConnected++;
			close(sockfd);

			

			//if there are too many clients connected
			
			if(getNumConnected() > 3)
			{
				//sends client kill code, then closes the socket
				strcpy(buffer, "12345");
				send(newSocket, buffer, strlen(buffer), 0);
				printf("Client %s:%d tried to connect,\n Too many clients connected, so was disconnected\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
				close(newSocket);
				d = getNumConnected();
				updateConnectedFile(d - 1);
				exit(0);
			}
			//if there are not too many clients connected
			else
			{
				//sends socket OK code
				strcpy(buffer, "10001");
				send(newSocket, buffer, strlen(buffer), 0);
			}
			strcpy(buffer, "");
			//---------------------------------forked process while loop-----------------------------------//
			while(shutdown == false)
			{
				recv(newSocket, buffer, 1024, 0);
				printf("Client with port %i sent: %s\n",ntohs(newAddr.sin_port), buffer);
				//printf("c comparison: %i\n", strcmp(buffer, "c"));
				if(strcmp(buffer, ":exit") == 0)
				{
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					d = getNumConnected();
					updateConnectedFile(d - 1);
					break;
				}
				else if(strcmp(buffer, "3") == 0)
				{
					printf("Client has decided to shut down server\n");
					close(newSocket);
					shutdown = true;
					//printf("this is before the exit method is called\n");
					execlp("some", "program", NULL);
					_exit(1);
					printf("THIS SHOULD NOT PRINT\n");
				}
				else if(strcmp(buffer, "c") == 0)
				{
					printf("amount connected in this fork: %i\n", getNumConnected());
					//printf("amount connected with func: %i\n", getNumConnected());
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
				else
				{
					
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
				//printf("-----end of while loop in fork loop----\n");
			}
			//printf("................end of fork if statement....................\n");
		}
		//printf(",,,,,,,,,,,,,,,,,,,,END OF FIRST WHILE LOOP,,,,,,,,,,,,,,,,,,,,\n");

		//parent process
		/*else
		{
			while(1)
			{

				printf("SHIT\n");
				printf("shutdown status: %i\n", shutdown);
				sleep(3);
				if(shutdown == true)
				{
					printf("the end is nye\n");
					_exit(0);
				}
			}
		}*/

	}
	printf("end of the program\n");
	close(newSocket);


	return 0;
}