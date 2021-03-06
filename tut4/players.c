/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Akira Aida(ID: 100526064), Kathryn McKay(ID: 100524201), Dennis Pacewicz (ID: 100524231), Truyen Truong(ID: 100516976)
 * All rights reserved.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, char *name)
{
	for(int i = 0; i < 4; i++){
		if(strcmp(players[i].name, name) == 0){
			return true;
		}
	}
    return false;
}

// Updates the score for that player given their name
void update_score(player *players, char *name, int score)
{
	//iterates through all 4 contestants
	//if the name of the player exists
	//adds the score
	for(int i = 0; i < 4; i++){
		if(strcmp(players[i].name, name) == 0){
			players[i].score = players[i].score + score;
			printf("Name: %s, Score: %d\n", players[i].name, players[i].score);
		}
	}
}