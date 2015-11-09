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


// gonna be deleted. oh no
int max_val(const int x, const int y)
{
    return x > y ? x : y;
}


// slated to go. that's sad.
int get_highest_priority(node_t* head)
{
    int maxpri = 0;
    while(head)
    {
        // compare priority to max
        maxpri = max_val(head->process.priority, maxpri);

        // step to next node
        head = head->next;
    }

    return maxpri;
}

// slated to go, how foolish of me
void sort_processes(node_t** head)
{
    // scan for highest/lowest priority
    int maxpri = get_highest_priority(*head);

    // pointer to current node
    node_t* curr_node = NULL;

    // pointer to previous node
    node_t* prev_node = NULL;

    // list of sorted items
    node_t* sorted_head = NULL;

    // end of sorted list
    node_t* sorted_end = NULL;

    // list of unsorted items
    node_t* unsorted_head = *head;

    // perform countsort
    for(int i = 0; i <=maxpri; i++)
    {
        prev_node = NULL;
        curr_node = unsorted_head;

        // traverse over each unsorted item
        while(curr_node->next)
        {
            if(curr_node->process.priority == i)
            {
                // remove it
                if(!prev_node)
                {
                    unsorted_head = curr_node->next;
                } else {
                    prev_node->next = curr_node->next;
                }

                // insert it
                node_t* temp_next = curr_node->next;
                if(!sorted_head)
                    sorted_head = curr_node;
                else
                    sorted_end->next = curr_node;

                // current node is now the end of the list
                curr_node->next = NULL;
                sorted_end = curr_node;

                // determine next node
                curr_node = temp_next;

            } else {
                // traverse normally
                prev_node = curr_node;
                curr_node = curr_node->next;
            }
        }


    }

    // give back the sorted list
    *head = sorted_head;

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

    bool check_priority = priority < 0;
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
            //todopop(head);
        } 
        if(curr_node)
            curr_node = curr_node->next;

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
    
    // prioritize list
    //sort_processes(&head);

    // run processes
    print_list_all(head);
    run_processes(&head, 0);
    print_list_all(head);
    run_processes(&head, -1);

    print_list_all(head);

    while(head)
    {
        pop(&head);
    }

    print_list_all(head);

    // run; now you're done.
    return 0;
}