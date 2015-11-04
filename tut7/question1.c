#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"



void push(proc p){
	queue q;
	q.process = p;
	q.next = NULL;

	printf("%d", q.process);
}
int main(void) {

	proc p;

	p.name = "test";
	p.priority = 1;
	p.pid = 1;
	p.runtime = 0;

	push(p);
	printf("test\n");
	
}