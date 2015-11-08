#ifndef TUT7PTOKENS_H
#define TUT7PTOKENS_H

#include "queue.h"

/**
* tokenize values from string into process values
*
* @param str 	Input string.
* @param name	Process name destination.
* @param priority	Priority destination.
* @param pid		Process id destination.
* @param runtime	Runtime destination.
*
**/
extern void get_process_info_from_line(char* str, proc* pobj);


/**
* Like above, but for question 5.
*
* @param str 	Input string.
* @param name	Process name destination.
* @param priority	Priority destination.
* @param runtime	Runtime destination.
*
**/
extern void get_process_info_from_line_q5(char* str, proc* pobj);



#endif //TUT7PTOKENS_H