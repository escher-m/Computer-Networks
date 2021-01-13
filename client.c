/*
Karishma Sinha
2018339

referred from the socket programming code shared in tutorial

*/


//client code
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

#define PORT 9001

int main()
{
	int sock = 0;
	struct sockaddr_in server;

	char textToSend[1024];
	char textToRec[1024];

	server.sin_family = AF_INET;     
	server.sin_port = htons(PORT);   
	server.sin_addr.s_addr = INADDR_ANY;   

	sock = socket(AF_INET, SOCK_STREAM, 0);

	//a.Client initiates the connection
	connect(sock, (struct sockaddr * )&server, sizeof(server));

	printf("You are now connected to the server on Local Host\n");

	printf("Enter File name\n");

	//b. Takes file name from the user
	scanf("%s", textToSend);
	//printf("name sent");
	//c. Sends File name to the server
	send(sock, textToSend, strlen(textToSend), 0);

	printf("Text sent !\nNow Reading \n");

	read(sock, textToRec, 1024);

	//f. Clients stores it in its local drive
	FILE *fp;
	
	// file saved using file handling by opening new file in write mode
	fp=fopen("ReceivedFile.txt","w");		//saves the data sent by server as ReceivedFile.txt in local drive
	fprintf(fp,"%s",textToRec);
	printf("the file was received successfully\n");
	printf("New file saved as ReceivedFile.txt\n");
	//printf("Text Received : %s\n", textToRec);


	//g. Client closes the connection
	printf("Now Closing \n");


	close(sock);
}

/*Notes from tut
	//socket descriptor
	//val assigned
	//server structure
	//buffer 
	//text provided by user from console
	//
	//INETV6
	//4 types: hton
	// INADDR_any: to run on local host
	//
	//print after connecting to server
	//ask user to enter text
	//send string to socket
	//0 : from where the string should be sent
	//Print sent
	//Ask server to send data
	//read systemcall
	//string to receive is diff
	//print received 
	//close connection so that port used becomes free
*/
