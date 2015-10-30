#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define BUFFER_LEN 256
#define NUMBERS 10

int buffer[5] = {0,0,0,0,0};
sem_t sem;

_Bool bufferFull() {
	if (buffer[0] != 0 && buffer[1] != 0 && buffer[2] != 0 && buffer[3] != 0 && buffer[4] != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

_Bool bufferEmpty() {
	if (buffer[0] == 0 && buffer[1] == 0 && buffer[2] == 0 && buffer[3] == 0 && buffer[4] == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void *producer(void* numbers)
{
	int i = 0;
	int currBufferLoc = 0;
	int *nums = (int *)numbers; 

	while (i < NUMBERS) {
		nanosleep(rand()%100);

		if (bufferFull() == 0) {
			sem_wait(&sem);

			buffer[currBufferLoc] = nums[i];
			printf("Produced %i.\n", buffer[currBufferLoc]);

			sem_post(&sem);

			if (currBufferLoc == 4) {
				currBufferLoc = 0;
			} else {
				currBufferLoc++;
			}

			i++;
		}
	}

	return NULL;
}

void *consumer(void* numbers)
{
	int o = 0;
	int currBufferLoc = 0;

	while (o < NUMBERS) {
		nanosleep(rand()%100);

		if (bufferEmpty() == 0) {
			sem_wait(&sem);

			printf("Consumed %i.\n", buffer[currBufferLoc]);
			buffer[currBufferLoc] = 0;

			sem_post(&sem);

			if (currBufferLoc == 4) {
				currBufferLoc = 0;
			} else {
				currBufferLoc++;
			}

			o++;
		}
	}

	return NULL;
}

int main() {

	int numbers[NUMBERS];
	pthread_t producer_t;
	pthread_t consumer_t;
	sem_init(&sem, 0, 1);
	srand(time(NULL));

	printf("Enter %d numbers:\n", NUMBERS);
	for (int i=0; i<NUMBERS; i++) {
		scanf("%i", &numbers[i]);
	}

	pthread_create(&producer_t, 0, producer, (void *)&numbers);
	pthread_create(&consumer_t, 0, consumer, (void *)&numbers);

	pthread_join(producer_t, 0);
	pthread_join(consumer_t, 0);

	sem_destroy(&sem);

	printf("\nEnd buffer:\n");
	for (int i=0; i<5; i++) {
		printf("Location %i: %i\n", i, buffer[i]);
	}
}