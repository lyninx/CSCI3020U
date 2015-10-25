#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 10

int total_grade;
pthread_mutex_t lock;

void *class_total(void* arg){

	int* grade = (int*)arg;

	pthread_mutex_lock(&lock);

	total_grade += *grade;

	pthread_mutex_unlock(&lock);

	return NULL;
}

int main(void)
{
	int grades[NUM_STUDENTS];	
	pthread_t pth[NUM_STUDENTS];

	// initialize lock
	pthread_mutex_init(&lock, 0);

	printf("Enter %d student grades:\n", NUM_STUDENTS);

	for(int i=0; i < NUM_STUDENTS; i++){
		scanf("%d", &grades[i]);	
	}

	for(int i = 0; i < NUM_STUDENTS; i++){
		pthread_create(&pth[i], 0, class_total, (void *)&grades[i]);
	}
	
	for(int i = 0; i < NUM_STUDENTS; i++){
		pthread_join(pth[i], NULL);
	}
	printf("%d\n", total_grade);

	return 0;
}