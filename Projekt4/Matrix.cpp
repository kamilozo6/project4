#include "pch.h"
#include "Matrix.h"


Matrix::Matrix() :
	matrixSize(NULL)
{
}


Matrix::~Matrix()
{
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
	SetMatrixCell(index, index, GetMatrixCell(index, index) - (unknownProb * (unknownProbNext - (double_t)1 / (double_t)(n - 1)) + yesProb * (yesProbNext - (double_t)1 / (double_t)(n - 1)) + noProb * (noProbNext - (double_t)1 / (double_t)(n - 1))));
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

