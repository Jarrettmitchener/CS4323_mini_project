#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#define sleepTime 500

int main()
{

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0)
    {
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0)
    {
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	//does intitial cleanup of first message sending

    //intial handshake
    if(recv(clientSocket, buffer, 1024, 0) < 0)
    {
        printf("[-]Error in receiving data.\n");
    }
    else
    {
		
        printf("Server sent: %s\n", buffer);
        int x = atoi(buffer);
        printf("x = %i\n", x);
        if(x == 12345)
        {
            close(clientSocket);
            printf("Disconnected from server, too many clients connected\n");
            exit(1);
        }
		else
		{
			printf("main menu options would be printed\n");
		}
    }

    
	
    //---------------------------------beginning of client while loop--------------------------------------//
	while(1)
    {
		usleep(500);
		//cleans buffer
		memset(buffer, 0, 1024);

		printf("Client: \t");
		scanf("%s", &buffer[0]);
		send(clientSocket, buffer, strlen(buffer), 0);

		if(strcmp(buffer, ":exit") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}
        if(strcmp(buffer, "3") == 0){
			close(clientSocket);
			printf("[-]Disconnected by client.\n");
			exit(1);
		}

		if(recv(clientSocket, buffer, 1024, 0) < 0)
        {
			printf("[-]Error in receiving data.\n");
		}
        else
        {
			printf("Server sent: %s\n", buffer);

			//main menu printed
			if(strcmp(buffer, "123") == 0)
			{
				printf("Main menu would be displayed\n");
			}
			else if(strcmp(buffer, "222") == 0)
			{
				printf("Multiplayer menu would be displayed\n");
			}
			else if(strcmp(buffer, "000") == 0)
			{
				printf("Server is busy with another set of client(s)\n");
			}
			else if(strcmp(buffer, "888") == 0)
			{
				printf("would display scoreboard s scoreboard\n");
				int counter = 0;
				for(int i = 0; i < counter; i++)
				{
					//prints the stream one by one
				}
				//would then receive 5 scoreboard streams
			}
			else if(strcmp(buffer, "999") == 0)
			{
				printf("would display multiplayer scoreboard\n");
				int counter = 0;
				for(int i = 0; i < counter; i++)
				{
					//prints the stream one by one
				}
				//would then receive 5 scoreboard streams
			}

			//--------------------------------Single player client-------------------------//
			else if(strcmp(buffer, "111") == 0)
			{
				printf("Singleplayer Game starting \n");
				int gameCont = 1;
				while (gameCont == 1)
				{
					memset(buffer, 0, 1024);
					char buf[1024];
					//printf("before first send\n");
					//strcpy(buf, "AMONGUS");
					//send(clientSocket, buf, strlen(buf), 0);
					//bzero(buf, sizeof(buf));
					//sleep(1);
					//usleep(500);
					//printf("after first send\n");

					usleep(500);
					
					recv(clientSocket, buf, 1024, 0);
					int code = atoi(buf);
					//printf("code received is: %i\n", code);
					if(code == 0)
					{
						printf("Game Over\n");
						usleep(500);
						recv(clientSocket, buf, 1024, 0);
						int x = atoi(buf);
						printf("Your final score was: %i\n", x);
						gameCont = 0;
						break;
					}


					//entering word area
					printf("Enter a word: \t");
					scanf("%s", &buffer[0]);
					send(clientSocket, buffer, strlen(buffer), 0);

					//received score for that word
					recv(clientSocket, buffer, 1024, 0);
					int score = atoi(buffer);
					printf("Score received: %i\n", score);
				}
				recv(clientSocket, buffer, 1024, 0);
				int ifAdd = atoi(buffer);
				//printf("scoreboard status: %i\n", ifAdd);
				//if player made it to scoreboard get required information
				if(ifAdd == 1)
				{
					printf("congratulations, you made it to the scoreboard\n");
					printf("Enter your first name:\t");
					scanf("%s", &buffer[0]);
					usleep(500);
					send(clientSocket, buffer, strlen(buffer), 0);

					printf("Enter your last name:\t");
					scanf("%s", &buffer[0]);
					usleep(500);
					send(clientSocket, buffer, strlen(buffer), 0);
					
					printf("Enter your country:\t");
					scanf("%s", &buffer[0]);
					usleep(500);
					send(clientSocket, buffer, strlen(buffer), 0);

					
				}

				printf("This would be the header of the scoreboard\n");
				for(int i = 0; i < 5; i++)
				{
					//usleep(500);
					//printf("this is after the sleep\n");
					
					recv(clientSocket, buffer, 1024, 0);
					printf("%s\n", buffer);
				}

				

				//printf("out of scoreboard area\n");
				//strcpy(buffer, "client_side_over");
				//send(clientSocket, buffer, strlen(buffer), 0);
			}
		}
		
	}
	
	

	return 0;
}
