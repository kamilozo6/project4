#pragma once
#include <stdint.h>
#include <cmath>

class Vector
{
private:
	double_t *vectorTable;
	uint32_t vectorSize;
public:
	Vector();
	~Vector();

	static Vector* Create(uint32_t size);
	virtual void EvaluateProbability(uint32_t n);

	uint32_t GetVectorSize()
	{
		return vectorSize;
	}

	double_t GetVectorCell(uint32_t row)
	{
		return vectorTable[row];
	}

	void SetVectorCell(uint32_t row, double_t value)
	{
		vectorTable[row] = value;
	}

	Vector& operator = (Vector*& input);

	uint32_t ReturnIndex(uint32_t yes, uint32_t no, uint32_t n);

	void WriteToConsole();

	double_t CountNorm();

	void CopySubstract(Vector*& minuend, Vector*& subtrahend);

	void CopyValues(Vector*& source);
};

