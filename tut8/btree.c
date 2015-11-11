#include "btree.h"
#include <stdlib.h>

void dfs(proc_tree* tree)
{
	// search left child
	if(tree->left != NULL)
		dfs(tree->left);

	// search right child
	if(tree->right != NULL)
		dfs(tree->right);

	// this function does nothing....



}


void add_node(proc_tree* tree, proc* process)
{
	if(tree->left != NULL)
		add_node(tree->left, process);
	else if(tree->right != NULL)
		add_node(tree->right, process);
	else 
	{
		tree->left = (proc_tree*)malloc(sizeof(proc_tree));
		tree->left->value = *process;

	}

}

void clear_tree(proc_tree** tree)
{
	if((*tree)->left != NULL)
	{
		clear_tree(&(*tree)->left);
	}

	if((*tree)->right != NULL)
	{
		clear_tree(&(*tree)->right);
	}

	free(*tree);
	*tree = NULL;
}