#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include "queue.h"
#include "tut7ptokens.h"
#include <signal.h>


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
            printf("%s,%d,%d,%d ", currproc->name, currproc->priority, currproc->pid, currproc->runtime);
            if((head = head->next))
            {
                printf("--> '%s' %d\n", head->process.name, head->process.priority);
            } else {
                printf("\n");
                break;
            }
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

bool launch_process_as_child(proc* process)
{
    pid_t pid = fork();
    char* argv[] = {NULL};
    if(pid == 0)
    {
        execv("./process", argv);
        return false;
    } else if (pid < 0){
        fprintf(stderr, "Error occured during fork.\n");
        return false;
    } else {
        // update pid of process
        process->pid = pid;

        // wait for process runtime to complete
        sleep(process->runtime);

        // now you're killing it. Stop it.
        kill(pid, SIGINT);

        // wait for it.
        waitpid(pid, 0, 0);

        // return.
        return false;
    }
}

// runs processes in queue
bool run_processes(node_t** head, int priority)
{

    bool check_priority = priority >= 0;
    node_t* curr_node = *head;
    proc* currproc;
    while(curr_node)
    {
        if(!check_priority || curr_node->process.priority == priority)
        {
            // get it
            currproc = &curr_node->process;



            // run it
            if(launch_process_as_child(currproc))
            {
                // child shouldn't spawn more children
                fprintf(stderr, "Error: pid %d reached this pointfor some reason\n", getpid());
                return false;
            }


            printf("[%d]process name '%s' priority %d pid %d runtime %d\n", getpid(), currproc->name, currproc->priority, currproc->pid, currproc->runtime);
            


            // be rid of it
            free_proc(currproc);
            if(curr_node == *head)
            {
                curr_node = curr_node->next;
                pop(head);
            } else {
                delete_pid(*head, currproc->pid);
                if(curr_node)
                    curr_node = curr_node->next;
            }
        } else {
            curr_node = curr_node->next;
        }

    }



    
    // you never got to be the one in the tank
    return true;
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
    
    // close the process list
    fclose(process_list);

    // run hi priority then lower-priority processes
    run_processes(&head, 0);
    run_processes(&head, -1);


    // pop any remaining nodes
    while(head)
    {
        pop(&head);
    }

    // run; now you're done.
    return 0;
}