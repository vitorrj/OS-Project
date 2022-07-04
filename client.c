/******************************************************
 *        Operating Systems Final Project               *
 *      Vitor Rodrigues Jacinto  0327000633           *
 *              A.A 2021/2022                         *
 *      Prof Luigi Romano & Giovanni Mazzeo           *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAX 256

char* readFile(char* filename, char str[]);
void saveFile(char str[], char filename[], char option);


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

    printf("\n\n=========================== CLIENT ==================================\n\n");

    char buffer[MAX];

    read(sock, &buffer, MAX);   
    printf("%s", buffer);    

    sleep(1);
    fgets(buffer, MAX, stdin);
    char option = buffer[0];
    write(sock, buffer, MAX);

    sleep(1);
    write(sock, str, MAX);

    sleep(1);
    read(sock, &buffer, MAX);             
    
    if (strcmp(buffer,"Error")==0){
        printf("\nOperation not valid, Aborting...\n\n");
        close(sock);
        exit(1);
    }
    
    saveFile(buffer, argv[1], option);

    printf("\n\n=====================================================================\n\n");
    
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

void saveFile(char str[], char filename[], char option){

    char newFilename[50];
    int i = 0;

    while(filename[i] != '.'){
        newFilename[i] = filename[i];
        i++;
    }

    switch (option){
    case '1':
        strcat(newFilename, "Compressed.txt");
        break;
    
    case '2':
        strcat(newFilename, "Decompressed.txt");
        break;
    }

    FILE *file_out;
    file_out = fopen(newFilename, "w");
    fputs(str, file_out);
    fclose(file_out);

    printf("\n%s\n\nsaved on %s", str, newFilename); 

}