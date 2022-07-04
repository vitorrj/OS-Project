#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


void* routine() {
    printf("Test from thread 1\n");
    sleep(3);
    printf("Ending thread\n");
    return 0;
}

int main(){

    pthread_t t1, t2;               // Variable where i save the struct about the thread

    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);

    pthread_join(t1, NULL);     // Like `wait` function for processes
    pthread_join(t2, NULL);     // Like `wait` function for processes

    return 0;
}