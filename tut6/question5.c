#include "tutorial6.h"

// number of elements to take from user
#define Q5_NVALUES 5

// size of string buffers
#define Q5_BUFFLEN 256

// file path to numbers for IPC
#define FPATH_NUMBERS "numbers.txt"

// format for number prompt
#define PROMPT_FOR_NUMBERS_FMT(d) "Enter %d numbers: ", d


void prompt_for_numbers(const int nvals, const char* fpath);

// prompts user for nvals numbers and prints to file
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
// ...
int main(int argc, char*  argv[])
{
	// get the numbers file
	prompt_for_numbers(Q5_NVALUES, FPATH_NUMBERS);

	//

	// stuff
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