#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 5

void *bellcurve(void* grade)
{
	int* gr = (int*)grade;
	//do bellcurve
	float result = (*gr) * 1.50;
	printf("%f\n", result);

	return 0;
}
int main(void)
{
	int grades[NUM_STUDENTS];
	pthread_t t[NUM_STUDENTS];

	printf("Enter %d student grades:\n", NUM_STUDENTS);

	// Enter grades
	for(int i=0; i < NUM_STUDENTS; i++){
		scanf("%d", &grades[i]);
			
	}
	printf("Adjusted grades:\n");
	// run bellcurve on a seperate thread for each student
	for(int i=0; i < NUM_STUDENTS; i++){
		pthread_create(&t[i], 0, bellcurve, (void *)&grades[i]);	
	}
	
	// join threads
	for(int i = 0; i < NUM_STUDENTS; i++){
		pthread_join(t[i], 0);
	}

	return 0;
}
