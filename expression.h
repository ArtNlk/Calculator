#ifndef EXPRESSIONS
#define EXPRESSIONS

#define MAX_EXPRESSION_LENGTH 2048

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "nodestack.h"
#include "exitcodes.h"
#include "debugs.h"
#include "utils.h"
#include "operations.h"

#define MAX_EXPRESSION_STRING_LENGTH 1024

typedef struct expression_struct
{
	int isRoot;
	char* varName;
	char* expression;
	complexDouble result;
}EXPRESSION;

EXPRESSION* initExpression();

EXPRESSION* initExpressionFromString(char* expressionString);

int replaceVariables(char* expression, EXPRESSION** expressionDatabase, int numExpressions);

void expressionStringToRPNNodestack(NODESTACK* nodestack, EXPRESSION* expression);

complexDouble solve(EXPRESSION* expression, EXPRESSION** expressionsDatabase, int numExpressions);

#endif