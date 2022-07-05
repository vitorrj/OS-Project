#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 256

char str1[MAX];
char str2[MAX];

void compression(char buffer[]);
    void* compressFirstHalf(void* str);
    void* compressSecondHalf(void* str);
    

int main(){
    
    char buffer[MAX] = "aaaaaaaabbbbbbbbccccccddddeeeeeefffffggggghhhzzzppplllqqqquuuoooxxxxmmmcccjjkkkkaaaaauuuuuwwwwwpppplllmmmnnnbbbvvvjhhhhaaaaccccpppoooaaakkkaaaqqqqbbbccccccccrrrrrrwwwwwuuuuaaaazzzzbbbdddhhhhjjjjqqqquuueeeetttzzzzzuuubbbaaaaapppqqqqquutttttiiiiwwwwbbbbccc";
    compression(buffer);

    strcat(str1, str2);
    printf("%s", str1);
}


// RLE COMPRESSION

void compression(char buffer[]){

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, compressFirstHalf, (void*)buffer);
    pthread_create(&thread2, NULL, compressSecondHalf, (void*)buffer);

    pthread_join(thread1, NULL);    
    pthread_join(thread2, NULL);   



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
