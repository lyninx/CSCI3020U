#include <string.h>
#include <stdio.h>
#include "tut7ptokens.h"

#define PTOKENS_DELIM ", "

void read_first_token_str(char* str, char* name)
{
	const char* tok = strtok(str, PTOKENS_DELIM);
    sscanf(tok, "%s", name);
}

void read_next_token_int(char* str, int* val)
{
	const char* tok = strtok(NULL, PTOKENS_DELIM);
	sscanf(tok, "%d", val);
}

void get_process_info_from_line(char* str, char* name, int* priority, int* pid, int* runtime)
{

}


void get_process_info_from_line_q5(char* str, char* name, int* priority, int* runtime)
{
        read_first_token_str(str, name);
        read_next_token_int(str, priority);
        read_next_token_int(str, runtime);
}
