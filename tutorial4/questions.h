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
#define N_QUESTIONS 12 //CHANGE TO 12 AFTER THE QUESTIONS HAVE BEEN ADDED

// List of 3 categories as array of strings
static char categories[N_CATS][MAX_LEN] = {"programming", "algorithms", "databases"};

// reference for point tiers
static const int point_tiers[N_QUESTIONS / N_CATS] = { 100, 200, 300, 500 };

// Content - Quiz questions
static const char question_questions[N_QUESTIONS][MAX_LEN] =
{
	// Programming 100 question
	"What is the symbol for a pointer?",

	// Programming 200 question
	"What does RAII stand for?",

	// Programming 300 question
	"",

	// Programming 500 question
	"",

	// Algorithms 100 question
	"",

	// Algorithm 200 question
	"",

	// Algorithm 300 question
	"What is the worst case big-O efficency of a binary search?",

	// Algorithm 500 question
	"",

	// Databases 100 question
	"",

	// Databases 200 question
	"",

	// Databases 300 question
	"",

	// Databases 500 question
	""
};

// Content - Quiz answers
static const char question_answers[N_QUESTIONS][MAX_LEN] =
{
	// Programming 100 answer
	"*",

	// Programming 200 answer
	"Resource Acquisition Is Initialization",

	// Programming 300 answer
	"",

	// Programming 500 answer
	"",

	// Algorithms 100 answer
	"",

	// Algorithm 200 answer
	"",

	// Algorithm 300 answer
	"n",

	// Algorithm 500 answer
	"",

	// Databases 100 answer
	"",

	// Databases 200 answer
	"",

	// Databases 300 answer
	"",

	// Databases 500 answer
	""
};

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

extern void display_question(char *category, int value);

// Returns true if the answer is correct for the question
extern bool valid_answer(char *category, int value, char *answer);

// Returns true if the question has already been answered
extern bool already_answered(char *category, int value);

extern void printAnswer(char *category, int value);

extern bool gameDone();

#endif /* QUESTIONS_H_ */