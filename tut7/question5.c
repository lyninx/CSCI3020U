#include "queue.h"


// filepath to the process list
#define FPATH_PROCESSES_Q5 "processes_q5.txt"

// buffer length

// loads the processes in some file 
void load_processes(FILE* file/*,queue type*/)
{
    
    
    //
    
    while(
    
    
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