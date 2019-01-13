#pragma once
#include "Matrix.h"

#define MATRIX_MAP std::unordered_map<uint32_t, double_t>
#define COLUMN_MAP std::unordered_set<uint32_t>

class SparseMatrix :
	public Matrix
{
private:
	// array of maps, size is n*n
	MATRIX_MAP *matrixTable;
	COLUMN_MAP *rowsInColumn;
public:
	SparseMatrix();
	~SparseMatrix();
	static SparseMatrix* Create(uint32_t size);

	virtual void WriteToConsole();

	virtual double_t GetMatrixCell(uint32_t row, uint32_t column)
	{
		return matrixTable[row].count(column) == 1 ? matrixTable[row][column] : 0;
	}

	MATRIX_MAP& GetRowMap(uint32_t row)
	{
		return matrixTable[row];
	}

	virtual void SetMatrixCell(uint32_t row, uint32_t column, double_t value);

	virtual void ResetValuesInCurrentColumn(uint32_t column, Vector& vectorB);

	virtual void CountXvalue(uint32_t row, Vector*& vectorX, Vector& vectorB);

	virtual void CountXValuesForIteration(uint32_t row, Vector*& vectorX, Vector*& vectorNewX, Vector*& baseB);

	virtual uint32_t SearchBestRow(uint32_t k);

	virtual void ChangeRows(uint32_t k, uint32_t best);

	void ClearRow(uint32_t row);

	void CopyRow(uint32_t row, MATRIX_MAP &source);
};

