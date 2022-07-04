//
// https://www.youtube.com/watch?v=LtXEMwSG5-8
// https://www.youtube.com/watch?v=DboEGcU6rLI&list=PLPyaR5G9aNDvs6TtdpLcVO43_jvxp4emI&index=6
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAX 256

char* readFile(char* filename, char str[]);
void saveFile(char str[]);


int main(int argc, char *argv[]){
    
    if (argv[1] == NULL){
        printf("\nFile name not provided\n\n");
        exit(1);
    }

    // READING FILE
    char str[MAX];
    readFile(argv[1], str);
    
    // CREATING SOCKET AND SETTING UP ITS PARAMETERS
    int sock = socket(AF_INET, SOCK_STREAM, 0 );  // CREATE A TCP

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;         // Which type of address are we connecting to? 
    server_address.sin_port   = htons(9002);     // Define the port and the translates to our struct with htons
    server_address.sin_addr.s_addr = INADDR_ANY; // Connecting to myself at ip 0.0.0.

    int connection_status = connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));  // It returns an integer that will let us know if the the connection has been succesful (0) or (1) failed

    if (connection_status == -1 ){
        printf("There was an error connecting to the remote socket \n\n");
    }

    // RECEIVING AND SENDING DATA FROM SERVER

    printf("\n\n=============================================================\n\n");

    char buffer[MAX];                           
    read(sock, &buffer, MAX);   
    printf("%s", buffer);                      

    sleep(1);
    write(sock, str, MAX);

    sleep(1);
    read(sock, &buffer, MAX);                
    saveFile(buffer);

    printf("\n\n=============================================================\n\n");
    
    close(sock);

    return 0;
}


char* readFile(char* filename, char str[]){

    FILE *file_in;
	file_in = fopen(filename, "r");
	fscanf(file_in,"%s", str);
    fclose(file_in);

    return str;
}

void saveFile(char str[]){

    char fileName[24] = "myFileCompressed.txt";

    FILE *file_out;
    file_out = fopen(fileName, "w");
    fputs(str, file_out);
    fclose(file_out);

    printf("\n%s\n\nsaved on %s", str, fileName); 

}