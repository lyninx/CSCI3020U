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
	if(*tree == NULL){
		*tree = newNode;
		return;
	}

	// This doesn't work. Need to fix insertion. Right now it just inserts the children of the root
	if(((*tree)->val.name == newNode->val.name) && (*tree)->left == NULL){
		(*tree)->left = newNode;
	} else if(((*tree)->val.name == newNode->val.name) && (*tree)->right == NULL){
		(*tree)->right = newNode;
	}
}

int main(void)
{
	// rootNode is the first node that the tree is built from
	proc_tree *rootNode;
	// currNode is the node that is created for each process
	proc_tree *currNode;

	// Initialize the rootNode to NULL (will be filled during first iteration)
	rootNode = NULL;

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
		addNode(&rootNode, currNode);
	}
	return 0;
}