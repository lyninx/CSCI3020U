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

// Initialization Functions
int get_category_index(int questionindex);
int get_question_value(int questionindex);

// search functions
// CURRENTLY NOT USED
question* get_question(const char* category, int value);


// Initializes the array of questions for the game
void initialize_game(void)
{
        // initialize questions
        for(int i = 0; i < N_QUESTIONS; ++i)
        {
			// Initialize values
			strcpy(questions[i].question, question_questions[i]);
			strcpy(questions[i].answer, question_answers[i]);
            strcpy(questions[i].category, categories[get_category_index(i)]);
            questions[i].value = get_question_value(i);
            questions[i].answered = false;

			// Append 'what is' to answer
			if (INIT_APPEND_WHAT_IS)
			{
				char whatis[MAX_LEN] = "what is ";
				strcat(whatis, questions[i].answer);
				strcpy(questions[i].answer, whatis);
			}

        }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
	printf("Available Categories\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\nPick One\n");
	for(int i = 0; i < N_QUESTIONS; i++){	//CHANGE 1 LATER AFTER TESTING
		if(questions[i].answered == false){
			printf("%s %d\n", questions[i].category, questions[i].value);			
		}
	}
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
	bool display = true;
	display = already_answered(category, value);
	if(display == false){
		for(int i = 0; i < N_QUESTIONS; i++){
			if((strcmp(questions[i].category, category) == 0) && (questions[i].value == value)){
				printf("%s\n", questions[i].question);
			}
		}			
	}
	else{
		printf("Question has already been answered or is not valid.\n");
	} 
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{	
    // Look into string comparison functions
	for(int i = 0; i < N_QUESTIONS; i++){
		if((strcmp(questions[i].category, category) == 0) && (questions[i].value == value)){

			// mark question as answered
			questions[i].answered = true;

			// determine if true or false
			if(strcmp(answer, questions[i].answer) == 0){

				return true;
			}
			else {
				break;
			}
		}
	}
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
	for(int i = 0; i < N_QUESTIONS; i++){ 
		if((strcmp(questions[i].category, category) == 0) && (questions[i].value == value) && questions[i].answered == false){

			
			return false;
		}
		else if((strcmp(questions[i].category, category) == 0) && (questions[i].value == value) && questions[i].answered == true){

			return true;
		}
	}
    return true;
}

void print_answer(char *category, int value){
	for(int i = 0; i < N_QUESTIONS; i++){ 
		if((strcmp(questions[i].category, category) == 0) && (questions[i].value == value)){
			printf("%s\n", questions[i].answer);
		}
	}
}

bool game_done(){
	for(int i = 0; i < N_QUESTIONS; i++){
		if(questions[i].answered == false){
			return false;
		}
	}
	return true;
}

int get_category_index(int questionindex)
{
    return (N_CATS*questionindex)/N_QUESTIONS;
}

int get_question_value(int questionindex)
{
    return point_tiers[questionindex % (N_QUESTIONS/N_CATS)];
}

question* get_question(const char* category, int value)
{
	// traverse questions
	for (int i = 0; i < N_QUESTIONS; i++){
		question* q = &questions[i];
		if ((strcmp(q->category, category) == 0) && (q->value == value)){
			return q;
		}
	}

	// question not found
	return NULL;
}