#pragma once
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Vector.h"


class Matrix
{
protected:
	uint32_t matrixSize;
public:
	Matrix();
	~Matrix();

	void EvaluateProbability(uint32_t n);
	void ProbablilityForSpecificCase(uint32_t yes, uint32_t no, uint32_t n);
	uint32_t ReturnIndex(uint32_t yes, uint32_t no, uint32_t n);

	uint32_t GetMatrixSize()
	{
		return matrixSize;
	}

	virtual void WriteToConsole() = 0;

	virtual double_t GetMatrixCell(uint32_t row, uint32_t column) = 0;

	virtual void SetMatrixCell(uint32_t row, uint32_t column, double_t value) = 0;

	virtual void ResetValuesInCurrentColumn(uint32_t column, Vector& vectorB) = 0;

	virtual void CountXvalue(uint32_t row, Vector*& vectorX, Vector& vectorB) = 0;

	virtual void CountXValuesForIteration(uint32_t row, Vector*& vectorX, Vector*& vectorNewX, Vector*& baseB) = 0;

	virtual uint32_t SearchBestRow(uint32_t k) = 0;

	virtual void ChangeRows(uint32_t k, uint32_t best) = 0;

};

