#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 256

typedef struct{
	char parent[256];
	char name[256];
	int priority;
	int memory;
} proc;

typedef struct node{

	struct node* left;
	struct node* right;
	proc val;

} proc_tree;

void tokenize(const char *input, proc *newProc){
	// k is used to identify what token will be inserted into the struct values
	int k = 0;	
	// Input copy
	char inputcpy[BUFFER_LEN] = { 0 }; 
	// The individual tokens(type string)			
	char *token;					
	// strtok looks for a ", "			
	const char delimiter[3] = ", ";	

	// Perform copy so the original isn't touched
	strcpy(inputcpy, input);

	// Tokenize input for the first value
    token = strtok(inputcpy, delimiter);

    // Loops until the string being tokenized is fully tokenized
    while(token != NULL){
    	if(k == 0){
   			strcpy(newProc->parent, token);
    	} else if(k == 1){
    		strcpy(newProc->name, token);
    	} else if(k == 2){
    		newProc->priority = atoi(token);
    	} else if(k == 3){
    		newProc->memory = atoi(token);
    	}
    	// Increment k after every insertion
	    k++;
	    // Tokenize for the rest of the values
	   	token = strtok(NULL, delimiter);
	}
}

proc createProc(void)
{
	// Creates a new instance of proc
    proc newProc;

    // Gives newProc default values of nothing
    strcpy(newProc.parent, "");
    strcpy(newProc.name, "");
    newProc.priority = 0;
    newProc.memory = 0;

    // Returns newProc to the call with the default values now
    return newProc;
}

void addNode(proc_tree **tree, proc_tree *newNode)
{
	// If there is no elements in tree, the first element becomes the root
	if(strcmp(newNode->val.parent, "NULL") == 0){
		*tree = newNode;
		return;
	}

	// Insert child left or right if they are NULL and the parent is correct
	if((strcmp((*tree)->val.name, newNode->val.parent) == 0) && (*tree)->left == NULL){
		(*tree)->left = newNode;
	} else if((strcmp((*tree)->val.name, newNode->val.parent) == 0) && (*tree)->right == NULL){
		(*tree)->right = newNode;
	}

	// Recursively moves down the left branch
	if((*tree)->left != NULL){
		addNode(&(*tree)->left, newNode);
	}
	// Recursively moves down the right branch
	if((*tree)->right != NULL){
		addNode(&(*tree)->right, newNode);
	}
}

void printTree(proc_tree *tree){

	// Prints the tree as long as there is an element in the root
	if(tree != NULL){
		// Print based on if the children are NULL
		if(tree->left != NULL && tree->right != NULL){
			printf("Parent: %s --> Children: %s, %s\n", tree->val.name, tree->left->val.name, tree->right->val.name);
		}
		else if(tree->left != NULL){
			printf("Parent: %s --> Children: %s, NULL\n", tree->val.name, tree->left->val.name);
		}
		else if(tree->right != NULL){
			printf("Parent: %s --> Children: NULL, %s\n", tree->val.name, tree->right->val.name);
		}
		else if(tree->left == NULL && tree->right == NULL){
			printf("Parent: %s --> Children: NULL, NULL\n", tree->val.name);
		}
		
		// Recursively moves down the left branch
		if(tree->left != NULL){
			printTree(tree->left);
		}
		// Recursively moves down the right branch
		if(tree->right != NULL){
			printTree(tree->right);
		}
	}
}

void freeTree(proc_tree **tree){

	// Frees the memory as long as there is an element in the root
	if(*tree != NULL){
		// Recursively moves down the left branch
		if((*tree)->left != NULL){
			freeTree(&(*tree)->left);
		}
		// Recursively moves down the right branch
		if((*tree)->right != NULL){
			freeTree(&(*tree)->right);
		}
		// Free the node
		free(*tree);
	}
}

int main(void)
{
	// tree is the first node that the tree is built from
	proc_tree *tree;
	// currNode is the node that is created for each process
	proc_tree *currNode;

	// Initialize the rootNode to NULL (will be filled during first iteration)
	tree = NULL;

	// Line stores the lines of the file
    char line[BUFFER_LEN] = { 0 };
    // file is the file to be opened
	FILE* file =  fopen("process_tree.txt", "r");
	// Loops until end of file
	while(fgets(line, BUFFER_LEN, file)){

		// Create a newProc struct and inputs the data from file into it. This uses tokenize to parse the data 
		proc newProc = createProc();
		tokenize(line, &newProc);

		// Allocate memory for the current node and gives the node default values(left/right) and the data parsed from the file
		currNode = (proc_tree*)malloc(sizeof(proc_tree));
		currNode->left = NULL;
		currNode->right = NULL;
		currNode->val = newProc;

		// Add the new node to the tree
		addNode(&tree, currNode);
	}

	printTree(tree);
	freeTree(&tree);

	return 0;
}