#include <stdio.h>
#include <stdlib.h>
#define MAX 256

int main(){
    
    char str[MAX]       = "aaaaaaaabbbbbbbbccccccddddeeeeeefffffggggghhhzzzppplllqqqquuuoooxxxxmmmcccjjkkkkaaaaauuuuuwwwwwpppplllmmmnnnbbbvvvjhhhhaaaaccccpppoooaaakkkaaaqqqqbbbccccccccrrrrrrwwwwwuuuuaaaazzzzbbbdddhhhhjjjjqqqquuueeeetttzzzzzuuubbbaaaaapppqqqqquutttttiiiiwwwwbbbbccc";
    char strCompressed[MAX];

    char currentChar = str[0];
    int count = 1;
    int j = 0;      

    for(int i=1; i < MAX; i++){
        if (str[i] == currentChar){
            count++;
        }    
        else{
            strCompressed[j] = currentChar;
            j++;
            strCompressed[j] = '0' + count ;
            j++;

            currentChar = str[i];
            count = 1;
        }
    }
    strCompressed[j] = currentChar;
    j++;
    strCompressed[j] = '0' + count ;



    printf("%s", strCompressed);
}
