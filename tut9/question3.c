#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>

#define NUM_INTS 100000000
int nums[NUM_INTS];

int main(void)
{
	srand((unsigned)time(NULL));
	int range = 100;
	double sum = 0;
	float norm = 0;
	float start = 0;
	float finish = 0;
	float run = 0;
	float run2 = 0;

	// Generate random integers from 0 to 100
	for(int i = 0; i < NUM_INTS; i++){
		nums[i] = rand() % (range+1);
	}

	start = omp_get_wtime();
	for(int i = 0; i < NUM_INTS; i++){
		sum = sum + nums[i];
	}
	finish = omp_get_wtime();

	run = finish - start;
	norm = sum/NUM_INTS;

	printf("SERIAL\n");
	printf("Sum: %f\n", sum);
	// This sum doesn't make sense, the reduction sum makes sense.
	printf("Average: %f\n",norm);
	printf("Runtime: %f\n",run);

	sum = 0;

	start = omp_get_wtime();
	#pragma omp parallel for reduction(+:sum) 
	for(int i = 0; i < NUM_INTS; i++){
		sum = sum + nums[i];
	}
	finish = omp_get_wtime();

	run2 = finish - start;
	norm = sum/NUM_INTS;

	printf("PARALLEL\n");
	printf("Sum: %f\n", sum);
	printf("Average: %f\n",norm);
	printf("Runtime: %f\n",run2);

	run = run - run2;
	printf("\n");
	printf("time save: %f\n",run);

	return 0;
}