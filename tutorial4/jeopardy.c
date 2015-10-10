/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Akira Aida(ID:100526064), Kathryn McKay(ID:100524201), Dennis Pacewicz (ID:), Truyen Truong(ID:)
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define TOKENS_COUNT 3

// Put global environment variables here


// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens){

	int k = 0;	
	char *token;									//the individual token(string)
	const char delimiter[2] = " ";					//strtok looks for a space

    token = strtok(input, delimiter);

    while( token != NULL ){
	  	tokens[k] = token;
	    k++;
	   
	   	token = strtok(NULL, delimiter);
	}
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players){
    for(int i = 0; i < 4; i++){
        printf("Name: %s, Score: %d\n", players[i].name, players[i].score);
    }
}

/**
*
*	KNOWN ISSUES (Kathryn, 2015/10/09, 20:14):
*		- So whether or not we accept that there are 25 questions now...
*			- currently a bug where the 2 new 2 word name categories cannot be
*				selected
*			- bug where questions cannot be answered with form 'who is'/'what is'.
*			- bug where answer input chokes if only content is 'who' or 'what'
*
*
**/
int main(int argc, char *argv[])
{
	// Values
	char checkName[BUFFER_LEN];						// Name buffer
	char category[BUFFER_LEN] = { 0 };				// Category buffer
	int val = 0;									// Question's money value
	bool answerCorrect = false;						// Correct answer buffer
	char userAnswer[BUFFER_LEN] = { 0 };			// user's answer buffer
	char *tokens[BUFFER_LEN];						//array of tokens
	player players[4];								// An array of 4 players
	char buffer[BUFFER_LEN] = { 0 };				// Input buffer and and commands

    // Display the game introduction and prompt for players names
    // initialize each of the players in the array
    for(int i = 0; i < 4; i++){
        printf("What is your name player %d\n", i+1);
        scanf("%s", players[i].name);
        players[i].score = 0;
    }

    // Generate the game's data
    initialize_game();

    // Game loop; continues to prompt until all questions have answers
    while(fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
		// check if game is done
		if (game_done() == 1){
			printf("Game is over!\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
			show_results(players);
			break;
		}

        // Execute the game until all questions are answered
        printf("Enter a name of a contestant: ");
        scanf("%s", checkName);
        answerCorrect = false;

		// Quiz the player
        if(player_exists(players, checkName) == true){

			// display choices
			display_categories();

			// select a question
			while (already_answered(category, val))
			{
				// get choice from player
				printf("Select a category & value: ");
				scanf("%s %d", category, &val);

				// display question OR status
				display_question(category, val);
			}

			// get answer
			scanf("%s", userAnswer);

			// get remaining tokens
			int answerlen = strlen(userAnswer) + 1;
			if (answerlen < BUFFER_LEN)
			{
				// get all before newline
				fgets(buffer, BUFFER_LEN - answerlen, stdin);
				int bufferlen = strlen(buffer);
				if (bufferlen > 0)
				{
					buffer[strlen(buffer) - 1] = 0;
				}

				// attach other tokens to answer
				strcat(userAnswer, buffer);

			}

			printf("'%s'\n", userAnswer);

			// validate answer
            tokenize(userAnswer, tokens);
			if (!is_valid_answer(tokens))
			{
				printf("You forgot to use \"What is/Who is\"!\n");
			}
			else {
				answerCorrect = valid_answer(category, val, tokens[2]); //returns boolean
			}

			// return result
			if (answerCorrect == 1){
				printf("Correct Answer!\n");
				update_score(players, checkName, val);
			}
			else if (answerCorrect != 1){
				printf("Incorrect Answer! The correct answer was: ");
				print_answer(category, val);
			}


			
		}


		printf("press enter to continue:");
			
    }

    return EXIT_SUCCESS;
}


bool is_valid_answer(char **tokens)
{
	return (strcmp(tokens[0], "what") == 0 || strcmp(tokens[0], "who") == 0) && strcmp(tokens[1], "is") == 0;
}