#include <stdio.h>
#include <string.h>

void decompression(char str[]);


int main(){
    
    char str[10] = "a4b3c6d2";

    decompression(str);

}


void decompression(char str[]){

    char strUncompressed[50];
    
    int n = strlen(str);
    int index = 0;

    for(int i = 0; i<(n-1); i=i+2){
        
        int count = str[i+1] - '0';

        for(int j = index; j<(index+count); j++){
            strUncompressed[j] = str[i];

        }
        index = index + count;
    }

    printf("%s", strUncompressed);
}
