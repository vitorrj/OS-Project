/******************************************************
 *        Operating Systems Final Project             *
 *      Vitor Rodrigues Jacinto  0327000633           *
 *              A.A 2021/2022                         *
 *      Prof Luigi Romano & Giovanni Mazzeo           *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX 256

char str1[MAX];
char str2[MAX];

void compression(char buffer[], int sock, int client_socket);
    void* compressFirstHalf(void* buffer);
    void* compressSecondHalf(void* buffer);
void decompression(char buffer[], int sock, int client_socket);
    void* decompressFirstHalf(void *buffer);
    void* decompressSecondHalf(void *buffer);
    

int main(){
    
    char buffer[MAX];
    
    // CREATING SOCKET AND SETTING UP ITS PARAMETERS
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port   = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&server_address, sizeof(server_address));

    printf("\n============================ SERVER =================================\n\n");
   
    listen(sock, 5);  // Server socket, how many clients can I have?
    
    int client_socket = accept(sock, NULL, NULL  ); // We accept and now we are able to send and receive data, the second parameter is our client socket

    // RECEIVING AND SENDING DATA TO CLIENT
    char server_message[MAX] = "You have reached the server. Please, press\n 1. Compression\n 2. Decompression\n\nOption: ";
    write(client_socket, server_message, MAX);

    read(client_socket, buffer, MAX);
    char option = buffer[0];
    
    read(client_socket, buffer, MAX);



    // COMPRESSING OR DECOMPRESSING FILES
    if(option == '1'){
        compression(buffer, sock, client_socket);

    }
    else if(option == '2'){
        decompression(buffer, sock, client_socket);
    }
    else{
        char errorMessage[MAX] = "Error";
        write(client_socket, errorMessage, MAX);
        close(client_socket);
        close(sock);
        exit(1);
    }


    return 0;
}


// RLE COMPRESSION

void compression(char buffer[], int sock, int client_socket){

    printf("The string has been received. \n\n%s\n\nStarting compression...\n\n", buffer);
    sleep(1);

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &compressFirstHalf, (void*)buffer);
    pthread_create(&thread2, NULL, &compressSecondHalf, (void*)buffer);

    pthread_join(thread1, NULL);    
    pthread_join(thread2, NULL);   

    strcat(str1, str2);
    printf("%s", str1);
    printf("\n\n=====================================================================\n\n");

    sleep(1);
    write(client_socket, str1, MAX);

    close(client_socket);
    close(sock);

}


void* compressFirstHalf(void* buffer){

    char *str = buffer;

    char currentChar = str[0];
    int count = 1;
    int j = 0;      

    for(int i=1; i < MAX/2; i++){
        if (str[i] == currentChar){
            count++;
        }    
        else{
            str1[j] = currentChar;
            j++;
            str1[j] = '0' + count ;
            j++;

            currentChar = str[i];
            count = 1;
        }
    }
    str1[j] = currentChar;
    j++;
    str1[j] = '0' + count ;


    return str1;
    pthread_exit(NULL);

}

void* compressSecondHalf(void* buffer){

    char *str = buffer;

    char currentChar = str[0];
    int count = 1;
    int j = 0;      

    for(int i=MAX/2; i < MAX; i++){
        if (str[i] == currentChar){
            count++;
        }    
        else{
            str2[j] = currentChar;
            j++;
            str2[j] = '0' + count;
            j++;

            currentChar = str[i];
            count = 1;
        }
    }
    str2[j] = currentChar;
    j++;
    str2[j] = '0' + count ;
    
    return str2;
    pthread_exit(NULL);

}

// RLE DECOMPRESSION 
void decompression(char buffer[], int sock, int client_socket){

    printf("The string has been received. \n\n%s\n\nStarting decompression...\n\n", buffer);
    sleep(1);

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, decompressFirstHalf, buffer);
    pthread_create(&thread2, NULL, decompressSecondHalf, buffer);

    pthread_join(thread1, NULL);    
    pthread_join(thread2, NULL);   

    strcat(str1, str2);
    printf("%s", str1);
    printf("\n\n=====================================================================\n\n");

    sleep(1);
    write(client_socket, str1, MAX);

    close(client_socket);
    close(sock);

}

void* decompressFirstHalf(void *buffer){

    char *str = buffer;

    int n = strlen(buffer);
    int index = 0;

    for(int i = 0; i<(n-1)/2; i=i+2){
        
        int count = str[i+1] - '0';

        for(int j = index; j < (index+count); j++){
            str1[j] = str[i];
        }
        index = index + count; 
    }

    return str1;
    pthread_exit(NULL);

}

void* decompressSecondHalf(void* buffer){

    char *str = buffer;

    int n = strlen(buffer);
    int index = 0;

    for(int i = (n-1)/2; i<n; i=i+2){
        
        int count = str[i+1] - '0';

        for(int j = index; j<(index+count); j++){
            str2[j] = str[i];

        }
        index = index + count;
    }

    return str2;
    pthread_exit(NULL);
}
