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
	bool singlePlayer = false;
	bool multiPlayer = false;
	int gameInProgress = 0;
	int occupied = 0;

	int sockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	
	updateConnectedFile(0);
	updateOccupiedFile(0);
	updateSearchPlayerFile(0);
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

			//strcpy(buffer, "");
			//send(newSocket, buffer, strlen(buffer), 0);
			//printf("after server send\n");
			//recv(newSocket, buffer, 1024, 0);
			//printf("after server recv\n");
			//strcpy(buffer, "");
			

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
			
			//---------------------------------forked process while loop-----------------------------------//
			while(shutdown == false)
			{
				usleep(500);
				//cleans buffer
				memset(buffer, 0, 1024);

				//printf("buffer at begging of loop: %s\n", buffer);
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
				
				else if(getOccupied() == 1 && gameInProgress == 0)
				{
					
					printf("Client with port: %d is trying to play a game\nbut server is busy with other client(s)\n", ntohs(newAddr.sin_port));
					strcpy(buffer, "000");
					//printf("what is suppose to be sent: %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					//printf("buffer is: %s\n", buffer);
					bzero(buffer, sizeof(buffer));

				}
				

				//this doesnt work correctly
				else if(strcmp(buffer, "3") == 0)
				{
					printf("Client has decided to shut down server\n");
					close(newSocket);
					shutdown = true;
					//printf("this is before the exit method is called\n");
					execlp("some", "program", NULL);
					_exit(1);
					
				}
				else if(strcmp(buffer, "c") == 0)
				{
					printf("amount connected in this fork: %i\n", getNumConnected());
					//printf("what is suppose to be sent to the client %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
				//---------------------------------------Singleplayer Section-------------------------------------//
				else if(strcmp(buffer, "1") == 0)
				{
					printf("Client with port: %d has decided to play singleplayer\n", ntohs(newAddr.sin_port));
					gameInProgress = 1;
					strcpy(buffer, "111");
					updateOccupiedFile(1);
					//printf("what is suppose to be sent to the client %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));

					int gameCounter = 0;
					//game end flag
					int gameCont = 1;
					//scoreboard flag if player needs to be recorded in the scoreboard
					int scoreboard = 0;

					while(gameCont == 1)
					{
						memset(buffer, 0, 1024);
						
						//printf("before first receive\n");
						char buf[1024];
						//recv(newSocket, buf, 1024, 0);	
						//printf("they sent: %s\n", buf);

						//game over status
						if(gameCounter > 3)
						{
							gameCont = 0;

							
						}
						usleep(500);
						strcpy(buf, "");
						sprintf(buf, "%d", gameCont);
						send(newSocket, buf, strlen(buf), 0);
						bzero(buf, sizeof(buf));
						if(gameCont == 0)
						{
							printf("Client with port: %d game has ended\n", ntohs(newAddr.sin_port));
							usleep(500);
							strcpy(buf, "1000");
							send(newSocket, buf, strlen(buf), 0);
							bzero(buf, sizeof(buf));

							//here would be the code to determine if the player gets added to the scoreboard
							//sets flag that name needs to be obtained from client
							scoreboard = 1;

							break;
						}


						recv(newSocket, buffer, 1024, 0);
						printf("Client with port: %i sent word: %s\n",ntohs(newAddr.sin_port), buffer);
						strcpy(buffer, "5");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));
						gameCounter++;
					}
					usleep(500);
					sprintf(buffer, "%d", scoreboard);
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));

					//if player needs to be added to scoreboard
					if(scoreboard == 1)
					{
						char firstname[1024];
						char lastname[1024];
						char country[1024];

						memset(buffer, 0, 1024);
						recv(newSocket, buffer, 1024, 0);
						strcpy(firstname, buffer);
						printf("Client with port: %i first name: %s\n",ntohs(newAddr.sin_port), firstname);

						memset(buffer, 0, 1024);
						recv(newSocket, buffer, 1024, 0);
						strcpy(lastname, buffer);
						printf("Client with port: %i last name: %s\n",ntohs(newAddr.sin_port), lastname);

						memset(buffer, 0, 1024);
						recv(newSocket, buffer, 1024, 0);
						strcpy(country, buffer);
						printf("Client with port: %i country: %s\n",ntohs(newAddr.sin_port), country);
					}
					for(int i = 0; i < 5; i++)
					{
						
						//sleep(1);
						usleep(500);
						//printf("after sleep at beginning\n");
						strcpy(buffer, "Long String Inbound");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));
						
					}

					printf("Finished sending scoreboard to client %s\n",ntohs(newAddr.sin_port));

					//updates occupied status of server
					printf("Client with port: %i is finished with their game\n", ntohs(newAddr.sin_port));
					printf("Their final score was %i\n", 5);
					
					//updates occupied status of server
					updateOccupiedFile(0);
				}
				//-----------------------------------------Multiplayer Section------------------------------------------//
				else if(strcmp(buffer, "2") == 0)
				{
					printf("Client with port %d has decided to play multiplayer\n", ntohs(newAddr.sin_port));
					//local variable just so it's easier to track 
					int counter = getNumConnected();
					//printf("what is suppose to be sent to the client %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					updateOccupiedFile(1);
					bzero(buffer, sizeof(buffer));
				}
				//this command isnt really important, will be cut later
				else if(strcmp(buffer, "cancel") == 0)
				{
					printf("Client has decided to end game\n");
					gameInProgress = 0;
					//printf("what is suppose to be sent to the client %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					updateOccupiedFile(0);
					bzero(buffer, sizeof(buffer));
				}
				else
				{
					//printf("what is suppose to be sent to the client %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
				//printf("-----end of while loop in fork loop----\n");
			}
			
			//printf("................end of fork if statement....................\n");
		}
		//printf(",,,,,,,,,,,,,,,,,,,,END OF FIRST WHILE LOOP,,,,,,,,,,,,,,,,,,,,\n");



	}
	printf("end of the program\n");
	close(newSocket);


	return 0;
}
