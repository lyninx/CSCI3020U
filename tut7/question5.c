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

// command length
#define PROCESS_NAME_LEN 16

void print_list_all(node_t* head)
{

    if(!head)
    {
        printf("<empty list>\n");
    } else {
        proc* currproc;
        while(head != NULL)
        {
            currproc = &head->process;
            printf("%s,%d,%d,%d\n", currproc->name, currproc->priority, currproc->pid, currproc->runtime);
            head = head->next;
        }
    }
    
}

proc new_proc(void)
{
    proc obj;
    obj.name = calloc(PROCESS_NAME_LEN, sizeof(char));
    obj.priority = 0;
    obj.pid = 0;
    obj.runtime = 0;

    return obj;
}

void free_proc(proc* obj)
{
    free(obj->name);
}

// loads the processes in some file 
void load_processes(FILE* file, node_t** head)
{
    // command buffer
    char buff[BUFFER_LEN] = { 0 };

    int max_priority = 0;

    // get each process from file
    while(fgets(buff, BUFFER_LEN, file))
    {
        // make new process object
        proc pobj = new_proc();
        get_process_info_from_line_q5(buff, &pobj);


        // initialize head or push new value
        if(!*head)
        {
            *head = malloc(sizeof(node_t));
            (*head)->next = NULL;
            (*head)->process = pobj;
        } else {
            push(*head, pobj);
        }
    }
    
}

// prioritizes processes in queue
void sort_processes(node_t** head)
{
    //todo
}

// runs processes in queue
void run_processes(node_t** head)
{
    printf("run processes\n");
    proc* currproc;
    while(*head)
    {
        currproc = &(*head)->process;
        printf("process name '%s' prio %d rt %d\n", currproc->name, currproc->priority, currproc->runtime);
        
        free_proc(currproc);
        pop(head);
        //todo

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
    node_t* head = NULL;
    load_processes(process_list, &head);


    printf("print em once\n");
    print_list_all(head);
    
    // close the process list
    fclose(process_list);


    printf("print em again\n");
    print_list_all(head);
    
    // prioritize list
    sort_processes(&head);

    // run processes
    run_processes(&head);
    
    printf("print a last time\n");
    print_list_all(head);
    
    
    return 0;
}