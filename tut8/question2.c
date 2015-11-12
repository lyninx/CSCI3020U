#include "queue.h"
#include <string.h>
#include <stdio.h>

#define MEMORY 1024
#define FPATH_PROCESSES_Q5 "processes_q5.txt"


// runtime
int main(void);

// auxillary; loads contents of 'in' for 'priority' and 'secondary' queues.
// processes with priority of 0 go into 'priority', all others 'secondary'.
void load_processes(FILE* in, node_t** priority, node_t** secondary);

// convenience; initializes a process
proc init_proc(void);

proc init_proc(void)
{
	// initialize
	proc p;

	// initialize name
	p.name[0] = 0;

	// initialize values
	p.priority = 0;
	p.pid = 0;
	p.address = 0;
	p.memory = 0;
	p.runtime = 0;
	p.suspended = true;

	// return process
	return p;
}

void load_processes(FILE* in, node_t** priority, node_t** secondary)
{

	//todo
}

int main(void)
{
	// available memory
	int avail_mem[MEMORY] = { 0 };

	// processes with priority 0
	node_t* priority = NULL;

	// processes with priorities not zero
	node_t* secondary = NULL;

	// try load up 'processes_q5.txt'
    FILE* fin =  fopen(FPATH_PROCESSES_Q5, "r");
    if(!fin)
    {
        fprintf(stderr, "Error: Failed to load '%s'\n", FPATH_PROCESSES_Q5);
        return 1;
    }
    
    // read in stuff from processes
    load_processes(fin, &priority, &secondary);
    
    // close the process list
    fclose(fin);

	// return successful
	return 0;
}