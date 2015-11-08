#include <string.h>
#include <stdio.h>
#include "tut7ptokens.h"

#define PTOKENS_DELIM ", "

void get_next_token(char* str)
{

}

void get_process_info_from_line(char* str, char* name, int* priority, int* pid, int* runtime)
{
	//todo
}


void get_process_info_from_line_q5(char* str, char* name, int* priority, int* runtime)
{
	
        const char* tok;
        tok = strtok(str, ", ");
        sscanf(tok, "%s", name);
        tok = strtok(NULL, ", ");
        sscanf(tok, "%d", priority);
        tok = strtok(NULL, ", ");
        sscanf(tok, "%d", runtime);
}
