#include "btree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_tree(const proc_tree* tree)
{
	// print tree
	if(tree != NULL)
	{
		// print data
		printf("%s ", tree->value.name);

		// print left
		if(tree->left != NULL)
		print_tree(tree->left);

		// print right
		if(tree->right != NULL)
			print_tree(tree->right);
	}

	// print nothing
	else
		printf("<empty>\n");

	

}

int main(void)
{
	proc_tree* tree = (proc_tree*)malloc(sizeof(proc_tree));
	proc process1;
	strcpy(process1.name, "blue");

	dfs(tree);
	add_node(tree, &process1);

	print_tree(tree);

	clear_tree(&tree);

	print_tree(tree);

	return 0;
}