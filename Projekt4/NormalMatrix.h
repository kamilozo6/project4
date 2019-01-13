#pragma once
#include "Matrix.h"
class NormalMatrix :
	public Matrix
{
private:
	double_t **matrixTable;
public:
	NormalMatrix();
	~NormalMatrix();

	static NormalMatrix* Create(uint32_t size);

	virtual void WriteToConsole();

	virtual double_t GetMatrixCell(uint32_t row, uint32_t column)
	{
		return matrixTable[row][column];
	}

	virtual void SetMatrixCell(uint32_t row, uint32_t column, double_t value)
	{
		matrixTable[row][column] = value;
	}

	virtual void ResetValuesInCurrentColumn(uint32_t column, Vector& vectorB);

	virtual void CountXvalue(uint32_t row, Vector*& vectorX, Vector& vectorB);

	virtual void CountXValuesForIteration(uint32_t row, Vector*& vectorX, Vector*& vectorNewX, Vector*& baseB);

	virtual uint32_t SearchBestRow(uint32_t k);

	virtual void ChangeRows(uint32_t k, uint32_t best);
};

