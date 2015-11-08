#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

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