#include "pch.h"
#include "Methods.h"
#include "SparseMatrix.h"
#include <Windows.h>
#include <Eigen/Sparse>

Methods::Methods()
{
}


Methods::~Methods()
{
}

Vector * Methods::Gauss(Matrix * baseA, Vector * baseB, double_t *time)
{
	Vector *vectorX = Vector::Create(baseB->GetVectorSize());

	LARGE_INTEGER start, end;
	QueryPerformanceFrequency(&start);
	double_t freq = (double_t)start.QuadPart;
	QueryPerformanceCounter(&start);

	for (uint32_t k = 0; k < baseA->GetMatrixSize() - 1; k++)
	{
		baseA->ResetValuesInCurrentColumn(k, *baseB);
	}

	for (int32_t i = baseA->GetMatrixSize() - 1; i >= 0; i--)
	{
		baseA->CountXvalue(i, vectorX, *baseB);
	}

	QueryPerformanceCounter(&end);
	if (time)
	{
		*time = double_t(end.QuadPart - start.QuadPart) / freq;
	}
	//vectorX->WriteToConsole();
	return vectorX;
}

Vector * Methods::GaussSeidel(Matrix * baseA, Vector * baseB, double_t *time)
{
	Vector *vectorX = Vector::Create(baseB->GetVectorSize()), *newX = Vector::Create(baseB->GetVectorSize()), *diff = Vector::Create(baseB->GetVectorSize());
	diff->SetVectorCell(0, 1);

	LARGE_INTEGER start, end;
	QueryPerformanceFrequency(&start);
	double_t freq = (double_t)start.QuadPart;
	QueryPerformanceCounter(&start);

	while (diff->CountNorm() > PRECISION)
	{
		for (uint32_t i = 0; i < vectorX->GetVectorSize(); i++)
		{
			baseA->CountXValuesForIteration(i, vectorX, newX, baseB);
		}
		diff->CopySubstract(vectorX, newX);
		vectorX->CopyValues(newX);
	}

	QueryPerformanceCounter(&end);
	if (time)
	{
		*time = double_t(end.QuadPart - start.QuadPart) / freq;
	}
	//vectorX->WriteToConsole();
	return vectorX;
}

void Methods::Eigen(Matrix * baseA, Vector * baseB, double_t * time)
{
	uint32_t size = baseA->GetMatrixSize();
	LARGE_INTEGER start, end;

	Eigen::SparseMatrix<double> eigA(size, size);
	Eigen::VectorXd eigB(size), eigX(size);

	for (uint32_t i = 0; i < size; i++)
	{
		for (auto pair : ((SparseMatrix*)baseA)->GetRowMap(i))
		{
			eigA.insert(i, pair.first) = pair.second;
		}
		eigB(i) = baseB->GetVectorCell(i);
	}

	Eigen::SparseLU<Eigen::SparseMatrix<double>> solv;
	solv.compute(eigA);
	QueryPerformanceFrequency(&start);
	double freq = (double)start.QuadPart;
	QueryPerformanceCounter(&start);

	eigX = solv.solve(eigB);

	QueryPerformanceCounter(&end);

	/*for (uint32_t i = 0; i < size; i++)
	{
		printf("%.5f\n", eigX(i));
	}
	printf("\n");*/
	
	if (time)
	{
		*time = double_t(end.QuadPart - start.QuadPart) / freq;
	}
}
