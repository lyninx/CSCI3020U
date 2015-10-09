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

int main(int argc, char *argv[])
{
    // Name buffer
	char checkName[BUFFER_LEN];

	// Category buffer
	char category[BUFFER_LEN];

	// Question's money value
	int val;

	// Correct answer buffer
	bool answerCorrect = false;

	// user's answer buffer
	char userAnswer[BUFFER_LEN] = "what are *";	//TEST CASE - CHANGE TO INPUT FROM USER
	char *tokens[BUFFER_LEN];						//array of tokens
													//KEEPS TRACK OF TOKENS ARRAY
	int ans1;
	int ans2;

	// An array of 4 players
	player players[4];

	// Input buffer and and commands
	char buffer[BUFFER_LEN] = { 0 };

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
        // Execute the game until all questions are answered
        printf("Enter a name of a contestant: ");
        scanf("%s", checkName);
        answerCorrect = false;

		// Quiz the player
        if(player_exists(players, checkName) == 1){

			// display choices
            display_categories();

			// get choice from player
			printf("Select a category & value: ");
            scanf("%s %d", category, &val);

			// quiz player
            display_question(category, val);

            //TOKENIZE CODE HERE (NOTE: scanf and strtok do not work together well (need to find a trick/hack))
            tokenize(userAnswer, tokens);

            //THIS BREAKS IF 3 INPUTS ARE NOT ENTERED - NO ERROR CHECKING
            //checks if "what is <answer>" or "who is <answer>" is valid
            ans1 = strcmp(tokens[0], "what");

            if(ans1 != 0){
            	ans1 = strcmp(tokens[0], "who");
            }
            if(ans1 == 0){
                ans2 = strcmp(tokens[1], "is");
            
                if((ans1 == 0) && (ans2 == 0)){
            	   answerCorrect = valid_answer(category, val, tokens[2]); //returns boolean
            	} else{
            	   printf("You forgot to use \"What is/Who is\"!\n");
               }
            }

            if(answerCorrect == 1){                  //UNCOMMENT THIS ONCE THE TOKENIZATION IS DONE
                printf("Correct Answer!\n");
                update_score(players, checkName, val);
            } else if(answerCorrect != 1){
                printf("Incorrect Answer! The correct answer was: ");
                printAnswer(category, val);
            }
            if(gameDone() == 1){
                printf("Game is over!\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
                show_results(players);
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}
