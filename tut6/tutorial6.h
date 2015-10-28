#ifndef TUTORIAL6_H
#define TUTORIAL6_H

#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>



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

#endif //TUTORIAL6_H