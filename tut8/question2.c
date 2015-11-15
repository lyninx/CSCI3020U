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

/// auxillary; loads contents of 'in' for 'priority' and 'secondary' queues.
/// processes with priority of 0 go into 'priority', all others 'secondary'.
void load_processes(FILE* in, node_t** priority, node_t** secondary);


/// auxillary; runs each process in queue.
/// outputs error messages for allocation failures.
void run_processes(node_t** list);

/// auxillary; perfoms allocation of memory.
/// returns index of memory segment, or 'memsize' if no memory is available.
/// @param memory       size of memory block
/// @param avail_mem    memory array
/// @param memsize	   memory size
int q2_alloc(int memory);

/// auxillary; checks if a memory segment is unused.
bool q2_alloc_isfree(int address, int memory);

/// auxillary, deallocates memory block.
/// returns true if successful, false if error.
/// prints error messages.
bool q2_free(int address, int memory);

/// auxillary; creates a child process.
void* launch_process(void* process);

/// convenience; initializes a process
proc init_proc(void);

/// debug only; prints out the contents of avail_mem.
/// NOTE: assumes ownership of avail_mem_lock because...it's bad....
void print_avail_mem(void);

// -----
// --- runtime functions
// -----

// main function
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

// -----
// --- auxillary functions
// -----

// reads in process data from file
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


// function that launches each process
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

// forks into a new process based on the process object
void* launch_process(void* _process)
{
	// cast process
	proc* process = (proc*)_process;

	// alloc
	int addr = q2_alloc(process->memory);
	if(addr == MEMORY)
	{
		printf("Error: unable to allocate memory\n");
		//...todo
	} else {
		process->address = addr;
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

// checks if a memory segment is free
bool q2_alloc_isfree(int k, int count)
{
	// check for any non-null bits
	for(int i = 0; i < count; i++)
		if(avail_mem[i+k] != 0)
			return false;

    // all bits are null
	return true;
}


// function that frees elements of avail_mem
int q2_alloc(int memory)
{

	printf("\n[q2_alloc]Waiting to allocate %d bits\n", memory);
	// acquire lock
	pthread_mutex_lock(&avail_mem_lock);

	printf("[q2_alloc]allocating %d bits\n", memory);

	// search array
	int index = 0;
	while(MEMORY - index >= memory)
	{
		// stop if you've found a free segment
		if(q2_alloc_isfree(index, memory))
			break;

		// iterate
		index++;
	}

	// change array if a block was found
	if(MEMORY - index >= memory)
	{
		// fill with ones (replace with memset or something? Is that a thing?)
		for(int i = 0; i < memory; i++)
			avail_mem[i+index] = 1; 
	} else {
		// signal an error condition
		printf("[q2_alloc]no index was found\n");
		index = MEMORY;
	}

	print_avail_mem();

	// release lock
	printf("[q2_alloc]done allocating %d bits at %d\n", memory, index);
	pthread_mutex_unlock(&avail_mem_lock);

	

	// return the index
	return index;
}

// function that frees elements of avail_mem
bool q2_free(int address, int memory)
{
	printf("[q2_free]Waiting to free %d bits at %d\n", memory, address);
	// acquire lock
	pthread_mutex_lock(&avail_mem_lock);

	printf("[q2_free]freeing %d bits at %d\n", memory, address);

	// erase portion of array
	int index = 0;
	for(index = 0; index < memory; index++)
	{
		if(avail_mem[address + index] == 0)
		{
			fprintf(stderr, "Error: q2 segmentation fault\n");
			break;
		} else {
			avail_mem[address + index] = 0;
		}
	}

	print_avail_mem();

	// release lock
	printf("[q2_free]done freeing %d bits at %d\n", memory, address);
	pthread_mutex_unlock(&avail_mem_lock);

	// check if all items were erased
	return index == memory;
}


// -----
// --- convenience functions
// -----

// initialize process
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

// -----
// --- development only functions
// -----

// print avail_mem array to console
void print_avail_mem(void)
{
	int curr_block_size = 1;
	int curr_block_val = 0;

	printf("[avail_mem]:\n");
	for(int i = 0; i < MEMORY; i++)
	{
		if(avail_mem[i]==curr_block_val && i != MEMORY-1)
		{
			curr_block_size++;
		} else {
			printf("%d\t%ds\n", curr_block_size, curr_block_val);
			curr_block_val = avail_mem[i];
			curr_block_size = 1;

		}
	}

	printf("\n");
}






