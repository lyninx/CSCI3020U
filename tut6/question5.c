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
int calculate_factorial(int val);

// factorial function solution
void* factorial(void* pargs);

// sum output function
void print_sum(const char* fpath);

/// sum factorial function (action of the child process)
/// @param fpath_src	filepath to number source file
/// @param fpath_dest	filepath to sum destination file
/// @return 0, on success
int do_sum_factorial(const char* fpath_src, const char* fpath_dest);


// args struct for factorial
typedef struct 
{
	int n;
	int* dest;
} factorial_args;


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
		return do_sum_factorial(FPATH_NUMBERS, FPATH_SUM);
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
	print_sum(FPATH_SUM);

	// stuff
	/*printf("%d\n", calculate_factorial(2));

	factorial_args args;
	int val;
	args.n = 5;
	args.dest = &val;
	pthread_t thr;
	pthread_create(&thr, NULL, factorial, (void*)&args);
	pthread_join(thr, NULL);
	printf("%d\n", val);*/

	return 0;
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
int calculate_factorial(int val)
{
	if (val == 0)
	{
		return 1;
	} else {
		return val * calculate_factorial(val - 1);
	}
}

void* factorial(void* pargs)
{
	factorial_args* args = (factorial_args*)pargs;
	*(args->dest) = calculate_factorial(args->n);

	return NULL;
}

int do_sum_factorial(const char* fpath_src, const char* fpath_dest)
{
	//todo
	return 0;
}

void print_sum(const char* fpath)
{
	//todo
}