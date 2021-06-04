#include "operations.h"

NODE* addOp(NODESTACK* nodestack)
{
	NODE tempNode = popNode(nodestack);
	topNode(nodestack)->value._Val[0] += tempNode.value._Val[0];
	topNode(nodestack)->value._Val[1] += tempNode.value._Val[1];

	return topNode(nodestack);
}

NODE* subOp(NODESTACK* nodestack)
{
	NODE tempNode = popNode(nodestack);
	topNode(nodestack)->value._Val[0] -= tempNode.value._Val[0];
	topNode(nodestack)->value._Val[1] -= tempNode.value._Val[1];

	return topNode(nodestack);
}

NODE* mulOp(NODESTACK* nodestack)
{
	NODE tempNode = popNode(nodestack);
	double newReal = topNode(nodestack)->value._Val[0] * tempNode.value._Val[0] - topNode(nodestack)->value._Val[1] * tempNode.value._Val[1]; // (x+yi)(u+vi) = (xu-yv)+(xv+yu)i
	double newImag = topNode(nodestack)->value._Val[0] * tempNode.value._Val[1] + topNode(nodestack)->value._Val[1] * tempNode.value._Val[0];

	topNode(nodestack)->value._Val[0] = newReal;
	topNode(nodestack)->value._Val[1] = newImag;

	return topNode(nodestack);
}

NODE* powOp(NODESTACK* nodestack)
{
	NODE tempNode = popNode(nodestack);
	topNode(nodestack)->value = cpow(topNodeValue(nodestack).value,tempNode.value);
}

NODE* divOp(NODESTACK* nodestack)
{
	NODE tempNode = popNode(nodestack);

	if (tempNode.value._Val[0] == 0.0 && tempNode.value._Val[1] == 0.0)
	{
		error("Division by zero!");
		exit(DIVISION_BY_ZERO_ERR_CODE);
	}
	double newReal = (topNode(nodestack)->value._Val[0] * tempNode.value._Val[0] + topNode(nodestack)->value._Val[1] * tempNode.value._Val[1]) / (tempNode.value._Val[0] * tempNode.value._Val[0] + tempNode.value._Val[1] * tempNode.value._Val[1]);
	double newImag = (topNode(nodestack)->value._Val[1] * tempNode.value._Val[0] - topNode(nodestack)->value._Val[0] * tempNode.value._Val[1]) / (tempNode.value._Val[0] * tempNode.value._Val[0] + tempNode.value._Val[1] * tempNode.value._Val[1]);
	
	topNode(nodestack)->value._Val[0] = newReal;
	topNode(nodestack)->value._Val[1] = newImag;

	return topNode(nodestack);
}

NODE* unaryMinusOp(NODESTACK* nodestack)
{
	topNode(nodestack)->value._Val[0] *= -1.0;
	topNode(nodestack)->value._Val[1] *= -1.0;

	return topNode(nodestack);
}

NODE* sqrtOp(NODESTACK* nodestack)
{
	_Dcomplex temp = _Cbuild(0.0, 0.0);

	temp = csqrt(topNodeValue(nodestack).value);

	topNode(nodestack)->value = temp;
	
	return topNode(nodestack);
}

NODE* sinOp(NODESTACK* nodestack)
{
	_Dcomplex temp = _Cbuild(0.0, 0.0);

	temp = csin(topNodeValue(nodestack).value);

	topNode(nodestack)->value = temp;

	return topNode(nodestack);
}

NODE* cosOp(NODESTACK* nodestack)
{
	_Dcomplex temp = _Cbuild(0.0, 0.0);

	temp = ccos(topNodeValue(nodestack).value);

	topNode(nodestack)->value = temp;

	return topNode(nodestack);
}

NODE* tanOp(NODESTACK* nodestack)
{
	_Dcomplex temp = _Cbuild(0.0, 0.0);

	temp = ctan(topNodeValue(nodestack).value);

	topNode(nodestack)->value = temp;

	return topNode(nodestack);
}


NODE* ctgOp(NODESTACK* nodestack)
{
	_Dcomplex temp1 = _Cbuild(0.0, 0.0);
	_Dcomplex temp2 = _Cbuild(0.0, 0.0);

	temp1 = csin(topNodeValue(nodestack).value);
	temp2 = ccos(topNodeValue(nodestack).value);

	double newReal = (temp2._Val[0] * temp1._Val[0] + temp2._Val[1] * temp1._Val[1]) / (temp1._Val[0] * temp1._Val[0] + temp1._Val[1] * temp1._Val[1]);
	double newImag = (temp2._Val[1] * temp1._Val[0] - temp2._Val[0] * temp1._Val[1]) / (temp1._Val[0] * temp1._Val[0] + temp1._Val[1] * temp1._Val[1]);

	topNode(nodestack)->value._Val[0] = newReal;
	topNode(nodestack)->value._Val[1] = newImag;

	return topNode(nodestack);
}

NODE* lnOp(NODESTACK* nodestack)
{
	_Dcomplex temp = _Cbuild(0.0, 0.0);

	temp = clog(topNodeValue(nodestack).value);

	topNode(nodestack)->value = temp;

	return topNode(nodestack);
}

NODE* logOp(NODESTACK* nodestack)
{
	NODE tempNode = popNode(nodestack);

	_Dcomplex temp1 = _Cbuild(0.0, 0.0);
	_Dcomplex temp2 = _Cbuild(0.0, 0.0);

	temp1 = clog(tempNode.value);
	temp2 = clog(topNodeValue(nodestack).value);

	double newReal = (temp2._Val[0] * temp1._Val[0] + temp2._Val[1] * temp1._Val[1]) / (temp1._Val[0] * temp1._Val[0] + temp1._Val[1] * temp1._Val[1]);
	double newImag = (temp2._Val[1] * temp1._Val[0] - temp2._Val[0] * temp1._Val[1]) / (temp1._Val[0] * temp1._Val[0] + temp1._Val[1] * temp1._Val[1]);
	
	topNode(nodestack)->value._Val[0] = newReal;
	topNode(nodestack)->value._Val[1] = newImag;

	return topNode(nodestack);

}

NODE* absOp(NODESTACK* nodestack)
{
	double newReal = sqrt(topNode(nodestack)->value._Val[0]* topNode(nodestack)->value._Val[0] + topNode(nodestack)->value._Val[1]* topNode(nodestack)->value._Val[1]);

	topNode(nodestack)->value._Val[0] = newReal;
	topNode(nodestack)->value._Val[1] = 0.0;

	return topNode(nodestack);
}

NODE* expOp(NODESTACK* nodestack)
{
	_Dcomplex temp = _Cbuild(0.0, 0.0);

	temp = cexp(topNodeValue(nodestack).value);

	topNode(nodestack)->value = temp;

	return topNode(nodestack);
}

NODE* realOp(NODESTACK* nodestack)
{
	double newReal = creal(topNodeValue(nodestack).value);

	topNode(nodestack)->value._Val[0] = newReal;
	topNode(nodestack)->value._Val[1] = 0;

	return topNode(nodestack);
}

NODE* imagOp(NODESTACK* nodestack)
{
	double newImag = cimag(topNodeValue(nodestack).value);

	topNode(nodestack)->value._Val[0] = 0;
	topNode(nodestack)->value._Val[1] = newImag;

	return topNode(nodestack);
}

NODE* magOp(NODESTACK* nodestack)
{
	double newReal = sqrt(topNode(nodestack)->value._Val[0] * topNode(nodestack)->value._Val[0] + topNode(nodestack)->value._Val[1] * topNode(nodestack)->value._Val[1]);

	topNode(nodestack)->value._Val[0] = newReal;
	topNode(nodestack)->value._Val[1] = 0.0;

	return topNode(nodestack);
}

NODE* phaseOp(NODESTACK* nodestack)
{
	if (topNode(nodestack)->value._Val[0] == 0)
	{
		if (topNode(nodestack)->value._Val[1] > 0)
		{
			topNode(nodestack)->value._Val[0] = M_PI / 2.0;
			topNode(nodestack)->value._Val[1] = 0;
		}
		else if (topNode(nodestack)->value._Val[1] < 0)
		{
			topNode(nodestack)->value._Val[0] = M_PI / 2.0 + M_PI;
			topNode(nodestack)->value._Val[1] = 0;
		}
		else
		{
			topNode(nodestack)->value._Val[0] = 0;
			topNode(nodestack)->value._Val[1] = 0;
		}
	}
	else
	{
		double real = topNode(nodestack)->value._Val[0];
		double imag = topNode(nodestack)->value._Val[1];
		topNode(nodestack)->value._Val[0] =atan(imag/real);
		topNode(nodestack)->value._Val[1] = 0;
	}
}

