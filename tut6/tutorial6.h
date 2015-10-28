#ifndef TUTORIAL6_H
#define TUTORIAL6_H

#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <unistd.h>



// factorial function
int factorial(int val)
{
	if (val == 0)
	{
		return 1;
	} else {
		return val * factorial(val - 1);
	}
}

// factorial function for threading
typedef struct 
{
	int n;
	int* dest;
} factorial_thr_args;

void* factorial_thr(void* pargs)
{
	factorial_thr_args* args = (factorial_thr_args*)pargs;
	*(args->dest) = factorial(args->n);

	return NULL;
}

#endif //TUTORIAL6_H