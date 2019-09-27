#include <stdio.h>		// printf(), perror()
#include <stdlib.h>		// atoi()
#include <string.h>		// strlen()
#include <sys/socket.h>		// socket(), connect(), send(), recv()
#include <unistd.h>		// close()
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <chrono>

void error(const char *msg);

int call_server(int port){
	printf("In server");
	int socketFD, newSocketFD;
    char tempbuffer[1000];
    int bytesRead =0, x =0;
	int option = 1;
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	struct sockaddr_in server_addr, client_addr;
     
	//Create a socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
		error("ERROR opening socket");
	}
    bzero((char *) &server_addr, sizeof(server_addr));
     
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

	// Bind - attach local add to socket
    if (bind(socketFD, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		error("ERROR on binding");
	}

	if(setsockopt(socketFD,SOL_SOCKET,(SO_REUSEPORT | SO_REUSEADDR),(char*)&option,sizeof(option)) < 0)
	{	
		close(socketFD);
		error("setsockopt failed\n");
	}
	// Listen - now willing to accept connections
	// if socketFD is valid, no error is thrown , hence no checking for errors
    listen(socketFD,5);
	startTime = std::chrono::system_clock::now(); 

    socklen_t clientAddSize = sizeof(client_addr);

	//Accept - block caller until connection request arrives
    newSocketFD = accept(socketFD, (struct sockaddr *)&client_addr, &clientAddSize);
    if (newSocketFD < 0) {
		error("ERROR on accept");
	}

    bzero(tempbuffer,1000);

	//Read - receive data over connection
    while( x = read(newSocketFD,tempbuffer,1000) > 0){
		bytesRead++;
		printf("%s\n",tempbuffer);
		if(tempbuffer[999] == 'T'){
			printf("FIN message received from client\n");
			break;
		}
	 bzero(tempbuffer,999);
	}

    if (bytesRead < 0) {
		error("ERROR reading from socket");
	}
	printf("sdvrg %d",bytesRead);
	
	// Send a FIN message to client
	x = write(newSocketFD,"T",1);
	if (x < 0) {
		error("ERROR writing to socket");
	}
	
	endTime = std::chrono::system_clock::now(); 
	
	std::chrono::duration<double> time = endTime - startTime;
    printf("Received=%d KB, Rate=%f Mbps\n",bytesRead, bytesRead/(1000.0 * time.count()));
    close(socketFD);
	close(newSocketFD);
    return 1;
}

int call_client( char *host ,int port, int time){
	printf("In Client");
	int socketFD, n =0;
	int bytesWritten = 0;
	std::chrono::time_point<std::chrono::system_clock> startTime;

    struct sockaddr_in server_addr;
    struct hostent *server;

    char tempbuffer[1000] = {0};
    
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) 
        error("ERROR opening socket");

    server = gethostbyname(host);
    if (server == NULL) {
        error("Incorrect hostname\n");
    }

    bzero((char *) &server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr,server->h_length);
    server_addr.sin_port = htons(port);

    if (connect(socketFD,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        error("ERROR connecting");
	}

	startTime = std::chrono::system_clock::now(); 

	memset(tempbuffer, '1',1000);
//	printf("%s",tempbuffer);
	std::chrono::duration<double> elapsedSec = std::chrono::system_clock::now() - startTime;
	while(elapsedSec.count() <= time){
		printf("%f\n",elapsedSec.count());
   		n = write(socketFD,tempbuffer,1000);
		bytesWritten++;
		elapsedSec = std::chrono::system_clock::now() - startTime;
	}
	printf("done");
	tempbuffer[999] = 'T';
   	n = write(socketFD,tempbuffer,1000);
	printf("%s\n",tempbuffer);
	printf("FIN message sent");
	bytesWritten++;

    if (bytesWritten < 0) {
         error("ERROR occured while writing to socket");
	}

    bzero(tempbuffer,1);
    n = read(socketFD,tempbuffer,1);
    if (n < 0) {
         error("ERROR occured while reading from socket");
	}
	
    printf("Sent=%d KB, Rate=%f Mbps\n",bytesWritten, bytesWritten/(1000.0*time));
	close(socketFD);
    return 1;
}

/*void printUsage(char option) {
	if(option == 's'){
		printf("Usage for Server Mode: ./iPerfer -s -p <listen_port>\n");
	}
	else if (option == 'c'){
		printf("Usage for Client Mode: ./iPerfer -c -h <server_hostname> -p <server_port> -t <time>\n");
	}
}*/

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {

	// Parse command line arguments for Server option
	if (argc == 4) {
		if(!(strcmp(argv[1], "-s") && strcmp(argv[2], "-p"))){
			int port = atoi(argv[3]);
			if(port >=1024 && port <= 65535){
				call_server(port);
			}
			else{
				error("Error: port number must be in the range of [1024, 65535]");
			}
		}
		else{
			error("Error: missing or extra arguments");
		}
		return 1;
	}
	// Parse command line arguments for Client option
	else if (argc == 8) {
		if(!(strcmp(argv[1], "-c") && strcmp(argv[2], "-h") && 
			strcmp(argv[4], "-p") && strcmp(argv[6], "-t"))){
			char *host = argv[3];
			int port = atoi(argv[5]);
			int time = atoi(argv[7]);
			if(port >=1024 && port <= 65535){
				if(time > 0){
					call_client(host, port, time);
				}
				else{
					error("Error: time argument must be greater than 0");
				}
			}
			else{
				error("Error: port number must be in the range of [1024, 65535]");
			}
		}
		else{
			error("Error: missing or extra arguments");
		}
		return 1;
	}
	else {
		error("Error: missing or extra arguments");
		return 1;
	}
	
	return 0;
}

