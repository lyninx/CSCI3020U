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
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define TOKENS_COUNT 3
#define PLAYER_COUNT 4

// Retrieves user names for number of participants indicated
void prompt_player_names(player* players, int count);

// Waits for a line of input
void prompt_line(char* dest, FILE* file);

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(const char *input, char **tokens){
	// initialize values
	int k = 0;	
	char inputcpy[MAX_LEN] = { 0 }; // input copy
	char *token;									//the individual token(string)
	const char delimiter[2] = " ";					//strtok looks for a space

	// perform copy
	strcpy(inputcpy, input);

	// tokenize input
    token = strtok(inputcpy, delimiter);
    while( token != NULL ){
	  	tokens[k] = token;
	    k++;
	   
	   	token = strtok(NULL, delimiter);
	}
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players){
    for(int i = 0; i < PLAYER_COUNT; i++){
        printf("Name: %s, Score: %d\n", players[i].name, players[i].score);
    }
}

int main()//int argc, char *argv[])
{
	// Values
	int val = 0;									// Question's money value
	char *tokens[BUFFER_LEN];						//array of tokens
	player players[PLAYER_COUNT];					// An array of 4 players
	//char buffer[BUFFER_LEN] = { 0 };				// Input buffer and and commands
	char checkName[BUFFER_LEN];						// Current user's name
	char category[BUFFER_LEN] = { 0 };				// Current Category
	bool answerCorrect = false;						// Correct answer buffer
	char userAnswer[BUFFER_LEN] = { 0 };			// user's answer buffer

    // Initialize each of the players in the array
	prompt_player_names(players, PLAYER_COUNT);

    // Generate the game's data
    initialize_game(GAME_CATS_USED, GAME_TIERS_USED);

    // Game loop; continues to prompt until all questions have answers or input ends
    while(!game_done() /*&& fgets(buffer, BUFFER_LEN, stdin) != NULL*/) // If this concerns you, please look at the issues list I've outlined above and then talk to me - Kathryn
    {
   		// display choices
        display_categories();

        // Execute the game until all questions are answered
        printf("Enter a name of a contestant: ");
		prompt_line(checkName, stdin);
        answerCorrect = false;


		// Quiz the player
        if(player_exists(players, checkName) == true){

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
			while (true)
			{
				// Accept tokenized input
				prompt_line(userAnswer, stdin);
				tokenize(userAnswer, tokens);

				// validate answer
				if (is_valid_answer(tokens))
					break;
				printf("You forgot to use \"What is/Who is\"!\n");
			}

			// evaluate user's response
			if (valid_answer(category, val, userAnswer)){
				printf("Correct Answer!\n");
				update_score(players, checkName, val);
			}
			else if (answerCorrect != 1){
				printf("Incorrect Answer! The correct answer was: ");
				print_answer(category, val);
			}


			
		}
			
    }

	// Show results
	printf("Game is over!\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	show_results(players);

	// return
    return EXIT_SUCCESS;
}


bool is_valid_answer(char **tokens)
{
	return (strcmp(tokens[0], "what") == 0 || strcmp(tokens[0], "who") == 0) && strcmp(tokens[1], "is") == 0;
}

void prompt_player_names(player* players, int count)
{
	for (int i = 0; i < count; i++){
		printf("What is your name player %d\n", i + 1);
		prompt_line(players[i].name, stdin);
		players[i].score = 0;
	}
}

void prompt_line(char* dest, FILE* file)
{
	// prompt for input
	scanf("%s", dest);

	// get remaining tokens
	char buffer[BUFFER_LEN] = { 0 };
	int answerlen = strlen(dest) + 1;
	if (answerlen < BUFFER_LEN)
	{
		// get all before newline
		fgets(buffer, BUFFER_LEN - answerlen, file);
		int bufferlen = strlen(buffer);
		if (bufferlen > 0)
		{
			// erase newline from buffer
			buffer[strlen(buffer) - 1] = 0;
		}

		// attach other tokens to answer
		strcat(dest, buffer);
	}
}