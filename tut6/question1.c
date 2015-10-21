#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *hello_world(void *arg){
    int randTime = rand() % 5;
    sleep(randTime);
    printf("%s\n",(char*)arg);
    return NULL;
}

void *goodbye(void *arg){
	int randTime = rand() % 5;
    sleep(randTime);
    printf("%s\n",(char*)arg);
    return NULL;
}


int main() {

    pthread_t pth;
    pthread_t pth2;

    pthread_create(&pth, 0, hello_world, "hello world");
    pthread_create(&pth2, 0, goodbye, "goodbye");

    pthread_join(pth, 0);
    pthread_join(pth2, 0);

    return 0;
}