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
#include "questions.h"

/**
*   Determines question category based on the index of the question
*   - Kathryn
**/
//int get_category(int index);


// Initializes the array of questions for the game
void initialize_game(void)
{
		strcpy(questions[0].category, categories[0]);
		strcpy(questions[0].question, "What is the color of a firetruck?");
		strcpy(questions[0].answer, "Red");
		questions[0].value = 100;
		questions[0].answered = false;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
	for(int i = 0; i < 1; i++){
		if(questions[i].answered == false){
			printf("%s %d\n", questions[i].category, questions[i].value);			
		}
	}
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
	   
}

// bool already_answered(char *category, int value)
// {
//     // lookup the question and see if it's already been marked as answered
//     return false;
// }

question* match_unanswered(const char* category, int value)
{
    
    // check each question
    for(int i = 0; i < N_QUESTIONS; i++)
    {
        // get current question
        question* currq = &questions[i];
        
        // skip if the question has been answered
        if(currq->answered)
        {
            continue;
        }
        
        // match dollar values
        if(currq->value == value)
        {
            // match category values
            if(strcmp(currq->category, category) == 0)
            {
                // return question pointer
                return currq;
            }
        }
    }
    
    return NULL;
}

bool prompt_answer(question* q)
{
    // print out answer
    
    // take in answer
    
    //return valid_answer(
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(question* q, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}

// int get_category(int index)
// {
//     return(N_CATS*index)/N_QUESTIONS;
// }
