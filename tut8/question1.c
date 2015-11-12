#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 256
#define PTOKENS_DELIM ", "

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
	// Initialize values
	int k = 0;	
	// Input copy
	char inputcpy[BUFFER_LEN] = { 0 }; 
	// The individual tokens(type string)			
	char *token;					
	// strtok looks for a ", "			
	const char delimiter[2] = ", ";	

	// Perform copy so the original isn't touched
	strcpy(inputcpy, input);

	// Tokenize input for the first value
    token = strtok(inputcpy, delimiter);

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

	    k++;
	    // Tokenize for the rest of the values
	   	token = strtok(NULL, delimiter);
	}
}

proc createProc(void)
{
    proc newProc;

    strcpy(newProc.parent, "");
    strcpy(newProc.name, "");
    newProc.priority = 0;
    newProc.memory = 0;

    return newProc;
}

void addNode(proc_tree **tree, proc_tree *newNode)
{
	// If there is no elements in tree, the first element becomes the root
	if(*tree == NULL){
		*tree = newNode;
		return;
	}

	// This doesn't work. Need to fix insertion
	if(((*tree)->val.name == newNode->val.name) && (*tree)->left == NULL){
		(*tree)->left = newNode;
	} else if(((*tree)->val.name == newNode->val.name) && (*tree)->right == NULL){
		(*tree)->right = newNode;
	}
}

int main(void)
{
	proc_tree *rootNode;
	proc_tree *currNode;

	rootNode = NULL;

	// Line stores the lines of the file
    char line[BUFFER_LEN] = { 0 };
    // File is the file to be opened
	FILE* file =  fopen("process_tree.txt", "r");
	while(fgets(line, BUFFER_LEN, file)){

		// Create a new process and input the data from file
		proc newProc = createProc();
		tokenize(line, &newProc);

		// Allocate memory for the current node
		currNode = (proc_tree*)malloc(sizeof(proc_tree));
		currNode->left = NULL;
		currNode->right = NULL;
		currNode->val = newProc;

		// Add the new node to the tree
		addNode(&rootNode, currNode);
	}
	return 0;
}