#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_LEN 256

int main(void) {
	pid_t PID = fork();
	char *agrv[] = {0};

	if (PID == 0) { // Child process.
      	execv("./process", agrv);
    } else if (PID < 0) { // If the forking fails.
    	printf("Error occured during the fork of the first child process.");
    	return 0;
  	} else { // Parent process.
   		sleep(5);
   		kill(PID,SIGINT);
	}	
}