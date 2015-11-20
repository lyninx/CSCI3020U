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
	int range = 200;
	float sum = 0;
	float norm = 0;
	float start = 0;
	float finish = 0;
	float run = 0;
	float run2 = 0;

	// generate random integers from 0 to 100
	for(int i = 0; i < NUM_INTS; i++){
		nums[i] = rand() % range;
		//printf("%d\n",nums[i]);
	}

	start = omp_get_wtime();
	for(int i = 0; i < NUM_INTS; i++){
		sum = sum + nums[i];
	}
	finish =  omp_get_wtime();

	run = finish - start;
	norm = sum/NUM_INTS;

	printf("SERIAL");
	printf("average: %f\n",norm);
	printf("runtime: %f\n",run);

	start = omp_get_wtime();
	#pragma omp parallel for shared(nums) private(sum) 
	for(int i = 0; i < NUM_INTS; i++){
		sum = sum + nums[i];
	}
	finish =  omp_get_wtime();
	run2 = finish - start;

	norm = sum/NUM_INTS;

	printf("PARALLEL");
	printf("average: %f\n",norm);
	printf("runtime: %f\n",run2);

	run = run - run2;
	printf("\n");
	printf("time save: %f\n",run);

	return 0;
}