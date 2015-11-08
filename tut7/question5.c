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



int max_val(const int x, const int y)
{
    return x > y ? x : y;
}

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

// prioritizes processes in queue
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
    
    // close the process list
    fclose(process_list);


    printf("before\n");
    print_list_all(head);
    
    // prioritize list
    sort_processes(&head);

    
    printf("after\n");
    print_list_all(head);

    // run processes
    run_processes(&head);

    printf("should be empty now:\n");
    print_list_all(head);
    
    
    return 0;
}