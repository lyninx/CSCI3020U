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

	for(int i = 0; i < TOKENS_COUNT; i++){	//prints the tokens
		printf("%s\n", tokens[i]);
	}
	// // get first token
	// scanf("%s", input);
	// strcpy(input, tokens);
	// gets(input);

	// // get remaining tokens
	// //gets(input) <--- should get remaining tokens until newline
	// char token[MAX_LEN] = { 0 };
	// while (sscanf(token, "%s", input) )
	// {
	// 	// nab token
		

	// 	// truncate input string
	// 	char* next = strchr(input, ' ');
	// 	if (next == NULL || strlen)
	// 	{
	// 		break;
	// 	}
	// 	else {
	// 		input = next;
	// 	}

	// 	printf("'%s'\n", token);

	// 	// increment tokens
	// 	tokens += MAX_LEN / 4;
	// }

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
	char userAnswer[BUFFER_LEN] = "What is *";	//TEST CASE - CHANGE TO INPUT FROM USER
	const char delimiter[2] = " ";					//strtok looks for a space
	char *token;									//the individual token(string)
	char *tokens[BUFFER_LEN];						//array of tokens
	int k = 0;										//KEEPS TRACK OF TOKENS ARRAY

	// An array of 4 players
	player players[4];

	// Input buffer and and commands
	char buffer[BUFFER_LEN] = { 0 };


	// token buffer
	// char tokens[TOKENS_COUNT][MAX_LEN] = {"one", "two", "three", "four", "five", "six", "seven", "eight"};//{ 0 };// = { "", "", "", "", "", "", "", "" };
	// char** tokens_test = tokens;
	// for (int i = 0; i < 5; i++)
	// {
	// 	printf("'%s'", tokens_test + i*(MAX_LEN/4));
	// }

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

        // Prints 1 if the name exists - this works
        // Don't need to print
        //printf("%d\n", player_exists(players, &checkName));

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

            token = strtok(userAnswer, delimiter);

            while( token != NULL ) 
		    {
		    	tokens[k] = token;
		        k++;
		    
		    	token = strtok(NULL, delimiter);
		   	}
            tokenize(userAnswer, tokens);

            //answerCorrect = valid_answer(category, val, &userAnswer); //returns boolean

            // if(answerCorrect == 1){                  //UNCOMMENT THIS ONCE THE TOKENIZATION IS DONE
            //     printf("Correct Answer!\n");
            //     update_score(players, checkName, val);
            // } else{
            //     printf("Incorrect Answer!\n");
            //     printAnswer(category, val);
            // }
            // if(gameDone() == 1){
            //     printf("Game is over!\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            //     show_results(players);
            //     break;
            // }

        }

		// I'm saving this condition
		/*while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
		{

		}*/


        // Display the final results and exit
    }
    return EXIT_SUCCESS;
}
