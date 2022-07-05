//
// https://www.youtube.com/watch?v=LtXEMwSG5-8
//https://www.youtube.com/watch?v=DboEGcU6rLI&list=PLPyaR5G9aNDvs6TtdpLcVO43_jvxp4emI&index=6
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(){

    // Creating network socket
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0 );  // CREATE A TCP

    // Specifying an address that we will connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;         // Which type of address are we connecting to? 
    server_address.sin_port   = htons(9002);     // Define the port and the translates to our struct with htons
    server_address.sin_addr.s_addr = INADDR_ANY; // Connecting to myself at ip 0.0.0.

    // Connecting to the socket
    int connection_status = connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));  // It returns an integer that will let us know if the the connection has been succesful (0) or (1) failed

    if (connection_status == -1 ){
        printf("There was an error connecting to the remote socket \n\n");
    }

    
    // Receiving and writing data from the server
    char buffer[256];                           // Where I eventually will store the data to receive from server
    read(sock, &buffer, sizeof(buffer));     // Receive the socket ahd store in the buffer
    printf("%s", buffer);                       // Print the message from server    

    sleep(1);
    char clientMessage[256] = "This is my first phrase\n";
    write(sock, clientMessage, sizeof(clientMessage));

    read(sock, &buffer, sizeof(buffer));     // Receive the socket ahd store in the buffer
    printf("%s", buffer);                       // Print the message from server    


    close(sock);



    return 0;
}