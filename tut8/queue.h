#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
/* QUEUE */

typedef struct _proc{
	char name[256];
	int priority;
	int pid;
	int address;
	int memory;
	int runtime;
	bool suspended;

} proc;


typedef struct _node {
    proc process;
    struct _node * next;
} node_t;

extern void push(node_t *, proc);
extern proc* pop(node_t **);
extern void print_list(node_t* head);
extern proc* delete_name(node_t * head, char* name);
extern proc* delete_pid(node_t * head, int pid);


#endif //QUEUE_H