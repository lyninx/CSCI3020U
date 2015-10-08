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

// Initializes the array of questions for the game
void initialize_game(void)
{
		strcpy(questions[0].category, categories[0]);
		strcpy(questions[0].question, "What the symbol for a pointer?");
		strcpy(questions[0].answer, "*");
		questions[0].value = 100;
		questions[0].answered = false;

		//INSERT 11 MORE QUESTIONS, 4 OF EACH CATEGORY
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
				questions[i].answered = true;
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

void printAnswer(char *category, int value){
	for(int i = 0; i < N_QUESTIONS; i++){ 
		if((strcmp(questions[i].category, category) == 0) && (questions[i].value == value)){
			printf("%s\n", questions[i].answer);
		}
	}
}

bool gameDone(){
	for(int i = 0; i < N_QUESTIONS; i++){
		if(questions[i].answered == false){
			return false;
		}
	}
	return true;
}
