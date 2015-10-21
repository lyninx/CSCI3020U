
#include <stdio.h>
#include <pthread.h>

void *threadFunc(void *arg)
{
    char *str;
    int i = 0;

    str=(char*)arg;

    while(i < 10)
    {
        // Show the thread is running
        printf("On %s\n",str);
        ++i;
    }

    return NULL;
}

void basic_example(void)
{
	// Thread object
	pthread_t pth;
	pthread_t pth2;

	// Create the thread.
	pthread_create(&pth, 0, threadFunc, (void *) "Thread 1");
	pthread_create(&pth2, 0, threadFunc, (void *) "Thread 2");

	// wait for our thread to finish before continuing
	pthread_join(pth, 0);
	pthread_join(pth2, 0);
}

// question 1 funciton
void hello_world(void)
{
	// random sleep duration
	// hello world would go here
}

// question 1 function
void goodbye(void)
{
	// random sleep duration
	// say goodbye would go here
}


// question 2 function
void bellcurve(double grade)
{
	// rpint grade * 1.50
}

// question 4 constant
static double total_grade = 0.0;

// question 4 function
void class_total(double grade)
{
	//todo
}

// question 5 function
void read_grades(void)
{
	//todo
}

// question 1 program
void do_q1(void)
{
	//todo
}

// question 2 program
void do_q2(void)
{
	//todo
}

// question 3 program
void do_q3(void)
{
	//todo
}

//question 4 program
void do_q4(void)
{
	//todo
}

//question 5 program
void do_q5(void)
{
	//todo
}

/**
 * Basic example that showing threading interleaving.
 */
int main(int argc, char *argv[]) {
	if (argc < 2)
	{
		basic_example();
	}
	else {
		switch ((int)(argv[1][0]))
		{
		case '1':
			do_q1();
			break;

		case '2':
			do_q2();
			break;

		case '3':
			do_q3();
			break;

		case '4':
			do_q4();
			break;

		case '5':
			do_q5();
			break;

		default:
			basic_example();
			break;
		}
	}



	
}