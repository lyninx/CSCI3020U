#include "tutorial6.h"

// ...
int main(int argc, char*  argv[])

{
	printf("%d\n", factorial(2));

	factorial_thr_args args;
	int val;
	args.n = 5;
	args.dest = &val;
	pthread_t thr;
	pthread_create(&thr, NULL, factorial_thr, (void*)&args);
	pthread_join(thr, NULL);
	printf("%d\n", val);

	return 0;
}