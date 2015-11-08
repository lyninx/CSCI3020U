#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"



int main(void) {

	node_t * queue = NULL;
	queue = malloc(sizeof(node_t));
	if (queue == NULL) {
	    return 1;
	}

	proc p;

	p.name = "test";
	p.priority = 1;
	p.pid = 1;
	p.runtime = 0;

	queue->process = p;
	queue->next = NULL;

	push(queue, p);
	push(queue, p);
	print_list(queue);
	
}