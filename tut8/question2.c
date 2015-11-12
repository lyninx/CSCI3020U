#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MEMORY 1024
#define FPATH_PROCESSES_Q5 "processes_q5.txt"
#define BUFFER_LEN 256


// runtime
int main(void);

// auxillary; loads contents of 'in' for 'priority' and 'secondary' queues.
// processes with priority of 0 go into 'priority', all others 'secondary'.
void load_processes(FILE* in, node_t** priority, node_t** secondary);


// auxillary; runs each process in queue.
// outputs error messages for allocation failures.
void run_processes(node_t** list, int* avail_mem, int size);

// auxillary; creates a child process.
void launch_process(proc* process);

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
	// command buffer
    char buff[BUFFER_LEN] = { 0 };

    // get each process from file
    while(fgets(buff, BUFFER_LEN, in))
    {
        // make new process object
        proc pobj = init_proc();

    	// parse name
    	strcpy(pobj.name, strtok(buff, ", "));

    	// parse remaining values
    	sscanf(strtok(NULL, "\n"), "%d, %d, %d", &pobj.priority, &pobj.memory, &pobj.runtime);
        
        // insert into appropriate queue
        push(pobj.priority == 0 ? priority : secondary, pobj);
    }
}

void launch_process(proc* process)
{

	// print it
	printf("[%d]process name '%s' priority %d pid %d memory %d runtime %d\n", getpid(), process->name, process->priority, process->pid, process->memory, process->runtime);
    

    // execute it
    //todo
}

void run_processes(node_t** list, int* avail_mem, int size)
{
    while(*list)
    {
        // run it
        launch_process(&(*list)->process);

        // pop it
        pop(list);

    }

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

    // ...
    printf("\nPRIORITY:\n");
    print_list(priority);
    printf("SECONDARY:\n");
    print_list(secondary);
    
    // close the process list
    fclose(fin);

    // execute high priority then low priority
    run_processes(&priority, avail_mem, MEMORY);
    run_processes(&secondary, avail_mem, MEMORY);

    //....
    while(priority)
    {
    	pop(&priority);
    }
    while(secondary)
    	pop(&secondary);
    printf("\nPRIORITY:\n");
    print_list(priority);
    printf("SECONDARY:\n");
    print_list(secondary);


	// return successful
	return 0;
}