/*
Karishma Sinha
2018339

referred from the socket programming code shared in tutorial
*/


//server code
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

#define PORT 9001
int main()
{
	int socketId, client;		//client is for identification of client, socketId for server's socket
	struct sockaddr_in server;	//stores socket address for server, struct sockaddr_in for IPv4
 	
	int addLen = sizeof(server);	//size of server address

	char *textToSend;
	char textToRec[1024] = {0};

	server.sin_family = AF_INET;	//for IPv4
	server.sin_port = htons(PORT);	// host to network short, Port 80 : TCP port for localhost
	server.sin_addr.s_addr = INADDR_ANY;

	socketId = socket(AF_INET, SOCK_STREAM, 0); //socketid contains file descriptor

	
	bind(socketId, (struct sockaddr *)&server, sizeof(server)); //protocol independent (struct sockaddr*)

	listen(socketId, 0);
	printf("Server ready\n");

	//Accepting connection
	client = accept(socketId, (struct sockaddr *)&server, (socklen_t *)&addLen);

	printf("Client Connected \n");
	read(client, textToRec, 1024);
	//char fname[1024] = *textToRec;

	//d. Server searches for the file name in its shared drive
	printf("Searching for file %s\n", textToRec);

	if( access( textToRec, F_OK ) != -1 )	//checking if file exists
	{
	    // file exists
	    printf("Found file %s\n", textToRec);

	    //e. Server sends the file to the client
	    FILE *fp;
	    long size;
	    fp = fopen(textToRec, "r");//opening file in read mode
		
		//calculating size of file

		fseek( fp , 0L , SEEK_END);	//fp at end of file
		size = ftell( fp );	//returns current position of stream
		fclose(fp);
		fp = fopen(textToRec, "r");	//reopening file to read
		//rewind( fp );

		/* allocate memory for entire content */
		textToSend = calloc( 1, size+1 );
		fread( textToSend , size, 1 , fp);	//reads file from fp into textToSend

		

		//fscanf(fp,"%s",textToSend);
		send(client, textToSend, strlen(textToSend), 0);
		fclose(fp);
		
		printf("File sent!\n");

	} 
	else
	{
	    // file doesn't exist
	    printf("File not found!\n");
	}

	// *fp = FILE *fopen(textToRec, "r");//opening file in read mode
	// if (fp == NULL) 
	// {
	//     printf("File not found!\n");
	//     return NULL;
	// }
	// else 
	// {
	//     printf("Found file %s\n", filename);
	// }

	// printf("Enter Text to send w/o space\n");
	// scanf("%s", &textToSend);

	// send(client, textToSend, strlen(textToSend), 0);

	// printf("Text sent!\n");


	close(socketId);
}

/* 
Notes from tutorial

//create connection of server
//sin_fam, sin_port, sin_addr.s_addr
//address: any
//socketid contains file descriptor
//bind: fd, server structure format
//listen
//0: number of connection waits in the queue
//at most the queue can be empty
//client is the client id
//accept: fd, server protocol independent struct, len
//print connected
//

// ..................
// compile server
// compile client 
// start server // run file
// prints : server ready
// start client 
// prints client connected
// enter data for client
// enter data to send back to server 
// close close 
*/