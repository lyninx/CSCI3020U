#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 5

int main(void)
{
	char *students[NUM_STUDENTS];	
	printf("Enter %d student names:\n", NUM_STUDENTS);

	for(int i=0; i < NUM_STUDENTS; i++){
		scanf("%s", &students[i]);	
	}
	

	return 0;
}