#include "pch.h"
#include "Methods.h"


Methods::Methods()
{
}


Methods::~Methods()
{
}

Vector * Methods::Gauss(Matrix * baseA, Vector * baseB)
{
	Vector *vectorX = Vector::Create(baseB->GetVectorSize());

	for (uint32_t k = 0; k < baseA->GetMatrixSize(); k++)
	{
		baseA->ResetValuesInCurrentColumn(k, *baseB);
	}

	for (int32_t i = baseA->GetMatrixSize() - 1; i >= 0; i--)
	{
		baseA->CountXvalue(i, vectorX, *baseB);
	}

	//vectorX->WriteToConsole();
	return vectorX;
}

Vector * Methods::GaussSeidel(Matrix * baseA, Vector * baseB)
{
	Vector *vectorX = Vector::Create(baseB->GetVectorSize()), *newX = Vector::Create(baseB->GetVectorSize()), *diff = Vector::Create(baseB->GetVectorSize());
	diff->SetVectorCell(0, 1);
	while (diff->CountNorm() > PRECISION)
	{
		for (uint32_t i = 0; i < vectorX->GetVectorSize(); i++)
		{
			baseA->CountXValuesForIteration(i, vectorX, newX, baseB);
		}
		diff->CopySubstract(vectorX, newX);
		vectorX->CopyValues(newX);
	}

	//vectorX->WriteToConsole();
	return vectorX;
}
