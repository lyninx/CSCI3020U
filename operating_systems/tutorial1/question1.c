#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// QUESTION 5

double euclid_dist(int x1, int y1, int x2, int y2){
	return sqrt(pow((x1 - y1),2) + pow((x2 - y2),2));;
}

int main(void)
{	
	time_t t;
	srand((unsigned) time(&t));

	for(int i; i<10; i++){
		int x1 = rand() % 101;
		int x2 = rand() % 101;
		int y1 = rand() % 101;
		int y2 = rand() % 101;
		double d = euclid_dist(x1, y1, x2, y2);
		printf("X1: %d Y1: %d X2: %d Y2: %d  || Euclidian Distance = %f\n", x1, y1, x2, y2, d);
	}
}