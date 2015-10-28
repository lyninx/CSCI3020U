#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_LEN 256

int main(){
	
	pid_t PID = 0;
	pid_t PID2 = 0;
	
	PID = fork();

	if(PID == -1){ //If failure to fork()
		printf("Error occured during the fork of the first child process.\n");
		return 0;
	}

	if(PID == 0){ //First Child Process

		char temp[BUFFER_LEN];
		sleep(1);
		FILE* file1 = fopen("child1.txt", "r");

		fgets(temp, BUFFER_LEN, file1);
		printf("%s\n", temp);


	} else{	//Parent Processes
		
		PID2 = fork();

		if(PID2 == -1){ //If failure to fork()
			printf("Error occured during the fork of the second child process.\n");
			return 0;
		}
		
		if(PID2 == 0){ //Second Child Process

			char temp[BUFFER_LEN];
			sleep(1);
			FILE* file2 = fopen("child2.txt", "r");

			fgets(temp, BUFFER_LEN, file2);
			printf("%s\n", temp);

		}else{ //Parent Process Again

			FILE* file1 = fopen("child1.txt", "w");
			fprintf(file1, "child 1");

			FILE* file2 = fopen("child2.txt", "w");
			fprintf(file2, "child 2");
		}
	}
}