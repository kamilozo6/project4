#include "NormalMatrix.h"



NormalMatrix::NormalMatrix() :
	Matrix(),
	matrixTable(NULL)
{
}


NormalMatrix::~NormalMatrix()
{
	for (uint32_t i = 0; i < matrixSize; i++)
	{
		delete[] matrixTable[i];
	}
	delete[] matrixTable;
}

NormalMatrix * NormalMatrix::Create(uint32_t size)
{
	NormalMatrix *newMatrix = new NormalMatrix();

	newMatrix->matrixSize = size;
	newMatrix->matrixTable = new double_t*[size];
	for (uint32_t i = 0; i < size; i++)
	{
		newMatrix->matrixTable[i] = new double_t[size];

		for (uint32_t j = 0; j < size; j++)
		{
			newMatrix->matrixTable[i][j] = 0;
		}
	}
	return newMatrix;
}

void NormalMatrix::WriteToConsole()
{
	for (uint32_t i = 0; i < matrixSize; i++)
	{
		for (uint32_t j = 0; j < matrixSize; j++)
		{
			printf("%.2f ", matrixTable[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void NormalMatrix::ResetValuesInCurrentColumn(uint32_t column, Vector & vectorB)
{
	for (uint32_t row = column + 1; row < matrixSize; row++)
	{
		if (matrixTable[row][column] == 0)
		{
			continue;
		}
		double_t m = matrixTable[row][column] / matrixTable[column][column];
		matrixTable[row][column] = 0;
		vectorB.SetVectorCell(row, vectorB.GetVectorCell(row) - m * vectorB.GetVectorCell(column));
		for (uint32_t j = column + 1; j < matrixSize; j++)
		{
			matrixTable[row][j] -= m * matrixTable[column][j];
		}
	}
}

void NormalMatrix::CountXvalue(uint32_t row, Vector *& vectorX, Vector & vectorB)
{
	vectorX->SetVectorCell(row, vectorB.GetVectorCell(row));
	for (uint32_t i = row + 1; i < matrixSize; i++)
	{
		vectorX->SetVectorCell(row, vectorX->GetVectorCell(row) - matrixTable[row][i] * vectorX->GetVectorCell(i));
	}
	vectorX->SetVectorCell(row, vectorX->GetVectorCell(row) / matrixTable[row][row]);
}

void NormalMatrix::CountXValuesForIteration(uint32_t row, Vector *& vectorX, Vector *& vectorNewX, Vector *& baseB)
{
	vectorNewX->SetVectorCell(row, baseB->GetVectorCell(row));
	for (uint32_t i = 0; i < matrixSize; i++)
	{
		if (i == row)
		{
			continue;
		}
		else if (i < row)
		{
			vectorNewX->SetVectorCell(row, vectorNewX->GetVectorCell(row) - vectorNewX->GetVectorCell(i) * matrixTable[row][i]);
		}
		else
		{
			vectorNewX->SetVectorCell(row, vectorNewX->GetVectorCell(row) - vectorX->GetVectorCell(i) * matrixTable[row][i]);
		}
	}
	vectorNewX->SetVectorCell(row, vectorNewX->GetVectorCell(row) / matrixTable[row][row]);
}

uint32_t NormalMatrix::SearchBestRow(uint32_t k)
{
	uint32_t best, actual, row = k;
	for (uint32_t value = k + 1; value < matrixSize; value++)
	{
		actual = abs(matrixTable[value][k]);
		best = abs(matrixTable[row][k]);
		if (actual > best)
		{
			row = value;
		}
	}
	return row;
}

void NormalMatrix::ChangeRows(uint32_t k, uint32_t best)
{
	double_t *help = matrixTable[k];
	matrixTable[k] = matrixTable[best];
	matrixTable[best] = help;
}
