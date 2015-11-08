#include <stdio.h>
#include <pthread.h>
#include "queue.h"


// filepath to the process list
#define FPATH_PROCESSES_Q5 "processes_q5.txt"

// buffer length
#define BUFFER_LEN 256

// loads the processes in some file 
void load_processes(FILE* file/*,queue type*/)
{
    // command buffer
    char buff[BUFFER_LEN] = { 0 };

    // store process name
    char name[BUFFER_LEN] = { 0 };

    // store process priority
    int priority = 0;

    // store process runtime
    int runtime = 0;

    // get each process from file
    while(fgets(buff, BUFFER_LEN, file))
    {

        // extract info from string
        sscanf(buff, "%s,%d,%d", name, &priority, &runtime);

        //todo
        printf("process name '%s' prio %d rt %d\n", name, priority, runtime);
    }

    
    
}


int main(int argc, char* argv[])
{
    // try load up 'processes_q5.txt'
    FILE* process_list =  fopen(FPATH_PROCESSES_Q5, "r");
    if(!process_list)
    {
        fprintf(stderr, "Error: Failed to load '%s'\n", FPATH_PROCESSES_Q5);
        return 1;
    }
    
    // read in stuff from processes
    load_processes(process_list);
    
    // close the process list
    fclose(process_list);
    
    // 
    
    
    
    return 0;
}