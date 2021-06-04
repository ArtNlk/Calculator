#include "nodestack.h"

NODESTACK* initStack()
{
	NODESTACK* nodestack = calloc(1,sizeof(NODESTACK));

	if (nodestack == NULL)
	{
		error("Error allocating new stack struct");
		exit(MALLOC_ERR_EXIT_CODE);
	}

	nodestack->nodes = calloc(START_NODESTACK_SIZE,sizeof(NODE));
	if (nodestack->nodes == NULL)
	{
		error("Error allocating stack nodes array");
		exit(MALLOC_ERR_EXIT_CODE);
	}

	nodestack->size = START_NODESTACK_SIZE;
	nodestack->topIndex = -1;
	nodestack->bottomIndex = -1;

	return nodestack;
}

int stackIsEmpty(NODESTACK* nodestack)
{
	return (nodestack->topIndex == -1);
}

int stackIsEmptyAsQueue(NODESTACK* nodestack)
{
	return (nodestack->topIndex+1 == nodestack->bottomIndex);
}

int stackIsFull(NODESTACK* nodestack)
{
	return (nodestack->topIndex + 1 == nodestack->size);
}

NODE popNode(NODESTACK* nodestack)
{
	if (stackIsEmpty(nodestack))
	{
		error("Attempt to pop from empty stack");
		exit(GENERAL_ERR_CODE);
	}
	
	nodestack->topIndex--;

	return nodestack->nodes[nodestack->topIndex + 1];
}

NODE popNodeFromBottom(NODESTACK* nodestack)
{
	if (nodestack->bottomIndex == (nodestack->topIndex + 1))
	{
		error("Attempt to pop from bottom of empty stack");
		exit(GENERAL_ERR_CODE);
	}

	nodestack->bottomIndex++;

	return nodestack->nodes[nodestack->bottomIndex - 1];
}

NODE topNodeValue(NODESTACK* nodestack)
{
	if (stackIsEmpty(nodestack))
	{
		error("Attempt to access a value of top node of empty stack");
		exit(GENERAL_ERR_CODE);
	}

	return nodestack->nodes[nodestack->topIndex];
}

NODE* topNode(NODESTACK* nodestack)
{
	if (stackIsEmpty(nodestack))
	{
		error("Attempt to access top node of empty stack");
		exit(GENERAL_ERR_CODE);
	}

	return &(nodestack->nodes[nodestack->topIndex]);
}

void pushNode(NODESTACK* nodestack, NODE node)
{
	if (stackIsFull(nodestack))
	{
		nodestack->size += 200;
		nodestack->nodes = realloc(nodestack->nodes, nodestack->size);

		if (nodestack->nodes == NULL)
		{
			error("Cannot reallocate node stack: out of memory");
			exit(GENERAL_ERR_CODE);
		}
	}

	if (nodestack->bottomIndex == -1)
	{
		nodestack->bottomIndex++;
	}

	(nodestack->topIndex) += 1;

	nodestack->nodes[nodestack->topIndex] = node;
}

void pushValue(NODESTACK* nodestack, complexDouble value)
{
	if (stackIsFull(nodestack))
	{
		nodestack->size += 200;
		nodestack->nodes = realloc(nodestack->nodes, nodestack->size);

		if (nodestack->nodes == NULL)
		{
			error("Cannot reallocate node stack in pushValue: out of memory");
			exit(GENERAL_ERR_CODE);
		}
	}

	nodestack->topIndex++;

	NODE* newNode = initValueNodeFromValue(value._Val[0],value._Val[1]);

	nodestack->nodes[nodestack->topIndex] = *newNode;

	free(newNode);

	return;
}

void pushOperator(NODESTACK* nodestack, char operatorChar)
{
	if (stackIsFull(nodestack))
	{
		nodestack->size += 200;
		nodestack->nodes = realloc(nodestack->nodes, nodestack->size);

		if (nodestack->nodes == NULL)
		{
			error("Cannot reallocate node stack in pushOperator: out of memory");
			exit(GENERAL_ERR_CODE);
		}
	}

	nodestack->topIndex++;

	NODE* newNode = initOperatorNodeFromValue(operatorChar);

	nodestack->nodes[nodestack->topIndex] = *newNode;

	free(newNode);

	return;
}
