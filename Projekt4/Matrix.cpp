#include "pch.h"
#include "Matrix.h"


Matrix::Matrix() :
	matrixSize(NULL),
	matrixTable(nullptr)
{
}


Matrix::~Matrix()
{
	for (uint32_t i = 0; i < matrixSize; i++)
	{
		matrixTable[i].clear();
	}
	delete[] matrixTable;
}

/// <summary>
/// Creates and initializies new instance of Matrix class
/// </summary>
/// <param name="size">matrix table size</param>
/// <returns>new Matrix instance</returns>
Matrix* Matrix::Create(uint32_t size)
{
	Matrix *newMatrix = new Matrix();

	newMatrix->matrixSize = size;
	newMatrix->matrixTable = new MATRIX_MAP[size];
	newMatrix->rowsInColumn = new COLUMN_MAP[size];

	return newMatrix;
}

void Matrix::EvaluateProbability(uint32_t n)
{
	for (uint32_t yes = 0; yes <= n; yes++)
	{
		for (uint32_t no = 0; no <= n - yes; no++)
		{
			ProbablilityForSpecificCase(yes, no, n);
		}
	}
}

void Matrix::ProbablilityForSpecificCase(uint32_t yes, uint32_t no, uint32_t n)
{
	uint32_t index = ReturnIndex(yes, no, n);
	double_t yesProb, noProb, unknownProb;
	double_t yesProbNext, noProbNext, unknownProbNext;
	yesProb = (double_t)yes / (double_t)n;
	noProb = (double_t)no / (double_t)n;
	unknownProb = (double_t)(n - yes - no) / (double_t)n;

	yesProbNext = (double_t)yes / (double_t)(n - 1);
	noProbNext = (double_t)no / (double_t)(n - 1);
	unknownProbNext = (double_t)(n - yes - no) / (double_t)(n - 1);



	SetMatrixCell(index, index, 1);

	if (yes == 0 || no == 0)
	{
		return;
	}

	if ((yes + 1 + no <= n) && (yesProb > 0) && (unknownProbNext > 0))
	{
		SetMatrixCell(index, ReturnIndex(yes + 1, no, n), 0 - 2 * yesProb * unknownProbNext);
	}
	if ((no + 1 + yes <= n) && (noProb > 0) && (unknownProbNext > 0))
	{
		SetMatrixCell(index, ReturnIndex(yes, no + 1, n), 0 - 2 * noProb * unknownProbNext);
	}

	if ((yes - 1 >= 0) && (no - 1 >= 0) && (yesProb > 0) && (noProbNext > 0))
	{
		SetMatrixCell(index, ReturnIndex(yes - 1, no - 1, n), 0 - 2 * yesProb * noProbNext);
	}
	SetMatrixCell(index, index, matrixTable[index][index] - (unknownProb * (unknownProbNext - (double_t)1 / (double_t)(n - 1)) + yesProb * (yesProbNext - (double_t)1 / (double_t)(n - 1)) + noProb * (noProbNext - (double_t)1 / (double_t)(n - 1))));
}

uint32_t Matrix::ReturnIndex(uint32_t yes, uint32_t no, uint32_t n)
{
	uint32_t index = 0;

	for (uint32_t i = 1; i <= yes; i++)
	{
		index += n + 2 - i;
	}

	index += no;
	return index;
}

void Matrix::WriteToConsole()
{
	for (uint32_t i = 0; i < matrixSize; i++)
	{
		for (auto pair : matrixTable[i])
		{
			printf("%.2f ", pair.second);
		}
		printf("\n");
	}
}

Matrix & Matrix::operator=(Matrix *& input)
{
	matrixSize = input->GetMatrixSize();
	matrixTable = new MATRIX_MAP[matrixSize];
	rowsInColumn = new COLUMN_MAP[matrixSize];
	for (uint32_t i = 0; i < matrixSize; i++)
	{
		for (auto pair : input->GetRowMap(i))
		{
			matrixTable[i][pair.first] = pair.second;
			rowsInColumn[pair.first].insert(i);
		}
	}
	return *this;
}

void Matrix::SetMatrixCell(uint32_t row, uint32_t column, double_t value)
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
#include <map>
#include <set>
#include <functional>
#include <vector>

void Matrix::ResetValuesInCurrentColumn(uint32_t column, Vector & vectorB)
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
			matrixTable[row][pair.first] -= m * pair.second;
		}
	}
	for (auto row : toZeroCells)
	{
		SetMatrixCell(row, column, 0);
	}
	toZeroCells.clear();
}

void Matrix::CountXvalue(uint32_t row, Vector* & vectorX, Vector & vectorB)
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

void Matrix::CountXValuesForIteration(uint32_t row, Vector *& vectorX, Vector *& vectorNewX, Vector *& baseB)
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

