/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef JEOPARDY_H_
#define JEOPARDY_H_

/*-----------------------------------------------------------------------------
*							Constants/Macros
*----------------------------------------------------------------------------*/
#define MAX_LEN 256
#define GAME_CATS_USED 3
#define GAME_TIERS_USED 4

/*-----------------------------------------------------------------------------
*						Function declarations
*----------------------------------------------------------------------------*/
// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
extern void tokenize(const char *input, char **tokens);

// Checks if the format of the answer matches who is/what iss
extern bool is_valid_answer(char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
extern void show_results(player *players);


//-----------------------------------------------------------------------------
#endif /* JEOPARDY_H_ */
//-----------------------------------------------------------------------------