#ifndef BTREE_H
#define BTREE_H

typedef struct
{
	char parent[256];
	char name[256];
	int priority;
	int memory;
} proc;

typedef struct node
{
	struct node* left;
	struct node* right;
	proc* value;
} proc_tree;

extern void dfs(proc_tree* tree);




#endif //BTREE_H