#include <stdio.h>
#include <pthread.h>

#define XOPEN_HEADER 600

// total_grade
static double total_grade = 0.0;
static double total_bellcurve = 0.0;

// barriers
pthread_barrier_t grades_read_barr;
pthread_barrier_t grades_sum_barr;
pthread_barrier_t bellcurve_sum_barr;
pthread_barrier_t bellcurve_saved_barr;

// mutual exclusion
pthread_mutex_t bellcurve_file_lock;
pthread_mutex_t total_grade_lock;
pthread_mutex_t total_bellcurve_lock;
pthread_mutex_t grades_sum_barr_lock;
pthread_mutex_t bellcurve_sum_barr_lock;

// number of grades to process
#define Q5_N_GRADES 10

// ceiling on how good you can do
#define Q5_MAX_GRADE 100.0f

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
	int barrier_status = pthread_barrier_wait(&grades_read_barr);

	
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
	// save grade before bellcurve
	double grade_val = *grade;

	// record grade
	printf("1[%lf] waiting to add grade\n", grade_val);
	pthread_mutex_lock(&total_grade_lock);
	printf("1[%lf] acquired grade lock\n", grade_val);
	total_grade += grade_val;
	printf("1[%lf] releasing grade lock\n", grade_val);
	pthread_mutex_unlock(&total_grade_lock);


	// wait around until the main thread recognizes what you did
	printf("2[%lf] ready to report total_grade\n", grade_val);
	pthread_mutex_lock(&grades_sum_barr_lock);
	printf("2[%lf] reporting total_grade\n", grade_val);
	pthread_barrier_wait(&grades_sum_barr);
	printf("2[%lf] move on from total_grade\n", grade_val);
	pthread_mutex_unlock(&grades_sum_barr_lock);

	// apply bellcurve
	double bellcurve_val = (bellcurve_val = grade_val*1.50f) > Q5_MAX_GRADE ? Q5_MAX_GRADE : bellcurve_val;

	//do bellcurve
	printf("3[%lf] waiting to add bellcurve\n", grade_val);
	pthread_mutex_lock(&total_bellcurve_lock);
	printf("3[%lf] acquired bellcurve lock\n", grade_val);
	total_bellcurve += bellcurve_val;
	printf("3[%lf] releasing bellcurve lock\n", grade_val);
	pthread_mutex_unlock(&total_bellcurve_lock);

	// wait around until the main thread recognizes what you did x2
	printf("4[%lf] bellcurve report ready to\n", grade_val);
	pthread_mutex_lock(&bellcurve_sum_barr_lock);
	printf("4[%lf] bellcurve report doing it\n", grade_val);
	pthread_barrier_wait(&bellcurve_sum_barr);
	printf("4[%lf] bellcurve report passing baton\n", grade_val);
	pthread_mutex_unlock(&bellcurve_sum_barr_lock);

	// print bellcurve
	printf("5[%lf] save bellcurve: ready to write to file\n", grade_val);
	pthread_mutex_lock(&bellcurve_file_lock);
	printf("5[%lf] save bellcurve: opening up file for writing\n", grade_val);
	FILE* bellcurvef = fopen(FPATH_BELLCURVE, "a");
	if (!bellcurvef)
	{
		fprintf(stderr, "Error: could not open '%s' for writing\n", FPATH_BELLCURVE);
	}
	else
	{
		fprintf(bellcurvef, "%lf\n", bellcurve_val);
	}
	fclose(bellcurvef);
	printf("5[%lf] save bellcurve: finished saving bellcurve\n", grade_val);
	pthread_mutex_unlock(&bellcurve_file_lock);


	// setup join
	printf("6[%lf] My work here is done\n", grade_val);
	pthread_barrier_wait(&bellcurve_saved_barr);
	printf("passed barrier\n");

}


int main(int argc, char* argv[])
{
	// init list
	double grades[Q5_N_GRADES] = { 1.0 };
	pthread_t save_bellcurve_thrs[Q5_N_GRADES];

	// averages
	double grades_average = 0.0f;
	double bellcurve_average = 0.0f;

	// init barriers
	pthread_barrier_init(&grades_read_barr, NULL, 2);
	pthread_barrier_init(&grades_sum_barr, NULL, 2);
	pthread_barrier_init(&bellcurve_sum_barr, NULL, 2);
	pthread_barrier_init(&bellcurve_saved_barr, NULL, Q5_N_GRADES + 1);

	// init mutual exclusion
	pthread_mutex_init(&bellcurve_file_lock, NULL);
	pthread_mutex_init(&total_bellcurve_lock, NULL);
	pthread_mutex_init(&total_grade_lock, NULL);
	pthread_mutex_init(&grades_sum_barr_lock, NULL);
	pthread_mutex_init(&bellcurve_sum_barr_lock, NULL);

	// read grades
	pthread_t readgrades_thr;
	pthread_create(&readgrades_thr, 0, read_grades, (void *)grades);
	int barrier = pthread_barrier_wait(&grades_read_barr);
	if (barrier != PTHREAD_BARRIER_SERIAL_THREAD && barrier != 0)
		return 1;

	// create sum/bellcurve threads
	for (int i = 0; i < Q5_N_GRADES; i++)
	{
		pthread_create(&save_bellcurve_thrs[i], 0, save_bellcurve, (void *)&grades[i]);
	}

	// wait for grades
	for (int i = 0; i < Q5_N_GRADES; i++)
	{
		printf("[main]waiting for grades from %d\n", i);
		barrier = pthread_barrier_wait(&grades_sum_barr);
		if (barrier != PTHREAD_BARRIER_SERIAL_THREAD && barrier != 0)
			return 1;
	}

	// get average for grades (humoring the mutex lock respectfully)
	printf("[main] calculating grade average...\n");
	pthread_mutex_lock(&total_grade_lock);
	grades_average = total_grade / (double)Q5_N_GRADES;
	pthread_mutex_unlock(&total_grade_lock);

	// wait for bellcurve
	for (int i = 0; i < Q5_N_GRADES; i++)
	{
		printf("[main]waiting for bellcurve from %d\n", i);
		barrier = pthread_barrier_wait(&bellcurve_sum_barr);
		if (barrier != PTHREAD_BARRIER_SERIAL_THREAD && barrier != 0)
			return 1;
	}
	
	// get average for grades (humoring the mutex lock respectfully)
	printf("[main] calculating bellcurved average...\n");
	pthread_mutex_lock(&total_bellcurve_lock);
	bellcurve_average = total_bellcurve / (double)Q5_N_GRADES;
	pthread_mutex_unlock(&total_bellcurve_lock);

	// wait for bellcurve to be saved to file
	printf("[main] waiting to output results...\n");
	barrier = pthread_barrier_wait(&bellcurve_saved_barr);
	if (barrier != PTHREAD_BARRIER_SERIAL_THREAD && barrier != 0)
		return 1;


	// join all threads
	printf("[main] waiting for threads to terminate...\n");
	pthread_join(readgrades_thr, 0);
	for (int i = 0; i < Q5_N_GRADES; i++)
	{
		pthread_join(save_bellcurve_thrs[i], 0);
	}


	// display stats
	printf("[main] gonna put out the results...\n");
	printf("Average before bellcurve: %lf\n", grades_average);
	printf("Average after bellcurve: %lf\n", bellcurve_average);

	
    // return
    return 0;
}