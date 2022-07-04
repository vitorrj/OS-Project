#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    
    char buffer[256];


    // Creating the sockets
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Specifiying the protocol, server address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port   = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Calling the bind function to bind ip and port to our socket
    bind(sock, (struct sockaddr*)&server_address, sizeof(server_address));

    // Listening for connections in a maximum of 5
    listen(sock, 5);  // Server socket, how many clients can I have?

    // Accepting the socket
    int client_socket = accept(sock, NULL, NULL  ); // We accept and now we are able to send and receive data, the second parameter is our client socket

    // Send the message and Receiving messages from client
    char server_message[256] = "You have reached the server...\n Waiting for an input\n";
    write(client_socket, server_message, 256);

    sleep(1);
    read(client_socket, buffer, 256);
    printf("\n=============================================================\n\n");
    printf("The string has been received...\n\n%s\n\nStarting compression...", buffer);
    printf("\n\n=============================================================\n");

    sleep(1);
    write(client_socket, server_message, 256);


    close(sock);


    return 0;
}