#include <pthread.h>


// total_grade
static double total_grade = 0.0;
static double total_bellcurve = 0.0;
// barrier
pthread_barrier_t read_grades_barr;
pthread_barrier_t save_bellcurve_barr;

// ngrades
#define N_GRADES 10

// read in grades from file
void read_grades(int* list)
{
	for (int i = 0; i < N_GRADES; i++)
	{
		list[i] = 0;
	}

}

void save_bellcurve(double grade)
{
	// record grade
	total_grade += grade;

	//do bellcurve
	grade *= 1.50;
	total_bellcurve += grade*1.50;

	// print bellcurve


}


int main(int argc, char* argv[])
{
	// init list
	int list[N_GRADES] = { 1 };

	// init barrier
	pthread_barrier_init(&read_grades_barr, NULL, 1);

	// read grades
	pthread_t thr;
	pthread_create(&thr, 0, read_grades, (void *)list);

	// join
	int barrier = pthread_barrier_wait(&read_grades_barr);
	if (barrier != PTHREAD_BARRIER_SERIAL_THREAD && barrier != 0)
		return 1;
    
    return 0;
}