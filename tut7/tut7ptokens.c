#include <string.h>
#include <stdio.h>
#include "tut7ptokens.h"

#define PTOKENS_DELIM ", "

void read_first_token_str(char* str, char* name)
{
	const char* tok = strtok(str, PTOKENS_DELIM);
    sscanf(tok, "%s", name);
}

int read_next_token_int(void)
{
	int val = 0;
	const char* tok = strtok(NULL, PTOKENS_DELIM);
	sscanf(tok, "%d", &val);
	return val;
}

void get_process_info_from_line(char* str, proc* pobj)
{
	read_first_token_str(str, pobj->name);
    pobj->priority = read_next_token_int();
    pobj->pid = read_next_token_int();
    pobj->runtime = read_next_token_int();
}


void get_process_info_from_line_q5(char* str, proc* pobj)
{
	read_first_token_str(str, pobj->name);
    pobj->priority = read_next_token_int();
    pobj->runtime = read_next_token_int();
    pobj->pid = 0;
}
