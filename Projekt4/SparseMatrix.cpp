#include "SparseMatrix.h"

#include <map>
#include <set>
#include <functional>
#include <vector>


SparseMatrix::SparseMatrix() :
	Matrix(),
	matrixTable(NULL),
	rowsInColumn(NULL)
{
}


SparseMatrix::~SparseMatrix()
{
	for (uint32_t i = 0; i < matrixSize; i++)
	{
		matrixTable[i].clear();
		rowsInColumn[i].clear();
	}
	delete[] matrixTable;
	delete[] rowsInColumn;
}

/// <summary>
/// Creates and initializies new instance of Matrix class
/// </summary>
/// <param name="size">matrix table size</param>
/// <returns>new Matrix instance</returns>
SparseMatrix* SparseMatrix::Create(uint32_t size)
{
	SparseMatrix *newMatrix = new SparseMatrix();

	newMatrix->matrixSize = size;
	newMatrix->matrixTable = new MATRIX_MAP[size];
	newMatrix->rowsInColumn = new COLUMN_MAP[size];

	return newMatrix;
}


void SparseMatrix::WriteToConsole()
{
	for (uint32_t i = 0; i < matrixSize; i++)
	{
		for (auto pair : matrixTable[i])
		{
			printf("%.2f ", pair.second);
		}
		printf("\n");
	}
	printf("\n");
}

void SparseMatrix::SetMatrixCell(uint32_t row, uint32_t column, double_t value)
{
	if (value == 0)
	{
		matrixTable[row].erase(column);
		rowsInColumn[column].erase(row);
	}
	else
	{
		matrixTable[row][column] = value;
		rowsInColumn[column].insert(row);
	}
}

void SparseMatrix::ResetValuesInCurrentColumn(uint32_t column, Vector & vectorB)
{
	std::set<uint32_t, std::greater<uint32_t>> sortedColumnSet(rowsInColumn[column].begin(), rowsInColumn[column].end());
	std::vector<uint32_t> toZeroCells;
	for (auto row : sortedColumnSet)
	{
		if (row <= column)
		{
			break;
		}
		toZeroCells.push_back(row);
		double_t m = matrixTable[row][column] / matrixTable[column][column];
		vectorB.SetVectorCell(row, vectorB.GetVectorCell(row) - m * vectorB.GetVectorCell(column));
		for (auto pair : matrixTable[column])
		{
			if (pair.first <= column)
			{
				continue;
			}
			SetMatrixCell(row, pair.first, GetMatrixCell(row, pair.first) - m * pair.second);
		}
	}
	for (auto row : toZeroCells)
	{
		SetMatrixCell(row, column, 0);
	}
	toZeroCells.clear();
}

void SparseMatrix::CountXvalue(uint32_t row, Vector* & vectorX, Vector & vectorB)
{
	vectorX->SetVectorCell(row, vectorB.GetVectorCell(row));
	for (auto pair : matrixTable[row])
	{
		if (pair.first <= row)
		{
			continue;
		}
		vectorX->SetVectorCell(row, vectorX->GetVectorCell(row) - pair.second * vectorX->GetVectorCell(pair.first));
	}
	vectorX->SetVectorCell(row, vectorX->GetVectorCell(row) / matrixTable[row][row]);
}

void SparseMatrix::CountXValuesForIteration(uint32_t row, Vector *& vectorX, Vector *& vectorNewX, Vector *& baseB)
{
	vectorNewX->SetVectorCell(row, baseB->GetVectorCell(row));
	for (auto pair : matrixTable[row])
	{
		if (pair.first == row)
		{
			continue;
		}
		else if (pair.first < row)
		{
			vectorNewX->SetVectorCell(row, vectorNewX->GetVectorCell(row) - vectorNewX->GetVectorCell(pair.first) * pair.second);
		}
		else
		{
			vectorNewX->SetVectorCell(row, vectorNewX->GetVectorCell(row) - vectorX->GetVectorCell(pair.first) * pair.second);
		}
	}
	vectorNewX->SetVectorCell(row, vectorNewX->GetVectorCell(row) / matrixTable[row][row]);
}

uint32_t SparseMatrix::SearchBestRow(uint32_t k)
{
	double_t best, actual;
	uint32_t row = k;
	std::set<uint32_t, std::greater<uint32_t>> sortedColumnSet(rowsInColumn[k].begin(), rowsInColumn[k].end());
	for (auto value : sortedColumnSet)
	{
		if (value == k)
		{
			break;
		}
		actual = abs(matrixTable[value][k]);
		best = abs(matrixTable[row][k]);
		if (actual > best)
		{
			row = value;
		}
	}
	return row;
}

void SparseMatrix::ChangeRows(uint32_t k, uint32_t best)
{
	if (k == best)
	{
		return;
	}
	MATRIX_MAP matK(matrixTable[k]), matBest(matrixTable[best]);
	ClearRow(k);
	ClearRow(best);

	CopyRow(best, matK);
	CopyRow(k, matBest);
}

void SparseMatrix::ClearRow(uint32_t row)
{
	std::vector<uint32_t> zeroColumns;
	for (auto pair : matrixTable[row])
	{
		zeroColumns.push_back(pair.first);
	}
	matrixTable->clear();
	for (auto value : zeroColumns)
	{
		rowsInColumn[value].erase(row);
	}
}

void SparseMatrix::CopyRow(uint32_t row, MATRIX_MAP &source)
{
	for (auto pair : source)
	{
		SetMatrixCell(row, pair.first, pair.second);
	}
}
