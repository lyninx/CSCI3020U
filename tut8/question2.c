#define _XOPEN_SOURCE 600
#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MEMORY 1024
#define FPATH_PROCESSES_Q5 "processes_q5.txt"
#define BUFFER_LEN 256

// runtime
int main(void);

/// auxillary; loads contents of 'in' for 'priority' and 'secondary' queues.
/// processes with priority of 0 go into 'priority', all others 'secondary'.
void load_processes(FILE* in, node_t** priority, node_t** secondary);


/// auxillary; runs each process in priority and secondary queues.
/// outputs error messages for allocation failures.
void run_processes(node_t** priority, node_t** secondary);

/// auxillary; perfoms allocation of memory.
/// returns index of memory segment, or 'memsize' if no memory is available.
/// @param memory       size of memory block
/// @param avail_mem    memory array
/// @param memsize	   memory size
int q2_alloc(int memory, int* avail_mem, int memsize);

/// convenience; checks if a memory segment is unused.
bool q2_alloc_isfree(int address, int memory, const int* avail_mem);

/// auxillary, deallocates memory block.
/// returns true if successful, false if error.
/// prints error messages.
bool q2_free(int address, int memory, int* avail_mem);

/// convenience; initializes a process
proc init_proc(void);

/// debug only; prints out the contents of avail_mem.
void print_avail_mem(const int* avail_mem, int memsize);

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
    
    // close the process list
    fclose(fin);

    // execute high priority then low priority
    run_processes(&priority, &secondary);

    // clear leftovers (just in case)
    while(priority)
    	pop(&priority);
    while(secondary)
    	pop(&secondary);


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
void run_processes(node_t** priority, node_t** secondary)
{

	// available memory
	int avail_mem[MEMORY] = { 0 };

	// initialize with null args
    char* argv[] = {NULL};

	// run priority processes
	while(*priority)
	{
		// pop current process
		proc process = (*priority)->process;
		pop(priority);

		// allocate memory
		process.address = q2_alloc(process.memory, avail_mem, MEMORY);

		// todo
		// initialize process
		process.pid = fork();
		if(process.pid == 0)
		{
			printf("%s, %d, %d, %d, %d\n", process.name, process.priority, getpid(), process.memory, process.runtime);
			execv("./process", argv);
			exit(1);
		} else if (process.pid < 0) {
			fprintf(stderr, "Error: failed to fork\n");
		} else {
			// run process

			sleep(process.runtime);

			kill(process.pid, SIGINT);

			// todo
			waitpid(process.pid, 0, 0);

			// free memory
			q2_free(process.address, process.memory, avail_mem);
		}
	}

	// run secondary processes
	while(*secondary)
	{
		proc process = (*secondary)->process;
		pop(secondary);
		if(process.pid == 0)
		{
			// allocate memory
			process.address = q2_alloc(process.memory, avail_mem, MEMORY);

			// allocation failure
			if(process.address == MEMORY)
			{
				//repush
				push(secondary, process);

			} else {
				// initialize process
				process.pid = fork();
				if(process.pid == 0)
				{
					printf("%s, %d, %d, %d, %d\n", process.name, process.priority, getpid(), process.memory, process.runtime);
					execv("./process", argv);
					exit(1);
				} else if (process.pid < 0) {
					fprintf(stderr, "Error: failed to fork\n");
				} else {
					// do stuff
					sleep(1);
					process.runtime -=1;
					kill(process.pid, SIGTSTP);
					process.suspended = true;

					//repush
					push(secondary, process);
				}
			}

			
		}
		else
		{
			// check if process is suspenders
			if(process.suspended)
			{
				// wait a second for signals to catch up
				sleep(1);

				// unsuspend
				process.suspended = false;
				kill(process.pid, SIGCONT);
			}

			// go for 1 tick
			sleep(1);
			process.runtime -= 1;

			// suspend or terminate based on runtime
			if(process.runtime > 0)
			{
				// suspend
				kill(process.pid, SIGTSTP);
				process.suspended = true;

				//repush
				push(secondary, process);
			} else {

				// kill
				kill(process.pid, SIGINT);
				waitpid(process.pid, 0, 0);

				// free memory
				q2_free(process.address, process.memory, avail_mem);
			}
		}
	}
}




// function that frees elements of avail_mem
int q2_alloc(int memory, int* avail_mem, int memsize)
{

	// search array
	int index = 0;
	while(memory - index >= memory)
	{
		// stop if you've found a free segment
		if(q2_alloc_isfree(index, memory, avail_mem))
			break;

		// iterate
		index++;
	}

	// change array if a block was found
	if(memory - index >= memory)
	{
		// fill with ones (replace with memset or something? Is that a thing?)
		for(int i = 0; i < memory; i++)
			avail_mem[i+index] = 1; 
	} else {
		// signal an error condition
		index = memsize;
	}

	// return the index
	return index;
}

// function that frees elements of avail_mem
bool q2_free(int address, int memory, int* avail_mem)
{

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


// checks if a memory segment is free
bool q2_alloc_isfree(int k, int count, const int* avail_mem)
{
	// check for any non-null bits
	for(int i = 0; i < count; i++)
		if(avail_mem[i+k] != 0)
			return false;

    // all bits are null
	return true;
}

// -----
// --- development only functions
// -----



// print avail_mem array to console
void print_avail_mem(const int* avail_mem, int memsize)
{
	int curr_block_size = 0;
	int curr_block_val = -1;

	printf("avail_mem:\n");
	for(int i = 0; i <= memsize; i++)
	{
		if(i < memsize && avail_mem[i]==curr_block_val)
		{
			curr_block_size++;
		} else {
			if(curr_block_size > 0)
				printf("\t%d\t%ds\n", curr_block_size, curr_block_val);
			curr_block_val = avail_mem[i];
			curr_block_size = 1;

		}
	}
}






