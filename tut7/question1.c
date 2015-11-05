#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
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
int pop(node_t ** head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->process;
    free(*head);
    *head = next_node;

    return retval;
}
void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->process);
        current = current->next;
    }
}
int main(void) {

	proc p;

	p.name = "test";
	p.priority = 1;
	p.pid = 1;
	p.runtime = 0;

	node_t * head = NULL;
	head = malloc(sizeof(node_t));
	if (head == NULL) {
	    return 1;
	}

	head->process = p;
	head->next = NULL;
	
}