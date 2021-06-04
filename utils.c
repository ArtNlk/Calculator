#include "utils.h"

int parenthesisAreRight(char* expression)
{
	int pCount = 0;
	int exprLength = strlen(expression);

	for (int i = 0; i<= exprLength; i++)
	{
		if (expression[i] == '(')
		{
			pCount++;
		}
		else if (expression[i] == ')')
		{
			if (pCount == 0)
			{
				printf_s("Unbalanced brackets detected in expression: %s",expression);
				return 0;
			}
			else
			{
				pCount--;
			}
		}
	}

	if (pCount != 0)
	{
		printf_s("Unbalanced brackets detected in expression: %s", expression);
		return 0;
	}
	else
	{
		return 1;
	}
}

void replaceStr(const char* needle, char* target, const char* replacement)
{
	char buffer[1024] = { 0 };
	char* insert_point = &buffer[0];
	const char* tmp = target;
	size_t needle_len = strlen(needle);
	size_t repl_len = strlen(replacement);

	while (1) {
		const char* p = strstr(tmp, needle);

		// walked past last occurrence of needle; copy remaining part
		if (p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}

		// copy part before needle
		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;

		// copy replacement string
		memcpy(insert_point, replacement, repl_len);
		insert_point += repl_len;

		// adjust pointers, move on
		tmp = p + needle_len;
	}

	// write altered string back to target
	strcpy(target, buffer);

	return;
}

int replaceVarName(const char* needle, char* target, const char* replacement)
{
	char buffer[2048] = { 0 };
	char* insert_point = &buffer[0];
	const char* tmp = target;
	size_t needle_len = strlen(needle);
	size_t repl_len = strlen(replacement);

	int counter = 0;

	while (1) {
		const char* p = strstr(tmp, needle);

		// walked past last occurrence of needle; copy remaining part
		if (p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}

		if (p == tmp && isalnum(*(p + strlen(needle))))
		{
			// copy part before needle
			memcpy(insert_point, tmp, p - tmp);
			insert_point += p - tmp;

			// copy needle string
			memcpy(insert_point, needle, needle_len);
			insert_point += needle_len;

			// adjust pointers, move on
			tmp = p + needle_len;

			continue;
		}

		if (p != tmp && *(p + 1) != '\0' && (isalnum(*(p + strlen(needle))) || isalnum(*(p - 1))))
		{
			// copy part before needle
			memcpy(insert_point, tmp, p - tmp);
			insert_point += p - tmp;

			// copy needle string
			memcpy(insert_point, needle, needle_len);
			insert_point += needle_len;

			// adjust pointers, move on
			tmp = p + needle_len;

			continue;
		}

		// copy part before needle
		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;

		// copy replacement string
		memcpy(insert_point, replacement, repl_len);
		insert_point += repl_len;
		counter++;

		// adjust pointers, move on
		tmp = p + needle_len;
	}

	// write altered string back to target
	strcpy(target, buffer);

	return counter;
}

void replaceFunctionNames(char* expression)
{
	char* operatorCharString = calloc(2,sizeof(char));
	for (int i = 0; i < NUM_FUNCTIONS; i++)
	{
		operatorCharString[0] = replaceableFunctionStrings[i][0];

		replaceStr(replaceableFunctionStrings[i] + 1,expression,operatorCharString); //Since first char in operator string is char of this operator, we search for string without first character
	}
	free(operatorCharString);
	return;
}

void replaceUnaryMinuses(char* expression)
{
	int index = 0;
	while (expression[index] != '\0')
	{
		if (index == 0)
		{
			if (expression[index] == '-')
			{
				expression[index] = '\\';
				index++;
				continue;
			}
			index++;
			continue;
		}
		else
		{
			if (expression[index] == '-' && !isdigit(expression[index - 1]) && expression[index - 1] != ')' && expression[index - 1] != 'j')
			{
				expression[index] = '\\';
				index++;
				continue;
			}
			index++;
			continue;
		}
	}
}

void replaceConstants(char* expression)
{
	replaceVarName(PI_REPLACEABLE_STRING,expression,PI_STRING);
	replaceVarName(E_REPLACEABLE_STRING,expression,E_STRING);

	return;
}


int isOperator(char testedChar)
{
	for (int i = 0; i < NUM_OPERATORS; i++)
	{
		if (operators[i] == testedChar)
		{
			return 1;
		}
	}

	return 0;
}

int isFunction(char testedChar)
{
	for (int i = 0; i < NUM_FUNCTIONS; i++)
	{
		if (functions[i] == testedChar)
		{
			return 1;
		}
	}

	return 0;
}

int operatorPriority(char operatorChar)
{
	if (isFunction(operatorChar))
	{
		return 100;
	}
	for (int i = 0; i < NUM_PRIORITIZED_OPERATORS; i++)
	{
		if (operatorPriorities[i][0] == operatorChar)
		{
			return operatorPriorities[i][1];
		}
	}

	printf("Invalid operator encountered in trying to get operator priotiy: %c",operatorChar);
	exit(INVALID_TOKEN_ERROR_CODE);
}

//Return new token node, changes expression string pointer to next token position
NODE* getNextTokenNode(char** expressionStringPointer)
{
	if (**expressionStringPointer == '\0')
	{
		return NULL;
	}

	if (isOperator(**expressionStringPointer))
	{
		NODE* newNode = initOperatorNodeFromValue(**expressionStringPointer);
		++*expressionStringPointer;
		return newNode;
	}

	if (isFunction(**expressionStringPointer))
	{
		NODE* newNode = initFunctionNodeFromValue(**expressionStringPointer);
		++* expressionStringPointer;
		return newNode;
	}

	if (**expressionStringPointer == '(')
	{
		NODE* newNode = initOpenBracketNode();
		++* expressionStringPointer;
		return newNode;
	}

	if (**expressionStringPointer == ')')
	{
		NODE* newNode = initClosingBracketNode();
		++* expressionStringPointer;
		return newNode;
	}

	if (**expressionStringPointer == ARG_SEPARATOR)
	{
		NODE* newNode = initSeparatorNode();
		++* expressionStringPointer;
		return newNode;
	}

	int isImag = 0;
	
	int offset = 0;
	char* tempString = calloc(MAX_NUMERIC_TOKEN_LENGTH,sizeof(char));

	if (tempString == NULL)
	{
		error("Cannot malloc temporary string for token reading");
		exit(GENERAL_ERR_CODE);
	}

	while (!isOperator((*expressionStringPointer)[offset]) && (*expressionStringPointer)[offset] != '(' && (*expressionStringPointer)[offset] != ')' && (*expressionStringPointer)[offset] != 0 && (*expressionStringPointer)[offset] != ARG_SEPARATOR)
	{
		if (offset >= MAX_NUMERIC_TOKEN_LENGTH-1)
		{
			printf("Lengthy token encountered in expression starting from %s, max token length is %d, including imaginary char", *expressionStringPointer, MAX_NUMERIC_TOKEN_LENGTH-1);
			exit(INVALID_TOKEN_ERROR_CODE);
		}
		tempString[offset] = (*expressionStringPointer)[offset];
		offset++;
	}

	//tempString[offset] = '\0'; Dont need that due to calloc

	isImag = tempString[offset-1] == IMAGINARY_CHAR;

	double value = 0.0;
	if (strlen(tempString) == 1 && isImag)
	{
		value = 1;
	}
	else
	{
		value = strtod(tempString, NULL);
	}
	free(tempString);

	if (isImag)
	{
		NODE* node = initValueNodeFromValue(0, value);
		*expressionStringPointer += offset;
		return node;
	}
	else
	{
		NODE* node = initValueNodeFromValue(value, 0);
		*expressionStringPointer += offset;
		return node;
	}
}