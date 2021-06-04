#include "nodes.h"

NODE* initNode()
{
	NODE* newNode = calloc(1,sizeof(NODE));

	if (newNode == NULL)
	{
		error("Error allocating new node struct");
		exit(MALLOC_ERR_EXIT_CODE);
	}

	newNode->nodeType = NoneNode;
	newNode->operatorChar = NULL;
	newNode->value = _Cbuild(0,0);
	newNode->varName = calloc(MAX_VARNAME_LENGTH,sizeof(char));

	return newNode;
}

NODE* initValueNode()
{
	NODE* newNode = calloc(1, sizeof(NODE));

	if (newNode == NULL)
	{
		error("Error allocating new value node struct");
		exit(MALLOC_ERR_EXIT_CODE);
	}

	newNode->nodeType = ValueNode;
	newNode->operatorChar = NULL;
	newNode->value = _Cbuild(0, 0);
	newNode->varName = NULL;

	return newNode;
}

NODE* initValueNodeFromValue(double real, double imag)
{
	NODE* newNode = calloc(1, sizeof(NODE));

	if (newNode == NULL)
	{
		error("Error allocating newvalue node struct from value");
		exit(MALLOC_ERR_EXIT_CODE);
	}

	newNode->nodeType = ValueNode;
	newNode->operatorChar = NULL;
	newNode->value = _Cbuild(real,imag);
	newNode->varName = NULL;

	return newNode;
}

NODE* initOperatorNode()
{
	NODE* newNode = calloc(1, sizeof(NODE));

	if (newNode == NULL)
	{
		error("Error allocating new operator node struct");
		exit(MALLOC_ERR_EXIT_CODE);
	}

	newNode->nodeType = OperatorNode;
	newNode->operatorChar = NULL;
	newNode->value = _Cbuild(0, 0);
	newNode->varName = NULL;

	return newNode;
}

NODE* initOperatorNodeFromValue(char operatorChar)
{
	NODE* newNode = calloc(1, sizeof(NODE));

	if (newNode == NULL)
	{
		error("Error allocating new operator node struct from value");
		exit(MALLOC_ERR_EXIT_CODE);
	}

	newNode->nodeType = OperatorNode;
	newNode->operatorChar = operatorChar;
	newNode->value = _Cbuild(0, 0);
	newNode->varName = NULL;

	return newNode;
}

NODE* initFunctionNode()
{
	NODE* newNode = calloc(1, sizeof(NODE));

	if (newNode == NULL)
	{
		error("Error allocating new function node struct");
		exit(MALLOC_ERR_EXIT_CODE);
	}

	newNode->nodeType = FunctionNode;
	newNode->operatorChar = NULL;
	newNode->value = _Cbuild(0, 0);
	newNode->varName = NULL;

	return newNode;
}

NODE* initFunctionNodeFromValue(char functionChar)
{
	NODE* newNode = calloc(1, sizeof(NODE));

	if (newNode == NULL)
	{
		error("Error allocating new function node struct from value");
		exit(MALLOC_ERR_EXIT_CODE);
	}

	newNode->nodeType = FunctionNode;
	newNode->operatorChar = functionChar;
	newNode->value = _Cbuild(0, 0);
	newNode->varName = NULL;

	return newNode;
}

NODE* initOpenBracketNode()
{
	NODE* node = initNode();

	node->nodeType = OpenBracketNode;
	node->operatorChar = '(';

	return node;
}

NODE* initClosingBracketNode()
{
	NODE* node = initNode();

	node->nodeType = ClosingBracketNode;
	node->operatorChar = ')';

	return node;
}

NODE* initSeparatorNode()
{
	NODE* node = initNode();

	node->nodeType = SeparatorNode;
	node->operatorChar = ',';

	return node;
}

//NODE* initVariableNodeFromValue(char* varName)
//{
//	NODE* newNode = calloc(1, sizeof(NODE));
//
//	if (newNode == NULL)
//	{
//		error("Error allocating new operator node struct from value");
//		exit(MALLOC_ERR_EXIT_CODE);
//	}
//
//	newNode->nodeType = VariableNode;
//	newNode->operatorChar = '\0';
//	newNode->value = _Cbuild(0, 0);
//	newNode->varName = NULL;
//
//	return newNode;
//}

double getReal(NODE* node)
{
	if (node->nodeType != ValueNode)
	{
		error("Requested real part from non-value node");
		exit(GENERAL_ERR_CODE);
	}

	return creal(node->value);
}

double getImag(NODE* node)
{
	if (node->nodeType != ValueNode)
	{
		error("Requested imaginary part from non-value node");
		exit(GENERAL_ERR_CODE);
	}

	return cimag(node->value);
}