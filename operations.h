#ifndef OPERATIONS
#define OPERATIONS

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <complex.h>
#include <math.h>

#include "nodestack.h"


NODE* addOp(NODESTACK* nodestack);
NODE* subOp(NODESTACK* nodestack);
NODE* mulOp(NODESTACK* nodestack);
NODE* powOp(NODESTACK* nodestack);
NODE* divOp(NODESTACK* nodestack);
NODE* unaryMinusOp(NODESTACK* nodestack);

NODE* sqrtOp(NODESTACK* nodestack);
NODE* sinOp(NODESTACK* nodestack);
NODE* cosOp(NODESTACK* nodestack);
NODE* tanOp(NODESTACK* nodestack);
NODE* ctgOp(NODESTACK* nodestack);
NODE* lnOp(NODESTACK* nodestack);
NODE* logOp(NODESTACK* nodestack);
NODE* absOp(NODESTACK* nodestack);
NODE* expOp(NODESTACK* nodestack);
NODE* realOp(NODESTACK* nodestack);
NODE* imagOp(NODESTACK* nodestack);
NODE* magOp(NODESTACK* nodestack);
NODE* phaseOp(NODESTACK* nodestack);

#endif // !OPERATIONS

