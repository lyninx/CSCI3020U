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
extern void print_list(node_t* head);
extern proc* delete_name(node_t * head, char* name);
extern proc* delete_pid(node_t * head, int pid);


#endif //QUEUE_H