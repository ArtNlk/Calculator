#ifndef NODES
#define NODES

#include "exitcodes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <malloc.h>



#define MAX_VARNAME_LENGTH 20
#define complexDouble _C_double_complex

typedef enum nodeType_enum { NoneNode, ValueNode, OperatorNode, FunctionNode,SeparatorNode,OpenBracketNode,ClosingBracketNode} NODETYPE;


typedef struct node_struct
{
	NODETYPE nodeType;
	char operatorChar;
	char* varName;
	complexDouble value;
} NODE;

NODE* initNode();

NODE* initValueNode();

NODE* initValueNodeFromValue(double real, double imag);

NODE* initOperatorNode();

NODE* initOperatorNodeFromValue(char operatorChar);

NODE* initFunctionNode();

NODE* initFunctionNodeFromValue(char functionChar);

NODE* initOpenBracketNode();

NODE* initClosingBracketNode();

NODE* initSeparatorNode();

double getReal(NODE* node);

double getImag(NODE* node);

#endif
