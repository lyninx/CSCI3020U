#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_LEN 256

int main(){
	
	pid_t PID = 0;

	PID = fork();

	if(PID == -1){ //If failure to fork()
		printf("Error occured during the fork of the first child process.\n");
		return 0;
	}

	if(PID == 0){ //Child Process

		sleep(1);
		printf("Child Process\n");
		exit(1);

	} else{ //Parent Process

		int status = 0;

		wait(&status);

		if(WIFEXITED(status)){
			
			printf("Parent Process\n");
			printf("The return status of the child is %d.\n", WEXITSTATUS(status));
		}
	}
}