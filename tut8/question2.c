#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define MEMORY 1024
#define FPATH_PROCESSES_Q5 "processes_q5.txt"
#define BUFFER_LEN 256


// available memory
static int avail_mem[MEMORY] = { 0 };

// memory lock
static pthread_mutex_t avail_mem_lock;

// runtime
int main(void);

// auxillary; loads contents of 'in' for 'priority' and 'secondary' queues.
// processes with priority of 0 go into 'priority', all others 'secondary'.
void load_processes(FILE* in, node_t** priority, node_t** secondary);


// auxillary; runs each process in queue.
// outputs error messages for allocation failures.
void run_processes(node_t** list);

// auxillary; perfoms allocation of memory.
// returns index of memory segment, or 'memsize' if no memory is available.
// @param memory       size of memory block
// @param avail_mem    memory array
// @param memsize	   memory size
int q2_alloc(int memory);

// auxillary, deallocates memory block.
// returns true if successful, false if error.
// prints error messages.
bool q2_free(int address, int memory);

// auxillary; creates a child process.
void* launch_process(void* process);

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
	p.address = MEMORY;
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

void* launch_process(void* _process)
{
	// cast process
	proc* process = (proc*)_process;

	// alloc
	if(q2_alloc(process->memory) == MEMORY)
	{
		printf("Error: unable to allocate memory\n");
		//...todo
	}

	// print it
	printf("[%d]process name '%s' priority %d pid %d memory %d runtime %d\n", getpid(), process->name, process->priority, process->pid, process->memory, process->runtime);
    

    // execute it
    //todo

    // dealloc
    if(!q2_free(process->address, process->memory))
    	return NULL; //todo


    // done
    return NULL;
}

int q2_alloc(int memory)
{

	printf("Waiting to allocate %d bits\n", memory);
	// acquire lock
	pthread_mutex_lock(&avail_mem_lock);

	printf("allocating %d bits\n", memory);

	// search array
	int index = 0;
	while(index < MEMORY)
	{
		if(avail_mem[index] == 0)
		{
			//todo
		}

		index++;
	}

	// change array

	// release lock
	printf("done allocating %d bits at %d\n", memory, index);
	pthread_mutex_unlock(&avail_mem_lock);

	

	// return the index
	return index;
}


bool q2_free(int address, int memory)
{
	printf("Waiting to free %d bits at %d\n", memory, address);
	// acquire lock
	pthread_mutex_lock(&avail_mem_lock);

	printf("freeing %d bits at %d\n", memory, address);

	// search array
	int index = 0;
	while(index < memory)
	{
		if(avail_mem[address + index] == 0)
		{
			fprintf(stderr, "Error: q2 segmentation fault\n");
			break;
		} else {
			avail_mem[address + index] = 0;
		}

		index++;
	}


	// change array

	// release lock
	printf("done freeing %d bits at %d\n", memory, address);
	pthread_mutex_unlock(&avail_mem_lock);

	//todo
	return false;
}

void run_processes(node_t** list)
{
	// lock for avail_mem
	pthread_mutex_init(&avail_mem_lock, NULL);

	// go through each list element
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
    run_processes(&priority);
    run_processes(&secondary);

    printf("\nCONSUMED:\nPRIORITY:\n");
    print_list(priority);
    printf("SECONDARY:\n");
    print_list(secondary);

    //....
    while(priority)
    {
    	pop(&priority);
    }
    while(secondary)
    	pop(&secondary);
    printf("\nCLEANED:\nPRIORITY:\n");
    print_list(priority);
    printf("SECONDARY:\n");
    print_list(secondary);


	// return successful
	return 0;
}