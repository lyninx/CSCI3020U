/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Akira Aida(ID: 100526064), Kathryn McKay(ID: 100524201), Dennis Pacewicz (ID: 100524231), Truyen Truong(ID: 100516976)
 * All rights reserved.
 *
 */
 
#ifndef PLAYERS_H_
#define PLAYERS_H_
/*-----------------------------------------------------------------------------
*								Headers
*----------------------------------------------------------------------------*/
#include <stdbool.h>

/*-----------------------------------------------------------------------------
*							Constants/Macros
*----------------------------------------------------------------------------*/
// String length
#define MAX_LEN 256

/*-----------------------------------------------------------------------------
*								Typedefs
*----------------------------------------------------------------------------*/
// Player data struct
typedef struct {
    char name[MAX_LEN];
    int score;
} player;

/*-----------------------------------------------------------------------------
*						Function declarations
*----------------------------------------------------------------------------*/
// Returns true if the player name matches one of the existing players
extern bool player_exists(player *players, char *name);

// Updates the score for that player given their name
extern void update_score(player *players, char *name, int score);


//-----------------------------------------------------------------------------
#endif /* PLAYERS_H_ */
//-----------------------------------------------------------------------------