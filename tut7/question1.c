#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"

char** str_split(char* a_str, char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    count += last_comma < (a_str + strlen(a_str) - 1);

    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

void push(node_t * head, proc p) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->process = p;
    current->next->next = NULL;
}
proc* pop(node_t ** head) {
    proc* retval = NULL;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return NULL;
    }

    next_node = (*head)->next;
    retval = &(*head)->process;
    free(*head);
    *head = next_node;

    return retval;
}
void print_list(node_t * head) {
    node_t * current = head->next;
    printf("\n");
    while (current != NULL) {
        printf("| %s ", current->process.name);
        printf("%d ", current->process.priority);
        printf("%d ", current->process.pid);
        printf("%d\n", current->process.runtime);
        current = current->next;
    }
}
int main(void) {
    char** proc_tokens;
    proc p;

	node_t * queue = NULL;
	queue = malloc(sizeof(node_t));

    queue->process = p;
    queue->next = NULL;

	if (queue == NULL) {
	    return 1;
	}
    
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen("./processes.txt", "r");
        if (fp == NULL)
           exit(EXIT_FAILURE);

        while ((read = getline(&line, &len, fp)) != -1) {
            printf("%s", line);
            // READ FROM FILE AND PARSE
            proc_tokens = str_split(line, ',');
            p.name = *proc_tokens;
            //p.priority = *proc_tokens + 1;
            p.priority = 1;
            p.pid = 1;
            p.runtime = 0;
            push(queue, p);
        }

        fclose(fp);


	//push(queue, p);
	print_list(queue);
	
}