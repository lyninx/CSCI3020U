/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
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

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens){

}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players){
    for(int i = 0; i < 4; i++){
        printf("Name: %s, Score: %d\n", players[i].name, players[i].score);
    }
}

int main(int argc, char *argv[])
{
    char checkName[BUFFER_LEN];
    char category[BUFFER_LEN];
    int val;
    bool answerCorrect = false;
    char userAnswer[BUFFER_LEN];

    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[4];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and prompt for players names
    // initial size each of the players in the array
    for(int i = 0; i < 4; i++){
        printf("What is your name player %d\n", i+1);
        scanf("%s", players[i].name);
        players[i].score = 0;
    }

    // Call functions from the questions and players source files
    initialize_game();

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Execute the game until all questions are answered
        printf("Enter a name of a contestant: ");
        scanf("%s", checkName);

        // Prints 1 if the name exists - this works
        // Don't need to print
        //printf("%d\n", player_exists(players, &checkName));

        if(player_exists(players, checkName) == 1){
            display_categories();
            scanf("%s %d", category, &val);
            display_question(category, val);

            //USER INPUT here (scanf maybe?)

            //TOKENIZE CODE HERE (NOTE: scanf and strtok do not work together well (need to find a trick/hack))

            //tokenize(userAnswer, tokens); 

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

        // Display the final results and exit
    }
    return EXIT_SUCCESS;
}
