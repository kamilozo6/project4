#pragma once
#include "Matrix.h"
class Vector :
	public Matrix
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
};

