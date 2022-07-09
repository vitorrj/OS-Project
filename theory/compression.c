#include <stdio.h>
#include <stdlib.h>
#define MAX 81900

int main(){
    
    char str[MAX];
    char strCompressed[MAX];

    FILE *file_in;
	file_in = fopen("stringa.txt", "r");
	fscanf(file_in,"%s", str);
    fclose(file_in);

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
