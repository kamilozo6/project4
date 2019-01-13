#include "pch.h"
#include "Vector.h"
#include <stdio.h>


Vector::Vector():
	vectorSize(0),
	vectorTable(NULL)
{
}


Vector::~Vector()
{
	delete vectorTable;
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

Vector & Vector::operator=(Vector *& input)
{
	vectorSize = input->GetVectorSize();
	vectorTable = new double_t[vectorSize];
	for (uint32_t i = 0; i < vectorSize; i++)
	{
		vectorTable[i] = input->GetVectorCell(i);
	}
	return *this;
}

uint32_t Vector::ReturnIndex(uint32_t yes, uint32_t no, uint32_t n)
{
	uint32_t index = 0;

	for (uint32_t i = 1; i <= yes; i++)
	{
		index += n + 2 - i;
	}

	index += no;
	return index;
}

double_t Vector::CountNorm()
{
	double_t result = 0;
	for (uint32_t i = 0; i < vectorSize; i++)
	{
		if (result < abs(vectorTable[i]))
		{
			result = abs(vectorTable[i]);
		}
	}
	return result;
}

void Vector::CopySubstract(Vector *& minuend, Vector *& subtrahend)
{
	for (uint32_t i = 0; i < vectorSize; i++)
	{
		vectorTable[i] = minuend->GetVectorCell(i) - subtrahend->GetVectorCell(i);
	}
}

void Vector::CopyValues(Vector *& source)
{
	for (uint32_t i = 0; i < vectorSize; i++)
	{
		vectorTable[i] = source->GetVectorCell(i);
	}
}

void Vector::WriteToConsole()
{
	for (uint32_t i = 0; i < vectorSize; i++)
	{
		printf("%.5f\n", vectorTable[i]);
	}
	printf("\n");
}
