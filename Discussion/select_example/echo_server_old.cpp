#include <cstdio> 
#include <string.h> //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> //close 
#include <arpa/inet.h> //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO, FD_SETSIZE macros 
#include <array> // std::array

#define TRUE 1 
#define FALSE 0 
#define PORT 8889
#define MAXCLIENTS 30
/* 
 *  Compile with: g++ --std=c++11 echo_server.cpp
 *  Try to run this server and run multiple instances 
 *  of "nc localhost 8888" to communicate with it!
*/

int get_master_socket(struct sockaddr_in * address){
    int opt = TRUE; 
    int master_socket;
    //create a master socket 
    master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(master_socket <= 0) { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    int success = setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &opt, 
                             sizeof(opt));
    if(success < 0) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    //type of socket created 
    address->sin_family = AF_INET; 
    address->sin_addr.s_addr = INADDR_ANY; 
    address->sin_port = htons(PORT); 

    //bind the socket to localhost port 8888 
    success = ::bind(master_socket, 
                     (struct sockaddr *)address, sizeof(*address));
    if (success < 0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    printf("Listening on port %d \n", PORT); 

    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    return master_socket;
}

int find_max_sd(fd_set * readfds, int * client_fds, int length, int max_sd) {
    int sd = -1;
    for (int i = 0; i < length; ++i) {
        //socket descriptor 
        sd = client_fds[i];

        //if valid socket descriptor then add to read list 
        if(sd > 0)
            FD_SET(sd, readfds);

        //highest file descriptor number, need it for the select function 
        if(sd > max_sd)
            max_sd = sd;
    }
    return max_sd;
}

int main(int argc , char *argv[]){
    int master_socket , addrlen , new_socket ,
        activity, valread , sd;
    std::array<int, MAXCLIENTS> client_sockets;
    int max_sd; 

    struct sockaddr_in address;
    master_socket = get_master_socket(&address);

    char buffer[1025]; //data buffer of 1K
    // Greeting message
    const char * message = "ECHO Daemon v1.0 \r\n";

    client_sockets.fill(0);
    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");
    //set of socket descriptors
    fd_set readfds;
    while(TRUE)
    {
        //clear the socket set 
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        max_sd = find_max_sd(&readfds, client_sockets.data(), MAXCLIENTS, 
                             max_sd);

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select(max_sd + 1, &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            std::perror("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                            (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

            //send new connection greeting message
            if( send(new_socket, message, strlen(message), 0) != strlen(message))
            {
                perror("send");
            }

            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            for (auto & client_sock: client_sockets) {
                //if position is empty
                if(client_sock == 0) {
                    client_sock = new_socket;
                    printf("Adding to list of sockets as %d\n" , new_socket);
                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (int i = 0; i < MAXCLIENTS; i++)
        {
            sd = client_sockets[i];
            if (FD_ISSET( sd , &readfds)) {
                //Check if it was for closing , and also read the
                //incoming message
                printf("Receiving from client\n");
                if ((valread = read( sd , buffer, 1024)) == 0) { 
                    //Somebody disconnected , get his details and print
                    getpeername(sd, (struct sockaddr*)&address,
                            (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" ,
                            inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                    //Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_sockets[i] = 0;
                }
                //Echo back the message that came in
                else
                {
                    //set the string terminating NULL byte on the end
                    //of the data read
                    buffer[valread] = '\0';
                    send(sd , buffer , strlen(buffer) , 0 );
                }
            }
        }
    }
    return 0; 
} 
