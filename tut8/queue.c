#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

node_t* init_node(const proc* p)
{
    // initialize values
    node_t* node = malloc(sizeof(node_t));
    node->process = *p;
    node->next = NULL;

    // return new node
    return node;

}

void push(node_t** head, proc p)
{
    // create a node at the end position
    if(!*head)
    {
        // initialize head
        *head = init_node(&p);
    } else {
        // browse through nodes
        node_t* currnode = *head;
        while(currnode->next != NULL)
            currnode = currnode->next;

        // initialize next
        currnode->next = init_node(&p);
    }
}

proc* pop(node_t ** head) {
    proc* retval = NULL;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return NULL;
    }

    next_node = (*head)->next;
    retval = &(*head)->process;
    free(*head);
    *head = next_node;

    return retval;
}

void print_list(node_t * head) {

    // check for empty list
    if(!head)
    {
        printf("<empty list>\n");
        return;
    }

    // else
    node_t * current = head;

    while (current != NULL) {
        printf("%s %d\n", current->process.name, current->process.priority);
        current = current->next;
    }
}

proc* remove_by_index(node_t ** head, int n) {
    proc* retval = NULL;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (int i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return NULL;
        }
        current = current->next;
    }

    temp_node = current->next;
    retval = &temp_node->process;
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}

proc* delete_name(node_t * head, char* name){
    node_t * current = head->next;
    int i = 1;
    while (current != NULL) {
        if(strcmp(current->process.name, name) == 0){
            remove_by_index(&head, i);
            //printf(current->process.name);
            return &current->process;
            //return NULL;
        }
        i = i + 1;
        current = current->next;
    }
    return NULL;
}

proc* delete_pid(node_t * head, int pid){
    node_t * current = head->next;
    int i = 1;
    while (current != NULL) {
        if(current->process.pid == pid){
            remove_by_index(&head, i);
            printf("%d", pid);
            return &current->process;
            //return NULL;
        }
        i = i + 1;
        current = current->next;
    }
    return NULL;
}

