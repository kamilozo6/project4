#include "Approximation.h"
#include "SparseMatrix.h"
#include "NormalMatrix.h"
#include <Windows.h>



Approximation::Approximation()
{
}


Approximation::~Approximation()
{
}

void Approximation::GaussWithOptimization()
{
	uint32_t size;
	double_t time;
	std::map<uint32_t, double_t> times;
	std::map<uint32_t, double_t> buildTimes;

	for (uint32_t i = 2; i < GAUSS_OPTIMIZE_MAX_AGENTS; i++)
	{
		size = CountSizeFromAgentsValue(i);
		SparseMatrix *baseA = SparseMatrix::Create(size);
		Vector *baseB = Vector::Create(size);

		LARGE_INTEGER start, end;
		QueryPerformanceFrequency(&start);
		double_t freq = (double_t)start.QuadPart / 1000.0;
		QueryPerformanceCounter(&start);

		baseA->EvaluateProbability(i);
		baseB->EvaluateProbability(i);

		QueryPerformanceCounter(&end);
		buildTimes[i] = double_t(end.QuadPart - start.QuadPart) / freq;

		Vector *X = Methods::Gauss(baseA, baseB, &time);
		times[i] = time;

		delete baseA;
		delete baseB;
		delete X;
	}
	Approximate(2, times);
	Approximate(1, buildTimes);
}

void Approximation::GaussWithoutOptimization()
{
	uint32_t size;
	double_t time;
	std::map<uint32_t, double_t> times;
	std::map<uint32_t, double_t> buildTimes;

	for (uint32_t i = 2; i < GAUSS_MAX_AGENTS; i++)
	{
		size = CountSizeFromAgentsValue(i);
		NormalMatrix *baseA = NormalMatrix::Create(size);
		Vector *baseB = Vector::Create(size);

		LARGE_INTEGER start, end;
		QueryPerformanceFrequency(&start);
		double_t freq = (double_t)start.QuadPart / 1000.0;
		QueryPerformanceCounter(&start);

		baseA->EvaluateProbability(i);
		baseB->EvaluateProbability(i);

		QueryPerformanceCounter(&end);
		buildTimes[i] = double_t(end.QuadPart - start.QuadPart) / freq;

		Vector *X = Methods::Gauss(baseA, baseB, &time);
		times[i] = time;

		delete baseA;
		delete baseB;
		delete X;
	}
	Approximate(3, times);
	Approximate(1, buildTimes);
}

void Approximation::GaussSeidelWithOptimization()
{
	uint32_t size;
	double_t time;
	std::map<uint32_t, double_t> times;

	for (uint32_t i = 2; i < GAUSS_SEIDEL_OPTIMIZE_MAX_AGENTS; i++)
	{
		size = CountSizeFromAgentsValue(i);
		SparseMatrix *baseA = SparseMatrix::Create(size);
		Vector *baseB = Vector::Create(size);

		baseA->EvaluateProbability(i);
		baseB->EvaluateProbability(i);

		Vector *X = Methods::GaussSeidel(baseA, baseB, &time);
		times[i] = time;

		delete baseA;
		delete baseB;
		delete X;
	}
	Approximate(2, times);
}

void Approximation::Eigen()
{

	uint32_t size;
	double_t time;
	std::map<uint32_t, double_t> times;
	for (uint32_t i = 2; i < EIGEN_MAX_AGENTS; i++)
	{
		size = CountSizeFromAgentsValue(i);
		SparseMatrix *baseA = SparseMatrix::Create(size);
		Vector *baseB = Vector::Create(size);

		baseA->EvaluateProbability(i);
		baseB->EvaluateProbability(i);

		Methods::Eigen(baseA, baseB, &time);
		times[i] = time;

		delete baseA;
		delete baseB;
	}
	Approximate(1, times);
}

uint32_t Approximation::CountSizeFromAgentsValue(uint32_t agents)
{
	uint32_t size = 0;
	for (uint32_t i = 1; i <= agents + 1; i++)
	{
		size += i;
	}
	return size;
}

void Approximation::Approximate(uint32_t degree, std::map<uint32_t, double_t> times)
{
	std::map<uint32_t, double_t> coefficients;
	std::map<uint32_t, double_t> freeExpressions;
	fopen_s(&f1, "q1.txt", "a");
	fopen_s(&f2, "q2.txt", "a");
	fopen_s(&f3, "q3.txt", "a");
	fopen_s(&f4, "q4.txt", "a");

	for (auto pair : times) {
		fprintf(f3, "Czas dla iloœæi Agentów: ");
		fprintf(f3, "%d  %f\n", pair.first, pair.second);
	}
	fprintf(f3, "\n");

	for (uint32_t i = 0; i < 2 * degree + 1; i++)
	{
		coefficients[i] = 0;
		if (i <= degree)
			freeExpressions[i] = 0;
		for (auto pair : times)
		{
			coefficients[i] += pow(pair.first, i);
			if (i <= degree)
				freeExpressions[i] += pair.second * pow(pair.first, i);
		}
	}
	uint32_t size = degree + 1;
	NormalMatrix *A = NormalMatrix::Create(size);
	Vector *B = Vector::Create(size);


	for (uint32_t i = 0; i < degree + 1; i++)
	{
		for (uint32_t j = i; j < degree + 1 + i; j++)
		{
			A->SetMatrixCell(i, j - i, coefficients[j]);
		}
		B->SetVectorCell(i, freeExpressions[i]);
	}

	Vector *X = Methods::Gauss(A, B);

	for (int i = 0; i < degree + 1; i++) 
	{
		fprintf(f4, "Wspó³czynnik przy niewiadomej: ");
		fprintf(f4, "%f\n", X->GetVectorCell(i));
	}
	fprintf(f4, "\n");

	double_t result, error = 0;
	for (auto pair : times)
	{
		result = 0;
		for (uint32_t i = 0; i <= degree; i++)
		{
			result += pow(pair.first, i)*X->GetVectorCell(i);
		}
		error += pow(pair.second - result, 2);

	}
	error = sqrt(error);
	fprintf(f2, "B³ad aproksymacji:");
	fprintf(f2, "%f\n", error);

	result = 0;
	for (uint32_t i = 0; i <= degree; i++)
	{
		result += pow(500, i)*X->GetVectorCell(i);
	}
	fprintf(f1, "Wynik dla macierzy 100000: %f\n", result);
	//printf("%.5f\n", error);

	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
}

