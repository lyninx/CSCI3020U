#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "queue.h"
#include "tut7ptokens.h"


// filepath to the process list
#define FPATH_PROCESSES_Q5 "processes_q5.txt"

// buffer length
#define BUFFER_LEN 256

// loads the processes in some file 
void load_processes(FILE* file, node_t* head)
{
    // command buffer
    char buff[BUFFER_LEN] = { 0 };

    // store process name
    char name[BUFFER_LEN] = { 0 };
    char* name2 = calloc(BUFFER_LEN, sizeof(char));



    proc pobj;
    pobj.name = name2;

    // get each process from file
    while(fgets(buff, BUFFER_LEN, file))
    {
        get_process_info_from_line_q5(buff, &pobj);

        //todo
        printf("process name '%s' prio %d rt %d\n", pobj.name, pobj.priority, pobj.runtime);
    }

    free(name2);


    
    
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
    node_t head;
    load_processes(process_list, &head);
    
    // close the process list
    fclose(process_list);
    
    // 
    
    
    
    return 0;
}