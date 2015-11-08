#ifndef QUEUE_H
#define QUEUE_H

/* QUEUE */

typedef struct{
	char* name;
	int priority;
	int pid;
	int runtime;
} proc;


typedef struct node {
    proc process;
    struct node * next;
} node_t;

extern void push(node_t *, proc);
extern proc* pop(node_t **);

#endif //QUEUE_H