#include "expression.h"

EXPRESSION* initExpression()
{
	EXPRESSION* newExpression = calloc(1,sizeof(EXPRESSION));

	if (newExpression == NULL)
	{
		error("Error allocating new operator node struct");
		exit(GENERAL_ERR_CODE);
	}

	newExpression->isRoot = 0;
	newExpression->expression = NULL;
	newExpression->varName = calloc(MAX_VARNAME_LENGTH,sizeof(char));

	if (newExpression->varName == NULL)
	{
		error("Canot allocate expression var name");
	}

	return newExpression;
}

EXPRESSION* initExpressionFromString(char* expressionString)
{
	EXPRESSION* expression = initExpression();
	replaceStr(" ",expressionString,"");
	replaceStr("\n", expressionString, "");

	if (!parenthesisAreRight(expressionString))
	{
		printf("Parenthesis parity error!\n");
		exit(UNBALANCED_PARENTHESIES_ERR_CODE);
	}

	int expressionStringLength = strlen(expressionString);
	int expressionLength = 0;

	expression->isRoot = 1;
	int varnameEndIndex = 0;

	for (int i = 0; i < expressionStringLength; i++)
	{
		if (expressionString[i] == '=')
		{
			expression->isRoot = 0;
			varnameEndIndex = i-1;
			break;
		}
	}

	if (expression->isRoot != 1)//if not root, get variable name
	{
		//for (int i = 0; i < varnameEndIndex; i++)
		//{
		//	expression->varName[i] = expressionString[i];
		//	if (i+1 == varnameEndIndex)
		//	{
		//		expression->varName[i + 1] = '\0';
		//	}
		//}

		strncpy_s(expression->varName,MAX_VARNAME_LENGTH,expressionString,varnameEndIndex+1);
		expressionLength = strlen(expressionString + varnameEndIndex + 2);
		//expression->expression = calloc(expressionLength+2+1,sizeof(char));//Leave space for brackets
		expression->expression = calloc(MAX_EXPRESSION_LENGTH, sizeof(char));
		expression->expression[0] = '(';
		strcpy_s(expression->expression+1,expressionLength+1,expressionString+varnameEndIndex + 2);
		expression->expression[strlen(expression->expression)] = ')';
	}
	else
	{
		expressionLength = strlen(expressionString);
		//expression->expression = calloc(expressionLength+1, sizeof(char));
		expression->expression = calloc(MAX_EXPRESSION_LENGTH, sizeof(char));
		strcpy_s(expression->expression, expressionLength+1, expressionString);
	}

	return expression;
}

int replaceVariables(char* expression, EXPRESSION** expressionDatabase, int numExpressions)
{
	int numReplacements = 0;
	for (int i = 0; i < numExpressions; i++)
	{
		if (!expressionDatabase[i]->isRoot)
		{
			numReplacements += replaceVarName(expressionDatabase[i]->varName,expression,expressionDatabase[i]->expression);
		}
	}

	return numReplacements;
}

void expressionStringToRPNNodestack(NODESTACK* nodestack, EXPRESSION* expression)
{
	NODESTACK* tempStack = initStack();

	NODE* nextNode = NULL;

	char* exprPointer = expression->expression;

	while (nextNode = getNextTokenNode(&exprPointer))
	{
		if (nextNode->nodeType == ValueNode)
		{
			pushNode(nodestack,*nextNode);
			free(nextNode);
			continue;
		}

		if (nextNode->nodeType == FunctionNode)
		{
			pushNode(tempStack, *nextNode);
			free(nextNode);
			continue;
		}

		if (nextNode->nodeType == SeparatorNode)
		{
			while (topNodeValue(tempStack).nodeType != OpenBracketNode)
			{
				if (stackIsEmpty(tempStack))
				{
					printf("Unbalanced brackets detected in expression %s", expression->expression);
					exit(GENERAL_ERR_CODE);
				}
				pushNode(nodestack,popNode(tempStack));
			}
			free(nextNode);
			continue;
		}

		if (nextNode->nodeType == OperatorNode)
		{
			while (!stackIsEmpty(tempStack) && operatorPriority(topNodeValue(tempStack).operatorChar) >= operatorPriority(nextNode->operatorChar))
			{
				pushNode(nodestack,popNode(tempStack));
			}
			pushNode(tempStack,*nextNode);
			free(nextNode);
			continue;
		}

		if (nextNode->nodeType == OpenBracketNode)
		{
			pushNode(tempStack,*nextNode);
			free(nextNode);
			continue;
		}

		if (nextNode->nodeType == ClosingBracketNode)
		{
			while (!stackIsEmpty(tempStack) && topNodeValue(tempStack).nodeType != OpenBracketNode)
			{
				pushNode(nodestack,popNode(tempStack));
			}
			popNode(tempStack);
			free(nextNode);
			continue;
		}
	}

	while (!stackIsEmpty(tempStack))
	{
		if (topNodeValue(tempStack).nodeType == OpenBracketNode || topNodeValue(tempStack).nodeType == ClosingBracketNode)
		{
			printf("Unbalanced brackets detected in expression %s", expression);
			exit(INVALID_TOKEN_ERROR_CODE);
		}

		pushNode(nodestack, popNode(tempStack));
	}

	return;
}

complexDouble solve(EXPRESSION* expression, EXPRESSION** expressionsDatabase, int numExpressions)
{
	while (replaceVariables(expression->expression, expressionsDatabase, numExpressions) != 0);

	replaceConstants(expression->expression);
	replaceConstants(expression->expression);

	replaceFunctionNames(expression->expression);
	replaceUnaryMinuses(expression->expression);

	NODESTACK* rpnStack = initStack();

	NODESTACK* solvingStack = initStack();

	NODE tempNode = { 0 };

	expressionStringToRPNNodestack(rpnStack,expression);

	while (!stackIsEmptyAsQueue(rpnStack))
	{
		tempNode = popNodeFromBottom(rpnStack);

		if (tempNode.nodeType == ValueNode)
		{
			pushNode(solvingStack,tempNode);
			continue;
		}

		switch (tempNode.operatorChar)
		{
			//MEMCARDS: 
			//'+' '-' '\\' '*' '/' '^'
			//'@','$','%','¹','#',':','&','|','?','<','>','~','`'
			//"@sqrt", "$sin", "%cos", "¹tan", "#ctg", ":ln", "&log", "|abs", "?exp", "<real", ">imag", "~mag", "`phase"
			case '+':
				addOp(solvingStack);
				break;

			case '-':
				subOp(solvingStack);
				break;

			case '\\':
				unaryMinusOp(solvingStack);
				break;

			case '*':
				mulOp(solvingStack);
				break;

			case '/':
				divOp(solvingStack);
				break;

			case '^':
				powOp(solvingStack);
				break;

			case '@':
				sqrtOp(solvingStack);
				break;

			case '$':
				sinOp(solvingStack);
				break;

			case '%':
				cosOp(solvingStack);
				break;

			case '¹':
				tanOp(solvingStack);
				break;

			case '#':
				ctgOp(solvingStack);
				break;

			case ':':
				lnOp(solvingStack);
				break;

			case '&':
				logOp(solvingStack);
				break;

			case '|':
				absOp(solvingStack);
				break;

			case '?':
				expOp(solvingStack);
				break;

			case '<':
				realOp(solvingStack);
				break;

			case '>':
				imagOp(solvingStack);
				break;

			case '~':
				magOp(solvingStack);
				break;

			case '`':
				phaseOp(solvingStack);
				break;

		}
	}

	tempNode = popNode(solvingStack);

	free(rpnStack->nodes);
	free(rpnStack);
	free(solvingStack->nodes);
	free(solvingStack);

	return tempNode.value;
}
