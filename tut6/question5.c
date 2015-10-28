#include "tutorial6.h"

// number of elements to take from user
#define Q5_NVALUES 5

// size of string buffers
#define Q5_BUFFLEN 256

// file path to numbers for IPC
#define FPATH_NUMBERS "numbers.txt"

// file path for sum for IPC
#define FPATH_SUM "sum.txt"

// format for number prompt
#define PROMPT_FOR_NUMBERS_FMT(d) "Enter %d numbers: ", d

// solution to question 5
int main (int argc, char* argv[]);

// prompts user for nvals numbers and prints to file
void prompt_for_numbers(const int nvals, const char* fpath);

// factorial function
int get_factorial(int val);

// factorial function solutionb
// @param value 	integer value
// @return void
void* factorial(void* value);

// sum output function
int print_sum(const char* fpath);

/// sum factorial function (action of the child process)
/// @param fpath_src	filepath to number source file
/// @param count		number of values to read
/// @param fpath_dest	filepath to sum destination file
/// @return 0, on success
int calculate_factorial_sum(const char* fpath_src, const int count, const char* fpath_dest);

/// barrier that is used to sync the reassignment of the factorial input
pthread_barrier_t acquire_currval_barr;

// sum of factorials
int total_sum = 0;

// semaphore over total_sum
sem_t total_sum_lock;

/*----------------------------------
*	Definitions
*---------------------------------*/

int main(int argc, char*  argv[])
{
	// get the numbers file
	prompt_for_numbers(Q5_NVALUES, FPATH_NUMBERS);

	// start doing stuff with the numbers
	pid_t PID = fork();
	switch(PID)
	{
	// child process
	case 0:
		return calculate_factorial_sum(FPATH_NUMBERS, Q5_NVALUES, FPATH_SUM);
		break;

	// it is neither the parent nor the child.
	case -1:
		return 0;
		break;

	// it's the parent process.
	default:
		break;
	}

	// wait for child to finish their business
	int  status;
	if(wait(&status) == -1)
	{
		fprintf(stderr, "%s\n", "Error: error waiting for child process");
		return 1;
	}


	// print the content of the text file given by the child
	return print_sum(FPATH_SUM);
}


void prompt_for_numbers(const int nvals, const char* fpath)
{
	// current value
	int currval = 0;

	// open output file
	FILE* fout = fopen(fpath, "w");

	// do numbers prompt
	printf(PROMPT_FOR_NUMBERS_FMT(nvals));
	for(int i = 0; i < nvals; i++)
	{
		// get input
		scanf("%d", &currval);

		// print to output
		fprintf(fout, "%d ", currval);

	}

	// close output file
	fclose(fout);
}

// factorial function
int get_factorial(int val)
{
	if (val == 0)
	{
		return 1;
	} else {
		return val * get_factorial(val - 1);
	}
}

void* factorial(void* value)
{
	// copy n
	int n = *(int*)value;

	// indicate that n has been copied
	pthread_barrier_wait(&acquire_currval_barr);

	// print out n
	printf("%d\n", n);
	n = get_factorial(n);
	printf("-->\t%d\n", n);

	//todo
	sem_wait(&total_sum_lock);
	total_sum += n;
	sem_post(&total_sum_lock);


	// done
	return NULL;
}

int calculate_factorial_sum(const char* fpath_src, const int count, const char* fpath_dest)
{
	// initialize semaphore
	sem_init(&total_sum_lock, 0, 1);

	// factorial threads
	pthread_t factorial_thrs[count];

	// open input file
	FILE* fin = fopen(fpath_src, "r");
	if(fin == NULL)
	{
		fprintf(stderr, "Error: file '%s' could not be opened for reading", fpath_src);
		return 1;
	}

	// the next int to calculate the factorial of
	int currval = 0;

	// initialize barrier that gives threads a chance to copy currval
	pthread_barrier_init(&acquire_currval_barr, NULL, 2);

	// launch threads for input value
	for(int i = 0; i < count; i++)
	{
		// get value
		fscanf(fin, "%d", &currval);

		// give value to factorial calculator
		pthread_create(&factorial_thrs[i], NULL, factorial, (void*)&currval);

		// wait politely to get current value back
		pthread_barrier_wait(&acquire_currval_barr);

	}

	// close input file
	fclose(fin);

	// join threads
	for(int i = 0; i < count; i++)
	{
		pthread_join(factorial_thrs[i], NULL);
	}

	// succexxy
	return 0;
}

int print_sum(const char* fpath)
{
	// open file for reading
	FILE* fin = fopen(fpath, "r");
	if(fin == NULL)
	{
		fprintf(stderr, "Error: file '%s' could not be opened for reading\n", fpath);
		return 1;
	}

	// do stuff
	
	// close file
	fclose(fin);
	return 0;
}