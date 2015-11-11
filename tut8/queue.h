#ifndef QUEUE_H
#define QUEUE_H

/* QUEUE */


typedef struct _proc{
	char name[256];
	int priority;
	int pid;
	int runtime;
} proc;


typedef struct _node {
    proc process;
    struct _node * next;
} node;

extern void push(node *, proc);
extern proc* pop(node **);
extern void print_list(node* head);
extern proc* delete_name(node * head, char* name);
extern proc* delete_pid(node * head, int pid);


#endif //QUEUE_H