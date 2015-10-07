/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef QUESTIONS_H_
#define QUESTIONS_H_

#include <stdbool.h>

// string length constant
#define MAX_LEN 256

// category count constant
#define N_CATS 3

// question count constant
#define N_QUESTIONS 12

// List of 3 categories as array of strings
static char categories[N_CATS][MAX_LEN] = {"programming", "algorithms", "databases"};

// Questions struct for each question
typedef struct {
    char category[MAX_LEN];
    char question[MAX_LEN];
    char answer[MAX_LEN];
    int value;
    bool answered;
} question;

// An array of 12 questions (4 for each category), initialized in initialize_game
// this may need to be a pointer if you want it set dynamically
question questions[N_QUESTIONS];

// Initializes the array of questions for the game
extern void initialize_game(void);

// Displays each of the remaining categories and question dollar values that have not been answered
extern void display_categories(void);

// Finds an unanswered question that matches the category and money values
// given.
// When no question is found, a pointer initialized to NULL is returned.
extern question* match_unanswered(const char* category, int value);

// Displays a prompt to answer the given question.
// If the question is answered correctly, the function returns true.
// Something else is responsible for distributing points to the player.
extern bool prompt_answer(question* q);

// Returns true if the answer is correct for the question
extern bool valid_answer(question* q, char *answer);

// Returns true if the question has already been answered
extern bool already_answered(char *category, int value);

#endif /* QUESTIONS_H_ */