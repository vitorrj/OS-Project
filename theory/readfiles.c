#include <stdio.h>
#include <string.h>

void readFile(char *filename);

int main(){


	readFile("stringa.txt");
    
    return 0;

}

void readFile(char *filename){

    char string[256];

    FILE *file_in;
	file_in = fopen(filename, "r");

	fscanf(file_in,"%s", string);

    return string;

}