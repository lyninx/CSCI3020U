#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	pid_t PID = 0;

	PID = fork();
	char *argv[] = { 0 };

	if(PID < 0){ //If failure to fork()
		printf("Error occured during the fork of the first child process.\n");
		return 0;
	}

	if(PID == 0){ //Child Process

		execv("./process", argv);


	} else{ //Parent Process

		sleep(5);
		kill(PID, SIGTSTP);
		sleep(10);
		kill(PID, SIGCONT);
		waitpid(PID, 0, 0);
	}
}