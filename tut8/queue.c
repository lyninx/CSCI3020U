#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

node_t* init_head(proc process)
{
    node_t* head = malloc(sizeof(node_t));
    head->next = NULL;
    head->process = process;

    return head;
}

void push(node_t * head, proc p) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->process = p;
    current->next->next = NULL;
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

