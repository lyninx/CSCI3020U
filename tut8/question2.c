#define _XOPEN_SOURCE 600
#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>

#define MEMORY 1024
#define FPATH_PROCESSES_Q5 "processes_q5.txt"
#define BUFFER_LEN 256


// available memory
static int avail_mem[MEMORY] = { 0 };

// memory lock
static pthread_mutex_t avail_mem_lock;

// barrier that is reached when an element in the queue has been copied
static pthread_barrier_t proc_list_copy_barr;

// flag indicating whether there was an allocation failure
bool q2_alloc_failed = false;

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

/// convenience; checks if a memory segment is unused.
/// assumes it has ownership of the mutex 'avail_mem_lock'... so yeah, watch out
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

	// lock for 'list'
	pthread_barrier_init(&proc_list_copy_barr, NULL,2);

	// array of threads
	const int nthrs = get_queue_size(*list);
	pthread_t thrs[nthrs];

	// go through each list element
	int currproc = 0;
    while(*list)
    {

        // run it
        pthread_create(&thrs[currproc], NULL, launch_process, (void*)&(*list)->process);

        // wait for process to copy
        pthread_barrier_wait(&proc_list_copy_barr);
        
        // pop process
        pop(list);

        // iterate
        currproc++;

    }

    // join threads
    for(int i = 0; i < nthrs; i++)
    	pthread_join(thrs[i], NULL);

}

// forks into a new process based on the process object
void* launch_process(void* _process)
{
	// copy process
	proc process = *(proc*)_process;

	// signal to the main that the copy was done
	pthread_barrier_wait(&proc_list_copy_barr);

	// try to allocate memory
	process.address = q2_alloc(process.memory);
	if(process.address == MEMORY)
	{
		printf("Error: unable to allocate memory for '%s'\n", process.name);
		q2_alloc_failed = true;
		return NULL;
	}

	// do a fork
	//todo
	int pid = fork();
	if(pid == 0)
	{
		// update pid
		process.pid = getpid(); 

		// print it
		printf("process name '%s' priority %d pid %d memory %d runtime %d\n", process.name, process.priority, process.pid, process.memory, process.runtime);
    	
    	// do the thing
		printf("[%d] I'm child for '%s' rt %d\n", getpid(), process.name, process.runtime);
		//todo

		// done
		exit(1);
	} else if (pid < 0) {
		fprintf(stderr, "Error occured during fork\n");
		exit(1);
	} else {

		// wait for process runtime to complete
        sleep(process.runtime);

        printf("killing process %d\n", pid);

        // now you're killing it. Stop it.
        kill(pid, SIGTSTP);

    	// wait for child
    	waitpid(pid, 0, 0);

		
    	// dealloc
	    if(!q2_free(process.address, process.memory))
	    	return NULL; //todo
	}

    


    // done
    return NULL;
}



// function that frees elements of avail_mem
int q2_alloc(int memory)
{

	printf("Waiting to allocate %d bits\n", memory);
	// acquire lock
	pthread_mutex_lock(&avail_mem_lock);

	printf("allocating %d bits\n", memory);

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
		index = MEMORY;
	}

	print_avail_mem();

	// release lock
	printf("done allocating %d bits at %d\n", memory, index);
	pthread_mutex_unlock(&avail_mem_lock);

	

	// return the index
	return index;
}

// function that frees elements of avail_mem
bool q2_free(int address, int memory)
{
	printf("Waiting to free %d bits at %d\n", memory, address);
	// acquire lock
	pthread_mutex_lock(&avail_mem_lock);

	printf("freeing %d bits at %d\n", memory, address);

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
	printf("done freeing %d bits at %d\n", memory, address);
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

// -----
// --- development only functions
// -----



// print avail_mem array to console
void print_avail_mem(void)
{
	int curr_block_size = 0;
	int curr_block_val = -1;

	printf("avail_mem:\n");
	for(int i = 0; i <= MEMORY; i++)
	{
		if(i < MEMORY && avail_mem[i]==curr_block_val)
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






