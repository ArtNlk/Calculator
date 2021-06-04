#ifndef _NODESTACK
#define _NODESTACK

#include "complex.h"
#include "nodes.h"
#include "debugs.h"



#define MAX_NODESTACK_SIZE 5000
#define START_NODESTACK_SIZE 1000

typedef struct NODESTACK_struct
{
	NODE* nodes;
	int topIndex;
	int bottomIndex;
	int size;
}NODESTACK;

NODESTACK* initStack();

NODE popNode(NODESTACK* nodestack);

NODE popNodeFromBottom(NODESTACK* nodestack);

NODE topNodeValue(NODESTACK* nodestack);

NODE* topNode(NODESTACK* nodestack);

int stackIsEmpty(NODESTACK* nodestack);

int stackIsEmptyAsQueue(NODESTACK* nodestack);

int stackIsFull(NODESTACK* nodestack);

void pushNode(NODESTACK* nodestack, NODE node);

void pushValue(NODESTACK* nodestack, complexDouble value);

void pushOperator(NODESTACK* nodestack, char operatorChar);

#endif

