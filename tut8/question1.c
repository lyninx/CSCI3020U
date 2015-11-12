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

typedef struct{

	struct node* left;
	struct node* right;
	proc val;

} proc_tree;

void tokenize(const char *input, proc *newProc){
	// initialize values
	int k = 0;	
	// input copy
	char inputcpy[BUFFER_LEN] = { 0 }; 
	// the individual tokens(type string)			
	char *token;					
	// strtok looks for a ,				
	const char delimiter[2] = ",";	

	// perform copy so the original isn't touched
	strcpy(inputcpy, input);

	// tokenize input for the first value
    token = strtok(inputcpy, delimiter);

    while( token != NULL ){
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
	    //tokenize for the rest of the values
	   	token = strtok(NULL, delimiter);
	}
	// Checks if tokenize worked properly
	// printf("%s ", newProc->parent);
	// printf("%s ", newProc->name);
	// printf("%i ", newProc->priority);
	// printf("%i\n", newProc->memory);
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

int main(void)
{
	proc_tree* tree;
	proc_tree* root;

	root = NULL;

    char buff[BUFFER_LEN] = { 0 };
	FILE* file =  fopen("process_tree.txt", "r");
	while(fgets(buff, BUFFER_LEN, file)){

		proc newProc = createProc();
		tokenize(buff, &newProc);

	}
	//tokenize input

	return 0;
}