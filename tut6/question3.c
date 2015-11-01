#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>

#define NUMVALS 5

int moving_sum[NUMVALS];
pthread_t threads[NUMVALS];
typedef struct {
	int value;
	int index;
} thread_data;
sem_t moving_sum_lock;

int get_factorial(int val)
{
	if (val == 0)
	{
		return 1;
	} else {
		return val * get_factorial(val - 1);
	}
}

void* factorial(void* data)
{
	sem_init(&moving_sum_lock, 0, 1);
	thread_data d = *(thread_data*)data;
	int n = get_factorial(d.value);

	while(moving_sum[d.index] == 0){
		sem_wait(&moving_sum_lock);

		if(moving_sum[d.index - 1] > 0 || d.index == 0){
			n = n + moving_sum[d.index - 1];
			moving_sum[d.index] = n;
		}

		sem_post(&moving_sum_lock);		
	}

	return NULL;
}

int main(){


	thread_data t_data[NUMVALS];

	printf("Enter %d numbers:\n", NUMVALS);

	for(int i = 0; i < NUMVALS; i++){
	scanf("%d", &t_data[i].value);
	t_data[i].index = i;

	}

	for(int i = 0; i < NUMVALS; i++){
		pthread_create(&threads[i], NULL, factorial, (void*)&t_data[i].value);
	}

	printf("%s\n", "moving_sum: ");
	for(int i = 0; i < NUMVALS; i++)
	{
		pthread_join(threads[i], NULL);
		printf("%s", "> ");
		printf("%d\n", moving_sum[i]);
	}

}