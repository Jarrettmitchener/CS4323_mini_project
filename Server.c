//Group Number: Group c
//Name: Jarrett Mitchener
//Email: Jarrett.Mitchener@okstate.edu
//Date: 2/26/2022



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
#include <time.h>
#include "methods.c"


//port definition, needs to be the same for client and server
#define PORT 4444

#define DELAY 500

int main()
{
	//flags
	bool shutdown = false;
	int gameInProgress = 0;
	int occupied = 0;
	int multiGameStart = 0;

	//used in determing in multiplayer which player is 0 or 1
	int playerID;

	int sockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	//initializes all multi process flags
	setConnectedFlag(0);
	setOccupiedFlag(0);
	setSearchPlayerFlag(0);
	setScoreP1(0);
	setScoreP2(0);
	updateMultiFlag(0);
	updateGameFlag(0);

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
		setConnectedFlag(d + 1);


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
				setConnectedFlag(d - 1);
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
				usleep(DELAY);
				//cleans buffer
				memset(buffer, 0, 1024);

				//printf("buffer at begging of loop: %s\n", buffer);
				recv(newSocket, buffer, 1024, 0);
				printf("Client with port %i sent: %s\n",ntohs(newAddr.sin_port), buffer);
				//printf("c comparison: %i\n", strcmp(buffer, "c"));

				//printf("occupied status: %i\n", getOccupied());
				//printf("MultiFlag status: %i\n", getMultiFlag());
				//printf("gameInProgress status: %i\n", gameInProgress);

				if(strcmp(buffer, ":exit") == 0)
				{
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					d = getNumConnected();
					setConnectedFlag(d - 1);
					break;
				}

				//if someone is in multi player and waiting for a player
				//and client chose single player
				else if (getOccupied() == 1 && getMultiFlag() == 1 && gameInProgress == 0 && strcmp(buffer, "1") == 0)
				{
					printf("Client with port: %d is trying to play a game\nbut server is waiting on \nSomeone to play a multiplayer game\n", ntohs(newAddr.sin_port));
					strcpy(buffer, "001");
					//printf("what is suppose to be sent: %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					//printf("buffer is: %s\n", buffer);
					bzero(buffer, sizeof(buffer));
				}
				//if someone is in multi player and waiting for a player
				//and client chose multi player
				else if (getOccupied() == 1 && getMultiFlag() == 1 && gameInProgress == 0 && strcmp(buffer, "2") == 0)
				{
					printf("Client with port: %d is trying to play a\nmultiplayer game when another player is\nwaiting to play\n", ntohs(newAddr.sin_port));
					strcpy(buffer, "022");
					//printf("what is suppose to be sent: %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					//printf("buffer is: %s\n", buffer);
					bzero(buffer, sizeof(buffer));
					multiGameStart = 1;
					updateMultiFlag(2);

					//generates the random turn variable to be either 0 or 1, then uses playerID to determine when a player goes
					srand(time(NULL));
					int randTurn = rand() % 2;
					printf("the random variable is :%i\n",randTurn);
					updateTurnFlag(randTurn);

					//sets playerID
					playerID = 1;
				}
				//if two people are in multi player gaming
				else if (getOccupied() == 1 && getMultiFlag() == 2 && gameInProgress == 0)
				{
					printf("Client with port: %d is trying to play a game\nbut multiplayer game is already active\n", ntohs(newAddr.sin_port));
					strcpy(buffer, "002");
					//printf("what is suppose to be sent: %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					//printf("buffer is: %s\n", buffer);
					bzero(buffer, sizeof(buffer));
				}
				//if someone is in singleplayer and game is started,
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
					setOccupiedFlag(1);
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
						usleep(DELAY);
						strcpy(buf, "");
						sprintf(buf, "%d", gameCont);
						send(newSocket, buf, strlen(buf), 0);
						bzero(buf, sizeof(buf));
						if(gameCont == 0)
						{
							printf("Client with port: %d game has ended\n", ntohs(newAddr.sin_port));
							usleep(DELAY);
							strcpy(buf, "1000");
							send(newSocket, buf, strlen(buf), 0);
							bzero(buf, sizeof(buf));

							//here would be the code to determine if the player gets added to the scoreboard
							//sets flag that name needs to be obtained from client
							scoreboard = 1;
							scoreboard = 0;//tired of debugging and asking for my name

							break;
						}


						recv(newSocket, buffer, 1024, 0);
						printf("Client with port: %i sent word: %s\n",ntohs(newAddr.sin_port), buffer);
						strcpy(buffer, "5");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));
						gameCounter++;
					}
					usleep(DELAY);
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
						usleep(DELAY);
						//printf("after sleep at beginning\n");
						strcpy(buffer, "Long String Inbound");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));
						
					}

					printf("Finished sending scoreboard to client %d\n",ntohs(newAddr.sin_port));

					//updates occupied status of server
					printf("Client with port: %i is finished with their game\n", ntohs(newAddr.sin_port));
					printf("Their final score was %i\n", 69);
					
					//updates occupied status of server
					setOccupiedFlag(0);
				}
				//-----------------------------------------Multiplayer Section------------------------------------------//
				else if(strcmp(buffer, "2") == 0)
				{
					printf("Client with port %d has decided to play multiplayer\n", ntohs(newAddr.sin_port));
					gameInProgress = 1;
					strcpy(buffer, "222");
					if (getMultiFlag() == 0)
					{
						updateMultiFlag(1);
					}
					else if (getMultiFlag() == 1)
					{
						updateMultiFlag(2);
					}
					
					setOccupiedFlag(1);
					
					//printf("what is suppose to be sent to the client %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
					multiGameStart = 1;

					//sets player ID to player 1(int 0)
					playerID = 0;
					
				}
				//this command isnt really important, will be cut later
				else if(strcmp(buffer, "cancel") == 0)
				{
					printf("Client has decided to end game\n");
					gameInProgress = 0;
					//printf("what is suppose to be sent to the client %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					setOccupiedFlag(0);
					bzero(buffer, sizeof(buffer));
				}
				else
				{
					//printf("what is suppose to be sent to the client %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}

				//--------------------------ACTUAL MULTIPLAYER CODE STARTS FOR THE GAME-----------------------------//
				if(multiGameStart == 1)
				{
					printf("made it to multiplayer code area\n");
					memset(buffer, 0, 1024);
					usleep(DELAY);

					int waiting = 0;
					//depending on if the player is the first one in the multiplayer process
					//or not, client needs to know if theyre waiting on another player 
					if(getMultiFlag() == 2)//two players connected
					{
						
						strcpy(buffer, "1");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));
						
						
					}
					else //only one player connected
					{
						printf("Only one player is connected, waiting until another to continue...\n");
						memset(buffer, 0, 1024);
						strcpy(buffer, "0");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));
						waiting = 1;
					}
					printf("waiting value is: %i\n", waiting);
					while(waiting == 1)
					{
						if(getMultiFlag() == 2)
						{
							printf("we have made it out of the loop!!!!\n");
							break;
						}
						sleep(1);
					}
					usleep(DELAY);
					strcpy(buffer, "pleaseWork");
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
					//printf("sent dummy code\n");

					//collects information on player
					char firstname[1024];
					char lastname[1024];
					char country[1024];
					usleep(DELAY);
					memset(buffer, 0, 1024);
					recv(newSocket, buffer, 1024, 0);
					strcpy(firstname, buffer);
					printf("Client %d first name is %s\n", ntohs(newAddr.sin_port), firstname);

					memset(buffer, 0, 1024);
					recv(newSocket, buffer, 1024, 0);
					strcpy(lastname, buffer);
					printf("Client %d last name is %s\n", ntohs(newAddr.sin_port), lastname);

					memset(buffer, 0, 1024);
					recv(newSocket, buffer, 1024, 0);
					strcpy(country, buffer);
					printf("Client %d country is %s\n", ntohs(newAddr.sin_port), country);

					//sends first player flag
					memset(buffer, 0, 1024);
					usleep(DELAY);
					if(playerID == getTurnFlag())
					{
						strcpy(buffer, "0");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));
					}
					else
					{
						strcpy(buffer, "1");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));
					}
					//gamecounter, will be changed/removed once games implemented
					int gameCounter = 0;
					int gameContinue = 1;
					int name = 0;
					
					usleep(DELAY);
					memset(buffer, 0, 1024);
					sprintf(buffer, "%d", playerID);
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));

					while(gameContinue == 1)
					{
						memset(buffer, 0, 1024);
						//code that is sent to tell client if game is over or not
						usleep(DELAY);

						//loop that will keep going until its that person turn					
						while(playerID == getTurnFlag())
						{
							sleep(1);
							//will run until previous player finishes their turn
						}
						printf("%s's turn now\n", firstname);

						//checks if game is still going on
						usleep(DELAY);
						if(getGameFlag() == 1)
						{
							//game is over, break loop
							strcpy(buffer, "1");
							send(newSocket, buffer, strlen(buffer), 0);
							bzero(buffer, sizeof(buffer));
							break;
						}
						else
						{
							strcpy(buffer, "0");
							send(newSocket, buffer, strlen(buffer), 0);
							bzero(buffer, sizeof(buffer));
						}
						memset(buffer, 0, 1024);

						//sends both players scores back to the user

						//writes first players score to buffer
						usleep(DELAY);
						sprintf(buffer, "%d", getScoreP1());
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));

						memset(buffer, 0, 1024);
						usleep(DELAY);
						//writes first players score to buffer
						sprintf(buffer, "%d", getScoreP2());
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));


						memset(buffer, 0, 1024);
						//this would be where we choose a random set of letters
						usleep(DELAY);
						strcpy(buffer, "EIAHVC");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));

						memset(buffer, 0, 1024);
						//this would be where we choose a random letter and send
						usleep(DELAY);
						strcpy(buffer, "I");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));

						//receive word they sent
						memset(buffer, 0, 1024);
						recv(newSocket, buffer, 1024, 0);
						printf("%s sent word: %s\n", firstname, buffer);

						
						//do some logic with the word they sent

						//sends if word was valid or not
						//0 for invalid, 1 for valid
						//add actual logic later
						usleep(DELAY);
						memset(buffer, 0, 1024);
						strcpy(buffer, "1");
						send(newSocket, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));

						int scoreForWord;//will be the score the person gets for the word they sent
						scoreForWord = 5;

						//updates player scores depending on which one they are
						if(playerID == 0)
						{
							int s = getScoreP1();
							setScoreP1(s + scoreForWord);
						}
						else if(playerID == 1)
						{
							int s = getScoreP2();
							setScoreP2(s + scoreForWord);
						}


						gameCounter++;
						//ends game, just for testing
						if(gameCounter > 3)
						{
							updateGameFlag(1);
						}
						//flips the turn flag which lets the other player get out of the while loop
						//while simultaneously getting the current player stuck in it
						if(getTurnFlag() == 0)
						{
							updateTurnFlag(1);
						}
						else
						{
							updateTurnFlag(0);
						}



					}
					
				}
				
			}
			
			
		}
		



	}
	printf("end of the program\n");
	close(newSocket);


	return 0;
}