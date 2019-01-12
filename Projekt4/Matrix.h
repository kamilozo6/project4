#pragma once
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Vector.h"


#define MATRIX_MAP std::unordered_map<uint32_t, double_t>
#define COLUMN_MAP std::unordered_set<uint32_t>

class Matrix
{
private:
	// array of maps, size is n*n
	MATRIX_MAP *matrixTable;
	COLUMN_MAP *rowsInColumn;
	uint32_t matrixSize;
public:
	Matrix();
	~Matrix();

	static Matrix* Create(uint32_t size);

	virtual void EvaluateProbability(uint32_t n);
	void ProbablilityForSpecificCase(uint32_t yes, uint32_t no, uint32_t n);
	uint32_t ReturnIndex(uint32_t yes, uint32_t no, uint32_t n);

	void WriteToConsole();

	Matrix& operator = (Matrix*& input);

	uint32_t GetMatrixSize()
	{
		return matrixSize;
	}

	double_t GetMatrixCell(uint32_t row, uint32_t collumn)
	{
		return matrixTable[row][collumn];
	}

	MATRIX_MAP& GetRowMap(uint32_t row)
	{
		return matrixTable[row];
	}

	void SetMatrixCell(uint32_t row, uint32_t column, double_t value);

	void ResetValuesInCurrentColumn(uint32_t column, Vector& vectorB);

	void CountXvalue(uint32_t row, Vector*& vectorX, Vector& vectorB);

	void CountXValuesForIteration(uint32_t row, Vector*& vectorX, Vector*& vectorNewX, Vector*& baseB);
};

