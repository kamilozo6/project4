#include "Approximation.h"



Approximation::Approximation()
{
}


Approximation::~Approximation()
{
}

void Approximation::GaussWithOptimization()
{
	uint32_t size;
	for (uint32_t i = 2; i < GAUSS_OPTIMIZE_MAX_AGENTS; i++)
	{
		printf("%d\n", i);
		size = CountSizeFromAgentsValue(i);
		Matrix *baseA = Matrix::Create(size);
		Vector *baseB = Vector::Create(size);

		baseA->EvaluateProbability(i);
		baseB->EvaluateProbability(i);

		Vector *X = Methods::Gauss(baseA, baseB);

		delete baseA;
		delete baseB;
		delete X;
	}
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

