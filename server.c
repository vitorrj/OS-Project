#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX 256

void* compressFirstHalf(char str[]);
void* compressSecondHalf(char str[]);

char strCompressed1[MAX];
char strCompressed2[MAX];

int main(){
    
    char buffer[MAX];
    
    // CREATING SOCKET AND SETTING UP ITS PARAMETERS
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port   = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&server_address, sizeof(server_address));
   
    listen(sock, 5);  // Server socket, how many clients can I have?
    
    int client_socket = accept(sock, NULL, NULL  ); // We accept and now we are able to send and receive data, the second parameter is our client socket


    // RECEIVING AND SENDING DATA TO CLIENT
    char server_message[MAX] = "You have reached the server. Starting compression...\n";
    write(client_socket, server_message, MAX);

    sleep(1);
    read(client_socket, buffer, MAX);
    printf("\n=============================================================\n\n");
    printf("The string has been received. \n\n%s\n\nStarting compression...\n\n", buffer);

    sleep(1);

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &compressFirstHalf, buffer);
    pthread_create(&thread2, NULL, &compressSecondHalf, buffer);

    pthread_join(thread1, NULL);    
    pthread_join(thread2, NULL);   

    strcat(strCompressed1, strCompressed2);
    printf("%s", strCompressed1);

    printf("\n\n=============================================================\n\n");

    sleep(1);
    write(client_socket, strCompressed1, MAX);

    close(client_socket);
    close(sock);


    return 0;
}



void* compressFirstHalf(char str[]){

    char currentChar = str[0];
    int count = 1;
    int j = 0;      

    for(int i=1; i < MAX/2; i++){
        if (str[i] == currentChar){
            count++;
        }    
        else{
            strCompressed1[j] = currentChar;
            j++;
            strCompressed1[j] = '0' + count ;
            j++;

            currentChar = str[i];
            count = 1;
        }
    }
    strCompressed1[j] = currentChar;
    j++;
    strCompressed1[j] = '0' + count ;


    return strCompressed1;
    pthread_exit(NULL);

}

void* compressSecondHalf(char str[]){

    char currentChar = str[0];
    int count = 1;
    int j = 0;      

    for(int i=MAX/2; i < MAX; i++){
        if (str[i] == currentChar){
            count++;
        }    
        else{
            strCompressed2[j] = currentChar;
            j++;
            strCompressed2[j] = '0' + count;
            j++;

            currentChar = str[i];
            count = 1;
        }
    }
    strCompressed2[j] = currentChar;
    j++;
    strCompressed2[j] = '0' + count ;
    
    return strCompressed2;
    pthread_exit(NULL);

}