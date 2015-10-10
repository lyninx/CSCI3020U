/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef QUESTIONS_H_
#define QUESTIONS_H_
/*-----------------------------------------------------------------------------
*								Headers
*----------------------------------------------------------------------------*/
#include <stdbool.h>

/*-----------------------------------------------------------------------------
*							Constants/Macros
*----------------------------------------------------------------------------*/
// string length constant
#define MAX_LEN 256

// category count constant
#define N_CATS 5

// point tier count constant
#define N_POINT_TIERS 5

// question count constant
#define N_QUESTIONS 25

// Flag to set whether 'What is' should be prefixed onto answers upon game initialization.
#define INIT_APPEND_WHAT_IS true

// List of 3 categories as array of strings
static char categories[N_CATS][MAX_LEN] = {"programming", "algorithms", "databases", "operating systems", "computer networks"};

// reference for point tiers
static const int point_tiers[N_POINT_TIERS] = { 100, 200, 300, 400, 500 };


/*-----------------------------------------------------------------------------
*						Question & Answer Strings
*----------------------------------------------------------------------------*/
// Content - Quiz questions
static const char question_questions[N_QUESTIONS][MAX_LEN] =
{
	// Programming 100 question
	"What is the symbol for a pointer?",

	// Programming 200 question
	"Java is a ______-oriented programing language.",

	// Programming 300 question
	"A computer program that converts source code in a programming language to computer language.",

	// Programming 400 question
	"The set of rules, principles, and processes that is the structure of the programming language.",

	// Programming 500 question
	"Low-level programming language that corresponds strongly between the language and architecture's machine code instructions.",

	// Algorithms 100 question
	"According Von Neumann's Model of a computer, a computer has addressable ________?",

	// Algorithm 200 question
	"Unlike C, Java lacks a _______ operator.",

	// Algorithm 300 question
	"The _______ of a binding is the part of the program that can refer to that bind.",

	// Algorithm 400 question
	"The efficency of quicksort belongs to big-O of ____.",

	// Algorithm 500 question
	"Merge sort is a ______ & conquer kind of algorithm.",

	// Databases 100 question
	"This is a thing or an object.",

	// Databases 200 question
	"Property of an entity set.",

	// Databases 300 question
	"Name of the edges between the relationship and the entity set.",

	// Databases 400 question
	"A good database design technique is to avoid _____________.",

	// Databases 500 question
	"________ are only executed when a specified condition occurs.",

	// Operating Systems 100 question
	"What is the name of a program in execution?",

	// Operating Systems 200 question
	"What is a sequential ordered data structure that uses last in, first out?",

	// Operating Systems 300 question
	"Which process state is when instructions are being executed?",

	// Operating Systems 400 question
	"What kind of process can be affected by other processes executing in the system?",

	// Operating Systems 500 question
	"A synchronization tool that provides more sophisticated for processes to synchronize their activities.",

	// Computer Networks 100 question
	"What is the lowest layer?",

	// Computer Networks 200 question
	"One advantage of layering is that it reduces ________.",

	// Computer Networks 300 question
	"Cisco has _ level(s) of certification.",

	// Computer Networks 400 question
	"A special set of rules that end points in a telecommunication connection use when they communicate.",

	// Computer Networks 500 question
	"Data can be ________ during transmission."
};

// Content - Quiz answers
static const char question_answers[N_QUESTIONS][MAX_LEN] =
{
	// Programming 100 answer
	"*",

	// Programming 200 answer
	"object",

	// Programming 300 answer
	"compiler",

	// Programming 400 answer
	"syntax",

	// Programming 500 answer
	"assembly",

	// Algorithms 100 answer
	"memory",

	// Algorithm 200 answer
	"dereference",

	// Algorithm 300 answer
	"scope",

	// Algorithm 400 answer
	"n^2",

	// Algorithm 500 answer
	"divide",

	// Databases 100 answer
	"entity",

	// Databases 200 answer
	"attribute",

	// Databases 300 answer
	"roles",

	// Databases 400 answer
	"redundancy",

	// Databases 500 answer
	"triggers",

	// Operating Systems 100 answer
	"process",

	// Operating Systems 200 answer
	"stack",

	// Operating Systems 300 answer
	"running",

	// Operating Systems 400 answer
	"cooperating",

	// Operating Systems 500 answer
	"semaphore",

	// Computer Networks 100 answer
	"physical",

	// Computer Networks 200 answer
	"complexity",

	// Computer Networks 300 answer
	"3",

	// Computer Networks 400 answer
	"protocol",

	// Computer Networks 500 answer
	"corrupted"
};


/*-----------------------------------------------------------------------------
*								Typedefs
*----------------------------------------------------------------------------*/
// Questions struct for each question
typedef struct {
    char category[MAX_LEN];
    char question[MAX_LEN];
    char answer[MAX_LEN];
    int value;
    bool answered;
} question;

/*-----------------------------------------------------------------------------
*						Function declarations
*----------------------------------------------------------------------------*/
// An array of 12 questions (4 for each category), initialized in initialize_game
// this may need to be a pointer if you want it set dynamically
question questions[N_QUESTIONS];

// Initializes the array of questions for the game; up to ncats categories and ntiers value tiers
extern void initialize_game(int ncats, int ntiers);

// Displays each of the remaining categories and question dollar values that have not been answered
extern void display_categories(void);

extern void display_question(char *category, int value);

// Returns true if the answer is correct for the question
extern bool valid_answer(char *category, int value, char *answer);

// Returns true if the question has already been answered
extern bool already_answered(char *category, int value);

// Prints the answer
extern void print_answer(char *category, int value);

// Checks if the game has finished.
extern bool game_done();


//-----------------------------------------------------------------------------
#endif /* QUESTIONS_H_ */
//-----------------------------------------------------------------------------