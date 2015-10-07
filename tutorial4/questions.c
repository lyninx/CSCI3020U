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
		questions[0].category = categories[get_category(0)];
		questions[0].question = "q1";
		questions[0].answer = "ans1";
		questions[0].value = "100";
		questions[0].answered = false;

		questions[1].category = categories[get_category(0)];
		questions[1].question = "q2";
		questions[1].answer = "ans2";
		questions[1].value = "200";
		questions[1].answered = false;

		questions[2].category = categories[get_category(0)];
		questions[2].question = "q3";
		questions[2].answer = "ans3";
		questions[2].value = "300";
		questions[2].answered = false;

		questions[3].category = categories[get_category(0)];
		questions[3].question = "q4";
		questions[3].answer = "ans4";
		questions[3].value = "400";
		questions[3].answered = false;

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

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
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
