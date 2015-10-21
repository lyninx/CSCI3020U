#include <stdio.h>
#include <pthread.h>


// total_grade
static double total_grade = 0.0;
static double total_bellcurve = 0.0;
// barrier
pthread_barrier_t read_grades_barr;
pthread_barrier_t total_grade_barr;
pthread_barrier_t total_bellcurve_barr;
pthread_barrier_t bellcurve_file_barr;
pthread_barrier_t save_bellcurve_barr;

// ngrades
#define N_GRADES 10

// read in grades from file
void read_grades(double* list)
{
	// todo
	for (int i = 0; i < N_GRADES; i++)
	{
		list[i] = 0;
	}

	// signal
	int barrier = pthread_barrier_wait(&read_grades_barr);
	if (barrier != PTHREAD_BARRIER_SERIAL_THREAD && barrier != 0)
		return 1;

}

void save_bellcurve(double* grade)
{

	// record grade
	//total_grade += grade;
	
	printf("print grade %d\n", *grade);
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
	double grades[N_GRADES] = { 1.0 };
	pthread_t save_bellcurve_thrs[N_GRADES];

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
	for (int i = 0; i < N_GRADES; i++)
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