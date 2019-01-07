#include "pch.h"
#include "Vector.h"


Vector::Vector()
	: Matrix()
{
}


Vector::~Vector()
{
}

Vector * Vector::Create(uint32_t size)
{
	Vector *newVector = new Vector();

	newVector->vectorSize = size;
	newVector->vectorTable = new double_t[size];
	return newVector;
}

void Vector::EvaluateProbability(uint32_t n)
{
	uint32_t index;
	for (uint32_t yes = 0; yes <= n; yes++)
	{
		for (uint32_t no = 0; no <= n - yes; no++)
		{
			index = ReturnIndex(yes, no, n);
			vectorTable[index] = (yes > 0) && (no == 0) ? 1 : 0;
		}
	}
}
