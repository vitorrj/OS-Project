#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#define MAX 256

void* compressFirstHalf(char str[]);
void* compressSecondHalf(char str[]);

char strCompressed1[MAX];
char strCompressed2[MAX];

int main(){
    
    char str[MAX]       = "aaaaaaaabbbbbbbbccccccddddeeeeeefffffggggghhhzzzppplllqqqquuuoooxxxxmmmcccjjkkkkaaaaauuuuuwwwwwpppplllmmmnnnbbbvvvjhhhhaaaaccccpppoooaaakkkaaaqqqqbbbccccccccrrrrrrwwwwwuuuuaaaazzzzbbbdddhhhhjjjjqqqquuueeeetttzzzzzuuubbbaaaaapppqqqqquutttttiiiiwwwwbbbbccc";

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &compressFirstHalf, str);
    pthread_create(&thread2, NULL, &compressSecondHalf, str);

    pthread_join(thread1, NULL);    
    pthread_join(thread2, NULL);  

    strcat(strCompressed1, strCompressed2);



    printf("%s", strCompressed1);
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
