#ifndef UTILS
#define UTILS

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <math.h>

#include "nodestack.h"

#define NUM_OPERATORS 6
#define NUM_FUNCTIONS 13
#define NUM_REPLACED_OPERATORS 13

#define NUM_PRIORITIZED_OPERATORS NUM_OPERATORS+2

#define IMAGINARY_CHAR 'j'
#define ARG_SEPARATOR ','

#define MAX_NUMERIC_TOKEN_LENGTH 18 + 1 + 1

#define PI_REPLACEABLE_STRING "PI"
#define PI_STRING "3.1415926535"
#define E_REPLACEABLE_STRING "e"
#define E_STRING "2.7182818284"

static const char* replaceableFunctionStrings[NUM_FUNCTIONS] = {"@sqrt", "$sin", "%cos", "¹tan", "#ctg", ":ln", "&log", "|abs", "?exp", "<real", ">imag", "~mag", "`phase"};
static const char operators[NUM_OPERATORS] = { '+','-','\\','*','/','^'};
static const char functions[NUM_FUNCTIONS] = {'@','$','%','¹','#',':','&','|','?','<','>','~','`'};

static const char operatorPriorities[NUM_PRIORITIZED_OPERATORS][2] = { {'(',-1}, {')',-1} ,{'+',5},{'-',5},{'\\',10},{'*',7},{'/',7},{'^',8} };

int parenthesisAreRight(char* expression);

void replaceStr(const char* needle, char* target, const char* replacement);

int replaceVarName(const char* needle, char* target, const char* replacement);

void replaceFunctionNames(char* expression);

void replaceUnaryMinuses(char* expression);

void replaceConstants(char* expression);

int isOperator(char testedChar);

int isFunction(char testedChar);

int operatorPriority(char operatorChar);

NODE* getNextTokenNode(char** expressionStringPointer);

#endif

