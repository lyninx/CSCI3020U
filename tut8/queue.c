#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

void push(node_t** head, proc p)
{
    // current element
    node_t** curr = head;

    // iterate to the end of the list
    if(*head != NULL)
    {
        // iterate until the last element is found
        while (*curr != NULL) {
            *curr = (*curr)->next;
        }

    }

    // allocate the node
    (*curr) = malloc(sizeof(node_t));
    (*curr)->process = p;
    (*curr)->next = NULL;
    
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
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->process.priority);
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

