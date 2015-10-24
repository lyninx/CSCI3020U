#include <stdio.h>
#include <pthread.h>

#define XOPEN_HEADER 600

// total_grade
static double total_grade = 0.0;
static double total_bellcurve = 0.0;
// barrier
pthread_barrier_t read_grades_barr;
pthread_barrier_t total_grade_barr;
pthread_barrier_t total_bellcurve_barr;
pthread_barrier_t bellcurve_file_barr;
pthread_barrier_t save_bellcurve_barr;

// number of grades to process
#define Q5_N_GRADES 10

// file paths
#define FPATH_GRADES "grades.txt"
#define FPATH_BELLCURVE "bellcurve.txt"

// read in grades from file
// @param dest values from the grades are put here
// @return 0 if no error has occured
int read_grades(double* dest)
{
	// this stores the status of certain operations
	int status = 0;

	// open file
	FILE* grades = fopen(FPATH_GRADES, "r");

	// read stuff in from file
	if (!grades || ferror(grades))
	{
		fprintf(stderr, "Error: error opening %s\n", FPATH_GRADES);
		status = 1;
	}
	else
	{
		// fill each element of array
		for (int i = 0; i < Q5_N_GRADES; i++)
		{
			// get grade
			if (fscanf(grades, "%lf", &dest[i]) != 1)
			{
				// failure to achieve a grade
				status = 2;
				break;
			}
		}

		
	}

	

	// signal
	int barrier_status = pthread_barrier_wait(&read_grades_barr);

	
	// check for file errors
	if (status != 1 && ferror(grades)) {
		fprintf(stderr, "Error: error reading %s\n", FPATH_GRADES);
		status = 1;
	}


	// close file
	status = fclose(grades) == 0 ? status : 3;

	// check barrier errors
	if (barrier_status != PTHREAD_BARRIER_SERIAL_THREAD && barrier_status != 0)
	{
		fprintf(stderr, "Error: barrier failed somehow\n");
		status = 4;
	}

	// return success of barrier & file operations
	return status;
}

void save_bellcurve(double* grade)
{

	// record grade
	//total_grade += grade;
	
	printf("print grade %lf\n", *grade);
	//sleep(50);


	//do bellcurve
	*grade = *grade *1.50;
	//total_bellcurve += grade*1.50;

	// print bellcurve


	// setup join
	pthread_barrier_wait(&save_bellcurve_barr);

}


int main(int argc, char* argv[])
{
	// init list
	double grades[Q5_N_GRADES] = { 1.0 };
	pthread_t save_bellcurve_thrs[Q5_N_GRADES];

	// init barriers
	pthread_barrier_init(&read_grades_barr, NULL, 2);
	pthread_barrier_init(&save_bellcurve_barr, NULL, 11);

	// read grades
	pthread_t thr;
	pthread_create(&thr, 0, read_grades, (void *)grades);
	
	// wait for read grades to finish
	int barrier = pthread_barrier_wait(&read_grades_barr);
	if (barrier != PTHREAD_BARRIER_SERIAL_THREAD && barrier != 0)
		return 1;

	// apply bellcurve
	for (int i = 0; i < Q5_N_GRADES; i++)
	{
		pthread_create(&save_bellcurve_thrs[i], 0, save_bellcurve, (void *)&grades[i]);
	}

	// wait for bellcurve
	barrier = pthread_barrier_wait(&save_bellcurve_barr);
	if (barrier != PTHREAD_BARRIER_SERIAL_THREAD && barrier != 0)
		return 1;

	
    // return
    return 0;
}