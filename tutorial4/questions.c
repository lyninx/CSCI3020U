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
int get_category(int index);


// Initializes the array of questions for the game
void initialize_game(void)
{
		// for(int i = 0; i < sizeof(questions); i++){
		// 	questions[i].answered = false;
		// }

		// questions[0].category = categories[get_category(0)];
		// questions[0].question = "q1";
		// questions[0].answer = "ans1";
		// questions[0].value = "100";

		// questions[1].category = categories[get_category(0)];
		// questions[1].question = "q2";
		// questions[1].answer = "ans2";
		// questions[1].value = "200";

		// questions[2].category = categories[get_category(0)];
		// questions[2].question = "q3";
		// questions[2].answer = "ans3";
		// questions[2].value = "300";

		// questions[3].category = categories[get_category(0)];
		// questions[3].question = "q4";
		// questions[3].answer = "ans4";
		// questions[3].value = "400";

		// questions[4].category = categories[get_category(0)];
		// questions[4].question = "q5";
		// questions[4].answer = "ans5";
		// questions[4].value = "100";

		// questions[5].category = categories[get_category(0)];
		// questions[5].question = "q6";
		// questions[5].answer = "ans6";
		// questions[5].value = "200";

		// questions[6].category = categories[get_category(0)];
		// questions[6].question = "q7";
		// questions[6].answer = "ans7";
		// questions[6].value = "300";

		// questions[7].category = categories[get_category(0)];
		// questions[7].question = "q8";
		// questions[7].answer = "ans8";
		// questions[7].value = "400";

		// questions[8].category = categories[get_category(0)];
		// questions[8].question = "q9";
		// questions[8].answer = "ans9";
		// questions[8].value = "100";

		// questions[9].category = categories[get_category(0)];
		// questions[9].question = "q10";
		// questions[9].answer = "ans10";
		// questions[9].value = "200";

		// questions[10].category = categories[get_category(0)];
		// questions[10].question = "q11";
		// questions[10].answer = "ans11";
		// questions[10].value = "300";

		// questions[11].category = categories[get_category(0)];
		// questions[11].question = "q12";
		// questions[11].answer = "ans12";
		// questions[11].value = "400";/
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    
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

int get_category(int index)
{
    return(N_CATS*index)/N_QUESTIONS;
}
