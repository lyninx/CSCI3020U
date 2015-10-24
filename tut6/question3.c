#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 5

typedef struct
{
	char name[50];
	int student_id;
	int grade;
} Student; 

void* bellcurve(void* arg)
{
	Student* student = (Student*) arg;

	student->grade = student->grade*1.5;

	printf("\nStudent Name: %s\n", student->name);
	printf("Student ID: %i\n", student->student_id);
	printf("Bellcurved Student Grade: %i\n", student->grade);

	return NULL;
}

int main(void)
{
	Student students[NUM_STUDENTS];
	pthread_t pth[NUM_STUDENTS];

	for (int i=0; i < NUM_STUDENTS; i++) {
		printf("\nEnter student #%i's name:\n", i+1);
		scanf("%s", students[i].name);	
		printf("Enter %s's student id number:\n", students[i].name);
		scanf("%i", &students[i].student_id);	
		printf("Enter %s's grade:\n", students[i].name);
		scanf("%i", &students[i].grade);	
	}

	for (int i = 0; i < NUM_STUDENTS; i++) {
		pthread_create(&pth[i], 0, bellcurve, (void *)&students[i]);
	}

	for(int i = 0; i < NUM_STUDENTS; i++) {
		pthread_join(pth[i], NULL);
	}

	return 0;
}